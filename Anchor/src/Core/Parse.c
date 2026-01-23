#include "Anchor/Anchor.h"

#include "Context.h"

int Anchor_Parse(Anchor_Context *ctx, const char **argv, int argc)
{
	if (!Anchor_Context_IsValid(ctx))
		return -1;

	Anchor_EntryContainer *entryContainer = ctx->EntryContainer;
	Anchor_PosArgContainer *posArgContainer = ctx->PosArgContainer;
	for (int i = 1; i < argc; i++)
	{
		const char *arg = argv[i];

		if (arg[0] == '-')
		{
			const Anchor_EntryView *view = Anchor_EntryContainer_GetView(entryContainer, arg);
			if (!view)
				continue;

			if (view->Kind == Anchor_EntryKind_Switch)
			{
				Anchor_EntryContainer_SetValue(entryContainer, arg, NULL);
				continue;
			}

			if (i + 1 == argc)
				return -1;
			Anchor_EntryContainer_SetValue(entryContainer, arg, argv[++i]);
		}
		else if (!Anchor_PosArgContainer_Add(posArgContainer, arg))
		{
			return -1;
		}
	}

	return 0;
}
