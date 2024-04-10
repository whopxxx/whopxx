#include <bits/stdc++.h>
using namespace std;
const int N = 5010;

void solve(){
    int n;
    cin >> n;
    map<int,int>mp;
    for(int i = 1; i <= n; i++){
        int x;cin >> x;
        if(x < n)
        mp[x]++;
    }
    int mex = 0;
    while(mp[mex] > 0)mex++;
    vector<int>f(mex + 1);
    int ans = mex * (mp[0] - 1);
    for(int i = 1; i < mex; i++){
        f[i] = 1e9;
        for(int j = 0; j < i; j++){
            f[i] = min(f[i], f[j] + i * mp[j]);
        }
        ans = min(ans, f[i] + mex * (mp[i] - 1));
    }
    cout << ans << endl;
    
}

signed main(){
    int _(1);
    cin >> _;
    while(_ --){
        solve();
    }
    return 0;
}