#ifndef OBJECT_H
#define OBJECT_H
class Object 
{
public:
    Object();

    // init object, without init all possibel objects are created, but 
    // not initialized and therefore not used
    void init(int a, int b, int left_in_use);
    //checking if current object from object pool is in use
    bool isInUse() const;

    // get next object in object pool
    Object* getNext() const;
    // set next object in object pool
    void setNext(Object* next);

    // method with important calculations
    bool method();
private:
    // how many iterations of method left
    int m_left_in_use;
    // eather object is initialized (inUse structure)
    // or object keeping pointer to next uninitialized object 
    union 
    {
        struct
        {
            int m_a, m_b;
        } inUse;

        Object* next;
    } m_state;
};
#endif