#include "local.h"

typedef struct _BOM_TREE
{
	char NODE_CODE[6];
	int REQ_NUM;

	struct _BOM_TREE* LeftChild;
	struct _BOM_TREE* RightSibling;
}BOM_TREE;



int main() {

	char* values[14] =
	{
		"'A0001', 'A0001', 1, NULL",
		"'A0001', 'B0001', 5, 'A0001'",
		"'A0001', 'B0002', 3, 'A0001'",
		"'A0001', 'C0001', 2, 'B0001'",
		"'A0001', 'C0002', 2, 'B0001'",
		"'A0001', 'C0003', 1, 'B0002'",
		"'A0001', 'C0004', 3, 'B0002'",
		"'A0002', 'A0001', 1, NULL",
		"'A0002', 'B0001', 2, 'A0001'",
		"'A0002', 'B0002', 2, 'A0001'",
		"'A0002', 'C0001', 1, 'B0001'",
		"'A0002', 'C0002', 5, 'B0001'",
		"'A0002', 'C0003', 4, 'B0002'",
		"'A0002', 'C0004', 1, 'B0002'"
	};

	//char* values = "'A0002', 'C0004', 1, 'B0002'";

	char* conditional = "ROOT_CODE = 'A0001'";
	//char* set = "codeNum=1015";

	char* select_column = "ROOT_CODE, NODE_CODE, REQ_NUM, M_CODE";

	result* _result;
	//result* find;
	int result_count;

	//_create("BOM_SAMPLE_3", "ROOT_CODE VARCHAR(6) NODE_CODE VARCHAR(6) REQ_NUM INT M_CODE VARCHAR(6)");

	if (initalizing("BOM_SAMPLE_3") == -1) {
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}

	/*if (_insert(values) == -1) {
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}*/

	/*for (int i = 0; i < 14; i++)
	{
		if (_insert(values[i]) == -1) {
			printf("%s\n", err_msg);

			file_column_free();
			return -1;
		}
	}*/

	print_data();
	printf("\n");

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

	if (_select(conditional, select_column, &select_result_str) == -1) {
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}
	else {
		//printf("%s\n\n", select_result_str);
	}


	//file_column_free();

	/**//**//**/
	if ((result_count = recv_result(&_result, select_result_str)) == -1) {
		printf("%s\n", err_msg);

		file_column_free();
		return -1;
	}
	result_print(_result, result_count);
	printf("\n\n");

	/**//**//**/

	/*if ((find = find_result(_result, "M_CODE")) == -1) {
		printf("%s\n", err_msg);

		file_column_free();
		result_free(_result, result_count);
		return -1;
	}
	printf("     %s\n", find->name);
	printf("=============\n");
	for (int i = 0; i < result_count; i++) {
		switch (find->type) {
		case _INT:
			if (int_is_null(find->_int_data[i]))
				printf("     (null)\n");
			else
				printf("     %d\n", find->_int_data[i]);
			break;
		case _FLOAT:
			if (float_is_null(find->_float_data[i]))
				printf("     (null)\n");
			else
				printf("     %.5f\n", find->_float_data[i]);
			break;
		case _DOUBLE:
			if (double_is_null(find->_double_data[i]))
				printf("     (null)\n");
			else
				printf("     %.12lf\n", find->_double_data[i]);
			break;
		case _CHAR:
			if (char_is_null(find->_char_data[i]))
				printf("     (null)\n");
			else
				printf("     %c\n", find->_char_data[i]);
			break;
		case _VARCHAR:
			if (string_is_null(find->_string_data[i]))
				printf("     (null)\n");
			else
				printf("     %s\n", find->_string_data[i]);
			break;
		}
	}*/

	//file_column_free();
	//result_free(_result, result_count);
}