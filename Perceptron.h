#ifndef Perceptron_h
#define Perceptron_h

#include "Data.h"


namespace Perceptron {
    
    // Semi-random initial values for the weights
    static float popW = 0.000001f;
    static float popCW = 0.1f;
    static float aSFPW = 0.1f;
    static float bW = 1.0f;
    static float hW = 1.0f;
    static float eBW = 0.01f;
    static float iW = 0.000001f;
    static float pW = 0.1f;
    static float dW = 0.01f;
    
    float getSum (DataEntries::Data&);
    void changeWeights (DataEntries::Data&, float, float);
    void checkWeights (std::vector<DataEntries::Data*>&);
    int checkDem (DataEntries::Data&);
}


#endif /* Perceptron_h */
