#include <cassert>

#include <utils/maths.h>
#include <utils/sparse.h>

using namespace utils;

void test_constructor() {
    Sparse sparse(vector <float>{5, 0, 0, 7, 0, 0, -9, 0, 3.6});
    assert(sparse.num_nonzero() == 4);
    assert(maths::isclose(sparse.values[3], 3.6));
    assert(sparse.indices[1] == 3);
}

void test_dot_product_dense() {
    vector <float> dense_a = {0, 0, 4, 7, -2, 0, 1.0};
    vector <float> dense_b = {7, 2, 0, 3, 12, 0, 2.3};
    Sparse sparse_a(dense_a);
    Sparse sparse_b(dense_b);
    assert(maths::isclose(sparse_a.dot_product(sparse_b), -0.7));
    assert(maths::isclose(sparse_b.dot_product(sparse_a), -0.7));
}

void test_dot_product_sparse() {
    vector <float> dense_a = {0, 0, 4, 7, -2, 0, 1.0};
    vector <float> dense_b = {7, 2, 0, 3, 12, 0, 2.3};
    Sparse sparse_a(dense_a);
    assert(maths::isclose(sparse_a.dot_product(dense_b), -0.7));
}

void test_multiply() {
    vector <float> dense_a = {0, 0, 4, 7, -2, 0, 1.0};
    vector <float> dense_b = {7, 2, 0, 3, 12, 0, 2.3};
    Sparse sparse_a = Sparse(dense_a).multiply(dense_b, true);
    assert(sparse_a.num_nonzero() == 4);
    assert(maths::isclose(sparse_a.values[0], 0));
    assert(maths::isclose(sparse_a.values[1], 21));
    assert(maths::isclose(sparse_a.values[2], -24));
    assert(maths::isclose(sparse_a.values[3], 2.3));
}

void test_normalize() {
    Sparse sparse(vector <float>{5, 0, 0, 7, 0, 0, -9, 0, 3.6});
    sparse = sparse.normalize();
    float total = 0;
    for (size_t g = 0; g < sparse.num_nonzero(); g++) {
        total += pow(sparse.values[g], 2);
    }
    assert(maths::isclose(total, 1));
}

int main() {
    test_constructor();
    test_dot_product_sparse();
    test_dot_product_dense();
    test_multiply();
    test_normalize();
}
