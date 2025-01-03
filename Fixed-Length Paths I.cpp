// Link to this code: https://cses.fi/paste/13eef759286541728e62be/
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
using namespace std;
/*
S.find_by_order(k) => returns iterator to the kth largest element
S.find_by_order(sz) returns end(S)
S.order_of_key(x) => number of items in the set that are strictly smaller than x
*/
template <typename T> using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
template <typename T> using ordered_multiset = tree<T, null_type, less_equal<T>, rb_tree_tag, tree_order_statistics_node_update>;
class custom_hash {
    public:
    static uint64_t splitmix64(uint64_t x) 
    {
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }
    size_t operator()(uint64_t x) const 
    {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};
 
typedef long long ll;
template <typename T> using uset = unordered_set<T, custom_hash>;
template <typename T> using umultiset = unordered_multiset<T, custom_hash>;
template <typename T1, typename T2> using umap = unordered_map<T1, T2, custom_hash>;
template <typename T1, typename T2> using hash = gp_hash_table<T1, T2, custom_hash>;
bool isPrime(int n) {if(n<2){return false;}  if(n<4){return true;}  if(n%2 == 0 || n%3 == 0){return false;}  for(int i=5; i*i<=n; i=i+6){if(n%(i+2) == 0 || n%i == 0){ return false;}} return true;}
template < typename T = int > istream& operator >> (istream &in, vector < T > &v) {
    for (auto &x : v) in >> x;
    return in;
}
 
template < typename T = int > ostream& operator << (ostream &out, const vector < T > &v) { 
    for (const T &x : v) out << x << ' '; 
    return out;
}
 
ll gcd(ll a, ll b) { return b == 0 ? a : gcd(b, a % b); }
ll lcm(ll a, ll b) { return (a / gcd(a, b)) * b; }
template <typename T> inline T max_(T a, T b) { return (a > b) ? a : b; }
template <typename T> inline T min_(T a, T b) { return (a < b) ? a : b; }
template <typename T> inline T abs_(T x) { return (x < 0) ? -x : x; }
#define add_mod(a, b, m) (((a % m) + (b % m)) % m)
#define sub_mod(a, b, m) (((a % m) - (b % m) + m) % m)
#define mul_mod(a, b, m) (((a % m) * (b % m)) % m)
template<class T> using pqg = priority_queue<T, vector<T>, greater<T>>;
typedef pair<int,int> p32;
typedef pair<ll,ll> p64;
typedef vector<ll> v64;
typedef vector<int> v32;
typedef vector<vector<int>> vv32;
typedef vector<vector<ll>> vv64;
typedef vector<vector<p64>> vvp64;
typedef vector<p64> vp64;
typedef vector<p32> vp32;
#define forn(i,a,b) for(int i = a; i < b; i++)
#define rforn(i,a,b) for(int i = a; i >= b; i--)
#define nl "\n"
#define dbg(x) cout << x << nl
#define pb push_back
#define ff first
#define ss second
#define all(x) begin(x), end(x)
#define lb lower_bound
#define ub upper_bound
#define sz(x) x.size()
const int MOD = 1e9+7;
const int MAXN = 200005;
v32 adj[MAXN];
int sub[MAXN];
int cnt[MAXN]{1};
int mdepth;
vector<bool> vis(MAXN,false),v(MAXN,false);
int n,k; 
ll ans = 0;
int dfs(int u,int p=0){
    sub[u] = 1;
    for(auto v:adj[u]){
        if(!vis[v] && v != p){
            sub[u] += dfs(v,u);
        }
    }
    return sub[u];
}
int centroid(int u,int d,int p=0){
    for(auto v:adj[u]){
        if(v != p && !vis[v] && sub[v] >= d){
            return centroid(v,d,u);
        }
    }
    return u;
}
void get_count(int u,int p,bool f,int depth = 1){
    if(depth > k){
        return;
    }
    mdepth = max(mdepth,depth);
    if(f) cnt[depth]++;
    else ans += cnt[k-depth];
    for(auto v:adj[u]){
        if(!vis[v] && v != p){
            get_count(v,u,f,depth+1);
        }
    }
}
void decompostion(int u=1){
    int cntrd = centroid(u,dfs(u)>>1);
    vis[cntrd] = 1;
    mdepth = 0;
    for(auto v:adj[cntrd]){
        if(!vis[v]){
            get_count(v,cntrd,false);
            get_count(v,cntrd,true);
        }
    }
    fill(cnt+1,cnt+mdepth+1,0);
    for(auto v:adj[cntrd]){
        if(!vis[v]){
            decompostion(v);
        }
    }
}
void solve() {
    cin>>n>>k;
    forn(i,1,n){
        int x,y;cin>>x>>y;
        adj[x].pb(y);
        adj[y].pb(x);
    }
    decompostion();
    cout<<ans<<endl;
}
 
int main() {
    ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
 
auto start_time = chrono::high_resolution_clock::now();
 
    ll test = 1;
    // cin >> test;
    while (test--) {
        solve();
    }
auto end_time = chrono::high_resolution_clock::now();
auto duration = chrono::duration_cast<chrono::milliseconds>(end_time - start_time);
cerr << duration.count() << nl;
 
    return 0;
}
