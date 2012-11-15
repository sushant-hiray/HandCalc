#include <iostream>
#include <stack>
#include <queue>
#include <cstdlib>
#include "ArithmeticExpression.h"
#include <sstream>

using namespace std;

bool ArithmeticExpression::isoperator(string op){				//returns true when a string is a operater
	return ((op=="+")||(op=="-")||(op=="/")||(op=="*"));
}

bool ArithmeticExpression::isoperator(char op){				//returns true when a character is a operater
	return ((op=='+')||(op=='-')||(op=='/')||(op=='*'));
}

bool ArithmeticExpression::isnumber(char num){              //returns true when a character is a number
	return !isoperator(num);
}

bool ArithmeticExpression::isnumber(string num){            //returns true when a string is a number
	return !isoperator(num);
}

bool ArithmeticExpression::isleaf(TreeNode1 v){				//returns true when a TreeNode1 node is a leaf(both subtrees are null)
	return ((v.ltree== NULL) && (v.rtree== NULL));
}

TreeNode1* ArithmeticExpression::maketree(string t){			//make a leaf with a character t
	TreeNode1* T;
	T=new TreeNode1;
	T->val=t;
	T->ltree=NULL;
	T->rtree=NULL;
	return T;
} 
	
TreeNode1* ArithmeticExpression::makentree(TreeNode1& l, string op, TreeNode1& r){	//make tree with two subtrees and a operator character
	TreeNode1 *T;
	T=new TreeNode1;
	T->val=op;
	T->ltree=&l;
	T->rtree=&r;
	return T;
}

int getval(string x){               //getval returns the integer according to priority giveb to a  operator(2(-) is lowest and 4(/) is highest)
    if(x=="/") return 4;
    else if(x=="*") return 3;
    else if(x=="+") return 2;
    else return 2;
}
bool isAB(string a,string b){       //returns true if operator "a" prior to "b"
    if(getval(a)> getval(b)) {return true;}
    else return false;
}


//arrange returns vector of strings.
//e.g. "123+45-87/74" returns a vector comprises  "123":"+":"45":"-"87":"/":"74"
pair<bool,vector<string> > ArithmeticExpression::arrange(string str){
    bool continuous_two =false;
    vector<string> Arranged_String;

    if(isoperator(str[0]) || isoperator(str[str.size() -1]) || str==""){
        return make_pair(false , Arranged_String);
    }

    int last_operator=1;
    for(int i=1;i<str.size();i++){
        if(isoperator(str[i])){
            if (i - last_operator == 1){
                continuous_two = true;
                break;
            }
            else{
                last_operator = i;
            }
        }
    }

    if(continuous_two){
        return make_pair(false , Arranged_String);
    }




	int index=0;
	

    pair<bool,string> local;
	local.second = "";
	local.first = false;
	
	while(index<str.size()){
		if(local.first==false){
			local.first = true;
			local.second = str.substr(index,1);
		}
		else if(isoperator(str[index])){//is operator
			Arranged_String.push_back(local.second);
			local.first = false;
			local.second = "";
			 
			Arranged_String.push_back(str.substr(index,1)); 
		}
		else{					//is a number
			local.first =true;
			local.second = local.second + str.substr(index,1);
        }
		index++;
	}
	if(local.first == true){
		Arranged_String.push_back(local.second);
	}
    return make_pair(true,Arranged_String);
}



bool ArithmeticExpression::readExpression(string Input){				//function which reads infix input and makes a internal tree
    //first arrange and then convert infix to postfix
    pair<bool,vector<string> > arranged_str = arrange(Input);
    if(!arranged_str.first){
        return false;
    }

    vector<string> str = infix_to_postfix(arranged_str.second);
    for(int i=0;i<str.size();i++){
        cout<<str[i]<<" ";
    }
	string op;
	TreeNode1 *t,*tl,*tr;
	stack<TreeNode1*> st;
	int i=0;
	while(i<str.size()){					
		op=str[i++];
		if(!isoperator(op)){				//when op is not operator then push it to stack after convertig it to a tree
			t=maketree(op);
			st.push(t);
		}
		else{
			tr=st.top();
			st.pop();
			tl=st.top();
			st.pop();
			t=makentree(*tl,op,*tr);		
			st.push(t);			//when op is operator then push it to stack after merging top two trees of stack to a tree and op as operator
		}
	}

	btree=st.top();			//final tree would be on the top of stack

    return true;
}

vector<string> ArithmeticExpression::infix_to_postfix(vector<string> to_be_evaluated){
	
	vector<string> postfix;
	stack<string> Operator_Holder;
	typename vector<string>::iterator infix_itr = to_be_evaluated.begin();
	while(infix_itr != to_be_evaluated.end()){
		if(!isoperator(*infix_itr)){
			postfix.push_back(*infix_itr);
		}
		else{
            while(Operator_Holder.size() !=0 and !(isAB(*infix_itr,Operator_Holder.top()))){
				postfix.push_back(Operator_Holder.top());
				Operator_Holder.pop();
			}
			Operator_Holder.push(*infix_itr);
		}
		infix_itr++;
	}
	while(Operator_Holder.size() !=0){
        cout<<"....................................................coutter"<<endl;
		postfix.push_back(Operator_Holder.top());
		Operator_Holder.pop();
    }
    return postfix;
}

void ArithmeticExpression::printExpression(){			//prints expression stored in Tree as infix expression
	print(*btree);				//calls print(a helper function)
}

void ArithmeticExpression::print(TreeNode1 v){		//helper funtion of printExpression()
	if(isleaf(v)){
		cout<<v.val;
	}
	else{
		cout<<"(";
		print(*(v.ltree));
		cout<<v.val;
		print(*(v.rtree));
		cout<<")";
	}
}

pair<bool,float> ArithmeticExpression::evaluate(string expression){			//evluates the expression
    bool if_read = readExpression(expression);
   // printExpression();
    if(if_read){
        return make_pair(true,eval(*btree));
    }
    else{
        return make_pair(false,0);
    }
}

float ArithmeticExpression::eval(TreeNode1 v){	
	if(isleaf(v)){
		int ret_val;
		stringstream(v.val)>>ret_val;
		return ret_val;
	}
	
	else if(v.val=="+") {return ((float)(eval(*(v.ltree)) + eval(*(v.rtree))));}
	else if(v.val=="-") {return ((float)(eval(*(v.ltree)) - eval(*(v.rtree))));}
	else if(v.val=="*") {return ((float)(eval(*(v.ltree)) * eval(*(v.rtree))));}
	else if(v.val=="/") {return ((float)(eval(*(v.ltree)) / eval(*(v.rtree))));}

}
