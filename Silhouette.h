#ifndef Silhouette_h
#define Silhouette_h

#include "Data.h"
#include <vector>

namespace Silhouette {
    
    float getDistance (std::vector<float>&, std::vector<float>&);
    float getSimilarity (std::vector<float>, std::vector<std::vector<float>>);
    float getSilhouetteVal (std::vector<float>, std::vector<std::vector<std::vector<float>>>, int, int);
    float getAvgSilVal (std::vector<std::vector<std::vector<float>>> clusters, int indexOfCluster, int indexOfOther);
    
}


#endif /* Silhouette_h */
