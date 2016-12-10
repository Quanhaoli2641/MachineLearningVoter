#include <stdio.h>
#include <math.h>
#include "AGNES.h"
#include <iostream>
#include "Silhouette.h"

using namespace std;
using namespace Silhouette;

namespace AGNES {
    
    UnsupervisedNode* UnsupervisedNode::getChild1 (){return child1;}
    UnsupervisedNode* UnsupervisedNode::getChild2 (){return child2;}
    void UnsupervisedNode::modChild1 (UnsupervisedNode* n){child1 = n;}
    void UnsupervisedNode::modChild2 (UnsupervisedNode* n){child2 = n;}
    
    // Initializes the Distance matrix with values
    void initializeDistMatrix (vector<vector<float>>& distMatrix, vector<vector<float>>& unlabeledData) {
        
        // For every data set in the data set holder
        // Or in another perspective: generate the rows of the matrices
        for (int k = 0; k < unlabeledData.size(); k++) {
            vector<float> inV;
            inV.clear();
            // and generate the columns of the matrices
            for (int l = 0; l < unlabeledData.size(); l++) {
                inV.push_back(0);
            }
            distMatrix.push_back(inV);
        }
        
        // For every row
        for (int i = 0; i < unlabeledData.size(); i++) {
            // and every column
            for (int j = 0; j < unlabeledData.size(); j++) {
                // Gets the Euclidean distance between two data sets
                distMatrix[i][j] = getDistance(unlabeledData[i], unlabeledData[j]);
            }
        }
    }
    
    // Initializes the vector of unsupervised node clusters
    // with values obtained from a file
    void initializeNodesVector (vector<UnsupervisedNode*>& vNodes, vector<vector<float>>& unlabeledData) {
        // For every value in the vector of datasets
        for (int i = 0; i < unlabeledData.size(); i++) {
            // create a Node pointer pointing to a Unsupervised Node with the data set
            UnsupervisedNode* n = new UnsupervisedNode (unlabeledData[i]);
            // and add it to the vector of unsupervised node clusters
            vNodes.push_back(n);
        }
    }
    
    // Finds the smallest distance between two datasets
    // inside the distance matrix
    pair<int, int> findMinDistCluster (vector<vector<float>>& distMatrix) {
        // initialize a minimum value with the largest float value
        float min = MAXFLOAT;
        pair<int, int> indices (0,0);
        // look at every row
        for (int i = 0; i < distMatrix.size(); i++) {
            // look at every column
            for (int j = 0; j < distMatrix.size(); j++) {
                // if the indices arent the same
                // because if they were, it would just return itself
                if (i != j) {
                    // if the distance is smaller than the minimum
                    if (distMatrix[i][j] < min) {
                        // reassign value
                        min = distMatrix[i][j];
                        // save the indices
                        indices.first = i;
                        indices.second = j;
                    }
                }
            }
        }
        // return the indices
        return indices;
    }
    
    // Modify the matrix to update its values
    void modMatrix (vector<vector<float>>& distMatrix, int index1, int index2) {
        
        // Since a new cluster will be created, it's closest distance must be updated
        // Luckily since it's members already have distances
        // Find the smallest distance from one of its members to other clusters
        // And use that value as the minimum distance
        for (int i = 0; i < distMatrix.size(); i++) {
            // Compares the smaller of the two values and saves the smaller of the two
            // at the end of the matrix row
            if (distMatrix[i][index1] > distMatrix[i][index2]) {
                distMatrix[i].push_back(distMatrix[i][index2]);
            }
            else {
                distMatrix[i].push_back(distMatrix[i][index1]);
            }
            // Remove the two data values from every row
            // Or the column of these two data sets
            distMatrix[i].erase(distMatrix[i].begin()+index1);
            distMatrix[i].erase(distMatrix[i].begin()+index2-1);
        }
        // Remove the rows of these two data sets
        distMatrix.erase(distMatrix.begin()+index1);
        if (index2 > index1) distMatrix.erase(distMatrix.begin()+index2-1);
        else distMatrix.erase(distMatrix.begin()+index2);
        vector<float> newRow;
        newRow.clear();
        // Insert a new row into the matrix holding it's smallest distance values
        // to other clusters
        for (int j = 0; j < distMatrix.size(); j++) {
            newRow.push_back(distMatrix[j][distMatrix.size()-1]);
        }
        newRow.push_back(0);
        distMatrix.push_back(newRow);
        
    }
    
    
    // Update the vector of clusters
    void modVNodes (vector<UnsupervisedNode*>& vNodes, int index1, int index2) {
        // Create a new cluster
        UnsupervisedNode* n = new UnsupervisedNode();
        // that holds the previous clusters
        n->modChild1(vNodes[index1]);
        n->modChild2(vNodes[index2]);
        // Remove the clusters from the vector of clusters
        vNodes.erase(vNodes.begin()+index1);
        if (index2 > index1) vNodes.erase(vNodes.begin()+index2-1);
        else vNodes.erase(vNodes.begin()+index2);
        // and put the new cluster in the vector of clusters
        vNodes.push_back(n);
    }
    
    // Generate the unsupervised tree for the agglomerate nesting cluster
    UnsupervisedNode* genTree (vector<vector<float>>& distMatrix, vector<UnsupervisedNode*>& nodes) {
        // Return a stump if there is nothing to create with
        if (nodes.size() == 0 || distMatrix.size() == 0) return nullptr;
        // Until there is only one giant cluster
        while (nodes.size() > 1) {
            cout << "Number of current clusters: " << nodes.size() << ", still processing..." << endl;
            // Find the smallest distance pair
            pair<int,int> t = findMinDistCluster(distMatrix);
            // Combine the two clusters into one
            modVNodes(nodes, t.first, t.second);
            // and fix the distance matrix to reflect this combination
            modMatrix(distMatrix, t.first, t.second);
        }
        
        // Return the head of the tree
        return nodes[0];
    }
    
    
}
