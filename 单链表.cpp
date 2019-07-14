#include<iostream>
#include<vector>

using namespace std;
/**/
struct ListNode {
	int val;
	ListNode* next;
	ListNode(int x):val(x),next(NULL){}//列表初始化
};

ListNode* createList() {
	ListNode* head = new ListNode(0);
	ListNode* node = head;
	vector<int> nums = { 1,2,3 };
	for (int i = 0; i < nums.size(); ++i) {
		ListNode * temp = new ListNode(nums[i]);
		node->next = temp;
		node = temp;
	}
	node->next = nullptr;
	return head;
}

ListNode* insert(ListNode* head, int pos, int elem) {
	ListNode* temp = head;
	int i = 0;
	//首先找到插入节点的上一节点，即pos-1位置
	while ((temp->next != nullptr) && (i < pos - 1)) {
		temp = temp->next;
		++i;
	}
	if (!temp || i > pos - 1) {
		cout << "Insert False!" << endl;
		return temp;
	}
	ListNode* node = new ListNode(elem);
	node->next = temp->next;
	temp->next = node;
	return head;
}

void printList(ListNode* head) {
	ListNode* node = head;
	while (node->next) {
		node = node->next;
		cout << node->val << "   ";
	}
	cout << endl;
}

int searchNode(ListNode* head, int elem) {
	ListNode* node = head;
	int pos = 0;
	int i = 1;
	while (node->next) {
		node = node->next;
		if (elem == node->val) {
			pos = i;
			cout << "元素： " << elem << "  在链表中的位置是：" << pos << endl;
			return pos;
		}
		++i;
	}
	cout << "search eoor!" << endl;
	return -1;
}

ListNode* replaceNode(ListNode* head, int pos, int elem) {
	ListNode* node = head;
	node = node->next;
	for (int i = 1; i < pos; ++i) {
		node = node->next;
	}
	node->val = elem;
	return head;
}

ListNode* deleteNode(ListNode* head, int pos) {
	ListNode* node = head;
	int i = 0; 
	while (node->next && i < pos - 1) {
		node = node->next;
		++i;
	}
	if (!node || i > pos - 1) {
		cout << "delete false!" << endl;
		return node;
	}
	ListNode* del = node->next;
	node->next = del->next;
	delete del;
	del = nullptr;
	return head;
}

void clearList(ListNode* head) {
	ListNode* node = head;
	ListNode* temp;
	if (!head) {
		cout << "链表为空！" << endl;
	}
	while (node->next) {
		temp = node->next;
		delete node;
		node = temp;
	}
	delete node;
	delete temp;
	node = nullptr;
	temp = nullptr;
	head->next = nullptr;
	cout << "链表清空！" << endl;
}

void destoryList(ListNode* head) {
	
	if (!head) {
		cout << "链表为空！" << endl;
	}
	ListNode* node = nullptr;
	while (head->next) {
		node = head->next;
		delete head;
		head = node;
	}
	if (head) {
		delete head;
		head = nullptr;
	}
	cout << "链表销毁成功！" << endl;
	
}

int sizeList(ListNode* head) {
	int size = 0;
	ListNode* node = head;
	while(node->next) {
		++size;
		node = node->next;
	}
	cout << "链表的长度是： " << size << endl;
	return size;
}

bool isEmptyList(ListNode* head) {
	if (!head) {
		cout << "链表为空！" << endl;
		return true;
	}
	cout << "链表不为空！" << endl;
	return false;
}

int main() {


	ListNode* node = createList();
	printList(node);
	node = insert(node, 2, 5);
	printList(node);
	int index = searchNode(node, 3);
	node = replaceNode(node, 4, 7);
	printList(node);
	node = deleteNode(node, 3);
	printList(node);
	//clearList(node);
	//destoryList(node);
	int size = sizeList(node);
	if(!isEmptyList(node))
		printList(node);
	//cout << node->val << endl;
	return 0;
}