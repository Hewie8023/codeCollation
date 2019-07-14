#include<iostream>
#include<vector>
#include<queue>
#include<stack>

using  namespace std;

#define MAXV 100 //最大顶点个数
#define INF 32767       //INF表示∞
//邻接矩阵
typedef struct {
	int no;//顶点编号
	int info;//顶点其他信息，可存放带权图的权值
}VertexType; //顶点类型

typedef struct {
	int edges[MAXV][MAXV]; //邻接矩阵
	int n, e;//顶点数，边数
	VertexType vexs[MAXV];//顶点表
}MGraph;

//邻接表

//边表结点
typedef struct EdgeNode {
	int adjvex;//该弧的终点位置
	struct EdgeNode *nextarc;//指向下一条弧的指针
	int info;//该弧的相关信息，存放权值
}EdgeNode;
//顶点表节点
typedef int Vertex;
typedef struct VextexNode {
	Vertex data;//顶点信息
	int count; //顶点的入度
	bool visited;//表示该节点是否被访问
	EdgeNode *firstEdge;//指向第一条弧
}VextexNode,AdjList[MAXV];
//邻接表
typedef struct {
	AdjList adjList;//邻接表
	int n, e;//图中顶点数和边数
}ALGraph;

void arrayToMat(int *arr, int n, MGraph &g);//用普通数组构造图的邻接矩阵
void arrayToList(int* arr, int n, ALGraph &g);//用普通数组构造图的邻接表
void MatToList(MGraph g, ALGraph &G);//邻接矩阵转邻接表
void ListToMat(ALGraph G, MGraph &g);//邻接表转邻接矩阵

void dispMat(MGraph g);//输出邻接矩阵g
void dispAdj(ALGraph g);//输出邻接表

void initVisted(ALGraph &G);//初始化节点的访问
void BFS(ALGraph G, int start, vector<int> &v);//宽搜
void DFS(ALGraph G, int start, vector<int> &v);//深搜

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
	arrayToMat(A[0], 6, g1);//取二维数组的起始地址作实参，用A[0]，因其实质为一维数组地址，与形参匹配
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
	int i, j, count = 0;//count用于统计边数，即矩阵中非0元素的个数
	g.n = n;
	for (i = 0; i < g.n; ++i) {
		for (j = 0; j < g.n; ++j) {
			g.edges[i][j] = arr[i*n + j];//将Arr看作n×n的二维数组，Arr[i*n+j]即是Arr[i][j]，计算存储位置的功夫在此应用
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
	//输入顶点信息，将边表置为0
	for (i = 0; i < g.n; ++i) {
		g.adjList[i].data = i;
		g.adjList[i].firstEdge = nullptr;
	}
	//建立边表
	for (i = 0; i < n; ++i) {//检查邻接矩阵中每个元素
		for (j = n - 1; j >= 0; --j) {
			if (arr[i*n + j] != 0) {  //存在一条边，将Arr看作n×n的二维数组，Arr[i*n+j]即是Arr[i][j]
				ep = (EdgeNode*)malloc(sizeof(EdgeNode));//创建一个节点*ep
				ep->adjvex = j;
				ep->info = arr[i*n + j];
				ep->nextarc = g.adjList[i].firstEdge;//采用头插法插入*ep
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
				cout << "∞ ";
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
		ep = G.adjList[current].firstEdge;//ep指向头结点，遍历边表
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


