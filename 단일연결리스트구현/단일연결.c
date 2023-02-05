#include <stdio.h>
#include <string.h>
#include <malloc.h>
// 지금의 경우는 포인터 하나(head pointer ??)로 첫 번째 노드에 접근하는것을 하는 것이다.
typedef struct NODE {
	// NODE구조체에 대한 포인터 선언
	struct NODE* next;
	char szData[64];
}NODE;

// 전역변수 설정, NULL 초기화 안해도 전역변수라 자동으로 NULL로 초기화 된다.
// 연결리스트 데이터가 있다면 g_pHead가 가르키고 있을 것, => not NULL
NODE* g_pHead = NULL;

/*연결 리스트 전체 데이터 출력*/
void PrintList(void){

	//// 논리적으로는 이상이 없지만 상당히 심각한 문제가 있는 코드라고 한다. 당연히 안되는 .., 난 이유를 모른다.
	//while (g_pHead != NULL) {
	//	// p는 주소가 되겟다.
	//	printf("[%p] %s, next[%p]\n",g_pHead, g_pHead->szData, g_pHead->next);
	//	// 4_ 이게 문제, 
	//	g_pHead = g_pHead->next;
	//}

	// 이렇게 해줘야 한다.
	NODE* pHead = g_pHead;
	while (pHead != NULL) {
		// p는 주소가 되겟다.
		printf("[%p] %s, next[%p]\n",pHead, pHead->szData, pHead->next);
		// 4_ 이게 문제, 
		pHead = pHead->next;
	}
	putchar('\n');
}

// 결과 확인, 이때 노드를 통으로 받을 것인가, char pointer로 받을 것이냐
int InsertNewNode(char* pszData) { // 여기선 포인터로 받는다.
	// 새 노드 하나 생성했다. 이제 이걸 어디에 추가할 것인가? 1_ => 기존 데이터와 g_pHead 사이에 새로운걸 넣을 것이다.
	NODE* pNode = (NODE*)malloc(sizeof(NODE)); // 이건 초기화가 안됨
	memset(pNode, 0, sizeof(NODE)); // 이렇게 0으로 모두 초기화 해주는데, 이건 해도되고 안 해도된다, 근데 해두는게 나쁠것이 없다고 한다.
	// pNode->szData 얘가 데이터를 담고있다.
	strcpy_s(pNode->szData, sizeof(pNode->szData), pszData);

	// 2_위의 데이터를 만듬
	if (g_pHead == NULL) {
		g_pHead = pNode;
	}else{ // 여기가 중요, 기존의 포인터(변수)가 재할당 되면 기존의 노드를 가르키던것이 사라지니 접근이 안된다. 그래서 먼저 새로운 노드가 기존의 노드를 가르키게 만들어야 한다. 그 다음 헤드포인터가 new를 가르키게한다.
		pNode->next = g_pHead;
		g_pHead = pNode;

	}

	return 1;
}

// 삭제 고고

int main(void) {
	// List 테스트를 위한 코드, 이렇게 세트로 만들어 놓고, 계속 테스트가 돌아가야 한다.
	
	// 3_
	InsertNewNode("TEST01");
	PrintList();
	InsertNewNode("TEST02");
	PrintList();
	InsertNewNode("TEST03");
	PrintList();

	return 0;
}

// 연결리스트 코딩순서 !!
// 1. 리스트 전체 출력 함수 작성(while문)
// 2. 새 노드 추가 함수 작성(개발에 앞서 절차를 정확히 글로 기술) => 이게 본격적 기능, malloc + free, test에선 free 안해도 된다. 이건 나중에 !
// 3. 리스트 삭제 함수 작성
// 4. 각 함수를 작성할 때 마다 main에서 테스트 코드 실행