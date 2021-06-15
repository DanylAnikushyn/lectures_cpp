#pragma once

class CObject 
{
public:
    CObject(int a);
    operator int() const;
    void print() const;
    virtual ~CObject();
private:
    int m_a;
};