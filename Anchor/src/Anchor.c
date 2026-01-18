#include "Anchor/Anchor.h"

#include "EntryContainer.h"

#include <stdlib.h>
#include <stdio.h>

typedef struct Anchor_Context
{
	Anchor_EntryContainer *EntryContainer;
} Anchor_Context;

static bool s_IsValid(Anchor_Context *ctx);

Anchor_Context *Anchor_Context_Create(void)
{
	Anchor_Context *context = (Anchor_Context *)malloc(sizeof(Anchor_Context));
	if (!context)
		return NULL;

	context->EntryContainer = Anchor_EntryContainer_Create();
	if (!context->EntryContainer)
	{
		free(context);
		return NULL;
	}

	return context;
}

void Anchor_Context_Destroy(Anchor_Context *ctx)
{
	if (!ctx)
		return;

	Anchor_EntryContainer_Destroy(ctx->EntryContainer);
	free(ctx);
}

bool Anchor_NewFlag(Anchor_Context *ctx, const char *sFlag, const char *lFlag, const char *info)
{
	if (!s_IsValid(ctx))
		return false;

	return Anchor_EntryContainer_Add(ctx->EntryContainer, sFlag, lFlag, info, Anchor_EntryKind_Flag);
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

	Anchor_EntryContainer *container = ctx->EntryContainer;
	for (int i = 1; i < argc; i++)
	{
		const char *arg = argv[i];

		if (arg[0] != '-')
			continue;

		if (!Anchor_EntryContainer_Has(container, arg))
			continue;

		if (Anchor_EntryContainer_GetKind(container, arg) == Anchor_EntryKind_Flag)
		{
			Anchor_EntryContainer_Set(container, arg, "true");
			continue;
		}

		if (i + 1 == argc)
			return -1;
		Anchor_EntryContainer_Set(container, arg, argv[++i]);
	}

	return 0;
}

bool Anchor_IsSet(Anchor_Context *ctx, const char *flag)
{
	if (!s_IsValid(ctx))
		return false;

	return Anchor_EntryContainer_Get(ctx->EntryContainer, flag);
}

int Anchor_GetInt(Anchor_Context *ctx, const char *flag, int dft)
{
	if (!s_IsValid(ctx))
		return dft;

	const char *rawValue = Anchor_EntryContainer_Get(ctx->EntryContainer, flag);
	if (!rawValue)
		return dft;

	return atoi(rawValue);
}

const char *Anchor_GetStr(Anchor_Context *ctx, const char *flag, const char *dft)
{
	if (!s_IsValid(ctx))
		return dft;

	const char *rawValue = Anchor_EntryContainer_Get(ctx->EntryContainer, flag);
	if (!rawValue)
		return dft;

	return rawValue;
}

bool s_IsValid(Anchor_Context *ctx)
{
	return ctx && ctx->EntryContainer;
}
