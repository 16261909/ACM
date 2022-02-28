#include<bits/stdc++.h>
using namespace std;
const int maxn=2e5+10;
const int maxch=27;
const int maxlen=2e6+10;
char s[maxlen],tmp[maxn];
int cnt[maxn],mp[maxn],d[maxn];
int n,sz;	
struct node
{
	int ch[maxch],f,val,ans;
	void clear(){memset(ch,0,sizeof ch),f=ans=val=0;}
}p[maxn];
void insert(char *str,int x)
{
	int u=0,len=strlen(str+1);
	for(int i=1;i<=len;i++)
	{
		if(!p[u].ch[str[i]-'a'])p[u].ch[str[i]-'a']=++sz,p[sz].clear();
		u=p[u].ch[str[i]-'a'];
	}
	if(!p[u].val)p[u].val=x,mp[x]=x;//duplicate
	else mp[x]=p[u].val;
	
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
			int &son=p[u].ch[i];
			if(!son)son=p[p[u].f].ch[i];
			else
			{
				q.push(son);
				p[son].f=p[p[u].f].ch[i];
				d[p[p[u].f].ch[i]]++;
			}
		}
	}
}
void query(char *str)
{
	int u=0,len=strlen(str+1);
	for(int i=1;i<=len;i++)
	{
		u=p[u].ch[str[i]-'a'];
		++p[u].ans;
	}
}
void topo()
{
	queue<int>q;
	for(int i=1;i<=sz;i++)if(!d[i])q.push(i);
	while(!q.empty())
	{
		int u=q.front();q.pop();
		cnt[p[u].val]=p[u].ans;
		p[p[u].f].ans+=p[u].ans;
		if(--d[p[u].f]==0)q.push(p[u].f);
	}
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%s",tmp+1);
		insert(tmp,i);
	}
	build();
	scanf("%s",s+1);
	query(s);
	topo();
	for(int i=1;i<=n;i++)printf("%d\n",cnt[mp[i]]);
} 
