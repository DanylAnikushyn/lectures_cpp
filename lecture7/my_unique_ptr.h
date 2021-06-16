#pragma once
#include "cobject.h"

class MyUniquePtr
{
public:
    MyUniquePtr(CObject* ptr) noexcept;
    MyUniquePtr(const MyUniquePtr&) = delete;
    MyUniquePtr& operator=(const MyUniquePtr&) = delete;
    MyUniquePtr(MyUniquePtr&& other) noexcept;
    MyUniquePtr& operator=(MyUniquePtr&& other) noexcept;
    CObject& operator*() const noexcept;
    CObject* operator->() const noexcept;
    CObject* get() const noexcept;
    CObject* release() noexcept;
    void swap(MyUniquePtr& other) noexcept;
    ~MyUniquePtr() noexcept;
private:
    CObject* m_ptr;
};