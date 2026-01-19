#include "Anchor/Anchor.h"

#include <stdio.h>
#include <stdlib.h>

static void PrintVersion(void);
static void PrintInt(int num);
static void PrintString(const char *str);

int main(int argc, char **argv)
{
	Anchor_Context *context = Anchor_Context_Create();

	Anchor_NewSwitch(context, "-v", "--version", "Show version");
	Anchor_NewSwitch(context, NULL, "--show", "Show PosArg");

	Anchor_NewOption(context, "-i", "--int", "Print int");
	Anchor_NewOption(context, "-s", "--str", "Print String");

	Anchor_Parse(context, argv, argc);

	if (Anchor_IsSet(context, "-v"))
	{
		PrintVersion();
		PrintString(Anchor_GetValue(context, "-v", NULL));
	}

	if (Anchor_IsSet(context, "-i"))
	{
		int outInt = atoi(Anchor_GetValue(context, "-i", 0));
		PrintInt(outInt);
	}

	const char *outStr = Anchor_GetValue(context, "-s", NULL);
	if (outStr)
		PrintString(outStr);

	size_t posArgCount = Anchor_GetPosArgCount(context);
	if (Anchor_IsSet(context, "--show"))
	{
		printf("Count: %zu\n", posArgCount);

		for (size_t i = 0; i < posArgCount; i++)
			printf("%zu: %s\n", i, Anchor_GetPosArgAt(context, i));
	}

	Anchor_Context_Destroy(context);
}

void PrintVersion(void)
{
	printf("v 0.1.0\n");
}

void PrintInt(int num)
{
	printf("%d\n", num);
}

void PrintString(const char *str)
{
	printf("%s", str);
}
