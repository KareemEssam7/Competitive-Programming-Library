template<typename t> 
class SparseTable{
    vector<int> logs;
    vector<vector<t>> table;
    
    t merge(t a, t b){
        return min(a, b);
    }
public:
    SparseTable(vector<t>& v){
        int n = v.size();
        logs.resize(n + 1);

        for(int i = 2; i <= n; i++)
            logs[i] = logs[i >> 1] + 1;

        table = vector<vector<t>>(n, vector<t>(logs[n] + 1));

        for(int i = 0; i < n; i++)
            table[i][0] = v[i];

        for(int j = 1; j <= logs[n]; j++)
            for(int i = 0; i + (1 << j) <= n; i++)
                table[i][j] = merge(table[i][j - 1], table[i + (1 << (j - 1))][j - 1]);
    }
    ll query(int l, int r){
        int _log = logs[r - l + 1];
        return merge(table[l][_log], table[r - (1 << _log) + 1][_log]);
    }
};