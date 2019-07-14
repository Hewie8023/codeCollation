#include <iostream>
#include<vector>
#include<unordered_map>

using namespace std;

template<class T>
class Union_Find {
public:
	Union_Find() = default;
	Union_Find(vector<T> data) {//初始化
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

	T find_set(T node) {//查找一个元素的根节点
		T f = father[node];
		if (node != f) {
			node = f;
			f = find_set(f);
		}
		father[node] = f;//将沿途所有元素的父节点都改为根节点 //路径压缩
		return f;
	}


	bool isSame_set(T a, T b) { //返回两个元素是否是同一个集合
		return find_set(a) == find_set(b);
	}

	void union_set(T a, T b) {//合并两个集合
		T aHead = find_set(a);
		T bHead = find_set(b);
		if (aHead != bHead) {
			int aSize = size[aHead];
			int bSize = size[bHead];
			if (aSize > bSize) { //按秩合并
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
	unordered_map<T, T> father;  //key:子节点 ，value:根节点
	unordered_map<T, int> size; //某个节点所在集合的元素的个数

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