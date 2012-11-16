#include "constants.h"
#include <iostream>
using namespace std;

void whitespace(ifstream& in){   //whitespace parser (file reading)
    char c=in.get();
    while((c==' '|| c== '\n' || c=='\t' ) && c!=EOF){
        c=in.get();
    }
    in.putback(c);
}

void readXY(float& x,float& y,ifstream& in){  //reading the x and y coordinate of a point
    char c=in.get();
    in>>x;
    c=in.get();
    in>>y;
    c=in.get();
}

void readDatabase(multimap<string,feature>& trainingData){   //reads the complete database from database.txt
    cout<<"entered\n";
    ifstream data;
    data.open("DataBase.txt");
    string key,symbol;char temp[5];
    float x,y;
    Pt point;
    feature representative;
    whitespace(data);
    cout<<"aftr ws "<<char(data.peek())<<endl;
    data.getline(temp,5,':');
    key=temp;
    cout<<"key is"<<key.size()<<endl;
    while(key.size() < 3 ){
        whitespace(data);
        data.getline(temp,5,':');
        symbol=temp;
        cout<<"symbol is"<<symbol<<endl;
        while(symbol.size()==1){//it is a symbol
            vector<Pt> samplepts;

            for(int i=0;i<SR;i++){
                whitespace(data);
                readXY(x,y,data);
                point.x=x;
                point.y=y;
                samplepts.push_back(point);
            }
            whitespace(data);
            representative.id=symbol;
            representative.vec=samplepts;
            //samplepts.erase(samplepts.begin());
            //cout<<"size after erase"<<samplepts.size()<<endl;
            trainingData.insert(make_pair(key,representative));
            cout<<"inserted into the map "<<key<<" , "<<symbol<<endl;
            data.getline(temp,5,':');
            symbol=temp;
            cout<<"aftr 36 "<<symbol<<endl;

        }
        key=symbol;
    }

    data.close();
}
