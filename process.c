#include "cereal.h"

#define FILE_NAME "process"
#define PLAN_NUM 100
#define PLAN_CODE "A1001"

typedef struct _process {
	int data;
	struct _process* next;
}S_process;
typedef struct _req_code {
	int num;
	char* code;
	struct _req_code* next;
}req_code;

//void init(void);
void bg_process(int num, char* bom_res, char* code);
//req_code* NewNode();

void check_parts(int num, char* bom_res, req_code);
int parts_produce(int num, char* bom_res, char* code);


void process(void)
{
	//init();
	initalizing("FILE_NAME");
	int input;

	printf("�޴��� �����ϼ���.\n");

	while (1)
	{
		
	}
	system("cls");

	if (input < 0 || input >2)
	{
		printf("�����Դϴ�. �ٽ� �Է��ϼ���.\n");
		getchar();
		getchar();
		system("cls");

		process();
	}

	switch (input)
	{
	case 1:
		printf("������ ����մϴ�.\n");
		printf("");

		break;
	case 2:
		printf("������ ��ȸ�մϴ�.\n");
		//view();
		break;
	case 0:
		break;
	}
}

void bg_process(int num, char* bom_res, char* code)
{
	char* bom_res;

	req_code* temp = (req_code*)malloc(sizeof(req_code));

	check_parts(PLAN_NUM, bom_res,temp);			//������ ���ۺ�ǰ �ִ��� �Ǵ�
	produce_parts();		//������ ���ۺ�ǰ ������ - LOT��ȣ �ʿ�...?
	//confirm_produce();	//�۾����� Ȯ�� - ���� �ִ��� Ȯ��
	give_LOT();				//����Ϸ�ǰ LOT��ȣ ����-���೯¥ ���
	produce_product();		//�����ȹ ǰ�� ����
	material_upload();		//�������� ���
}

void check_parts(int num, char* bom_res, req_code* temp)
{
	
}

//void init(void)
//{
//	_create("FILE_NAME","'ǰ���ڵ�' INT '�����ڵ�' INT '����' INT");
//	initalizing("FILE_NAME");
//	_insert("1001,2001,100");
//	_insert("1002,2002,100");
//	_insert("1003,2003,100");
//	_insert("1004,2004,100");
//	_insert("1005,2005,100");
//
//}