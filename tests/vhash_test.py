from __future__ import annotations

from copy import deepcopy
from math import isclose
from typing import Any

from nptyping import NDArray

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
    transformed = vhash.transform(docs)
    check_result(transformed)
    assert((vhash.transform(['name']) == 0).all())


def test_fit_transform():
    docs, labels = get_data()
    transformed = VHash().fit_transform(docs, labels)
    check_result(transformed)


def test_pickle():
    docs, labels = get_data()
    model = VHash().fit(docs, labels)
    transformed = model.transform(docs)
    model2 = deepcopy(model)
    model = None
    transformed2 = model2.transform(docs)
    assert((transformed == transformed2).all())


if __name__ == '__main__':
    test_fit()
    test_fit_transform()
    test_pickle()
