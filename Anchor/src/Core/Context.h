#pragma once

#include "Container/EntryContainer.h"
#include "Container/PosArgContainer.h"

#include "Anchor/Detail/Types.h"

typedef struct Anchor_Context
{
	Anchor_EntryContainer *EntryContainer;
	Anchor_PosArgContainer *PosArgContainer;

	Anchor_Error Error;
	Anchor_ErrorCallback ErrorCallback;
} Anchor_Context;

bool Anchor_Context_IsValid(Anchor_Context *ctx);

void Anchor_Context_ResetError(Anchor_Context *ctx);
Anchor_Status Anchor_Context_SetError(Anchor_Context *ctx, Anchor_Status status, int argIndex, const char *token);
