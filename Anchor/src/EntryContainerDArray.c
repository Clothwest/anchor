#include "EntryContainer.h"

#include <stdlib.h>
#include <string.h>

#define INIT_CAP 16

typedef struct Anchor_Entry
{
	Anchor_EntryView View;

	bool IsSet;
	const char *RawValue;
} Anchor_Entry;

typedef struct Anchor_EntryContainer
{
	Anchor_Entry *Data;

	size_t Size;
	size_t Capacity;
} Anchor_EntryContainer;

static int s_GrowIfNeeded(Anchor_EntryContainer *container);
static Anchor_Entry *s_FindEntry(Anchor_EntryContainer *container, const char *flag);

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

	newEntry->View.ShortFlag = sFlag;
	newEntry->View.LongFlag = lFlag;
	newEntry->View.Information = info;

	newEntry->View.Kind = kind;

	newEntry->IsSet = false;
	newEntry->RawValue = NULL;

	return true;
}

bool Anchor_EntryContainer_Has(Anchor_EntryContainer *container, const char *flag)
{
	return s_FindEntry(container, flag);
}

size_t Anchor_EntryContainer_GetViewCount(Anchor_EntryContainer *container)
{
	return container->Size;
}

const Anchor_EntryView *Anchor_EntryContainer_GetViewAt(Anchor_EntryContainer *container, size_t index)
{
	return &(container->Data + index)->View;
}

const Anchor_EntryView *Anchor_EntryContainer_GetView(Anchor_EntryContainer *container, const char *flag)
{
	Anchor_Entry *entry = s_FindEntry(container, flag);
	if (!entry)
		return NULL;

	return &entry->View;
}

bool Anchor_EntryContainer_IsSet(Anchor_EntryContainer *container, const char *flag)
{
	Anchor_Entry *entry = s_FindEntry(container, flag);
	if (!entry)
		return false;

	return entry->IsSet;
}

bool Anchor_EntryContainer_SetValue(Anchor_EntryContainer *container, const char *flag, const char *value)
{
	Anchor_Entry *entry = s_FindEntry(container, flag);
	if (!entry)
		return false;

	entry->IsSet = true;
	entry->RawValue = value;
	
	return true;
}

const char *Anchor_EntryContainer_GetValue(Anchor_EntryContainer *container, const char *flag)
{
	Anchor_Entry *entry = s_FindEntry(container, flag);
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
	container->Capacity = newCapacity;
	return (int)(newCapacity - oldCapacity);
}

Anchor_Entry *s_FindEntry(Anchor_EntryContainer *container, const char *flag)
{
	for (int i = 0; i < container->Size; i++)
	{
		Anchor_Entry *entry = container->Data + i;
		Anchor_EntryView *view = &entry->View;

		if ((view->ShortFlag) && (strcmp(flag, view->ShortFlag) == 0) || (view->LongFlag) && (strcmp(flag, view->LongFlag) == 0))
		{
			return entry;
		}
	}

	return NULL;
}
