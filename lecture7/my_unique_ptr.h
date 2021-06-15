#pragma once
#include "cobject.h"

class MyUniquePtr
{
public:
    MyUniquePtr(CObject* ptr);
    MyUniquePtr(const MyUniquePtr&) = delete;
    MyUniquePtr& operator=(const MyUniquePtr&) = delete;
    MyUniquePtr(MyUniquePtr&& other);
    MyUniquePtr& operator=(MyUniquePtr&& other);
    CObject& operator*() const;
    CObject* operator->() const;
    CObject* get() const;
    CObject* release();
    void swap(MyUniquePtr& other);
    ~MyUniquePtr();
private:
    CObject* m_ptr;
};