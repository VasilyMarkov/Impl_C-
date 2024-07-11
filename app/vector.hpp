#pragma once
#include <iostream>
#include <exception>
#include <type_traits>
#include <concepts>

namespace my {

template <typename T, typename U>
requires(std::same_as<T, std::decay_t<U>>)
void construct(T* ptr, U&& rhs) noexcept(noexcept(U{})) {new (ptr) T(std::forward<U>(rhs));}

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
    Vector(It begin, It end) {
        auto size = std::distance(begin, end);
        reserve(size);
        std::uninitialized_copy(begin, end, data_);
        size_ = size;
    }

    Vector(const Vector& another) {
        reserve(another.size_);
        std::uninitialized_copy(another.data_, another.data_+another.size_, data_);
        size_ = another.size_;
    }

    Vector(Vector&& another) noexcept: data_(another.data_), size_(another.size_), cap_(another.cap_) {
        another.data_ = nullptr;
        another.size_ = 0;
        another.cap_ = 0;
    }
    
    Vector& operator=(const Vector& another) {
        destroy(data_, data_+size_);
        ::operator delete(data_);
        reserve(another.size_);
        std::uninitialized_copy(another.data_, another.data_+another.size_, data_);
        size_ = another.size_;
        return *this;
    }

    Vector& operator=(Vector&& another) noexcept {
        std::cout << another.cap_ << std::endl;
        std::cout << cap_ << std::endl;
        std::swap(data_, another.data_); 
        std::swap(size_, another.size_);
        std::swap(cap_,  another.cap_);
        return *this;
    }
    ~Vector() {        
        destroy(data_, data_+size_);
        ::operator delete(data_);
    }
    void reserve(size_t n) {
        if (n <= cap_) return;

        T* new_data = n == 0 ? nullptr : static_cast<T*>(::operator new(sizeof(T*)*n));
        try {
            std::uninitialized_copy(data_, data_+size_, new_data);
        }
        catch(const std::exception& e) {
            ::operator delete (data_);
            throw;
        }
        destroy(data_, data_+size_);
        ::operator delete (data_);
        data_ = new_data;
        cap_ = n;
    }
    void resize(size_t n, const T& value = T()) {

    }

    void push_back(const T& value) {
        if(size_ == 0) {reserve(2);}
        else if (size_ == cap_) {
            reserve(2*size_);
        }
        construct(data_+size_, value);
        ++size_;
    }

    void push_back(T&& value) {
        if(size_ == 0) {reserve(2);}
        else if (size_ == cap_) {
            reserve(2*size_);
        }
        construct(data_+size_, std::move(value));
        ++size_;
    }

    template <typename ... Args>
    void emplace_back(Args&&... args) {
        if(size_ == 0) {reserve(2);}
        else if (size_ == cap_) {
            reserve(2*size_);
        }
        construct(data_+size_, std::forward<Args>(args)...);
        ++size_;
    }

    void pop_back() noexcept {
        --size_;
        destroy(data_+size_, data_+size_+1);
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

    const T& operator[](size_t index) const noexcept {
        return data_[index];
    }

    T& at(size_t index) {
        if(index > size_) {
            throw std::out_of_range("out of range");
        }
        return data_[index];
    }

    const T& at(size_t index) const {
        if(index > size_) {
            throw std::out_of_range("out of range");
        }
        return data_[index];
    }

    class Iterator {
        T* ptr_;
    public:
        Iterator(T* ptr): ptr_(ptr) {}

        T& operator*() {
            return *ptr_;
        }

        Iterator& operator++() {
            ptr_++;
            return *this;
        }

        bool operator!=(const Iterator& other) const {
            return ptr_ != other.ptr;
        }
    };

    Iterator begin() {
        return {data_};
    }

    Iterator end() {
        return {data_+size_};
    }
};
}