#include "cereal.h"

#define FILE_NAME "process"
typedef struct _process {
	int data;
	struct _process* next;
}S_process;
void init(void);

void process(void)
{
	//init();
	initalizing("FILE_NAME");
	int input;
	printf("�޴��� �����ϼ���.\n");
	printf("1.�������\n");
	printf("2.������ȸ\n");
	printf("0.��������\n");
	scanf("%d", &input);
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
		printf("");
		break;
	case 0:
		break;
	}
}

void init(void)
{
	_create("FILE_NAME","'ǰ���ڵ�' INT '�����ڵ�' INT '����' INT");
	initalizing("FILE_NAME");
	_insert("1001,2001,100");
	_insert("1002,2002,100");
	_insert("1003,2003,100");
	_insert("1004,2004,100");
	_insert("1005,2005,100");

}