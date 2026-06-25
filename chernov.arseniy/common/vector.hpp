namespace chernov {

  template< class T >
  struct Vector {
    T * data;
    size_t size;
    size_t capacity;
  };

}
