#include<bits/stdc++.h>
#include<unistd.h>
int ALLT=60;
const int del_skip_f=50;
int redT=40;
using namespace std;
// const int N=1000005;
// const int M=5000005;
int proportion=100;
int c0,c1,c2;
int gx;
int bandom=0;
int bandeg=0;
int banind=0;
#define ull unsigned long long
int read(int &x)
{
    char c=getchar();
    x=0;
    while (c>'9'||c<'0')
    {
        if (c=='c')
        {
            while (c!='\n')
                c=getchar();
        }
        c=getchar();
    }
    while (c>='0'&&c<='9')
    {
        x=x*10+c-'0';
        c=getchar();
    }
    return (c=='\n')||(c=='\r')||(c==EOF);
}
void _read(int &x)
{
    char c=getchar();
    x=0;
    while (c>'9'||c<'0')
    {
        if (c=='c')
        {
            while (c!='\n')
                c=getchar();
        }
        c=getchar();
    }
    while (c>='0'&&c<='9')
    {
        x=x*10+c-'0';
        c=getchar();
    }
}
int seed = 0;
mt19937 rnd;//(998244353);//maybe add to NodeInfoForDsatur
struct NodeInfoForDsatur
{
    int id,sat,uncolnb;
    bool operator<(const NodeInfoForDsatur &a)const
    {
        return sat!=a.sat?sat>a.sat:(uncolnb!=a.uncolnb?uncolnb>a.uncolnb:id<a.id);
    }
};
const int S_N=200;
int bms_mx=64;
int bms_mn=1;
int allans=10000000;
int bms_count=bms_mn;
struct Graph
{
    int n,resn,m;
    vector<int> d,b,to,able,q,in,mp_from_old_to_new,cand,canin;
    bitset<S_N> mp[S_N];
    bool ask_edge(int u,int v)
    {
        if (n<=S_N)
            return mp[u][v];
        int l=b[u],r=b[u+1]-1;
        while (l<=r)
        {
            int mid=(l+r)>>1;
            if (to[mid]<=v)
                l=mid+1;
            else
                r=mid-1;
        }
        // cout<<"!!!"<<u<<' '<<v<<' '<<(r>=b[u]&&to[r]==v)<<endl;
        return r>=b[u]&&to[r]==v;
    }
    int lb,rb;
    void init()
    {
        read(n);
        int o=read(m),tmp;
        while (!o)
            o=read(tmp);
        d.resize(n);
        in.resize(n,0);
        able.resize(n,1);
        to.resize(m*2);
        b.resize(n+1);
        q.resize(n+1);
        cand.resize(n);
        canin.resize(n,0);
        // cout<<"?"<<n<<' '<<m<<endl;
        int ed=0;
        for (int i=0,v;i<n;++i)
        {
            b[i]=ed;
            while (!read(v))
            {
                --v;
                to[ed++]=v;
                // cout<<ed<<' '<<i<<' '<<v<<endl;
            }
            --v;
            to[ed++]=v;
            d[i]=ed-b[i];
            rb=max(rb,d[i]+1);
        }
        // cout<<"??"<<lb<<' '<<rb<<endl;
        b[n]=ed;
        resn=n;
        if (n<=S_N)
        {
            for (int i=0;i<n;++i)
            {
                mp[i].reset();
                for (int j=b[i];j<b[i+1];++j)
                    mp[i][to[j]]=1;
            }
        }
        // cout<<b[0]<<' '<<b[1]<<' '<<b[2]<<' '<<b[3]<<endl;
        // for (int i=0;i<n;++i)
        //     for (int j=b[i];j<b[i+1];++j)
        //         cout<<"!"<<i<<' '<<to[j]<<endl;
    }
    void init1(int type = 0)
    {
        vector<vector<int> > edg;
        if (type==0)
        {
            char s[100];
            scanf("%s",s);
            while (s[0]!='p'||strlen(s)!=1)
                scanf("%s",s);
            scanf("%s",s);
            _read(n);
            _read(m);
            edg.resize(n);
            for (int i=0;i<n;++i)
                edg[i].clear();
            for (int i=0,x,y;i<m;++i)
            {
                scanf("%s",s);
                _read(x);
                _read(y);
                --x;
                --y;
                edg[x].push_back(y);
                edg[y].push_back(x);
            }
            cout<<(clock()-(double)c0)/CLOCKS_PER_SEC<<endl;
            for (int i=0;i<n;++i)
                if (!edg[i].empty())
                    sort(edg[i].begin(),edg[i].end());
        }
        else
        {
            _read(n);
            _read(m);
            edg.resize(n);
            for (int i=0;i<n;++i)
                edg[i].clear();
            for (int i=0,x,y;i<m;++i)
            {
                _read(x);
                _read(y);
                edg[x].push_back(y);
                edg[y].push_back(x);
            }
            cout<<(clock()-(double)c0)/CLOCKS_PER_SEC<<endl;
            for (int i=0;i<n;++i)
                if (!edg[i].empty())
                {
                    sort(edg[i].begin(),edg[i].end());
                    edg[i].erase(unique(edg[i].begin(),edg[i].end()),edg[i].end());
                }
        }
        d.resize(n);
        in.resize(n,0);
        able.resize(n,1);
        to.resize(m*2);
        b.resize(n+1);
        q.resize(n+1);
        cand.resize(n);
        canin.resize(n,0);
        int ed=0;
        for (int i=0;i<n;++i)
        {
            b[i]=ed;
            for (int x:edg[i])
                to[ed++]=x;
            d[i]=ed-b[i];
            rb=max(rb,d[i]+1);
        }
        b[n]=ed;
        resn=n;
        if (n<=S_N)
        {
            for (int i=0;i<n;++i)
            {
                mp[i].reset();
                for (int j=b[i];j<b[i+1];++j)
                    mp[i][to[j]]=1;
            }
        }
    }
    int ql,qr;
    int exans=0;
    vector<pair<int,int> > ord;
    // bool cmp(int x,int y)
    // {
    //     return d[x]>d[y];
    // }
    void del(int u)
    {
        if (!able[u])
            return;
        --resn;
        able[u]=0;
        for (int i=b[u];i<b[u+1];++i)
        {
            int v=to[i];
            --d[v];
            if (d[v]<lb&&able[v]&&!in[v])
            {
                q[qr++]=v;
                in[v]=1;
            } 
        }
    }    
    void ndel(int u)
    {
        if (!able[u])
            return;
        --resn;
        able[u]=0;
        for (int i=b[u];i<b[u+1];++i)
        {
            int v=to[i];
            --d[v];
            if (d[v]<nlb&&able[v]&&!in[v])
            {
                q[qr++]=v;
                in[v]=1;
            } 
        }
    }    
    void del_no_ins_q(int u)
    {
        if (!able[u])
            return;
        --resn;
        able[u]=0;
        for (int i=b[u];i<b[u+1];++i)
        {
            int v=to[i];
            --d[v];
        }
    }
    vector<int> fa;
    int getfa(int x)
    {
        return x==fa[x]?x:fa[x]=getfa(fa[x]);
    }
    void link(int x,int y)
    {
        x=getfa(x);
        y=getfa(y);
        if (x!=y)
            fa[x]=y;
    }
    void shrink(int x=0)
    {
        mp_from_old_to_new.resize(n,0);
        int p=0;
        for (int i=0;i<n;++i)
            if (able[i])
            {
                mp_from_old_to_new[i]=p++;
            }
            // else
            // {
            //  cout<<i<<"????"<<endl;
            // }
        // for (int x:mp_from_old_to_new)
        //  cout<<x<<' ';
        // cout<<endl;
        // cout<<"?????"<<p<<' '<<resn<<endl;
        int ed=0;
        for (int i=0;i<n;++i)
            if (able[i])
            {
                int oed=ed;
                for (int j=b[i];j<b[i+1];++j)
                    if (able[to[j]])
                    {
                        to[ed++]=mp_from_old_to_new[to[j]];
                        // if (to[ed-1]==mp_from_old_to_new[i])
                        //     cerr<<"!!!!!!"<<resn<<' '<<to[ed-1]<<'\n';
                        // cout<<"?"<<mp_from_old_to_new[i]<<' '<<mp_from_old_to_new[to[j]]<<endl;
                    }
                b[mp_from_old_to_new[i]]=oed;
                d[mp_from_old_to_new[i]]=ed-oed;
            }
        b[p]=ed;
        b.resize(p+1);b.shrink_to_fit();
        d.resize(p);d.shrink_to_fit();
        to.resize(ed);to.shrink_to_fit();
        if (x==0)
        {
            able.resize(p);able.shrink_to_fit();
            in.resize(p);in.shrink_to_fit();
        }
        for (int i=0;i<p;++i)
            able[i]=1;
        for (int i=0;i<p;++i)
            in[i]=0;
        // cand.resize(p);cand.shrink_to_fit();
        // canin.resize(p,0);cand.shrink_to_fit();
        n=p;
        if (n<=S_N)
        {
            for (int i=0;i<n;++i)
            {
                mp[i].reset();
                for (int j=b[i];j<b[i+1];++j)
                    mp[i][to[j]]=1;
            }
        }
        if (x==1)
        {
            for (int i=0;i<n;++i)
                ord[i]={d[i],i};
            sort(ord.begin(),ord.begin()+n,greater<pair<int,int> >());
        }
        //maybeworkwithq
        // ed=0;
        // for (int i=ql;i<qr;++i)
        //     if (able[q[i]])
        //         q[ed++]=mp_from_old_to_new[q[i]];
        // q.resize(ed);q.shrink_to_fit();
    }
    /*void clique(int x)
    {
        vector<int> nbs;
        vector<int> C;
        for (int i=b[x];i<b[x+1];++i)
            nbs.push_back(to[i]);
        for (int t=1;t<=10;++t)
        {
            random_shuffle(nbs.begin(),nbs.end());
            C.clear();
            int mxw=d[x]-lb;
            int w=0;
            for (int i=0;i<d[x];++i)
            {
                bool b=true;
                int u=nbs[i];
                for (int y:C)
                    if (!ask_edge(u,y))
                    {
                        b=false;
                        break;
                    }
                if (b)
                    C.push_back(u);
                else
                {
                    if (++w>mxw)
                        break;
                }
            }
            // if ((int)C.size()+1>lb)
            // {
            //  cout<<"!"<<C.size()+1<<':';
            //  for (int y:C)
            //      cout<<y<<' ';
            //  cout<<x<<endl;
            // }
            lb=max(lb,(int)C.size()+1);
            if (w==0)
                return;
        }
    }*/
    void clique(int x,int &lb)
    {
        // cerr<<"??.."<<x<<' '<<lb<<'\n';
        vector<int> can;
        for (int i=b[x];i<b[x+1];++i)
        {
            int u=to[i];
            can.push_back(u);
            cand[u]=0;
            canin[u]=1;
        }
        for (int u:can)
            for (int i=b[u];i<b[u+1];++i)
                if (canin[to[i]])
                    cand[u]++;
        for (int i=b[x];i<b[x+1];++i)
            canin[to[i]]=0;
        int cs=1;
        while (!can.empty()) 
        {
            int add_v=can[0];
            if (can.size()<=bms_count) 
            {
                for (int i=1;i<(int)can.size();++i)
                    if (cand[can[i]]>cand[add_v])
                        add_v=can[i];
            }
            else 
            {
                for (int i=1;i<=bms_count;++i)
                {
                    int v=can[rnd()%can.size()];
                    if (cand[v]>cand[add_v])
                        add_v=v;
                }
            }
            ++cs;
            if (cs+cand[add_v]<=lb)
                break;
            // if (cs>lb) cerr<<'('<<cs<<','<<add_v<<')'<<endl;
            for (int u:can)
                canin[u]=1;
            for (int i=b[add_v];i<b[add_v+1];++i)
            {
                canin[to[i]]=0;
                // if (to[i]==add_v)
                // {
                //     cerr<<i<<' '<<to[i]<<' '<<add_v<<'\n';
                // }
            }
            for (int i=0;i<(int)can.size();)
            {
                int v=can[i];
                if (canin[v])
                {
                    for (int j=b[v];j<b[v+1];++j)
                        --cand[to[j]];
                    can[i]=can.back();
                    can.pop_back();
                }
                else
                {
                    // if (v==add_v)
                    //     cerr<<"??????"<<endl;
                    ++i;
                }
            }
        }
        lb=max(lb,cs);
        // cerr<<"??..??"<<x<<' '<<lb<<'\n';
    }
    void get_new_lb(int &lb)
    {
        for (int i=0;i<n;++i)
            if (d[i]>=lb&&(rnd()%proportion==0||i==0))
                clique(i,lb);
    }
    vector<int> sat,ucn;
    vector<vector<int> > nc;
    // priority_queue<pair<int,int> > pq;
    set<NodeInfoForDsatur> pq;
    int dsatur()
    {
        // puts("dsa");
        //two stg:1-vec 2-ull
        nc.resize(lb);
        for (int i=0;i<lb;++i)
        {
            nc[i].resize(n);
            for (int j=0;j<n;++j)
                nc[i][j]=0;
        }
        int ans=lb;
        // cout<<ans<<endl;
        // nc.shrink_to_fit();
        sat.resize(n);
        for (int i=0;i<n;++i)  
            sat[i]=0;
        // sat.shrink_to_fit();
        // while (!pq.empty())
        //     pq.pop();
        pq.clear();
        ucn.clear();
        for (int i=0;i<n;++i)
            ucn.push_back(d[i]);
        for (int i=0;i<n;++i)
            // pq.pus({0,i});
            pq.insert((NodeInfoForDsatur){i,0,d[i]});
        for (int i=0;i<n;++i)
        {
            auto it=pq.begin();
            int u=it->id,col=-1;
            for (int j=0;j<ans;++j)
                if (!nc[j][u])
                {
                    col=j;
                    break;
                }
            pq.erase(it);
            if (col==-1)
            {
                col=ans++;
                if (ans==rb)
                    return ans;
                // nc.push_back(vector
                nc.resize(ans);
                nc[ans-1].resize(n,0);
            }
            // cout<<"!!!"<<i<<' '<<u<<' '<<col<<' '<<sat[u]<<' '<<b[u]<<' '<<b[u+1]<<endl;
            sat[u]=-1;
            for (int j=b[u];j<b[u+1];++j)
            {
                int v=to[j];
                // cout<<"?!!"<<j<<' '<<u<<' '<<v<<endl;
                if (sat[v]==-1)
                    continue;
                pq.erase((NodeInfoForDsatur){v,sat[v],ucn[v]});
                if (!nc[col][v])
                {
                    nc[col][v]=1;
                    ++sat[v];
                }
                --ucn[v];
                pq.insert((NodeInfoForDsatur){v,sat[v],ucn[v]});
            }
        }
        // cout<<ans<<endl; 
        return ans;
        // return 1;
    }
    vector<int> pos,col;
    vector<vector<int> > satbuc;
    int nowcol;
    int choose_col(int u,int p=-1)
    {
        if (gx<=10)
        {
            for (int i=0;i<nowcol;++i)
                if (!nc[i][u]&&i!=p)
                    return i;
            return -1;
        }
        else
        {
            vector<int> v;
            for (int i=0;i<nowcol;++i)
                if (!nc[i][u]&&i!=p)
                    v.push_back(i);
            return v.empty()?-1:v[rnd()%v.size()];
        }
    }
    int mx;
    void color(int x,int y)
    {
        col[x]=y;
        for (int i=b[x];i<b[x+1];++i)
        {
            int u=to[i];
            if (!nc[y][u])
            {
                if (pos[u]!=-1)
                {
                    int w=satbuc[sat[u]].back();
                    satbuc[sat[u]][pos[u]]=w;
                    pos[w]=pos[u];
                    satbuc[sat[u]].pop_back();
                    ++sat[u];
                    if (sat[u]>mx)
                        mx=sat[u];
                    pos[u]=satbuc[sat[u]].size();
                    satbuc[sat[u]].push_back(u);
                }
                else
                    ++sat[u];
            }
            ++nc[y][u];
        }
    }
    void uncolor(int x,int y)
    {
        for (int i=b[x];i<b[x+1];++i)
        {
            int u=to[i];
            --nc[y][u];
            if (!nc[y][u])
            {
                if (pos[u]!=-1)
                {
                    int w=satbuc[sat[u]].back();
                    satbuc[sat[u]][pos[u]]=w;
                    pos[w]=pos[u];
                    satbuc[sat[u]].pop_back();
                    --sat[u];
                    pos[u]=satbuc[sat[u]].size();
                    satbuc[sat[u]].push_back(u);
                }
                else
                    --sat[u];
            }
        }
        color(x,choose_col(x,y));
    }
    vector<int> tmp;
    int rnd_dsatur(int lb)
    {
        // puts("rnddsa");
        nc.resize(rb);
        for (int i=0;i<rb;++i)
        {
            nc[i].resize(n);
            for (int j=0;j<n;++j)
                nc[i][j]=0;
        }
        sat.resize(n);
        col.resize(n);
        tmp.resize(rb);
        for (int i=0;i<n;++i)
        {
            sat[i]=0;
            col[i]=-1;
        }
        satbuc.resize(rb+2);
        satbuc[0].resize(n);
        pos.resize(n);
        for (int i=0;i<n;++i)
            pos[i]=satbuc[0][i]=i;
        for (int i=1;i<(int)satbuc.size();++i)
            satbuc[i].clear();
        mx=0;
        int ans=lb;
        nowcol=lb;
        // set<int> used;
        // int ttt=10;
        for (int i=0;i<n;++i)
        {
            while (!satbuc[mx+1].empty())
                ++mx;
            while (satbuc[mx].empty()&&mx>=0)
                --mx;
            // if (mx==-1)
            //     puts("??????");
            int x=rnd()%satbuc[mx].size();
            int u=satbuc[mx][x],v=satbuc[mx].back();
            // if (mx!=sat[u]&&ttt)
            // {
            //     ttt--;
            //     cout<<"?????"<<' '<<mx<<' '<<u<<' '<<sat[u]<<'\n';
            // }
            // if (sat[u]==ans)cout<<i<<' '<<u<<' '<<sat[u]<<endl;
            // used.insert(u);
            if (u!=v)
            {
                pos[v]=x;
                satbuc[mx][x]=v;
            }
            satbuc[mx].pop_back();
            pos[u]=-1;
            int col_u=choose_col(u);
            // for (int i=0;i<ans;++i)
            //     if (nc[i][u]==0)
            //     {
            //         col_u=i;
            //         break;
            //     }
            if (col_u==-1)
            {
                for (int i=0;i<ans;++i)
                    tmp[i]=0;
                for (int j=b[u];j<b[u+1];++j)
                {
                    int v=to[j];
                    if (col[v]==-1)
                        continue;
                    // if (sat[v]==ans)
                    // {
                    //     printf("strange %d %d %d %d %d\n",u,v,sat[u],sat[v],ans);
                    // }
                    if (sat[v]==ans-1)
                        tmp[col[v]]=-1;
                    else
                    {
                        if (tmp[col[v]]!=-1)
                            ++tmp[col[v]];
                    }
                }
                int p=0;
                for (int i=1;i<ans;++i)
                    if (tmp[i]!=-1&&(tmp[p]==-1||tmp[i]<tmp[p]))
                        p=i;
                if (tmp[p]!=-1)
                {
                    // cout<<u<<' '<<p<<':';
                     col_u=p;
                    for (int j=b[u];j<b[u+1];++j)
                    {
                        int v=to[j];
                        // cout<<v<<' ';
                        if (col[v]==p)
                        {
                            uncolor(v,p);
                            // cout<<u<<' '<<p<<' '<<v<<' '<<col[v]<<' '<<sat[u]<<' '<<ans<<endl;
                        }
                    }
                    // cout<<'\n';
                }
            }
            if (col_u==-1)
            {
                col_u=ans++;
                if (ans==rb)
                    return rb;
                nowcol=ans;
            }
            color(u,col_u);
        }
        // printf("used:%d\n",(int)used.size());
        return ans;
    }
    bool fastcheck(int u)
    {
        return (!bandeg && d[u]<lb)||(!banind && d[u]>=resn-2);
    }
    int nlb,nrb,nexans;
    bool nfastcheck(int u)
    {
        return !bandeg && d[u]<nlb;
    }
    // int find_no_con(int u)
    // {
    //     for (int i=0,l=b[u];i<n;++i)
    //         if (able[i]&&i!=u)
    //         {
    //             while (to[l]<i&&l<b[u+1])
    //                 ++l;
    //             if (to[l]!=i||l>=b[u+1])
    //                 return i;
    //         }
    //     return -1;
    // }
    vector<int> find_no_con(int u)
    {
        vector<int> v;
        for (int i=0,l=b[u];i<n;++i)
        {
            if (able[i]&&i!=u)
            {
                while (to[l]<i&&l<b[u+1])
                    ++l;
                if (to[l]!=i||l>=b[u+1])
                    v.push_back(i);
            }
        }
        return v;
    }
    int degcore()
    {
        // puts("deg");
        // cerr<<"?..?"<<endl;
        int mxd=0;
        for (int i=0;i<n;++i)
            mxd=max(mxd,d[i]);
        vector<int> vertex_sorted(n),vertex_degree(n),bin_pos(mxd+1,0),index_in_vertex_sorted(n);
        for (int i=0;i<n;++i)
            bin_pos[vertex_degree[i]=d[i]]++;
        int start=0;
        for (int i=0;i<=mxd;++i)
        {
            int tmp=bin_pos[i];
            bin_pos[i]=start;
            start+=tmp;
        }
        for (int i=0;i<n;++i)
        {
            int pos=bin_pos[vertex_degree[i]];
            index_in_vertex_sorted[i]=pos;
            vertex_sorted[pos]=i;
            bin_pos[vertex_degree[i]]++;
        }
        for (int i=mxd;i;--i)
            bin_pos[i]=bin_pos[i-1];
        bin_pos[0]=0;
        int ans=0;
        for (int i=0;i<n;++i)
        {
            int v=vertex_sorted[i];
            int dv=vertex_degree[v];
            ans=max(ans,dv);
            for (int j=b[v];j<b[v+1];++j)
            {
                int u=to[j];
                if (vertex_degree[u]>dv)
                {
                    int idu=index_in_vertex_sorted[u];
                    int idw=bin_pos[vertex_degree[u]];
                    int w=vertex_sorted[idw];
                    vertex_sorted[idu]=w;
                    vertex_sorted[idw]=u;
                    index_in_vertex_sorted[u]=idw;
                    index_in_vertex_sorted[w]=idu;
                    bin_pos[vertex_degree[u]]++;
                    vertex_degree[u]--;
                }
            }
        }
        return ans+1;
    }
    // void check()
    // {
        // for (int i=0;i<n;++i)
        //     if (col[i]==-1)
        //         printf("uncolor %d\n",i);
        // for (int i=0;i<n;++i)
        //     for (int j=b[i];j<b[i+1];++j)
        //         if (col[i]==col[to[j]])
        //             printf("same color %d %d\n",i,to[j]);
    // }
    int bak_n;
    vector<int> bak_to,bak_d,bak_b,can;
    void bak()
    {
        bak_n=n;
        bak_to=to;
        bak_d=d;
        bak_b=b;
        ord.resize(n);
        can.resize(n);
        for (int i=0;i<n;++i)
        {
            able[i]=1;
            in[i]=0;
        }
    }
    int sumofrollback=0;
    void roll_back()
    {
        ++sumofrollback;
        // cerr<<++sumofrollback<<"\n";
        n=resn=bak_n;
        d=bak_d;
        to=bak_to;
        b=bak_b;
        bms_count=bms_mn;
        // in.resize(n);
        // able.resize(n);
        for (int i=0;i<n;++i)
        {
            in[i]=0;
            able[i]=1;
        }
    }
    void del_ind(int t)
    {
        // cerr<<"!"<<t<<' ';
        for (int i=0;i<n;++i)
            can[i]=1;
        queue<int> q;
        for (int i=0;i<n;++i)
        {
            if (i!=0&&rnd()%del_skip_f<t)
            {
                q.push(i);
                continue;
            }
            int x=ord[i].second;
            if (able[x]&&can[x])
            {
                del_no_ins_q(x);
                for (int j=b[x];j<b[x+1];++j)
                    can[to[j]]=0;
            }     
        }
        while (!q.empty())
        {
            int i=q.front();
            q.pop();
            if (i!=0&&rnd()%100<t)
            {
                q.push(i);
                continue;
            }
            int x=ord[i].second;
            if (able[x]&&can[x])
            {
                del_no_ins_q(x);
                for (int j=b[x];j<b[x+1];++j)
                    can[to[j]]=0;
            } 
        }
        // cerr<<endl;
    }
    void reduce()
    {
        int bg=clock();
        gx=-1;
        int rcnt=0,ssum=0;
        while ((clock()-bg <= redT*CLOCKS_PER_SEC || rcnt<=20)&&lb<rb)
        {
            ++rcnt;
            if (resn!=n)
            {
                shrink();
                gx=0;
                // printf("ruduce to %d\n",n);
            }
            else
            {
                bms_count*=2;
                if (bms_count==bms_mx)
                    bms_count=bms_mn;
                ++gx;
            }
            // lb=max(lb,clique());
            int olb=lb;
            get_new_lb(lb);
            // cout<<".."<<lb<<' '<<rb<<endl;
            if (lb>=rb)
                break;
            if (gx!=0)
            // if (0)
            {
                // cout<<"!"<<endl;
                if (gx==1)
                    rb=min(rb,dsatur());
                else
                {
                    // cout<<"!"<<endl;
                    rb=min(rb,rnd_dsatur(lb));
                    // check();
                }
            }
            else
            {
                // cout<<"?"<<endl;
                rb=min(rb,degcore());
            }
            // cout<<"..."<<lb<<' '<<rb<<' '<<exans<<' '<<n<<'\n';
            if (max(lb,rb)+exans<allans)
            {
                allans=max(lb,rb)+exans;
                cout<<"new:"<<allans<<' '<<((double)clock()-c1)/CLOCKS_PER_SEC<<'\n';
                // cerr<<"resn:"<<resn<<' '<<rcnt<<"\n";
            }
            if (lb>=rb)
                break;
            if (olb==lb)
            {
                ++ssum;
                // if (ssum>=1)
                    continue;
            }
            else
                ssum=0;
            ql=qr=0;
            for (int i=0;i<n;++i)
                if (able[i]&&fastcheck(i)&&!in[i])
                {
                    // cout<<"!"<<i<<endl;
                    in[i]=1;
                    q[qr++]=i;
                }
            if (n<=S_N&&gx&&!bandom)
            {
                for (int i=0;i<n;++i)
                    if (able[i]&&!in[i])
                        for (int j=0;j<n;++j)
                            if (i!=j&&!mp[i][j]&&((mp[i]&mp[j])==mp[i])&&!in[i])
                            {
                                in[i]=1;
                                q[qr++]=i;
                                break;
                            }

            }
            // if (ql!=qr&&olb==lb)
            //     cerr<<"?"<<rcnt<<' '<<resn<<' '<<lb<<"\n";
            while (ql<qr)
            {
                int u=q[ql++];
                // cout<<"!"<<ql<<' '<<qr<<' '<<u<<endl;
                if (!able[u])
                    continue;
                if (d[u]<lb)
                {
                    del(u);//str 1
                }
                else
                {
                    if (d[u]>=resn-2)
                    {
                        exans++;
                        lb--;
                        rb--;
                    }
                    if (d[u]==resn-2)
                    {
                        // int v=find_no_con(u);
                        // del(v);
                        auto v=find_no_con(u);
                        for (int x:v)
                            del(x);
                    }
                    del(u);
                }
            } 
            // rb=min(rb,dsatur());     
        }
        print();
        // cerr<<"de begin"<<resn<<' '<<rcnt<<endl;
        if (lb>=rb)
            return;
        if (resn!=n)
            shrink();
        bak();
        // for (int i=0;i<n;++i)
        // {
        //     cerr<<i<<':';
        //     for (int j=b[i];j<b[i+1];++j)
        //         cerr<<to[j]<<' ';
        //     cerr<<endl;
        // }
        nlb=lb,nrb=rb,nexans=0;
        int nt=0;
        int dec=0;
        bms_mn=8;
        int fi=1;
        while (clock()-bg <= ALLT*CLOCKS_PER_SEC&&lb<rb)
        {
            bool change=false;
            if (resn!=n||fi)
            {
                shrink(1);
                fi=0;
            }
            else
            {
                bms_count*=2;
                if (bms_count==bms_mx)
                {
                    del_ind(nt);
                    ++nexans;
                    --nlb;
                    change = true;
                    // --nrb;
                    bms_count=bms_mn;
                }
            }
            int onlb=nlb;
            get_new_lb(nlb); 
            if (onlb!=nlb)
                change= true;
            if (nlb+nexans>=rb)
            {
                roll_back();
                nlb=lb,nrb=rb,nexans=0;
                ++nt;
                if (nt>=del_skip_f/2)
                    nt=0;
                 continue;
            }
            if (resn!=n)
                shrink(1);
            nrb=min(nrb,rnd_dsatur(nlb));
            if (nrb+nexans+exans<allans)
            {
                allans=nrb+nexans+exans;
                rb = nrb+nexans;
                // cerr<<"."<<nt<<' '<<nlb<<' '<<nrb<<' '<<nexans<<' '<<exans<<endl;
                // cout<<"new:"<<allans<<' '<<((double)clock()-c1)/CLOCKS_PER_SEC<<'\n';
            }
            if (nlb>=nrb)
            {
                roll_back();
                nlb=lb,nrb=rb,nexans=0;
                ++nt;
                if (nt>=del_skip_f/2)
                    nt=0;
                continue;
            }
            if (lb>=rb)
                break;
            if (!change)
                continue;
            ql=qr=0;
            for (int i=0;i<n;++i)
                if (able[i]&&nfastcheck(i)&&!in[i])
                {
                    in[i]=1;
                    q[qr++]=i;
                }
            if (n<=S_N&&gx&&!bandom)
            {
                for (int i=0;i<n;++i)
                    if (able[i]&&!in[i])
                        for (int j=0;j<n;++j)
                            if (i!=j&&!mp[i][j]&&((mp[i]&mp[j])==mp[i]))
                            {
                                in[i]=1;
                                q[qr++]=i;
                                break;
                            }

            }
            while (ql<qr)
            {
                int u=q[ql++];
                if (!able[u])
                    continue;
                ndel(u);
            }   
        }
        // cerr<<sumofrollback<<endl;
    }
    void print()
    {
        shrink();
        printf("Size:%d %d\n",n,(int)to.size()/2);
        // fa.clear();
        // for (int i=0;i<n;++i)
        //     fa.push_back(i);
        // for (int i=0;i<n;++i)
        //     for (int j=b[i];j<b[i+1];++j)
        //         link(i,to[j]);
        // int sum=0;
        // for (int i=0;i<n;++i)
        //     if (getfa(i)==i)
        //         ++sum;
        // cout<<sum<<endl;
                // cout<<i+1<<' '<<to[j]+1<<endl;
    }
    
}G;
int main(int argc, char *argv[]) 
{
    c0=clock();
    string file_name;
    char optc;
    int type=0;
    while ((optc = getopt(argc, argv, "f:b:p:t:m:s:c:")) != -1) 
    {
        switch (optc) 
        {
            case 'f':
                file_name = optarg;
                break;
            case 'b':
                // bms_mx = atoi(optarg);
                for (int i=0;i<strlen(optarg);++i)
                {
                    if (optarg[i]=='i')
                        banind=1;
                    if (optarg[i]=='d')
                        bandom=1;
                    if (optarg[i]=='g')
                        bandeg=1;
                }
                break;
            case 'p':
                proportion = atoi(optarg);
                break;
            case 't':
                type = atoi(optarg);
                break;
            case 'm':
                bms_mx = atoi(optarg);
                break;
            case 'c':
                ALLT = atoi(optarg);
                redT = ALLT / 3 * 2;
                break;
            case 's':
                seed = atoi(optarg);
                rnd.seed(seed);
                break;
            default:
                std::cout << "usage: " << std::endl;
                return 1;
        }
    }
    freopen(file_name.data(),"r",stdin);
    G.init1(type);
    printf("n:%d m:%d\n",G.n,(int)G.to.size()/2);
    c1=clock();
    G.reduce();
    // G.print();
    c2=clock();
    printf("file: %s seed: %d ",file_name.data(),seed);
    printf("lb: %d rb: %d\n",G.lb+G.exans,G.rb+G.exans);
    cout<<((double)c1-c0)/CLOCKS_PER_SEC<<' '<<((double)c2-c1)/CLOCKS_PER_SEC<<endl;
    // cerr<<G.resn<<endl;
    cerr<<"no degree:"<<bandeg<<" no dominate: "<<bandom<<" no bignode:"<<banind<<endl;
    // G.print();
}