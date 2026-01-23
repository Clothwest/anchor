#pragma once

#include "Container/EntryContainer.h"
#include "Container/PosArgContainer.h"

typedef struct Anchor_Context
{
	Anchor_EntryContainer *EntryContainer;
	Anchor_PosArgContainer *PosArgContainer;
} Anchor_Context;

bool Anchor_Context_IsValid(Anchor_Context *ctx);
