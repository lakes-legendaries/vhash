from math import isclose

from numpy import array

from vhash import VHash


def test():

    # make sample data
    docs = [
        'hi, my name is Mike',
        'hi, my name is George',
        'hello, my name is Mike',
    ]
    labels = [1, 0, 1]

    # instantiate classs
    vhash = VHash()

    # transform documents
    transformed = array(vhash.fit_transform(docs, labels))

    # check results
    assert(all([dim == 3 for dim in transformed.shape]))
    assert(isclose(transformed[0, 0], 1, abs_tol=1E-6))
    assert(isclose(transformed[1, 1], 1, abs_tol=1E-6))
    assert(isclose(transformed[2, 2], 1, abs_tol=1E-6))
    assert(transformed[0, 2] > transformed[0, 1])
    assert(transformed[2, 0] > transformed[2, 1])


if __name__ == '__main__':
    test()
