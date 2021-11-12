#include <utils/files.h>

using namespace utils;

template <>
string files::binary_read <string>(ifstream& file) {
    size_t size = binary_read <size_t>(file);
    string str;
    str.resize(size);
    file.read(&str[0], size);
    return str;
}

template <>
void files::binary_write <string>(ofstream& file, const string& pt) {
    size_t size = pt.size();
    binary_write(file, size);
    file.write((char*)&pt[0], size);
}
