//BOJ 10423
//Disjoint-set & Kruskal Algorithm

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int par[1001];
int Rank[1001];

struct cable {
	int u, v, w;
};

vector<cable> KS;

bool cmp(cable &a, cable &b) {
	return a.w < b.w;
}

int find(int x) {
	if (x == par[x]) return x;
	return par[x] = find(par[x]);
}

void merge(int x, int y) {
	x = find(x); y = find(y);
	if (x == y) return;
	if (Rank[x] < Rank[y]) swap(x, y);
	if (Rank[x] == Rank[y]) Rank[x]++;
	par[y] = x;
	Rank[x] += Rank[y];
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);
	vector<int> plant;
	int n, m, k; cin >> n >> m >> k;

	for (int i = 1; i <= n; i++) {
		par[i] = i; Rank[i] = 1;
	}

	for (int i = 0; i < k; i++) {
		int x; cin >> x;
		plant.push_back(x);
	}

	//발전소를 한 묶음으로 처리! 여기서 헤맸음
	for (int i = 1; i < k; i++) {
		merge(plant[i], plant[i - 1]);
	}

	for (int i = 0; i < m; i++) {
		int u, v, w; cin >> u >> v >> w;
		KS.push_back({ u,v,w});
	}
	sort(KS.begin(), KS.end(), cmp);
	int result = 0;

	for (int i = 0; i < m; i++) {
		if (find(KS[i].u) == find(KS[i].v)) continue;
		merge(KS[i].u, KS[i].v);
		result += KS[i].w;
	}
	
	cout << result;
}