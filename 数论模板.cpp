#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<cmath>
#include<iostream>
#include<algorithm>
#include<ctime>
using namespace std;

typedef long long LL;
//��������� 
LL random(LL n){
	srand(time(0));
	return (LL)((double)rand()/RAND_MAX*n+0.5);
} 

//ɸ��������ѡ��С�������� 
const int pn = 100;
int mark[pn+1],prime[pn+1],cnt;
void Get_Prime(int n=pn){
	memset(mark,0,sizeof(mark));
	cnt = 0;
	for(int i=2; i<=n; i++){
		if(!mark[i]) mark[i] = prime[cnt++] = i;
		for(int j=0; j<cnt&&prime[j]*i<=n; j++){
			mark[i*prime[j]] = prime[j];
			if(i%prime[j] == 0) break;
		}
	}
}

//������������֮�ͣ����õ���������ɸѡ
int sump[pn+2];
void Get_prime_sum(int n=pn){
	sump[1] = 0;
	for(int i=2; i<=n; i++){
		int t = 1;
		for(int j=i; j%mark[i]==0; j/=mark[i]) t *= mark[i];
		sump[i] = mark[i]+sump[i/t];
	}
} 

//����������֮�ͣ����õ���������ɸѡ
long long sumall[pn+2]; 
void Get_all_sum(int n=pn){
	sumall[1] = 1;
	for(int i=2; i<=n; i++){
		int t = 1;
		for(int j=i; j%mark[i]==0; j/=mark[i]) t *= mark[i];
		if(i == t) sumall[i] = (1ll*mark[i]*i-1)/(mark[i]-1);
		else sumall[i] = sumall[t]*sumall[i/t]; 
	}
}

//ŷ������+����ɸѡ 
int euler[pn+2];
void Get_Euler(int n=pn){
	memset(euler,0,sizeof(euler));
	euler[1] = 1;
	cnt = 0; 
	for(int i=2; i<=n; i++){
		if(!euler[i]){
			euler[i] = i-1;
			prime[cnt++] = i;
		} 
		for(int j=0; j<cnt&&prime[j]*i<=n; j++){
			if(i%prime[j]) euler[prime[j]*i] = euler[i]*(prime[j]-1);
			else {
				euler[prime[j]*i] = euler[i]*prime[j];
				break;
			}
		}
	}
}
//������ 
long long quick_power(long long a,long long b,long long m){
	long long ans = 1;
	a %= m;
	while(b){
		if(b&1) ans = (ans*a)%m;
		b >>= 1;
		a = (a*a)%m;
	} 
	return ans;
}
//�����ޱ��������� 
int Times = 100;
bool witness(long long a,long long n){
	long long m = n-1;
	int j = 0;
	while((m&1) == 0){
		j++;m>>=1;
	}
	long long x = quick_power(a,m,n);
	if(x==1 || x==n-1) return false;
	while(j--){
		x = (x*x)%n;
		if(x == n-1) return false;
	}
	return true;
}
bool Miller_Rabin(long long n){
	srand(time(0));
	if(n < 2) return 0;
	if(n == 2) return 1;
	if((n&1) == 0) return 0;
	for(int i=0; i<Times; i++){
		long long a = random(n-2)+1;
		if(witness(a,n)) return false; 
	}
	return true;
}
 
//÷ɭ����-¬��˹�б�
// r(k) = r(k-1)^2 - 2 (mod M(p)), 0 < r(k) < M(p)
//M(p) = 2^p - 1;
//M(p)���������ҽ���r(p-1) = 0 (mod M(p)) 

//��չŷ������㷨��ax+by=d���������Լ��d 
int extend_gcd(int a,int b,int& x,int& y)
{ 
	int d = a;
	if(b != 0){
		d = extend_gcd(b,a%b,y,x);
		y -= (a/b)*x;
	}
	else {
		x = 1;y = 0;
	}
	return d;
}

//һԪ����ͬ�෽�̣�����������չŷ������㷨 
struct One_Variable_linear{
	vector<int> ans;
	int a,b,m;
	One_Variable_linear(){ans.clear();}
	void set_value(int aa,int bb,int mm){
		a = aa;b = bb;m = mm;
	}
	bool solve(){//����true�����н⣬�����޽� 
		int x,y,d;
		d = extend_gcd(a,m,x,y);
		if(b%d) return false;
		x = x*(b/d)%m;
		for(int i=1; i<=d; i++){
			y = (x+(i-1)*m/d)%m;
			if(y < 0) y += m;
			ans.push_back(y);
		}
		return true;
	}
} ; 

//�й�ʣ�ඨ��������M�е�Ψһ�� 
struct CRT{
	int a[maxn],m[maxn],n;
	CRT(){}
	void read(){
		scanf("%d",&n);
		for(int i=0; i<n; i++){
			scanf("%d %d",&a[i],&m[i]);
		}
	}
	int solve(){
		long long M = 1,Mi;
		int x,y,d,ans = 0;
		for(int i=0; i<n; i++) M *= m[i];
		for(int i=0; i<n; i++){
			Mi = M/m[i];
			d = extend_gcd(Mi,m[i],x,y);
			ans = (ans+Mi*x*a[i])%M;
		}
		if(ans < 0) ans += M;
		return ans;
	}
};  

int main()
{
	
	return 0;
}
