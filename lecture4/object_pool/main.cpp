#include "object_pool.h"

int main()
{
    ObjectPool obj_pool;
    obj_pool.create(2, 2, 4);
    obj_pool.create(1, 7, 2);
    obj_pool.method();
    obj_pool.method();
    obj_pool.method();
    obj_pool.method();
    obj_pool.create(0, 0, 1);
    obj_pool.method();
    obj_pool.method();
    return 0;
}