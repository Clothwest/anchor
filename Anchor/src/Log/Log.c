#include "Log.h"

#include <stdio.h>
#include <stdarg.h>

static Anchor_Log_Level s_LogLevel = Anchor_Log_Level_Off;

static const char *s_Colors[] = {
	"\x1b[90m", // TRACE
	"\x1b[92m", // INFO
	"\x1b[33m", // WARN
	"\x1b[31m", // ERROR
	"\x1b[41m"  // CRITICAL
};

static const char *s_DefaultColor = "\x1b[0m";

static const char *s_ExtractFileName(const char *filePath);

void Anchor_Log_Init()
{
	Anchor_Log_SetLevel(Anchor_Log_Level_Trace);
}

void Anchor_Log_SetLevel(Anchor_Log_Level level)
{
	s_LogLevel = level;
}

void Anchor_Log(Anchor_Log_Level level, const char *filePath, int line, ...)
{
	if (level < s_LogLevel)
		return;

	if (level >= 5)
		return;

	va_list ap;
	va_start(ap, line);
	const char *fmt = va_arg(ap, const char *);

	fprintf(stderr, "%s[%s] (%d): ", s_Colors[(int)level], s_ExtractFileName(filePath), line);
	vfprintf(stderr, fmt, ap);
	fprintf(stderr, "%s\n", s_DefaultColor);

	va_end(ap);
}

const char *s_ExtractFileName(const char *filePath)
{
	const char *fileName = filePath;
	while (*filePath)
	{
		if (*filePath == '/' || *filePath == '\\')
			fileName = filePath + 1;
		filePath++;
	}
	return fileName;
}
