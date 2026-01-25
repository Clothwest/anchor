#pragma once

#include "Anchor/Detail/Config.h"

#include "Anchor/Detail/Types.h"

#include <stdbool.h>
#include <stddef.h>

typedef struct Anchor_EntryContainer Anchor_EntryContainer;

typedef enum Anchor_EntryContainer_Status
{
	Anchor_EntryContainer_Status_Success = 0,
	Anchor_EntryContainer_Status_Failure = 1,

	Anchor_EntryContainer_Status_OutOfMemory,

	Anchor_EntryContainer_Status_DuplicateFlag,

	Anchor_EntryContainer_Status_UnknownFlag
} Anchor_EntryContainer_Status;

Anchor_EntryContainer *Anchor_EntryContainer_Create(void);
void Anchor_EntryContainer_Destroy(Anchor_EntryContainer *container);

bool Anchor_EntryContainer_Add(Anchor_EntryContainer *container, const char *sFlag, const char *lFlag, const char *info, Anchor_EntryKind kind);
bool Anchor_EntryContainer_Has(Anchor_EntryContainer *container, const char *flag);

size_t Anchor_EntryContainer_GetViewCount(Anchor_EntryContainer *container);
const Anchor_EntryView *Anchor_EntryContainer_GetViewAt(Anchor_EntryContainer *container, size_t index);
const Anchor_EntryView *Anchor_EntryContainer_GetView(Anchor_EntryContainer *container, const char *flag);

bool Anchor_EntryContainer_IsSet(Anchor_EntryContainer *container, const char *flag);
bool Anchor_EntryContainer_SetValue(Anchor_EntryContainer *container, const char *flag, const char *value);
const char *Anchor_EntryContainer_GetValue(Anchor_EntryContainer *container, const char *flag);

Anchor_EntryContainer_Status Anchor_EntryContainer_GetStatus(Anchor_EntryContainer *container);
