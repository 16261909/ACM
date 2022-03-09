#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn=2e6+10;
char s[maxn];
int a[maxn],c[maxn],cnt[maxn],n;
ll ans=0;
struct SAM
{
	int last,sz;//fa是suffix_link 
	int ch[maxn<<1][26],fa[maxn<<1],l[maxn<<1];//两倍 
	void ins(int c)
	{
		int p=last,np=last=++sz;l[np]=l[p]+1;
		for(;p&&!ch[p][c];p=fa[p])ch[p][c]=np;//回跳
		if(!p)fa[np]=1;//起点是1，1的link是0 
		else
		{
			int q=ch[p][c];
			if(l[p]+1==l[q])fa[np]=q;
			else
			{
				int nq=++sz;l[nq]=l[p]+1;
				memcpy(ch[nq],ch[q],sizeof ch[q]);
				fa[nq]=fa[q];fa[q]=fa[np]=nq;
				for(;p&&ch[p][c]==q;p=fa[p])ch[p][c]=nq;
			}
		}
		cnt[np]=1;//done结点初始化 
	}
	void init()
	{
		memset(ch[1],0,sizeof ch[1]);
		last=sz=1;
	}
	void build()
	{
		scanf("%s",s+1);int len=strlen(s+1);
		for(int i=1;i<=len;i++)ins(s[i]-'a'); 
	}
	void calc()
	{
		for(int i=1;i<=sz;i++)c[l[i]]++;
		for(int i=1;i<=sz;i++)c[i]+=c[i-1];
		for(int i=1;i<=sz;i++)a[c[l[i]]--]=i; 
		for(int i=sz;i;i--)
		{
			int p=a[i];
			cnt[fa[p]]+=cnt[p];
			if(cnt[p]>1)ans=max(ans,1LL*cnt[p]*l[p]);
		}
		printf("%lld\n",ans);
	}
}sam;
int main()
{
	sam.init();
	sam.build();
	sam.calc();
} 
