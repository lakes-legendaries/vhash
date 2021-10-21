#ifndef UTILS_TEXT_H
#define UTILS_TEXT_H

#include <string>
#include <vector>

using std::string;
using std::vector;


namespace utils {
    namespace text {
        
        /* apply standard formatting to line

        This operation:

        #. removes non-alphanumeric characters
        #. removes repeated whitespace
        #. sends all text to lowercase
        #. adds spaces between adjacent characters and numbers
        #. removes surrounding whitespace

        Parameters
        ----------
        line: const string&
            line to format

        Returns
        -------
        string
            formatted line
         */
        string format(string line);
        
        /* break line into words

        automatically applies text::format()

        Parameters
        ----------
        line: const string&
            line to process

        Returns
        -------
        vector <string>
            words in line
         */
        vector <string> get_words(const string& line);

        /* break line into phrases

        automatically applies text::format()

        Parameters
        ----------
        line: const string&
            line to process
        phrase_len: const size_t&
            phrase length

        Returns
        -------
        vector <string>
            phrases in line (of length phrase_len)
         */
        vector <string> get_phrases(
            const string& line,
            const size_t& phrase_len
        );
    }
}
#endif
