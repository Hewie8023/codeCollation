#include<iostream>
#include<stack>
#include<queue>
#include<vector>
using namespace std;

struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

void createTree(TreeNode* &head) {
	char ch;
	cin >> ch;
	if (ch == '#') {
		head = nullptr;
	}
	else {
		head = new TreeNode(ch - '0');
		createTree(head->left);
		createTree(head->right);
	}
}
void preorderUnRecur(TreeNode* head) {
	if (head) {
		stack<TreeNode*> stack;
		stack.push(head);
		while (!stack.empty()) {
			head = stack.top();
			stack.pop();
			cout << head->val << " ";
			if (head->right) {
				stack.push(head->right);
			}
			if (head->left) {
				stack.push(head->left);
			}
		}
	}
	cout << endl;
}
void preorderRecur(TreeNode* head) {
	if (!head) {
		return;
	}
	cout << head->val << " ";
	preorderRecur(head->left);
	preorderRecur(head->right);
}

void inorderRecur(TreeNode* head) {
	if (!head) {
		return;
	}
	inorderRecur(head->left);
	cout << head->val << " ";
	inorderRecur(head->right);
}

void inorderUnRecur(TreeNode* head) {
	if (head) {
		stack<TreeNode*> stack;
		while (!stack.empty() || head) {
			if (head) {
				stack.push(head);
				head = head->left;
			}
			else {
				head = stack.top();
				stack.pop();
				cout << head->val << " ";
				head = head->right;
			}
		}
		cout << endl;
	}
}
void posorderRecur(TreeNode* head) {
	if (!head) {
		return;
	}
	posorderRecur(head->left);
	posorderRecur(head->right);
	cout << head->val << " ";
}

void posorderReRecur(TreeNode* head) {
	if (head) {
		stack<TreeNode*> s1;
		stack<TreeNode*> s2;
		s1.push(head);
		while (!s1.empty()) {
			head = s1.top();
			s1.pop();
			s2.push(head);
			if (head->left) {
				s1.push(head->left);
			}
			if (head->right) {
				s1.push(head->right);
			}
		}
		while (!s2.empty()) {
			cout << s2.top()->val << " ";
			s2.pop();
		}
		cout << endl;
	}
}

void levelOrderUnRecur(TreeNode* head) {
	queue<TreeNode*> queue;
	queue.push(head);
	while (!queue.empty()) {
		head = queue.front();
		queue.pop();
		cout << head->val << " ";
		if (head->left) {
			queue.push(head->left);
		}
		if (head->right) {
			queue.push(head->right);
		}
	}
	cout << endl;
}

int treeDepth(TreeNode* head) {
	if (!head) {
		return 0;
	}
	else {
		int m = treeDepth(head->left);
		int n = treeDepth(head->right);
		return m > n ? m + 1 : n + 1;
	}
}
int treeNodeNums(TreeNode* head) {
	if (!head) {
		return 0;
	}
	else {
		return treeNodeNums(head->left) + treeNodeNums(head->right) + 1;
	}
}

int treeLeftNums(TreeNode* head) {
	if (!head) {
		return 0;
	}
	if (!head->left && !head->right) {
		return 1;
	}
	else {
		return treeLeftNums(head->left) + treeLeftNums(head->right);
	}
}

void getAllPath(TreeNode* head, vector<int>& path, int pathLen) {
	int i;
	if (head) {
		//path[pathLen] = head->val;
		path.push_back(head->val);
		if (!head->left && !head->right) {
			for (i = 0; i <= pathLen; ++i) {
				cout << path[i] << " ";
			}
			cout << endl;
		}
		else {
			getAllPath(head->left, path, pathLen + 1);
			path.pop_back();
			getAllPath(head->right, path, pathLen + 1);
			path.pop_back();
		}
	}
}
int treeNode_1_Nums(TreeNode* head) {
	if (!head) {
		return 0;
	}
	if ((!head->left && head->right) || (head->left && !head->right)) {
		return 1 + treeNode_1_Nums(head->left) + treeNode_1_Nums(head->right);
	}
	else {
		return treeNode_1_Nums(head->left) + treeNode_1_Nums(head->right);
	}
}

TreeNode* searchNode(TreeNode* head, int elem) {
	if (!head) {
		return nullptr;
	}
	stack<TreeNode*> stack;
	stack.push(head);
	while (!stack.empty()) {
		head = stack.top();
		stack.pop();
		if (head->val == elem) {
			cout << "find it!" << endl;
			return head;
		}
		if (head->right) {
			stack.push(head->right);
		}
		if (head->left) {
			stack.push(head->left);
		}
	}
	cout << "can't find it!" << endl;
}

void insertNode(TreeNode* head, int elem) {
	queue<TreeNode*> queue;
	queue.push(head);
	while (!queue.empty()) {
		head = queue.front();
		queue.pop();
		if (!head->left) {
			TreeNode* node = new TreeNode(elem);
			head->left = node;
			break;
		}
		else {
			queue.push(head->left);
		}
		if (!head->right) {
			TreeNode* node = new TreeNode(elem);
			head->right = node;
			break;
		}
		else {
			queue.push(head->right);
		}
	}
}

void createSearchTree(TreeNode* &head, int elem) {
	if (!head) {
		head = new TreeNode(elem);
		return;
	}
	else {
		if (elem < head->val) {
			createSearchTree(head->left, elem);
		}
		else if (elem > head->val) {
			createSearchTree(head->right, elem);
		}
		else {
			cout << "已存在！" << endl;
			return;
		}
	}
}

TreeNode* findNodeInSearchTree(TreeNode* head, int elem) {
	if (!head) {
		cout << "cne't find!" << endl;
		return head;
	}
	if (head->val > elem) {
		findNodeInSearchTree(head->left, elem);
	}
	if (head->val < elem) {
		findNodeInSearchTree(head->right, elem);
	}
	if (head->val == elem) {
		cout << "find!" << endl;
		return head;
	}
}

void insertNodetoSearchTree(TreeNode* &head, int elem) {
	if (!head) {
		cout << "插入成功" << endl;
		head = new TreeNode(elem);
		return;
	}
	if (head->val > elem) {
		insertNodetoSearchTree(head->left, elem);
	}
	if (head->val < elem) {
		insertNodetoSearchTree(head->right, elem);
	}
	if (head->val == elem) {
		cout << "已存在，插入失败" << endl;
		return;
	}
}


TreeNode* findMin(TreeNode* head) {
	if (head) {
		while (head->left) {
			if (head->left) {
				head = head->left;
			}
		}
	}
	return head;
}

TreeNode* deleteNodeInSearchTree(TreeNode* &head, int elem) {
	TreeNode* temp = nullptr;
	if (!head) {
		cout << "没有此节点！" << endl;
	}
	else if (head->val > elem) {
		head->left = deleteNodeInSearchTree(head->left, elem);
	}
	else if (head->val < elem) {
		head->right = deleteNodeInSearchTree(head->right, elem);
	}
	else {
		//有两个子节点
		if (head->left && head->right) {
			temp = findMin(head->right);
			head->val = temp->val;
			head->right = deleteNodeInSearchTree(head->right, head->val);
		}
		else {
			temp = head;
			if (!head->left) {
				head = head->right;
			}
			else if (!head->right) {
				head = head->left;
			}
			delete temp;
		}
	}
	return head;
}

int main() {
	TreeNode* head;
	/*createTree(head);
	preorderUnRecur(head);
	preorderRecur(head);
	cout << endl;
	inorderUnRecur(head);
	inorderRecur(head);
	cout << endl;
	posorderReRecur(head);
	posorderRecur(head);
	cout << endl;
	levelOrderUnRecur(head);
	cout << treeDepth(head) << endl;
	cout << treeNodeNums(head) << endl;
	cout << treeLeftNums(head) << endl;
	vector<int> v;
	int len = 0;
	getAllPath(head,v,len);
	cout << treeNode_1_Nums(head) << endl;
	searchNode(head, 7);
	insertNode(head, 8);
	preorderUnRecur(head);*/
	TreeNode* phead = nullptr;
	createSearchTree(phead,5);
	createSearchTree(phead, 3);
	createSearchTree(phead, 1);
	createSearchTree(phead, 4);
	createSearchTree(phead, 6);
	createSearchTree(phead, 7);
	createSearchTree(phead, 9);
	createSearchTree(phead, 2);
	preorderUnRecur(phead);
	findNodeInSearchTree(phead, 8);
	findNodeInSearchTree(phead, 2);
	insertNodetoSearchTree(phead, 11);
	insertNodetoSearchTree(phead, 8);
	insertNodetoSearchTree(phead, 1);
	phead = deleteNodeInSearchTree(phead, 3);
	preorderUnRecur(phead);
	phead = deleteNodeInSearchTree(phead, 1);
	preorderUnRecur(phead);
	return 0;
}