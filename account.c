#include "cereal.h"
#include "local.h"

void test()
{
	if (_create("acoount", "ACC_CODE VARCHAR(5) BN_REGI_NUM INT NAME VARCHAR(30)") == -1) {
		printf(" % s\n", err_msg);

		return -1;
	}
}

typedef struct Accountnode {
	int ACC_CODE;
	char account_name[20];
	char account_contact[20];
	struct Accontnode * next;
}Anode;

void insertAcconut()
{
	
	int new_code;
	char new_name[20];
	char new_contract[20];

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
	newNode->ACC_CODE = new_code;
	strcpy(newNode->account_name, new_name);
	strcpy(newNode->account_contact, new_contract);


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
	/*case 1:
		insertAcconut();
		break;
	case 2:
		updateAccount();
		break;*/
	case 3:
		readAccount();
		break;
	case 4:
		deleteAccount();
		break;
	}
}