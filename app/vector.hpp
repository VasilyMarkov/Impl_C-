#pragma once
#include <iostream>
#include <exception>
#include <type_traits>
#include <concepts>

namespace my {

template <typename T, typename U>
requires(std::same_as<T, std::decay_t<U>>)
void construct(T* ptr, U&& rhs) {new (ptr) T(std::forward<U>(rhs));}

template<typename T> void destroy(T* ptr) {ptr->~T();}

template<typename It> void destroy(It begin, It end) {
    while(begin != end) {
        destroy(&*begin++);
    }
}
template <typename T>
class Vector {
private:
    T* data_ = nullptr;
    size_t size_ = 0;
    size_t cap_ = 0;
public:
    Vector() = default;

    explicit Vector(size_t n) {
        reserve(2*n);
        while(size_ < n) {
            construct(data_+size_++, T());
        }
    }
    template<typename It>
    // Vector(It begin, It end):size_(std::distance(begin, end)) {
    //     reserve(2*size_);
    //     size_t cnt = 0;
    //     while(begin != end) {
    //         construct(data_+cnt++, *begin++);
    //     }
    // }
    Vector(const Vector& another) {
        // reserve(another.size());
        // try {
        //     while(size_ < another.size_) {
        //         construct(data_+size_, *(another.data_+size_));
        //         ++size_;
        //     }
        // }
        // catch(const std::exception& e) {
        //     destroy(data_, data_+size_);
        //     size_ = 0;
        //     throw std::bad_alloc("bad alloc");
        // }

    }
    Vector(Vector&& another) noexcept {
        
    }
    Vector& operator=(const Vector& another) {
        
    }
    Vector& operator=(Vector&& another) noexcept {

    }
    ~Vector() {        
        destroy(data_, data_+size_);
        ::operator delete(data_);
    }
    void reserve(size_t n) {
        if (n <= cap_) return;

        T* new_data = n == 0 ? nullptr : static_cast<T*>(::operator new(sizeof(T*)*n));
        size_t used = 0;
        
        try {
            std::uninitialized_copy(data_, data_+size_, new_data_);
            // while(used < size_) { //non-exception safety
            //     construct(new_data+used, std::move(*(data_+used)));
            //     ++used;
            // }
        }
        catch(...) {
            // destroy(data_, data_+used);
            ::operator delete (data_);
            throw;
        }
        destroy(data_, data_+size_);
        ::operator delete (data_);
        data_ = new_data;
        cap_ = n;
    }
    void resize(size_t n, const T& value = T()) {
        // if(n > cap_) reserve(n);
        // if(n == size_) return;
        // if(n > size_) {
        //     for(size_t i = size_; i < n; ++i) {
        //         data_[i] = value;
        //     }
        // }
        // else {
        //     size_ = n;
        // }
    }

    void push_back(const T& value) {

        try {
            if (size_ == cap_) {
                reserve(2*size_);
            }
            construct(data_+size_, value);
            ++size_;
        }
        catch(const std::exception& e) {

        }

    }
    void push_back(T&& value) {
        if (size_ == cap_) {
            reserve(2*size_);
        }
        data_[size_++] = std::move(value);
    }
    void pop_back() {
        --size_;
    }
    size_t size() const noexcept {
        return size_;
    }
    size_t capacity() const noexcept {
        return cap_;
    }
    T& operator[](size_t index) noexcept {
        return data_[index];
    }
    T& at(size_t index) {
        if(index > size_) {
            throw std::out_of_range("out of range");
        }
        return data_[index];
    }
};
}