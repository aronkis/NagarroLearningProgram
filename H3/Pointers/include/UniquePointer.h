#ifndef _POINTERS_UNIQUE_POINTER_H_
#define _POINTERS_UNIQUE_POINTER_H_

#include <iostream>

template <typename T>
struct DefaultDeleter
{
  DefaultDeleter() {}
  DefaultDeleter(DefaultDeleter &) {}
  DefaultDeleter(const DefaultDeleter &) {}
  DefaultDeleter(DefaultDeleter &&) {}

  void operator()(T *ptr) const { delete ptr; }
};

template <typename T, typename Deleter = DefaultDeleter<T>>
class UniquePointer
{
public:
  // Constructors
  UniquePointer() : dummy_pointer_(nullptr) {}
  UniquePointer(T* pointer) : dummy_pointer_(pointer) {}
  UniquePointer(T* pointer, const Deleter& deleter) 
    : dummy_pointer_(pointer), deleter_(deleter) {}
  UniquePointer (size_t size)
  {
    size_ = size;
    dummy_pointer_ = new T[size];
  }
  UniquePointer (T array[], size_t size)
  {
    size_ = size;
    dummy_pointer_ = array;
  }
  
  ~UniquePointer()
  {
    if (size_ == 0)
    {
      delete dummy_pointer_;
    }
    else
    {
      dummy_pointer_ = nullptr;
      delete[] dummy_pointer_;
    }
  }

  // no copy
  UniquePointer(const UniquePointer& other) = delete;
  UniquePointer& operator=(const UniquePointer& other) = delete; 

  //Move Operator
  UniquePointer (UniquePointer&& other) noexcept
    : dummy_pointer_(other.release()), deleter_(other.deleter_) {}
  
  UniquePointer& operator=(UniquePointer&& other) noexcept
  {
    dummy_pointer_ = reset(other.release());
    deleter_ = std::forward<Deleter>(other.get_deleter());
  }

  template<typename U, typename E>
  UniquePointer& operator=(UniquePointer<U,E>&& other)
  {
    dummy_pointer_ = other.release();
    deleter_ = std::forward<Deleter>(other.get_deleter());
  }

  // Modifiers
  void reset(T* pointer) noexcept
  {
    if (dummy_pointer_ != pointer)
    {
      deleter_(dummy_pointer_);
      dummy_pointer_ = pointer;
    }
  }

  T* release() noexcept
  {
    T* temp = dummy_pointer_;
    dummy_pointer_ = nullptr;
    return temp;
  }

  void swap(UniquePointer& other) noexcept
  {
    std::swap(dummy_pointer_, other.dummy_pointer_);
    if (size_)
    {
      std::swap(size_, other.size_);
    }
  }

  // Observers
  T* get()
  {
    return dummy_pointer_;
  }

  Deleter get_deleter() const noexcept
  {
    return deleter_;
  }

  explicit operator bool()
  {
    return dummy_pointer_ != nullptr;
  }

  // Single-object versions
  T& operator*() const noexcept
  {
    return *dummy_pointer_;
  }

  T* operator->() const noexcept
  {
    return dummy_pointer_;
  }

  // Array version 
  T& operator[](const int index)
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

  std::ostream& operator<<(std::ostream& os)
  {
    os << dummy_pointer_;
    return os;
  }

private:
  T* dummy_pointer_;
  Deleter deleter_ = Deleter();
  int size_ = 0; // for arrays
};

template<typename T>
UniquePointer<T> make_unique()
{
  return UniquePointer<T> (new T);
}

template<typename T>
UniquePointer<T> make_unique(T* array, int size)
{
  return UniquePointer<T> (array, size);
}

#endif