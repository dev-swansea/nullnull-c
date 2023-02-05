#include <stdio.h>
#include <string.h>
#include <malloc.h>

typedef struct NODE {
	struct NODE* next;
	char szData[64];
}NODE;

NODE* g_pHead = NULL;

void PrintList(void){


	NODE* pHead = g_pHead;
	while (pHead != NULL) {
		printf("[%p] %s, next[%p]\n",pHead, pHead->szData, pHead->next);
		pHead = pHead->next;
	}
	putchar('\n');
}

int InsertNewNode(char* pszData) { 
	NODE* pNode = (NODE*)malloc(sizeof(NODE));
	memset(pNode, 0, sizeof(NODE)); 
	strcpy_s(pNode->szData, sizeof(pNode->szData), pszData);

	if (g_pHead == NULL) {
		g_pHead = pNode;
	}else{ 
		pNode->next = g_pHead;
		g_pHead = pNode;

	}

	return 1;
}

// ���� ���
void ReleaseList(void){
	NODE* pTemp = g_pHead; // ù ��° ��忡 �����ϴ� ������ => ? 3��°���� ù ��° ��尡 �����µ�
	while (pTemp != NULL) { // �ݺ��� �ȿ� ���� ������ �ſ� ����������, �ֱٿ��� �����Ϸ� ����ȭ ������ ���� �������ٰ� �Ѵ�.
		NODE* pDelete = pTemp;
		pTemp = pTemp->next;

		// ��� �����Ǵ��� ������
		printf("Delete: [%p} %s\n", pDelete, pDelete->szData);
		free(pDelete);
	}
}

// ������ ���� �����͸� ã�ƺ���
int FindData(char* pszData) {
	NODE* pTemp = g_pHead;
	while (pTemp != NULL) {
		// �����Ͱ� ������ ��
		if (strcmp(pTemp->szData, pszData) == 0) {
			return 1;
		}
		pTemp = pTemp->next;
	}
		return 0;
}

int Delete(char* pszData) { // �����ϰ� �������� �Ѱܾ��Ѵ�.
	NODE* pTemp = g_pHead;
	// �տ����� �˰� �־�� �Ѵ�.? ������ ����
	NODE* pPrev = NULL;
	while (pTemp != NULL) {
		if (strcmp(pTemp->szData, pszData) == 0) {
			// ����
			printf("DeleteData(): %s\n", pTemp->szData);
			if (pPrev != NULL)
			{
			pPrev->next = pTemp->next; // ���� �������.. �� ���� �ָ� �����Ѷ� 
			}
			else {
				// ������ �����Ͱ� ù ��°�� ���(head)
				g_pHead = pTemp->next;
			}
			free(pTemp);
			return 1;

		}
			pPrev = pTemp; // ������ ���
			pTemp = pTemp->next;
	}
}

int main(void) {
	
	InsertNewNode("TEST01");
	PrintList();
	InsertNewNode("TEST02");
	PrintList();
	InsertNewNode("TEST03");
	PrintList();

	if (FindData("TEST01") == 1) { // 1, 2 ��ã�� �Ф� 
		printf("FINDD DATA(): TEST01 found\n");
	}
	if (FindData("TEST02") == 1) {
		printf("FINDD DATA(): TEST02 found\n");
	}
	if (FindData("TEST03") == 1) {
		printf("FINDD DATA(): TEST03 found\n");
	}

	Delete("TEST01");
	Delete("TEST02");
	Delete("TEST03");

	ReleaseList();

	return 0;
}

// ���Ͽ��ῡ�� ������ ���� ����, �� ������ ������ ���� ���� ��带 ã�Ƽ� ���� ��, �� ���� ��忡 ������ ���Ѿ� �ϱ� �����̴�.
// �� ������ �ذ��ϱ� ���� ���� �����͸� �����, �ƴϸ� double linked list�� ����ϴ°� ���ٰ� �Ѵ�.
// �׷��� head�� tail�� ���������� ���� ���Ͽ��Ḯ��Ʈ���� ������ ���� �ʴ´�.

// �̱ۿ��� �տ� ���̸� �δ°�, �߰��� �ִ� ���� �����ؾ� �ɶ� ����Ʈ�� �ǰڴ�.
// ���̳�尡 ������ �׻� ������带 �߰��ϴ� ���� ����غ��� �Ѵ�.