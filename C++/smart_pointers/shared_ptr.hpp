#pragma once

namespace awesome {

class ControlBlock {
  public:
    ControlBlock(): mRefCount(0) {}
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
    ControlBlock *mControlBlockPtr;
};

template<typename T>
shared_ptr<T>::shared_ptr(): mPtr(nullptr), mControlBlockPtr(nullptr) {}

template<typename T>
shared_ptr<T>::shared_ptr(T *ptr): mPtr(ptr) {
  mControlBlockPtr = new ControlBlock;
  mControlBlockPtr->incRefCount();
}

template<typename T>
shared_ptr<T>::~shared_ptr() {
  if (mControlBlockPtr->decRefCount() <= 0) {
    deletePtr();
    delete mControlBlockPtr;
  }
}

template<typename T>
shared_ptr<T>::shared_ptr(const shared_ptr<T> & other) {
  if (this != &other) {
    if (mControlBlockPtr->decRefCount() <= 0) {
      deletePtr();
      delete mControlBlockPtr;
    }
    mPtr = other.mPtr;
    mControlBlockPtr = other.mControlBlockPtr;
    mControlBlockPtr->incRefCount();
  }
}

template<typename T>
shared_ptr<T>::shared_ptr(shared_ptr<T> && other) {
  if (this != &other) {
    if (mControlBlockPtr->decRefCount() <= 0) {
      deletePtr();
      delete mControlBlockPtr;
    }
    mPtr = other.mPtr;
    mControlBlockPtr = other.mControlBlockPtr;
    mControlBlockPtr->incRefCount();
  }
}

template<typename T>
shared_ptr<T> & shared_ptr<T>::operator=(const shared_ptr<T> & other) {
  if (this != &other) {
    if (mControlBlockPtr->decRefCount() <= 0) {
      deletePtr();
      delete mControlBlockPtr;
    }
    mPtr = other.mPtr;
    mControlBlockPtr = other.mControlBlockPtr;
    mControlBlockPtr->incRefCount();
  }
  return *this;
}

template<typename T>
shared_ptr<T> & shared_ptr<T>::operator=(shared_ptr<T> && other) {
  if (this != &other) {
    if (mControlBlockPtr->decRefCount() <= 0) {
      deletePtr();
      delete mControlBlockPtr;
    }
    mPtr = other.mPtr;
    mControlBlockPtr = other.mControlBlockPtr;
    mControlBlockPtr->incRefCount();
  }
  return *this;
}

template<typename T>
void shared_ptr<T>::reset(T *ptr) {
  if (mControlBlockPtr->decRefCount() <= 0) {
    deletePtr();
    delete mControlBlockPtr;
  }
  mPtr = ptr;
  mControlBlockPtr = new ControlBlock;
  mControlBlockPtr->incRefCount();
}

template<typename T>
T * shared_ptr<T>::release() {
  T * ptr = mPtr;
  if (mControlBlockPtr->decRefCount() <= 0) {
    //deletePtr();
    delete mControlBlockPtr;
  }
  mPtr = nullptr;
  mControlBlockPtr = nullptr;
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
