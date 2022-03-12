#include "cereal.h"
#include <string.h>
#include <time.h>

#define PRO_FILE_NAME "process"
//#define MAT_FILE_NAME "test_pro_material"
#define MAT_FILE_NAME "material"
#define BOM_FILE_NAME "BOM_SAMPLE_3"

void init(void);
void PRO_all_read();

void bg_process(plan* prd_plan, bomRes* result);
//void check_parts(bomRes*);			// 자체생산부품 필요량 파악
int produce_parts(bomRes* head);			// 생산계획따라 자재에서 사용함으로 바꿈
void produce_product(char* p_code, int p_num);		//  생산계획따라 품목 자재에 생산 수량 업로드
void pro_material_create(char* p_code);
void pro_material_use(char* p_code, int num);
char* give_LOT();		// 생산품 LOT번호 생성

bomRes* New(bomRes* head, int num, char* code);
bomRes* Head(void);
void free_node(bomRes* head);

//void process(*plan prd_plan)
void process(bomRes* result , plan* p)
{
	plan* tmp = p;
	bomRes* p_use_amount = result;
	system("cls");
	PRO_all_read();
	system("pause");
	//init();
	printf("\n");
	printf("\t\t\t-----------------------------\n");
	printf("\t\t\t|*                         *|\n");
	printf("\t\t\t|*          잠시후         *|\n");
	printf("\t\t\t|*    공정이 시작됩니다.   *|\n");
	printf("\t\t\t|*                         *|\n");
	printf("\t\t\t-----------------------------\n");
	Sleep(2500);
	system("cls");
	bg_process(tmp, p_use_amount);

	PRO_all_read();
	system("pause");
	free(tmp);
	main_manu();
}

void bg_process(plan* prd_plan, bomRes* result)
{
	char* p_code = prd_plan->CODE;
	int p_num = atoi(prd_plan->PLAN_PRODUCTION);

	//bomRes* mat_head = Head();

	//check_parts(mat_head);				//부족한 제작부품 개수 파악
	produce_parts(result);			//부족한 제작부품 생산명령, 원자재 사용
	produce_product(p_code,p_num);		//생산계획 품목 생산 및 등록

	system("pause");

	free_node(result);
}

//void check_parts(bomRes* head)
//{
//	//_BOM_Backward_PrintTree();
//
//	New(head, 1, "B0001");//2
//	New(head, 2, "B0002");//3
//	New(head, 2, "B0003");//4
//	New(head, 3, "B0004");//5
//	New(head, 2, "C0001");//4
//	New(head, 2, "C0002");//3
//	New(head, 2, "C0003");//2
//	New(head, 1, "D0001");//5
//}

int produce_parts(bomRes* head)
{
	bomRes* cur = head->next;
	int p_num;
	char* p_code;
	int cnt = 0;

	while (cur != NULL)
	{
		p_num = cur->AMOUNT;
		p_code = cur->CODE;
		//printf("pro_material_use 실행 %d번\n", cnt + 1);
		printf("\n");
		printf("\t\t\t-----------------------------\n");
		printf("\t\t\t|*                         *|\n");
		printf("\t\t\t|       자재 생산중...      |\n");
		printf("\t\t\t|*                         *|\n");
		printf("\t\t\t-----------------------------\n");
		//printf("\t\t\t\t\n");
		pro_material_use(p_code, p_num);
		cnt++;
		cur = cur->next;
	}
}
bomRes* Head(void)
{
	bomRes* head = (bomRes*)malloc(sizeof(bomRes));
	if (head == NULL) exit(1);
	head->AMOUNT = NULL;
	head->CODE = NULL;
	head->next = NULL;
	return head;
}
bomRes* New(bomRes* head, int num, char* code)
{
	bomRes* NewNode = (bomRes*)malloc(sizeof(bomRes));
	if (NewNode == NULL) exit(1);

	NewNode->AMOUNT = num;
	NewNode->CODE = code;
	NewNode->next = head->next;
	head->next = NewNode;
}
void free_node(bomRes* head)
{
	bomRes* cur = head->next;
	if (cur == NULL) exit(1);
	while (cur->next != NULL)
	{
		head = cur;
		cur = cur->next;
		free(head);
	}
	free(cur);
}

void pro_material_use(char* p_code, int p_num) {

	char* text1 = "PRD_CODE = '";
	char* text2 = "'";
	char* conditional = (char*)malloc(sizeof(text1) + sizeof(p_code) + sizeof(text2));
	if (conditional == 0) exit(1);

	char* select_column = "PRD_CODE,STATUS,LOT";
	char* set = "STATUS='uesed'";
	char* CODE = p_code;
	result* _result;
	result* cur;
	int result_count;
	int cnt = 0;

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
		int i = 0;

		if ((result_count = recv_result(&_result, select_result_str)) == -1) {
			printf("%s\n", err_msg);

			file_column_free();
			result_free(_result, result_count);
			return -1;
		}
		//result_print(_result, result_count);
		//system("pause");
		printf("\t\t\t|*     품목코드 = %s    *|\n", CODE);
		printf("\t\t\t-----------------------------\n");
		//update 하기
		for (int i = 0; i < p_num; i++) {
			cur = _result;
			while (1) {
				//현재 노드의 컬럼명이 STATUS일 경우
				if (strcmp(cur->name, "STATUS") == 0) {
					//STATUS컬럼에 대응하는 데이터가 store(저장상태)일 경우
					if (strcmp(cur->_string_data[i], "store") == 0) {
						while (strcmp(cur->name, "LOT") != 0)
						{
							cur = cur->next;
						}				//LOT까지 가기
						char* lot = (char*)malloc(sizeof(cur->_string_data[i]));
						if (lot == 0) exit(1);
						char* txt1 = "LOT='";
						char* txt2 = "'";
						char* conditional1 = (char*)malloc(sizeof(txt1) + sizeof(lot) + sizeof(txt2));
						if (conditional1 == 0) exit(1);
						char* set = "STATUS = '_used'";

						strcpy(lot, cur->_string_data[i]);
						strcpy(conditional1, txt1);
						strcat(conditional1, lot);
						strcat(conditional1, txt2);

						if (_update(conditional1, set) == -1) {
							printf("%s\n", err_msg);

							file_column_free();
							return -1;
						}
						printf("\t\t\t|*   사용자재 %s  *|\n", conditional1);
						printf("\t\t\t-----------------------------\n");

						cnt++;
						free(conditional1);
						free(lot);
					}
				}

				if (cur->next == NULL)
					break;
				else
					cur = cur->next;
			}

		}
		if (cnt < p_num) printf("자재가 부족합니다.\n");
	}
	file_column_free();
	result_free(_result, result_count);
	free(conditional);

	Sleep(3000);
	system("cls");
}
void pro_material_create(char* p_code) {
	char values[50];
	char* PRD_CODE = p_code;
	char STATUS[6] = "store";
	char DATE[9] = {""};
	char tmp[9] = {""};
	char LOT[6];

	strcpy(LOT,give_LOT());

	//날짜 입력
	time_t t = time(NULL);
	struct tm tm = *localtime(&t);
	sprintf(tmp, "%d", tm.tm_year+1900);

	strcpy(DATE, tmp);
	if (tm.tm_mon < 10)
	{
		strcat(DATE, "0");
	}
	sprintf(tmp, "%d", tm.tm_mon);
	strcat(DATE, tmp);
	sprintf(tmp, "%d", tm.tm_mday);
	strcat(DATE, tmp);

	strcpy(values, "'");
	strcat(values, PRD_CODE);
	strcat(values, "', '");
	strcat(values, STATUS);
	strcat(values, "', ");
	strcat(values, DATE);
	strcat(values, ", '");
	strcat(values, LOT);
	strcat(values, "'");
	printf("\n");

	//_create("material", "PRD_CODE VARCHAR(6) STATUS VARCHAR(6) DATE INT LOT VARCHAR(6)");

	if (initalizing(MAT_FILE_NAME) == -1) {
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}

	if (_insert(values) == -1) {
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}

	//print_data();
	//printf("\n");
	file_column_free();

}
char* give_LOT(void)
{
	char LOT[6] = {""};
	int random = 0;
	char tmpRand[5];

	srand(time(NULL));
	random = (rand() % 10000);
	if (random < 1000) 	strcpy(LOT, "L0");
	else strcpy(LOT, "L");
	strcat(LOT, itoa(random, tmpRand, 10));
	Sleep(1000);		//수정,1초 지나게함
	//printf("LOT = %s", LOT);
	return LOT;
}
void produce_product(char* p_code, int p_num)
{
	for (int i = 0; i < p_num; i++)
	{
		pro_material_create(p_code);
	}
	//printf("\n");
	gotoxy(0, 1);
	printf("\t\t\t-----------------------------\n");
	printf("\t\t\t|*                         *|\n");
	printf("\t\t\t|       자재 생산 완료!     |\n");
	printf("\t\t\t|*                         *|\n");
	printf("\t\t\t-----------------------------\n");
	printf("\t\t\t|*   생산한 자재 : %s   *|\n", p_code);
	printf("\t\t\t-----------------------------\n");
	printf("\t\t\t|*        생산량 : %d       *|\n", p_num);
	printf("\t\t\t-----------------------------\n");

	Sleep(3000);
}

void init(void)
{
	_create(MAT_FILE_NAME, "PRD_CODE VARCHAR(6) STATUS VARCHAR(6) DATE INT LOT VARCHAR(6)");

	char* value[30];

	value[0] = "'B0001','store',22031001,'L0001'";
	value[1] = "'B0001','store',22031002,'L0002'";
	value[2] = "'B0002','store',22031001,'L0003'";
	value[3] = "'B0002','store',22031002,'L0004'";
	value[4] = "'B0002','store',22031003,'L0005'";
	value[5] = "'B0003','store',22031001,'L0006'";
	value[6] = "'B0003','store',22031002,'L0007'";
	value[7] = "'B0003','store',22031003,'L0008'";
	value[8] = "'B0003','store',22031004,'L0009'";
	value[9] = "'B0004','store',22031001,'L0010'";
	value[10] = "'B0004','store',22031002,'L0011'";
	value[11] = "'B0004','store',22031003,'L0012'";
	value[12] = "'B0004','store',22031004,'L0013'";
	value[13] = "'B0004','store',22031005,'L0014'";
	value[14] = "'C0001','store',22031001,'L0015'";
	value[15] = "'C0001','store',22031002,'L0016'";
	value[16] = "'C0001','store',22031003,'L0017'";
	value[17] = "'C0001','store',22031004,'L0018'";
	value[18] = "'C0002','store',22031001,'L0019'";
	value[19] = "'C0002','store',22031002,'L0020'";
	value[20] = "'C0002','store',22031003,'L0021'";
	value[21] = "'C0003','store',22031001,'L0022'";
	value[22] = "'C0003','store',22031002,'L0023'";
	value[23] = "'D0001','store',22031001,'L0024'";


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

	//print_data();
	//printf("\n");
	file_column_free();
}

void PRO_all_read() {
	char* conditional = "*";
	char* select_column = "PRD_CODE, STATUS, DATE, LOT";
	//char* values = "'B4001', 'store', 20220308, 'L0004'";
	int result_count;
	result* _result;

	if (initalizing(MAT_FILE_NAME) == -1) {
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}

	if (_select(conditional, select_column, &select_result_str) == -1) {
		printf("조회할 데이터가 없습니다.\n");

		file_column_free();
		system("pause");
		system("cls");
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