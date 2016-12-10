#include <stdio.h>
#include "Data.h"


using namespace std;

namespace DataEntries {
    
    
    // getters for the Data class
    float Data::getDem () {return democrat;}
    float Data::getPop () {return population;}
    float Data::getPopChange () {return popChange;}
    float Data::getAgeSFP () {return ageSFp;}
    float Data::getBlack () {return black;}
    float Data::getHispanic () {return hispanic;}
    float Data::getEBach () {return eBach;}
    float Data::getIncome () {return income;}
    float Data::getPoverty () {return poverty;}
    float Data::getDensity () {return density;}
    
    // Fill a vector with random amount of data entries
    // based on the parameter split
    void fillSets (ifstream& f, vector<DataEntries::Data*>& set) {
        
        float democrat, population, popChange, ageSFp, black, hispanic, eBach, income, poverty, density;
        string s;
        
        // reads lines from a file
        while (getline(f, s)) {
            
            // initializes the different values for an instance of a data set from the file line
            int pos1 = s.find_first_of(',');
            democrat = stof(s.substr(0,pos1));
            
            int pos2 = s.find_first_of(',', pos1+1);
            population = stof(s.substr(pos1+1, pos2-pos1-1));
            
            int pos3 = s.find_first_of(',', pos2+1);
            popChange = stof(s.substr(pos2+1, pos3-pos2-1));
            
            int pos4 = s.find_first_of(',', pos3+1);
            ageSFp = stof(s.substr(pos3+1, pos4-pos3-1));
            
            int pos5 = s.find_first_of(',', pos4+1);
            black = stof(s.substr(pos4+1, pos5-pos4-1));
            
            int pos6 = s.find_first_of(',', pos5+1);
            hispanic = stof(s.substr(pos5+1, pos6-pos5-1));
            
            int pos7 = s.find_first_of(',', pos6+1);
            eBach = stof(s.substr(pos6+1, pos7-pos6-1));
            
            int pos8 = s.find_first_of(',', pos7+1);
            income = stof(s.substr(pos7+1, pos8-pos7-1));
            
            int pos9 = s.find_first_of(',', pos8+1);
            poverty = stof(s.substr(pos8+1, pos9-pos8-1));
            
            int pos10 = s.find_first_of(',', pos9+1);
            density = stof(s.substr(pos9+1, pos10-pos9-1));
            
            set.push_back(new DataEntries::Data (democrat, population, popChange, ageSFp, black, hispanic,
                                                             eBach, income, poverty, density));
        }
    }

    
};
