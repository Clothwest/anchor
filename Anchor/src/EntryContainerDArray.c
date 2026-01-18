#include "EntryContainer.h"

#include <stdlib.h>
#include <string.h>

#define INIT_CAP 8

typedef struct Anchor_Entry
{
	const char *ShortFlag;
	const char *LongFlag;
	const char *Information;

	Anchor_EntryKind Kind;
	const char *RawValue;
} Anchor_Entry;

typedef struct Anchor_EntryContainer
{
	Anchor_Entry *Data;

	size_t Size;
	size_t Capacity;
} Anchor_EntryContainer;

static int s_GrowIfNeeded(Anchor_EntryContainer *container);
static Anchor_Entry *s_FindEntry(Anchor_EntryContainer *container, const char *key);

Anchor_EntryContainer *Anchor_EntryContainer_Create(void)
{
	Anchor_EntryContainer *container = (Anchor_EntryContainer *)malloc(sizeof(Anchor_EntryContainer));
	if (!container)
		return NULL;

	container->Data = (Anchor_Entry *)malloc(INIT_CAP * sizeof(Anchor_Entry));
	if (!container->Data)
	{
		free(container);
		return NULL;
	}

	container->Size = 0;
	container->Capacity = INIT_CAP;

	return container;
}

void Anchor_EntryContainer_Destroy(Anchor_EntryContainer *container)
{
	free(container->Data);
	free(container);
}

bool Anchor_EntryContainer_Add(Anchor_EntryContainer *container, const char *sFlag, const char *lFlag, const char *info, Anchor_EntryKind kind)
{
	size_t grownCapacity = s_GrowIfNeeded(container);
	if (grownCapacity == -1)
		return false;

	Anchor_Entry *newEntry = container->Data + container->Size++;

	newEntry->ShortFlag = sFlag;
	newEntry->LongFlag = lFlag;
	newEntry->Information = info;

	newEntry->Kind = kind;
	newEntry->RawValue = NULL;

	return true;
}

bool Anchor_EntryContainer_Has(Anchor_EntryContainer *container, const char *key)
{
	return s_FindEntry(container, key);
}

Anchor_EntryKind Anchor_EntryContainer_GetKind(Anchor_EntryContainer *container, const char *key)
{
	Anchor_Entry *entry = s_FindEntry(container, key);
	if (!entry)
		return Anchor_EntryKind_None;

	return entry->Kind;
}

bool Anchor_EntryContainer_Set(Anchor_EntryContainer *container, const char *key, const char *value)
{
	Anchor_Entry *entry = s_FindEntry(container, key);
	if (!entry)
		return false;

	entry->RawValue = value;
	return true;
}

const char *Anchor_EntryContainer_Get(Anchor_EntryContainer *container, const char *key)
{
	Anchor_Entry *entry = s_FindEntry(container, key);
	if (!entry)
		return NULL;

	return entry->RawValue;
}

int s_GrowIfNeeded(Anchor_EntryContainer *container)
{
	size_t oldCapacity = container->Capacity;

	if (container->Size < container->Capacity)
		return 0;

	size_t newCapacity = 2 * container->Capacity;
	Anchor_Entry *newData = (Anchor_Entry *)realloc(container->Data, newCapacity * sizeof(Anchor_Entry));
	if (!newData)
		return -1;

	container->Data = newData;
	return (int)(newCapacity - oldCapacity);
}

Anchor_Entry *s_FindEntry(Anchor_EntryContainer *container, const char *key)
{
	for (int i = 0; i < container->Size; i++)
	{
		Anchor_Entry *entry = container->Data + i;

		if ((entry->ShortFlag) && (strcmp(key, entry->ShortFlag) == 0) || (entry->LongFlag) && (strcmp(key, entry->LongFlag) == 0))
		{
			return entry;
		}
	}

	return NULL;
}
