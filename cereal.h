#pragma once
#include "local.h"
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include "BOMTree.h"

typedef struct Plan
{
	char* PLAN_PRODUCTION;
	char* CODE;
	char* values;
	struct Plan* next;
} plan;


//�����ȹ �޼��� �ʿ��� ǰ��� ��, ���� �������ִ� ��, �����ؾ� �� �� ������ ���� ����ü
typedef struct _bomRes {
	char* CODE;
	int AMOUNT;
	struct _bomRes* next;
}bomRes;

//��� ������ ������ ��� ����ü
typedef struct Material {
	char PRD_CODE[5];
	char PRD_NAME[20];
	char STATUS[5];
	int DATE;
};

//����ǰ�� ���� ����ü
typedef struct _order
{
	char* ACC_CODE; //�迭���� �ּҰ��� ����Ų��.
	char* PRD_CODE; //�迭���� �ּҰ��� ����Ų��.
	int O_Day;		//������
	int D_Day;		//������
	int NUM;		//����

	struct _order* next;

}Order;
char LOT[5];

//�ŷ�ó ���� ����ü
typedef struct Accontnode {
	char ACC_CODE[10];
	char BN_REGI_NUM[10];
	char PRD_CODE[10];
	char RorD[5];
	struct Accountnode* next;
}Anode;

