#include <iostream>

class Test {
    inline static size_t cnt = 0;
public:
    Test() {cnt++; std::cout << "Test() " << cnt << std::endl;}
    Test(const Test& t) {cnt++; std::cout << "Test(const Test&) " << cnt << std::endl;}
    Test(Test&& t) {cnt++; std::cout << "Test(Test&&) " << cnt << std::endl;}
    Test& operator=(const Test& t) {std::cout << "operator=(const Test&)" << std::endl; return *this;}
    Test operator=(Test&& t) {std::cout << "operator=(Test&&)" << std::endl; return *this;}
    ~Test() {std::cout << "~Test() " << cnt << std::endl; --cnt;}
};

Test f(const Test& t) {
    auto r = t;
    return r;
};

int main() {
    auto b = Test();
    auto c = std::move(b);
    return 0;
}