#pragma once

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
