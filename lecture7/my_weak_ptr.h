#pragma once
#include "control_block.h"
#include "my_shared_ptr.h"

class MySharedPtr;

class MyWeakPtr
{
public:
    MyWeakPtr(const MySharedPtr& other) noexcept;
    MyWeakPtr(const MyWeakPtr& other) noexcept;
    MyWeakPtr& operator=(const MySharedPtr& other) noexcept;
    MyWeakPtr& operator=(const MyWeakPtr& other) noexcept;
    std::size_t use_count() const noexcept;
    bool expired() const noexcept;
    MySharedPtr lock() const;
    ~MyWeakPtr() noexcept;
private:
    CObject* m_ptr;
    ControlBlock* m_ctrl_block;

    friend class MySharedPtr;
};