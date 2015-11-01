//Euler Graph
struct Edge{
	int to,next;
};

int head[maxn];
Edge edge[maxm<<1];
int ans[maxm],cnt;
bool vis[maxm<<1];

void dfs(int u){
	memset(vis,0,sizeof(vis));
	for(int i=head[u]; i!=-1; i=edge[i].next){
		if(!vis[i]){
			vis[i] = true;
			vis[i^1] = true;
			dfs(edge[i].to);
			ans[cnt++] = i;
		}
	}
} 