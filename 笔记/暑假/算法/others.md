1. 快排求第k小的数
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 5000010;
int a[N];
int whp(int l,int r,int k){ 
    if(l == r)return a[l];
    int i = l - 1, j = r + 1, x = a[(l + r) >> 1];
    while(i < j){
        do i++; while(a[i] < x);
        do j--; while(a[j] > x);
        if(i < j)swap(a[i],a[j]);
    }
    if(k <= j)return whp(l,j,k);
    else return whp(j + 1,r,k);
}
void solve(){
    int n,k;
    scanf("%d%d",&n,&k);
    k++;
    for(int i = 1; i <= n; i++){
        scanf("%d",&a[i]);
    }
    cout << whp(1,n,k) << endl;
}
int main(){
    int _;
    _ = 1;
    //cin >> _;
    while(_--){
        solve();
    }
    return 0;
}
```
2. 对顶对(维护第k数)
```cpp
// 对顶堆
#include "bits/stdc++.h"
using namespace std;
void solve(){
    int n;
    cin >> n;
    priority_queue<int, vector<int>>a;
    priority_queue<int, vector<int>, greater<int>>b;
    for(int i = 1; i <= n; i++){
        int x;cin >> x;
        b.push(x);
    }
    int t = n/2;
    while(b.size() > t)a.push(b.top()), b.pop();
    int q;cin >> q;
    while(q--){
        string s;cin >> s;
        if(s[0] == 'm'){
            if((a.size() + b.size()) & 1){
                cout << a.top() << endl;
            }
            else cout << min(a.top(), b.top()) << endl;
        }
        else {
            int x;cin >> x;
            if(x > b.top())b.push(x);
            else a.push(x);
            int t = (a.size() + b.size())/2;
            while(b.size() > t)a.push(b.top()), b.pop();
            while(b.size() < t)b.push(a.top()),a.pop();
        }
    }
}
int main(){
    int _;
    _ = 1;
    // cin >> _;
    while(_ --){
        solve();
    }
    return 0;
}
```
3. 逆序对(归并排序)
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e6;
const int mod = 10000;
int n,k;
int a[N];
int tmp[N];
ll ans;
void memrge_sort(int l,int r){
    if(l == r)return;
    int mid = l + r >> 1;
    memrge_sort(l,mid),memrge_sort(mid + 1,r);
    int i = l ,j = mid + 1,k = l;
    while(i <= mid && j <= r){
        if(a[i] < a[j])tmp[k++] = a[i++];
        else tmp[k++] = a[j++],ans = ans + mid - i + 1; 
    }
    while(i <= mid)tmp[k++] = a[i++];
    while(j <= r)tmp[k++] = a[j++];
    for(int i = l; i <= r; i++)a[i] = tmp[i];
}

int main(){
    int _;
    cin >> _;
    while(_--){
        ans = 0;
        cin >> n;
        for(int i = 1;i <= n ;i++){
            cin >> a[i];
        }
        memrge_sort(1,n);
        cout << ans << endl;
    }
    return 0;
}
```
4. 带权并查集1(食物链)
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 100010;

int f[N],d[N];
void init(int n){
    for(int i = 1; i <= n; i++)f[i] = i;
}
int find(int x){
    if(x != f[x]){
        int root = find(f[x]);
        d[x] += d[f[x]];
        f[x] = root;
    }
    return f[x];
}

int n,m;
int main(){
    cin >> n >> m;
    init(n);
    int ans = 0;
    for(int i = 1; i <= m ; i++){
        int op,a,b;
        cin >> op >> a >> b;
        if(a > n || b > n){
            ans++;continue;
        }
        int fa = find(a),fb = find(b);
        if(op == 1){
            if(fa == fb && (d[a] - d[b]) % 3){
                ans++;
            }
            else if(fa != fb){
                f[fa] = fb;
                d[fa] = d[b] - d[a];
            }
            
        }
        else{
            if(fa == fb && (d[a] - d[b] - 1) % 3){
                ans++;
            }
            else if(fa != fb){
                f[fa] = fb;
                d[fa] = d[b] - d[a] + 1;
            }
        }
    }
    cout << ans << endl;
    return 0;
}
```

6. 带权并查集2(cf div4 886 H)
```cpp
#include<bits/stdc++.h>
using namespace std;
#define Y() puts("YES")
#define N() puts("NO")
using ll = long long;
const int N = 210000;
ll fa[N],sz[N];
ll find(ll x){
    if(x != fa[x]){
        ll r = find(fa[x]);
        sz[x] += sz[fa[x]];
        fa[x] = r;
    }
    return fa[x];
}
void solve(){
    int n,m;
    cin >> n >> m;
    int k = 0;
    for(int i = 0; i <= n; i++)fa[i] = i,sz[i] = 0;
    for(int i = 1; i <= m; i++){
        ll u,v,w;
        cin >> u >> v >> w;
        ll x = find(u),y = find(v);
        if(x == y){
            ll t = sz[u] - sz[v];
            if(t != w)k = 1;
        }
        else {
            fa[x] = y;
            sz[x] = sz[v] - sz[u] + w;
        }
    }
    if(k){
        N();
    }
    else Y();
}
int main(){
    int _;
    _ = 1;
    cin >> _ ;
    while( _ --){
        solve();
    }
    return 0;
}
```