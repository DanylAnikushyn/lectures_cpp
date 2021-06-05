#ifndef OBJECT_POOL_H
#define OBJECT_POOL_H
#include "object.h"
class ObjectPool
{
public:
    ObjectPool();
    // adding object to a pool
    void create(int a, int b, int left_in_use);
    // calling metohod on all available objects in pool
    void method();
private:
    // number of all possible objects in poo;
    static const int m_pool_size = 100;
    // object pool
    Object m_objects[m_pool_size];

    // pointer on first object in free list
    Object* m_first_object;
};
#endif