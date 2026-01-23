#pragma once

#include "Detail/Config.h"

#include "Detail/Types.h"

#ifndef __cplusplus
#include <stdbool.h>
#endif
#include <stddef.h>

ANCHOR_API Anchor_Context *Anchor_CreateContext(void);
ANCHOR_API void Anchor_DestroyContext(Anchor_Context *ctx);

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

ANCHOR_API void Anchor_PrintDefaultHelp(Anchor_Context *ctx);
