#include <iostream>
#include <stdexcept>
#include <fstream>
#include <vector>

class CannotOpenFileException : public std::exception {
public:
    const char* what() const noexcept override {
        return "Cannot open a file\n";
    }
};

class CannotCalculateSizeException : public std::exception {
public:
    const char* what() const noexcept override {
        return "Cannot calculate size of a file\n";
    }
};

class CannotReadFileException : public std::exception {
public:
    const char* what() const noexcept override {
        return "Cannot read a file\n";
    }
};

class CannotCloseFileException : public std::exception {
public:
    const char* what() const noexcept override {
        return "Cannot close a file\n";
    }
};


// version with custom exceptions
void read_file_into_buffer(const  std::string& filename) {
    try {

        std::ifstream file(filename, std::ios::binary | std::ios::ate);
        if (!file.good()) throw CannotOpenFileException();

        // probably set failbit isnt possible at this point, because
        // one(?) reason to failbit to be set is not good stream before
        // set badbit is possible
        std::streamsize size = file.tellg();
        if (file.fail() || file.bad()) throw CannotCalculateSizeException();
        
        file.seekg(0, std::ios::beg);
        auto buffer = std::vector<char>();
        if (file.read(buffer.data(), size))
        {
            std::cout << "File is read!" << std::endl;
        }
        else {
            throw CannotReadFileException();
        }

        // std::ifstream::close sets failbit if operation fails
        file.close();
        if (file.fail()) throw CannotCloseFileException();
    }
    catch (const std::bad_alloc& exc) {
        std::cerr << "No memory to allocate for buffer : " << exc.what() << "\n";  
        throw;
    }
    catch (const std::exception& exc) {
        std::cerr << exc.what(); 
        throw;
    }
    catch (...) {
        std::cerr << "Encountered other error\n";
        throw;
    }
}

// much cleaner variant with exceptions from io library
void read_file_into_buffer_alternative(const std::string& filename)
{
    std::ifstream file;
    // when one of these flags is set exception std::ifstream::failure occurs
    file.exceptions(std::ifstream::eofbit | std::ifstream::failbit | std::ifstream::badbit);
    try {
        file.open(filename, std::ios::binary | std::ios::ate);
        std::streamsize size = file.tellg();
        file.seekg(0, std::ios::beg);
        auto buffer = std::vector<char>();
        if (file.read(buffer.data(), size))
        {
            std::cout << "File is read!" << std::endl;
        }
        file.close();
    }
    catch (const std::ifstream::failure& exc) {
        std::cerr << "Exception opening/reading/closing file\n";
        throw;
    }
    catch (const std::bad_alloc& exc) {
        std::cerr << "No memory to allocate for buffer : " << exc.what() << "\n";  
        throw;
    }
    catch (...) {
        std::cerr << "Encountered other error\n";
        throw;
    }
}

enum class ErrorCode {
    SUCCESS,
    NO_FILE,
    NO_SIZE,
    NO_READ,
    NO_CLOS
};

// version with error codes
ErrorCode read_file_into_buffer_error_code(const  std::string& filename) {
    std::ifstream file(filename, std::ios::binary | std::ios::ate);
    if (!file.good()) return ErrorCode::NO_FILE;
    std::streamsize size = file.tellg();
    if (file.fail() || file.bad()) return ErrorCode::NO_SIZE;
    file.seekg(0, std::ios::beg);
    auto buffer = std::vector<char>();
    buffer.reserve(size);
    if (file.read(buffer.data(), size))
    {
        std::cout << "File is read!" << std::endl;
    }
    else {
        return ErrorCode::NO_READ;
    }
    file.close();
    if (file.fail()) return ErrorCode::NO_CLOS;
    return ErrorCode::SUCCESS;
}

int main() {
    auto error_code = read_file_into_buffer_error_code("test.txt");
    switch (error_code) {
        case ErrorCode::SUCCESS: std::cout << "Success!\n"; break;
        case ErrorCode::NO_FILE: std::cerr << "Cannot open a file\n"; return -1;
        case ErrorCode::NO_SIZE: std::cerr << "Cannot calculate size of a file\n"; return -1;
        case ErrorCode::NO_READ: std::cerr << "Cannot read a file\n"; return -1;
        case ErrorCode::NO_CLOS: std::cerr << "Cannot close a file\n"; return -1;
    }
    // read_file_into_buffer_alternative("test.txt");
    // read_file_into_buffer("test.txt");
    return 0;
}
