#include <cassert>

#include <vhash/vhash.h>

using namespace vhash;


void test_private() {
    VHash::_test();
}

int main() {
    test_private();
}
