#ifndef VECTOR_H
#define VECTOR_H
#include <cstddef>
#include <initializer_list>
template <typename T>
class Vector
{
public:
    using iterator = T*;

    Vector();
    explicit Vector(size_t size, const T& value = T());
    Vector(const Vector& other);
    Vector(Vector&& other);
    Vector(std::initializer_list<T> init);

    Vector& operator=(const Vector& other);
    Vector& operator=(std::initializer_list<T> init); 

    iterator begin() const;
    iterator end() const;

    T& operator[](size_t index);
    const T& operator[](size_t index) const;

    T& at(size_t index);
    const T& at(size_t index) const;

    size_t size() const;
    size_t capacity() const;
    bool empty() const;

    void resize(size_t size, const T& value = T());

    void clear();
    void reserve(size_t size);

    iterator erase(iterator place);
    iterator erase(iterator first, iterator last);
    
    void pop_back();

    void push_back(const T& value);
    void insert(iterator place, const T& value);
    template <typename... Args>
    void emplace_back(Args&&... args);
    template <typename... Args>
    void emplace(iterator place, Args&&... args);

    ~Vector();
private:
    void allocate();

    T* m_array;
    size_t m_size;
    size_t m_capacity;
};

#include "vector.tpp"
#endif