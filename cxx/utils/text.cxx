#include <utils/text.h>

using namespace utils;


string text::format(string line) {

    // Remove non-alphanumeric characters
    for (size_t c = 0; c < line.size(); c++) {
        if (isalnum(line[c])) {continue;}
        line[c] = ' ';
    }

    // Remove repeated whitespace
    for (size_t c = 0; c < line.size(); c++) {
        if (line[c] == ' ' && (c + 1 == line.size() || line[c+1] == ' ')) {
            line.erase(c--, 1);
        }
    }

    // Send to lowercase
    for (size_t c = 0; c < line.size(); c++) {
        if (!isalpha(line[c])) {continue;}
        line[c] = tolower(line[c]);
    }

    // Separate characters from numbers
    for (size_t c = 0; c + 1 < line.size(); c++) {
        size_t cur_score  = !!isalpha(line[c  ]) + 2 * !!isdigit(line[c  ]);
        size_t next_score = !!isalpha(line[c+1]) + 2 * !!isdigit(line[c+1]);
        if (cur_score + next_score != 3) {continue;}
        line.insert(c+1, " ");
    }

    // Remove surrounding whitespace
    {
        size_t start = 0, finish = line.size();
        while (start < line.size() && line[start] == ' ') {start++;}
        while ((int)finish >= 0 && line[finish-1] == ' ') {finish--;}
        line = line.substr(start, finish - start + 1);
    }

    // Return result
    return line;
}

vector <string> text::get_words(const string& line) {

    // Format string
    string fline = format(line);

    // Extract words (by spaces)
    vector <string> words;
    for (size_t c = 0, start = 0; c < fline.size(); c++) {
        if (c + 1 == fline.size()) {c++;}              // end of line -- get last word of line
        else if (fline[c] != ' ') {continue;}          // skip if not a space
        words.push_back(fline.substr(start, c-start)); // save word
        start = c + 1;                                 // save position of start of next word
    }

    // Return result
    return words;
}

vector <string> text::get_phrases(const string& line, const size_t& phrase_len) {

    // Get words
    vector <string> words = get_words(line);

    // Error-checking (not enough words to make any phrases)
    if (words.size() < phrase_len) {return vector <string>();}

    // Meta-data
    size_t num_phrases = words.size() - phrase_len + 1;

    // Get phrases
    vector <string> phrases(num_phrases);
    for (size_t phrase_num = 0; phrase_num < num_phrases; phrase_num++) {
        for (size_t phrase_pos = 0; phrase_pos < phrase_len; phrase_pos++) {
            phrases[phrase_num] += (phrase_pos? " ": "") + words[phrase_num + phrase_pos];
        }
    }

    // Return result
    return phrases;
}
