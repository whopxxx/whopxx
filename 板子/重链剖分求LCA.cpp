#include <bits/stdc++.h>
using namespace std;
const int N = 5000010;
vector<int>g[N];
int sz[N],fa[N],son[N],dep[N],top[N];

void dfs1(int u){
    sz[u] = 1;
    for(auto v: g[u]){
        if(v == fa[u])continue;
        fa[v] = u;
        dep[v] = dep[u] + 1;
        dfs1(v);
        sz[u] += sz[v];
        if(sz[v] > sz[son[u]]){
            son[u] = v;
        }
    }
}

void dfs2(int u,int h){
    top[u] = h;
    if(son[u])dfs2(son[u], h);
    for(auto v:g[u]){
        if(v == fa[u] || v == son[u])continue;
        dfs2(v, v);
    }
}

int lca(int x,int y){
    while(top[x] != top[y]){
        if(dep[top[x]] > dep[top[y]]){
            x = fa[top[x]];
        }
        else y = fa[top[y]];
    }
    return dep[x] < dep[y] ? x : y;
}

signed main(){
    int n, m, s;
    cin >> n >> m >> s;
    for(int i = 1; i < n; i++){
        int x,y;cin >> x >> y;
        g[x].push_back(y);
        g[y].push_back(x);
    }
    dfs1(s),dfs2(s, s);
    while(m--){
        int l,r;
        cin >> l >> r;
        cout << lca(l, r) << endl;
    }
    return 0;
}