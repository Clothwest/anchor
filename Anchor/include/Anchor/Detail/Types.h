#pragma once

#ifndef __cplusplus
#include <stdbool.h>
#endif
#include <stddef.h>

#define NON_INDEX -1

typedef struct Anchor_Context Anchor_Context;

typedef enum Anchor_EntryKind
{
	Anchor_EntryKind_None = 0,
	Anchor_EntryKind_Switch,
	Anchor_EntryKind_Option
} Anchor_EntryKind;

typedef struct Anchor_EntryView
{
	const char *ShortFlag;
	const char *LongFlag;
	const char *Information;

	Anchor_EntryKind Kind;
} Anchor_EntryView;

typedef enum Anchor_Status
{
	Anchor_Status_Success = 0,
	Anchor_Status_Failure = 1,

	Anchor_Status_OutOfMemory,

	Anchor_Status_InvalidFlag,
	Anchor_Status_DuplicateFlag,

	Anchor_Status_UnknownFlag,
	Anchor_Status_MissingValue
} Anchor_Status;

typedef struct Anchor_Error
{
	Anchor_Status Status;
	int ArgIndex;
	const char *Token;
} Anchor_Error;

typedef void (*Anchor_ErrorCallback)(Anchor_Context *ctx);
