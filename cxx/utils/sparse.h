#ifndef UTILS_SPARSE_H
#define UTILS_SPARSE_H

#include <utils/maths.h>


namespace utils {
    class Sparse {
        public:

            // ===============================================================
            // Constructors

            /* Empty constructor */
            Sparse() {}

            /* Make sparse vector from dense vector

            Parameters
            ----------
            dense: const vector <Z>&
                dense vector
             */
            template <class Z>
            Sparse(const vector <Z>& dense);

            /* Make sparse vector from predefined components

            Parameters
            ----------
            max_index_: const size_t&
                size of dense vector represented as sparse vector
            values_: const vector <float>&
                values of non-zero entries in dense vector
            indices: const vector <size_t>&
                indices of non-zero entries in dense vector
                This should be sorted!!
             */
            Sparse(
                const size_t& max_index_,
                const vector <float>& values_,
                const vector <size_t>& indices_
            );

            // ===============================================================
            // Data members

            /* size of dense vector */
            size_t max_index = 0;
            
            /* values of non-zero members */
            vector <float> values;

            /* indices of non-zero members */
            vector <size_t> indices;

            // ===============================================================
            // Maths

            /* Dot product of two sparse vectors

            Parameters
            ----------
            multiplier: const Sparse&
                Vector to use in computing inner product
            
            Returns
            -------
            float
                dot product
             */
            float dot_product(const Sparse& multiplier) const;

            /* Dot product with a dense vector

            Parameters
            ----------
            multiplier: const vector <float>&
                Vector to use in computing inner product
            
            Returns
            -------
            float
                dot product
             */
            float dot_product(const vector <float>& multiplier) const;

            /* Elementwise multiplication

            Parameters
            ----------
            multiplier: const vector <float>&
                Vector to use in computing inner product
            in_place: bool
                Whether operation should be done in place
            
            Returns
            -------
            Sparse
                resulting vector (or calling object, if `in_place`)
             */
            Sparse multiply(
                const vector <float>& multiplier,
                const bool& in_place = false
            );

            /* Normalize vector

            Returns
            -------
            Sparse
                Normalized sparse vector
             */
            Sparse normalize() const;

            // ===============================================================
            // Meta-data

            /* Check if vector is empty
            
            Returns
            -------
            bool
                True if vector is empty
             */
            bool empty() const {return indices.empty();}

            /* Number of non-zero elements in sparse vector
            
            Returns
            -------
            size_t
                Number of non-zero elements in sparse vector
             */
            size_t num_nonzero() const {return indices.size();}
    };
}
#include <utils/sparse.hxx>
#endif
