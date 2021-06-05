#include "object.h"
#include <iostream>

Object::Object() : m_left_in_use(0)
{
}

void Object::init(int a, int b, int left_in_use)
{
    m_state.inUse.m_a = a;
    m_state.inUse.m_b = b;
    m_left_in_use = left_in_use;
}

bool Object::isInUse() const
{
    return m_left_in_use > 0;
}

Object* Object::getNext() const
{
    return m_state.next;
}

void Object::setNext(Object* next)
{
    m_state.next = next;
}

bool Object::method()
{
    if (!isInUse()) return false;
    --m_left_in_use;
    std::cout << "Left iterations: " << m_left_in_use << std::endl;
    std::cout << "Doing some important stuff: a + b = " 
                << m_state.inUse.m_a + m_state.inUse.m_b << std::endl; 
    return m_left_in_use == 0;
}
