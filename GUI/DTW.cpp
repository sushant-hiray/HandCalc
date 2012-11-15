#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>
#include <string>
#include "DTW.h"
#define PI 3.14159
#define MAX pow(2, 20)
#define d_cost 0.5      //diagonal cost(weight)
#define h_cost 1        //horizontal cost(weight)
#define v_cost 1        //vertical cost(weight)

using namespace std;

double DTW::distance_sets(Pt point1,Pt point2){
    return sqrt(pow((point1.x - point2.x) , 2) + pow((point1.y - point2.y) , 2));
}

//DTW takes two strokes as input and returns the cost of comparing these two strokes
//less the cost better the match


float DTW::warp(vector<Pt> stroke1, vector<Pt> stroke2){
	float cost = 0;
    int size1 = stroke1.size();
    int size2 = stroke2.size();
	float variable_cost;
    //int PathLength =0;                //to calculate the length of minimum cost path
    pair<double,string>** Cost_Matrix;

    Cost_Matrix = new pair<double,string>*[size1];
	for(int i = 0 ; i<size1 ; i++){
        Cost_Matrix[i] = new pair<double,string>[size2];
	}

    //"11" :- diagonal parent , "01" :- column parent , "10" :- row parent
	//initialise the dtw matrix
	for(int i =0; i<size2; i++){
		for(int j =0; j<size1; j++){
            Cost_Matrix[j][i].first = MAX;
            Cost_Matrix[j][i].second = "11";
		}
	}
	
    Cost_Matrix[0][0].first = distance_sets(stroke1[0],stroke2[0]);
    Cost_Matrix[0][0].second = "11";
	
	//setting the first column
	for(int r = 1; r <size1 ; r++){
        Cost_Matrix[r][0].first = Cost_Matrix[r-1][0].first + v_cost*distance_sets(stroke1[r],stroke2[0]);
        Cost_Matrix[r][0].second = "10";
	}
	
	//setting the first row
	for(int c = 1; c <size2 ; c++){
        Cost_Matrix[0][c].first = Cost_Matrix[0][c-1].first + h_cost*distance_sets(stroke1[0],stroke2[c]);
        Cost_Matrix[0][c].second = "01";
	}

    //filling the rest of the Cost_Martix
	for(int r = 1; r <size1 ; r++){
		for(int c = 1; c <size2 ; c++){
            double minimum = min(min(Cost_Matrix[r-1][c].first , Cost_Matrix[r][c-1].first) , Cost_Matrix[r-1][c-1].first);
            if(minimum == Cost_Matrix[r-1][c].first){variable_cost = v_cost;}
            else if(minimum == Cost_Matrix[1][c-1].first){variable_cost = h_cost;}
			else{variable_cost = d_cost;}
            double local_cost = distance_sets(stroke1[r] , stroke2[c]);
            Cost_Matrix[r][c].first = minimum + variable_cost*local_cost;
			
            if(minimum == Cost_Matrix[r-1][c].first){
                Cost_Matrix[r][c].second = "10";
			}
            if(minimum == Cost_Matrix[r][c-1].first){
                Cost_Matrix[r][c].second = "01";
			}
            if(minimum == Cost_Matrix[r-1][c-1].first){
                Cost_Matrix[r][c].second = "11";
			}
			
		}
	}
    cost = Cost_Matrix[size1 -1][size2-1].first;

    delete Cost_Matrix;
	return cost;
}

