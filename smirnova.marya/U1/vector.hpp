#ifndef SMIRNOVA_VECTOR_HPP
#define SMIRNOVA_VECTOR_HPP

#include <cstddef>
#include <utility>

namespace smirnova
{
  template< typename T >
  class Vector
  {
  public:
    Vector();
    Vector(const Vector& other);
    Vector& operator=(const Vector& other);
    ~Vector();

    void push_back(const T& value);

    T& operator[](size_t index);
    const T& operator[](size_t index) const;

    size_t size() const;

    T* begin();
    T* end();

    const T* begin() const;
    const T* end() const;

  private:
    void reserve(size_t newCapacity);

    T* data_;
    size_t size_;
    size_t capacity_;
  };

  template< typename T >
  Vector< T >::Vector() :
    data_(nullptr),
    size_(0),
    capacity_(0)
  {}

  template< typename T >
  Vector< T >::Vector(const Vector& other) :
    data_(nullptr),
    size_(other.size_),
    capacity_(other.capacity_)
  {
    if (capacity_ == 0)
    {
      return;
    }

    data_ = new T[capacity_];

    for (size_t i = 0; i < size_; ++i)
    {
      data_[i] = other.data_[i];
    }
  }

  template< typename T >
  Vector< T >& Vector< T >::operator=(const Vector& other)
  {
    if (this == &other)
    {
      return *this;
    }

    T* newData = nullptr;

    if (other.capacity_ > 0)
    {
      newData = new T[other.capacity_];

      for (size_t i = 0; i < other.size_; ++i)
      {
        newData[i] = other.data_[i];
      }
    }

    delete[] data_;

    data_ = newData;
    size_ = other.size_;
    capacity_ = other.capacity_;

    return *this;
  }

  template< typename T >
  Vector< T >::~Vector()
  {
    delete[] data_;
  }

  template< typename T >
  void Vector< T >::push_back(const T& value)
  {
    if (size_ == capacity_)
    {
      reserve(capacity_ == 0 ? 1 : capacity_ * 2);
    }

    data_[size_] = value;
    ++size_;
  }

  template< typename T >
  T& Vector< T >::operator[](size_t index)
  {
    return data_[index];
  }

  template< typename T >
  const T& Vector< T >::operator[](size_t index) const
  {
    return data_[index];
  }

  template< typename T >
  size_t Vector< T >::size() const
  {
    return size_;
  }

  template< typename T >
  T* Vector< T >::begin()
  {
    return data_;
  }

  template< typename T >
  T* Vector< T >::end()
  {
    return data_ + size_;
  }

  template< typename T >
  const T* Vector< T >::begin() const
  {
    return data_;
  }

  template< typename T >
  const T* Vector< T >::end() const
  {
    return data_ + size_;
  }

  template< typename T >
  void Vector< T >::reserve(size_t newCapacity)
  {
    if (newCapacity <= capacity_)
    {
      return;
    }

    T* newData = new T[newCapacity];

    for (size_t i = 0; i < size_; ++i)
    {
      newData[i] = data_[i];
    }

    delete[] data_;

    data_ = newData;
    capacity_ = newCapacity;
  }

}

#endif

