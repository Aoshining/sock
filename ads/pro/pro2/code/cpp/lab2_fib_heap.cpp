#include<bits/stdc++.h>
using namespace std;
using namespace std::chrono;

const int MAX = 34292500; 
typedef pair<int, int> pp; //存放边末端和距离
list<pp> adj[MAX]; //邻接表，存储图的信息

class FibHeap{
public:
	class Node{
	public:
		Node *parent;//父节点
		Node *child;//子节点
		Node *left;//左兄弟节点
		Node *right;//右兄弟节点
		int degree;//度
		bool marked;//标记是否失去过子节点
		int dist;//距离源节点的距离
		int vert;//节点编号
		Node(pp p) : parent(NULL), child(NULL), left(this), right(this), degree(0), marked(false), dist(p.first), vert(p.second) {
			Dest[vert] = this;
		}
	};

	FibHeap(int n) : min(NULL), Degree(log(n)/log(2))//根据二项堆的性质可知根链表中最多不超过log(n)个根节点
	{}

	void push(pp p)
	{
		Node *newnode = new Node(p);
		if(min)//若已有最小根节点则将新节点插入根链表中（以下插入均默认插在右侧）
		{
			newnode->left = min;
			newnode->right = min->right;
			min->right->left = newnode;
			min->right = newnode;
			if(newnode->dist < min->dist)
				min = newnode;
		}
		else//若无最小根节点则将新节点设为最小根节点
			min = newnode;
	}

	int pop()
	{
		int minvert = min->vert;
		if (min->child) //若有子节点则将所有子节点连至根链表中
		{
			//断绝最小根节点的所有子节点与其的联系
			Node *child = min->child;
			child->parent = NULL;
			child->marked = false;
			child = child->right;
			while(child != min->child)
			{
				child->parent = NULL;
				child->marked = false;
				child = child->right;
			}
			//若定义子节点是子链表中最左侧的节点，则子节点的左兄弟是子链表中最右侧的节点，从而实现将整个子链表插入到根链表中
			child->left->right = min->right;
			min->right->left = child->left;
			child->left = min;
			min->right = child;
		}
		if (min->right == min)//若根链表中只存在最小节点则直接将最小节点设置为空，完成删除
			min = NULL;
		else
		{
			// 将根链表中所有度相同的节点合并
			Node *root = min->right;
			while (root != min)
			{
				Node *combine = Degree[root->degree];//与当前根节点度相同的、待合并的结点
				Node *next = root->right;
				while(combine)//直至无待结合的节点
				{
					if (combine->dist < root->dist)
						swap(combine, root);//保证root结点作为结合后的父节点
					//使待合并的结点从根链表中脱离
					combine->left->right = combine->right;
					combine->right->left = combine->left;
					if(root->child)//若root节点有子节点则将combine节点插入到子链表中
					{
						combine->left = root->child;
						combine->right = root->child->right;
						root->child->right->left = combine;
						root->child->right = combine;
					}
					else//若root节点无子节点则设置combine节点为其唯一子节点
						root->child = combine->left = combine->right = combine;
					Degree[root->degree] = NULL;
					if(++root->degree>Degree.size())//更新root节点的度，并检查是否需要对待结合节点vector扩容
						Degree.resize(2 * Degree.size());
					combine->parent = root;
					combine->marked = false;
					combine = Degree[root->degree];//更新待结合的节点
				}
				Degree[root->degree] = root;//记录此度下的根节点
				root = next;
			}
			//寻找新的最小距离节点
			Node *newmin = root = min->right;
			while (root != min)
			{
				if(newmin->dist>root->dist)
					newmin = root;
				Degree[root->degree] = NULL;//清空待结合节点vector
				root = root->right;
			}
			//删除原最小距离节点并更新最小节点
			min->left->right = min->right;
			min->right->left = min->left;
			delete min;
			min = newmin;
		}
		return minvert;
	}

	void decrease_key(int dist, int vert)
	{
		Node *dest = Dest[vert];//根据map映射找到当前序号地点对应的节点
		dest->dist = dist;
		if (dest->parent && dest->parent->dist > dist)
		{
			Node *parent = dest->parent;
			cut(dest);//将被减小节点剪切至根链表中
			cascading_cut(parent);//根据marked标记有无对被减小节点的父节点进行级联剪切
			if (dest->dist < min->dist)//检查是否需要更新最小根节点
				min = dest;
		}
	}

	bool empty()
	{
		return min == NULL;
	}

private:
	vector<Node *> Degree;//根链表中根据度的多少划分根节点
	static map<int, Node *> Dest;//将地点序号与节点一一对应
	Node *min;//指向堆中距源节点最小距离的根节点（后续注释简称“最小根节点”）

	void cut(Node *node)
	{
		if (--node->parent->degree == 0)//若父节点只有一个子节点则将子节点设为空
			node->parent->child = NULL;
		else//若父节点有不止一个孩子则将被减小节点从子链表中移除
		{
			node->parent->child = node->right;
			node->left->right = node->right;
			node->right->left = node->left;
		}
		node->marked = false;
		node->parent = NULL;
		//剪切至根链表
		node->right = min->right;
		min->right->left = node;
		node->left = min;
		min->right = node;
	}

	void cascading_cut(Node *node)
	{
		if(node->parent)//若父节点还未被标记则此时标记
		{
			if(node->marked == false)
				node->marked = true;
			else//若父节点已经被标记为true则进行级联剪切
			{
				Node *parent = node->parent;
				cut(node);
				cascading_cut(parent);
			}
		}
	}
};

map<int, FibHeap::Node *> FibHeap::Dest;

int dijkstra(int x, int y, int n)
{
    FibHeap Q(n);
	vector<int> dist(MAX, INT_MAX);
	Q.push(make_pair(0, x)); //将源节点添加到堆中，则与自己的距离为0
	dist[x] = 0; //更新源节点的distance

    while(!Q.empty()){
        int u = Q.pop(); //获取堆顶元素，即当前最短路径最短的节点
        if(u == y)
            return dist[u]; //找到到达目的地的最短距离
        //遍历该节点的所有邻居节点
        for(auto &c : adj[u]){
            int v = c.first; //邻居节点
            int w = c.second; //边权重
            if(dist[u] + w < dist[v]){
                if(dist[v] == INT_MAX){//如果该节点未被访问过，则将其添加到堆中
                    dist[v] = dist[u] + w;
                    Q.push(make_pair(dist[v], v));
                }
                else{ //否则直接更新键值
                    dist[v] = dist[u] + w;
                    Q.decrease_key(dist[v], v);
                }
            }
        }
    }
	return -1;
}

int main()
{
    int nodes, edges;
	string f;
	cin >> f;
	ifstream file(f);
	string backet;
	string backet2, backet3;
	getline(file, backet);
	getline(file, backet);
	getline(file, backet);
	getline(file, backet);
    file >> backet2 >> backet3 >> nodes >> edges;
	file >> backet;
	getline(file, backet);
	getline(file, backet);
    for(int i = 0; i < edges; i++){
        string a;
        int x, y, w;
        file >> a >> x >> y >> w;
        adj[x].push_back(make_pair(y, w));
    }

    /*计算程序耗时*/
    // 获取开始时间
    auto start = high_resolution_clock::now();
	srand(time(0));
    for(int i = 0; i < 1000; i++){
		//int rand_sour = rand() % nodes + 1;//随机起始点
		int rand_dest = rand() % nodes + 1;//随机目的点
		dijkstra(1, rand_dest, nodes);
		if(i == 10 || i == 100 || i == 300 || i == 500 || i == 800)
			cout << i << endl;
	}
    // 获取结束时间
    auto stop = high_resolution_clock::now();
    // 计算运行时间
    auto duration_total = duration_cast<microseconds>(stop - start);
    double duration = double(duration_total.count())/1000;
    cout << "For <" << f << ">, " << "time taken by function: "
         << duration/1000000 << " s" << endl;
    /*end*/

    return 0;
}