#include <iostream>
#include "cobject.h"
#include "my_unique_ptr.h"
#include "my_shared_ptr.h"

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

void test_my_shared_ptr()
{
    auto ptr1 = MySharedPtr(new CObject(1));
    {
        auto ptr2(ptr1);
        std::cout << "ptr1 ref count in scope: " << ptr1.get_count() << std::endl;
        std::cout << "ptr2 ref count in scope: " << ptr2.get_count() << std::endl;
    }
    std::cout << "ptr1 ref count: " << ptr1.get_count() << std::endl;
    auto ptr2(ptr1);
    auto ptr3 = MySharedPtr(new CObject(3));
    std::cout << "ptr2 before ptr2 = ptr3: ";
    ptr2->print();
    ptr2 = ptr3;
    std::cout << "ptr1 ref count after ptr2 = ptr3: " << ptr1.get_count() << std::endl;
    std::cout << "ptr3 ref count after ptr2 = ptr3: " << ptr2.get_count() << std::endl;
    std::cout << "ptr2 after ptr2 = ptr3: ";
    ptr2->print();
}

void test_my_weak_ptr()
{
    auto ptr1 = MySharedPtr(new CObject(1));
    auto ptr2 = MySharedPtr(ptr1);
    auto w_ptr1 = MyWeakPtr(ptr2);
    std::cout << w_ptr1.use_count() << std::endl;
    auto ptr3 = w_ptr1.lock();
    if (ptr3.get() != nullptr) std::cout << *ptr3 << std::endl;
    ptr3 = w_ptr1;
    std::cout << *ptr3 << std::endl;
    {
        auto ptr4 = MySharedPtr(new CObject(4));
        w_ptr1 = ptr4;
    }
    try 
    {
        ptr3 = w_ptr1;
    }
    catch(std::runtime_error e)
    {
        std::cout << e.what() << std::endl;
    }
    auto ptr5 = w_ptr1.lock();
    if (ptr5.get() != nullptr) std::cout << *ptr5 << std::endl;
}

int main(int argc, char* argv[])
{
//    test_my_unique_ptr();
//    test_my_shared_ptr();
    test_my_weak_ptr();
    return 0;
}