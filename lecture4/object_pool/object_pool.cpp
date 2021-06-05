#include "object_pool.h"
#include "object.h"
#include <iostream>

ObjectPool::ObjectPool()
{
    m_first_object = &m_objects[0];

    for (int i = 0; i < m_pool_size - 1; ++i)
    {
        m_objects[i].setNext(&m_objects[i + 1]);
    }
    m_objects[m_pool_size - 1].setNext(nullptr);
}

void ObjectPool::create(int a, int b, int left_in_use)
{
    Object* new_object = m_first_object;
    m_first_object = new_object->getNext();
    new_object->init(a, b, left_in_use);
}

void ObjectPool::method()
{
    for (int i = 0; i < m_pool_size; ++i)
    {
        if (m_objects[i].method())
        {
            m_objects[i].setNext(m_first_object);
            m_first_object = &m_objects[i];
        }
    }
}