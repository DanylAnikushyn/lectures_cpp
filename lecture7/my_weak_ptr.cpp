#include "my_weak_ptr.h"

MyWeakPtr::MyWeakPtr(const MySharedPtr& other)  noexcept
{
    m_ctrl_block = other.m_ctrl_block;
    m_ctrl_block->weak_counter++;
    m_ptr = other.m_ptr;
}
MyWeakPtr::MyWeakPtr(const MyWeakPtr& other) noexcept
{
    m_ctrl_block = other.m_ctrl_block;
    m_ctrl_block->weak_counter++;
    m_ptr = other.m_ptr;
}
MyWeakPtr& MyWeakPtr::operator=(const MySharedPtr& other) noexcept
{
    m_ctrl_block->weak_counter--;
    if(m_ctrl_block->weak_counter == 0 && expired()) 
    {
        delete m_ctrl_block;
    }
    m_ctrl_block = other.m_ctrl_block;
    m_ctrl_block->weak_counter++;
    return *this;
}
MyWeakPtr& MyWeakPtr::operator=(const MyWeakPtr& other) noexcept
{
    m_ctrl_block->weak_counter--;
    if(m_ctrl_block->weak_counter == 0)
    {
        delete m_ctrl_block;
    }
    m_ctrl_block = other.m_ctrl_block;
    m_ctrl_block->weak_counter++;
    return *this;
}
std::size_t MyWeakPtr::use_count() const noexcept
{
    return m_ctrl_block->ref_counter;
}
bool MyWeakPtr::expired() const noexcept
{
    return m_ctrl_block->ref_counter == 0;
}
MySharedPtr MyWeakPtr::lock() const 
{
    if (expired()) return MySharedPtr(nullptr); 
    else return MySharedPtr(*this);
}
MyWeakPtr::~MyWeakPtr() noexcept
{
    m_ctrl_block->weak_counter--;
    if(m_ctrl_block->weak_counter == 0 && expired())
    {
        delete m_ctrl_block;
    }
}