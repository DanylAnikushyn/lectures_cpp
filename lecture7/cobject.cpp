#include "cobject.h"
#include <iostream>

CObject::CObject(int a = 0) : m_a(a)
{}
CObject::operator int() const
{
    return m_a;
}
void CObject::print() const
{
    std::cout << m_a << std::endl;
}
CObject::~CObject() 
{}