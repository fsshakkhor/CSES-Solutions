#include<bits/stdc++.h>

using namespace std;

class SegTreeRange
{
    public:
    vector<long long> tree, lazy;

    SegTreeRange(vector<int>&ara){
        int n = ara.size();
        initialize(n);

        for(int i = 0;i < n;i++){
            update(1,1,n,i + 1,i + 1,ara[i]);
        }
    }

    SegTreeRange(int n){
        initialize(n);
    }

    void initialize(int n){
        tree.resize(n * 4);
        lazy.resize(n * 4);
    }

    void propagate(int node,int start,int end){
        if(lazy[node] != 0){
            tree[node] += (end - start + 1) * lazy[node];
            if(start != end)
            {
                lazy[node*2] += lazy[node];
                lazy[node*2+1] += lazy[node];
            }
            lazy[node] = 0;
        }
    }

    // 1 indexed
    void update(int node, int start, int end, int l, int r, int val){
        propagate(node,start,end);
        if(start > end or start > r or end < l)return;
        if(start >= l and end <= r){
            tree[node] += (end - start + 1) * val;
            if(start != end)
            {
                lazy[node*2] += val;
                lazy[node*2+1] += val;
            }
            return;
        }

        int mid = (start + end) / 2;
        update(node*2, start, mid, l, r, val);
        update(node*2 + 1, mid + 1, end, l, r, val);
        tree[node] = tree[node*2] + tree[node*2+1];
    }

    long long query(int node, int start, int end, int l, int r){
        if(start > end or start > r or end < l)return 0;
        propagate(node,start,end);

        if(start >= l and end <= r){
            return tree[node];
        }

        int mid = (start + end) / 2;
        long long p1 = query(node*2, start, mid, l, r);
        long long p2 = query(node*2 + 1, mid + 1, end, l, r);
        return (p1 + p2);
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

    SegTreeRange segTreeRange(ara);

    while(q--){
        int type;
        cin >> type;

        if(type == 1){
            int pos , val;
            cin >> pos >> val;
            segTreeRange.update(1,1,n,pos,pos,val - ara[pos - 1]);
            ara[pos - 1] = val;
        }else{
            int l , r;
            cin >> l >> r;
            cout << segTreeRange.query(1,1,n,l,r) << "\n";
        }
    }
}

