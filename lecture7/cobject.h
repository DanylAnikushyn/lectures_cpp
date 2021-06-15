#pragma once

class CObject 
{
public:
    CObject(int a);
    operator int() const;
    void print() const;
private:
    int m_a;
};