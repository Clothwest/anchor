#include "Anchor/Anchor.h"

#include "Context.h"

static bool s_IsFlag(const char *arg);
static bool s_IsShortFlag(const char *arg);
static bool s_IsLongFlag(const char *arg);

int Anchor_Parse(Anchor_Context *ctx, const char **argv, int argc)
{
	if (!Anchor_Context_IsValid(ctx))
		return -1;

	Anchor_Context_ResetError(ctx);
	int errorCount = 0;

	Anchor_EntryContainer *entryContainer = ctx->EntryContainer;
	Anchor_PosArgContainer *posArgContainer = ctx->PosArgContainer;
	for (int i = 1; i < argc; i++)
	{
		const char *arg = argv[i];

		if (s_IsFlag(arg))
		{
			const Anchor_EntryView *view = Anchor_EntryContainer_GetView(entryContainer, arg);
			if (!view)
			{
				Anchor_Context_SetError(ctx, Anchor_Status_UnknownFlag, i, arg);
				errorCount++;
				continue;
			}

			if (view->Kind == Anchor_EntryKind_Switch)
			{
				Anchor_EntryContainer_SetValue(entryContainer, arg, NULL);
				continue;
			}

			if (i + 1 == argc || s_IsFlag(*(argv + i + 1)))
			{
				Anchor_Context_SetError(ctx, Anchor_Status_MissingValue, i, arg);
				errorCount++;
				continue;
			}
			Anchor_EntryContainer_SetValue(entryContainer, arg, argv[++i]);
		}
		else if (!Anchor_PosArgContainer_Add(posArgContainer, arg))
		{
			if (Anchor_PosArgContainer_GetStatus(posArgContainer) == Anchor_PosArgContainer_Status_OutOfMemory)
				Anchor_Context_SetError(ctx, Anchor_Status_OutOfMemory, i, arg);
			errorCount++;
			continue;
		}
	}

	return errorCount;
}

bool s_IsFlag(const char *arg)
{
	return arg[0] == '-';
}

bool s_IsShortFlag(const char *arg)
{
	return arg[0] == '-' && arg[1] != '-';
}

bool s_IsLongFlag(const char *arg)
{
	return arg[0] == '-' && arg[1] == '-';
}
