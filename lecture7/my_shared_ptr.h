#pragma once
#include "cobject.h"
#include "control_block.h"
#include "my_weak_ptr.h"

class MyWeakPtr;

class MySharedPtr
{
public:
    MySharedPtr(CObject* ptr);
    MySharedPtr(const MySharedPtr& other);
    MySharedPtr(const MyWeakPtr& other);
    MySharedPtr& operator=(MySharedPtr& other);
    CObject& operator*() const;
    CObject* operator->() const;
    CObject* get() const;
    std::size_t get_count() const;
    ~MySharedPtr();
private:
    CObject* m_ptr;
    ControlBlock* m_ctrl_block;

    friend class MyWeakPtr;
};