#ifndef DTW_H
#define DTW_H
#include "constants.h"
class DTW{
public:
    float warp(vector<Pt> v1, vector<Pt> v2);
    double distance_sets(Pt s1,Pt s2);

};


#endif // DTW_H
