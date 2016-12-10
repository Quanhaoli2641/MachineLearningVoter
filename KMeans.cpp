#include <stdio.h>
#include "Kmeans.h"
#include <fstream>
#include <string>
#include <iostream>
#include "Silhouette.h"
#include <math.h>

using namespace Silhouette;
using namespace std;

namespace KMeans {
    
    // Fills a vector of unlabeled data given a file
    void fillVector (vector<vector<float>>& v, ifstream& file, string& delimiter) {
        if (!file) return;
        
        // Initialization of variables
        vector<float> insideV;
        size_t pos = 0;
        string line;
        float val = 0;
        
        // While there are lines to be read from the file
        while (getline(file, line)) {
            // Clear the dataset to be used for the line read
            // from the file
            insideV.clear();
            // While can still find sub strings
            // separated by a delimiter
            while ((pos = line.find(delimiter)) != string::npos) {
                // Stores the value of the substring as a float
                val = stof(line.substr(0, pos));
                // Erase that substring along with the found delimiter from the line
                line.erase(0, pos + delimiter.size());
                // Stores the value of the float inside the vector
                insideV.push_back(val);
            }
            // The last element is not stored because
            // the while loop broke since no more
            // delimiters could be found
            // so store last element
            val = stof(line.substr(0, line.size()));
            insideV.push_back(val);
            // Store the data set inside another vector
            v.push_back(insideV);
        }
        
    }
    
    
    // Modifies the two clusters to append certain data sets
    void modify (vector<vector<float>>& dem, vector<vector<float>>& rep, int which, vector<float>& data) {
        // If needing to append to the first cluster
        // but that cluster already contains that data
        // dont append
        if (which == 1 && find(dem.begin(), dem.end(), data) != dem.end()) {
            return;
        }
        // Same logic but for second cluster
        if (which == 2 && find(rep.begin(), rep.end(), data) != rep.end()) {
            return;
        }
        // Want to append to first cluster when
        // data not yet found in cluster
        if (which == 1) {
            // Check if data is in the other cluster
            auto i = find(rep.begin(), rep.end(), data);
            if (i != rep.end()) {
                // If so, delete the data
                rep.erase(i);
            }
            // Adds the data to the correct cluster
            dem.push_back(data);
            return;
        }
        // Same logic but for second cluster
        else {
            auto i = find(dem.begin(), dem.end(), data);
            if (i != dem.end()) {
                dem.erase(i);
            }
            rep.push_back(data);
            return;
        }
    }
    
    // Recalculates the centers of the clusters
    unsigned long redefineCenter (vector<vector<float>> set, unsigned long center) {
        
        // Dataset to hold the ideal mean dataset
        vector<float> meanSet;
        meanSet.clear();
        
        // Initializes the mean dataset with empty values
        for (int k = 0; k < set[set.size()-1].size(); k++) {
            meanSet.push_back(0);
        }
        
        // Calculates the mean values from the cluster
        for (int i = 0; i < set.size(); i++) {
            for (int j = 0; j < set[i].size(); j++) {
                meanSet[j] += set[i][j];
            }
        }
        for (int l = 0; l < meanSet.size(); l++) {
            meanSet[l] /= set.size();
        }
        
        // Since the ideal mean dataset probably doesn't exist
        // Find the closest mean dataset
        // By comparing Euclidean distances of each dataset in cluster
        float min = MAXFLOAT;
        for (int m = 0; m < set.size(); m++) {
            float dist = getDistance(meanSet, set[m]);
            // Modifies the center if a lower value is found
            if (dist < min) {
                min = dist;
                center = m;
            }
        }
        return center;
    }
    
    // Generates the clusters
    // This specific design only generates 2 clusters
    void getClusters (vector<vector<vector<float>>>& clusters, vector<vector<float>>& data, unsigned long center1, unsigned long center2,
                      vector<vector<float>>& demCluster, vector<vector<float>>& repCluster) {
        
        // No data to generate clusters with
        if (data.empty()) return;
        clusters.clear();
        
        //int filling = 1;
        bool changed = true;
        
        demCluster.clear();
        repCluster.clear();
        
        
        // Loop until no more changes for the centers of the clusters are made
        while (changed) {
            
            for (int i = 0; i < data.size(); i++) {
                // calculates the distance a dataset is from both centers
                float dist1 = getDistance(data[i], data[center1]);
                float dist2 = getDistance(data[i], data[center2]);
                // chooses smallest and adds dataset to appropriate cluster
                int which = 0;
                if (dist1 < dist2) which = 1;
                else if (dist1 > dist2) which = 2;
                if (which != 0) modify(demCluster, repCluster, which, data[i]);
            }
            
            // recalculated centers
            unsigned long newCenter1 = redefineCenter(demCluster, center1);
            unsigned long newCenter2 = redefineCenter(repCluster, center2);
            
            // Since the recalculated centers are generated from the smaller clusters
            // they need to readjusted so their values match the giant data structure
            // holding both clusters and all the information
            auto i = find(data.begin(), data.end(), demCluster[newCenter1]);
            unsigned long center01 = i - data.begin();
            
            auto j = find(data.begin(), data.end(), repCluster[newCenter2]);
            unsigned long center02 = j - data.begin();
            
            // If the centers have not changed, break the loop
            if (center1 == center01 && center2 == center02) changed = false;
            else {
                // Otherwise reassign centers
                center1 = center01;
                center2 = center02;
            }
            
        }
        // Store clusters in a larger data structure
        clusters.push_back(demCluster);
        clusters.push_back(repCluster);
        
    }
    
}
