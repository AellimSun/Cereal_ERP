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
//로컬

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

//서버

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

//클라이언트


static char pad = 255;
static char pad_seprator[2] = { 255,'\0' };
static char* _file_location;
char err_msg[ERR_MSG_SIZE];
char* select_result_str;   //로컬로 빠짐 (서버)
//로컬

int initalizing(char* file_name);						//"2.초기화" - 테이블 파일 이름(확장자 제외)를 매개변수로 사용
int add_column(column tmp);								//
int _create(char* file_name, char* column_list);		//"1.Create" - column_list에 "데이터타입 변수명" 형식으로 차례대로 입력
int _insert(char* values);								//"3.INSERT" - 입력할 데이터 리스트의 문자열을 매개변수로 사용(컬럼 순서대로, 구분은 반점',')
int _delete(char* conditional);							//"4.DELETE" - 조건에 맞는 데이터 전부 삭제("컬럼 = 데이터" 형식)
int _update(char* conditional, char* set);				//"5.UPDATA" - 조건에 맞는 데이터 전부 수정(조건문, 수정문 모두 "컬럼 = 데이터")
int _select(char* conditional, char* select, char** result);//"6.SELECT" - 조건에 맞는 데이터 원하는 컬럼 전부 추출
															//(조건문, 추출할 컬럼 리스트, 결과문자열 저장될 공간)("컬럼 = 데이터", "컬럼1,컬럼2,컬럼3,..",&주소값)
void print_column();									//
int print_data();										//"2.초기화" - 테이블에 입력된 데이터 출력 함수. sample.c에 있는 데이터 리스트 출력
void sdts_free(sdts* node);
void file_column_free();								//"2.초기화" - 프로그램 종료 전 initalizing 함수에 할당된 메모리 해제

//서버

int recv_result(result** result_head, char* receive);	// "7.SELECT 후처리" _select에서 추출된 결과값을 구조체에 해당타입에 맞춰 배열형태로 저장시켜주는 함수
result* find_result(result* result_head, char* column_name);
void result_print(result* result_head, int result_count);
int int_is_null(int _int_data);
int float_is_null(float _float_data);
int double_is_null(double _double_data);
int char_is_null(char _char_data);
int string_is_null(char* _string_data);
void result_free(result* node, int result_count);

//클라이언트