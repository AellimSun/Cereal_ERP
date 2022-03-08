#include "cereal.h"

typedef struct Accountnode {
	int acconut_code;
	char account_name[20];
	char account_contact[20];
	struct Accontnode * next;
}Anode;

void insertAcconut()
{
	int new_code;
	char new_name[20] = { 0 };
	char new_contract[20] = { "0" };

	printf("====================\n");
	printf("거래처를 등록합니다.\n");
	printf("====================\n\n");

	printf("거래처 코드 등록 : \n");
	printf("현재 사용 중인 코드 : ****");
	scanf("%d",&new_code);
	printf("거래처 이름 등록 : ");
	scanf("%s", &new_name);
	printf("거래처 연락처 등록 : ");
	scanf("%s", &new_contract);
	Anode* newNode =(Anode *) malloc(sizeof(Anode));
	if (newNode == NULL)return;
	newNode->acconut_code = new_code;
	/*newNode->account_name = new_name;
	newNode->account_contact = new_contract;*/


}

void updateAccount()
{

}

void readAccount()
{

}

void deleteAccount()
{

}

void account()
{
	int menu;
	printf("거래처 등록\n");
	printf("거래처 수정\n");
	printf("거래처 조회\n");
	printf("거래처 삭제\n");
	scanf("%d", &menu);

	switch (menu)
	{
	case 1:
		insertAcconut();
		break;
	case 2:
		updateAccount();
		break;
	case 3:
		readAccount();
		break;
	case 4:
		deleteAccount();
		break;
	}
}