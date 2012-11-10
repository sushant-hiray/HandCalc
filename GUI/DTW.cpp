#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>
#include <string>
#include "DTW.h"
#define PI 3.14159
#define MAX pow(2, 20)
#define d_cost 0.5
#define h_cost 1
#define v_cost 1

using namespace std;

double distance_sets(Pt s1,Pt s2){
	//return sqrt(pow((s1.x - s2.x) , 2) + pow((s1.y - s2.y) , 2) + pow((s1.angle - s2.angle) , 2)) ;
	return sqrt(pow((s1.x - s2.x) , 2) + pow((s1.y - s2.y) , 2));
}

float DTW(vector<Pt> v1, vector<Pt> v2){
	float cost = 0;
	int size1 = v1.size();
	int size2 = v2.size();
	float variable_cost;
	pair<double,string>** v;
	v= new pair<double,string>*[size1];
	for(int i = 0 ; i<size1 ; i++){
		v[i] = new pair<double,string>[size2];
	}
	
	//initialise the dtw matrix
	for(int i =0; i<size2; i++){
		for(int j =0; j<size1; j++){
			v[j][i].first = MAX;
			v[j][i].second = "11";
		}
	}
	
	v[0][0].first = distance_sets(v1[0],v2[0]);
	v[0][0].second = "11";
	
	//setting the first column
	for(int r = 1; r <size1 ; r++){
		v[r][0].first = v[r-1][0].first + v_cost*distance_sets(v1[r],v2[0]);
		v[r][0].second = "10";
	}
	
	//setting the first row
	for(int c = 1; c <size2 ; c++){
		v[0][c].first = v[0][c-1].first + h_cost*distance_sets(v1[0],v2[c]);
		v[0][c].second = "01";
	}

	for(int r = 1; r <size1 ; r++){
		for(int c = 1; c <size2 ; c++){
			double minimum = min(min(v[r-1][c].first , v[r][c-1].first) , v[r-1][c-1].first);
			if(minimum == v[r-1][c].first){variable_cost = v_cost;}
			else if(minimum == v[1][c-1].first){variable_cost = h_cost;}
			else{variable_cost = d_cost;}
			double dis = distance_sets(v1[r] , v2[c]);
			v[r][c].first = minimum + variable_cost*dis;
			
			if(minimum == v[r-1][c].first){
				v[r][c].second = "10";
			}
			if(minimum == v[r][c-1].first){
				v[r][c].second = "01";
			}
			if(minimum == v[r-1][c-1].first){
				v[r][c].second = "11";
			}
			
		}
	}
	cost = v[size1 -1][size2-1].first;
	
	//backtracking
	delete v;
	return cost;
}

