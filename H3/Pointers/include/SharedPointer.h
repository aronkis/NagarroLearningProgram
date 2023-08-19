#ifndef _POINTERS_SHARED_POINTER_H_
#define _POINTERS_SHARED_POINTER_H_

#include <iostream>

template<typename T>
class SharedPointer
{
  template<typename U>
  friend class SharedPointer;
public:
  SharedPointer(T* dummy_pointer = nullptr)
    : dummy_pointer_(dummy_pointer), count_(new size_t(1)) {}

  SharedPointer(const SharedPointer& other)
  {
    dummy_pointer_ = other.dummy_pointer_;
    count_ = other.count_;
    ++*count_;
  }

  SharedPointer(size_t size)
  {
    size_ = size;
    dummy_pointer_ = new T[size];
  }

  SharedPointer (T array[], size_t size)
  {
    size_ = size;
    dummy_pointer_ = array;
  }

  ~SharedPointer()
  {
    --*count_;
    if (*count_ == 0)
    {
      delete count_;
      delete dummy_pointer_;
    }
  }

  SharedPointer& operator=(const SharedPointer& other)
  {
    SharedPointer(other).swap(*this);
    return *this;
  }

  template <typename U>
  SharedPointer(const SharedPointer<U>& other)
  {
    dummy_pointer_ = other.dummy_pointer_;
    count_ = other.count_;
    ++*count_;
  }

  SharedPointer& operator=(SharedPointer&& other) noexcept
  {
    SharedPointer(std::move(other)).swap(*this);
    return *this;
  }

  SharedPointer(SharedPointer&& other) noexcept
  {
    dummy_pointer_ = other.dummy_pointer_;
    count_ = other.count_;
    other.dummy_pointer_ = nullptr;
    other.count_ = new size_t(1);
  }

  // Modifiers
  void reset() noexcept
  {
    SharedPointer temp_;
    temp_.swap(*this);
  }

  void reset(T* pointer) noexcept
  {
    SharedPointer(pointer).swap(*this);
  }

  void swap(SharedPointer& other) noexcept
  {
    std::swap(dummy_pointer_, other.dummy_pointer_);
    std::swap(count_, other.count_);
  }

  //Observers
  T* get() const noexcept
  {
    return dummy_pointer_;
  }

  T& operator*() const noexcept
  {
    return *dummy_pointer_;
  }

  T* operator->() const noexcept
  {
    return dummy_pointer_;
  }

  T& operator[](const int index) const
  {
    if (index < size_)
    {
      return dummy_pointer_[index];
    }
    else
    {
      exit(0);
    }
  }

  long use_count() const noexcept
  {
    return dummy_pointer_ == nullptr ? 0 : *count_;
  }

  bool unique() const noexcept
  {
    return *this->use_count == 1;
  }

  explicit operator bool() const noexcept
  {
    return get() != nullptr;
  }

private:
  T* dummy_pointer_;
  size_t* count_;
  size_t size_;
};

template<typename T>
SharedPointer<T> make_shared()
{
  return SharedPointer<T> (new T);
}

template<typename T>
SharedPointer<T> make_shared(T* array, int size)
{
  return SharedPointer<T> (array, size);
}

#endif