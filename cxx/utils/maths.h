#ifndef UTILS_MATHS_H
#define UTILS_MATHS_H

#include <cmath>
#include <vector>

using std::vector;


namespace utils {
    namespace maths {

        /* check if two numbers are close

        Parameters
        ----------
        x: const Z&
            any scalar
        y: const I&
            any scalar

        Returns
        -------
        bool
            True if |x - y| < 1E-6
         */
        template <class Z, class I>
        bool isclose(const Z& x, const I& y);

        /* elementwise equality

        Parameters
        ----------
        vec: const vector <Z>&
            vector of values
        value: const I&
            value to compare to

        Returns
        -------
        vector <char>
            elementwise equality
         */
        template <class Z, class I>
        vector <char> equals(const vector <Z>& vec, const I& value);
        
        /* vector max

        Parameters
        ----------
        vec: const vector <Z>&
            vector of values

        Returns
        -------
        Z
            max value of vec
         */
        template <class Z>
        Z max(const vector <Z>& vec);

        /* vector min

        Parameters
        ----------
        vec: const vector <Z>&
            vector of values

        Returns
        -------
        Z
            min value of vec
         */
        template <class Z>
        Z min(const vector <Z>& vec);

        /* vector norm

        Parameters
        ----------
        vec: const vector <Z>&
            vector of values

        Returns
        -------
        float
            vector norm
         */
        template <class Z>
        float norm(const vector <Z>& vec);

        /* normalize vector

        Parameters
        ----------
        vec: const vector <Z>&
            vector of values

        Returns
        -------
        vector <float>
            normalized vector
         */
        template <class Z>
        vector <Z> normalize(const vector <Z>& vec);

        /* vector sum

        Parameters
        ----------
        vec: const vector <Z>&
            vector of values

        Returns
        -------
        I
            sum of vec
         */
        template <class Z, class I>
        I sum(const vector <Z>& vec);

       /* vector sum

        Parameters
        ----------
        vec: const vector <Z>&
            vector of values

        Returns
        -------
        Z
            sum of vec
         */
        template <class Z>
       Z sum(const vector <Z>& vec);
    }
}
#include <utils/maths.hxx>
#endif
