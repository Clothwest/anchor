#include <Anchor/Anchor.h>

#include "Scanner.h"

int main(int argc, char **argv)
{
	Anchor_Context *context = Anchor_CreateContext();

	Anchor_NewSwitch(context, "-h", "--help", "Show help info");
	Anchor_NewSwitch(context, "-r", "--recursive", "Recursive");
	Anchor_NewSwitch(context, "-v", "--verbose", "Show Lines of each file");

	if (argc < 2)
	{
		Anchor_FPrintDefaultHelp(context, stdout);
		Anchor_DestroyContext(context);
		return 0;
	}
	
	if (Anchor_Parse(context, argv, argc) == -1)
	{
		printf("Error");
		Anchor_DestroyContext(context);
		return 0;
	}

	const char *path = Anchor_GetPosArgValueAt(context, 0);
	if (!path)
	{
		printf("Missing Path!");
		Anchor_DestroyContext(context);
		return 0;
	}

	Tloc_Scan(path, Anchor_IsSet(context, "-r"), Anchor_IsSet(context, "-v"));

	Anchor_DestroyContext(context);
}
