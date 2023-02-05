#include <stdio.h>
#include <string.h>
#include <malloc.h>
// ������ ���� ������ �ϳ�(head pointer ??)�� ù ��° ��忡 �����ϴ°��� �ϴ� ���̴�.
typedef struct NODE {
	// NODE����ü�� ���� ������ ����
	struct NODE* next;
	char szData[64];
}NODE;

// �������� ����, NULL �ʱ�ȭ ���ص� ���������� �ڵ����� NULL�� �ʱ�ȭ �ȴ�.
// ���Ḯ��Ʈ �����Ͱ� �ִٸ� g_pHead�� ����Ű�� ���� ��, => not NULL
NODE* g_pHead = NULL;

/*���� ����Ʈ ��ü ������ ���*/
void PrintList(void){

	//// �������δ� �̻��� ������ ����� �ɰ��� ������ �ִ� �ڵ��� �Ѵ�. �翬�� �ȵǴ� .., �� ������ �𸥴�.
	//while (g_pHead != NULL) {
	//	// p�� �ּҰ� �ǰٴ�.
	//	printf("[%p] %s, next[%p]\n",g_pHead, g_pHead->szData, g_pHead->next);
	//	// 4_ �̰� ����, 
	//	g_pHead = g_pHead->next;
	//}

	// �̷��� ����� �Ѵ�.
	NODE* pHead = g_pHead;
	while (pHead != NULL) {
		// p�� �ּҰ� �ǰٴ�.
		printf("[%p] %s, next[%p]\n",pHead, pHead->szData, pHead->next);
		// 4_ �̰� ����, 
		pHead = pHead->next;
	}
	putchar('\n');
}

// ��� Ȯ��, �̶� ��带 ������ ���� ���ΰ�, char pointer�� ���� ���̳�
int InsertNewNode(char* pszData) { // ���⼱ �����ͷ� �޴´�.
	// �� ��� �ϳ� �����ߴ�. ���� �̰� ��� �߰��� ���ΰ�? 1_ => ���� �����Ϳ� g_pHead ���̿� ���ο�� ���� ���̴�.
	NODE* pNode = (NODE*)malloc(sizeof(NODE)); // �̰� �ʱ�ȭ�� �ȵ�
	memset(pNode, 0, sizeof(NODE)); // �̷��� 0���� ��� �ʱ�ȭ ���ִµ�, �̰� �ص��ǰ� �� �ص��ȴ�, �ٵ� �صδ°� ���ܰ��� ���ٰ� �Ѵ�.
	// pNode->szData �갡 �����͸� ����ִ�.
	strcpy_s(pNode->szData, sizeof(pNode->szData), pszData);

	// 2_���� �����͸� ����
	if (g_pHead == NULL) {
		g_pHead = pNode;
	}else{ // ���Ⱑ �߿�, ������ ������(����)�� ���Ҵ� �Ǹ� ������ ��带 ����Ű������ ������� ������ �ȵȴ�. �׷��� ���� ���ο� ��尡 ������ ��带 ����Ű�� ������ �Ѵ�. �� ���� ��������Ͱ� new�� ����Ű���Ѵ�.
		pNode->next = g_pHead;
		g_pHead = pNode;

	}

	return 1;
}

// ���� ���

int main(void) {
	// List �׽�Ʈ�� ���� �ڵ�, �̷��� ��Ʈ�� ����� ����, ��� �׽�Ʈ�� ���ư��� �Ѵ�.
	
	// 3_
	InsertNewNode("TEST01");
	PrintList();
	InsertNewNode("TEST02");
	PrintList();
	InsertNewNode("TEST03");
	PrintList();

	return 0;
}

// ���Ḯ��Ʈ �ڵ����� !!
// 1. ����Ʈ ��ü ��� �Լ� �ۼ�(while��)
// 2. �� ��� �߰� �Լ� �ۼ�(���߿� �ռ� ������ ��Ȯ�� �۷� ���) => �̰� ������ ���, malloc + free, test���� free ���ص� �ȴ�. �̰� ���߿� !
// 3. ����Ʈ ���� �Լ� �ۼ�
// 4. �� �Լ��� �ۼ��� �� ���� main���� �׽�Ʈ �ڵ� ����