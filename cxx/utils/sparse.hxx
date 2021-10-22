#ifdef UTILS_SPARSE_H

template <class Z>
utils::Sparse::Sparse(const vector <Z>& dense): max_index(dense.size()) {
    for (size_t i = 0; i < max_index; i++) {
        if (!dense[i]) {continue;}
        indices.push_back(i);
        values.push_back(dense[i]);
    }
}

#endif
