#pragma once

#include "Anchor/Config.h"

#include <stdbool.h>
#include <stddef.h>

typedef struct Anchor_PosArgContainer Anchor_PosArgContainer;

ANCHOR_API Anchor_PosArgContainer *Anchor_PosArgContainer_Create(void);
ANCHOR_API void Anchor_PosArgContainer_Destroy(Anchor_PosArgContainer *container);

ANCHOR_API bool Anchor_PosArgContainer_Add(Anchor_PosArgContainer *container, const char *arg);
ANCHOR_API const char *Anchor_PosArgContainer_GetAt(Anchor_PosArgContainer *container, size_t index);

ANCHOR_API size_t Anchor_PosArgContainer_GetCount(Anchor_PosArgContainer *container);
