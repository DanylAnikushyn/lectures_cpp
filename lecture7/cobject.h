#pragma once

class CObject 
{
public:
    CObject(int a) noexcept;
    operator int() const noexcept;
    void print() const;
    virtual ~CObject() noexcept;
private:
    int m_a;
};