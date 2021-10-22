#ifndef VHASH_VHASH_H
#define VHASH_VHASH_H

#include <unordered_map>
#include <string>
#include <vector>

#include <utils/sparse.h>

using std::unordered_map;
using std::string;
using std::vector;


namespace vhash {

    /* Hash table for vector quantization of text documents

    This class supplies custom-trained hash tables that perform fast vector
    quantization of your documents. To train this class, you must provide it
    with documents and with a single class label for each document.

    This class differs from many commonly-used methods and packages (e.g. BERT,
    BOW, TFIDF) in that it learns its representation from your class labels,
    instead of using some generalized scheme that is not specific to the task
    at hand.

    To compute a phrase's weight

    #. Compute the phrase's document frequency. A phrase's document frequency
       is the number of documents it appears in in the training set.

    #. Compute the phrase's expected document frequency, if it were evenly
       distributed among all classes. E.g. if a phrase appears in 82% of
       documents, we'd expect that phrase to occur in 82% of the documents
       belonging to each class, if that phrase were evenly distributed.
    
    #. Compute the actual document frequency of each class. E.g. a term might
       occur in 20% of the documents from one class, and 90% of the documents from
       another class.

    #. Compute each phrase's weight as:

           `\sqrt( \sum_c( |expected_freq_c - actual_freq_c|^2 ) )`
    
       where `sum_c` is the sum over each class, `expected_freq_c` is the
       expected frequency for class `c`, and `actual_freq_c` is the actual
       frequency for class `c`.

    To vectorize a document, the following procedure is followed:

    #. Each phrase in the document that exists in the hash table is counted.
       This creates a sparse integer array, where each index in the array
       corresponds to a single phrase.

    #. The count of each phrase is transformed via

           `count -> log(1 + count) `

       This creates a sparse floating-point array.
    
    #. Each phrase is multiplied by its weight. This modifies the existing
       sparse floating-point array.

    #. This sparse floating-point array is L2 normalized.

    #. Sparse arrays are then transformed into information-rich dense arrays
       by comparing them with previously-saved features.

       Features are simply documents that were used during fitting, and are
       saved by the model. These documents are converted into sparse arrays
       following the procedure listed above.

       The resulting dense array is a 1 x `num_features` array, where each
       entry is computed as

           `dense[feature_num] = sparse_array * feature[feature_num]`

    This process thus creates information-rich dense representations of text
    documents, learning heavily from the training data.
     */
    class VHash {
        public:

            /* Hash table for vector quantization of text documents

            Parameters
            ----------
            largest_ngram: const size_t&
                max # of words to take as a single phrase
            min_phrase_occurrence: const float&
                if min_phrase_occurrence < 1:
                    remove from table iff count < min_phrase_occurrence * docs.size()
                else:
                    remove from table iff count < min_phrase_occurrence
            num_features: const size_t&
                # of features to compute ( == dimension of each dense vector)
            max_num_phrases: const size_t&
                largest allowed size for any vhash table (0 -> off)
            downsample_to: const size_t&
                max # to keep when constructing (random downsample) (-1 -> off)
            live_evaluation_step: const size_t&
                remove infreq elements, if max_num_phrases reached, every X documents
             */
            VHash(
                const size_t& largest_ngram = 3,
                const float&  min_phrase_occurrence = 1E-3,
                const size_t& num_features = 1000,
                const size_t& max_num_phrases = 1E6,
                const size_t& downsample_to = 100E3,
                const size_t& live_evaluation_step = 10E3
            );

            /* virtual destructor */
            virtual ~VHash() {}

            /* Train model

            Parameters
            ----------
            docs: const vector <string>&
                documents to use to train model
            labels: const vector <size_t>&
                class label for each document.
                Assumes that classes are numbered sequentially, starting at zero.
            
            Returns
            -------
            VHash
                Calling object
             */
            VHash fit(
                const vector <string>& docs,
                const vector <size_t>& labels
            );

            /* Fit model, transform docs 

            Parameters
            ----------
            docs: const vector <string>&
                documents to use to train model, then to transform
            labels: const vector <size_t>&
                class label for each document
                Assumes that classes are numbered sequentially, starting at zero.

            Returns
            -------
            vector <vector <float>> rep
                Numeric representation of documents
                rep[x] is for docs[x]
                rep[x].size() == num_features (set in constructor)
             */
           vector <vector <float>> fit_transform(
                const vector <string>& docs,
                const vector <size_t>& labels
            );

            /* Transform docs, using fitted model

            Parameters
            ----------
            docs: const vector <string>&
                documents to transform

            Returns
            -------
            vector <vector <float>> rep
                Numeric representation of documents
                rep[x] is for docs[x]
                rep[x].size() == num_features (set in constructor)
             */
            vector <vector <float>> transform(
                const vector <string>& docs
            );

            /* public access to testing private methods */
            static void _test();

        private:

            // ===============================================================
            // construction parameters

            size_t _largest_ngram;
            float  _min_phrase_occurrence;
            size_t _num_features;
            size_t _max_num_phrases;
            size_t _downsample_to;
            size_t _live_evaluation_step;

            // ===============================================================
            // fitting helper variables

            // number of documents used for fitting
            size_t _num_docs;

            // ===============================================================
            // data members

            // actual hash table
            unordered_map <string, size_t> _table;

            // features for comparison when making dense reps
            vector <utils::Sparse> _features;

            // weight of each term, for vectorizing
            vector <float> _weights;

            // ===============================================================
            // fitting functions

            // insert terms into hash table
            void _create_table(
                const vector <string>& docs,
                const vector <char>& insert_me
            );
            
            // compute weight of each term
            void _compute_weights(
                const vector <string>& docs,
                const vector <size_t>& labels,
                const vector <char>& insert_me
            );

            // make features, used in dense vectorization
            void _make_features(
                const vector <string>& docs
            );

            // ===============================================================
            // text preprocessing

            // break document into vector of phrases
            vector <string> _break_into_phrases(const string& doc) const; // document -> vector of phrases

            // ===============================================================
            // table modification

            // remove infrequent terms from table
            void _remove_infreq(const size_t& thresh);

            // assign each term in table a sequential index
            void _assign_indices();

            // ===============================================================
            // vectorization

            utils::Sparse _vectorize(const string& doc);

            // ===============================================================
            // tests

            static std::pair <vector <string>, vector <size_t>> _get_test_data();
            static void _test_basic_creation();
            static void _test_min_phrase_occurrence();
            static void _test_assigned_indices();
            static void _test_weights();
            static void _test_vectorization();
            static void _test_transform();
    };
}
#endif
