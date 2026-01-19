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

	size_t Size;
	size_t Capacity;
} Anchor_PosArgContainer;

static int s_GrowIfNeeded(Anchor_PosArgContainer *container);

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

	container->Size = 0;
	container->Capacity = INIT_CAP;

	return container;
}

void Anchor_PosArgContainer_Destroy(Anchor_PosArgContainer *container)
{
	free(container->Data);
	free(container);
}

bool Anchor_PosArgContainer_Add(Anchor_PosArgContainer *container, const char *arg)
{
	size_t grownCapacity = s_GrowIfNeeded(container);
	if (grownCapacity == -1)
		return false;

	Anchor_PosArg *newArg = container->Data + container->Size++;

	newArg->RawValue = arg;

	return true;
}

const char *Anchor_PosArgContainer_GetAt(Anchor_PosArgContainer *container, size_t index)
{
	return container->Data[index].RawValue;
}

size_t Anchor_PosArgContainer_GetCount(Anchor_PosArgContainer *container)
{
	return container->Size;
}

int s_GrowIfNeeded(Anchor_PosArgContainer *container)
{
	size_t oldCapacity = container->Capacity;

	if (container->Size < container->Capacity)
		return 0;

	size_t newCapacity = 2 * container->Capacity;
	Anchor_PosArg *newData = (Anchor_PosArg *)realloc(container->Data, newCapacity * sizeof(Anchor_PosArg));
	if (!newData)
		return -1;

	container->Data = newData;
	return (int)(newCapacity - oldCapacity);
}
