#ifdef UTILS_MATHS_H

template <class Z, class I>
bool utils::maths::isclose(const Z& x, const I& y) {
    return std::abs(x - y) < 1E-6;
}

template <class Z, class I>
vector <char> utils::maths::equals(
    const vector <Z>& vec,
    const I& value
) {
    vector <char> out(vec.size());
    for (size_t g = 0; g < vec.size(); g++) {
        out[g] = vec[g] == (Z)value;
    }
    return out;
}

template <class Z>
Z utils::maths::max(const vector <Z>& vec) {
    if (vec.empty()) {return 0;}
    Z out = vec[0];
    for (size_t g = 1; g < vec.size(); g++) {
        if (vec[g] > out) {
            out = vec[g];
        }
    }
    return out;
}

template <class Z>
Z utils::maths::min(const vector <Z>& vec) {
    if (vec.empty()) {return 0;}
    Z out = vec[0];
    for (size_t g = 1; g < vec.size(); g++) {
        if (vec[g] < out) {
            out = vec[g];
        }
    }
    return out;
}

template <class Z>
float utils::maths::norm(const vector <Z>& vec) {
    float out = 0;
    for (size_t g = 0; g < vec.size(); g++) {
        out += pow(vec[g], 2);
    }
    return std::sqrt(out);
}

template <class Z>
vector <Z> utils::maths::normalize(const vector <Z>& vec) {
    if (vec.empty()) {return vector <Z>();}
    float vec_norm = norm(vec);
    if (vec_norm == 0) {return vec;}
    vector <Z> out(vec.size());
    for (size_t g = 0; g < vec.size(); g++) {
        out[g] = vec[g] / vec_norm;
    }
    return out;
}

template <class Z, class I>
I utils::maths::sum(const vector <Z>& vec) {
    I out = 0;
    for (size_t g = 0; g < vec.size(); g++) {
        out += vec[g];
    }
    return out;
}

template <class Z>
Z utils::maths::sum(const vector <Z>& vec) {
    return sum<Z, Z>(vec);
}

#endif
