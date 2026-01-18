#pragma once

#include "Anchor/Config.h"

#include <stdbool.h>

typedef struct Anchor_Container Anchor_Container;

ANCHOR_API Anchor_Container *Anchor_Container_Create(void);
ANCHOR_API void Anchor_Container_Destroy(Anchor_Container *container);

ANCHOR_API bool Anchor_Container_Add(Anchor_Container *container, const char *sFlag, const char *lFlag, const char *info, bool isBool);
ANCHOR_API bool Anchor_Container_Has(Anchor_Container *container, const char *key);

ANCHOR_API bool Anchor_Container_IsBool(Anchor_Container *container, const char *key);

ANCHOR_API bool Anchor_Container_Set(Anchor_Container *container, const char *key, const char *value);
ANCHOR_API const char *Anchor_Container_Get(Anchor_Container *container, const char *key);
