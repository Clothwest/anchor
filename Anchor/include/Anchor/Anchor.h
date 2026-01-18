#pragma once

#include "Config.h"

#include <stdbool.h>

typedef struct Anchor_Context Anchor_Context;

ANCHOR_API Anchor_Context *Anchor_Context_Create(void);
ANCHOR_API void Anchor_Context_Destroy(Anchor_Context *ctx);

ANCHOR_API bool Anchor_NewFlag(Anchor_Context *ctx, const char *sFlag, const char *lFlag, const char *info);
ANCHOR_API bool Anchor_NewOption(Anchor_Context *ctx, const char *sFlag, const char *lFlag, const char *info);

ANCHOR_API int Anchor_Parse(Anchor_Context *ctx, const char **argv, int argc);

ANCHOR_API bool Anchor_GetBool(Anchor_Context *ctx, const char *key);
ANCHOR_API int Anchor_GetInt(Anchor_Context *ctx, const char *key, int dft);
ANCHOR_API const char *Anchor_GetStr(Anchor_Context *ctx, const char *key, const char *dft);
