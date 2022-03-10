#pragma once
#include "local.h"
#include <stdio.h>
#include <Windows.h>
#include "BOMTree.h"

typedef struct Plan
{
	int PLAN_PRODUCTION;
	char CODE[5];
	char values[30];
} plan;