#include<bits/stdc++.h>
using namespace std;
using namespace std::chrono;

const int MAX = 34292500; 
typedef pair<int, int> pp; //存放边末端和距离
list<pp> adj[MAX]; //邻接表，存储图的信息

class BinaryHeap{
    vector<pp> heap; //堆，存储距离和节点（一个线段的目标节点）
    vector<int> pos; //位置数组，存放每个节点在堆中的位置
public:
    BinaryHeap(int n){
        heap.resize(n+1);
        pos.resize(n+1);
    }
    bool empty(){
        return heap.size() == 1;
    }
    //添加元素 
    void push(pp p){
        heap.push_back(p);//先将元素添加到末尾
        int idx = heap.size()-1;
        pos[p.second] = idx; //获取并记录新元素的位置
        while(idx > 1 && heap[idx].first < heap[idx/2].first){
            swap(pos[heap[idx].second], pos[heap[idx/2].second]);//更新位置信息
            swap(heap[idx], heap[idx/2]); //更新堆元素信息
            idx /= 2;
        }
    }
    //删除元素
    int pop(){
		int min = heap[1].second;
		pos[heap.back().second] = 1; //更新堆中最后一个点的位置
        pos[heap[1].second] = 0; //删掉堆中第一个元素的位置
        heap[1] = heap.back(); //更新堆中的根元素
        heap.pop_back(); //删除最后一个元素
        int idx = 1;
        while(true){ //per_down
            int child = idx*2;
            if(child < heap.size() && heap[child].first > heap[child+1].first) //如果右孩子更小，则操作右孩子
                child++;
            if(child >= heap.size() || heap[idx].first <= heap[child].first)
                break;
            swap(pos[heap[idx].second], pos[heap[child].second]);
            swap(heap[idx], heap[child]);
            idx = child;
        }
		return min;
	}

    void decrease_key(int key, int node){
        int idx = pos[node]; //获取节点在堆中的位置
        heap[idx].first = key; //更新该节点的键值
        while(idx > 1 && heap[idx].first < heap[idx/2].first){ //per_up
            swap(pos[heap[idx].second], pos[heap[idx/2].second]);
            swap(heap[idx], heap[idx/2]);
            idx /= 2;
        }
    }
};


int dijkstra(int x, int y, int n)
{
	BinaryHeap Q(n);
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