#include"LNode.h"
int main() {
	LinkList list = (LinkList)malloc(sizeof(LNode));
	list->next = NULL;
	List_HeadInsert(list);
	PrintNode(list);
	Reserve(list);
	PrintNode(list);
	return 0;
}