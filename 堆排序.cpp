#include<bits/stdc++.h>
using namespace std;

void heapSort(vector<int>& arr);
void heapInsert(vector<int>& arr, int i);
void swap(vector<int>& arr, int i, int j);
void heapify(vector<int>& arr,int index, int heapSize);

int main() {
	int n;
	cin >> n;
	vector<int> arr(n);
	for (int i = 0; i < n; ++i) {
		cin >> arr[i];
	}
	heapSort(arr);
	for (int i = 0; i < arr.size(); ++i) {
		cout << arr[i] << " ";
	}
	cout << endl;
	return 0;
}

void heapSort(vector<int>& arr) {
	if (arr.size() < 2 || arr.empty()) {
		return;
	}
	for (int i = 0; i < arr.size(); ++i) {
		heapInsert(arr, i); //0~i之间形成大根堆；
	}
	int heapSize = arr.size();
	swap(arr, 0, --heapSize);
	while (heapSize > 0) {
		heapify(arr, 0, heapSize);
		swap(arr, 0, --heapSize);
	}
}

//往上调整
void heapInsert(vector<int>& arr, int i) {
	while (arr[i] > arr[(i - 1) / 2]) {
		swap(arr, i, (i - 1) / 2);
		i = (i - 1) / 2;
	}
}

void swap(vector<int>& arr, int i, int j) {
	int tmp = arr[i];
	arr[i] = arr[j];
	arr[j] = tmp;
}
//往下调整
void heapify(vector<int>& arr, int index, int heapSize) {
	int left = index * 2 + 1;
	while (left < heapSize) {//下方还有孩子的时候
		//两个孩子谁大，下标给largest
		int largest = left + 1 < heapSize && arr[left + 1] > arr[left] ? left + 1 : left;
		//父节点和孩子节点谁大，下标给largest
		largest = arr[largest] > arr[index] ? largest : index;
		if (largest == index) {
			break;
		}
		swap(arr, largest, index);
		index = largest;
		left = index * 2 + 1;
	}
}