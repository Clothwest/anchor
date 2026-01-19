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
		free(context->EntryContainer);
		free(context->PosArgContainer);

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
			if (!Anchor_EntryContainer_Has(entryContainer, arg))
				continue;

			if (Anchor_EntryContainer_GetKind(entryContainer, arg) == Anchor_EntryKind_Switch)
			{
				Anchor_EntryContainer_Set(entryContainer, arg, NULL);
				continue;
			}

			if (i + 1 == argc)
				return -1;
			Anchor_EntryContainer_Set(entryContainer, arg, argv[++i]);
		}
		else if (!Anchor_PosArgContainer_Add(posArgContainer, arg))
		{
			return -1;
		}
	}

	return 0;
}

bool Anchor_IsSet(Anchor_Context *ctx, const char *flag)
{
	if (!s_IsValid(ctx))
		return false;

	return Anchor_EntryContainer_IsSet(ctx->EntryContainer, flag);
}

const char *Anchor_GetValue(Anchor_Context *ctx, const char *flag, const char *dft)
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

const char *Anchor_GetPosArgAt(Anchor_Context *ctx, size_t index)
{
	if (!s_IsValid(ctx))
		return NULL;

	if (index >= Anchor_PosArgContainer_GetCount(ctx->PosArgContainer))
		return NULL;

	return Anchor_PosArgContainer_GetAt(ctx->PosArgContainer, index);
}

bool s_IsValid(Anchor_Context *ctx)
{
	return ctx && ctx->EntryContainer && ctx->PosArgContainer;
}
