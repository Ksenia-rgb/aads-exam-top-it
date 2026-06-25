#ifndef ARRAY_HPP
#define ARRAY_HPP

#include <cstddef>
#include <utility>

namespace burukov {

  template< class T >
  struct darray
  {
    T* data;
    size_t size;
    size_t cap;
  };

  template< class T >
  darray< T > makeArray(size_t cap)
  {
    darray< T > res{nullptr, 0, 0};
    if (cap > 0)
    {
      res.data = new T[cap];
      res.cap = cap;
    }
    return res;
  }

  template< class T >
  void clearArray(darray< T >& dr)
  {
    delete[] dr.data;
    dr.data = nullptr;
    dr.cap = 0;
    dr.size = 0;
  }

  template< class T >
  void swapArray(darray< T >& a, darray< T >& b)
  {
    std::swap(a.data, b.data);
    std::swap(a.cap, b.cap);
    std::swap(a.size, b.size);
  }

  template< class T >
  darray< T > copyArray(const darray< T >& src, size_t cap)
  {
    darray< T > res{nullptr, 0, 0};
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
  void pushBackArray(darray< T >& dr, T val)
  {
    if (dr.size < dr.cap)
    {
      dr.data[dr.size] = std::move(val);
      ++dr.size;
      return;
    }
    size_t newCap = (dr.cap == 0) ? 1 : (dr.cap * 2);
    darray< T > tmp = copyArray(dr, newCap);
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

}

#endif
