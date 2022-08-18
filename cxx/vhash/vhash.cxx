#include <cassert>

#include <utils/files.h>
#include <utils/manip.h>
#include <utils/maths.h>
#include <utils/text.h>
#include <vhash/vhash.h>

using namespace utils;
using namespace vhash;


VHash::VHash(
    const size_t& largest_ngram,
    const float&  min_phrase_occurrence,
    const size_t& num_features,
    const size_t& max_num_phrases,
    const size_t& downsample_to,
    const size_t& live_evaluation_step,
    const size_t& smallest_ngram
):
    _largest_ngram(largest_ngram),
    _min_phrase_occurrence(min_phrase_occurrence),
    _num_features(num_features),
    _max_num_phrases(max_num_phrases),
    _downsample_to(downsample_to),
    _live_evaluation_step(live_evaluation_step),
    _smallest_ngram(smallest_ngram) {
}

VHash VHash::fit(
    const vector <string>& docs,
    const vector <size_t>& labels
) {
    // downsample docs
    _num_docs = maths::min(vector <size_t>{docs.size(), _downsample_to});
    vector <char> insert_me = manip::rand_select(docs.size(), _num_docs);

    // create table
    _create_table(docs, insert_me);

    // compute weights
    _compute_weights(docs, labels, insert_me);

    // make features
    _make_features(docs);

    // return
    return *this;
}

vector <vector <float>> VHash::fit_transform(
    const vector <string>& docs,
    const vector <size_t>& labels
) {
    return fit(docs, labels).transform(docs);
}

vector <vector <float>> VHash::transform(
    const vector <string>& docs
) {
    vector <vector <float>> out(docs.size(), vector <float>(_features.size()));
    for (size_t doc_num = 0; doc_num < docs.size(); doc_num++) {
        Sparse vectorized = 
            _vectorize(docs[doc_num])
            .multiply(_weights, true)
            .normalize()
        ;
        for (size_t feature_num = 0; feature_num < _features.size(); feature_num++) {
            out[doc_num][feature_num] = vectorized.dot_product(_features[feature_num]);
        }
    }
    return out;
}

#ifndef __CXX_TESTING__
py::tuple VHash::__get_state__(const vhash::VHash &v) {
    
    // serialize hash table
    size_t hash_size = v._table.size();
    vector <string> hash_keys;
    vector <size_t> hash_values;
    for (auto it = v._table.begin(); it != v._table.end(); it++) {
        hash_keys.push_back((*it).first);
        hash_values.push_back((*it).second);
    }

    // serialize features
    size_t features_size = v._features.size();
    vector <size_t> features_max_index;
    vector <vector <size_t>> features_index;
    vector <vector <float>> features_value;
    for (auto feature: v._features) {
        features_max_index.push_back(feature.max_index);
        features_index.push_back(feature.indices);
        features_value.push_back(feature.values);
    }

    // return state
    return py::make_tuple(
        v._largest_ngram,
        v._min_phrase_occurrence,
        v._num_features,
        v._max_num_phrases,
        v._downsample_to,
        v._live_evaluation_step,
        v._smallest_ngram,
        v._num_docs,
        hash_size,
        hash_keys,
        hash_values,
        features_size,
        features_max_index,
        features_index,
        features_value,
        v._weights
    );
}

VHash VHash::__set_state__(py::tuple t) {
    
    // initialize
    VHash v;
    size_t g = 0;

    // set parameters
    v._largest_ngram = t[g++].cast<size_t>();
    v._min_phrase_occurrence = t[g++].cast<float>();
    v._num_features = t[g++].cast<size_t>();
    v._max_num_phrases = t[g++].cast<size_t>();
    v._downsample_to = t[g++].cast<size_t>();
    v._live_evaluation_step = t[g++].cast<size_t>();
    v._smallest_ngram = t[g++].cast<size_t>();
    v._num_docs = t[g++].cast<size_t>();

    // reconstruct hash table
    size_t hash_size = t[g++].cast<size_t>();
    vector <string> hash_keys = t[g++].cast<vector <string>>();
    vector <size_t> hash_values = t[g++].cast<vector <size_t>>();
    for (size_t h = 0; h < hash_size; h++) {
        v._table.insert(
            std::pair <string, size_t>(
                hash_keys[h],
                hash_values[h]
            )
        );
    }

    // load in features
    size_t features_size = t[g++].cast<size_t>();
    vector <size_t> features_max_index = t[g++].cast<vector <size_t>>();
    vector <vector <size_t>> features_index = t[g++].cast<vector <vector <size_t>>>();
    vector <vector <float>> features_value = t[g++].cast<vector <vector <float>>>();
    for (size_t h = 0; h < features_size; h++) {
        v._features.push_back(
            Sparse(
                features_max_index[h],
                features_value[h],
                features_index[h]
            )
        );
    }

    // reconstruct weights
    v._weights = t[g++].cast<vector <float>>();

    // return
    return v;
}
#endif

void VHash::_test() {
    _test_basic_creation();
    _test_min_phrase_occurrence();
    _test_assigned_indices();
    _test_weights();
    _test_vectorization();
    _test_transform();
    _test_null();
}

void VHash::_create_table(
    const vector <string>& docs,
    const vector <char>& insert_me
) {

    // insert documents
    for (size_t doc_num = 0; doc_num < docs.size(); doc_num++) {

        // insert document, if preselected
        if (insert_me[doc_num]) {

            // Get phrases contained in document
            vector <string> phrases = _break_into_phrases(docs[doc_num]);

            // Add each phrase to table
            for (const string& phrase: phrases) {
                auto element = _table.find(phrase);
                if (element == _table.end()) {
                    _table.insert(std::pair <string, size_t>(phrase, 1));
                } else {
                    (*element).second++;
                }
            }
        }

        // Knock table down to a reasonable size
        if ((doc_num + 1) % _live_evaluation_step == 0) {
            for (size_t remove_thresh = 2; _table.size() > _max_num_phrases; remove_thresh++) {
                _remove_infreq(remove_thresh);
            }
        }
    }

    // remove infrequent members
    size_t final_size = (
        _min_phrase_occurrence > 1?
            _min_phrase_occurrence:
            _min_phrase_occurrence * _num_docs
    );
    _remove_infreq(final_size);

    // assign an index to each table entry
    _assign_indices();
}

void VHash::_compute_weights(
    const vector <string>& docs,
    const vector <size_t>& labels,
    const vector <char>& insert_me
) {
    // resize weights
    _weights = vector <float>(_table.size());

    // get meta-data
    size_t num_classes = maths::max(labels) + 1;

    // get count of number of docs in each class
    vector <size_t> docs_in_class(num_classes, 0);
    for (size_t doc_num = 0; doc_num < docs.size(); doc_num++) {
        if (!insert_me[doc_num]) {continue;}
        docs_in_class[labels[doc_num]]++;
    }

    // get document frequency for each phrase
    vector <vector <size_t>> doc_freq(_table.size(), vector <size_t>(num_classes, 0));
    for (size_t doc_num = 0; doc_num < docs.size(); doc_num++) {

        // check if document is being used (downsampling)
        if (!insert_me[doc_num]) {continue;}

        // get phrases
        vector <string> phrases = _break_into_phrases(docs[doc_num]);
        
        // count each phrase, once for each doc
        vector <char> in_doc(_table.size(), 0);
        for (const string& phrase: phrases) {

            // find element in table, skip if DNE
            auto element = _table.find(phrase);
            if (element == _table.end()) {continue;}

            // get phrase index
            size_t phrase_index = element->second;

            // check if term has already been counted for this doc
            if (in_doc[phrase_index]) {continue;}
            in_doc[phrase_index] = true;

            // increment count
            doc_freq[phrase_index][labels[doc_num]]++;
        }
    }

    // compute phrase weights
    for (size_t phrase_index = 0; phrase_index < _table.size(); phrase_index++) {

        // get overall document frequency
        float overall_doc_freq = maths::sum(doc_freq[phrase_index]);

        // get expected occurrence for each class, if phrases were evenly distributed
        float expected_occurrence = overall_doc_freq / _num_docs;

        // add in contributing term from each class
        for (size_t class_num = 0; class_num < num_classes; class_num++) {
            if (!docs_in_class[class_num]) {continue;}
            float actual_occurrence = doc_freq[phrase_index][class_num] / (float)docs_in_class[class_num];
            float difference_from_expectation = expected_occurrence - actual_occurrence;
            _weights[phrase_index] += pow(difference_from_expectation, 2);
        }

        // take sqrt to make euclidean
        _weights[phrase_index] = sqrt(_weights[phrase_index]);
    }
}

void VHash::_make_features(
    const vector <string>& docs
) {
    // initialize features vector
    _features = vector <Sparse>(maths::min(vector <size_t>{docs.size(), _num_features}));

    // select features
    vector <char> use_doc = manip::rand_select(docs.size(), _features.size());

    // vectorize documents to create features
    for (size_t doc_num = 0, feature_count = 0; doc_num < docs.size(); doc_num++) {
        if (!use_doc[doc_num]) {continue;}
        _features[feature_count++] = 
            _vectorize(docs[doc_num])
            .multiply(_weights, true)
            .normalize()
        ;
    }
}

vector <string> VHash::_break_into_phrases(const string& doc) const {
    vector <string> out;
    for (size_t phrase_len = _smallest_ngram; phrase_len <= _largest_ngram; phrase_len++) {
        vector <string> phrases = text::get_phrases(doc, phrase_len);
        out.insert(out.end(), phrases.begin(), phrases.end());
    }
    return out;
}

void VHash::_remove_infreq(const size_t& thresh) {
    if (!thresh) {return;}
    for (auto it = _table.begin(); it != _table.end();) {
        if ((*it).second < thresh) {
            it = _table.erase(it);
        } else {
            it++;
        }
    }
}

void VHash::_assign_indices() {
    size_t index = 0;
    for (auto it = _table.begin(); it != _table.end(); it++) {
        (*it).second = index++;
    }
}

Sparse VHash::_vectorize(const string& doc) {
    
    // get phases
    vector <string> phrases = _break_into_phrases(doc);

    // get counts of each phrase
    vector <size_t> counts(_table.size(), 0);
    for (const string& phrase: phrases) {
        auto element = _table.find(phrase);
        if (element == _table.end()) {continue;}
        counts[element->second]++;
    }

    // convert to sparse
    Sparse out = Sparse(counts);

    // take log of non-zero entries
    for (float& value: out.values) {
        value = log(1 + value);
    }

    // return
    return out;
}

std::pair <vector <string>, vector <size_t>> VHash::_get_test_data() {
    return std::pair <vector <string>, vector <size_t>>(
        vector <string> {
            "hi, my name is Mike",
            "hi, my name is George",
            "hello, my name is Mike",
        },
        vector <size_t> {0, 1, 0}
    );
}

void VHash::_test_basic_creation() {
    auto data = VHash::_get_test_data();
    VHash vhash = VHash(2).fit(data.first, data.second);
    assert(vhash._table.size() == 13);
    assert(vhash._table.find("hi") != vhash._table.end());
    assert(vhash._table.find("my name") != vhash._table.end());
    assert(vhash._table.find("my name is") == vhash._table.end());
}

void VHash::_test_min_phrase_occurrence() {
    auto data = VHash::_get_test_data();
    VHash vhash = VHash(2, 2).fit(data.first, data.second);
    assert(vhash._table.size() == 9);
    assert(vhash._table.find("george") == vhash._table.end());
    assert(vhash._table.find("is mike") != vhash._table.end());
}

void VHash::_test_assigned_indices() {
    auto data = VHash::_get_test_data();
    VHash vhash = VHash(2, 2).fit(data.first, data.second);
    vector <char> index_assigned(vhash._table.size(), false);
    for (auto it = vhash._table.begin(); it != vhash._table.end(); it++) {
        index_assigned[(*it).second] = true;
    }
    assert((size_t)maths::sum(index_assigned) == index_assigned.size());
}

void VHash::_test_weights() {
    auto data = VHash::_get_test_data();
    VHash vhash = VHash().fit(data.first, data.second);
    assert(maths::isclose(vhash._weights[vhash._table.find("hi")->second], 0.372677996));
    assert(maths::isclose(vhash._weights[vhash._table.find("mike")->second], 0.745355992));
    assert(maths::isclose(vhash._weights[vhash._table.find("name")->second], 0));
}

void VHash::_test_vectorization() {
    
    // make data and train model
    auto data = VHash::_get_test_data();
    VHash vhash = VHash().fit(data.first, data.second);

    // test single word
    Sparse sparse = vhash._vectorize("hi");
    assert(sparse.num_nonzero() == 1);
    assert(maths::isclose(sparse.values[0], log(2)));

    // test repeated word
    sparse = vhash._vectorize("hi hi");
    assert(sparse.num_nonzero() == 1);
    assert(maths::isclose(sparse.values[0], log(3)));
}

void VHash::_test_transform() {

    // make data and train model
    auto data = VHash::_get_test_data();
    VHash vhash = VHash().fit(data.first, data.second);

    // transform docs
    vector <vector <float>> doc_vecs = vhash.transform(data.first);

    // assert
    assert(doc_vecs.size() == 3);
    assert(doc_vecs[0].size() == 3);
    assert(maths::isclose(doc_vecs[0][0], 1));
    assert(maths::isclose(doc_vecs[1][1], 1));
    assert(maths::isclose(doc_vecs[2][2], 1));
    assert(doc_vecs[0][2] > doc_vecs[0][1]);
    assert(doc_vecs[2][0] > doc_vecs[2][1]);
}

void VHash::_test_null() {
    auto data = VHash::_get_test_data();
    data.first[1] = "";
    VHash vhash = VHash().fit(data.first, data.second);
    data.first[1] = VHash::_get_test_data().first[1];
    vhash.transform(data.first);
    data.first[1] = "";
    vhash.transform(data.first);
}
