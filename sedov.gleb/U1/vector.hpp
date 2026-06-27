#ifndef VECTOR_HPP
#define VECTOR_HPP
#include <cstddef>
#include <utility>

namespace sedov
{
  template< class T >
  struct Vector
  {
    T * data;
    size_t size;
    size_t cap;
  };

  template< class T >
  Vector< T > makeVec(size_t cap)
  {
    Vector< T > res{nullptr, 0, 0};
    if (cap > 0)
    {
      res.data = new T[cap];
      res.cap = cap;
    }
    return res;
  }

  template< class T >
  void clearVec(Vector< T > & dr) noexcept
  {
    delete[] dr.data;
    dr.data = nullptr;
    dr.cap = 0;
    dr.size = 0;
  }

  template< class T >
  void swapVec(Vector< T > & a, Vector< T > & b) noexcept
  {
    std::swap(a.data, b.data);
    std::swap(a.cap, b.cap);
    std::swap(a.size, b.size);
  }

  template< class T >
  Vector< T > copyVec(const Vector< T > & src, size_t cap)
  {
    Vector< T > res{nullptr, 0, 0};
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
      clearVec(res);
      throw;
    }
    return res;
  }

  template< class T >
  void pushBackVec(Vector< T > & dr, T val)
  {
    if (dr.size == dr.cap)
    {
      size_t newCap = dr.cap == 0 ? 1 : dr.cap * 2;
      Vector< T > tmp = copyVec(dr, newCap);
      try
      {
        tmp.data[tmp.size] = std::move(val);
        ++tmp.size;
      }
      catch (...)
      {
        clearVec(tmp);
        throw;
      }
      swapVec(tmp, dr);
      clearVec(tmp);
    }
    else
    {
      dr.data[dr.size] = std::move(val);
      ++dr.size;
    }
  }
}

#endif
