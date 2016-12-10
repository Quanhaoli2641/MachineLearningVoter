#ifndef Data_h
#define Data_h

#include <fstream>
#include <vector>

namespace DataEntries {
    class Data {
        
    private:
        
        float democrat, population, popChange, ageSFp, black, hispanic, eBach, income, poverty, density;
        
    public:
        
        std::vector<float> val;
        
        // Constructor for Data class
        Data (float dem, float pop, float pC, float SF, float b, float h, float eB, float inc, float pov, float den):
        democrat(dem), population (pop), popChange (pC), ageSFp (SF), black (b), hispanic (h), eBach (eB),
        income (inc), poverty (pov), density (den){
            val.push_back(dem);
            val.push_back(pop);
            val.push_back(pC);
            val.push_back(SF);
            val.push_back(b);
            val.push_back(h);
            val.push_back(eB);
            val.push_back(inc);
            val.push_back(pov);
            val.push_back(den);
        }
        
        
        
        float getDem ();
        float getPop ();
        float getPopChange ();
        float getAgeSFP ();
        float getBlack ();
        float getHispanic ();
        float getEBach ();
        float getIncome ();
        float getPoverty ();
        float getDensity ();
        
    };
    
    void fillSets (std::ifstream&, std::vector<DataEntries::Data*>&);
}


#endif /* Data_h */
