#pragma once

#include "Anchor/Config.h"

#include <stdbool.h>

typedef struct Anchor_Container Anchor_Container;

typedef enum Anchor_EntryKind
{
	Anchor_EntryKind_None = 0,
	Anchor_EntryKind_Flag,
	Anchor_EntryKind_Option
} Anchor_EntryKind;

ANCHOR_API Anchor_Container *Anchor_Container_Create(void);
ANCHOR_API void Anchor_Container_Destroy(Anchor_Container *container);

ANCHOR_API bool Anchor_Container_Add(Anchor_Container *container, const char *sFlag, const char *lFlag, const char *info, Anchor_EntryKind kind);
ANCHOR_API bool Anchor_Container_Has(Anchor_Container *container, const char *key);

ANCHOR_API Anchor_EntryKind Anchor_Container_GetKind(Anchor_Container *container, const char *key);

ANCHOR_API bool Anchor_Container_Set(Anchor_Container *container, const char *key, const char *value);
ANCHOR_API const char *Anchor_Container_Get(Anchor_Container *container, const char *key);
