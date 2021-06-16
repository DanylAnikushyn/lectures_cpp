#include "cobject.h"
#include <iostream>

CObject::CObject(int a = 0) noexcept : m_a(a) 
{}
CObject::operator int() const noexcept
{
    return m_a;
}
void CObject::print() const
{
    std::cout << m_a << std::endl;
}
CObject::~CObject() noexcept
{}