class Solution {
public:
    vector<int> getCoprimes(vector<int>& nums, vector<vector<int>>& edges) {
        set<int>f[51];
        for(int i = 1; i <= 50; i++){
            for(int j = 1; j <= 50; j++){
                if(gcd(i,j) == 1){
                    f[i].insert(j);
                }
            }
        }
        int n = nums.size();
        vector<int>g[n];
        for(auto &vt:edges){
            int u = vt[0],v = vt[1];
            g[u].push_back(v);
            g[v].push_back(u);
        }
        vector<int>ans(n, -1);
        pair<int,int>val_dep[51];
        function<void(int,int,int)>dfs = [&](int u,int fa,int d){
            int val = nums[u];
            int max_d = 0;
            for(int j:f[val]){
                auto [dep, id] = val_dep[j];
                if(dep > max_d){
                    max_d=dep;
                    ans[u]=id;
                }
            }    
            auto tmp = val_dep[val];
            val_dep[val] = {d, u};
            for(int v:g[u]){
                if(v != fa){
                    dfs(v, u,d + 1);
                }
            }
            val_dep[val] = tmp;
        };
        dfs(0,-1,1);
        return ans;
    }
};