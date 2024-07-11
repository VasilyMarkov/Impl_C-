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
// TEST(Vector, controllable_constructor) {
//     Vector<Controllable> v(2);
// }

