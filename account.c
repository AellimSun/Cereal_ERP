#include "local.h"
#include "cereal.h"



void insertAccount();
void readAccount();
void read_all();
void read_ACC_CODE();
void read_BN_REGI_NUM();
void read_PRD_CODE();
void read_RorD();
void deleteAccount();
void updateAccount();
void read_prd(char* code);
//�ŷ�ó ���� �ʱ�ȭ��
void account()
{
	int menu;
	printf("��ġ : ���θ޴� -> ������� -> �ŷ�ó����\n");
	printf("\t\t\t-----------------------------\n");
	printf("\t\t\t|*                         *|\n");
	printf("\t\t\t|     �޴��� �����ϼ���.    |\n");
	printf("\t\t\t|*                         *|\n");
	printf("\t\t\t-----------------------------\n");
	printf("\t\t\t|      1. �ŷ�ó ���       |\n");
	printf("\t\t\t-----------------------------\n");
	printf("\t\t\t|      2. �ŷ�ó ����       |\n");
	printf("\t\t\t-----------------------------\n");
	printf("\t\t\t|      3. �ŷ�ó ��ȸ       |\n");
	printf("\t\t\t-----------------------------\n");
	printf("\t\t\t|      4. �ŷ�ó ����       |\n");
	printf("\t\t\t-----------------------------\n");
	printf("\t\t\t|      0. ��������          |\n");
	printf("\t\t\t-----------------------------\n\n");

	printf("\t\t\t\t �Է� :\n");
	printf("\t\t\t\t        ^");
	gotoxy(40, 17);
	scanf("%d", &menu);

	system("cls");

	switch (menu)
	{
	case 1:
		insertAccount();
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
	case 0:
		main_manu();
		break;
	}
}

void insertAccount()
{
	char values[50];
	char ACC_CODE[5];		//�ŷ�ó �ڵ�
	char BN_REGI_NUM[20];	//����� ��� ��ȣ
	char PRD_CODE[5];			//��� ǰ�� �ڵ�
	char RorD[2];			//R:������ D:��ǰ

	printf("��ġ : ���θ޴� -> ������� -> �ŷ�ó���� -> �ŷ�ó ���\n\n");
	printf("\t\t\t==========================\n");
	printf("\t\t\t���ο� �ŷ�ó�� ����մϴ�.\n");
	printf("\t\t\t==========================\n\n");

	printf("\t\t�ŷ�ó �ڵ带 �Է��ϼ���. \n");
	printf("\n\t\t\t-> \n");
	printf("\n\t\t�ŷ�ó�� ����� ��� ��ȣ�� �Է��ϼ���. \n");
	printf("\n\t\t\t-> \n");
	printf("\n\t\t��� ǰ�� �ڵ带 �Է��ϼ���. \n");
	printf("\n\t\t\t-> \n");
	printf("\n\t\t������ �ŷ�ó�� 'R' ��ǰ �ŷ�ó�� 'D'�� �Է��ϼ���. \n");
	printf("\n\t\t\t-> \n");
	gotoxy(27,8);
	scanf("%s", ACC_CODE);
	gotoxy(27, 12);
	scanf("%s", BN_REGI_NUM);
	gotoxy(27, 16);
	scanf("%s", PRD_CODE);
	gotoxy(27, 20);
	scanf("%s", RorD);
	//printf("%s", RorD);
	//char temp = ("R\n" || "D\n");

	read_prd(PRD_CODE);

	system("cls");
	while(1)
	{
		if ((strcmp(RorD, "R") != 0) && (strcmp(RorD, "D") != 0))
		{
			printf("\n\t\t\t< �߸� �Է��߽��ϴ�! >\n");
			printf("\t  < ������ ��� �ŷ�ó�� 'R' ��ǰ ��� �ŷ�ó�� 'D�� �Է����ּ���! >\n\n");
			printf("\t\t\t 'R' Ȥ�� 'D' �Է� :  ");
			scanf("%s", RorD);
			system("cls");
		}
		else
			break;
	}
	
		printf("\n\n");
		strcpy(values, "'");
		strcat(values, ACC_CODE);
		strcat(values, "', '");
		strcat(values, BN_REGI_NUM);
		strcat(values, "', '");
		strcat(values, PRD_CODE);
		strcat(values, "', '");
		strcat(values, RorD);
		strcat(values, "'");

		printf("%s\n\n", values);

		/*if (_create("account", "ACC_CODE VARCHAR(10) BN_REGI_NUM VARCHAR(30) PRD_CODE VARCHAR(10) RorD VARCHAR(2)") == -1)
		{
			printf("%s\n", err_msg);

			return -1;
		}*/
		if (initalizing("account") == -1)
		{
			printf("%s\n", err_msg);

			file_column_free();
			return -1;
		}

		char ex1[50] = "'A1001', '18-854-1123', 'D0001', 'R'";
		char ex2[50] = "'A1002', '20-774-4556', 'D0002', 'R'";
		char ex3[50] = "'A1003', '21-814-9563', 'D0003', 'R'";

		/*if (_insert(ex1) == -1)
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
		}*/
		if (_insert(values) == -1)
		{
			printf("%s\n", err_msg);

			file_column_free();
			return -1;
		}

		print_data();
		printf("\n");
		file_column_free();

		printf("\n\t\t < ���ο� �ŷ�ó ��ϿϷ�! �������� �̵��մϴ�. >");
		system("pause");
		system("cls");
		account();
}

void readAccount()
{
	int menu;
	printf("��ġ : ���θ޴� -> ������� -> �ŷ�ó���� -> �ŷ�ó ��ȸ\n\n");
	printf("\t\t\t-----------------------------\n");
	printf("\t\t\t|*                         *|\n");
	printf("\t\t\t|     �޴��� �����ϼ���.    |\n");
	printf("\t\t\t|*                         *|\n");
	printf("\t\t\t-----------------------------\n");
	printf("\t\t\t|   1. �ŷ�ó �ڵ�� ��ȸ   |\n");
	printf("\t\t\t-----------------------------\n");
	printf("\t\t\t| 2. ����� ��� ��ȣ�� ��ȸ|\n");
	printf("\t\t\t-----------------------------\n");
	printf("\t\t\t|    3. ǰ�� �ڵ�� ��ȸ    |\n");
	printf("\t\t\t-----------------------------\n");
	printf("\t\t\t|   4. �ŷ�ó ���к� ��ȸ   |\n");
	printf("\t\t\t-----------------------------\n");
	printf("\t\t\t|       5. ��ü ��ȸ        |\n");
	printf("\t\t\t-----------------------------\n");
	printf("\t\t\t|       0. ��������         |\n");
	printf("\t\t\t-----------------------------\n");
	//printf("7.test\n");
	printf("\t\t\t\t �Է� :\n");
	printf("\t\t\t\t        ^");
	gotoxy(40, 19);
	scanf("%d", &menu);
	system("cls");
	switch (menu)
	{
	case 1:
		read_ACC_CODE();
		break;
	case 2:
		read_BN_REGI_NUM();
		break;
	case 3:
		read_PRD_CODE();
		break;
	case 4:
		read_RorD();
		break;
	case 5:
		read_all();
		break;
	case 0:
		account();
		break;
	case 7:
		//read_prd();
		break;
	}
}

void read_all()
{
	printf("��ġ : ���θ޴� -> ������� -> �ŷ�ó���� -> �ŷ�ó ��ȸ -> ��ü ��ȸ\n\n");
	if (initalizing("account") == -1)
	{
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}

	print_data();
	printf("\n");
	file_column_free();
	system("pause");
	system("cls");
	account();
}

void read_ACC_CODE()
{
	char naver[10];
	char temp[30] = "ACC_CODE='";

	result* _result;
	int result_count;


	printf("��ġ : ���θ޴� -> ������� -> �ŷ�ó���� -> �ŷ�ó ��ȸ -> �ڵ�� ��ȸ\n\n");
	printf("\t\t�˻��� �ŷ�ó�� �ڵ带 �Է��ϼ��� \n");
	printf("\t\t\t -> ");
	scanf("%s", naver);

	strcat(temp, naver);
	strcat(temp, "'");

	char* conditional = temp;
	char* select_column = "ACC_CODE, BN_REGI_NUM, PRD_CODE";

	if (initalizing("account") == -1)
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
	if ((result_count = recv_result(&_result, select_result_str)) == -1) {
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}
	result_print(_result, result_count);
	printf("\n\n");

	//print_data();
	printf("\n");
	file_column_free();
	system("pause");
	system("cls");
	account();
}

void read_BN_REGI_NUM()
{
	char naver[10];
	char temp[20] = "BN_REGI_NUM='";

	result* _result;
	int result_count;

	printf("��ġ : ���θ޴� -> ������� -> �ŷ�ó���� -> �ŷ�ó ��ȸ -> ����� ��ȣ�� ��ȸ\n\n");
	printf("\t\t�˻��� �ŷ�ó�� ����� ��ȣ�� �Է��ϼ��� : \n");
	printf("\t\t\t -> ");
	scanf("%s", naver);

	strcat(temp, naver);
	strcat(temp, "'");

	char* conditional = temp;
	char* select_column = "ACC_CODE, BN_REGI_NUM, PRD_CODE";

	if (initalizing("account") == -1)
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

	if ((result_count = recv_result(&_result, select_result_str)) == -1) {
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}
	result_print(_result, result_count);
	printf("\n\n");

	//print_data();
	printf("\n");
	file_column_free();
	system("pause");
	system("cls");
	account();
}

void read_PRD_CODE()
{
	char naver[10];
	char temp[20] = "PRD_CODE='";

	result* _result;
	int result_count;
	printf("��ġ : ���θ޴� -> ������� -> �ŷ�ó���� -> �ŷ�ó ��ȸ -> ǰ�� �ڵ�� ��ȸ\n\n");
	printf("\t\t�˻��� ǰ���� �ڵ带 �Է��ϼ��� : \n");
	printf("\t\t\t -> ");
	scanf("%s", naver);

	strcat(temp, naver);
	strcat(temp, "'");

	char* conditional = temp;
	char* select_column = "ACC_CODE, BN_REGI_NUM, PRD_CODE";

	if (initalizing("account") == -1)
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

	if ((result_count = recv_result(&_result, select_result_str)) == -1) {
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}
	result_print(_result, result_count);
	printf("\n\n");

	//print_data();
	printf("\n");
	file_column_free();
	system("pause");
	system("cls");
	account();
}

void read_RorD()
{
	char naver[5];
	char temp[20] = "RorD='";

	result* _result;
	int result_count;
	printf("��ġ : ���θ޴� -> ������� -> �ŷ�ó���� -> �ŷ�ó ��ȸ -> ����� ��ȣ�� ��ȸ\n\n");
	printf("\t\t�˻��� �ŷ�ó�� ������ �Է��ϼ��� : \n");
	printf("\t\t< ������ 'R' ��ǰ 'D' >");
	printf("\t\t\t -> ");
	scanf("%s", naver);

	strcat(temp, naver);
	strcat(temp, "'");

	char* conditional = temp;
	char* select_column = "ACC_CODE, BN_REGI_NUM, PRD_CODE";

	if (initalizing("account") == -1)
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

	if ((result_count = recv_result(&_result, select_result_str)) == -1) {
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}
	result_print(_result, result_count);
	printf("\n\n");

	//print_data();
	printf("\n");
	file_column_free();
	system("pause");
	system("cls");
	account();
}

void deleteAccount()
{
	if (initalizing("account") == -1)
	{
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}

	print_data();
	printf("\n");
	//file_column_free();

	char naver[20];
	char temp[30] = "BN_REGI_NUM='";
	printf("��ġ : ���θ޴� -> ������� -> �ŷ�ó���� -> �ŷ�ó ����\n\n");
	printf("\t\t������ �ŷ�ó�� ����� ��ȣ�� �Է��ϼ��� : \n");
	printf("\t\t -> ");
	scanf("%s", naver);
	strcat(temp, naver);
	strcat(temp, "'");

	char* conditional = temp;
	//_delete(conditional);

	if (_delete(conditional) == -1)
	{
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}

	print_data();
	printf("\n");
	file_column_free();
	system("pause");
	system("cls");
	account();
}

void updateAccount()
{
	printf("\n");
	printf(" < �ŷ�ó ��� >\n");
	printf("========================================================\n");

	//������ �ŷ�ó �� �� �ְ� ��ȸ���ֱ�
	if (initalizing("account") == -1)
	{
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}
	print_data();
	printf("\n");

	char naver1[10];
	char temp[30] = "ACC_CODE='";
	char naver2[20], naver3[10];
	char temp2[30];

	//char new_ACC_CODE[5];		//�ŷ�ó �ڵ�
	//char new_BN_REGI_NUM[20];	//����� ��� ��ȣ
	//char new_PRD_CODE[5];			//��� ǰ�� �ڵ�
	//char new_RorD[2];			//R:������ D:��ǰ

	//result* _result;
	//int result_count;

	printf("========================================================\n\n");
	printf("\t\t������ �ŷ�ó�� �ڵ带 �Է��ϼ��� : ");
	scanf("%s", naver1);

	strcat(temp, naver1);
	strcat(temp, "'");

	char* conditional = temp;

	printf("\t\t������ �÷����� �Է��ϼ��� : ");
	scanf("%s", naver2);
	printf("\t\t���ο� ���� �Է��ϼ��� : ");
	scanf("%s", naver3);
	strcat(naver2, "='");
	strcat(naver2, naver3);
	strcat(naver2, "'");
	char* set = naver2;

	if (_update(conditional, set) == -1)
	{
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}

	print_data();
	printf("\n");
	file_column_free();
	
	account();
}

void read_prd(char *code)
{
	if (initalizing("list") == -1) {
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}
	char PRD_CODE[5];
	bomRes* list = (bomRes*)malloc(sizeof(bomRes));
	bomRes* head = (bomRes*)malloc(sizeof(bomRes));

	int result_count;
	result* _result;
	char* select_column = "CODE";
	char conditional[20] = "CODE='";
	strcat(conditional, code);
	strcat(conditional, "'");

	if (_select(conditional, select_column, &select_result_str) == -1) {
		file_column_free();
		system("cls");
		printf("�����ϴ� �ʴ� ǰ���ڵ��Դϴ�.\n");
		system("pause");
		system("cls");
		insertAccount();
	}
	else {
		if ((result_count = recv_result(&_result, select_result_str)) == -1) {
			file_column_free();
			result_free(_result, result_count);
			printf("�����ϴ� �ʴ� ǰ���ڵ��Դϴ�.\n");
			insertAccount();
		}
		
	}

	file_column_free();
	result_free(_result, result_count);

	for (int i = 0; i < list->AMOUNT; i++) {

		if (initalizing("account") == -1) {
			printf("%s\n", err_msg);

			file_column_free();
			return -1;
		}

		strcpy(PRD_CODE, list->CODE);

		printf("%s\n", list->CODE);

		printf("\n");
		file_column_free();

	}

	free(list);
	free(head);
}