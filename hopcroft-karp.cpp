#include <bits/stdc++.h>
using namespace std ;

#define mset0(x) memset(x,0,sizeof(x))
const int maxN = 50000 ;
const int maxM = 50000 ;
struct HopcroftKarp {
    int vis[maxN], level[maxN], ml[maxN], mr[maxM];
    vector<int> edge[maxN]; // constructing edges for left part only

    void init(int n) {
        for (int i = 1; i <= n; ++i) edge[i].clear();
    }

    void add(int u, int v) {
       // cout << u << " " << v << endl ;
        edge[u].push_back(v);
    }

    bool dfs(int u) {
        vis[u] = true;
        for (vector<int>::iterator it = edge[u].begin(); it != edge[u].end(); ++it) {
            int v = mr[*it];
            if (v == -1 || (!vis[v] && level[u] < level[v] && dfs(v))) {
                ml[u] = *it;
                mr[*it] = u;
                return true;
            }
        }
        return false;
    }

    int matching(int n) { // n for left
        mset0(vis);
        mset0(level);
        memset(ml, -1,sizeof(ml));
        memset(mr, -1,sizeof(mr));
        for (int match = 0;;) {
            queue<int> que;
            for (int i = 1; i <= n; ++i) {
                if (ml[i] == -1) {
                    level[i] = 0;
                    que.push(i);
                } else level[i] = -1;
            }
            while (!que.empty()) {
                int u = que.front();
                que.pop();
                for (vector<int>::iterator it = edge[u].begin(); it != edge[u].end(); ++it) {
                    int v = mr[*it];
                    if (v != -1 && level[v] < 0) {
                        level[v] = level[u] + 1;
                        que.push(v);
                    }
                }
            }
            for (int i = 1; i <= n; ++i) vis[i] = false;
            int d = 0;
            for (int i = 1; i <= n; ++i) if (ml[i] == -1 && dfs(i)) ++d;
            if (d == 0) return match;
            match += d;
        }
    }
};

int t, cs, a[205][205],n,m,x,y,k;
int dx[]={-2,-2,-1,-1,1,1,2,2};
int dy[]={-1,1,-2,2,2,-2,1,-1};
int main() {
    //freopen("out.txt","w", stdout ) ;
    scanf("%d",&t);
    while(cs<t) {
        cs++;

        scanf("%d %d %d",&n,&m,&k);
        memset(a,0,sizeof(a));
        for(int i = 0 ; i < k ; i++) {
            scanf("%d %d",&x,&y);

            a[x][y] = 1 ;
        }
        HopcroftKarp hp ;
        hp.init(n*m );
        for( int i = 1 ; i <= n ; i++)
        {
            for(int j = 1 ; j <= m ; j++)
            {
                if((i+j)%2==1){continue;}
                if(a[i][j]==1){continue;}
                for(int k = 0 ; k < 8 ; k++)
                {
                    int ii = i + dx[k] ;
                    int jj = j + dy[k] ;
                    if(a[ii][jj]==1){continue;}
                    if( 1 <= ii && ii <= n && 1 <= jj && jj <= m )
                    {
                        hp.add((i-1)*m+j, (ii-1)*m+jj ) ;
                    }
                }
            }
        }
        int ans = n*m-hp.matching(n*m)-k;
        printf("Case %d: %d\n", cs, ans ) ;



    }


    return 0 ;

}
