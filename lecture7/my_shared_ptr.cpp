#include "my_shared_ptr.h"
#include "cobject.h"
#include <stdexcept>

MySharedPtr::MySharedPtr(CObject* ptr) : m_ptr(ptr)
{
    m_ctrl_block = new ControlBlock;
    m_ctrl_block->ref_counter = 1;
}
MySharedPtr::MySharedPtr(const MySharedPtr& other)
{
    m_ctrl_block = other.m_ctrl_block;
    m_ctrl_block->ref_counter++;
    m_ptr = other.m_ptr;
}
MySharedPtr::MySharedPtr(const MyWeakPtr& other)
{
    if (other.expired()) 
    {
        throw std::runtime_error("bad_weak_ptr");
    }
    m_ctrl_block = other.m_ctrl_block;
    m_ctrl_block->ref_counter++;
    m_ptr = other.m_ptr;
}
MySharedPtr& MySharedPtr::operator=(MySharedPtr& other)
{
    m_ctrl_block->ref_counter--;
    if (get_count() == 0) 
    {
        if(m_ctrl_block->weak_counter == 0) delete m_ctrl_block;
        delete m_ptr;
    }
    m_ctrl_block = other.m_ctrl_block;
    m_ctrl_block->ref_counter++;
    m_ptr = other.m_ptr;
    return *this;
}
CObject& MySharedPtr::operator*() const
{
    return *get();
}
CObject* MySharedPtr::operator->() const
{
    return get();
}
CObject* MySharedPtr::get() const
{
    return m_ptr;
}
std::size_t MySharedPtr::get_count() const
{
    return m_ctrl_block->ref_counter;
}
MySharedPtr::~MySharedPtr()
{
    if (--m_ctrl_block->ref_counter == 0) 
    {
        if(m_ctrl_block->weak_counter == 0) delete m_ctrl_block;
        delete m_ptr;
    }
}