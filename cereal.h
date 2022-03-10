#pragma once
#include <stdio.h>
#include <Windows.h>
#include "local.h"
#include "BOMTree.h"

typedef struct Plan
{
	char PLAN_PRODUCTION[10];
	char CODE[5];
	char values[30];
} plan;