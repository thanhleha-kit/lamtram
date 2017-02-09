#pragma once

#include <lamtram/sentence.h>
#include <lamtram/linear-encoder.h>
#include <lamtram/ll-stats.h>
#include <lamtram/builder-factory.h>
#include <lamtram/multitask-model.h>
#include <dynet/dynet.h>
#include <dynet/expr.h>
#include <vector>
#include <iostream>

namespace dynet {
class Model;
struct ComputationGraph;
struct LookupParameter;
struct RNNBuilder;
}

namespace lamtram {

// A class for feed-forward neural network LMs
class SharedWordEmbeddingMultiTaskLinearEncoder : public LinearEncoder , public MultiTaskModel{
    friend class EncoderAttentional;

public:

    // Create a new SharedWordEmbeddingMultiTaskLinearEncoder and add it to the existing model
    SharedWordEmbeddingMultiTaskLinearEncoder(const std::vector<int> & vocab_size, int wordrep_size,
             const BuilderSpec & hidden_spec, int unk_id,
             dynet::Model & model);
    ~SharedWordEmbeddingMultiTaskLinearEncoder() { }


    // Reading/writing functions
    static SharedWordEmbeddingMultiTaskLinearEncoder* Read(std::istream & in, dynet::Model & model);
    virtual void Write(std::ostream & out);

    static std::string ModelID() { return "sharedwordembeddingmultitasklinearencoder"; }

    // Accessors
    int GetVocabSize() const { std::cerr << "Get VocabSize not supported for multi-task" << std::endl; exit(-1); }
    
    void SetVocabulary(int sourceIndex, int targetIndex) {current_voc_ = sourceIndex; builder_ = builders_[current_voc_];};

    virtual void SetDropout(float dropout);

protected:

    int vocab_size_;

    // Pointers to the parameters
    dynet::LookupParameter ps_wr_W_; // Wordrep weights

    int current_voc_;

    // The RNN builder
    std::vector<BuilderPtr> builders_;


};

typedef std::shared_ptr<SharedWordEmbeddingMultiTaskLinearEncoder> SharedWordEmbeddingMultiTaskLinearEncoderPtr;

}