#include <iostream>
#include <stdexcept>

#ifndef UNIQUE_PTR_H
#define UNIQUE_PTR_H

template <typename T>
class UniquePtr {
 private:
  T* ptr_;

 public:
  UniquePtr() : ptr_(nullptr) {
  }
  explicit UniquePtr(T* other_ptr) : ptr_(other_ptr) {
  }

  UniquePtr(const UniquePtr<T>& other_uptr) = delete;
  UniquePtr& operator=(const UniquePtr<T>& other_uptr) = delete;

  UniquePtr(UniquePtr&& other_uptr) noexcept {
    ptr_ = other_uptr.ptr_;
    other_uptr.ptr_ = nullptr;
  }
  UniquePtr& operator=(UniquePtr&& other_uptr) noexcept {
    Reset(other_uptr.ptr_);
    other_uptr.ptr_ = nullptr;
    return *this;
  }

  T* Release() {
    T* copy = ptr_;
    ptr_ = nullptr;
    return copy;
  }
  void Reset(T* new_ptr = nullptr) {
    delete ptr_;
    ptr_ = new_ptr;
  }
  void Swap(UniquePtr<T>& other) {
    T* temp = std::move(ptr_);
    ptr_ = std::move(other.ptr_);
    other.ptr_ = std::move(temp);
  }

  T& operator*() const {
    return *ptr_;
  }
  T* operator->() const {
    return ptr_;
  }
  T* Get() const {
    return ptr_;
  }

  explicit operator bool() const {
    return ptr_ != nullptr;
  }
};

#endif
