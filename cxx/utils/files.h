#ifndef UTILS_FILES_H
#define UTILS_FILES_H

#include <fstream>
#include <string>
#include <vector>

using std::ifstream;
using std::ofstream;
using std::string;
using std::vector;

namespace utils {
    namespace files {

        /* Open binary file

        Template
        --------
        Z
            ifstream or ofstream

        Parameters
        ----------
        fname: const str&
            file to open

        Returns
        -------
        Z
            file handle
        
        Raises
        ------
        std::runtime_error
            if can't open file
         */
        template <class Z>
        Z open(const string& fname);

        /* Read 1 data point from a binary file

        Template
        --------
        Z
            data type

        Parameters
        ----------
        file: ifstream&
            file handler

        Returns
        -------
        Z
            data pt
        */
        template <class Z>
        Z binary_read(ifstream& file);

        template <>
        string binary_read <string>(ifstream& file);

        /* Read a vector from a binary file

        Template
        --------
        Z
            data type

        Parameters
        ----------
        file: ifstream&
            file handler

        Returns
        -------
        vector <Z>
            vector from file
        */
        template <class Z> 
        vector <Z> binary_read_vec(ifstream& file);

        /* Write 1 data point to a binary file

        Template
        --------
        Z
            data type

        Parameters
        ----------
        file: ofstream&
            file handler
        pt: const Z&
            data point to write
        */
        template <class Z>
        void binary_write(ofstream& file, const Z& pt);

        template <>
        void binary_write <string>(ofstream& file, const string& pt);

        /* Write a vector to a binary file

        Template
        --------
        Z
            data type

        Parameters
        ----------
        file: ofstream&
            file handler
        pts: const vector <Z>&
            vector to write
        */
        template <class Z> 
        void binary_write(ofstream& file, const vector <Z>& pts);
    }
}
#include <utils/files.hxx>
#endif
