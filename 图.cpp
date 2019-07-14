#include<iostream>
#include<vector>
#include<queue>
#include<stack>

using  namespace std;

#define MAXV 100 //��󶥵����
#define INF 32767       //INF��ʾ��
//�ڽӾ���
typedef struct {
	int no;//������
	int info;//����������Ϣ���ɴ�Ŵ�Ȩͼ��Ȩֵ
}VertexType; //��������

typedef struct {
	int edges[MAXV][MAXV]; //�ڽӾ���
	int n, e;//������������
	VertexType vexs[MAXV];//�����
}MGraph;

//�ڽӱ�

//�߱���
typedef struct EdgeNode {
	int adjvex;//�û����յ�λ��
	struct EdgeNode *nextarc;//ָ����һ������ָ��
	int info;//�û��������Ϣ�����Ȩֵ
}EdgeNode;
//�����ڵ�
typedef int Vertex;
typedef struct VextexNode {
	Vertex data;//������Ϣ
	int count; //��������
	bool visited;//��ʾ�ýڵ��Ƿ񱻷���
	EdgeNode *firstEdge;//ָ���һ����
}VextexNode,AdjList[MAXV];
//�ڽӱ�
typedef struct {
	AdjList adjList;//�ڽӱ�
	int n, e;//ͼ�ж������ͱ���
}ALGraph;

void arrayToMat(int *arr, int n, MGraph &g);//����ͨ���鹹��ͼ���ڽӾ���
void arrayToList(int* arr, int n, ALGraph &g);//����ͨ���鹹��ͼ���ڽӱ�
void MatToList(MGraph g, ALGraph &G);//�ڽӾ���ת�ڽӱ�
void ListToMat(ALGraph G, MGraph &g);//�ڽӱ�ת�ڽӾ���

void dispMat(MGraph g);//����ڽӾ���g
void dispAdj(ALGraph g);//����ڽӱ�

void initVisted(ALGraph &G);//��ʼ���ڵ�ķ���
void BFS(ALGraph G, int start, vector<int> &v);//����
void DFS(ALGraph G, int start, vector<int> &v);//����

int main() {
	MGraph g1,g2;
	ALGraph G1, G2;
	int A[6][6] = {
		{ 0,5,0,7,0,0 },
		{ 0,0,4,0,0,0 },
		{ 8,0,0,0,0,9 },
		{ 0,0,5,0,0,6 },
		{ 0,0,0,5,0,0 },
		{ 3,0,0,0,1,0 }
	};
	arrayToMat(A[0], 6, g1);//ȡ��ά�������ʼ��ַ��ʵ�Σ���A[0]������ʵ��Ϊһά�����ַ�����β�ƥ��
	dispMat(g1);
	arrayToList(A[0], 6, G1);
	dispAdj(G1);
	MatToList(g1, G2);
	dispAdj(G2);
	ListToMat(G1, g2);
	dispMat(g2);

	initVisted(G1);
	vector<int> v;
	BFS(G1, 0, v);
	for (int i = 0; i < v.size(); ++i) {
		cout << v[i] << " ";
	}
	cout << endl;

	initVisted(G1);
	vector<int> v1;
	DFS(G1, 0, v1);
	for (int i = 0; i < v1.size(); ++i) {
		cout << v1[i] << " ";
	}
	cout << endl;

	return 0;

}


void arrayToMat(int *arr, int n, MGraph &g) {
	int i, j, count = 0;//count����ͳ�Ʊ������������з�0Ԫ�صĸ���
	g.n = n;
	for (i = 0; i < g.n; ++i) {
		for (j = 0; j < g.n; ++j) {
			g.edges[i][j] = arr[i*n + j];//��Arr����n��n�Ķ�ά���飬Arr[i*n+j]����Arr[i][j]������洢λ�õĹ����ڴ�Ӧ��
			if (g.edges[i][j] != 0 && g.edges[i][j] != INF) {
				++count;
			}
		}
	}
	g.e = count;
}
void arrayToList(int* arr, int n, ALGraph &g) {
	int i, j, count = 0;
	g.n = n;
	EdgeNode *ep;
	//���붥����Ϣ�����߱���Ϊ0
	for (i = 0; i < g.n; ++i) {
		g.adjList[i].data = i;
		g.adjList[i].firstEdge = nullptr;
	}
	//�����߱�
	for (i = 0; i < n; ++i) {//����ڽӾ�����ÿ��Ԫ��
		for (j = n - 1; j >= 0; --j) {
			if (arr[i*n + j] != 0) {  //����һ���ߣ���Arr����n��n�Ķ�ά���飬Arr[i*n+j]����Arr[i][j]
				ep = (EdgeNode*)malloc(sizeof(EdgeNode));//����һ���ڵ�*ep
				ep->adjvex = j;
				ep->info = arr[i*n + j];
				ep->nextarc = g.adjList[i].firstEdge;//����ͷ�巨����*ep
				g.adjList[i].firstEdge = ep;
				++count;
			}
		}
	}
	g.e = count;
}

void MatToList(MGraph g, ALGraph &G) {
	int i, j;
	EdgeNode* ep;
	for (i = 0; i < g.n; ++i) {
		G.adjList[i].firstEdge = nullptr;
	}
	for (i = 0; i < g.n; ++i) {
		for (j = g.n - 1; j >= 0; --j) {
			if (g.edges[i][j] != 0) {
				ep = (EdgeNode*)malloc(sizeof(EdgeNode));
				ep->adjvex = j;
				ep->info = g.edges[i][j];
				ep->nextarc = G.adjList[i].firstEdge;
				G.adjList[i].firstEdge = ep;
			}
		}
	}
	G.n = g.n;
	G.e = g.e;
}

void ListToMat(ALGraph G, MGraph &g) {
	int i, j;
	EdgeNode *ep;
	g.n = G.n;
	g.e = G.e;
	for (i = 0; i < G.n; ++i) {
		for (j = 0; j < G.n; ++j) {
			g.edges[i][j] = 0;
		}
	}
	for (i = 0; i < G.n; ++i) {
		ep = G.adjList[i].firstEdge;
		while (ep) {
			g.edges[i][ep->adjvex] = ep->info;
			ep = ep->nextarc;
		}
	}
}

void dispMat(MGraph g) {
	int i, j;
	for (i = 0; i < g.n; ++i) {
		for (j = 0; j < g.n; ++j) {
			if (g.edges[i][j] == INF) {
				cout << "�� ";
			}
			else {
				cout << g.edges[i][j] << " ";
			}
		}
		cout << endl;
	}
}

void dispAdj(ALGraph g) {
	int i;
	EdgeNode* ep;
	for (i = 0; i < g.n; ++i) {
		ep = g.adjList[i].firstEdge;
		cout << i << ":";
		while (ep) {
			cout << "->" << ep->adjvex << "/" << ep->info;
			ep = ep->nextarc;
		}
		cout << endl;
	}
}

void initVisted(ALGraph &G) {
	for (int i = 0; i < G.n; ++i) {
		G.adjList[i].visited = 0;
	}
}


void BFS(ALGraph G, int start, vector<int>& v) {
	queue<int> q;
	q.push(start);
	G.adjList[start].visited = 1;
	
	while (!q.empty()) {
		int current = q.front();
		q.pop();
		v.push_back(current);
		EdgeNode *ep;
		ep = (EdgeNode*)malloc(sizeof(EdgeNode));
		ep = G.adjList[current].firstEdge;//epָ��ͷ��㣬�����߱�
		while (ep) {
			if (!G.adjList[ep->adjvex].visited) {
				q.push(ep->adjvex);
				G.adjList[ep->adjvex].visited = 1;
			}
			ep = ep->nextarc;
		}
	}
}

void DFS(ALGraph G, int start, vector<int>& v) {
	stack<int> s;
	s.push(start);
	G.adjList[start].visited = 1;
	v.push_back(start);
	while (!s.empty()) {
		int current = s.top();
		s.pop();
		EdgeNode *ep;
		ep = (EdgeNode*)malloc(sizeof(EdgeNode));
		ep = G.adjList[current].firstEdge;
		while (ep) {
			if (!G.adjList[ep->adjvex].visited) {
				s.push(current);
				s.push(ep->adjvex);
				G.adjList[ep->adjvex].visited = 1;
				v.push_back(ep->adjvex);
				break;
			}
			ep = ep->nextarc;
		}
	}
}


