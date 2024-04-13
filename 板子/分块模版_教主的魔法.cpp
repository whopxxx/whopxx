#include <bits/stdc++.h>
using namespace std;
const int N = 1e6 + 10;
const int M = 1010;
int a[N];
int be[N],L[M],R[M];
int tag[M];
int e[N];

void cg(int k){
    for(int i = L[k]; i <= R[k]; i++){
        e[i] = a[i];
    }
    sort(e + L[k],e + R[k] + 1);
}

signed main(){
    int n, q;
    cin >> n >> q;
    for(int i = 1; i <= n; i++) cin >> a[i];
    int b = sqrt(n);
    int cnt = (n + b - 1) / b;
    for(int i = 1; i <= cnt; i++){
        L[i] = (i - 1) * b + 1;
        R[i] = min(n, i * b);
        for(int j = L[i]; j <= R[i]; j++){
            be[j] = i;
        }
        cg(i);
    }
    while(q--){
        char op;
        cin >> op;
        int l, r, c;
        cin >> l >> r >> c;
        if(op == 'A'){
            int ans = 0;
            if(be[l] == be[r]){
                for(int i = l; i <= r; i++){
                    ans += ((a[i] + tag[be[l]]) >= c);
                }
            }
            else{
                for(int i = l;i <= R[be[l]]; i++) ans += ((a[i] + tag[be[i]]) >= c);
                for(int i = L[be[r]]; i <= r; i++) ans += ((a[i] + tag[be[i]]) >= c);
                for(int i = be[l] + 1;i <= be[r] - 1; i++){
                    int ll = L[i],rr = R[i];
                    ans += e + R[i] + 1 - lower_bound(e + ll, e + rr + 1, c - tag[i]);
                }
            }
            cout << ans << endl;
        }
        else if(op == 'M'){
            if(be[l] == be[r]){
                for(int i = l; i <= r; i++){
                    a[i] += c;
                }
                cg(be[l]);
            }
            else{
                for(int i = l;i <= R[be[l]]; i++) a[i] += c;
                cg(be[l]);
                for(int i = L[be[r]]; i <= r; i++) a[i] += c;
                cg(be[r]);
                for(int i = be[l] + 1; i <= be[r] - 1; i++){
                    tag[i] += c;
                }
            }
        }

    }

    return 0;
}