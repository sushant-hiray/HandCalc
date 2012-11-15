#include <vector>
#include <string>
using namespace std;

//class to construct tree to calculate Arithmetic Expression
//takes regular string of expression as input (spaces are not taken)
//e.g. 5+8*9-7
//it first read infix-expression and then convert it into post-fix expression
//evaluate and return the value of the expression

struct TreeNode1{
	string val ;
	TreeNode1* parent;
	TreeNode1* ltree;
	TreeNode1* rtree;
};

class ArithmeticExpression{
	TreeNode1* btree;
    bool isoperator(char op);       //returns true if char is '+','-','*' or '/'
    bool isoperator(string op);     //returns true if string is '+','-','*' or '/'
    bool isnumber(char num);        //returns false if char is '+','-','*' or '/'
    bool isnumber(string num);      //returns false if string is '+','-','*' or '/'
    bool isleaf(TreeNode1 v);       //returns true if node is leaf
    void print(TreeNode1 v);
	TreeNode1* maketree(string t);
	TreeNode1* makentree(TreeNode1& l, string op, TreeNode1& r);
    float eval(TreeNode1 v);
    //arrange takes a string as input and returns vector of strings.
    //e.g. "123+45-87/74" returns a vector comprises  "123":"+":"45":"-"87":"/":"74"
    pair<bool,vector<string> > arrange(string str);

    //takes input from output of arrange and converts into its postfix expression and returns vector of strings
    //e.g."123":"+":"45"  reurns   "123":"45":"+"
    vector<string> infix_to_postfix(vector<string> to_be_evaluated);
	
	public:
    bool readExpression(string Input);
	void printExpression();
    pair<bool,float> evaluate(string Expression);   //main function to evaluate the expression
};
