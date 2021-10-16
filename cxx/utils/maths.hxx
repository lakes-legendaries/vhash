#ifdef UTILS_MATHS_H

template <class Z, class I>
bool utils::maths::isclose(const Z& x, const I& y) {
    return std::abs(x - y) < 1E-6;
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
Z utils::maths::sum(const vector <Z>& vec) {
    Z out = 0;
    for (size_t g = 0; g < vec.size(); g++) {
        out += vec[g];
    }
    return out;
}

#endif
