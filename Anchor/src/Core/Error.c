#include "Anchor/Anchor.h"

#include "Context.h"

#include <stdio.h>

#define ANCHOR_CASE(status) case status: format = #status ": %s"; break

void Anchor_SetErrorCallback(Anchor_Context *ctx, Anchor_ErrorCallback errorCallback)
{
	ctx->ErrorCallback = errorCallback;
}

Anchor_Status Anchor_GetErrorStatus(Anchor_Context *ctx)
{
	return ctx->Error.Status;
}

const Anchor_Error *Anchor_GetError(Anchor_Context *ctx)
{
	return &ctx->Error;
}

size_t Anchor_GetErrorMsg(Anchor_Context *ctx, char *buffer, size_t bufSize)
{
	const char *format = NULL;

	switch (ctx->Error.Status)
	{
		ANCHOR_CASE(Anchor_Status_Success);
		ANCHOR_CASE(Anchor_Status_Failure);
		ANCHOR_CASE(Anchor_Status_OutOfMemory);
		ANCHOR_CASE(Anchor_Status_InvalidFlag);
		ANCHOR_CASE(Anchor_Status_DuplicateFlag);
		ANCHOR_CASE(Anchor_Status_UnknownFlag);
		ANCHOR_CASE(Anchor_Status_MissingValue);
	}

	return (size_t)snprintf(buffer, bufSize, format ? format : "%s", format ? (ctx->Error.Token ? ctx->Error.Token : "----") : "");
}
