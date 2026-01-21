#pragma once

#include "Anchor/Detail/Config.h"

#include "Anchor/Detail/Types.h"

#include <stdbool.h>
#include <stddef.h>

typedef struct Anchor_EntryContainer Anchor_EntryContainer;

ANCHOR_API Anchor_EntryContainer *Anchor_EntryContainer_Create(void);
ANCHOR_API void Anchor_EntryContainer_Destroy(Anchor_EntryContainer *container);

ANCHOR_API bool Anchor_EntryContainer_Add(Anchor_EntryContainer *container, const char *sFlag, const char *lFlag, const char *info, Anchor_EntryKind kind);
ANCHOR_API bool Anchor_EntryContainer_Has(Anchor_EntryContainer *container, const char *flag);

ANCHOR_API size_t Anchor_EntryContainer_GetViewCount(Anchor_EntryContainer *container);
ANCHOR_API const Anchor_EntryView *Anchor_EntryContainer_GetViewAt(Anchor_EntryContainer *container, size_t index);
ANCHOR_API const Anchor_EntryView *Anchor_EntryContainer_GetView(Anchor_EntryContainer *container, const char *flag);

ANCHOR_API bool Anchor_EntryContainer_IsSet(Anchor_EntryContainer *container, const char *flag);
ANCHOR_API bool Anchor_EntryContainer_SetValue(Anchor_EntryContainer *container, const char *flag, const char *value);
ANCHOR_API const char *Anchor_EntryContainer_GetValue(Anchor_EntryContainer *container, const char *flag);
