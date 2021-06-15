#pragma once
#include "cobject.h"
#include "control_block.h"

class MySharedPtr
{
public:
    MySharedPtr(CObject* ptr);
    MySharedPtr(const MySharedPtr& other);
    MySharedPtr& operator=(MySharedPtr& other);
    CObject& operator*() const;
    CObject* operator->() const;
    CObject* get() const;
    unsigned get_count() const;
    ~MySharedPtr();
private:
    CObject* m_ptr;
    ControlBlock* m_ctrl_block;
};