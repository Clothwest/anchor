#include "PosArgContainer.h"

#include <stdlib.h>

#define INIT_CAP 4

typedef struct Anchor_PosArg
{
	const char *RawValue;
} Anchor_PosArg;

typedef struct Anchor_PosArgContainer
{
	Anchor_PosArg *Data;

	size_t Count;
	size_t Capacity;

	Anchor_PosArgContainer_Status Status;
} Anchor_PosArgContainer;

static int s_EGrowIfNeeded(Anchor_PosArgContainer *container);

static void s_ResetStatus(Anchor_PosArgContainer *container);
static Anchor_PosArgContainer_Status s_SetStatus(Anchor_PosArgContainer *container, Anchor_PosArgContainer_Status status);

Anchor_PosArgContainer *Anchor_PosArgContainer_Create(void)
{
	Anchor_PosArgContainer *container = (Anchor_PosArgContainer *)malloc(sizeof(Anchor_PosArgContainer));
	if (!container)
		return NULL;

	container->Data = (Anchor_PosArg *)malloc(INIT_CAP * sizeof(Anchor_PosArg));
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

void Anchor_PosArgContainer_Destroy(Anchor_PosArgContainer *container)
{
	free(container->Data);
	free(container);
}

bool Anchor_PosArgContainer_Add(Anchor_PosArgContainer *container, const char *arg)
{
	s_ResetStatus(container);

	int grownCapacity = s_EGrowIfNeeded(container);
	if (grownCapacity == -1)
		return false;

	Anchor_PosArg *newArg = container->Data + container->Count++;

	newArg->RawValue = arg;

	return true;
}

const char *Anchor_PosArgContainer_GetAt(Anchor_PosArgContainer *container, size_t index)
{
	return container->Data[index].RawValue;
}

size_t Anchor_PosArgContainer_GetCount(Anchor_PosArgContainer *container)
{
	return container->Count;
}

Anchor_PosArgContainer_Status Anchor_PosArgContainer_GetStatus(Anchor_PosArgContainer *container)
{
	return container->Status;
}

int s_EGrowIfNeeded(Anchor_PosArgContainer *container)
{
	size_t oldCapacity = container->Capacity;

	if (container->Count < container->Capacity)
		return 0;

	size_t newCapacity = 2 * container->Capacity;
	Anchor_PosArg *newData = (Anchor_PosArg *)realloc(container->Data, newCapacity * sizeof(Anchor_PosArg));
	if (!newData)
	{
		s_SetStatus(container, Anchor_PosArgContainer_Status_OutOfMemory);
		return -1;
	}

	container->Data = newData;
	container->Capacity = newCapacity;
	return (int)(newCapacity - oldCapacity);
}

void s_ResetStatus(Anchor_PosArgContainer *container)
{
	container->Status = Anchor_PosArgContainer_Status_Success;
}

Anchor_PosArgContainer_Status s_SetStatus(Anchor_PosArgContainer *container, Anchor_PosArgContainer_Status status)
{
	return container->Status = status;
}
