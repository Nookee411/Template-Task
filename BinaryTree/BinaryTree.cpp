#include <iostream>
#include <vector>
#include <string>
#include <functional>


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
      int depth();
	  string leaves();
      bool search(T);
	  bool remove(T value);
};

int main()
{
	binaryTree<int> bt;
	bt.push(3);
	bt.push(4);
	bt.push(2);
	cout << "Depth: " << bt.depth()<<endl;
	cout <<"- leaves"<< bt.leaves()<<endl;
	cout <<"Is search working? "<< ((bt.search(3)) ? "ya" : "no");
	bt.remove(3);
	bt.remove(4);
	bt.leaves();
}

template <typename T>
binaryTree<T>::node::node(T value) :value(value) {}

template <typename T>
binaryTree<T>::binaryTree() {}
template<typename T>
binaryTree<T>::~binaryTree()
{
	if (root != NULL)
		del(*root);
};

template <typename T>
void binaryTree<T>::del(node& cur)
{
	if (&cur == NULL)
		return;
    if (cur.RightSib != NULL)
        del(*cur.RightSib);
    if (cur.LeftSib != NULL)
        del(*cur.LeftSib);
    delete &cur;
}

template<typename T>
void binaryTree<T>::ins(node&cur,node& temp)
{
	if (temp.value > cur.value)
	{
		if (cur.RightSib != NULL)
			ins(*cur.RightSib, temp);
		else
			cur.RightSib = &temp;
	}
	else
	{
		if (cur.LeftSib != NULL)
			ins(*cur.LeftSib, temp);
		else
			cur.LeftSib = &temp;
	}
}


template <typename T>
void binaryTree<T>::push(T value)
{
	node* temp = new node(value);
	if (root == NULL)
		root = temp;
	else if (!search(value))
		ins(*root,*temp);
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
		return exactSeatch(value,root);
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
		exactLeaves(root,res);
	return res;
}


template <typename T>
string binaryTree<T>::exactLeaves(node* current,string& res)
{
		if (current->LeftSib)
			exactLeaves(current->LeftSib,res);
		if (current->RightSib!=NULL)
			exactLeaves(current->RightSib,res);
		if (current->LeftSib==NULL && current->RightSib==NULL)
			cout<< current->value<<' ';
		return res;
}

template <typename T>
bool binaryTree<T>::remove(T value)
{
	function<node*(node*, int)> helper = [&helper](node* current, int value) -> node*
	{
		if (!current)
			return current;
		else if (value < current->value)
		{
			current->LeftSib = helper(current->LeftSib, value);
			return current;
		}
		else if (value > current->value)
		{
			current->RightSib = helper(current->RightSib, value);
			return current;
		}
		else
		{
			if (!current->LeftSib)
			{
				node* temp = current->RightSib;
				delete current;
				return temp;
			}
			else if (!current->RightSib)
			{
				node* temp = current->LeftSib;
				delete current;
				return temp;
			}
			else
			{
				function<node* (node*)> find_max = [](node* cur) -> node*
				{
					while (cur->RightSib)
						cur = cur->RightSib;
					return cur;
				};
				node* max_node = find_max(current->LeftSib);
				current->value = max_node->value;
				current->LeftSib = helper(current->LeftSib, max_node->value);
				return current;
			}
		}
	};
	if (!search(value))
		return false;
	helper(root, value);
	return true;
}
