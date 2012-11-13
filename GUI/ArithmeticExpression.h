#include <vector>
#include <string>
using namespace std;


struct mypair1{
	char var;
	int value;
};

struct TreeNode1{
	string val ;
	TreeNode1* parent;
	TreeNode1* ltree;
	TreeNode1* rtree;
};

class ArithmeticExpression{
	TreeNode1* btree;
	bool isoperator(char op);
	bool isoperator(string op);
	bool isnumber(char num);
	bool isnumber(string num);
	bool isleaf(TreeNode1 v);
	void print(TreeNode1 v);
	TreeNode1* maketree(string t);
	TreeNode1* makentree(TreeNode1& l, string op, TreeNode1& r);
	float eval(TreeNode1 v);
	bool isA_priorto_B(string A, string B);
	vector<string> arrange(string str);
	vector<string> infix_to_postfix(vector<string> to_be_evaluated);
	
	public:
	void readExpression(string Input);
	void printExpression();
	float evaluate(string Expression);
};
