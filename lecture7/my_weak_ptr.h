#pragma once
#include "control_block.h"
#include "my_shared_ptr.h"

class MySharedPtr;

class MyWeakPtr
{
public:
    MyWeakPtr(const MySharedPtr& other);
    MyWeakPtr(const MyWeakPtr& other);
    MyWeakPtr& operator=(const MySharedPtr& other);
    MyWeakPtr& operator=(const MyWeakPtr& other);
    std::size_t use_count() const;
    bool expired() const;
    MySharedPtr lock() const;
    ~MyWeakPtr();
private:
    CObject* m_ptr;
    ControlBlock* m_ctrl_block;

    friend class MySharedPtr;
};