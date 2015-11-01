#include<vector>
#include<queue>
using namespace std;

const int maxn = 1005; 
	
struct Edge{
	int to,cap;
};

vector<int> G[maxn];
int d[maxn];
int cur[maxn];
vector<Edge> edge;
int s,t;

void addedge(int from,int to,int cap)
{
	edge.push_back((Edge){to,cap});
	edge.push_back((Edge){from,0});
	int m = edge.size();
	G[from].push_back(m-2);
	G[to].push_back(m-1);
}

bool bfs()
{
	memset(d,-1,sizeof(d));
	queue<int> q;
	q.push(s);
	d[s] = 0;
	while(!q.empty()){
		int x = q.front();
		q.pop();
		for(int i=0; i<G[x].size(); i++){
			Edge& e = edge[G[x][i]];
			if(d[e.to]<0 && e.cap>0){
				d[e.to] = d[x]+1;
				q.push(e.to);
			}
		}
	}
	return d[t]!=-1;
}

int dfs(int x,int a)
{
	if(x==t || a==0) return a;
	int flow = 0,f;
	for(int& i=cur[x]; i<G[x].size(); i++){
		Edge& e = edge[G[x][i]];
		if(d[x]+1==d[e.to] && ((f = dfs(e.to,min(a,e.cap))) > 0)){
			e.cap -= f;
			edge[G[x][i]^1].cap += f;
			flow += f;
			a -= f;
			if(a == 0) break;
		}
	}
	return flow;
}

int Maxflow()
{
	int flow = 0;
	while(bfs()){
		memset(cur,0,sizeof(cur));
		flow += dfs(s,INF);
	}
	return flow;
}
