#include <stdio.h>
#include "DTree.h"
#include <Math.h>
#include <iostream>

using namespace std;
using namespace DataEntries;

namespace Dtree {
    
    // Setters for the Node class
    void Node::setAttr(std::string& a){attr = a;}
    void Node::setVal (float v){val = v;}
    void Node::setO (Node* n){child1 = n;}
    void Node::setTw (Node* n){child2 = n;}
    void Node::setTh (Node* n){child3 = n;}
    
    // Getters for the Node class
    Node* Node::getO (){return child1;}
    Node* Node::getTw (){return child2;}
    Node* Node::getTh (){return child3;}
    std::string Node::getAttr (){return attr;}
    float Node::getVal(){return val;}
    
    
    // Determines the Info value
    float getInfoMod(vector<pair<float,float>>& v) {
        if (v.empty()) return 0;
        float info = 0;
        for (int i = 0; i<v.size()-1; i++) {
            // uses the value/sum * log2 (value/sum)
            float sum = v[i].first + v[i].second;
            float frac = sum/v[v.size()-1].first;
            float firstHalf = -1*v[i].first*log2f(v[i].first/sum)/sum;
            float secHalf = -1*v[i].second/sum*log2f(v[i].second/sum);
            info += frac*(firstHalf-secHalf);
        }
        return info;
    }
    
    // Returns a vector containing the values needed for
    // the calculation of the Info value
    vector<pair<float,float>> getPercentages (vector<Data*>& d, string& s, float fBin, float sBin, vector<string>& att) {
        vector<pair<float,float>> v;
        
        // Finds the index where the appropriate attribute value is
        auto i = find (att.begin(), att.end(), s);
        // Checks if attribute is not yet used from the sample data set
        if (i == att.end()) {
            return v;
        }
        int index = i - att.begin();
        
        // Stores the vector with 3 dummy values
        for (int k = 0; k< 3; k++) {
            v.push_back(pair<float, float> (0,0));
        }
        
        // Increments the vector with values
        // so that each index would contain the amount of
        // dem votes for a specific bin
        for (int j = 0; j<d.size(); j++) {
            if (d[j]->val[index] <= fBin) {
                if (d[j]->getDem() == 1) v[0].first++;
                else v[0].second++;
            }
            else if (d[j]->val[index] > fBin && d[j]->val[index] < sBin) {
                if (d[j]->getDem() == 1) v[1].first++;
                else v[1].second++;
            }
            else if (d[j]->val[index] > sBin) {
                if (d[j]->getDem() == 1) v[2].first++;
                else v[2].second++;
            }
        }
        // Also pushes the size of the entire data set into the vector
        // for division when calculating the Info
        v.push_back(pair<float,float>(d.size(),0));
        return v;
    }
    
    // Finds the best attribute to split the tree
    string getBestAttr (vector<Data*>& d, vector<string>& s, float info, vector<string>& att) {
        string best = " ";
        float bestVal = 0;
        float fBin = 0;
        float sBin = 0;
        if (d.size() == 0) return best;
        // Depending on the attribute to be found, use different bin amounts
        for (int i = 1; i < s.size(); i++) {
            if (s[i] == "pop") {
                fBin = 50000;
                sBin = 100000;
            }
            else if (s[i] == "popC") {
                fBin = -5;
                sBin = 5;
            }
            else if (s[i] == "ageSFP") {
                fBin = 15;
                sBin = 20;
            }
            else if (s[i] == "black") {
                fBin = 0.2;
                sBin = 0.5;
            }
            else if (s[i] == "hispanic") {
                fBin = 0.02;
                sBin = 0.05;
            }
            else if (s[i] == "eBach") {
                fBin = 10;
                sBin = 15;
            }
            else if (s[i] == "income") {
                fBin = 30000;
                sBin = 50000;
            }
            else if (s[i] == "poverty") {
                fBin = 20;
                sBin = 25;
            }
            else if (s[i] == "density") {
                fBin = 50;
                sBin = 100;
            }
            else {
                return " ";
            }
            
            // Determines the gain from each attribute
            vector<pair<float,float>> f = getPercentages(d, s[i], fBin, sBin, att);
            float curr = getInfoMod(f);
            float gain = info - curr;
            
            // Return the best one
            if (gain > bestVal) {
                bestVal = gain;
                best = s[i];
            }
        }
        return best;
    }
    
    // Creates a smaller dataset to look into
    void subTree (vector<Data*>& d, vector<Data*>& dest, string& attr, float fBin, float sBin, vector<string>& att) {
        
        dest.clear();
        
        // Finds the appropriate data value for the attribute
        // If it can be found
        auto it = find(att.begin(), att.end(), attr);
        if (it == att.end()) return;
        int index = it - att.begin();
        
        // Push the right data sets that fit the bin into a smaller dataset
        for (int i = 0; i<d.size(); i++) {
            if (d[i]->val[index] >= fBin && d[i]->val[index] < sBin){
                dest.push_back(d[i]);
            }
        }
        
        //return dest;
    }
    
    // Generates the tree
    Node* genTree (vector<Data*>& d, vector<string>& s, float info, vector<string>& att) {
        
        // Can't generate the tree if the dataset is empty
        // or if there are no attributes
        if (d.empty()) return nullptr;
        if (s.empty()) return nullptr;
        
        // Determines the best attribute
        string best = getBestAttr(d, s, info, att);
        Node* head = new Node(best);
        head->set = d;
        // Finds the attribute to know where to look in the data
        // For parsing
        auto it = find(s.begin(), s.end(), best);
        if (it != s.end()) s.erase(it);
        Node* childOne;
        Node* childTwo;
        Node* childThree;
        
        float fBin;
        float sBin;
        vector<Data*> dest;
        
        // Initialize different values for bins for different attributes
        if (best == "pop") {
            fBin = 50000;
            sBin = 100000;
        }
        else if (best == "popC") {
            fBin = -5;
            sBin = 5;
        }
        else if (best == "ageSFP") {
            fBin = 15;
            sBin = 20;
        }
        else if (best == "black") {
            fBin = 0.2;
            sBin = 0.5;
        }
        else if (best == "hispanic") {
            fBin = 0.02;
            sBin = 0.05;
        }
        else if (best == "eBach") {
            fBin = 10;
            sBin = 15;
        }
        else if (best == "income") {
            fBin = 30000;
            sBin = 50000;
        }
        else if (best == "poverty") {
            fBin = 20;
            sBin = 25;
        }
        else if (best == "density") {
            fBin = 50;
            sBin = 100;
        }
        
        // Creates the children of the tree recursively
        subTree(d, dest, best, INT_MIN, fBin, att);
        childOne = genTree(dest, s, info, att);
        
        subTree(d, dest, best, fBin, sBin, att);
        childTwo = genTree(dest, s, info, att);
        
        subTree(d, dest, best, sBin, MAXFLOAT, att);
        childThree = genTree(dest, s, info, att);
        
        if (childOne) childOne->setVal(fBin);
        if (childTwo) childTwo->setVal(sBin);
        
        // Assign the children
        head->setO(childOne);
        head->setTw(childTwo);
        head->setTh(childThree);
        
        // Return the head of the tree
        return head;
    }
    
    bool getVote (vector<Data*>& d) {
        int votes = 0;
        for (int i = 0; i < d.size(); i++) {
            if (d[i]->getDem() == 0) votes--;
            else if (d[i]->getDem() == 1) votes++;
        }
        
        return votes > 0;
    }
    
    // Looks through the tree to find out what the vote is
    int parseTree (Node* n, Data* d, vector<string>& att) {
        
        // If the tree is empty, return Republican
        // If the Data set passed in is empty, return Republican
        // Because Republican is the majority vote
        if (!n) return 0;
        if (!d) return 0;
        
        // Finds where to look for specific attribute
        auto i = find(att.begin(), att.end(), n->getAttr());
        int index = i - att.begin();
        // Looks through tree, traversing through the children
        // Depending on the values in the data set
        while (n->getO()) {
            
            if (d->val[index] < n->getO()->getVal()) {
                n = n->getO();
            }
            else if (d->val[index] < n->getTw()->getVal()) {
                n = n->getTw();
            }
            else {
                n = n->getTh();
            }
            i = find(att.begin(), att.end(), n->getAttr());
            index = i - att.begin();
        }
        // Returns the vote;
        return getVote(n->set);
    }
}
