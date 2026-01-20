#include <Anchor/Anchor.h>

int main(int argc, char **argv)
{
	Anchor_Context *context = Anchor_Context_Create();

	Anchor_NewSwitch(context, "-h", "--help", "Show help");
	Anchor_NewSwitch(context, "-v", "--version", "Show version info");

	Anchor_Parse(context, argv, argc);

	if (Anchor_IsSet(context, "-h"))
	{
		Anchor_FPrintDefaultHelp(context, stdout);
	}

	if (Anchor_IsSet(context, "-v"))
	{
		printf("v0.1.0\n");
	}

	Anchor_Context_Destroy(context);
}
