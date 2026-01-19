#include "Anchor/Anchor.h"

#include <stdio.h>
#include <stdlib.h>

static void PrintVersion(void);
static void PrintHelp(Anchor_Context *context);
static void PrintInt(int num);
static void PrintString(const char *str);

int main(int argc, char **argv)
{
	Anchor_Context *context = Anchor_Context_Create();

	Anchor_NewSwitch(context, "-v", "--version", "Show version");
	Anchor_NewSwitch(context, "-h", "--help", "Show help info");
	Anchor_NewSwitch(context, NULL, "--show", "Show PosArg");

	Anchor_NewOption(context, "-i", "--int", "Print int");
	Anchor_NewOption(context, "-s", "--str", "Print String");

	Anchor_Parse(context, argv, argc);

	if (Anchor_IsSet(context, "-v"))
	{
		PrintVersion();
	}

	if (Anchor_IsSet(context, "-h"))
	{
		Anchor_FPrintDefaultHelp(context, stdout);
	}

	if (Anchor_IsSet(context, "-i"))
	{
		int outInt = atoi(Anchor_GetOptionValue(context, "-i", 0));
		PrintInt(outInt);
	}

	const char *outStr = Anchor_GetOptionValue(context, "-s", NULL);
	if (outStr)
		PrintString(outStr);

	size_t posArgCount = Anchor_GetPosArgCount(context);
	if (Anchor_IsSet(context, "--show"))
	{
		printf("Count: %zu\n", posArgCount);

		for (size_t i = 0; i < posArgCount; i++)
			printf("%zu: %s\n", i, Anchor_GetPosArgValueAt(context, i));
	}

	Anchor_Context_Destroy(context);
}

void PrintVersion(void)
{
	printf("v 0.1.0\n");
}

void PrintHelp(Anchor_Context *context)
{
	for (size_t i = 0; i < Anchor_GetEntryViewCount(context); i++)
	{
		const Anchor_EntryView *view = Anchor_GetEntryViewAt(context, i);

		printf("%s\t%s\t%s\n", view->ShortFlag, view->LongFlag, view->Information);
	}
}

void PrintInt(int num)
{
	printf("%d\n", num);
}

void PrintString(const char *str)
{
	printf("%s", str);
}
