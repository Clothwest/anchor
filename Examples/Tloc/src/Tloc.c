#include <Anchor/Anchor.h>

#include "Scanner.h"

#include <stdio.h>

int main(int argc, char **argv)
{
	Anchor_Context *context = Anchor_CreateContext();

	Anchor_NewSwitch(context, "-h", "--help", "Show help info");
	Anchor_NewSwitch(context, "-r", "--recursive", "Recursive");
	Anchor_NewSwitch(context, "-v", "--verbose", "Show Lines of each file");

	if (argc < 2)
	{
		Anchor_PrintDefaultHelp(context);
		Anchor_DestroyContext(context);
		return 0;
	}
	
	if (Anchor_Parse(context, argv, argc) == -1)
	{
		printf("Error");
		Anchor_DestroyContext(context);
		return 0;
	}

	if (Anchor_IsSet(context, "-h"))
		Anchor_PrintDefaultHelp(context);

	size_t count = Anchor_GetPosArgCount(context);
	const char *path = NULL;
	if (count > 0)
	{
		path = Anchor_GetPosArgValueAt(context, 0);
		if (!path)
		{
			printf("Missing Path!");
			Anchor_DestroyContext(context);
			return 0;
		}
	}

	Tloc_Scan(path, Anchor_IsSet(context, "-r"), Anchor_IsSet(context, "-v"));

	Anchor_DestroyContext(context);
}
