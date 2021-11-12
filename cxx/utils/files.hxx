#ifdef UTILS_FILES_H

template <class Z>
Z utils::files::open(const string& fname) {
	Z file;
	file.open(fname.c_str(), std::ios::binary);
	if (!file.is_open()) {
		throw std::runtime_error("Could not find/open/create file: " + fname);
	}
	return file;
}

template <class Z>
Z utils::files::binary_read(ifstream& file) {
	char *pt = new char[sizeof(Z)]; // create input buffer
	file.read(pt, sizeof(Z));       // read to input buffer
	Z out = *((Z*)pt);              // convert to Z type
	delete[] pt;                    // delete input buffer
	return out;                     // return data
}

template <class Z>
vector <Z> utils::files::binary_read_vec(ifstream& file) {
	uint32_t num_pts = binary_read <uint32_t>(file);
	char *pt = new char[sizeof(Z) * num_pts];              // create input buffer
	file.read(pt, sizeof(Z) * num_pts);                    // read to input buffer
	vector <Z> out = vector <Z>((Z*)pt, (Z*)pt + num_pts); // convert to Z type (by range)
	delete[] pt;                                           // delete input buffer
	return out;                                            // return data
}

template <class Z>
void utils::files::binary_write(ofstream& file, const Z& data) {
	file.write((char*)&data, sizeof(Z)); // write single data point
}

template <class Z>
void utils::files::binary_write(ofstream& file, const vector <Z>& data) {
	binary_write <uint32_t>(file, data.size());           // write size of data
	file.write((char*)&data[0], sizeof(Z) * data.size()); // write data
}

#endif
