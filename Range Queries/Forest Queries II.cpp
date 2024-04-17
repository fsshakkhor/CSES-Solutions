#include<bits/stdc++.h>

using namespace std;

// 1 Indexed
class BIT2D{
public:
    int n;
    vector<vector<int>>bit;

    BIT2D(int sz){
        n = sz;
        for(int i = 0;i <= n;i++){
            bit.push_back(vector<int>());
            bit[i].resize(n + 1);
        }
    }

    void update(int x, int y, int val) {
        for (; x <= n; x += (x & (-x))) {
            for (int i = y; i <= n; i += (i & (-i))) { bit[x][i] += val; }
        }
    }

    int query(int x1, int y1, int x2, int y2) {
        int ans = 0;
        for (int i = x2; i; i -= (i & (-i))) {
            for (int j = y2; j; j -= (j & (-j))) { ans += bit[i][j]; }
        }
        for (int i = x2; i; i -= (i & (-i))) {
            for (int j = y1 - 1; j; j -= (j & (-j))) { ans -= bit[i][j]; }
        }
        for (int i = x1 - 1; i; i -= (i & (-i))) {
            for (int j = y2; j; j -= (j & (-j))) { ans -= bit[i][j]; }
        }
        for (int i = x1 - 1; i; i -= (i & (-i))) {
            for (int j = y1 - 1; j; j -= (j & (-j))) { ans += bit[i][j]; }
        }
        return ans;
    }
};

int main()
{
    int n , q;
    cin >> n >> q;

    BIT2D bit(n);

    string str[n];
    for(int i = 0;i < n;i++){
        cin >> str[i];
        for(int j = 0;j < n;j++){
            if(str[i][j] == '*'){
                bit.update(i + 1,j + 1,1);
            }
        }
    }

    while(q--){
        int type;
        cin >> type;

        if(type == 1){
            int x , y;
            cin >> x >> y;
            if(bit.query(x,y,x,y)){
                bit.update(x,y,-1);
            }else{
                bit.update(x,y,1);
            }
        }else{
            int x1, y1, x2, y2;
            cin >> x1 >> y1 >> x2 >> y2;
            cout << bit.query(x1,y1,x2,y2) << "\n";
        }

    }
}

