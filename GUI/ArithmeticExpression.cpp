#include <iostream>
#include <stack>
#include <queue>
#include <cstdlib>
#include "ArithmeticExpression.h"
#include <sstream>

using namespace std;

bool ArithmeticExpression::isoperator(string op){				//returns true when a character is a operater
	return ((op=="+")||(op=="-")||(op=="/")||(op=="*"));
}

bool ArithmeticExpression::isoperator(char op){				//returns true when a character is a operater
	return ((op=='+')||(op=='-')||(op=='/')||(op=='*'));
}

bool ArithmeticExpression::isnumber(char num){
	return !isoperator(num);
}

bool ArithmeticExpression::isnumber(string num){
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

bool ArithmeticExpression::isA_priorto_B(string A, string B){
	if(A==B){
        return true;
		if(A=="/") return true;
		else return false;
	}
	else if(A=="/"){return true;}
	else if(A=="*" and B!= "/"){return true;}
	else if((A == "+")or(A == "-")){
		if(B == "+" or B == "-"){return true;}
        else false;
	}
	else false;
}

vector<string> ArithmeticExpression::arrange(string str){
	vector<string> Arranged_String;
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
	return Arranged_String;
}



void ArithmeticExpression::readExpression(string Input){				//function which reads input and makes a internal tree
	vector<string> str = infix_to_postfix(arrange(Input));
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
			//while(Operator_Holder.size() !=0 and !(isA_priorto_B(*infix_itr,Operator_Holder.top()))){
            while(Operator_Holder.size() !=0 and !(isA_priorto_B(Operator_Holder.top(),*infix_itr))){
				postfix.push_back(Operator_Holder.top());
				Operator_Holder.pop();
			}
			Operator_Holder.push(*infix_itr);
		}
		infix_itr++;
	}
	while(Operator_Holder.size() !=0){
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

float ArithmeticExpression::evaluate(string expression){			//evluates the expression
	readExpression(expression);
    printExpression();
	return eval(*btree);
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
