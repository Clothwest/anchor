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

	size_t Count;
	size_t Capacity;

	Anchor_EntryContainer_Status Status;
} Anchor_EntryContainer;

static int s_EGrowIfNeeded(Anchor_EntryContainer *container);
static Anchor_Entry *s_FindEntry(Anchor_EntryContainer *container, const char *flag);

static void s_ResetStatus(Anchor_EntryContainer *container);
static Anchor_EntryContainer_Status s_SetStatus(Anchor_EntryContainer *container, Anchor_EntryContainer_Status status);

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

	container->Count = 0;
	container->Capacity = INIT_CAP;

	s_ResetStatus(container);

	return container;
}

void Anchor_EntryContainer_Destroy(Anchor_EntryContainer *container)
{
	free(container->Data);
	free(container);
}

bool Anchor_EntryContainer_Add(Anchor_EntryContainer *container, const char *sFlag, const char *lFlag, const char *info, Anchor_EntryKind kind)
{
	s_ResetStatus(container);

	if (sFlag && s_FindEntry(container, sFlag) || lFlag && s_FindEntry(container, lFlag))
	{
		s_SetStatus(container, Anchor_EntryContainer_Status_DuplicateFlag);
		return false;
	}

	int grownCapacity = s_EGrowIfNeeded(container);
	if (grownCapacity == -1)
		return false;

	Anchor_Entry *newEntry = container->Data + container->Count++;

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
	return container->Count;
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

Anchor_EntryContainer_Status Anchor_EntryContainer_GetStatus(Anchor_EntryContainer *container)
{
	return container->Status;
}

int s_EGrowIfNeeded(Anchor_EntryContainer *container)
{
	size_t oldCapacity = container->Capacity;

	if (container->Count < container->Capacity)
		return 0;

	size_t newCapacity = 2 * container->Capacity;
	Anchor_Entry *newData = (Anchor_Entry *)realloc(container->Data, newCapacity * sizeof(Anchor_Entry));
	if (!newData)
	{
		s_SetStatus(container, Anchor_EntryContainer_Status_OutOfMemory);
		return -1;
	}

	container->Data = newData;
	container->Capacity = newCapacity;
	return (int)(newCapacity - oldCapacity);
}

Anchor_Entry *s_FindEntry(Anchor_EntryContainer *container, const char *flag)
{
	for (int i = 0; i < container->Count; i++)
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

void s_ResetStatus(Anchor_EntryContainer *container)
{
	container->Status = Anchor_EntryContainer_Status_Success;
}

Anchor_EntryContainer_Status s_SetStatus(Anchor_EntryContainer *container, Anchor_EntryContainer_Status status)
{
	return container->Status = status;
}
