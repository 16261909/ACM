#include<bits/stdc++.h>
using namespace std;
const int maxn=160;
const int maxlen=1e6+10;
char s[maxlen],m[maxn][maxn];
int cnt[maxn];
int n,ans,sz;
struct node
{
	int ch[26],f,last,val;
	void clear(){memset(ch,0,sizeof ch),f=last=val=0;}
}p[maxn*100];
void init()
{
	ans=sz=0;
	p[0].clear();
	memset(cnt,0,sizeof cnt);
}
void insert(char *str,int v)
{
	int u=0,len=strlen(str+1);
	for(int i=1;i<=len;i++)
	{
		if(!p[u].ch[str[i]-'a'])p[u].ch[str[i]-'a']=++sz,p[sz].clear();
		u=p[u].ch[str[i]-'a'];
	}p[u].val=v;
}
void build()
{
	queue<int>q;
	for(int i=0;i<26;i++)if(p[0].ch[i])q.push(p[0].ch[i]);
	while(!q.empty())
	{
		int u=q.front();q.pop();
		for(int i=0;i<26;i++)
		{
			int& son=p[u].ch[i];
			if(!son)son=p[p[u].f].ch[i];
			else
			{
				q.push(son);
				p[son].f=p[p[u].f].ch[i];
				p[son].last=p[p[son].f].val?p[son].f:p[p[son].f].last;
			}
		}
	}
}
void update(int u)
{
	while(u)
	{
		ans=max(ans,++cnt[p[u].val]);
		u=p[u].last;
	}
}
void query(char *str)
{
	int len=strlen(str+1),u=0;
	for(int i=1;i<=len;i++)
	{
		u=p[u].ch[str[i]-'a'];
		if(p[u].val)update(u);
		else if(p[p[u].last].val)update(p[u].last);
	}
}
int main()
{
	while(scanf("%d",&n)&&n)
	{
		init();
		for(int i=1;i<=n;i++)
		{
			scanf("%s",m[i]+1);
			insert(m[i],i);
		}
		build();
		scanf("%s",s+1);
		query(s);
		printf("%d\n",ans);
		for(int i=1;i<=n;i++)
			if(cnt[i]==ans)printf("%s\n",m[i]+1);
	}
} 
