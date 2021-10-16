#include <cassert>

#include <utils/maths.h>

using namespace utils;

#include <iostream>
using std::cout;

void test_isclose() {
    assert(maths::isclose(0, 1E-7));
    assert(maths::isclose(10, 10.0000001));
    assert(maths::isclose(10, 9.99999999));
}

void test_max() {
    assert(maths::isclose(maths::max(vector <float>{0, -1, 5.6, 2.8}), 5.6));
    assert(maths::isclose(maths::max(vector <int>{0, -1, 7, -48}), 7));
}

void test_sum() {
    assert(maths::isclose(maths::sum(vector <float>{7, 2.5, 3}), 12.5));
    assert(maths::sum(vector <int>{5, 1, -3}) == 3);
}

int main() {
    test_isclose();
    test_max();
    test_sum();
}
