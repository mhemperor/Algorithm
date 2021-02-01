//BOJ 2042
//Segment Tree �⺻

#include <iostream>
using namespace std;

const int ST = 1 << 20;// Ʈ���� ũ��� n���� ū 2�� ���� ���� ���Ѵ�

long long segTree[2 * ST]; //���׸�Ʈ Ʈ���� �迭�� ���׸�Ʈ Ʈ�� ũ���� 2��� ��´�

void build() {
	// ä���� ���� ��带 �������� ���׸�Ʈ Ʈ���� �ϼ��Ѵ�
	// �� ������ �������� ä��������.
	// segTree[ST-1]=segTree[2ST-2]+segTree[2ST-1]
	for (int i = ST - 1; i > 0; i--) {
		segTree[i] = segTree[2 * i] + segTree[2 * i + 1]; // i��° ����� �ڽ� ���� 2i, 2i+1��°
	}
}

void update(int index, long long val) {
	int n = ST + index; // index��° ���� segTree[ST+index]�� ����Ǿ� ����
	segTree[n] = val;
	for (n /= 2; n > 0; n /= 2) {
		segTree[n] = segTree[2 * n] + segTree[2 * n + 1];
	}
}

long long partialSum(int n, int nl, int nr, int l, int r) {
	if (l > nr || r < nl) return 0; // ���� ������ ���Ϸ��� ���� ���� ���
	if (l <= nl && nr <= r) return segTree[n]; // ���� ������ ���Ϸ��� ������ �� ���� ���
	//���� ������ �� ���ҵǾ�� �ϴ� ���
	int mid = (nl + nr) / 2;
	return partialSum(2 * n, nl, mid, l, r) + partialSum(2 * n + 1, mid + 1, nr, l, r);
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);
	long long n, m, k; cin >> n >> m >> k;

	for (int i = 1; i <= n; i++) {
		long long num; cin >> num;
		segTree[ST + i] = num; //i��° ���� ���� �迭�� ST+i���� �����Ѵ�
	}

	build();

	for (int i = 0; i < m + k; i++) {
		long long a, b, c; cin >> a >> b >> c;
		if (a == 1) update(b, c);
		else if (a == 2) {
			// n : ��� ��ȣ. ��Ʈ ����� 1������ ����
			// nl : ��ü ������ ���� �� �ε����� 0���� ����
			// nr : ��ü ������ ������ �� �ε����� ST-1���� ����
			cout << partialSum(1, 0, ST - 1, b, c) << "\n";
		}
	}

}