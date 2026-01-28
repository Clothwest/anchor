#include <Anchor/Anchor.h>

#include <stdio.h>

static void s_ErrorCallback(Anchor_Context *ctx);

int main(int argc, char **argv)
{
	Anchor_Context *app = Anchor_CreateContext();
	if (!app)
		return 0;

	Anchor_SetErrorCallback(app, &s_ErrorCallback);

	Anchor_NewSwitch(app, "-h", "--help", "Show help info");
	Anchor_NewSwitch(app, "-v", "--version", "Show version info");
	Anchor_NewOption(app, "-o", "--output", "Set output file name");

	int errorCount = Anchor_Parse(app, argv, argc);

	Anchor_DestroyContext(app);
}

void s_ErrorCallback(Anchor_Context *ctx)
{
	char buffer[64];
	Anchor_GetErrorMsg(ctx, buffer, 64);
	printf(buffer);
	printf("\n");
}
