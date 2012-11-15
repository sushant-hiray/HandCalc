#ifndef CONSTANTS_H
#define CONSTANTS_H
#include <list>
#include<vector>
#include<fstream>
#include<cstring>
#include<stdio.h>
#include<map>
using namespace std;

#define SR 36  //sampling rate
#define distortion 0.3 // x/y


//constants for preprocessing
#define Delta 0.20      //constant to determine the characterstic of stroke
#define Threshold 0.5   //to identify stroke
struct Pt{
    float x;
    float y;
};


struct feature{
    string id; //id is the actual symbol
    vector<Pt> vec;
};

struct myRect{ //to tell which area to delete from the canvas when backspace operation is done
    int x1;
    int y1;
    int x2;
    int y2;
    myRect(){
        x1=x2=y1=y2=0;
    }
};

void whitespace(ifstream& in);      //remove whitespace character reading DataBase textfile
void readDatabase(multimap<string,feature>& trainingData);
void readXY(float& x,float& y,ifstream& in);

#endif // CONSTANTS_H
