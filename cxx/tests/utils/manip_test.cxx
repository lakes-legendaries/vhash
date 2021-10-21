#include <cassert>

#include <utils/manip.h>
#include <utils/maths.h>

using namespace utils;

void test_rand_select() {
    vector <char> selected = manip::rand_select(100, 30);
    assert(maths::sum(selected) == 30);
    assert(maths::max(selected) == 1);

    selected = manip::rand_select(10, 30);
    assert(maths::sum(selected) == 10);
    assert(maths::max(selected) == 1);
}

int main() {
    test_rand_select();
}
