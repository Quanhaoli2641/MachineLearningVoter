#include <stdio.h>
#include "Silhouette.h"
#include <iostream>
#include <math.h>

using namespace std;

namespace Silhouette {
    
    // Determines the similarity of a dataset to a cluster of datasets
    float getSimilarity (vector<float> data, vector<vector<float>> currCluster) {
        float value = 0;
        
        // Evaluates the distance between a instance of a dataset with
        // the entirety of a cluster of data sets
        for (int i = 0; i < currCluster.size(); i++) {
            value += getDistance(data, currCluster[i]);
        }
        
        return value;
    }
    
    // Calculates the silhouette value for one instance of a data set
    float getSilhouetteVal (vector<float> data, vector<vector<vector<float>>> clusters, int indexOfCluster, int indexOfOther) {
        
        // a(i) - instance's average similarity to all other points
        // in it's cluster
        float simValThisCluster = getSimilarity(data, clusters[indexOfCluster]) / clusters[indexOfCluster].size();
        
        // b(i) - instance's similarity to all other points
        // in all other clusters
        // In this specific design
        // only 2 clusters were generated
        float simValOtherCluster = getSimilarity(data, clusters[indexOfOther]);
        
        // Difference of a(i) and b(i)
        float dif = simValOtherCluster - simValThisCluster;
        
        // Silhouette value -> difference divided by the max of the two values
        dif /= max(simValThisCluster, simValOtherCluster);
        return dif;
        
    }
    
    // Calculates the average silhouette value for a cluster
    float getAvgSilVal (vector<vector<vector<float>>> clusters, int indexOfCluster, int indexOfOther) {
        
        float avg = 0;
        
        // Looks at every data set in cluster
        // Generates the corresponding Silhouette values
        // and finds the average
        for (int i = 0; i<clusters[indexOfCluster].size(); i++) {
            avg += getSilhouetteVal(clusters[indexOfCluster][i], clusters, indexOfCluster, indexOfOther);
        }
        
        avg /= float(clusters[indexOfCluster].size());
        
        return avg;
    }
    
    // Determines the Euclidean distance between two datasets
    float getDistance (vector<float>& v, vector<float>& v2) {
        if (v.empty()) return 0;
        if (v2.empty()) return 0;
        
        float dif = 0;
        
        // Finds the sum of the differences squared
        for (int i =0; i < v.size(); i++) {
            dif += powf(float(v[i]) -float(v2[i]), 2);
        }
        
        // Returns the square root of sum
        return sqrtf(dif);
    }
    
}
