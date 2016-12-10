#ifndef DTree_h
#define DTree_h

#include "Data.h"
#include <vector>
#include <string>

namespace Dtree {
    
    // Node Class
    class Node {
    private:
        // Three children
        // for the three bins created for each attribute
        Node* child1;
        Node* child2;
        Node* child3;
        
        // Attribute name
        std::string attr;
        // Bin value
        float val;
    public:
        
        // Constructor
        Node () {}
        Node (std::string a, float v = 0, Node* o = nullptr, Node* tw = nullptr, Node* th = nullptr)
        : attr(a), val(v), child1(o), child2(tw), child3 (th) {};
        
        std::vector<DataEntries::Data*> set;
        
        void setAttr(std::string& Attr);
        void setVal (float v);
        void setO (Node* n);
        void setTw (Node* n);
        void setTh (Node* n);
        Node* getO ();
        Node* getTw ();
        Node* getTh ();
        std::string getAttr ();
        float getVal();
    };
    
    float getInfoMod(std::vector<std::pair<float,float>>&);
    std::vector<std::pair<float,float>> getPercentages (std::vector<DataEntries::Data*>&, std::string&, float, float, std::vector<std::string>&);
    std::string getBestAttr (std::vector<DataEntries::Data*>&, std::vector<std::string>&, float, std::vector<std::string>&);
    void subTree (std::vector<DataEntries::Data*>&, std::vector<DataEntries::Data*>&, std::string&, float, float, std::vector<std::string>&);
    Node* genTree (std::vector<DataEntries::Data*>&, std::vector<std::string>&, float, std::vector<std::string>&);
    bool getVote (std::vector<DataEntries::Data*>& d);
    int parseTree (Node*, DataEntries::Data*, std::vector<std::string>&);
    
}

#endif /* DTree_h */
