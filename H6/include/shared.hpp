#ifndef _SMART_POINTERS_SHARED_POINTERS_H
#define _SMART_POINTERS_SHARED_POINTERS_H

#include <iostream>
#include <memory>

template<typename T>
class SharedPtr {
public:
    SharedPtr(T* ptr = nullptr, void (*deleter)(T*) = [](T* p) { delete p; }) : ptr_(ptr), counter_(new size_t(1)), deleter_(deleter) {}
    ~SharedPtr() 
    {
        if (--(*counter_) == 0) {
            deleter_(ptr_);
            delete counter_;
        }
    }

    SharedPtr(const SharedPtr& other) : ptr_(other.ptr_), counter_(other.counter_), deleter_(other.deleter_) 
    {
        ++(*counter_);
    }

    SharedPtr& operator=(const SharedPtr& other) 
    {
        if (this != &other) {
            if (--(*counter_) == 0) {
                deleter_(ptr_);
                delete counter_;
            }
            ptr_ = other.ptr_;
            counter_ = other.counter_;
            deleter_ = other.deleter_;
            ++(*counter_);
        }
        return *this;
    }

    T* get() const noexcept 
    { return ptr_; }

    T& operator*() const noexcept 
    { return *ptr_; }

    T* operator->() const noexcept 
    { return ptr_; }
    
    size_t use_count() const noexcept 
    { return *counter_; }
    
    void reset(T* ptr = nullptr) noexcept 
    {
        if (ptr_ != ptr) {
            if (--(*counter_) == 0) {
                deleter_(ptr_);
                delete counter_;
            }
            ptr_ = ptr;
            counter_ = new size_t(1);
        }
    }
    
    void swap(SharedPtr& other) noexcept 
    {
        std::swap(ptr_, other.ptr_);
        std::swap(counter_, other.counter_);
        std::swap(deleter_, other.deleter_);
    }

    void (*get_deleter())(T*) noexcept 
    { return deleter_; }

    explicit operator bool() const noexcept
    {
        return ptr_ != nullptr;
    }

    bool unique() const noexcept
    {
        return this->use_count() == 1;
    }
    
    bool owner_before(const SharedPtr& other) const noexcept
    {
        return counter_ < other.counter_;
    }
    
    T& operator[](size_t index) const
    {
        return *(ptr_ + index);
    }
    template<typename... Args>
    SharedPtr<T> make_shared(Args&&... args)
    {
        auto* obj = new T(std::forward<Args>(args)...);
        return SharedPtr<T>(obj);
    }

private:
    T* ptr_;
    size_t* counter_;
    void (*deleter_)(T*);
};

#endif