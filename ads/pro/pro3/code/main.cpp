#include <iostream>
#include <vector>
#include <utility>
#include <ctime>
#include <algorithm>

//测试重复次数
#define TIME 1000


using namespace std;

struct Node{
    int degree; //度数
    vector<pair<int, int>> xy; //相连点的坐标
    int count; //目前相连点的个数
};

// 定义四个方向
int dx[4] = {-1, 0, 1, 0};
int dy[4] = {0, 1, 0, -1};

// 定义地图和访问标记
vector<vector<Node>> map;
vector<vector<bool>> visited; //count == degree
vector<vector<int>> solution;

// 判断是否在地图内
bool inMap(int x, int y, int n, int m) {
    return x >= 0 && x < n && y >= 0 && y < m;
}

// 回溯函数
bool backtrack(int x, int y, int n, int m) {
    if (x == n) {
        return true;
    }
    if (y == m) {
        return backtrack(x + 1, 0, n, m);
    }

    //degree == -1指当前位置是篱笆
    if (map[x][y].degree == 0 || visited[x][y] || map[x][y].degree == -1) {
        return backtrack(x, y + 1, n, m);
    }
    for (int i = 1; i < 16; i++) {
        //以下四个if判断为剪枝1
        if(map[x][y].degree-map[x][y].count == 1){
            if(!(i == 0b0001 || i == 0b0010 || i == 0b0100 || i == 0b1000))
                continue;
        }
        else if(map[x][y].degree-map[x][y].count == 2){
            if(!(i == 0b0011 || i == 0b0110 || i == 0b1100 || i == 0b0101 || i == 0b1010 || i == 0b1001))
                continue;
        }
        else if(map[x][y].degree-map[x][y].count == 3){
            if(!(i == 0b0111 || i == 0b1110 || i == 0b1101 || i == 0b1011))
                continue;
        }
        else if(map[x][y].degree-map[x][y].count == 4){
            if(!(i == 0b1111))
                continue;
        }
        //剪枝1结束
        int cnt = 0;
        int nx, ny;
        for (int j = 0; j < 4; j++) {
            nx = x + dx[j];
            ny = y + dy[j];
            int flag = 0;
            if ((i >> j) & 1) {
                while(1){
                    if (!inMap(nx, ny, n, m) || visited[nx][ny] || map[nx][ny].degree == -1) {
                        pair<int, int> pp = {nx, ny};
                        //看看该点是不是自己连着的
                        if(inMap(nx, ny, n, m) && visited[nx][ny] && find(map[x][y].xy.begin(), map[x][y].xy.end(), pp) != map[x][y].xy.end()){
                            break;
                        }
                        flag = 1;
                        break;
                    }
                    //如果遇到普通道路，继续沿着当前方向走
                    if(map[nx][ny].degree == 0){
                        switch(j){
                            case 0: nx--; break;
                            case 1: ny++; break;
                            case 2: nx++; break;
                            case 3: ny--; break;
                        }
                    }
                    else if(map[nx][ny].degree != 0 && map[nx][ny].degree > map[nx][ny].count){
                        cnt++;
                        pair<int, int> pp = {nx, ny};
                        auto& xy_vec = map[x][y].xy;

                        if (std::find(xy_vec.begin(), xy_vec.end(), pp) == xy_vec.end()) {
                            // 如果pp不存在于xy_vec中，则插入新元素
                            xy_vec.push_back(pp);
                            map[x][y].count++;
                            map[nx][ny].count++;
                        }
                        break;
                    }
                }
            }
            if(flag == 1)
                break;
            if (map[x][y].count == map[x][y].degree) {
                break;
            }
        }
        //剪枝2
        if (map[x][y].count != map[x][y].degree) {
            //将当次新建的联系清除
            for(int k = 0; k < cnt; k++){
                int nx = map[x][y].xy.back().first;
                int ny = map[x][y].xy.back().second;
                map[nx][ny].count--;
                map[x][y].count--;
                map[x][y].xy.pop_back();
            }
            continue;
        }
        //剪枝2结束
        visited[x][y] = true;
        for(int k = 0; k < map[x][y].xy.size(); k++){
            int nx = map[x][y].xy[k].first;
            int ny = map[x][y].xy[k].second;
            //下面两个if为设置篱笆
            if(nx == x){
                int start = min(y, ny)+1;
                int end = max(y, ny)-1;
                for(int q = start; q <= end; q++){
                    map[x][q].degree = -1;
                }
            }
            if(ny == y){
                int start = min(x, nx)+1;
                int end = max(x, nx)-1;
                for(int q = start; q <= end; q++){
                    map[q][y].degree = -1;
                }
            }
            pair<int, int> pp = {x, y};
            auto it = find(map[nx][ny].xy.begin(), map[nx][ny].xy.end(), pp);
            if(it == map[nx][ny].xy.end()){
                map[nx][ny].xy.push_back({x, y});
            }
            if(map[nx][ny].count == map[nx][ny].degree){
                visited[nx][ny] = true;
            }
        }
        solution[x][y] = i;
        //递归
        if (backtrack(x, y + 1, n, m)) {
            return true;
        }
        //回溯回来后清楚当前点右侧和下侧的联系
        visited[x][y] = false;
        vector<int> idx;
        for(int k = 0; k < map[x][y].xy.size(); k++){
            int nx = map[x][y].xy[k].first;
            int ny = map[x][y].xy[k].second;
            if(nx >= x && ny >= y){
                map[x][y].count--;
                solution[x][y] = -1;
                idx.push_back(k);
                map[nx][ny].count--;
                solution[nx][ny] = -1;
                visited[nx][ny] = false;
                
                pair<int, int> pp = {x, y};
                auto it = find(map[nx][ny].xy.begin(), map[nx][ny].xy.end(), pp);
                if(it != map[nx][ny].xy.end()){
                    map[nx][ny].xy.erase(it);
                }
                if(nx == x){
                    int start = min(y, ny)+1;
                    int end = max(y, ny)-1;
                    for(int q = start; q <= end; q++){
                        map[x][q].degree = 0;
                    }
                }
                if(ny == y){
                    int start = min(x, nx)+1;
                    int end = max(x, nx)-1;
                    for(int q = start; q <= end; q++){
                        map[q][y].degree = 0;
                    }
                }
            }
        }
        while(!idx.empty()){
            int d = idx.back();
            map[x][y].xy.erase(map[x][y].xy.begin()+d);
            idx.pop_back();
        }
        // map[x][y].count = 0;
        // solution[x][y] = -1;
        //i = 0;
    }
    return false;
}

int main() {
    int n, m;
    cin >> n >> m;
    int sum = 0;
    map = vector<vector<Node>>(n, vector<Node>(m));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> map[i][j].degree;
            map[i][j].count = 0;
            sum += map[i][j].degree;
        }
    }
    //如果sum of degree是偶数，继续处理
    if(sum % 2 == 0){
        double init_time = 0;
        //总时间
        clock_t begin = clock();
        bool has_sol;
        for(int i = 0; i < TIME; i++){
            visited = vector<vector<bool>>(n, vector<bool>(m, false));
            solution = vector<vector<int>>(n, vector<int>(m, -1));
            //记录非算法操作时间，最后要扣除
            clock_t b = clock();
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < m; j++) {
                    map[i][j].count = 0;
                    map[i][j].xy.clear();
                    if(map[i][j].degree < 0)
                        map[i][j].degree = 0;
                }
            }
            clock_t e = clock();
            init_time += (e-b);
            has_sol = backtrack(0, 0, n, m);
        }
        clock_t end = clock();
        double during = (end - begin - init_time) * 1.0 / TIME;
        cout << endl;
        cout << "average time" << endl << during << " ms" << endl;
        cout << endl;
        if (has_sol) {
            cout << "a solution" << endl;
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < m; j++) {
                    if (map[i][j].degree > 0) {
                        cout << i + 1 << " " << j + 1 << " ";
                        solution[i][j] = 0;
                        for(int q = 0; q < map[i][j].xy.size(); q++){
                            int nx = map[i][j].xy[q].first;
                            int ny = map[i][j].xy[q].second;
                            if(nx == i){
                                if(ny > j) 
                                    solution[i][j] |= 0b0010;
                                if(ny < j) 
                                    solution[i][j] |= 0b1000;
                            }
                            if(ny == j){
                                if(nx < i) 
                                    solution[i][j] |= 0b0001;
                                if(nx > i) 
                                    solution[i][j] |= 0b0100;
                            }
                        }
                        for (int k = 0; k < 4; k++) {
                            int dir;
                            if(k == 0) dir = 0;
                            if(k == 1) dir = 2;
                            if(k == 2) dir = 3;
                            if(k == 3) dir = 1;
                            cout << ((solution[i][j] >> dir) & 1) << " ";
                        }
                        cout << endl;
                    }
                }
            }
        } else {
            cout << "No Solution" << endl;
        }
    }
    else{
        cout << "No Solution" << endl;
    }
    return 0;
}
