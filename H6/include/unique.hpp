#ifndef _SMART_POINTERS_UNIQUE_POINTERS_H
#define _SMART_POINTERS_UNIQUE_POINTERS_H

#include <iostream>
#include <memory>
#include <utility>
#include <typeinfo>


template <typename T>
class uniquePtr {
    public:
        typedef void (*deleter)(T*);

        explicit uniquePtr(T* ptr=nullptr, void (*deleter)(T*) =[](T* p) {delete p;}): ptr_(ptr), deleter_(deleter) { //the constructor that takes a pointer to an object of type T and points to that object
            //std::cout << "Unique pointer created\n";
        }
        ~uniquePtr() { //the destructor that releases the allocated memory for the object that points to ptr_ and properly deallocates the memory
            deleter_(ptr_);
        }

        //copy constructor and copy assignment operator are explicitly deleted as so they cannot be called
        //because using one of those could result to bad behaviour when releasing the memory
        uniquePtr(const uniquePtr&) = delete;

        uniquePtr& operator=(const uniquePtr&) = delete;

        //the move constructor that takes an rvalue to another unique pointer object and moves the ownership using the release function
        uniquePtr(uniquePtr&& other) noexcept : ptr_(other.release()), deleter_(other.getDeleter()) 
        {}
        
        //the move assignment operator, same as above
        uniquePtr& operator=(uniquePtr&& other) noexcept {
            reset(other.release());
            deleter_=other.deleter_;
            return *this;
        }

        //overloading operators
        T* get() const noexcept 
        { return ptr_; }
        T& operator*() const noexcept 
        { return *ptr_; }
        T* operator->() const noexcept
        { return ptr_; }

        //realeses ownership of the managed pointer and returns the raw pointer
        T* release() noexcept {
            T* temp = ptr_;
            ptr_ = nullptr;
            return temp;
        }

        //replace the managed pointer with a new pointer
        void reset(T* ptr = nullptr) noexcept {
            if (ptr_ != ptr) {
                deleter_(ptr_);
                ptr_ = ptr;
            }
        }

        void swap(uniquePtr& other) noexcept
        {
            std::swap(ptr_, other.ptr_);
            std::swap(deleter_, other.deleter_);
        }

        deleter getDeleter() noexcept {
            return deleter_;
        }

        explicit operator bool() const noexcept
        {
            return *this->get != nullptr;
        }
        
        T& operator[](size_t index) const
        {
            return *(ptr_ + index);
        }

        template<typename... Args>
        uniquePtr<T> make_unique(Args&&... args)
        {
            return uniquePtr<T>(new T(std::forward<Args>(args)...));
        }

        private:
            T* ptr_;
            void (*deleter_)(T*);
};

#endif