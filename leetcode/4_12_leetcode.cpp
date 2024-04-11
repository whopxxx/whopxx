class Solution {
public:
    int findChampion(vector<vector<int>>& grid) {
        int n = grid.size();
        for(int i = 0; i < n; i++){
            int f = 0;
            for(int j = 0; j < n; j++){
                if(grid[i][j] == 0 && i != j){
                    f = 1;
                    break;
                }
            }
            if(f)continue;
            return i;
        }
        return 0;
    }
};