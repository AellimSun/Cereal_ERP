#include "cereal.h"
#include "stdbool.h"

plan* production_new_plan();
plan* production_menu();
void plan_reading();



void production_plan(void)
{
	plan* values;
	//char* conditional = "TP='q'";
	//char* set = "TP='c'";
	char* select_column = "PLAN_YEAR, PLAN_PRODUCTION, CODE";

	result* _result;
	result* find;
	int result_count;

	values = production_menu();

	// 파일 생성
	if (_create("Product_Plan", "PLAN_YEAR INT PLAN_PRODUCTION INT CODE VARCHAR(20)") == -1) {
		printf("%s\n", err_msg);

		return -1;
	}

	// 생성한 파일 정보보기
	if (initalizing("Product_Plan") == -1) {
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}
	if (_insert(values->values) == -1) {
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}

	/*if (_delete(conditional) == -1) {
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}*/

	/*if (_update(conditional, set) == -1) {
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}*/

	//print_data();
	file_column_free();

	confirm_Material(values);

	printf("\n");

	/*if (_select(conditional, select_column, &select_result_str) == -1) {
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}
	else {
		printf("%s\n\n", select_result_str);
	}

	if ((result_count = recv_result(&_result, select_result_str)) == -1) {
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}
	result_print(_result, result_count);
	printf("\n\n");*/

	/*if ((find = find_result(_result, "FLdf")) == -1) {
		printf("%s\n", err_msg);

		file_column_free();
		result_free(_result, result_count);
		return -1;
	}*/
	/*printf("     %s\n", find->name);
	printf("=============\n");
	for (int i = 0; i < result_count; i++) {
		switch (find->type) {
		case INT:
			if (int_is_null(find->_int_data[i]))
				printf("     (null)\n");
			else
				printf("     %d\n", find->_int_data[i]);
			break;
		case FLOAT:
			if (float_is_null(find->_float_data[i]))
				printf("     (null)\n");
			else
				printf("     %.5f\n", find->_float_data[i]);
			break;
		case DOUBLE:
			if (double_is_null(find->_double_data[i]))
				printf("     (null)\n");
			else
				printf("     %.12lf\n", find->_double_data[i]);
			break;
		case CHAR:
			if (char_is_null(find->_char_data[i]))
				printf("     (null)\n");
			else
				printf("     %c\n", find->_char_data[i]);
			break;
		case VARCHAR:
			if (string_is_null(find->_string_data[i]))
				printf("     (null)\n");
			else
				printf("     %s\n", find->_string_data[i]);
			break;
		}
	}

	file_column_free();
	result_free(_result, result_count);*/


	free(values);
}

plan* production_new_plan()
{
	char* str[3] = { 0 };
	char* year;
	char* product;
	char* code;

	getchar();

	printf("위치 : 메인메뉴 -> 생산관리 -> 생산계획 관리\n\n");

	printf("\t\t       < 계획연도, 연간계획량, 품목 코드 입력 > \n\n");
	printf("\t\t( 예시 : 20220301     50           Q666 )\n\n");
	printf("\t\t -> ");

	for (int i = 0; i < 3; i++)
	{
		char temp[100];
		gets(temp);
		str[i] = (char*)malloc(strlen(temp) + 1);
		strcpy(str[i], temp);

	}
	year = str[0];
	product = str[1];
	code = str[2];


	year = (char*)realloc(year, _msize(year) + _msize(product) + _msize(code) + 2);

	strcat(year, ",");
	strcat(year, product);
	strcat(year, ",");
	strcat(year, code);

	/*free(str[1]);
	free(str[2]);*/

	plan* newPlan = (plan*) malloc(sizeof(plan));
	newPlan->CODE = code;
	newPlan->PLAN_PRODUCTION = product;
	newPlan->values = year;
	/*newPlan->PLAN_PRODUCTION = product;*/

	return newPlan;
}

plan* production_menu()
{
	int key;
	plan* values;

	printf("위치 : 메인메뉴 -> 생산관리 -> 생산계획 관리\n\n");
	while(1)
	{
		printf("\t\t\t-----------------------------\n");
		printf("\t\t\t|*                         *|\n");
		printf("\t\t\t|     메뉴를 선택하세요.    |\n");
		printf("\t\t\t|*                         *|\n");
		printf("\t\t\t-----------------------------\n");
		printf("\t\t\t|      1. 새 계획 수립      |\n");
		printf("\t\t\t-----------------------------\n");
		printf("\t\t\t|     2. 계획 목록 열람     |\n");
		printf("\t\t\t-----------------------------\n\n");

		printf("\t\t\t\t 입력 :\n");
		printf("\t\t\t\t        ^");
		gotoxy(40, 12);
		scanf("%d", &key);
		system("cls");

		if (key == 1) 
		{
			values = production_new_plan();
			return values;
		}
		else if (key == 2)
		{
			plan_reading();
		}
		else printf("\n\t\t    < 잘못된 입력값입니다. > \n\n");
	}	
}

void plan_reading()		//기존 계획 열람 함수
{

}

