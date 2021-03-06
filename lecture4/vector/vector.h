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
    Vector(Vector&& other) noexcept;
    Vector(std::initializer_list<T> init);

    Vector& operator=(const Vector& other);
    Vector& operator=(Vector&& other) noexcept;
    Vector& operator=(std::initializer_list<T> init); 

    iterator begin() const noexcept;
    iterator end() const noexcept;
 
    T* data() noexcept;
    void swap(Vector& other) noexcept;

    T& operator[](size_t index);
    const T& operator[](size_t index) const;

    T& at(size_t index);
    const T& at(size_t index) const;

    size_t size() const noexcept;
    size_t capacity() const noexcept;
    bool empty() const noexcept;

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

    void shrink_to_fit();

    ~Vector();
private:
    // reallocate m_array automatically, if m_size >= m_capacity
    void reallocate();
    // reallocate
    void reallocate(size_t size);

    T* m_array;
    size_t m_size;
    size_t m_capacity;
};

#include "vector.tpp"
#endif