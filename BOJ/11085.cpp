// BOJ 11085
// Disjoint-set

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

int par[50001];
int sz[50001];

struct way {
	int start, end, width;
};

int find(int x) {
	if (x == par[x]) return x;
	return par[x] = find(par[x]);
}

void merge(int x, int y) {
	x = find(x); y = find(y);
	if (x == y) return;
	if (sz[x] < sz[y]) swap(x, y);
	par[y] = x;
	sz[x] += sz[y];
}

struct cmp {
	bool operator()(way &a, way &b) {
		return a.width < b.width;
	}
};
int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);
	int p, w, c, v; cin >> p >> w >> c >> v;
	priority_queue<way,vector<way>,cmp> pq;

	for (int i = 0; i < p; i++) par[i] = i;

	for (int i = 0; i < w; i++) {
		int start, end, width;
		cin >> start >> end >> width;
		pq.push({ start,end,width });
	}
	way temp;
	int result;
	while (!pq.empty()) {
		temp = pq.top();
		pq.pop();
		if (find(c) == find(v)) break;
		if (find(temp.start) == find(temp.end)) continue;
		merge(temp.start, temp.end);
		result = temp.width;
	}
	cout << result;

}