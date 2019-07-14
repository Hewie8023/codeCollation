#include<iostream>
#include<vector>
using namespace std;

typedef int DataType;
typedef struct Heap {
	vector<DataType> arr;
	size_t size;
}Heap;

//���������
void HeapInsert(Heap &heap, int index);//����Ԫ��
void Heapify(Heap &heap, int index, int heapsize); //���¶�
void heapSort(Heap &heap);//������
int HeapTop(Heap &heap);//ȡ�Ѷ�Ԫ��
void HeapPop(Heap & heap);//ɾ���Ѷ�Ԫ��

//����С����
void HeapInsertSmall(Heap &heap, int index);
void HeapitySmall(Heap & heap, int index, int heapSize);
void HeapSortSmall(Heap &heap);

void swap(Heap &heap, int i, int j);

int main() {
	Heap heap;
	heap.size = 0;
	Heap heapS;
	heapS.size = 0;
	vector<int> v = { 10,8,12,2,15,20 };
	for (int i = 0; i < v.size(); ++i) {
		heap.arr.push_back(v[i]);
		heap.size++;
		HeapInsert(heap, i);
		heapS.arr.push_back(v[i]);
		heapS.size++;
		HeapInsertSmall(heapS, i);
	}
	for (int i = 0; i < heap.size; ++i) {
		cout << heap.arr[i] << " ";
	}
	cout << endl;
	/*heapSort(heap);
	for (int i = 0; i < heap.size; ++i) {
		cout << heap.arr[i] << " ";
	}
	cout << endl;*/
	cout << HeapTop(heap) << endl;
	HeapPop(heap);
	for (int i = 0; i < heap.size; ++i) {
		cout << heap.arr[i] << " ";
	}
	cout << endl;

	for (int i = 0; i < heapS.size; ++i) {
		cout << heapS.arr[i] << " ";
	}
	cout << endl;
	HeapSortSmall(heapS);
	for (int i = 0; i < heapS.size; ++i) {
		cout << heapS.arr[i] << " ";
	}
	cout << endl;

	return 0;
}

void swap(Heap &heap, int i, int j) {
	int temp = move(heap.arr[i]);
	heap.arr[i] = move(heap.arr[j]);
	heap.arr[j] = move(temp);
}

void HeapInsert(Heap &heap, int index) {
	//indexλ�����丸�ڵ��λ�ý��бȽ�

	while (heap.arr[index] > heap.arr[(index - 1) / 2]) {	
		swap(heap, index, (index - 1) / 2);
		index = (index - 1) / 2;
	}
}
void Heapify(Heap &heap, int index,int heapSize) {
	int left = index * 2 + 1;//��Ҷ�ڵ�
	while (left < heapSize) {
		int longest = left + 1 < heapSize && heap.arr[left + 1] > heap.arr[left] ? left + 1 : left;
		longest = heap.arr[longest] > heap.arr[index] ? longest : index;
		if (longest == index) break;
		swap(heap, longest, index);
		index = longest;
		left = index * 2 + 1;
	}
}

void heapSort(Heap &heap) {
	if (heap.size == 0) return;
	int heapSize = heap.size;
	swap(heap, 0, --heapSize);
	while (heapSize) {
		Heapify(heap, 0, heapSize);
		swap(heap, 0, --heapSize);
	}
}

int HeapTop(Heap & heap) {
	int val;
	if (heap.size == 0) {
		return 0;
	}
	val = heap.arr[0];
	return val;
}

/*
�����ж��Ƿ�Ϊ�նѣ����Ϊ�ն�ֱ�ӷ��أ����򽫶���Ԫ�����ĩԪ�ؽ��н�����
��size����--������Ȼ������ѵĽṹ��ʹ�仯��Ķ���������ѵĽṹ��
*/
void HeapPop(Heap& heap) {
	if (heap.size == 0) {
		return;
	}
	swap(heap, 0, heap.size - 1);
	int heapSize = --heap.size;
	Heapify(heap, 0, heapSize);
}

void HeapInsertSmall(Heap &heap, int index) {
	while (heap.arr[index] < heap.arr[(index - 1) / 2]) {
		swap(heap, index, (index - 1) / 2);
		index = (index - 1) / 2;
	}
}

void HeapitySmall(Heap &heap, int index, int heapSize) {
	int left = index * 2 + 1;
	while (left < heapSize) {
		int smallest = left + 1 < heapSize && heap.arr[left + 1] < heap.arr[left] ? left + 1 : left;
		smallest = heap.arr[smallest] < heap.arr[index] ? smallest : index;
		if (smallest == index) break;
		swap(heap, smallest, index);
		index = smallest;
		left = index * 2 + 1;
	}
}

void HeapSortSmall(Heap &heap) {
	if (heap.size == 0) return;
	int heapSize = heap.size;
	swap(heap, 0, --heapSize);
	while (heapSize) {
		HeapitySmall(heap, 0, heapSize);
		swap(heap, 0, --heapSize);
	}
}