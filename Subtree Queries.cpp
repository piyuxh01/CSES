// Link to this code: https://cses.fi/paste/0641ae855cf7f23a9745e4/
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
using namespace std;
 
template <typename T> using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
template <typename T> using ordered_multiset = tree<T, null_type, less_equal<T>, rb_tree_tag, tree_order_statistics_node_update>;
 
class custom_hash {
public:
    static uint64_t splitmix64(uint64_t x) {
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }
    size_t operator()(uint64_t x) const {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};
 
typedef long long ll;
template <typename T> using uset = unordered_set<T, custom_hash>;
template <typename T> using umultiset = unordered_multiset<T, custom_hash>;
template <typename T1, typename T2> using umap = unordered_map<T1, T2, custom_hash>;
template <typename T1, typename T2> using hash = gp_hash_table<T1, T2, custom_hash>;
 
bool isPrime(int n) {
    if (n < 2) return false;
    if (n < 4) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;
    for (int i = 5; i * i <= n; i += 6) {
        if (n % (i + 2) == 0 || n % i == 0) return false;
    }
    return true;
}
 
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
 
typedef pair<int, int> p32;
typedef pair<ll, ll> p64;
typedef vector<ll> v64;
typedef vector<int> v32;
typedef vector<vector<int>> vv32;
typedef vector<vector<ll>> vv64;
typedef vector<vector<p64>> vvp64;
typedef vector<p64> vp64;
typedef vector<p32> vp32;
 
#define forn(i, a, b) for (int i = a; i < b; i++)
#define rforn(i, a, b) for (int i = a; i >= b; i--)
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
 
vector<v32> adj(MAXN);
v64 seg(4 * MAXN), arr(MAXN), sub(MAXN);
vector<int> tin(MAXN);
int timer = 0;
int n; // Global variable for tree size
 
void dfs(int u, int px, v64 &val) {
    tin[u] = ++timer;
    arr[tin[u]] = val[u];
    sub[u] = 1; // Initialize subtree size with 1 (itself)
    for (auto v : adj[u]) {
        if (v != px) {
            dfs(v, u, val);
            sub[u] += sub[v]; // Accumulate subtree sizes
        }
    }
}
 
void build(int index, int low, int high) {
    if (low == high) {
        seg[index] = arr[low];
        return;
    }
    int mid = (low + high) / 2;
    build(2 * index, low, mid);
    build(2 * index + 1, mid + 1, high);
    seg[index] = seg[2 * index] + seg[2 * index + 1];
}
 
void build() {
    build(1, 1, n);
}
 
ll query(int index, int low, int high, int l, int r) {
    if (r < low || high < l) {
        return 0; // Return identity element based on the operation
    }
    if (low >= l && high <= r) {
        return seg[index];
    }
    int mid = (low + high) / 2;
    ll left = query(2 * index, low, mid, l, r);
    ll right = query(2 * index + 1, mid + 1, high, l, r);
    return left + right;
}
 
ll query(int l, int r) {
    return query(1, 1, n, l, r);
}
 
void update(int index, int low, int high, int i, ll val) {
    if (low == high) {
        seg[index] = val;
        return;
    }
    int mid = (low + high) / 2;
    if (i <= mid) {
        update(2 * index, low, mid, i, val);
    } else {
        update(2 * index + 1, mid + 1, high, i, val);
    }
    seg[index] = seg[2 * index] + seg[2 * index + 1];
}
 
void update(int idx, ll val) {
    update(1, 1, n, idx, val);
}
 
void solve() {
    int q;
    cin >> n >> q;
    v64 val(n);
    
    forn(i, 0, n) cin >> val[i];
    forn(i, 0, n - 1) {
        int u, v;
        cin >> u >> v;
        --u; --v; // Adjust to 0-based indexing
        adj[u].pb(v);
        adj[v].pb(u);
    }
    
    dfs(0, -1, val);
    build();
    while (q--) {
        int l;
        cin >> l;
        if (l == 1) {
            int idx;
            ll vl;
            cin >> idx >> vl; 
            --idx; // Adjust to 0-based indexing
            update(tin[idx], vl);
            val[idx] = vl;
        } else {
            int idx;
            cin >> idx; 
            --idx; // Adjust to 0-based indexing
            ll ans = query(tin[idx], tin[idx] + sub[idx] - 1);
            cout << ans << '\n';
        }
    }
}
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
 
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
