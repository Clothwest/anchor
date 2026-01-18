#pragma once

#include "Anchor/Config.h"

#include <stdbool.h>

typedef struct Anchor_EntryContainer Anchor_EntryContainer;

typedef enum Anchor_EntryKind
{
	Anchor_EntryKind_None = 0,
	Anchor_EntryKind_Flag,
	Anchor_EntryKind_Option
} Anchor_EntryKind;

ANCHOR_API Anchor_EntryContainer *Anchor_EntryContainer_Create(void);
ANCHOR_API void Anchor_EntryContainer_Destroy(Anchor_EntryContainer *container);

ANCHOR_API bool Anchor_EntryContainer_Add(Anchor_EntryContainer *container, const char *sFlag, const char *lFlag, const char *info, Anchor_EntryKind kind);
ANCHOR_API bool Anchor_EntryContainer_Has(Anchor_EntryContainer *container, const char *key);

ANCHOR_API Anchor_EntryKind Anchor_EntryContainer_GetKind(Anchor_EntryContainer *container, const char *key);

ANCHOR_API bool Anchor_EntryContainer_Set(Anchor_EntryContainer *container, const char *key, const char *value);
ANCHOR_API const char *Anchor_EntryContainer_Get(Anchor_EntryContainer *container, const char *key);
