#pragma once

typedef enum Anchor_LogLevel
{
	Anchor_LogLevel_Trace = 0,
	Anchor_LogLevel_Info,
	Anchor_LogLevel_Warn,
	Anchor_LogLevel_Error,
	Anchor_LogLevel_Critical,
	Anchor_LogLevel_Off
} Anchor_LogLevel;

void Anchor_InitLog();
void Anchor_SetLogLevel(Anchor_LogLevel level);

void Anchor_Log(Anchor_LogLevel level, const char *filePath, int line, ...);

#ifdef ANCHOR_DEBUG
#define ANCHOR_INIT_LOG()                Anchor_InitLog()
#define ANCHOR_SET_LOG_LEVEL(level)      Anchor_SetLogLevel(level)

#define ANCHOR_TRACE(...)                Anchor_Log(Anchor_LogLevel_Trace, __FILE__, __LINE__, __VA_ARGS__)
#define ANCHOR_INFO(...)                 Anchor_Log(Anchor_LogLevel_Info, __FILE__, __LINE__, __VA_ARGS__)
#define ANCHOR_WARN(...)                 Anchor_Log(Anchor_LogLevel_Warn, __FILE__, __LINE__, __VA_ARGS__)
#define ANCHOR_ERROR(...)                Anchor_Log(Anchor_LogLevel_Error, __FILE__, __LINE__, __VA_ARGS__)
#define ANCHOR_CRITICAL(...)             Anchor_Log(Anchor_LogLevel_Critical, __FILE__, __LINE__, __VA_ARGS__)

#define ANCHOR_ASSERT(condition, ...)    do { if (!(condition)) { ANCHOR_CRITICAL("Assertion Failed: " __VA_ARGS__); __debugbreak(); } } while(0)

#else
#define ANCHOR_INIT_LOG()
#define ANCHOR_SET_LOG_LEVEL(level)

#define ANCHOR_TRACE(...)
#define ANCHOR_INFO(...)
#define ANCHOR_WARN(...)
#define ANCHOR_ERROR(...)
#define ANCHOR_CRITICAL(...)

#define ANCHOR_ASSERT(condition, ...)
#endif