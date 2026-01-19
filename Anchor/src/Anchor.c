#include "Anchor/Anchor.h"

#include "EntryContainer.h"
#include "PosArgContainer.h"

#include <stdlib.h>

typedef struct Anchor_Context
{
	Anchor_EntryContainer *EntryContainer;
	Anchor_PosArgContainer *PosArgContainer;
} Anchor_Context;

static bool s_IsValid(Anchor_Context *ctx);

Anchor_Context *Anchor_Context_Create(void)
{
	Anchor_Context *context = (Anchor_Context *)malloc(sizeof(Anchor_Context));
	if (!context)
		return NULL;

	context->EntryContainer = Anchor_EntryContainer_Create();
	context->PosArgContainer = Anchor_PosArgContainer_Create();
	if (!context->EntryContainer || !context->PosArgContainer)
	{
		if (context->EntryContainer)
			Anchor_EntryContainer_Destroy(context->EntryContainer);
		if (context->PosArgContainer)
			Anchor_PosArgContainer_Destroy(context->PosArgContainer);

		free(context);

		return NULL;
	}

	return context;
}

void Anchor_Context_Destroy(Anchor_Context *ctx)
{
	if (!ctx)
		return;

	if (ctx->EntryContainer)
		Anchor_EntryContainer_Destroy(ctx->EntryContainer);
	if (ctx->PosArgContainer)
		Anchor_PosArgContainer_Destroy(ctx->PosArgContainer);

	free(ctx);
}

bool Anchor_NewSwitch(Anchor_Context *ctx, const char *sFlag, const char *lFlag, const char *info)
{
	if (!s_IsValid(ctx))
		return false;

	return Anchor_EntryContainer_Add(ctx->EntryContainer, sFlag, lFlag, info, Anchor_EntryKind_Switch);
}

bool Anchor_NewOption(Anchor_Context *ctx, const char *sFlag, const char *lFlag, const char *info)
{
	if (!s_IsValid(ctx))
		return false;

	return Anchor_EntryContainer_Add(ctx->EntryContainer, sFlag, lFlag, info, Anchor_EntryKind_Option);
}

int Anchor_Parse(Anchor_Context *ctx, const char **argv, int argc)
{
	if (!s_IsValid(ctx))
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

size_t Anchor_GetEntryViewCount(Anchor_Context *ctx)
{
	if (!s_IsValid(ctx))
		return 0;

	return Anchor_EntryContainer_GetViewCount(ctx->EntryContainer);
}

const Anchor_EntryView *Anchor_GetEntryViewAt(Anchor_Context *ctx, size_t index)
{
	if (!s_IsValid(ctx))
		return NULL;

	if (index >= Anchor_EntryContainer_GetViewCount(ctx->EntryContainer))
		return NULL;

	return Anchor_EntryContainer_GetViewAt(ctx->EntryContainer, index);
}

const Anchor_EntryView *Anchor_GetEntryView(Anchor_Context *ctx, const char *flag)
{
	if (!s_IsValid(ctx))
		return NULL;

	return Anchor_EntryContainer_GetView(ctx->EntryContainer, flag);
}

bool Anchor_IsSet(Anchor_Context *ctx, const char *flag)
{
	if (!s_IsValid(ctx))
		return false;

	return Anchor_EntryContainer_IsSet(ctx->EntryContainer, flag);
}

const char *Anchor_GetOptionValue(Anchor_Context *ctx, const char *flag, const char *dft)
{
	if (!s_IsValid(ctx))
		return dft;

	const char *rawValue = Anchor_EntryContainer_GetValue(ctx->EntryContainer, flag);
	if (!rawValue)
		return dft;

	return rawValue;
}

size_t Anchor_GetPosArgCount(Anchor_Context *ctx)
{
	if (!s_IsValid(ctx))
		return 0;

	return Anchor_PosArgContainer_GetCount(ctx->PosArgContainer);
}

const char *Anchor_GetPosArgValueAt(Anchor_Context *ctx, size_t index)
{
	if (!s_IsValid(ctx))
		return NULL;

	if (index >= Anchor_PosArgContainer_GetCount(ctx->PosArgContainer))
		return NULL;

	return Anchor_PosArgContainer_GetAt(ctx->PosArgContainer, index);
}

void Anchor_FPrintDefaultHelp(Anchor_Context *ctx, FILE *stream)
{
	if (!s_IsValid(ctx) || !stream)
		return;

	size_t count = Anchor_EntryContainer_GetViewCount(ctx->EntryContainer);
	for (size_t i = 0; i < count; i++)
	{
		const Anchor_EntryView *view = Anchor_EntryContainer_GetViewAt(ctx->EntryContainer, i);
		if (!view)
			return;

		fprintf(stream, "  ");

		const char *shortFlag = view->ShortFlag;
		const char *longFlag = view->LongFlag;

		fprintf(stream, "%-4s", shortFlag ? shortFlag : "");
		fprintf(stream, "%-4s", (shortFlag && longFlag) ? ", " : "");
		fprintf(stream, "%-16s", longFlag ? longFlag : "");

		fprintf(stream, "%-16s", (view->Kind == Anchor_EntryKind_Option) ? "<value>" : "");

		const char *information = view->Information;
		fprintf(stream, "%s", information ? information : "");

		fprintf(stream, "\n");
	}
}

bool s_IsValid(Anchor_Context *ctx)
{
	return ctx && ctx->EntryContainer && ctx->PosArgContainer;
}
