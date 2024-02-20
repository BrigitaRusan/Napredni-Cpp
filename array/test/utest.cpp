#include "gtest/gtest.h"
#include "../src/array.h"

#include <memory>
#include <stdexcept>

template <typename T>
class ArrayTest : public ::testing::Test {
protected:
	Array<int, 3> ars;
};

using MyTypes = ::testing::Types<char, int, long, float, double>;
TYPED_TEST_SUITE(ArrayTest, MyTypes);

TYPED_TEST(ArrayTest, DefaultConstructor) {
    Array<TypeParam, 4> a;
    for (std::size_t i = 0; i < 4; ++i) {
        EXPECT_EQ(a[i], TypeParam());
    }
}

TYPED_TEST(ArrayTest, ParamConstruct){
    Array<TypeParam, 5> a(TypeParam(6));
    for (std::size_t i = 0; i < 5; ++i) {
        EXPECT_EQ(a[i], TypeParam(6));
    }
}

TYPED_TEST(ArrayTest, CopyConstructor) {
    Array<TypeParam, 3> original;
    for (std::size_t i = 0; i < 3; ++i) {
        original[i] = i;
    }

    Array<TypeParam, 3> copy(original);

    for (std::size_t i = 0; i < 3; ++i) {
        EXPECT_EQ(copy[i], original[i]);
    }
}

TYPED_TEST(ArrayTest, AssignmentOperator) {
    Array<TypeParam, 3> original, assigned;
    for (std::size_t i = 0; i < 3; ++i) {
        original[i] = i;
    }
    assigned = original;

    for (std::size_t i = 0; i < 3; ++i) {
        EXPECT_EQ(assigned[i], original[i]);
    }
}

TYPED_TEST(ArrayTest, InitListConstructor){
    EXPECT_THROW( (Array<TypeParam, 2>{TypeParam(1), TypeParam(2), TypeParam(3)}), std::runtime_error);

    Array<TypeParam, 3> arr{TypeParam(1), TypeParam(2), TypeParam(3)};
    for (std::size_t i = 0; i < 3; ++i) {
        EXPECT_EQ(arr[i], static_cast<TypeParam>(i+1));
        }
}
TYPED_TEST(ArrayTest, IndexOperatorConst) {
    const Array<TypeParam, 3> arr = {TypeParam(1), TypeParam(2), TypeParam(3)};

    for (std::size_t i = 0; i < 3; ++i) {
        EXPECT_EQ(arr[i], static_cast<TypeParam>(i + 1));
    }
}
TYPED_TEST(ArrayTest, IndexOperatorNonConst) {
    Array<TypeParam, 3> arr;
    for (std::size_t i = 0; i < 3; ++i) {
        arr[i] = static_cast<TypeParam>(i + 1);
    }

    for (std::size_t i = 0; i < 3; ++i) {
        EXPECT_EQ(arr[i], static_cast<TypeParam>(i + 1));
    }
}
TYPED_TEST(ArrayTest, MoveOnlyTypeIndexOperator) {
    Array<std::unique_ptr<int>, 3> arr;
    for (int i = 0; i < 3; ++i) {
        arr[i] = std::make_unique<int>(i);
        EXPECT_EQ(*(arr[i]), i);
    }


    auto moved_ptr = std::move(arr[1]);
    EXPECT_EQ(arr[1], nullptr);
    EXPECT_EQ(*moved_ptr, 1);
}

TYPED_TEST(ArrayTest, RangeForLoop) {
    Array<TypeParam, 3> arr;

    for (std::size_t i = 0; i < 3; ++i) {
        arr[i] = i+1;
    }

    int i = 1;
    for (TypeParam value : arr) {
        EXPECT_EQ(value, i);
        ++i;
    }
}

TYPED_TEST(ArrayTest, EqualityOperator) {
    Array<double, 3> arr1{1.0,2.0,3.0};
    Array<int, 3> arr2{1,2,3};
    // OVO NE TESTIRA OPERATOR ==
    for (std::size_t i = 0; i < 3; ++i){
         EXPECT_EQ(arr1[i], arr2[i]);
     }

}
