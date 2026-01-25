#include "Context.h"
#include "Anchor/Anchor.h"

#include "Log/Log.h"

#include <stdlib.h>

static bool s_FlagIsValid(const char *sFlag, const char *lFlag);

static bool s_ENewEntry(Anchor_Context *ctx, const char *sFlag, const char *lFlag, const char *info, Anchor_EntryKind kind);

Anchor_Context *Anchor_CreateContext(void)
{
	ANCHOR_INIT_LOG();
	ANCHOR_INFO("Log initialized");

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

	Anchor_Context_ResetError(context);
	context->ErrorCallback = NULL;

	return context;
}

void Anchor_DestroyContext(Anchor_Context *ctx)
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
	if (!Anchor_Context_IsValid(ctx))
		return false;

	Anchor_Context_ResetError(ctx);

	return s_ENewEntry(ctx, sFlag, lFlag, info, Anchor_EntryKind_Switch);
}

bool Anchor_NewOption(Anchor_Context *ctx, const char *sFlag, const char *lFlag, const char *info)
{
	if (!Anchor_Context_IsValid(ctx))
		return false;

	Anchor_Context_ResetError(ctx);

	return s_ENewEntry(ctx, sFlag, lFlag, info, Anchor_EntryKind_Option);
}

size_t Anchor_GetEntryViewCount(Anchor_Context *ctx)
{
	if (!Anchor_Context_IsValid(ctx))
		return 0;

	return Anchor_EntryContainer_GetViewCount(ctx->EntryContainer);
}

const Anchor_EntryView *Anchor_GetEntryViewAt(Anchor_Context *ctx, size_t index)
{
	if (!Anchor_Context_IsValid(ctx))
		return NULL;

	if (index >= Anchor_EntryContainer_GetViewCount(ctx->EntryContainer))
		return NULL;

	return Anchor_EntryContainer_GetViewAt(ctx->EntryContainer, index);
}

const Anchor_EntryView *Anchor_GetEntryView(Anchor_Context *ctx, const char *flag)
{
	if (!Anchor_Context_IsValid(ctx))
		return NULL;

	return Anchor_EntryContainer_GetView(ctx->EntryContainer, flag);
}

bool Anchor_IsSet(Anchor_Context *ctx, const char *flag)
{
	if (!Anchor_Context_IsValid(ctx))
		return false;

	return Anchor_EntryContainer_IsSet(ctx->EntryContainer, flag);
}

const char *Anchor_GetOptionValue(Anchor_Context *ctx, const char *flag, const char *dft)
{
	if (!Anchor_Context_IsValid(ctx))
		return dft;

	const char *rawValue = Anchor_EntryContainer_GetValue(ctx->EntryContainer, flag);
	if (!rawValue)
		return dft;

	return rawValue;
}

size_t Anchor_GetPosArgCount(Anchor_Context *ctx)
{
	if (!Anchor_Context_IsValid(ctx))
		return 0;

	return Anchor_PosArgContainer_GetCount(ctx->PosArgContainer);
}

const char *Anchor_GetPosArgValueAt(Anchor_Context *ctx, size_t index)
{
	if (!Anchor_Context_IsValid(ctx))
		return NULL;

	if (index >= Anchor_PosArgContainer_GetCount(ctx->PosArgContainer))
		return NULL;

	return Anchor_PosArgContainer_GetAt(ctx->PosArgContainer, index);
}

bool Anchor_Context_IsValid(Anchor_Context *ctx)
{
	return ctx && ctx->EntryContainer && ctx->PosArgContainer;
}

void Anchor_Context_ResetError(Anchor_Context *ctx)
{
	ctx->Error.Status = Anchor_Status_Success;
	ctx->Error.ArgIndex = NON_INDEX;
	ctx->Error.Token = NULL;
}

Anchor_Status Anchor_Context_SetError(Anchor_Context *ctx, Anchor_Status status, int argIndex, const char *token)
{
	ctx->Error.Status = status;
	ctx->Error.ArgIndex = argIndex;
	ctx->Error.Token = token;

	if (ctx->ErrorCallback)
	{
		ctx->ErrorCallback(ctx);
	}

	return status;
}

bool s_FlagIsValid(const char *sFlag, const char *lFlag)
{
	return sFlag || lFlag;
}

bool s_ENewEntry(Anchor_Context *ctx, const char *sFlag, const char *lFlag, const char *info, Anchor_EntryKind kind)
{
	if (!s_FlagIsValid(sFlag, lFlag))
	{
		Anchor_Context_SetError(ctx, Anchor_Status_InvalidFlag, NON_INDEX, NULL);
		return false;
	}

	bool success = Anchor_EntryContainer_Add(ctx->EntryContainer, sFlag, lFlag, info, kind);
	switch (Anchor_EntryContainer_GetStatus(ctx->EntryContainer))
	{
		case Anchor_EntryContainer_Status_DuplicateFlag:
			Anchor_Context_SetError(ctx, Anchor_Status_DuplicateFlag, NON_INDEX, NULL);
			break;
		case Anchor_EntryContainer_Status_OutOfMemory:
			Anchor_Context_SetError(ctx, Anchor_Status_OutOfMemory, NON_INDEX, NULL);
			break;
	}

	return success;
}
