// Link to this code: https://cses.fi/paste/a83894accc4c84ca9769e7/
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
#define maxe(x) *max_element(all(x))
#define mine(x) *min_element(all(x))
#define setbitsll(x) __builtin_popcountll(x)
#define setbits(x) __builtin_popcount(x)
#define rt(x) return x
const int MOD = 1000000007;
const int MAXN = 200001;
v32 adj[MAXN];
int tin[MAXN],tout[MAXN];
int timer = 0;
template <typename T = int, int Base = 0>
class SGTree {
public:
    vector<T> seg;
    int n;
    T operation(T a,T b){
        return (a+b); // Change this for different operations
    }
public:
    SGTree(int n) : n(n) {
        seg.resize(4 * n);
    }
    T query(int index, int low, int high, int l, int r) {
        if (r < low || high < l) {
            return 0; // Return identity element based on the operation
        }
        if (low >= l && high <= r) {
            return seg[index];
        }
        int mid = (low + high) / 2;
        T left = query(2 * index + 1, low, mid, l, r);
        T right = query(2 * index + 2, mid + 1, high, l, r);
        return operation(left, right);
    }
    T query(int l, int r) {
        return query(0, 0, n - 1, l, r);
    }
    void update(int index, int low, int high, int i, T val) {
        if (low == high) {
            seg[index] = val;
            return;
        }
        int mid = (low + high) / 2;
        if (i <= mid) {
            update(2 * index + 1, low, mid, i, val);
        } else {
            update(2 * index + 2, mid + 1, high, i, val);
        }
        seg[index] = operation(seg[2 * index + 1], seg[2 * index + 2]);
    }
    void update(int idx, T val) {
        update(0, 0, n - 1, idx, val);
    }
};
void dfs(int u,int p){
    tin[u] = timer++;
    for(auto v:adj[u]){
        if(v != p){
            dfs(v,u);
        }
    }
    tout[u] = timer++;
}
void solve() {
    int n,q;cin>>n>>q;
    v64 val(n);
    forn(i,0,n) cin>>val[i];
    int u,v;
    forn(i,0,n-1){
        cin>>u>>v;
        --u;--v;
        adj[u].pb(v);
        adj[v].pb(u);
    }
    dfs(0,-1);
    SGTree<ll> tree(2*n);
    forn(i,0,n){
        tree.update(tin[i],val[i]);
        tree.update(tout[i],-val[i]);
    }
    ll ans = 0;
    ll vx = 0;
    while(q--){
        int l;cin>>l;
        if(l == 1){
            cin>>u>>vx;
            --u;
            tree.update(tin[u],vx);
            tree.update(tout[u],-vx);
        }
        else{
            cin>>v;--v;
            ans = tree.query(tin[0],tout[v]-1);
            dbg(ans);
        }
    }
 
}
 
int main() {
    ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
 
#ifndef debugs
#else
#define debug(...)
#define debugArr(...)
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
