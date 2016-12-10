#include <stdio.h>
#include "Perceptron.h"
#include "Data.h"
#include <vector>

#include <iostream>
#include <Math.h>

using namespace std;
using namespace DataEntries;

namespace Perceptron {
    
    float getSum (Data& d) {
        
        // Collects the sum of the product
        // of the weights and values of each attribute
        float tot = 0;
        tot += d.getPop()*popW;
        tot += d.getPopChange()*popCW;
        tot += d.getAgeSFP()*aSFPW;
        tot += d.getBlack()*bW;
        tot += d.getHispanic()*hW;
        tot += d.getEBach()*eBW;
        tot += d.getIncome()*iW;
        tot += d.getPoverty()*pW;
        tot += d.getDensity()*dW;
        
        return tot;
    }
    
    void changeWeights (Data&d, float val, float diff) {
        
        // Modifies the weight according to a specific converging value
        // and difference from wanted value
        popW += val*popW*diff;
        popCW += val*popCW*diff;
        aSFPW += val*aSFPW*diff;
        bW += val*bW*diff;
        hW += val*hW*diff;
        eBW += val*eBW*diff;
        iW += val*iW*diff;
        pW += val*pW*diff;
        dW += val*dW*diff;
    }
    
    void checkWeights (vector<Data*>& set) {
        for (int j = 0; j < 5; j++){
            float weightModifier = 0.1;
            for (int i = 0; i < set.size(); i++) {
                // Finds the weighted sum of the attributes
                // of a sample data
                float sum = getSum(*set[i]);
                // Determines the difference between the weighted sum
                // And actual value
                float diff = set[i]->getDem() - sum;
                // Modify the weights if the difference is off
                if (diff != 0) changeWeights(*set[i], weightModifier, diff);
            }
            weightModifier*=0.1f;
        }
    }
    
    // Checks to see the value given by the perceptron
    int checkDem (Data& d) {
        float sum = getSum(d);
        // Returns the rounded value
        // Rounded value will be either 1 or 0
        // Corresponding to Democrat and Republican respectively
        return round(sum);
    }
    
}


