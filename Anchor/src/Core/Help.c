#include "Anchor/Anchor.h"

#include "Context.h"

#include <stdio.h>

void Anchor_PrintDefaultHelp(Anchor_Context *ctx)
{
	if (!Anchor_Context_IsValid(ctx))
		return;

	size_t count = Anchor_EntryContainer_GetViewCount(ctx->EntryContainer);
	for (size_t i = 0; i < count; i++)
	{
		const Anchor_EntryView *view = Anchor_EntryContainer_GetViewAt(ctx->EntryContainer, i);
		if (!view)
			return;

		printf("  ");

		const char *shortFlag = view->ShortFlag;
		const char *longFlag = view->LongFlag;

		printf("%-4s", shortFlag ? shortFlag : "");
		printf("%-4s", (shortFlag && longFlag) ? ", " : "");
		printf("%-16s", longFlag ? longFlag : "");

		printf("%-16s", (view->Kind == Anchor_EntryKind_Option) ? "<value>" : "");

		const char *information = view->Information;
		printf("%s", information ? information : "");

		printf("\n");
	}
}
