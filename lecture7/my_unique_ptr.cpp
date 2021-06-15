#include "my_unique_ptr.h"

MyUniquePtr::MyUniquePtr(CObject* ptr) : m_ptr(ptr)
{}
MyUniquePtr::MyUniquePtr(MyUniquePtr&& other)
{
    m_ptr = other.m_ptr;
    other.m_ptr = nullptr;
}
MyUniquePtr& MyUniquePtr::operator=(MyUniquePtr&& other)
{
    if (this == &other) return *this;
    m_ptr = other.m_ptr;
    other.m_ptr = nullptr;
    return *this;
}
CObject& MyUniquePtr::operator*() const
{
    return *get();
}
CObject* MyUniquePtr::operator->() const
{
    return get();
}
CObject* MyUniquePtr::get() const
{
    return m_ptr;
}
CObject* MyUniquePtr::release()
{
    CObject* return_ptr = m_ptr;
    m_ptr = nullptr;
    return return_ptr;
}
void MyUniquePtr::swap(MyUniquePtr& other) {
    CObject* temp = other.m_ptr;
    other.m_ptr = m_ptr;
    m_ptr = temp;
}
MyUniquePtr::~MyUniquePtr()
{
    delete m_ptr;
}