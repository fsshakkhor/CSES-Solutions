#include<bits/stdc++.h>

using namespace std;

class SegTree
{
    public:
    vector<long long> tree;

    SegTree(vector<int>&ara){
        int n = ara.size();
        initialize(n);

        for(int i = 0;i < n;i++){
            update(1,1,n,i + 1,ara[i]);
        }
    }

    SegTree(int n){
        initialize(n);
    }

    void initialize(int n){
        tree.resize(n * 4);
    }

    void update(int node, int start, int end, int pos, int val){
        if(start > end or pos > end or pos < start)return;
        if(pos == start and pos == end){
            tree[node] = val;
            return;
        }

        int mid = (start + end) / 2;
        update(node*2, start, mid, pos, val);
        update(node*2 + 1, mid + 1, end, pos, val);
        tree[node] = min(tree[node*2] , tree[node*2+1]);
    }

    long long query(int node, int start, int end, int l, int r){
        if(start > end or l > end or r < start)return INT_MAX;

        if(start >= l and end <= r){
            return tree[node];
        }

        int mid = (start + end) / 2;
        long long p1 = query(node*2, start, mid, l, r);
        long long p2 = query(node*2 + 1, mid + 1, end, l, r);
        return min(p1 , p2);
    }
};

int main()
{
    int n , q;
    cin >> n >> q;

    vector<int>ara(n);
    for(int i = 0;i < n;i++){
        cin >> ara[i];
    }

    SegTree segTree(ara);

    while(q--){
        int l , r;
        cin >> l >> r;
        cout << segTree.query(1,1,n,l,r) << "\n";
    }
}

