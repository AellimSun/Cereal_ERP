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

	//if (_create("sample_Client", "ACC_CODE VARCHAR(10)") == -1)
	//{
	//	printf("%s\n", err_msg);
	//	return -1;
	//}

	if (initalizing("D:\\00_Bird_00\\ý��\\project\\Cereal\\Clanguage\\make_Sample_file\\make_Sample_file\\sample_Client") == -1) {
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}
	if (_insert("'a001', 'co001', NULL, 'sample08'") == -1) {
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}
	print_data();

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

	//if (_insert("'b001' , 'am001', 3321723, '����02'") == -1) {
	//	printf("%s\n", err_msg);

	//	file_column_free();
	//	return -1;
	//}

	//if (_insert("'a002' , 'ch001', 3321723, 'sample03'") == -1) {
	//	printf("%s\n", err_msg);

	//	file_column_free();
	//	return -1;
	//}

	//if (_insert("'b002' , 'co002', 3321723, '����04'") == -1) {
	//	printf("%s\n", err_msg);

	//	file_column_free();
	//	return -1;
	//}

	//if (_insert("'d001' , 'c003', 3321723, '����05'") == -1) {
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


	if (_select("PRD_CODE=co001","ACC_CODE, PRD_CODE, BN_REGI_NUM, NAME", &select_result_str) == -1) {
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}
	else {
		//printf("%s\n\n", select_result_str);
		printf("\n...������ �����ϴ� �����Ͱ� �����մϴ�\n\n");
	}

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
