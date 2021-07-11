#include "SeqList.h"
int main() {
	lpSeqList list = (lpSeqList)malloc(sizeof(SeqList));
	InitList(list);
	ListInsert(list, 0, 4);
	PrintList(list);
	ListInsert(list, 0, 2);
	PrintList(list);
	ListInsert(list, 0, 2);
	PrintList(list);
	ListInsert(list, 0, 1);
	PrintList(list);
	DeleteAllElem(list, 2);
	PrintList(list);
	return 0;
}