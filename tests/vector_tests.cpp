#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "vector.hpp"
#include "Controllable.hpp"

using namespace my;

TEST(Vector, zero_constructor) {
    Vector<int> v(2);
    EXPECT_EQ(v[0], 0);
    EXPECT_EQ(v[1], 0);
}

TEST(Vector, reserve) {
    Vector<int> v(1);
    v.reserve(3);
    EXPECT_EQ(v.size(), 1);
    EXPECT_EQ(v.capacity(), 3);
    EXPECT_EQ(v[0], 0);
}

TEST(Vector, at) {
    Vector<int> v;
    v.push_back(2);
    v.push_back(3);
    EXPECT_EQ(v.at(0), 2);
    EXPECT_EQ(v.at(1), 3);
}

TEST(Vector, copy_constructor) {
    Vector<int> v1;
    v1.push_back(2);
    v1.push_back(3);
    v1.push_back(4);
    Vector<int> v2(v1);
    EXPECT_EQ(v2.size(), 3);
    EXPECT_EQ(v2.capacity(), 3);
    EXPECT_EQ(v2[0], 2);
    EXPECT_EQ(v2[1], 3);
    EXPECT_EQ(v2[2], 4);
}

TEST(Vector, copy_operator) {
    Vector<int> v1;
    v1.push_back(2);
    v1.push_back(3);
    v1.push_back(4);
    Vector<int> v2 = v1;;
    EXPECT_EQ(v2.size(), 3);
    EXPECT_EQ(v2.capacity(), 3);
    EXPECT_EQ(v2[0], 2);
    EXPECT_EQ(v2[1], 3);
    EXPECT_EQ(v2[2], 4);
}

TEST(Vector, move_constructor) {
    Vector<int> v1;
    v1.push_back(2);
    v1.push_back(3);
    v1.push_back(4);
    Vector<int> v2(std::move(v1));
    EXPECT_EQ(v2.size(), 3);
    EXPECT_EQ(v2.capacity(), 4);
    EXPECT_EQ(v2[0], 2);
    EXPECT_EQ(v2[1], 3);
    EXPECT_EQ(v2[2], 4);
}

TEST(Vector, move_operator) {
    Vector<int> v1;
    v1.push_back(2);
    v1.push_back(3);
    v1.push_back(4);
    Vector<int> v2 = std::move(v1);
    EXPECT_EQ(v2.size(), 3);
    EXPECT_EQ(v2.capacity(), 4);
    EXPECT_EQ(v2[0], 2);
    EXPECT_EQ(v2[1], 3);
    EXPECT_EQ(v2[2], 4);
}

TEST(Vector, it_constructor) {
    std::vector<int> v1 = {1,2,3};
    Vector<int> v2(std::begin(v1), std::end(v1));
    EXPECT_EQ(v2.size(), 3);
    EXPECT_EQ(v2.capacity(), 3);
    EXPECT_EQ(v2[0], 1);
    EXPECT_EQ(v2[1], 2);
    EXPECT_EQ(v2[2], 3);
}

TEST(Vector, push_back) {
    Vector<int> v;
    v.push_back(2);
    int a = 5;
    v.push_back(a);
    v.push_back(4);
    EXPECT_EQ(v.size(), 3);
    EXPECT_EQ(v.capacity(), 4);
    EXPECT_EQ(v[0], 2);
    EXPECT_EQ(v[1], 5);
    EXPECT_EQ(v[2], 4);
}

TEST(Vector, emplace_back) {
    Vector<int> v;
    v.emplace_back(2);
    EXPECT_EQ(v.size(), 1);
    EXPECT_EQ(v.capacity(), 2);
    EXPECT_EQ(v[0], 2);
}

TEST(Vector, pop_back) {
    Vector<int> v;
    v.push_back(2);
    v.push_back(3);
    v.push_back(4);
    v.pop_back();
    EXPECT_EQ(v.size(), 2);
    EXPECT_EQ(v.capacity(), 4);
    EXPECT_EQ(v[0], 2);
    EXPECT_EQ(v[1], 3);
}

TEST(Vector, fill_constructor) {
    Vector<int> v(2,2);
    EXPECT_EQ(v.size(), 2);
    EXPECT_EQ(v.capacity(), 4);
    EXPECT_EQ(v[0], 2);
    EXPECT_EQ(v[1], 2);
}





