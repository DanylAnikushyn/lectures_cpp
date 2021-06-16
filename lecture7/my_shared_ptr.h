#pragma once
#include "cobject.h"
#include "control_block.h"
#include "my_weak_ptr.h"

class MyWeakPtr;

class MySharedPtr
{
public:
    MySharedPtr(CObject* ptr);
    MySharedPtr(const MySharedPtr& other) noexcept;
    MySharedPtr(const MyWeakPtr& other);
    MySharedPtr& operator=(MySharedPtr& other) noexcept;
    CObject& operator*() const noexcept;
    CObject* operator->() const noexcept;
    CObject* get() const noexcept;
    std::size_t get_count() const noexcept;
    ~MySharedPtr() noexcept;
private:
    CObject* m_ptr;
    ControlBlock* m_ctrl_block;

    friend class MyWeakPtr;
};