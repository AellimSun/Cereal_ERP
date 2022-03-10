#include "cereal.h"
#include <stdio.h>


//int main(void)
//{
//	char* values = "NULL, 800, 'q', 69.11212, 4215.134555666777";
//	char* conditional = "TP='q'";
//	char *set = "TP='c'";
//	char* select_column = "code, number, TP, FLT, DBL";
//
//	result* _result;
//	result* find;
//	int result_count;
//
//	if (initalizing("D:\\git\\my\\Project1\\samplec") == -1)
//	{
//		printf("%s\n", err_msg);
//
//		file_column_free();
//		return -1;
//	}
//	print_data();
//
//	printf("n");
//
//}


typedef struct Materialsnode {
	char CODE[5];
	char NAME[20];
	int backup;
	struct Materialsnode* next;
}Matls;

void insertMaterials();
void updateMaterials();
void readMaterials();
void deleteMaterials();

void product_list()
{
	//_create("list", "CODE VARCHAR(6) NAME VARCHAR(30) BACKUP INT");
	//print_data();
	
		if (initalizing("list") == -1)
		{
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
		}
	
		_insert("'A0000', '�ٳ���', 10");
		
		print_data();

		file_column_free();

	int menu;
	printf("����ǰ�� ���\n");
	printf("����ǰ�� ����\n");
	printf("����ǰ�� ��ȸ\n");
	printf("����ǰ�� ����\n");
	scanf("%d", &menu);

	switch (menu)
	{
	case 1:
		insertMaterials();
		break;
	case 2:
		updateMaterials();
		break;
	case 3:
		readMaterials();
		break;
	case 4:
		deleteMaterials();
		break;
	}
}


void insertMaterials()
{
	char value[50];
	char CODE[5];
	char NAME[30];
	int safe_stock;

	printf("==================\n");
	printf("���縦 ����մϴ�.\n");
	printf("==================\n\n");

	printf("����ǰ�� �ڵ� ��� : \n");
	//printf("���� ��� ���� �ڵ� : ****");
	scanf("%s", CODE);
	printf("����ǰ�� �̸� ��� : ");
	scanf("%s", NAME);
	printf("���� ��� ��� : ");
	scanf("%d", &safe_stock);

	//Matls* newNode = (Matls*)malloc(sizeof(Matls));
	//if (newNode == NULL)
	//	return;
	//strcpy(newNode->CODE, CODE);
	//strcpy(newNode->materials_name, Materials_name);
	//strcpy(newNode->backup, safe_stock);

	strcpy(value, "'");
	strcat(value, CODE);
	strcat(value, "','");
	strcat(value, NAME);
	strcat(value, "'");
	//strcat(value, safe_stock);
	//strcat(value, "'");

	printf("%s\n", value);

	if (initalizing("33") == -1)
	{
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}

	char ex1[50] = "'M1001', '������'";
	char ex2[50] = "'M1002', '����'";
	char ex3[50] = "'M1003', '�ұ�'";

	if (_insert(value) == -1)
	{
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}

	print_data();
	printf("\n");
	file_column_free();

	printf("���ο� ����ǰ�� ��ϿϷ�. �������� �̵��մϴ�.");
	system("pause");
	system("cls");
	main();
}

void updateMaterials()
{

}

void readMaterials()
{
	int menu;

	printf("1. ����ǰ�� �ڵ�� ��ȸ\n");
	printf("2. ����ǰ�� �̸����� ��ȸ\n");
	scanf("%d", &menu);

	switch (menu)
	{
	case 1:
		read_CODE();
		break;
	case 2:
		read_materials_name();
		break;
	}
}

void deleteMaterials()
{

}

void read_CODE()
{
	char search[5];
	char temp[20] = "CODE='";

	printf("�˻��� ����ǰ�� �ڵ带 �Է� : ");
	scanf("%s", search);

	strcat(temp, search);
	strcat(temp, "'");

	char* conditional = "CODE='M1001'";
	char* select_column = "CODE, NAME";

	if (initalizing("33") == -1)
	{
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}
	printf("%s", conditional);

	if (_select(conditional, select_column, &select_result_str) == -1)
	{
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}
	else {
		printf("%s\n", select_result_str);
	}

	print_data();
	printf("\n");
	file_column_free();

	main();

}

void read_materials_name()
{
	char search[5];
	char temp[20] = "NAME='";

	printf("�˻��� �ŷ�ó�� ����� ��ȣ�� �Է��ϼ��� : ");
	scanf("%s", search);

	strcat(temp, search);
	strcat(temp, "'");

	char* conditional = temp;
	char* select_column = "CODE, NAME";

	if (initalizing("33") == -1)
	{
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}


	if (_select(conditional, select_column, &select_result_str) == -1)
	{
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}
	else {
		printf("%s\n", select_result_str);
	}

	print_data();
	printf("\n");
	file_column_free();

	main();
}

