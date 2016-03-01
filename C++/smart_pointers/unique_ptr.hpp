#pragma once

namespace awesome {

template<typename T>
class unique_ptr {
  public:
    unique_ptr();
    unique_ptr(T *ptr);
    // A unique_ptr cannot be copied
    unique_ptr(const unique_ptr<T> & other) = delete;
    unique_ptr(unique_ptr<T> && other);
    // A unique_ptr cannot be copied
    unique_ptr<T> & operator=(const unique_ptr<T> & other) = delete;
    unique_ptr<T> & operator=(unique_ptr<T> && other);
    ~unique_ptr();

    void reset(T *ptr);
    T * release();
    T * operator->() const;
  private:
    void deletePtr();

    T *mPtr;
};

template<typename T>
unique_ptr<T>::unique_ptr(): mPtr(nullptr) {}

template<typename T>
unique_ptr<T>::unique_ptr(T *ptr): mPtr(ptr) {}

template<typename T>
unique_ptr<T>::~unique_ptr() {
  deletePtr();
}

/*
template<typename T>
unique_ptr<T>::unique_ptr(const unique_ptr<T> & other) {
  if (this != &other) {
    deletePtr();
    mPtr = other.mPtr;
    // TODO
    // std::vector requires a copy constructor for the provided object
    // but a unique_ptr doesn't want to implement a copy constructor
    //other.mPtr = nullptr;
  }
}
*/

template<typename T>
unique_ptr<T>::unique_ptr(unique_ptr<T> && other) {
  if (this != &other) {
    deletePtr();
    mPtr = other.mPtr;
    other.mPtr = nullptr;
  }
}

template<typename T>
unique_ptr<T> & unique_ptr<T>::operator=(unique_ptr<T> && other) {
  if (this != &other) {
    deletePtr();
    mPtr = other.mPtr;
    other.mPtr = nullptr;
  }
  return *this;
}

template<typename T>
void unique_ptr<T>::reset(T *ptr) {
  deletePtr();
  mPtr = ptr;
}

template<typename T>
T * unique_ptr<T>::release() {
  T * ptr = mPtr;
  mPtr = nullptr;
  return ptr;
}

template<typename T>
T * unique_ptr<T>::operator->() const {
  return mPtr;
}

template<typename T>
void unique_ptr<T>::deletePtr() {
  delete mPtr;
}


} // end owesome
