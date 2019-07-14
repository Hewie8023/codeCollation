#include <iostream>
#include<vector>
#include<unordered_map>

using namespace std;

template<class T>
class Union_Find {
public:
	Union_Find() = default;
	Union_Find(vector<T> data) {//��ʼ��
		father.clear();
		size.clear();
		make_set(data);
	}

	void make_set(vector<T> data) {
		for (T var : data) {
			father.insert({ var,var });
			size.insert({ var,1 });
		}
	}

	T find_set(T node) {//����һ��Ԫ�صĸ��ڵ�
		T f = father[node];
		if (node != f) {
			node = f;
			f = find_set(f);
		}
		father[node] = f;//����;����Ԫ�صĸ��ڵ㶼��Ϊ���ڵ� //·��ѹ��
		return f;
	}


	bool isSame_set(T a, T b) { //��������Ԫ���Ƿ���ͬһ������
		return find_set(a) == find_set(b);
	}

	void union_set(T a, T b) {//�ϲ���������
		T aHead = find_set(a);
		T bHead = find_set(b);
		if (aHead != bHead) {
			int aSize = size[aHead];
			int bSize = size[bHead];
			if (aSize > bSize) { //���Ⱥϲ�
				father[b] = a;
				size[a] += size[b];
			}

			else {
				father[a] = b;
				size[b] += size[a];
			}
		}
	}

private:
	unordered_map<T, T> father;  //key:�ӽڵ� ��value:���ڵ�
	unordered_map<T, int> size; //ĳ���ڵ����ڼ��ϵ�Ԫ�صĸ���

};


int main() {
	vector<char> v1 = { 'A','B','C','D' };
	vector<char> v2 = { 'E','F','G' };
	Union_Find<char> uf1(v1);
	Union_Find<char> uf2(v2);
	uf1.union_set('A', 'B');
	cout << uf1.isSame_set('A','B') << endl;
	cout << uf1.isSame_set('A', 'C') << endl;
	return 0;
}