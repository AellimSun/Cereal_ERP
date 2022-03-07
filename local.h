#pragma once
#define _CRT_SECURE_NO_WARNINGS
#define INT 1
#define FLOAT 2
#define DOUBLE 3
#define CHAR 4
#define VARCHAR 5
#define ERR_MSG_SIZE 51
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>
#include <math.h>
//����

typedef struct column {
	char* name;
	unsigned int length;
	int type;
	int start_index;
	struct column* next;
}column;
typedef struct search_data_to_string {
	char* str;
	struct search_data_to_string* next;
}sdts;

//����

typedef struct result_column {
	char* name;
	int type;

	int* _int_data;
	float* _float_data;
	double* _double_data;
	char* _char_data;
	char** _string_data;
	struct result_column* next;

}result;

//Ŭ���̾�Ʈ


static char pad = 255;
static char pad_seprator[2] = { 255,'\0' };
static char* _file_location;
char err_msg[ERR_MSG_SIZE];
char* select_result_str;   //���÷� ���� (����)
//����

int initalizing(char* file_name);						//"2.�ʱ�ȭ" - ���̺� ���� �̸�(Ȯ���� ����)�� �Ű������� ���
int add_column(column tmp);								//
int _create(char* file_name, char* column_list);		//"1.Create" - column_list�� "������Ÿ�� ������" �������� ���ʴ�� �Է�
int _insert(char* values);								//"3.INSERT" - �Է��� ������ ����Ʈ�� ���ڿ��� �Ű������� ���(�÷� �������, ������ ����',')
int _delete(char* conditional);							//"4.DELETE" - ���ǿ� �´� ������ ���� ����("�÷� = ������" ����)
int _update(char* conditional, char* set);				//"5.UPDATA" - ���ǿ� �´� ������ ���� ����(���ǹ�, ������ ��� "�÷� = ������")
int _select(char* conditional, char* select, char** result);//"6.SELECT" - ���ǿ� �´� ������ ���ϴ� �÷� ���� ����
															//(���ǹ�, ������ �÷� ����Ʈ, ������ڿ� ����� ����)("�÷� = ������", "�÷�1,�÷�2,�÷�3,..",&�ּҰ�)
void print_column();									//
int print_data();										//"2.�ʱ�ȭ" - ���̺� �Էµ� ������ ��� �Լ�. sample.c�� �ִ� ������ ����Ʈ ���
void sdts_free(sdts* node);
void file_column_free();								//"2.�ʱ�ȭ" - ���α׷� ���� �� initalizing �Լ��� �Ҵ�� �޸� ����

//����

int recv_result(result** result_head, char* receive);	// "7.SELECT ��ó��" _select���� ����� ������� ����ü�� �ش�Ÿ�Կ� ���� �迭���·� ��������ִ� �Լ�
result* find_result(result* result_head, char* column_name);
void result_print(result* result_head, int result_count);
int int_is_null(int _int_data);
int float_is_null(float _float_data);
int double_is_null(double _double_data);
int char_is_null(char _char_data);
int string_is_null(char* _string_data);
void result_free(result* node, int result_count);

//Ŭ���̾�Ʈ