#include <algorithm>
#include <memory>
namespace my {

template <typename T, typename Deleter = std::default_delete<T>> 
class unique_ptr {
    T* ptr_ = nullptr;
    Deleter deleter;
public:
    constexpr unique_ptr() noexcept = default;

    constexpr unique_ptr(T* ptr) noexcept: ptr_(ptr) {}

    unique_ptr(const unique_ptr&) = delete;

    unique_ptr& operator=(const unique_ptr&) = delete;

    unique_ptr(unique_ptr&& another) noexcept {reset(another.release());}

    unique_ptr& operator=(unique_ptr&& another) noexcept {
        if (ptr_ != another.get()) {
            reset(another.release());
        }
        return *this;
    }
    ~unique_ptr() {
        delete ptr_;
    }

    T* get() const noexcept {
        return ptr_;
    }
    void reset(T* ptr = nullptr) noexcept {
        if (ptr_ != ptr) {
            T* old_ptr = std::exchange(ptr_, ptr);
            delete old_ptr;
        }
    }
    T* release() noexcept {
        return std::exchange(ptr_, nullptr);
    }
    T& operator*() const noexcept {return *get();}
    T* operator->() const noexcept {return get();}
    operator bool() const {
        return ptr_ != nullptr;
    }
};

template <typename T, typename... Args> 
unique_ptr<T> make_unique (Args&&... args) {
    unique_ptr<T>(new T(std::forward<Args>(args)...));
}
}