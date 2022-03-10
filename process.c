#include "cereal.h"

#define PRO_FILE_NAME "process"
#define MAT_FILE_NAME "material"

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
void bg_process(void);
//req_code* NewNode();

void check_parts(int num, char* bom_res, req_code*);			// ��ü�����ǰ �ʿ䷮ �ľ�
int parts_produce(int num, char* bom_res, char* code);		// ������ ��ǰ ����/ ���翡 ��ǰ�� ���� ���ε�
give_LOT();		// ����ǰ LOT��ȣ ����
produce_product();		//�����ȹ ǰ�� ���翡 ���� ���� ���ε�
req_code* New(req_code* head, int num, char* code);

void process(void)
{
	//init();
	//initalizing("FILE_NAME");
	int input;

	printf("�޴��� �����ϼ���.\n");

	bg_process();

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

void bg_process(void)
{
	char* bom_res;
	char* con = "A1000S";
	BOM_SEARCH(con);

	req_code* head = (req_code*)malloc(sizeof(req_code));

	check_parts(PLAN_NUM, bom_res,head);			//������ ���ۺ�ǰ ���� �ľ�
	produce_parts(head);		//������ ���ۺ�ǰ ������ - LOT��ȣ �ʿ�...?
	//confirm_produce();	//�۾����� Ȯ�� - ���� �ִ��� Ȯ��
	//give_LOT();				//����Ϸ�ǰ LOT��ȣ ����-���೯¥ ���
	//produce_product();		//�����ȹ ǰ�� ���� �� ���
	//material_upload();		//�������� ���
}

void check_parts(int num, char* bom_res, req_code* head)
{
	//_BOM_Backward_PrintTree();
	New(head, 10,"A1000");
	New(head, 20,"A5000");
	New(head, 30,"A6000");
	New(head, 40,"A7000");
	New(head, 50,"A8000");


	while (0);
}

int produce_parts(req_code* head)
{
	req_code* cur = head->next;
	int p_num;
	char* p_code;

	while (cur != NULL)
	{
		int cnt = 0;
		p_num = cur->num;
		p_code = cur->code;
		while (cnt < p_num)
		{

			cnt++;
		}
		cur = cur->next;
	}
}

req_code* New(req_code* head, int num, char* code)
{
	req_code* NewNode = (req_code*)malloc(sizeof(req_code));
	NewNode->num = num;
	NewNode->code = code;
	NewNode->next = head->next;
	head->next = NewNode;
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