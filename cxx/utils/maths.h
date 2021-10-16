#ifndef UTILS_MATHS_H
#define UTILS_MATHS_H
#include <cmath>
#include <vector>
using std::vector;
namespace utils {
    namespace maths {

        template <class Z, class I>
        bool isclose(const Z& x, const I& y);
        /*true if |x - y| < 1E-6*/

        template <class Z>
        Z max(const vector <Z>&);
        /*vector max*/

        template <class Z>
        Z sum(const vector <Z>&);
        /*vector sum*/
    }
}
#include <utils/maths.hxx>
#endif
