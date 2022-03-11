#include "cereal.h"
#include <string.h>


#define PRO_FILE_NAME "process"
#define MAT_FILE_NAME "test_pro_material"

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

void init(void);
void PRO_all_read();

void bg_process(void);
void check_parts(int num, char* bom_res, req_code*);			// ��ü�����ǰ �ʿ䷮ �ľ�
int produce_parts(req_code* head);		// ������ ��ǰ ����/ ���翡�� ��������� �ٲ�

void pro_material_create(char* p_code);
void pro_material_use(char* p_code, int num);
//give_LOT();		// ����ǰ LOT��ȣ ����
//produce_product();		//�����ȹ ǰ�� ���翡 ���� ���� ���ε�
req_code* New(req_code* head, int num, char* code);

void process(void)
{
	//init();
	//initalizing("FILE_NAME");
	int input;

	printf("�޴��� �����ϼ���.\n");

	bg_process();

}

void bg_process(void)
{
	BOM_TREE* bom_res;
	char* con = "A0001";
	bom_res = BOM_SEARCH(con);

	req_code* head = (req_code*)malloc(sizeof(req_code));
	if (head == NULL) exit(1);
	head->num = NULL;
	head->code = NULL;
	head->next = NULL;

	PRO_all_read();

	//pro_material_create();

	check_parts(PLAN_NUM, bom_res,head);			//������ ���ۺ�ǰ ���� �ľ�
	produce_parts(head);		//������ ���ۺ�ǰ ������ - LOT��ȣ �ʿ�...?
	//confirm_produce();	//�۾����� Ȯ�� - ���� �ִ��� Ȯ��
	//give_LOT();				//����Ϸ�ǰ LOT��ȣ ����-���೯¥ ���
	//produce_product();		//�����ȹ ǰ�� ���� �� ���
	//material_upload();		//�������� ���

	PRO_all_read();


	free(head);
}

void check_parts(int num, char* bom_res, req_code* head)
{
	//_BOM_Backward_PrintTree();
	New(head, 2,"B0001");
	New(head, 3,"B0002");
	New(head, 4,"B0003");
	New(head, 5,"B0004");
	New(head, 4,"C0001");
	New(head, 3,"C0002");
	New(head, 2,"C0003");
	New(head, 5,"D0001");

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
			pro_material_use(p_code, p_num);
			cnt++;
			printf("while�� : %d\n", cnt);
		}
		cur = cur->next;
	}
}

req_code* New(req_code* head, int num, char* code)
{
	req_code* NewNode = (req_code*)malloc(sizeof(req_code));
	if (NewNode == NULL) exit(1);

	NewNode->num = num;
	NewNode->code = code;
	NewNode->next = head->next;
	head->next = NewNode;
}

void pro_material_create() {

	system("pause");
	system("cls");
}

void pro_material_use(char* p_code, int p_num) {

	char* text1 = "PRD_CODE = '";
	char* text2 = "'";
	char* conditional = (char*)malloc(sizeof(text1) + sizeof(p_code) + sizeof(text2));
	if (conditional == 0) exit(1);
	char* select_column = "PRD_CODE,STATUS,LOT";
	char* set = "STATUS='uesed'";
	char* CODE = p_code;
	result* find;
	result* _result;
	int result_count;

	strcpy(conditional, text1);
	strcat(conditional, CODE);
	strcat(conditional, text2);


	if (initalizing(MAT_FILE_NAME) == -1) {
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}

	if (_select(conditional, select_column, &select_result_str) == -1) {
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}
	else {
		if ((result_count = recv_result(&_result, select_result_str)) == -1) {
			printf("%s\n", err_msg);

			file_column_free();
			result_free(_result, result_count);
			return -1;
		}
		//update �ϱ�
		while (_result->next != NULL) {
			//���� ����� �÷����� STATUS�� ���
			if (strcmp(_result->name, "STATUS") == 0) {
				//STATUS�÷��� �����ϴ� �����Ͱ� store(�������)�� ���
				if (strcmp(*(_result->_string_data), "store") == 0) {
					while (strcmp(_result->name,"LOT")!=0)
					{
						_result = _result->next;
					}				//LOT���� ����
					char* lot = (char*)malloc(sizeof(_result->_string_data));
					char* txt1 = "LOT='";
					char* txt2 = "'";
					char* conditional1 = (char*)malloc(sizeof(txt1)+sizeof(lot)+sizeof(txt2));
					char* set = "STATUS = 'used_'";
					if (conditional1 == 0) exit(1);
					
					strcpy(lot, *(_result->_string_data));

					strcpy(conditional1, txt1);
					strcat(conditional1, lot);

					strcat(conditional1, txt2);

					if (_update(conditional1,set) == -1){
						printf("%s\n", err_msg);

						file_column_free();
						return -1;
					}

					printf("������� : %s",conditional1 );
				}
			}
			_result = _result->next;
		}
	}

	//if ((find = find_result(_result, "DATE")) == -1)
	//{
	//	printf("%s\n", err_msg);

	//	result_free(_result, result_count);
	//	return -1;
	//}
	file_column_free();

	//print_data();

	result_free(_result, result_count);
	free(conditional);

	//system("pause");
	//system("cls");
}

void init(void)
{
	_create(MAT_FILE_NAME, "PRD_CODE VARCHAR(6) STATUS VARCHAR(6) DATE INT ACC_CODE VARCHAR(6) LOT VARCHAR(6)");

	char* value[30];

	value[0] = "'B0001','store',22031001,'0000','L0001'";
	value[1] = "'B0001','store',22031002,'0000','L0002'";
	value[2] = "'B0002','store',22031001,'0000','L0003'";
	value[3] = "'B0002','store',22031002,'0000','L0004'";
	value[4] = "'B0002','store',22031003,'0000','L0005'";
	value[5] = "'B0003','store',22031001,'0000','L0006'";
	value[6] = "'B0003','store',22031002,'0000','L0007'";
	value[7] = "'B0003','store',22031003,'0000','L0008'";
	value[8] = "'B0003','store',22031004,'0000','L0009'";
	value[9] = "'B0004','store',22031001,'0000','L0010'";
	value[10] = "'B0004','store',22031002,'0000','L0011'";
	value[11] = "'B0004','store',22031003,'0000','L0012'";
	value[12] = "'B0004','store',22031004,'0000','L0013'";
	value[13] = "'B0004','store',22031005,'0000','L0014'";
	value[14] = "'C0001','store',22031001,'0000','L0015'";
	value[15] = "'C0001','store',22031002,'0000','L0016'";
	value[16] = "'C0001','store',22031003,'0000','L0017'";
	value[17] = "'C0001','store',22031004,'0000','L0018'";
	value[18] = "'C0002','store',22031001,'0000','L0019'";
	value[19] = "'C0002','store',22031002,'0000','L0020'";
	value[20] = "'C0002','store',22031003,'0000','L0021'";
	value[21] = "'C0003','store',22031001,'0000','L0022'";
	value[22] = "'C0003','store',22031002,'0000','L0023'";
	value[23] = "'D0001','store',22031001,'0000','L0024'";


	if (initalizing("test_pro_material") == -1) {
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}
	int i = 0;

	while (i <= 23)
	{
		if (_insert(value[i]) == -1) {
			printf("%s\n", err_msg);

			file_column_free();
			return -1;
		}
		i++;
	}

	print_data();
	printf("\n");
	file_column_free();
}

void PRO_all_read() {
	char* conditional = "*";
	char* select_column = "PRD_CODE, STATUS, DATE, ACC_CODE, LOT";
	//char* values = "'B4001', 'store', 20220308, 'D0004'";
	int result_count;
	result* _result;

	if (initalizing(MAT_FILE_NAME) == -1) {
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}

	if (_select(conditional, select_column, &select_result_str) == -1) {
		printf("��ȸ�� �����Ͱ� �����ϴ�.\n");

		file_column_free();
		system("pause");
		system("cls");
		stock();
	}
	else {
		if ((result_count = recv_result(&_result, select_result_str)) == -1) {
			printf("%s\n", err_msg);

			file_column_free();
			return -1;
		}
		result_print(_result, result_count);
		printf("\n\n");
	}

	file_column_free();
	result_free(_result, result_count);

	system("pause");
	system("cls");
}