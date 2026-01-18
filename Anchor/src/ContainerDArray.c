#include "Container.h"

#include <stdio.h>
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


typedef struct Anchor_Container
{
	Anchor_Entry *Data;

	size_t Size;
	size_t Capacity;
} Anchor_Container;

static int s_GrowIfNeeded(Anchor_Container *container);
static Anchor_Entry *s_FindItem(Anchor_Container *container, const char *key);

Anchor_Container *Anchor_Container_Create(void)
{
	Anchor_Container *container = (Anchor_Container *)malloc(sizeof(Anchor_Container));
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

void Anchor_Container_Destroy(Anchor_Container *container)
{
	if (!container)
		return;

	free(container->Data);
	free(container);
}

bool Anchor_Container_Add(Anchor_Container *container, const char *sFlag, const char *lFlag, const char *info, Anchor_EntryKind kind)
{
	size_t grownCapacity = s_GrowIfNeeded(container);
	if (grownCapacity == -1)
		return false;

	Anchor_Entry *newItem = container->Data + container->Size++;

	newItem->ShortFlag = sFlag;
	newItem->LongFlag = lFlag;
	newItem->Information = info;

	newItem->Kind = kind;
	newItem->RawValue = NULL;

	return true;
}

bool Anchor_Container_Has(Anchor_Container *container, const char *key)
{
	return s_FindItem(container, key);
}

Anchor_EntryKind Anchor_Container_GetKind(Anchor_Container *container, const char *key)
{
	Anchor_Entry *item = s_FindItem(container, key);
	if (!item)
		return Anchor_EntryKind_None;

	return item->Kind;
}

bool Anchor_Container_Set(Anchor_Container *container, const char *key, const char *value)
{
	Anchor_Entry *item = s_FindItem(container, key);
	if (!item)
		return false;

	item->RawValue = value;
	return true;
}

const char *Anchor_Container_Get(Anchor_Container *container, const char *key)
{
	Anchor_Entry *item = s_FindItem(container, key);
	if (!item)
		return NULL;

	return item->RawValue;
}

int s_GrowIfNeeded(Anchor_Container *container)
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

Anchor_Entry *s_FindItem(Anchor_Container *container, const char *key)
{
	for (int i = 0; i < container->Size; i++)
	{
		Anchor_Entry *item = container->Data + i;

		if ((item->ShortFlag) && (strcmp(key, item->ShortFlag) == 0) || (item->LongFlag) && (strcmp(key, item->LongFlag) == 0))
		{
			return item;
		}
	}

	return NULL;
}
