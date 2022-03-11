#include "local.h"
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

result* _result;
result* find;
int result_count;

int main(void)
{
	//if (_create("sample_Client", "ACC_CODE VARCHAR(10) PRD_CODE VARCHAR(10) BN_REGI_NUM INT NAME VARCHAR(10)") == -1)
	//{
	//	printf("%s\n", err_msg);
	//	return -1;
	//}

	//if (_create("sample_Order", "O_DATE INT D_DATE INT ACC_CODE VARCHAR(10) ORDER_NUM INT PRD_CODE VARCHAR(10) NUM INT") == -1)
	//{
	//	printf("%s\n", err_msg);
	//	return -1;
	//}

	//if (_create("sample_Client", "ACC_CODE VARCHAR(10)") == -1)
	//{
	//	printf("%s\n", err_msg);
	//	return -1;
	//}
	

	//if (initalizing("sample_Client") == -1) {
	//	printf("%s\n", err_msg);

	//	file_column_free();
	//	return -1;
	//}
	//if (_insert("'b003', 'co002', null, 3211") == -1) {
	//	printf("%s\n", err_msg);

	//	file_column_free();
	//	return -1;
	//}
	 
	if (initalizing("account") == -1) {
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}
	//print_data();

	/*
	//if (_insert("'hi'") == -1) {
	//	printf("%s\n", err_msg);

	//	file_column_free();
	//	return -1;
	//}

	//if (_insert("'a001', 'co001', NULL, 'sample01'") == -1) {
	//	printf("%s\n", err_msg);

	//	file_column_free();
	//	return -1;
	//}

	//if (_insert("'b001' , 'am001', 3321723, '샘플02'") == -1) {
	//	printf("%s\n", err_msg);

	//	file_column_free();
	//	return -1;
	//}

	//if (_insert("'a002' , 'ch001', 3321723, 'sample03'") == -1) {
	//	printf("%s\n", err_msg);

	//	file_column_free();
	//	return -1;
	//}

	//if (_insert("'b002' , 'co002', 3321723, '샘플04'") == -1) {
	//	printf("%s\n", err_msg);

	//	file_column_free();
	//	return -1;
	//}

	//if (_insert("'d001' , 'c003', 3321723, '샘플05'") == -1) {
	//	printf("%s\n", err_msg);

	//	file_column_free();
	//	return -1;
	//}

	//if (_insert("'a006' , 'c004', 3321723, 'sample06'") == -1) {
	//	printf("%s\n", err_msg);

	//	file_column_free();
	//	return -1;
	//}

	//if (_insert("'a008' , 'c010', 3321723, 'sample07'") == -1) {
	//	printf("%s\n", err_msg);

	//	file_column_free();
	//	return -1;
	//}
	 
	*/




	if (_select("*", "ACC_CODE, BN_REGI_NUM, PRD_CODE, RorD", &select_result_str) == -1) {
	//if (_select("*", "O_DATE, D_DATE , ACC_CODE , ORDER_NUM , PRD_CODE , NUM INT", &select_result_str) == -1) {

		
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}
	else {
		//printf("%s\n\n", select_result_str);
		printf("\n...조건을 만족하는 데이터가 존재합니다\n\n");
	}
	//print_data();
	if ((result_count = recv_result(&_result, select_result_str)) == -1) {
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}
	result_print(_result, result_count);
	printf("\n\n");

	//if ((find = find_result(_result, "FLdf")) == -1) {
	//	printf("%s\n", err_msg);

	//	file_column_free();
	//	result_free(_result, result_count);
	//	return -1;
	//}


	file_column_free();
	return 0;
}
