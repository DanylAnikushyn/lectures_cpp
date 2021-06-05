#include <utility>
#include <stdexcept>
#include <sstream>
#include <iostream>
template <typename T>
void Vector<T>::allocate()
{
    if (m_size >= m_capacity)
    {
        m_capacity = 2 * m_size;

        T* new_array = new T[m_capacity];
        for (int i = 0; i < m_size; ++i)
        {
            new_array[i] = m_array[i];
        }
        delete[] m_array;
        m_array = new_array;
    }
}

template <typename T>
Vector<T>::Vector() : m_size(0), m_capacity(1)
{
    m_array = new T[m_capacity];
}

template <typename T>
Vector<T>::Vector(size_t size, const T& value) : m_size(size), m_capacity(size)
{
    m_array = new T[m_capacity];
    for (int i = 0; i < m_size; ++i)
    {
        m_array[i] = value;
    }
}

template <typename T>
Vector<T>::Vector(const Vector<T>& other)
{
    m_size = other.m_size;
    m_capacity = other.m_capacity;
    m_array = new T[m_capacity];
    for (int i = 0; i < m_size; ++i)
    {
        m_array[i] = other.m_array[i];
    }
}

template <typename T>
Vector<T>::Vector(Vector<T>&& other) 
    : m_array(std::move(other.m_array)), m_size(std::move(other.m_size)), m_capacity(std::move(other.m_capacity))
{
    other.m_array = nullptr;
    other.m_size = 0;
    other.m_size = 0;
}

template <typename T>
Vector<T>::Vector(std::initializer_list<T> init)
{
    m_size = 0;
    size_t init_size = init.size();
    m_capacity = init.size();
    m_array = new T[m_capacity];
    for (auto elem : init) 
    {
        m_array[m_size++] = elem;
    }
}

template <typename T>
Vector<T>& Vector<T>::operator=(const Vector<T>& other)
{   
    if (this != &other)
    {   
        resize(other.size());
        for (int i = 0; i < size(); ++i)
        {
            m_array[i] = other.m_array[i];
        }
    }
    return *this;
}

template <typename T>
Vector<T>& Vector<T>::operator=(std::initializer_list<T> init)
{
    resize(0);
    m_size = 0;
    size_t init_size = init.size();
    m_capacity = init.size();
    m_array = new T[m_capacity];
    for (auto elem : init) 
    {
        m_array[m_size++] = elem;
    }
    return *this;
} 

template <typename T>
typename Vector<T>::iterator Vector<T>::begin() const
{
    return m_array;
}

template <typename T>
typename Vector<T>::iterator Vector<T>::end() const
{
    return m_array + m_size;
}

template <typename T>
T& Vector<T>::operator[](size_t index)
{
    return m_array[index];
}

template <typename T>
const T& Vector<T>::operator[](size_t index) const
{
    return m_array[index];
}

template <typename T>
T& Vector<T>::at(size_t index)
{
    if (index >= 0 && index < m_size)
    {
        return m_array[index];
    }
    else 
    {
        std::stringstream err_msg;
        err_msg << "out_of_range exception with index [" << index << "]\n"; 
        throw std::out_of_range(err_msg.str());
    }
}

template <typename T>
const T& Vector<T>::at(size_t index) const
{
    if (index >= 0 && index < m_size)
    {
        return m_array[index];
    }
    else 
    {
        std::stringstream err_msg;
        err_msg << "with index [" << index << "]\n"; 
        throw std::out_of_range(err_msg.str());
    }
}

template <typename T>
size_t Vector<T>::size() const
{
    return m_size;
}

template <typename T>
size_t Vector<T>::capacity() const
{
    return m_capacity;
}

template <typename T>
bool Vector<T>::empty() const
{
    return m_size == 0 ? true : false;
}

template <typename T>
void Vector<T>::resize(size_t size, const T& value)
{
    if (m_size < size) 
    {
        size_t prev_size = m_size;
        m_size = size;
        allocate();
        for (int i = prev_size; i != m_size; ++i)
        {
            m_array[i] = value;
        }
    }
    else 
    {
        m_size = size;
    }
}

template <typename T>
void Vector<T>::clear()
{
    delete[] m_array;
    m_size = 0;
    m_array = new T[m_capacity];
}

template <typename T>
void Vector<T>::reserve(size_t size)
{
    if (size < m_capacity)
    {
        m_capacity = size;
        T* new_array = new T[m_capacity];
        for (int i = 0; i < m_size; ++i)
        {
            new_array[i] = m_array[i];
        }
        delete[] m_array;
        m_array = new_array;
    }
}

template<typename T>
typename Vector<T>::iterator Vector<T>::erase(iterator place)
{
    if (place >= begin() && place < end())
    {
        ptrdiff_t diff = end() - place;
        size_t dest = m_size - diff;

        for (int i = dest; i < m_size - 1; ++i)
        {
            m_array[i] = m_array[i + 1];
        }
        --m_size;
        return place;
    }
    else 
    {
        throw std::out_of_range("invalid iterator");
    }
}

template <typename T>
typename Vector<T>::iterator Vector<T>::erase(iterator first, iterator last)
{
    if (first <= last && first >= begin() && last < end())
    {
        ptrdiff_t diff_first = end() - first;
        size_t dest = m_size - diff_first;
        ptrdiff_t diff_last = last - first;

        for (int i = dest; i < m_size - 1; ++i)
        {
            m_array[i] = m_array[i + diff_last];
        }
        m_size -= diff_last;
        return first;
    }
    else 
    {
        throw std::out_of_range("invalid iterators");
    }
}

template <typename T>
void Vector<T>::pop_back()
{
    --m_size;
}

template<typename T>
void Vector<T>::push_back(const T& value)
{
    emplace_back(value); 
}

template<typename T>
void Vector<T>::insert(iterator place, const T& value)
{
    emplace(place, value);
}

template<typename T>
template<typename... Args>
void Vector<T>::emplace_back(Args&& ... args)
{
    allocate();
    m_array[m_size++] = T(std::forward<Args>(args)...);
}

template<typename T>
template<typename... Args>
void Vector<T>::emplace(iterator place, Args&& ... args)
{
    if(place >= begin() && place <= end())
    {
        ptrdiff_t diff = end() - place;
        size_t dest = m_size - diff;

        allocate();
        ++m_size;
        for (int i = m_size ; i > dest; --i)
        {
            m_array[i] = m_array[i - 1];
        }
        m_array[dest] = T(std::forward<Args>(args)...);
    }
    else 
    { 
        throw std::out_of_range("invalid iterator");
    }
}

template <typename T>
Vector<T>::~Vector()
{
    if(m_array) delete[] m_array;
}