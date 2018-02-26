#include <iomanip>
#include <iostream>
#include<stdio.h>
using namespace std;

template <class T>
class LeftistNode {
public:
	T key;                // �ؼ���(��ֵ)
	int npl;            // ��·������(Null Path Length)
	LeftistNode *left;    // ����
	LeftistNode *right;    // �Һ���

	LeftistNode(T value, LeftistNode *l, LeftistNode *r) :
		key(value), npl(0), left(l), right(r) {}
};

template <class T>
class LeftistHeap {
private:
	LeftistNode<T> *mRoot;    // �����

public:
	LeftistHeap();
	~LeftistHeap();

	// ǰ�����"�����"
	void preOrder();
	// �������"�����"
	void inOrder();
	// �������"�����"
	void postOrder();

	// ��other������Ѻϲ���this�С�
	void merge(LeftistHeap<T>* other);
	// �����(keyΪ�ڵ��ֵ)���뵽�������
	void insert(T key);
	// ɾ�����(keyΪ�ڵ��ֵ)
	void remove();

	// ���������
	void destroy();

	// ��ӡ�����
	void print();

	void getHead()
	{
		if(mRoot != NULL)
			printf("%d\n", mRoot->key);
		else
			printf("%d\n",-1);
	}
private:

	// ǰ�����"�����"
	void preOrder(LeftistNode<T>* heap) const;
	// �������"�����"
	void inOrder(LeftistNode<T>* heap) const;
	// �������"�����"
	void postOrder(LeftistNode<T>* heap) const;

	// �����ڵ�x�ͽڵ�y
	void swapNode(LeftistNode<T> *&x, LeftistNode<T> *&y);
	// �ϲ�"�����x"��"�����y"
	LeftistNode<T>* merge(LeftistNode<T>* &x, LeftistNode<T>* &y);
	// �����(z)���뵽�����(heap)��
	LeftistNode<T>* insert(LeftistNode<T>* &heap, T key);
	// ɾ�������(heap)�еĽ��(z)�������ر�ɾ���Ľ��
	LeftistNode<T>* remove(LeftistNode<T>* &heap);

	// ���������
	void destroy(LeftistNode<T>* &heap);

	// ��ӡ�����
	void print(LeftistNode<T>* heap, T key, int direction);
};

/*
* ���캯��
*/
template <class T>
LeftistHeap<T>::LeftistHeap() :mRoot(NULL)
{
}

/*
* ��������
*/
template <class T>
LeftistHeap<T>::~LeftistHeap()
{
	destroy(mRoot);
}

/*
* ǰ�����"�����"
*/
template <class T>
void LeftistHeap<T>::preOrder(LeftistNode<T>* heap) const
{
	if (heap != NULL)
	{
		cout << heap->key << " ";
		preOrder(heap->left);
		preOrder(heap->right);
	}
}

template <class T>
void LeftistHeap<T>::preOrder()
{
	preOrder(mRoot);
}

/*
* �������"�����"
*/
template <class T>
void LeftistHeap<T>::inOrder(LeftistNode<T>* heap) const
{
	if (heap != NULL)
	{
		inOrder(heap->left);
		cout << heap->key << " ";
		inOrder(heap->right);
	}
}

template <class T>
void LeftistHeap<T>::inOrder()
{
	inOrder(mRoot);
}

/*
* �������"�����"
*/
template <class T>
void LeftistHeap<T>::postOrder(LeftistNode<T>* heap) const
{
	if (heap != NULL)
	{
		postOrder(heap->left);
		postOrder(heap->right);
		cout << heap->key << " ";
	}
}

template <class T>
void LeftistHeap<T>::postOrder()
{
	postOrder(mRoot);
}

/*
* ���������ڵ������
*/
template <class T>
void LeftistHeap<T>::swapNode(LeftistNode<T> *&x, LeftistNode<T> *&y)
{
	LeftistNode<T> *tmp = x;
	x = y;
	y = tmp;
}


/*
* �ϲ�"�����x"��"�����y"
*/
template <class T>
LeftistNode<T>* LeftistHeap<T>::merge(LeftistNode<T>* &x, LeftistNode<T>* &y)
{
	if (x == NULL)
		return y;
	if (y == NULL)
		return x;

	// �ϲ�x��yʱ����x��Ϊ�ϲ�������ĸ���
	// ����Ĳ����Ǳ�֤: x��key < y��key
	if (x->key > y->key)
		swapNode(x, y);

	// ��x���Һ��Ӻ�y�ϲ���"�ϲ�������ĸ�"��x���Һ��ӡ�
	x->right = merge(x->right, y);

	// ���"x������Ϊ��" ���� "x�����ӵ�npl<�Һ��ӵ�npl"
	// �򣬽���x��y
	if (x->left == NULL || x->left->npl < x->right->npl)
	{
		LeftistNode<T> *tmp = x->left;
		x->left = x->right;
		x->right = tmp;
	}
	// ���úϲ��������(x)��npl
	if (x->right == NULL || x->left == NULL)
		x->npl = 0;
	else
		x->npl = (x->left->npl > x->right->npl) ? (x->right->npl + 1) : (x->left->npl + 1);

	return x;
}

/*
* ��other������Ѻϲ���this�С�
*/
template <class T>
void LeftistHeap<T>::merge(LeftistHeap<T>* other)
{
	mRoot = merge(mRoot, other->mRoot);
}

/*
* �������뵽������У������ظ��ڵ�
*
* ����˵����
*     heap ����ѵĸ����
*     key ����Ľ��ļ�ֵ
* ����ֵ��
*     ���ڵ�
*/
template <class T>
LeftistNode<T>* LeftistHeap<T>::insert(LeftistNode<T>* &heap, T key)
{
	LeftistNode<T> *node;    // �½����

							 // �½��ڵ�
	node = new LeftistNode<T>(key, NULL, NULL);
	if (node == NULL)
	{
		cout << "ERROR: create node failed!" << endl;
		return heap;
	}

	return merge(mRoot, node);
}

template <class T>
void LeftistHeap<T>::insert(T key)
{
	mRoot = insert(mRoot, key);
}

/*
* ɾ����㣬���ظ��ڵ�
*
* ����˵����
*     heap ����ѵĸ����
* ����ֵ��
*     ���ڵ�
*/
template <class T>
LeftistNode<T>* LeftistHeap<T>::remove(LeftistNode<T>* &heap)
{
	if (heap == NULL)
		return NULL;

	LeftistNode<T> *l = heap->left;
	LeftistNode<T> *r = heap->right;

	// ɾ�����ڵ�
	delete heap;

	return merge(l, r); // �������������ϲ��������
}

template <class T>
void LeftistHeap<T>::remove()
{
	mRoot = remove(mRoot);
}

/*
* ���������
*/
template <class T>
void LeftistHeap<T>::destroy(LeftistNode<T>* &heap)
{
	if (heap == NULL)
		return;

	if (heap->left != NULL)
		destroy(heap->left);
	if (heap->right != NULL)
		destroy(heap->right);

	delete heap;
}

template <class T>
void LeftistHeap<T>::destroy()
{
	destroy(mRoot);
}

/*
* ��ӡ"���������"
*
* key        -- �ڵ�ļ�ֵ
* direction  --  0����ʾ�ýڵ��Ǹ��ڵ�;
*               -1����ʾ�ýڵ������ĸ���������;
*                1����ʾ�ýڵ������ĸ������Һ��ӡ�
*/
template <class T>
void LeftistHeap<T>::print(LeftistNode<T>* heap, T key, int direction)
{
	if (heap != NULL)
	{
		if (direction == 0)    // heap�Ǹ��ڵ�
			cout << setw(2) << heap->key << "(" << heap->npl << ") is root" << endl;
		else                // heap�Ƿ�֧�ڵ�
			cout << setw(2) << heap->key << "(" << heap->npl << ") is " << setw(2) << key << "'s " << setw(12) << (direction == 1 ? "right child" : "left child") << endl;

		print(heap->left, heap->key, -1);
		print(heap->right, heap->key, 1);
	}
}

template <class T>
void LeftistHeap<T>::print()
{
	if (mRoot != NULL)
		print(mRoot, mRoot->key, 0);
}

int main()
{
	int N,M,i,tmp,op,tmp2;
	scanf("%d%d",&N,&M);
	LeftistHeap<int> *q = new LeftistHeap<int>[N];

	for (i = 0;i < N;++i)
	{
		scanf("%d", &tmp);
		q[i].insert(tmp);
	}

	for (i = 0;i < M;++i)
	{
		scanf("%d", &op);
		if (op == 0)
		{
			scanf("%d%d", &tmp, &tmp2);
			q[tmp].merge(&q[tmp2]);
		}
		else if (op == 1)
		{
			scanf("%d", &tmp);
			q[tmp].getHead();
			q[tmp].remove();
		}
		else if (op == 2)
		{
			scanf("%d%d", &tmp, &tmp2);
			q[tmp].insert(tmp2);
		}
	}


	return 0;
}
