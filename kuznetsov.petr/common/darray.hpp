#ifndef AADS_EXAM_TOP_IT_DARRAY_HPP
#define AADS_EXAM_TOP_IT_DARRAY_HPP
#include <iostream>
#include <utility>

namespace kuznetsov {

  template< class T >
  struct darray {
    T* data;
    size_t size, cap;
  };

  template< class T >
  darray< T > makeDarray(size_t cap)
  {
    darray< T > res {nullptr, 0, 0};
    res.data = new T[cap];
    res.cap = cap;
    return res;
  }

  template< class T >
  void clearDarray(darray< T >& dr)
  {
    delete[] dr.data;
    dr.data = nullptr;
    dr.cap = 0;
    dr.size = 0;
  }

  template< class T >
  darray< T > copyDarray(darray< T > dr, size_t cap = 0)
  {
    darray< T > nr {nullptr, 0, 0};
    if (cap < dr.size) {
      cap = dr.cap;
    }
    nr.data = new T[cap];
    try {
      for (size_t i = 0; i < dr.size; ++i) {
        nr.data[i] = dr.data[i];
        ++nr.size;
      }
      nr.cap = cap;
      return nr;
    } catch (...) {
      clearDarray(nr);
      throw;
    }
  }

  template< class T >
  void swapDarray(darray< T >& a, darray< T >& b)
  {
    std::swap(a.data, b.data);
    std::swap(a.cap, b.cap);
    std::swap(a.size, b.size);
  }

  template< class T >
  void pushBackDarray(darray< T >& dr, T& val)
  {
    darray< T > tmp {nullptr, 0, 0};
    size_t cap = dr.cap;
    if (dr.size == dr.cap) {
      cap = dr.cap * 2 + 1;
    }
    tmp = copyDarray(dr, cap);
    try {
      tmp.data[dr.size] = std::forward< T >(val);
      ++tmp.size;
      swapDarray(tmp, dr);
    } catch (...) {
      clearDarray(tmp);
      throw;
    }
    clearDarray(tmp);
  }

  template< class  T >
  void removeDarray(darray< T >& dr, size_t pos)
  {
    if (pos >= dr.size) {
      throw std::logic_error("Pos");
    }
    darray< T > cp = copyDarray(dr);
    try {
      for (size_t i = pos; i + 1 < dr.size; ++i) {
        cp.data[i] = std::move(cp.data[i + 1]);
      }
      --cp.size;
      swapDarray(dr, cp);
    } catch (...) {
      clearDarray(cp);
      throw;
    }
    clearDarray(cp);
  }

  template< class T, class E >
  bool containsDarray(darray< T >& dr, const T& val, E eq)
  {
    for (size_t i = 0; i < dr.size; ++i) {
      if (eq(dr.data[i], val)) {
        return true;
      }
    }
    return false;
  }

}

#endif
