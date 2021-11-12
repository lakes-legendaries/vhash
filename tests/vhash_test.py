from math import isclose
from os import remove
from typing import Any

from nptyping import NDArray
from numpy import array

from vhash import VHash


def get_data() -> tuple[list[str], list[int]]:
    docs = [
        'hi, my name is Mike',
        'hi, my name is George',
        'hello, my name is Mike',
    ]
    labels = [1, 0, 1]
    return docs, labels


def check_result(transformed: NDArray[(Any, Any), float]):
    assert(all([dim == 3 for dim in transformed.shape]))
    assert(isclose(transformed[0, 0], 1, abs_tol=1E-6))
    assert(isclose(transformed[1, 1], 1, abs_tol=1E-6))
    assert(isclose(transformed[2, 2], 1, abs_tol=1E-6))
    assert(transformed[0, 2] > transformed[0, 1])
    assert(transformed[2, 0] > transformed[2, 1])


def test_fit():
    docs, labels = get_data()
    vhash = VHash().fit(docs, labels)
    transformed = array(vhash.transform(docs))
    check_result(transformed)
    assert((array(vhash.transform(['name'])) == 0).all())


def test_fit_transform():
    docs, labels = get_data()
    transformed = array(VHash().fit_transform(docs, labels))
    check_result(transformed)


def test_io():
    temp_fname = 'tests/model.bin'
    try:
        docs, labels = get_data()
        model = VHash().fit(docs, labels)
        transformed = array(model.transform(docs))
        model.save(temp_fname)
        model2 = VHash.load(temp_fname)
        transformed2 = array(model2.transform(docs))
        assert((transformed == transformed2).all())
    finally:
        remove(temp_fname)


if __name__ == '__main__':
    test_fit()
    test_fit_transform()
    test_io()
