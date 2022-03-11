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
	char STATUS[5];
	int DATE;
	char ACC_CODE[5];
	char LOT[5];
};