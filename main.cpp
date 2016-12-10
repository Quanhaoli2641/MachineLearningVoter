#include <iostream>
#include <math.h>
#include "KNN.h"
#include "Data.h"
#include "Perceptron.h"
#include "DTree.h"
#include "KMeans.h"
#include "Silhouette.h"
#include "AGNES.h"


using namespace DataEntries;
using namespace KNN;
using namespace Perceptron;
using namespace Dtree;
using namespace KMeans;
using namespace Silhouette;
using namespace AGNES;
using namespace std;

// Runs a menu asking for which algorithm to run
int menu () {
    
    string answer;
    cout << "Which algorithm would you like to run?" << endl;
    cout << "1. K Nearest Neighbor" << endl;
    cout << "2. Perceptron" << endl;
    cout << "3. ID3 Decision Tree" << endl;
    cout << "4. K Means" << endl;
    cout << "5. Agglomerative Nesting" << endl;
    cout << "Please only input a single number choice." << endl;
    
    cin >> answer;
    
    // If the answer given is too large or it's ASCII value is not 49 (1) or 50 (2) or 51 (3) or 52 (4) or 53(4)
    // restart the menu
    if (answer.size() > 1 || ((unsigned int)answer[0] != 49 && (unsigned int)answer[0] != 50 && (unsigned int)answer[0] != 51 && (unsigned int)answer[0] != 52 && (unsigned int)answer[0] != 53)) {
        cout << "That is not a valid input, please try again.";
        menu();
    }
    
    // Otherwise return the input
    return (unsigned int) answer[0];
    
}

// Prints the contents of a Unsupervised Node tree
// created in the process of generating the
// Agglomerate Nesting Cluster
void printTree (UnsupervisedNode* n, int depth) {
    // Ends the function if the node is null
    if (!n) return;
    // Prints out Democrat or Republican as well as the current depth
    cout << "At current depth: " << depth;
    if(n->values.size() > 0) {
        if (n->values[0] == 1) cout << ", " << "Democrat!";
        else cout << ", " << "Republican";
    }
    cout << endl;
    // If there are no values in the vector
    // then that means this a branch holding another sub tree
    // Make a recursive call on that sub tree
    if (n->values.size() == 0) {
        printTree(n->getChild1(), depth+1);
        printTree(n->getChild2(), depth+1);
    }
    
}

int main(int argc, const char * argv[]) {
    
    
    vector<string> att;
    // Initialize the static vector of strings
    // To know the proper indices for different attributes/ labels
    att.push_back("dem");
    att.push_back("pop");
    att.push_back("popC");
    att.push_back("ageSFP");
    att.push_back("black");
    att.push_back("hispanic");
    att.push_back("eBach");
    att.push_back("income");
    att.push_back("poverty");
    att.push_back("density");
    
    vector<Data*> trainingSet;
    vector<Data*> testingSet;
    vector<Data*> nearestNeighbors;
    
    // Gets user input
    int choice = menu();
    
    // opens file and checks if it can be found/ exists
    ifstream trainingInfo ("/votes-train.csv");
    if (!trainingInfo) {
        cerr << "Could not find votes-train.csv" << endl;
        exit(-1);
    }
    
    // read the first line of the file
    // pointer is now at the second line
    // because that is where the data values begin
    
    string s;
    getline(trainingInfo,s);
    
    // Fill the trainingSet
    fillSets(trainingInfo, trainingSet);
    
    // opens file and checks if it can be found/ exists
    ifstream testingInfo ("/votes-train.csv");
    if (!testingInfo) {
        cerr << "Could not find votes-test.csv" << endl;
        exit(-1);
    }
    
    // read the first line of the file
    // pointer is now at the second line
    // because that is where the data values begin
    
    getline(testingInfo,s);
    
    // Fill the testingSet
    fillSets(testingInfo, testingSet);
    
    int count;
    
    // ----------------------------------------------------------------------------------------------------
    // ----------------------------------------------------------------------------------------------------
    // K Nearest Neighbor
    // ----------------------------------------------------------------------------------------------------
    // ----------------------------------------------------------------------------------------------------
    // ASCII value for 1
    if (choice == 49) {
        count = 0;
        cout << " ------ K Nearest Neighbor ------ " << endl;
        // Prints out the guess and the actual vote
        for (int i = 0; i < testingSet.size() ; i++) {
            Data* test = testingSet[i];
            // Gets nearest neighbors of a specific sample
            // in the testing set
            nearestNeighbors = getNeighbors(trainingSet, *test, 10);
            // Collect the information to generate a response
            bool democrat = getResponse(nearestNeighbors);
            
            // Prints out the guess vote
            cout << "Guess: ";
            if (democrat) cout << "Democrat!";
            else cout << "Republican!";
            
            // Print out the actual vote
            cout << ", Actual: ";
            if (testingSet[i]->getDem() == 0) cout << "Republican!";
            else cout << "Democrat!";
            cout << endl;
            
            if ((democrat && testingSet[i]->getDem() == 1) || (!democrat && testingSet[i]->getDem() == 0)) {
                // increment the counter whenever there is a match
                // to check for percentage
                count++;
            }
        }
        
        // Prints out the percentage correct
        cout << "Percentage: " << float(count)/float(testingSet.size()) << endl;
    }
    
    
    // ----------------------------------------------------------------------------------------------------
    // ----------------------------------------------------------------------------------------------------
    // Perceptron
    // ----------------------------------------------------------------------------------------------------
    // ----------------------------------------------------------------------------------------------------
    // ASCII value for 2
    if (choice == 50) {
        count = 0;
        cout << " -------- Perceptron -------- " << endl;
        
        // Modify the weights of each attribute to a specific sample
        // from the testing set
        checkWeights(trainingSet);
        for (int j = 0; j<testingSet.size(); j++) {
            
            bool pDemocrat;
            
            // Determine the guess vote status
            int num = checkDem(*testingSet[j]);
            if (num == 0) pDemocrat = false;
            else pDemocrat = true;
            
            // Prints the guess vote
            cout << "Guess: ";
            if (!pDemocrat) cout << "Republican!";
            else cout << "Democrat!";
            
            // Prints the Actual vote
            cout << ", Actual: ";
            if (testingSet[j]->getDem() == 0) cout << "Republican!";
            else cout << "Democrat!";
            cout << endl;
            
            if ((pDemocrat && testingSet[j]->getDem() == 1) || (!pDemocrat && testingSet[j]->getDem() == 0)) {
                // increment the counter whenever there is a match
                // to check for percentage
                count++;
            }
            
        }
        
        // Prints out the percentage correct
        cout << "Percentage: " << float(count) / float (testingSet.size()) << endl;
    }
    
    // ----------------------------------------------------------------------------------------------------
    // ----------------------------------------------------------------------------------------------------
    // ID3 Decision Tree
    // ----------------------------------------------------------------------------------------------------
    // ----------------------------------------------------------------------------------------------------
    // ASCII value for 3
    if (choice == 51) {
        count = 0;
        cout << " ------ ID3 Decision Tree ------" << endl;
        
        // Calculates the Info percentage
        // for the total training set
        float dems = 0;
        for (int i = 0; i < trainingSet.size(); i++) {
            // Checks to see if the sample data votes democratic
            if (trainingSet[i]->getDem() == 1) dems++;
        }
        // The actual calculation for the info
        // -Dem/Total * log2(Dem/Total) and -Rep/Total * log2(Rep/Total)
        float firstPart = -1*(dems/float(trainingSet.size()))*log2f(dems/float(trainingSet.size()));
        float secondPart = -1*(float(trainingSet.size() - dems)/float(trainingSet.size()))*log2f(float(trainingSet.size() - dems)/float(trainingSet.size()));
        float info = firstPart - secondPart;
        
        // A copied vector of the strings initialized in the beginning
        // To keep track of the attributes already looked at
        vector<string> s = *new vector<string> (att);
        
        // Generate the tree
        Node* n = genTree(trainingSet, s, info, att);
        
        // Looks through the testing set
        for  (int j = 0; j < testingSet.size(); j++) {
            
            // Generates the vote for a sample data set
            int vote = parseTree(n, testingSet[j], att);
            
            // Prints out the guess vote
            cout << "Guess: ";
            if (vote == 0) cout << "Republican!";
            else cout << "Democrat!";
            
            // Prints out the actual vote
            cout << ", Actual: ";
            if (testingSet[j]->getDem() == 0) cout << "Republican!";
            else cout << "Democrat!";
            cout << endl;
            
            if ((vote == 0 && testingSet[j]->getDem() == 0) || (vote == 1 && testingSet[j]->getDem() == 1)) {
                // increment the counter whenever there is a match
                // to check for percentage
                count++;
            }
        }
        // Prints out the percentage correct
        cout << "Percentage: " << float(count) / float (testingSet.size()) << endl;

    }
    
    // ----------------------------------------------------------------------------------------------------
    // ----------------------------------------------------------------------------------------------------
    // K Means
    // ----------------------------------------------------------------------------------------------------
    // ----------------------------------------------------------------------------------------------------
    // ASCII value for 4
    if (choice == 52) {
        cout << "-------- K Means --------" << endl;
        
        // Initialize data sets to contain the clusters
        vector<vector<vector<float>>> clusters;
        vector<vector<float>> unLabeledData;
        vector<vector<float>> demCluster;
        vector<vector<float>> repCluster;
        
        // reset the file pointer in the trainingInfo file
        trainingInfo.clear();
        trainingInfo.seekg(0, ios::beg);
        getline(trainingInfo, s);
        
        // Initialize the delimiter
        string delimiter = ",";
        // Stores the unlabeled data presented in the file
        fillVector(unLabeledData, trainingInfo, delimiter);
        
        // Defines two random cluster points
        int indexOne = rand()%unLabeledData.size();
        int indexTwo = rand()%unLabeledData.size();
        while (indexOne == indexTwo) indexTwo = rand()%unLabeledData.size();
        
        // Generates the clusters
        getClusters(clusters, unLabeledData, indexOne, indexTwo, demCluster, repCluster);
        
        // Prints out the average Silhouette values for each cluster
        cout << "Silhouette value for demCluster: " << getAvgSilVal(clusters, 0, 1)<< endl;
        cout << "Silhouette value for repCluster: " << getAvgSilVal(clusters, 1, 0) << endl;
    }
    
    // ----------------------------------------------------------------------------------------------------
    // ----------------------------------------------------------------------------------------------------
    // AGNES
    // ----------------------------------------------------------------------------------------------------
    // ----------------------------------------------------------------------------------------------------
    // ASCII value for 5
    if (choice == 53) {
        cout << "-------- Agglomerative Nesting --------" << endl;
        
        vector<vector<float>> unLabeledData;
        vector<vector<float>> distMatrix;
        vector<UnsupervisedNode*> vNodes;
        
        // reset the file pointer in the trainingInfo file
        trainingInfo.clear();
        trainingInfo.seekg(0, ios::beg);
        getline(trainingInfo, s);
        
        // Initialize the delimiter
        string delimiter = ",";
        // Stores the unlabeled data presented in the file
        fillVector(unLabeledData, trainingInfo, delimiter);
        
        // Initialize the distance matrix and Nodes vector
        initializeDistMatrix(distMatrix, unLabeledData);
        initializeNodesVector(vNodes, unLabeledData);
        
        // Generate the tree and return the head of the tree
        UnsupervisedNode* head = genTree(distMatrix, vNodes);
        // Print the tree
        printTree(head, 0);
    }
    
    // close the files opened
    trainingInfo.close();
    testingInfo.close();
    
    return 0;
}
