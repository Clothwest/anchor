#pragma once

#include "Anchor/Detail/Config.h"

#include <stdbool.h>
#include <stddef.h>

typedef struct Anchor_PosArgContainer Anchor_PosArgContainer;

typedef enum Anchor_PosArgContainer_Status
{
	Anchor_PosArgContainer_Status_Success = 0,
	Anchor_PosArgContainer_Status_Failure = 1,

	Anchor_PosArgContainer_Status_OutOfMemory
} Anchor_PosArgContainer_Status;

Anchor_PosArgContainer *Anchor_PosArgContainer_Create(void);
void Anchor_PosArgContainer_Destroy(Anchor_PosArgContainer *container);

bool Anchor_PosArgContainer_Add(Anchor_PosArgContainer *container, const char *arg);
const char *Anchor_PosArgContainer_GetAt(Anchor_PosArgContainer *container, size_t index);

size_t Anchor_PosArgContainer_GetCount(Anchor_PosArgContainer *container);

Anchor_PosArgContainer_Status Anchor_PosArgContainer_GetStatus(Anchor_PosArgContainer *container);
