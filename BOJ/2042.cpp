//BOJ 2042
//Segment Tree 기본

#include <iostream>
using namespace std;

const int ST = 1 << 20;// 트리의 크기는 n보다 큰 2의 제곱 수로 정한다

long long segTree[2 * ST]; //세그먼트 트리의 배열은 세그먼트 트리 크기의 2배로 잡는다

void build() {
	// 채워진 리프 노드를 바탕으로 세그먼트 트리를 완성한다
	// 맨 끝부터 역순으로 채워나간다.
	// segTree[ST-1]=segTree[2ST-2]+segTree[2ST-1]
	for (int i = ST - 1; i > 0; i--) {
		segTree[i] = segTree[2 * i] + segTree[2 * i + 1]; // i번째 노드의 자식 노드는 2i, 2i+1번째
	}
}

void update(int index, long long val) {
	int n = ST + index; // index번째 노드는 segTree[ST+index]에 저장되어 있음
	segTree[n] = val;
	for (n /= 2; n > 0; n /= 2) {
		segTree[n] = segTree[2 * n] + segTree[2 * n + 1];
	}
}

long long partialSum(int n, int nl, int nr, int l, int r) {
	if (l > nr || r < nl) return 0; // 현재 구간이 구하려는 구간 밖인 경우
	if (l <= nl && nr <= r) return segTree[n]; // 현재 구간이 구하려는 구간에 쏙 들어가는 경우
	//현재 구간이 더 분할되어야 하는 경우
	int mid = (nl + nr) / 2;
	return partialSum(2 * n, nl, mid, l, r) + partialSum(2 * n + 1, mid + 1, nr, l, r);
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);
	long long n, m, k; cin >> n >> m >> k;

	for (int i = 1; i <= n; i++) {
		long long num; cin >> num;
		segTree[ST + i] = num; //i번째 리프 노드는 배열의 ST+i번에 저장한다
	}

	build();

	for (int i = 0; i < m + k; i++) {
		long long a, b, c; cin >> a >> b >> c;
		if (a == 1) update(b, c);
		else if (a == 2) {
			// n : 노드 번호. 루트 노드인 1번부터 시작
			// nl : 전체 구간의 왼쪽 끝 인덱스인 0부터 시작
			// nr : 전체 구간의 오른쪽 끝 인덱스인 ST-1부터 시작
			cout << partialSum(1, 0, ST - 1, b, c) << "\n";
		}
	}

}