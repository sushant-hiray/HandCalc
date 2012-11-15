#include <iostream>
#include <fstream>

using namespace std;

int main(){
	ifstream input;
	float asdl;

	input.open("strokes.txt");
	while(input.good()){
		input>>asdl;
		cout<<asdl<<endl;
	}
	input.close();
	return 0;
}
