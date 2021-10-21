#include <cstdlib>

#include <utils/manip.h>

using namespace utils;


vector <char> manip::rand_select(const size_t& pool_size, const size_t& num_select) {
    if (num_select >= pool_size) {return vector <char>(pool_size, true);}
    vector <char> out(pool_size, false);
    for (size_t num_selected = 0; num_selected < num_select; num_selected++) {
        size_t index;
        do {
            index = rand() % pool_size;
        } while (out[index]);
        out[index] = true;
    }
    return out;
}
