#include "Anchor/Anchor.h"

#include <stdio.h>

static void PrintVersion(void);
static void PrintInt(int num);
static void PrintString(const char *str);

int main(int argc, char **argv)
{
	Anchor_Context *context = Anchor_Context_Create();

	Anchor_NewFlag(context, "-v", "--version", "Show version");
	Anchor_NewOption(context, "-i", "--int", "Print int");
	Anchor_NewOption(context, "-s", "--str", "Print String");

	Anchor_Parse(context, argv, argc);

	if (Anchor_IsSet(context, "-v"))
		PrintVersion();

	if (Anchor_IsSet(context, "-i"))
	{
		int outInt = Anchor_GetInt(context, "-i", 0);
		PrintInt(outInt);
	}

	const char *outStr = Anchor_GetStr(context, "-s", NULL);
	if (outStr)
		PrintString(outStr);

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
