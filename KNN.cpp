#include <stdio.h>
#include <string>
#include <random>
#include <math.h>
#include "KNN.h"
#include "Data.h"
#include <iostream>

using namespace std;
using namespace DataEntries;


// Calculates the Euclidean distance between two data entries

namespace KNN {

    float getDistance (Data& trainingOne, Data& trainingTwo) {
        
        float dist = 0;
        
        // sum of difference of squares
        dist += pow(trainingOne.getPop() - trainingTwo.getPop(),2);
        dist += pow(trainingOne.getPopChange() - trainingTwo.getPopChange(),2);
        dist += pow(trainingOne.getAgeSFP() - trainingTwo.getAgeSFP(),2);
        dist += pow(trainingOne.getBlack() - trainingTwo.getBlack(),2);
        dist += pow(trainingOne.getHispanic() - trainingTwo.getHispanic(),2);
        dist += pow(trainingOne.getEBach() - trainingTwo.getEBach(),2);
        dist += pow(trainingOne.getIncome() - trainingTwo.getIncome(),2);
        dist += pow(trainingOne.getPoverty() - trainingTwo.getPoverty(),2);
        dist += pow(trainingOne.getDensity() - trainingTwo.getDensity(),2);
        
        // returns square root
        return sqrtf(dist);
        
    }
    
    // Comparator function
    bool checker (pair<Data*,float>& dataOne, pair<Data*,float>& dataTwo) {
        return dataOne.second < dataTwo.second;
    }
    
    // Finds x closest neighbors
    vector<Data*> getNeighbors (vector<Data*>& trainingSet, Data& testInstance, int range) {
        vector<pair<Data*,float>> v{};
        // for every data entry
        for (int i = 0; i < trainingSet.size(); i++) {
            // calculate the Euclidean distance
            float dist = KNN::getDistance(testInstance, *trainingSet[i]);
            pair<Data*, float> p;
            p.first = trainingSet[i];
            p.second = dist;
            // store it in a vector
            v.push_back(p);
        }
        // sort the vector
        sort(v.begin(), v.end(), KNN::checker);
        vector<Data*> ret;
        // appends the x closest neighbors to a new vector and returns
        for (int j = 0; j < range; j++) {
            ret.push_back(v[j].first);
        }
        return ret;
    }
    
    // Determine if a county might vote republic or democrat
    bool getResponse (vector<Data*>& d) {
        int num = 0;
        // loops through neighbors
        for (int i = 0; i<d.size();i++) {
            // check if neighbors are republican or democrat
            if (d[i]->getDem() == 1) {
                num+=1;
            }
            else num-=1;
        }
        // return republican or democrat
        return num > 0;
        
    }
}









