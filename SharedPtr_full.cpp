#include <iostream>
#include <stdexcept>

template <typename T>
class SharedPtr {
private:
  T* ptr_ = nullptr;
  int* amount = nullptr;

public:
  SharedPtr() = default;
  SharedPtr(T* new_ptr) : ptr_(new_ptr), amount(new int(1)) {}

  SharedPtr(const SharedPtr& other) : ptr_(other.ptr_), amount(other.amount) {
    if (amount != nullptr) {
      ++*amount;
    }
  }
  SharedPtr& operator=(const SharedPtr& other) {
    Reset();
    ptr_ = other.ptr_;
    amount = other.amount;

    if (ptr_ != nullptr) {
      ++*amount;
    }
  }

  SharedPtr(const SharedPtr&& other) {
    ptr_ = other.ptr_;
    amount = other.amount;

    other.ptr_ = nullptr;
    other.amount = nullptr;
  }
  SharedPtr& operator=(const SharedPtr&& other) {
    Reset();

    ptr_ = other.ptr_;
    amount = other.amount;

    other.ptr_ = nullptr;
    other.amount = nullptr;
  }

  void Reset(T* other = nullptr) {
    if (amount != nullptr) {
      --*amount;
      if (*amount == 0) {
        delete ptr_;
        delete amount;
      }
    }
    ptr_ = other;
    if (ptr_ != nullptr) {
      amount = new int(1);
    }
  }

  ~SharedPtr() {
    if (amount == nullptr) {
      return;
    }
    --*amount;
    if (*amount == 0) {
      delete ptr_;
      delete amount;
    }
  }
};
