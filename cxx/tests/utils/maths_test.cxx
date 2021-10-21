#include <cassert>

#include <utils/maths.h>

using namespace utils;

void test_isclose() {
    assert(maths::isclose(0, 1E-7));
    assert(maths::isclose(10, 10.0000001));
    assert(maths::isclose(10, 9.99999999));
}

void test_equals() {
    assert(maths::sum(maths::equals(vector <size_t>{0, 1, 0, 1, 0}, 0)) == 3);
    assert(maths::sum(maths::equals(vector <size_t>{0, 1, 0, 1, 0}, 1)) == 2);
    assert(maths::equals(vector <size_t>{0, 1, 0, 1, 0}, 1).size() == 5);
}

void test_max() {
    assert(maths::isclose(maths::max(vector <float>{0, -1, 5.6, 2.8}), 5.6));
    assert(maths::isclose(maths::max(vector <int>{0, -1, 7, -48}), 7));
}

void test_min() {
    vector <float> vec {0, -7, 5.6, 2.8, -12.2};
    assert(vec[4] == maths::min(vec));
}

void test_norm() {
    vector <float> vec {2, 3, 1, 1, 1};
    assert(maths::isclose(maths::norm(vec), 4));
}

void test_normalize() {
    vector <float> vec {7, 12, -6.7, 48, 0};
    vector <float> normalized = maths::normalize(vec);
    float total = 0;
    for (size_t g = 0; g < normalized.size(); g++) {
        total += pow(normalized[g], 2);
    }
    assert(maths::isclose(total, 1));
}

void test_sum() {
    assert(maths::isclose(maths::sum <float>(vector <float>{7, 2.5, 3}), 12.5));
    assert(maths::sum <int>(vector <int>{5, 1, -3}) == 3);
    assert((maths::sum <float, int>(vector <float>{7, 2.5, 3})) == 12);
}

int main() {
    test_isclose();
    test_equals();
    test_max();
    test_min();
    test_norm();
    test_normalize();
    test_sum();
}
