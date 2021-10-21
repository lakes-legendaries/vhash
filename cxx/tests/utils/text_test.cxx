#include <cassert>

#include <utils/text.h>

using namespace utils;

void test_format() {
    string line = "  hi42 my email Is miKe@gmail.com  ";
    assert(!text::format(line).compare("hi 42 my email is mike gmail com"));
}

void test_get_words() {
    string line = "hi, my name is Mike";
    vector <string> words = text::get_words(line);
    assert(words.size() == 5);
    assert(!words[0].compare("hi"));
    assert(!words[2].compare("name"));
    assert(!words[4].compare("mike"));
}

void test_get_phrases() {
    string line = "hi, my name is Mike";
    vector <string> phrases = text::get_phrases(line, 3);
    assert(phrases.size() == 3);
    assert(!phrases[0].compare("hi my name"));
    assert(!phrases[2].compare("name is mike"));
}

int main() {
    test_format();
    test_get_words();
    test_get_phrases();
}
