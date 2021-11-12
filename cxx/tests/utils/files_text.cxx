#include <cassert>

#include <utils/files.h>

using namespace utils;

void test_open() {

    // check writing
    ofstream ofile = files::open <ofstream>("bin/test.bin");
    ofile.close();

    // check reading
    ifstream ifile = files::open <ifstream>("bin/test.bin");
    ifile.close();
}

void test_single() {

    // sample date
    int a = 5;
    float b = 7;
    double c = 12.7;

    // open file for writing
    ofstream ofile = files::open <ofstream>("bin/test.bin");

    // write data
    files::binary_write(ofile, a);
    files::binary_write(ofile, b);
    files::binary_write(ofile, c);

    // close file
    ofile.close();

    // open file for reading
    ifstream ifile = files::open <ifstream>("bin/test.bin");

    // read data
    int a2 = files::binary_read <int>(ifile);
    float b2 = files::binary_read <float>(ifile);
    double c2 = files::binary_read <double>(ifile);

    // close file
    ifile.close();

    // check results
    assert(a == a2);
    assert(b == b2);
    assert(c == c2);
}

void test_vec() {

    // sample data
    vector <float> data = {4, 5.6, 489, -7};

    // write data
    ofstream ofile = files::open <ofstream>("bin/test.bin");
    files::binary_write(ofile, data);
    ofile.close();

    // read data
    ifstream ifile = files::open <ifstream>("bin/test.bin");
    vector <float> data2 = files::binary_read_vec <float>(ifile);
    ifile.close();

    // check results
    assert(data.size() == data2.size());
    for (size_t g = 0; g < data.size(); g++) {
        assert(data[g] == data2[g]);
    }
}

void test_str() {

    // sample data
    string data = "Hello, world!";

    // write data
    ofstream ofile = files::open <ofstream>("bin/test.bin");
    files::binary_write(ofile, data);
    ofile.close();

    // read data
    ifstream ifile = files::open <ifstream>("bin/test.bin");
    string data2 = files::binary_read <string>(ifile);
    ifile.close();

    // check results
    assert(!data.compare(data2));
}

int main() {
    test_open();
    test_single();
    test_vec();
    test_str();
}
