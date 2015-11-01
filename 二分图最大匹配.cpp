int V;
vector<int> G[maxn];
int match[maxn];
int used[maxn];

void addedge(int u,int v)
{
	G[u].push_back(v); 
}

bool check(int u)
{
	for(int i=0; i<G[u].size(); i++){
		int v = G[u][i];
		if(!used[v]){
			used[v] = true;
			if(match[v]==-1 || check(v)){
				match[v] = u;
				return true;
			}
		}
	}
	return false;
} 

int bipartite_matching()
{
	int res = 0;
	memset(match,-1,sizeof(match));
	for(int i=0; i<n; i++){
		memset(used,0,sizeof(used));
		if(check(i)) res++;
	}
	return res;
}