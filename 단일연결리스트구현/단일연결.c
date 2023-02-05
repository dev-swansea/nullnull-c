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

// 삭제 고고
void ReleaseList(void){
	NODE* pTemp = g_pHead; // 첫 번째 노드에 접근하는 포인터 => ? 3번째에서 첫 번째 노드가 찍히는데
	while (pTemp != NULL) { // 반복문 안에 변수 설정이 매우 안좋았지만, 최근에는 컴파일러 최적화 때문에 많이 좋아졌다고 한다.
		NODE* pDelete = pTemp;
		pTemp = pTemp->next;

		// 어떤게 삭제되는지 보여줌
		printf("Delete: [%p} %s\n", pDelete, pDelete->szData);
		free(pDelete);
	}
}

// 삭제를 위해 데이터를 찾아보자
int FindData(char* pszData) {
	NODE* pTemp = g_pHead;
	while (pTemp != NULL) {
		// 데이터가 같은지 비교
		if (strcmp(pTemp->szData, pszData) == 0) {
			return 1;
		}
		pTemp = pTemp->next;
	}
		return 0;
}

int Delete(char* pszData) { // 삭제하고 다음으로 넘겨야한다.
	NODE* pTemp = g_pHead;
	// 앞에것을 알고 있어야 한다.? 삭제될 것의
	NODE* pPrev = NULL;
	while (pTemp != NULL) {
		if (strcmp(pTemp->szData, pszData) == 0) {
			// 삭제
			printf("DeleteData(): %s\n", pTemp->szData);
			if (pPrev != NULL)
			{
			pPrev->next = pTemp->next; // 내가 사라지니.. 내 다음 애를 가리켜라 
			}
			else {
				// 삭제할 데이터가 첫 번째인 경우(head)
				g_pHead = pTemp->next;
			}
			free(pTemp);
			return 1;

		}
			pPrev = pTemp; // 데이터 백업
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

	if (FindData("TEST01") == 1) { // 1, 2 못찾음 ㅠㅠ 
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

// 단일연결에서 삭제가 가장 어려운데, 그 이유는 삭제할 놈의 앞의 노드를 찾아서 삭제 후, 그 다음 노드에 연결을 시켜야 하기 때문이다.
// 이 문제를 해결하기 위해 더미 데이터를 사용함, 아니면 double linked list를 사용하는게 좋다고 한다.
// 그러나 head나 tail의 삭제에서는 딱히 단일연결리스트에선 문제가 되지 않는다.

// 싱글에선 앞에 더미를 두는게, 중간에 있는 놈을 삭제해야 될때 베스트가 되겠다.
// 더미노드가 없으면 항상 앞전노드를 추가하는 것을 고민해봐야 한다.