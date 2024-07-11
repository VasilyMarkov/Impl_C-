#include <iostream>

struct Controllable {
    static inline size_t cnt = 0;
    Controllable()  {
        std::cout << "Controllable(): " << std::endl;
    }

    Controllable(Controllable&& rhs) noexcept {
        std::cout << "Controllable(Controllable&&)" << cnt << std::endl;
    }
    Controllable& operator=(Controllable&& rhs) noexcept {
        std::cout << "operator= Controllable&&" << std::endl;
        return *this;
    }
    Controllable(const Controllable& rhs) {
        std::cout << "Controllable(const Controllable&)" << std::endl;
    }
    Controllable& operator=(const Controllable& rhs) {
        std::cout << "operator= const Controllable&" <<  std::endl;
        return *this;
    }
    ~Controllable() { 
        std::cout << "~Controllable()" << std::endl; 
    }
};
