#include <iostream>

using namespace std;

class djs {
public:
	int Size;
	int *p;
	djs(int s)
	{
		Size = s;
		p = new int[Size];
		for (int i = 0; i < Size; ++i) p[i] = -1;
	}
	~djs() { delete[] p; }
	void Union(int r1, int r2)
	{
		if (r1 == r2) return;
		p[r1] = r2;
	}
	int Find(int x)
	{
		int start = x, tmp;
		while (p[x] >= 0) x = p[x];
		while (start != x)
		{
			tmp = p[start];
			p[start] = x;
			start = tmp;
		}
		return x;
	}
};

int w[1000][1000] = { 0 };

//��·��
void fp(int s);

int *pa, cnt = 0;
int N, M, A, B, P, Q, proot, n;
int *visit;
int *km;

djs puz(1000000);



//�Ƿ�λ������������
bool zs(int x) {
	for (int i = 0; i < N; ++i) {
		if (x == km[i] - i)
			return true;
	}
	return false;
}

//�Ƿ�λ������������
bool ys(int x) {
	for (int i = 0; i < N; ++i) {
		if (x == km[i])
			return true;
	}
	return false;
}

//�Ƿ�λ�������εױ�
bool zyx(int x) {
	for (int i = 0; i < N; ++i) {
		if (x == M - 1 - i)
			return true;
	}
	return false;
}

//λ�ڵڼ���
int row(int x) {
	for (int i = 0; i < N; ++i) {
		if (km[i] - i <= x && x <= km[i])
			return i + 1;
	}
	cout << "Error!" << endl;
}

int flag = 1;
//��·��

void fp(int s)
{
	if (!flag) return;
	if (s == B) { cout << A + 1 << ' ';for (int i = 0; i<cnt; ++i) cout << pa[i] + 1 << ' ';flag = 1;return; }
	for (int i = 0; i<M; ++i)
		if (w[s][i] && !visit[i])
		{
			visit[i] = 1;
			pa[cnt++] = i;
			fp(i);
			cnt--;

		}
}

int main() {
	cin >> N >> A >> B;
	A--; B--;//ת��Ϊ��0��ʼ�����

			 //km[i]Ϊ��i+1����β���
	km = new int[N];
	M = N*(N + 1) / 2;
	for (int i = 0; i < N; ++i) {
		km[i] = (i + 1)*(i + 2) / 2 - 1;
	}


	pa = new int[M];
	visit = new int[M];
	for (int i = 0; i < M; ++i) { pa[i] = -1; }
	for (int i = 0; i < M; ++i) { visit[i] = 0; }


	//��ǽ
	while (1) {
		if (puz.Find(A) == puz.Find(B) && puz.Find(A) != -1)break;
		cin >> P >> Q;
		P--;
		proot = puz.Find(P);
		n = row(P);//nΪP���к�
		switch (Q) {
		case 0:		//������
			if (!zs(P)) { puz.Union(proot, puz.Find(P - n)); }
			w[P][P - n] = 1;
			w[P - n][P] = 1;
			break;
		case 1:		//������
			if (!ys(P)) { puz.Union(proot, puz.Find(P - n + 1)); }
			w[P][P - n + 1] = 1;
			w[P - n + 1][P] = 1;
			break;
		case 2:		//������
			if (!zyx(P)) { puz.Union(proot, puz.Find(P + n)); }
			w[P][P + n] = 1;
			w[P + n][P] = 1;
			break;
		case 3:		//������
			if (!zyx(P)) { puz.Union(proot, puz.Find(P + n + 1)); }
			w[P][P + n + 1] = 1;
			w[P + n + 1][P] = 1;
			break;
		}

	}
	fp(A);
	return 0;
}