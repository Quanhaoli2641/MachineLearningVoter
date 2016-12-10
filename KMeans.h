#ifndef KMeans_h
#define KMeans_h


#include <vector>
#include <fstream>

namespace KMeans {
    
    void fillVector (std::vector<std::vector<float>>&, std::ifstream&, std::string&);
    void modify (std::vector<std::vector<float>>&, std::vector<std::vector<float>>&, int, std::vector<float>&);
    unsigned long redefineCenter (std::vector<std::vector<float>> set, unsigned long center);
    void getClusters (std::vector<std::vector<std::vector<float>>>&, std::vector<std::vector<float>>&, unsigned long, unsigned long,
                      std::vector<std::vector<float>>&, std::vector<std::vector<float>>&);
    
}

#endif /* KMeans_h */
