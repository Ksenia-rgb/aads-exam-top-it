#ifndef ARRAY_HPP
#define ARRAY_HPP

#include <cstddef>
#include <utility>

namespace vasyakin
{

  template< class T >
  struct array
  {
    T* data;
    size_t size;
    size_t cap;
  };

  template< class T >
  array< T > makeArray(size_t cap)
  {
    array< T > res{nullptr, 0, 0};
    if (cap > 0)
    {
      res.data = new T[cap];
      res.cap = cap;
    }

    return res;
  }

  template< class T >
  void clearArray(array< T >& dr) noexcept
  {
    delete[] dr.data;
    dr.data = nullptr;
    dr.cap = 0;
    dr.size = 0;
  }

  template< class T >
  void swapArray(array< T >& a, array< T >& b) noexcept
  {
    std::swap(a.data, b.data);
    std::swap(a.cap, b.cap);
    std::swap(a.size, b.size);
  }

  template< class T >
  array< T > copyArray(const array< T >& src, size_t cap)
  {
    array< T > res{nullptr, 0, 0};
    if (cap < src.size)
    {
      cap = src.size;
    }

    if (cap == 0)
    {
      return res;
    }

    res.data = new T[cap];
    res.cap = cap;

    try
    {
      for (; res.size < src.size; ++res.size)
      {
        res.data[res.size] = src.data[res.size];
      }
    }
    catch (...)
    {
      clearArray(res);
      throw;
    }

    return res;
  }

  template< class T >
  void pushBackArray(array< T >& dr, T val)
  {
    if (dr.size == dr.cap)
    {
      size_t newCap = dr.cap == 0 ? 1 : dr.cap * 2;
      array< T > tmp = copyArray(dr, newCap);

      try
      {
        tmp.data[tmp.size] = std::move(val);
        ++tmp.size;
      }
      catch (...)
      {
        clearArray(tmp);
        throw;
      }

      swapArray(tmp, dr);
      clearArray(tmp);
    }
    else
    {
      dr.data[dr.size] = std::move(val);
      ++dr.size;
    }
  }
}

#endif
