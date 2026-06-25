#ifndef ARRAY_HPP
#define ARRAY_HPP

#include <cstddef>
#include <stdexcept>

namespace petrov
{
  namespace detail
  {
    template< class T >
    struct array_t
    {
      T * data;
      std::size_t size;
      std::size_t capacity;
    };

    template< class T >
    void initArray(array_t< T >& array)
    {
      const std::size_t initial_capacity = 16;
      array.data = new T[initial_capacity];
      array.size = 0;
      array.capacity = initial_capacity;
    }

    template< class T >
    void destroyArray(array_t< T >& array) noexcept
    {
      delete[] array.data;
      array.data = nullptr;
      array.size = 0;
      array.capacity = 0;
    }

    template< class T >
    void pushBackArray(array_t< T >& array, const T& value)
    {
      if (array.size == array.capacity)
      {
        const std::size_t growth_factor = 2;
        const std::size_t new_capacity =
            array.capacity * growth_factor;
        T * new_data = new T[new_capacity];
        try
        {
          for (std::size_t i = 0; i < array.size; ++i)
          {
            new_data[i] = array.data[i];
          }
        }
        catch (...)
        {
          delete[] new_data;
          throw;
        }
        delete[] array.data;
        array.data = new_data;
        array.capacity = new_capacity;
      }
      array.data[array.size] = value;
      ++array.size;
    }
  }
}

#endif
