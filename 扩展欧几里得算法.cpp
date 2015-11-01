#include<cstdio>
using namespace std; 
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

int main()
{
	int a,b,x,y,r;
	while(scanf("%d %d",&a,&b) == 2){
		r = extend_gcd(a,b,x,y);
		printf("%d * %d + %d * %d = %d\n",a,x,b,y,r);
	} 
	return 0;
}