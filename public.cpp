#include <iostream>
using namespace std;
int n;
const int N = 16;
int st[N];//判断位的数是否选中,0表示未考虑，1表示选中，2表示未选中
//u表示当前选到第几个数->对应二叉树的第几层
void dfs(int u) {
    if (u == n) {
        for (int i = 0; i < n; ++i) {
            if (st[i] == 1) {
                cout << i + 1 << " ";
            }
        }
        cout << endl;
        return; 
    }
    //遍历可能出现的分支
    for (int i = 1; i <= 2; ++i) {
        st[u] = i;
        dfs(u + 1);
        //恢复
        st[u] = 0;
    }

}

int main2() {
    
    cin >> n;
    dfs(0);
    return 0;
}
