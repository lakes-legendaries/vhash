#include <utils/sparse.h>

using namespace utils;


Sparse::Sparse(
    const size_t& max_index_,
    const vector <float>& values_,
    const vector <size_t>& indices_
): max_index(max_index_),
   values(values_),
   indices(indices_) {}

float Sparse::dot_product(const Sparse& multiplier) const {
    if (multiplier.num_nonzero() == 0) {return 0;}
    float out = 0;
    for (size_t i = 0, m_i = 0; i < num_nonzero(); i++) {
        while (indices[i] > multiplier.indices[m_i]) {
            if (++m_i == multiplier.num_nonzero()) {
                return out;
            }
        }
        if (indices[i] == multiplier.indices[m_i]) {
            out += values[i] * multiplier.values[m_i];
        }
    }
    return out;
}

float Sparse::dot_product(const vector <float>& multiplier) const {
    float out = 0;
    for (size_t g = 0; g < num_nonzero(); g++) {
        out += values[g] * multiplier[indices[g]];
    }
    return out;
}

Sparse Sparse::multiply(
    const vector <float>& multiplier,
    const bool& in_place
) {
    Sparse out = in_place? *this: Sparse(*this);
    for (size_t g = 0; g < num_nonzero(); g++) {
        out.values[g] *= multiplier[indices[g]];
    }
    return out;
}

Sparse Sparse::normalize() const {
    return Sparse(
        max_index,
        maths::normalize(values),
        indices
    );
}
