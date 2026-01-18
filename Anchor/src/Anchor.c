#include "Anchor/Anchor.h"

#include "Container.h"

#include <stdlib.h>
#include <stdio.h>

typedef struct Anchor_Context
{
	Anchor_Container *Container;
} Anchor_Context;

static bool s_IsValid(Anchor_Context *ctx);

Anchor_Context *Anchor_Context_Create(void)
{
	Anchor_Context *context = (Anchor_Context *)malloc(sizeof(Anchor_Context));
	if (!context)
		return NULL;

	context->Container = Anchor_Container_Create();
	if (!context->Container)
	{
		free(context);
		return NULL;
	}

	return context;
}

void Anchor_Context_Destroy(Anchor_Context *ctx)
{
	Anchor_Container_Destroy(ctx->Container);
	free(ctx);
}

bool Anchor_NewFlag(Anchor_Context *ctx, const char *sFlag, const char *lFlag, const char *info)
{
	if (!s_IsValid(ctx))
		return false;

	return Anchor_Container_Add(ctx->Container, sFlag, lFlag, info, true);
}

bool Anchor_NewOption(Anchor_Context *ctx, const char *sFlag, const char *lFlag, const char *info)
{
	if (!s_IsValid(ctx))
		return false;

	return Anchor_Container_Add(ctx->Container, sFlag, lFlag, info, false);
}

int Anchor_Parse(Anchor_Context *ctx, const char **argv, int argc)
{
	if (!s_IsValid(ctx))
		return -1;

	Anchor_Container *container = ctx->Container;
	for (int i = 1; i < argc; i++)
	{
		const char *arg = argv[i];

		if (arg[0] != '-')
			continue;

		if (!Anchor_Container_Has(container, arg))
			continue;

		if (Anchor_Container_IsBool(container, arg))
		{
			Anchor_Container_Set(container, arg, "true");
			continue;
		}

		if (i + 1 == argc)
			return -1;
		Anchor_Container_Set(container, arg, argv[++i]);
	}

	return 0;
}

bool Anchor_GetBool(Anchor_Context *ctx, const char *key)
{
	if (!s_IsValid(ctx))
		return false;

	return Anchor_Container_Get(ctx->Container, key);
}

int Anchor_GetInt(Anchor_Context *ctx, const char *key, int dft)
{
	if (!s_IsValid(ctx))
		return dft;

	const char *rawValue = Anchor_Container_Get(ctx->Container, key);
	if (!rawValue)
		return dft;

	return atoi(rawValue);
}

const char *Anchor_GetStr(Anchor_Context *ctx, const char *key, const char *dft)
{
	if (!s_IsValid(ctx))
		return dft;

	const char *rawValue = Anchor_Container_Get(ctx->Container, key);
	if (!rawValue)
		return dft;

	return rawValue;
}

bool s_IsValid(Anchor_Context *ctx)
{
	return ctx && ctx->Container;
}
