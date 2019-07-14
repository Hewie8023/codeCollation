#include <iostream>
#include<vector>

using namespace std;

struct ListNode {
	int val;
	struct ListNode *pre;
	struct ListNode *next;
	ListNode(int x) :
		val(x), pre(nullptr), next(nullptr) {
	}
}; 

ListNode* createList() {
	ListNode* head = new ListNode(-1);
	ListNode* node = head;
	vector<int> nums = { 1,2,3 };
	for (int i = 0; i < nums.size(); ++i) {
		ListNode* temp = new ListNode(nums[i]);
		node->next = temp;
		temp->pre = node;
		node = node->next;
	}
	return head;
}

ListNode* insertNode(ListNode* head, int pos, int elem) {
	ListNode* node = head;
	int i = 0;
	while (node->next && i < pos - 1) {
		node = node->next;
		++i;
	}
	if (!node || i > pos - 1) {
		cout << "²åÈëÊ§°Ü£¡" << endl;
		return node;
	}
	ListNode* temp = new ListNode(elem);
	node->next->pre = temp;
	temp->next = node->next;
	node->next = temp;
	temp->pre = node;
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
		cout << "É¾³ýÊ§°Ü£¡" << endl;
		return head;
	}
	ListNode* del = node->next;
	node->next = del->next;
	del->next->pre = node;
	delete del;
	del = nullptr;
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

int main()
{
	ListNode* node = createList();
	printList(node);
	node = insertNode(node, 2, 8);
	printList(node);
	node = deleteNode(node, 2);
	printList(node);
	return 0;
}