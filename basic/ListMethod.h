#pragma once

#define MAX_IMPL(T)						_MAX_IMPL(T)
#define _MAX_IMPL(T)					T MAX(T)(T a,T b){return a>b?a:b;}
#define MAX(T)							_MAX(T)
#define _MAX(T)							MAX$##T##$

#define _MIN_IMPL(T)					T MIN(T)(T a,T b){return a<b?a:b;}
#define MIN_IMPL(T)						_MIN_IMPL(T)
#define MIN(T)							_MIN(T)
#define _MIN(T)							MIN$##T##$

#define _Pair(T1,T2)					Pair$##T1##$$##T2##$
#define Pair(T1,T2)						_Pair(T1,T2)
#define _Pair_IMPL(T1,T2)				typedef struct{T1 frist;T2 second;}Pair(T1,T2);
#define Pair_IMPL(T1,T2)				_Pair_IMPL(T1,T2)

//全部从0开始计数
typedef int ElemType;
//#define _ElemType(T) ElemType$##T##$
//#define ElemType(T) _ElemType(T)
//#define _ElemType_IMPL(T) typedef struct {T data;} ElemType(T);
//#define ElemType_IMPL(T) _ElemType_IMPL(T)

//动态线性表
#ifdef _SeqList_
#define _MAXSIZE_ 100

typedef struct SeqList {
	ElemType* data;
	int MaxSize, length;
} SeqList, * lpSeqList;

//#define _SeqList(T) SeqList$##T##$
//#define SeqList(T) _SeqList(T)
//#define _lpSeqList(T) lpSeqList$##T##$
//#define lpSeqList(T) _lpSeqList(T)
//#define _SeqList_IMPL(T) typedef struct {T *data;int MaxSize, length;} SeqList(T), * lpSeqList(T);
//#define SeqList_IMPL(T) _SeqList_IMPL(T)

#define _LPTYPENAME_ lpSeqList
#define _TYPENAME_ SeqList

#endif // _SeqList_

//静态线性表
#ifdef _SqList_
#define _MAXSIZE_ 100
typedef struct SqList {
	ElemType data[_MAXSIZE_];
	int length;
} SqList, * lpSqList;
#define _LPTYPENAME_ lpSqList
#define _TYPENAME_ SqList

#endif //_SqList_

#if defined _SeqList_ || defined _SqList_

void Reserve(_LPTYPENAME_ L) {
	int front = 0, back = L->length - 1;
	while (front < back) {
		ElemType temp = L->data[front];
		L->data[front] = L->data[back];
		L->data[back] = temp;
		front++;
		back--;
	}
}

//返回删除个数
int DeleteAllElem(_LPTYPENAME_ L, ElemType e) {
	int i = 0, count = 0;
	for (; i < L->length; i++) {
		if (L->data[i] == e) {
			L->data[i] = L->data[L->length - 1];

#ifdef _SeqList_
			//printf("%d\n", &L->data[L->length - 1]);
			//free(&L->data[L->length-1]);
#endif // _SeqList_

			L->length--;
			count++;
			i--;
		}
	}
	return count;
}

void InitList(_LPTYPENAME_ L) {
	L->length = 0;

#ifdef _SeqList_
	L->MaxSize = _MAXSIZE_;
	L->data = (ElemType*)malloc(L->length * sizeof(ElemType));
#endif // _SeqList_

}

int ListDelete(_LPTYPENAME_ L, int i, ElemType* e) {
	if (i > L->length - 1 || i < 0) return 2;
	int pos = i;
	*e = L->data[pos];
	for (; pos < L->length - 1; pos++) {
		L->data[pos] = L->data[pos + 1];
	}

#ifdef _SeqList_
	ElemType* temp = (ElemType*)realloc(L->data, sizeof(ElemType) * (L->length - 1));
	L->data = temp;
	if (!L->data) return 0;
#endif //_SeqList_
	L->length--;
	return 1;
}

int Empty(_LPTYPENAME_ L) {//为空返回1
	if (L->length == 0) {
		return 1;
	}
	return 0;
}

void DestroyList(_LPTYPENAME_ L) {

#ifdef _SeqList_
	free(L->data);
#endif // _SeqList_

	free(L);
}

int ListInsert(_LPTYPENAME_ L, int i, ElemType e) {//长度不足2 正常1 错误0
	int pos = L->length, j = 0;
	if (L->length + 1 > _MAXSIZE_ || i > L->length || i < 0) return 2;

#ifdef _SeqList_
	L->data= (ElemType*)realloc(L->data, sizeof(ElemType) * (L->length + 1));
	printf("%d\n", _msize(L->data));
	if (!L->data) return 0;
#endif // _SeqList_

	for (; pos > i; pos--) {
		L->data[pos] = L->data[pos - 1];
	}
	L->data[i] = e;
	L->length++;
	return 1;
}

void PrintList(_LPTYPENAME_ L) {
	int i = 0;
	for (; i < L->length; i++) {
		printf("%d", L->data[i]);
		if (i == L->length - 1) {
			printf("\n");
		}
		else {
			printf(" ");
		}
	}
}

ElemType Length(_LPTYPENAME_ L) {
	return L->length;
}

//大于等于0为找到 -1为没找到
ElemType LocateElem(_LPTYPENAME_ L, ElemType e) {
	int i = 0;
	for (i = 0; i < L->length; i++) {
		if (L->data[i] == e) {
			return i;
		}
	}
	return -1;
}

ElemType GetElem(_LPTYPENAME_ L, int i) {
	return L->data[i];
}
#endif

//链表
#ifdef _LNODE_

typedef struct LNode {
	ElemType data;
	struct LNode* next;
}LNode, * LinkList;

#define _LPTYPENAME_ LinkList
#define _TYPENAME_ LNode

void DeleteLNode(LinkList L, int pos) {
	//调用函数方式
//    LinkList pre = GetElem(L, pos - 1);
//    LinkList dest = pre->next;
//    pre->next = dest->next;
//    free(dest);

	//调换方式
	if (pos < 0) return;
	LinkList head = L->next, pre = L;
	int count = -1;
	if (!head) return;
	while (head->next) {
		count++;
		if (count >= pos) {
			ElemType temp = head->data;
			head->data = head->next->data;
			head->next->data = temp;
		}
		head = head->next;
		L = L->next;
	}
	L->next = NULL;
	free(head);
}

//链表反转
void Reserve(LinkList L) {
	LinkList head = L->next->next;
	LinkList pre = L->next;
	LinkList temp = NULL;
	L->next->next = NULL;
	while (head) {
		temp = head->next;
		head->next = pre;
		pre = head;
		head = temp;
	}
	L->next = pre;
}

#endif // _LNODE_

//双链表
#ifdef _DNODE_

typedef struct DNode {
	ElemType data;
	struct DNode* prior, * next;
}DNode, * DLinkList;

#define _LPTYPENAME_ DLinkList
#define _TYPENAME_ DNode

//获得尾节点
DLinkList GetTailNode(DLinkList L) {
	DLinkList head = L->next, pre = L;
	while (head) {
		head = head->next;
		pre = pre->next;
	}
	return pre;
}

void PrintReverseDNode(DLinkList L) {
	DLinkList head = L;
	while (head) {
		if (!head->prior) break;
		printf("%d ", head->data);
		head = head->prior;
	}
	printf("\n");
}

void DeleteDNode(DLinkList L, int pos) {
	DLinkList goal = GetElem(L, pos);
	goal->next->prior = goal->prior;
	goal->prior->next = goal->next;
}


#endif // _DNODE_


#if defined _DNODE_ || defined _LNODE_
int Length(_LPTYPENAME_ L) {
	int count = 0;
	_LPTYPENAME_ head = L->next;
	while (head) {
		count++;
		head = head->next;
	}
	return count;
}

//输入999表示结束
void List_HeadInsert(_LPTYPENAME_ L) {
	int tempData = 0;
	scanf_s("%d", &tempData);
	while (tempData != 999) {
		_LPTYPENAME_ temp = (_LPTYPENAME_)malloc(sizeof(_TYPENAME_));
		temp->data = tempData;
		temp->next = L->next;

#ifdef _DNODE_
		temp->prior = L;
#endif // _DNODE_

		L->next = temp;
		scanf_s("%d", &tempData);
	}
}

//输入999表示结束
_LPTYPENAME_ List_TailInsert(_LPTYPENAME_ L) {
	_LPTYPENAME_ head = L, tail = L;
	int tempData = 0;
	scanf_s("%d", &tempData);
	while (tempData != 999) {
		_LPTYPENAME_ temp = (_LPTYPENAME_)malloc(sizeof(_TYPENAME_));
		temp->data = tempData;
		temp->next = NULL;
		tail->next = temp;

#ifdef _DNODE_
		temp->prior = tail;
#endif // _DNODE_

		tail = tail->next;
		scanf_s("%d", &tempData);
	}
	return head;
}

//找不到返回nullptr
_LPTYPENAME_ GetElem(_LPTYPENAME_ L, int i) {
	int count = 0;
	_LPTYPENAME_ head = L->next;
	while (head) {
		if (count == i) {
			return head;
		}
		head = head->next;
	}
	return head;
}

//按值查找表节点
//找不到返回nullptr
_LPTYPENAME_ LocateElem(_LPTYPENAME_ L, ElemType e) {
	_LPTYPENAME_ head = L->next;
	while (head) {
		if (head->data == e) {
			return head;
		}
		head = head->next;
	}
	return head;
}

void PrintNode(_LPTYPENAME_ L) {
	_LPTYPENAME_ head = L->next;
	while (head) {
		printf("%d ", head->data);
		head = head->next;
	}
	printf("\n");
}

void InsertLNode(_LPTYPENAME_ L, int pos, ElemType value) {
	_LPTYPENAME_ pre = GetElem(L, pos - 1);
	if (!pre) return;
	_LPTYPENAME_ temp = (_LPTYPENAME_)malloc(sizeof(_TYPENAME_));
	temp->data = value;

#ifdef _DNODE_
	pre->next->prior = temp;
	temp->prior = pre;
#endif // _DNODE_

	temp->next = pre->next;
	pre->next = temp;
}

#endif