#include "my_unique_ptr.h"

MyUniquePtr::MyUniquePtr(CObject* ptr) noexcept : m_ptr(ptr)
{}
MyUniquePtr::MyUniquePtr(MyUniquePtr&& other) noexcept
{
    m_ptr = other.m_ptr;
    other.m_ptr = nullptr;
}
MyUniquePtr& MyUniquePtr::operator=(MyUniquePtr&& other) noexcept
{
    if (this == &other) return *this;
    m_ptr = other.m_ptr;
    other.m_ptr = nullptr;
    return *this;
}
CObject& MyUniquePtr::operator*() const noexcept
{
    return *get();
}
CObject* MyUniquePtr::operator->() const noexcept
{
    return get();
}
CObject* MyUniquePtr::get() const noexcept
{
    return m_ptr;
}
CObject* MyUniquePtr::release() noexcept
{
    CObject* return_ptr = m_ptr;
    m_ptr = nullptr;
    return return_ptr;
}
void MyUniquePtr::swap(MyUniquePtr& other) noexcept {
    CObject* temp = other.m_ptr;
    other.m_ptr = m_ptr;
    m_ptr = temp;
}
MyUniquePtr::~MyUniquePtr() noexcept
{
    delete m_ptr;
}