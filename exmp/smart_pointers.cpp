#include <iostream>

class Test {
    inline static size_t cnt = 0;
public:
    int x = 5;
    Test() {cnt++; std::cout << "Test() " << cnt << std::endl;}
    Test(const Test& t) {cnt++; std::cout << "Test(const Test&) " << cnt << std::endl;}
    Test(Test&& t) {cnt++; std::cout << "Test(Test&&) " << cnt << std::endl;}
    Test& operator=(const Test& t) {std::cout << "operator=(const Test&)" << std::endl; return *this;}
    Test operator=(Test&& t) {std::cout << "operator=(Test&&)" << std::endl; return *this;}
    ~Test() {std::cout << "~Test() " << cnt << std::endl; --cnt;}
};

namespace smart {
template <typename T>
class unique_ptr {
    T* data_;
    public:
    unique_ptr() = default;
    unique_ptr(T* data):data_(data) {std::cout << "unique_ptr(T*)" << std::endl;}
    unique_ptr(unique_ptr&& ptr):data_(ptr.data_) {
        ptr = nullptr;
        std::cout << "unique_ptr(unique_ptr&&)" << std::endl;
    }
    ~unique_ptr() {std::cout << "~unique_ptr()" << std::endl; delete data_;}

    unique_ptr& operator=(const unique_ptr& ptr) = delete;
    unique_ptr& operator=(unique_ptr&& ptr) noexcept {
        if(&ptr == &this) return *this;
        std::swap(data_, ptr.data_);
        std::cout << "operator=(unique_ptr&&)" << std::endl;
        return *this;
    }
    T& operator*() const {
        return *data_;
    }
    T* operator->() const {
        return data_;
    }
};

template <typename T>
class shared_ptr {
    T* data_;
    size_t* cnt_;
public:
    shared_ptr() = default;
    shared_ptr(T* data):data_(data), cnt_(new size_t(1)) {std::cout << "shared_ptr(T*)" << std::endl;}

    shared_ptr(const shared_ptr& ptr):data_(ptr.data_), cnt_(ptr.cnt_) {
        ++*cnt_;
        std::cout << "shared_ptr(const shared_ptr&)" << std::endl;
    }

    shared_ptr(shared_ptr&& ptr):data_(ptr.data_), cnt_(ptr.cnt_) {
        ptr = nullptr;
        ptr.cnt_ = nullptr;
        std::cout << "shared_ptr(shared_ptr&&)" << std::endl;
    }

    ~shared_ptr() {
        std::cout << "~shared_ptr()" << std::endl;  
        if(*cnt_ > 1 ) {
            --*cnt_;
            return;
        }
        delete data_;
        delete cnt_;
        std::cout << "delete data" << std::endl;
    }

    shared_ptr& operator=(const shared_ptr& ptr) {
        if(&ptr == &this) return *this;
        data_ = ptr.data_;
        cnt_ = ptr.cnt_;
        ++*cnt_;
        std::cout << "operator=(const shared_ptr&)" << std::endl;
        return *this;
    }
    shared_ptr& operator=(shared_ptr&& ptr) noexcept {
        if(&ptr == this) return *this;
        std::swap(data_, ptr.data_);
        std::swap(cnt_, ptr.cnt_);
        std::cout << "operator=(shared_ptr&&)" << std::endl;
        return *this;
    }
    T& operator*() const {
        return *data_;
    }
    T* operator->() const {
        return data_;
    }
    

};
}

using namespace smart;

template<typename T, typename... Ts>
unique_ptr<T> make_unique(Ts&&... params) {
    return unique_ptr<T>(new T(std::forward<Ts>(params)...));
}

int main () {
    smart::shared_ptr<Test> s_ptr = new Test();
    auto a_ptr = std::move(s_ptr);
    // std::cout << s_ptr->x << ' ' << a_ptr->x << std::endl;
    return 0;
}