add_compile_options(-Wall -pedantic)

# add the executable
add_executable(pointers_test test.cpp cobject.cpp cobject.h control_block.h my_unique_ptr.cpp my_unique_ptr.h 
        my_shared_ptr.cpp my_shared_ptr.h my_weak_ptr.cpp my_weak_ptr.h)
