#include <iostream>
#include <vector>
#include <string>


using namespace std;

template <typename T>
class binaryTree
{
private:
    typedef struct node
    {
		node* LeftSib = NULL;
		node* RightSib = NULL;
        T value;
        node(T);
    }node;
    node* root = NULL;
	void del(node&);
	void ins(node&,node&);
	void exactPull(node*, int);
	bool exactSeatch(int, node*);
	int exactDepth(node*);
	string exactLeaves(node* current, string& res);


//
//
public:
    //Constructors
      binaryTree();
    //Destructor
      ~binaryTree();
//    //Methods
      void push(T);
      void pull(T);
      int depth();
	  string leaves();
      bool search(T);	  
};

int main()
{
    
}

template <typename T>
binaryTree<T>::node::node(T value) :value(value) {}

template <typename T>
binaryTree<T>::binaryTree() {}
template<typename T>
binaryTree<T>::~binaryTree()
{
	if (root != NULL)
		del(root);
};

template <typename T>
void binaryTree<T>::del(node& cur)
{
    if (cur->RightSib != NULL)
        del(cur->RightSib);
    if (cur->LeftSib != NULL)
        del(cur->RightSib);
    delete cur;
}

template<typename T>
void binaryTree<T>::ins(node&cur,node& temp)
{
	if (temp->value > cur->value)
	{
		if (cur->RightSib != NULL)
			ins(cur->RightSib, temp);
		else
			cur -> RightSib = temp;
	}
	else
	{
		if (cur->LeftSib != NULL)
			ins(cur->LeftSib, temp);
		else
			ins(cur->RightSib, temp);
	}
}

template<typename T>
void binaryTree<T>::exactPull(node* cur, int value)
{
	if (cur == NULL)
		return;
	else if (value < cur->value)
	{
		cur->LeftSib = exactPull(cur->LeftSib, value);
	}
	else if (value > cur->value)
	{
		cur->RightSib = exactPull(cur->RightSib, value);
	}
	else
	{
		if (cur->LeftSib != NULL)
		{
			node* temp = cur->RightSib;
			delete cur;
		}
		else if (cur->RightSib != NULL)
		{
			node* temp = cur->LeftSib;
			delete cur;
		}
		else
		{
			node* tempMax = cur;
			while (tempMax->RightSib != NULL)
				tempMax = tempMax->RightSib;
			cur->LeftSib = exactPull(cur->LeftSib, tempMax->value);
			cur->value = tempMax->value;
		}
	}
}
template <typename T>
void binaryTree<T>::push(T value)
{
	node* temp = new node(value);
	if (root == NULL)
		root = temp;
	if (search(value))
		ins(root);
}

template<typename T>
void binaryTree<T>::pull(T value)
{
	if (!search(value))
		return;
	else
		exactPull(root, value);
}

template<typename T>
int binaryTree<T>::depth()
{
	if (root != NULL)
		return exactDepth(root);
	else
		return 0;
}

template<typename T>
int binaryTree<T>::exactDepth(node* cur)
{
	int rh = (cur->RightSib != NULL) ? exactDepth(cur->RightSib) : 0;
	int lh = (cur->LeftSib != NULL) ? exactDepth(cur->LeftSib) : 0;
	return 1 + (rh > lh ? rh : lh);
}

template <typename T>
bool binaryTree<T>::search(T value)
{
	if (root == NULL)
		return false;
	else
		return exactSeatch(root);
}


template<typename T>
bool binaryTree<T>::exactSeatch(int value, node*cur)
{
	if (value == cur->value)
		return true;
	if (cur->LeftSib != NULL && value < cur->value)
		return exactSeatch(value, cur->LeftSib);
	if (cur->RightSib != NULL && value >= cur->value)
		return exactSeatch(value, cur->RightSib);
	return false;
}

template <typename T>
string binaryTree<T>::leaves()
{
	string res="";
	if (root)
		helper(root);
	return res;
}


template <typename T>
string binaryTree<T>::exactLeaves(node* current,string& res)
{
		if (current->left_child)
			exactLeaves(current->left_child,res);
		if (current->right_child,res)
			exactLeaves(current->right_child,res);
		if (!current->left_child && !current->right_child,res)
			res += current.value + " ";
}
