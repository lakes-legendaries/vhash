#ifndef UTILS_MANIP_H
#define UTILS_MANIP_H

#include <vector>

using std::vector;


namespace utils {
    namespace manip {

        /* Select `num_select` from `pool_size`

        Parameters
        ----------
        pool_size: const size_t&
            total number of possible choices
        num_select: const size_t&
            number to select (without repeats)

        Returns
        -------
        vector <char>
            boolean array w/ selected items as true
         */
        vector <char> rand_select(
            const size_t& pool_size,
            const size_t& num_select
        );
    }
}
#endif
