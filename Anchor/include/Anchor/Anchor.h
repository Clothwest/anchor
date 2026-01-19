#pragma once

#include "Config.h"

#include "Types.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

typedef struct Anchor_Context Anchor_Context;

ANCHOR_API Anchor_Context *Anchor_Context_Create(void);
ANCHOR_API void Anchor_Context_Destroy(Anchor_Context *ctx);

ANCHOR_API bool Anchor_NewSwitch(Anchor_Context *ctx, const char *sFlag, const char *lFlag, const char *info);
ANCHOR_API bool Anchor_NewOption(Anchor_Context *ctx, const char *sFlag, const char *lFlag, const char *info);

ANCHOR_API int Anchor_Parse(Anchor_Context *ctx, const char **argv, int argc);

ANCHOR_API size_t Anchor_GetEntryViewCount(Anchor_Context *ctx);
ANCHOR_API const Anchor_EntryView *Anchor_GetEntryViewAt(Anchor_Context *ctx, size_t index);
ANCHOR_API const Anchor_EntryView *Anchor_GetEntryView(Anchor_Context *ctx, const char *flag);

ANCHOR_API bool Anchor_IsSet(Anchor_Context *ctx, const char *flag);
ANCHOR_API const char *Anchor_GetOptionValue(Anchor_Context *ctx, const char *flag, const char *dft);

ANCHOR_API size_t Anchor_GetPosArgCount(Anchor_Context *ctx);
ANCHOR_API const char *Anchor_GetPosArgValueAt(Anchor_Context *ctx, size_t index);

ANCHOR_API void Anchor_FPrintDefaultHelp(Anchor_Context *ctx, FILE *stream);
