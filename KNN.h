#ifndef KNN_h
#define KNN_h

#include <vector>
#include "Data.h"

namespace KNN {

    float getDistance (DataEntries::Data&, DataEntries::Data&);
    bool checker (std::pair<DataEntries::Data*,float>&, std::pair<DataEntries::Data*,float>&);
    std::vector<DataEntries::Data*> getNeighbors (std::vector<DataEntries::Data*>&, DataEntries::Data&, int);
    bool getResponse (std::vector<DataEntries::Data*>&);
    
}

#endif /* KNN_h */
