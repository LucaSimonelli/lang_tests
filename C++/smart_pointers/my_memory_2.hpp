#pragma once

namespace owesome {

class Data {
  public:
    Data(): mRefCount(0) {}
    void incRefCount() {
      ++mRefCount;
    }
    int decRefCount() {
      if (mRefCount > 0) {
        --mRefCount;
      }
      return mRefCount;
    }
    int mRefCount;
};

template<typename T>
class shared_ptr {
  public:
    shared_ptr();
    shared_ptr(T *ptr);
    shared_ptr(const shared_ptr<T> & other);
    shared_ptr(shared_ptr<T> && other);
    shared_ptr<T> & operator=(const shared_ptr<T> & other);
    shared_ptr<T> & operator=(shared_ptr<T> && other);
    ~shared_ptr();

    void reset(T *ptr);
    T * release();
    T * operator->() const;
  private:
    void deletePtr();

    T *mPtr;
    Data *mData;
};

template<typename T>
shared_ptr<T>::shared_ptr(): mPtr(nullptr), mData(nullptr) {}

template<typename T>
shared_ptr<T>::shared_ptr(T *ptr): mPtr(ptr) {
  mData = new Data;
  mData->incRefCount();
}

template<typename T>
shared_ptr<T>::~shared_ptr() {
  if (mData->decRefCount() <= 0) {
    deletePtr();
    delete mData;
  }
}

template<typename T>
shared_ptr<T>::shared_ptr(const shared_ptr<T> & other) {
  if (this != &other) {
    if (mData->decRefCount() <= 0) {
      deletePtr();
      delete mData;
    }
    mPtr = other.mPtr;
    mData = other.mData;
    mData->incRefCount();
  }
}

template<typename T>
shared_ptr<T>::shared_ptr(shared_ptr<T> && other) {
  if (this != &other) {
    if (mData->decRefCount() <= 0) {
      deletePtr();
      delete mData;
    }
    mPtr = other.mPtr;
    mData = other.mData;
    mData->incRefCount();
  }
}

template<typename T>
shared_ptr<T> & shared_ptr<T>::operator=(const shared_ptr<T> & other) {
  if (this != &other) {
    if (mData->decRefCount() <= 0) {
      deletePtr();
      delete mData;
    }
    mPtr = other.mPtr;
    mData = other.mData;
    mData->incRefCount();
  }
  return *this;
}

template<typename T>
shared_ptr<T> & shared_ptr<T>::operator=(shared_ptr<T> && other) {
  if (this != &other) {
    if (mData->decRefCount() <= 0) {
      deletePtr();
      delete mData;
    }
    mPtr = other.mPtr;
    mData = other.mData;
    mData->incRefCount();
  }
  return *this;
}

template<typename T>
void shared_ptr<T>::reset(T *ptr) {
  if (mData->decRefCount() <= 0) {
    deletePtr();
    delete mData;
  }
  mPtr = ptr;
  mData = new Data;
  mData->incRefCount();
}

template<typename T>
T * shared_ptr<T>::release() {
  T * ptr = mPtr;
  if (mData->decRefCount() <= 0) {
    //deletePtr();
    delete mData;
  }
  mPtr = nullptr;
  mData = nullptr;
  return ptr;
}

template<typename T>
T * shared_ptr<T>::operator->() const {
  return mPtr;
}

template<typename T>
void shared_ptr<T>::deletePtr() {
  delete mPtr;
}


} // end owesome
