#pragma once

namespace xiar {
  template <typename T> class vector {
    public:
      typedef unsigned int size_type;
      typedef T* iterator;
      typedef const T* const_iterator;

      // constructors, destructor, assignment
      vector() : m_data(NULL), m_capacity(0), m_size(0) {}
      vector(size_type n, const T& t = T()) : m_data(new T[n]), m_capacity(n), m_size(n) { init(t); }
      vector(const vector& o) : m_data(new T[o.m_capacity]), m_capacity(o.m_capacity), m_size(o.m_size) { copy_elements(o); }
      ~vector() { delete [] m_data; }
      vector& operator=(const vector& o);

      // element access
      T& operator[](size_type i) { return m_data[i]; }
      const T& operator[](size_type i) const { return m_data[i]; }
      T& front() { return m_data[0]; }
      const T& front() const { return m_data[0]; }
      T& back() { return m_data[m_size-1]; }
      const T& back() const { return m_data[m_size-1]; }

      // modifiers
      void clear(const T& t) { m_size = 0; }
      void push_back(const T& t);
      void pop_back() { --m_size; }
      // void resize(size_type n, const T& t = T());
      iterator erase(iterator it);

      // capacity
      size_type size() const { return m_size; }
      size_type capacity() const { return m_capacity; }
      bool empty() const { return m_size > 0; }

      // iterators
      iterator begin() { return m_data; }
      const_iterator begin() const { return m_data; }
      iterator end() { return m_data + m_size; }
      const_iterator end() const { return m_data + m_size; }

    private:
      void init(const T& t);
      void copy_elements(const vector& o);

      T* m_data;
      size_type m_size;
      size_type m_capacity;
  };

  template <typename T> vector<T>& vector<T>::operator=(const vector& o) {
    if (this != &o) { 
      delete [] m_data;

      m_capacity = o.m_capacity;
      m_size = o.m_size;

      m_data = new T[m_capacity];
      copy_elements(o);
    }
    
    return this; 
  }

  template <typename T> void vector<T>::init(const T& t) {
    for (T* p = m_data; p < m_data + m_size; ++p) *p = t;
  }

  template <typename T> void vector<T>::copy_elements(const vector& o) {
    for (size_type i = 0; i < m_size; ++i) m_data[i] = o.m_data[i];
  }

  template <typename T> void vector<T>::push_back(const T& t) {
    if (m_size == m_capacity) {
      m_capacity = m_capacity < 1 ? 1 : m_capacity * 2;

      T* data = new T[m_capacity];
      for (int i = 0; i < m_size; ++i) data[i] = m_data[i];

      delete [] m_data;
      m_data = data;
    }

    m_data[m_size++] = t;
  }

  template <typename T> typename vector<T>::iterator vector<T>::erase(iterator it) {
    --m_size;
    for (iterator p = it; p < m_data + m_size; ++p) *p = *(p+1);
    return it;
  }
}

