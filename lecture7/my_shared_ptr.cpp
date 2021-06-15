#include "my_shared_ptr.h"
#include "cobject.h"

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
MySharedPtr& MySharedPtr::operator=(MySharedPtr& other)
{
    m_ctrl_block->ref_counter--;
    if (get_count() == 0) 
    {
        delete m_ctrl_block;
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
unsigned MySharedPtr::get_count() const
{
    return m_ctrl_block->ref_counter;
}
MySharedPtr::~MySharedPtr()
{
    m_ctrl_block->ref_counter--;
    if (get_count() == 0) 
    {
        delete m_ctrl_block;
        delete m_ptr;
    }
}