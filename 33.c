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
	int BACKUP;
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
	int BACKUP;

	printf("==================\n");
	printf("���縦 ����մϴ�.\n");
	printf("==================\n\n");

	printf("����ǰ�� �ڵ� ��� : \n");
	//printf("���� ��� ���� �ڵ� : ****");
	scanf("%s", CODE);
	printf("����ǰ�� �̸� ��� : ");
	scanf("%s", NAME);
	printf("���� ��� ��� :(g) ");
	scanf("%d", BACKUP);

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
	strcat(value, "','");
	strcat(value, BACKUP);
	strcat(value, "'");

	printf("%s\n", value);

	if (initalizing("product_list") == -1)
	{
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}

	char ex1[50] = "'M1001', '������', '400'";
	char ex2[50] = "'M1002', '����', '50'";
	char ex3[50] = "'M1003', '�ұ�', '10'";

	if (_insert(ex1) == -1)
	{
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}

	if (_insert(ex2) == -1)
	{
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}

	if (_insert(ex3) == -1)
	{
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}

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
	printf("3. ����ǰ�� ��ü��ȸ\n");
	printf("0. ��������\n");
	scanf("%d", &menu);

	switch (menu)
	{
	case 1:
		read_CODE();
		break;
	case 2:
		read_NAME();
		break;
	case 3:
		read_Code_Name_Backup();
		break;
	case 0:
		product_list();
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

	result* _result;
	int result_count;

	printf("�˻��� ����ǰ�� �ڵ带 �Է� : ");
	scanf("%s", search);

	strcat(temp, search);
	strcat(temp, "'");

	char* conditional = temp;
	char* select_column = "CODE, NAME, BACKUP";

	if (initalizing("product_list") == -1)
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
	else 
	{
		printf("%s\n", select_result_str);
	}
	if ((result_count = recv_result(&_result, select_result_str)) == -1) 
	{
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}
	result_print(_result, result_count);

	print_data();
	printf("\n");
	file_column_free();

	main();

}

void read_NAME()
{
	char search[5];
	char temp[20] = "NAME='";

	result* _result;
	int result_count;

	printf("�˻��� ����ǰ�� �̸��� �Է��ϼ��� : ");
	scanf("%s", search);

	strcat(temp, search);
	strcat(temp, "'");

	char* conditional = temp;
	char* select_column = "CODE, NAME, BACKUP";

	if (initalizing("product_list") == -1)
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
	else 
	{
		printf("%s\n", select_result_str);
	}

	if ((result_count = recv_result(&_result, select_result_str)) == -1) 
	{
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}
	result_print(_result, result_count);
	printf("\n\n");


	print_data();
	printf("\n");
	file_column_free();

	main();
}

void read_Code_Name_Backup()
{
	if (initalizing("product_list") == -1)
	{
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}

	print_data();
	printf("\n");
	file_column_free();

	product_list();
}