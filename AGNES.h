#ifndef AGNES_h
#define AGNES_h

#include <vector>
#include <fstream>

namespace AGNES {
    
    class UnsupervisedNode {
    private:
        UnsupervisedNode* child1;
        UnsupervisedNode* child2;
    public:
        std::vector<float> values;
        UnsupervisedNode(){};
        // Constructor
        UnsupervisedNode(std::vector<float> v) : values(v){};
        UnsupervisedNode* getChild1 ();
        UnsupervisedNode* getChild2 ();
        void modChild1 (UnsupervisedNode*);
        void modChild2 (UnsupervisedNode*);
    };
    
    void initializeDistMatrix (std::vector<std::vector<float>>&, std::vector<std::vector<float>>&);
    void initializeNodesVector (std::vector<UnsupervisedNode*>&, std::vector<std::vector<float>>&);
    std::pair<int, int> findMinDistCluster (std::vector<std::vector<float>>&);
    void modMatrix (std::vector<std::vector<float>>&, int, int);
    void modVNodes (std::vector<UnsupervisedNode*>&, int, int);
    UnsupervisedNode* genTree (std::vector<std::vector<float>>&, std::vector<UnsupervisedNode*>& nodes);
}


#endif /* AGNES_h */
