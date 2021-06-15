#include <iostream>
#include "cobject.h"
#include "my_unique_ptr.h"

void test_my_unique_ptr()
{
    auto ptr1 = MyUniquePtr(new CObject(1));
    std::cout << "*ptr1 ";
    ptr1->print();
    std::cout << *ptr1 << std::endl;
    auto ptr2 = MyUniquePtr(new CObject(2));
    std::cout << "First ptr before swap : ";
    ptr1->print();
    std::cout << "Second ptr before swap : ";
    ptr2->print();
    ptr1.swap(ptr2);
    std::cout << "First ptr after swap : "; 
    ptr1->print();
    std::cout << "Second ptr after swap : ";
    ptr2->print();
    delete ptr2.release();
    if (!ptr2.get()) std::cout << "After release get() return nullptr" << std::endl;
    ptr2 = std::move(ptr1);
    if (ptr2.get() && !ptr1.get()) std::cout << "ptr1 is moved into ptr2" << std::endl; 
}

int main(int argc, char* argv[])
{
    test_my_unique_ptr();
    return 0;
}