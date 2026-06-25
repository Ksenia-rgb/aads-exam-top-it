namespace chernov {

  template< class T >
  struct Vector {
    T * data;
    size_t size;
    size_t capacity;
  };

  template< class T >
  void init(Vector< T > & v);

  template< class T >
  void destroy(Vector< T > & v);

}

template< typename T >
void chernov::init(Vector< T > & v)
{
  v.data = nullptr;
  v.size = 0;
  v.capacity = 0;
}

template< typename T >
void chernov::destroy(Vector< T > & v)
{
  if (v.data) {
    delete[] v.data;
  }
  init(v);
}
