#pragma once

typedef enum Anchor_Log_Level
{
	Anchor_Log_Level_Trace = 0,
	Anchor_Log_Level_Info,
	Anchor_Log_Level_Warn,
	Anchor_Log_Level_Error,
	Anchor_Log_Level_Critical,
	Anchor_Log_Level_Off
} Anchor_Log_Level;

void Anchor_Log_Init();
void Anchor_Log_SetLevel(Anchor_Log_Level level);

void Anchor_Log(Anchor_Log_Level level, const char *filePath, int line, ...);

#ifdef ANCHOR_DEBUG
#define ANCHOR_INIT_LOG()                     Anchor_Log_Init()
#define ANCHOR_SET_LOG_LEVEL(level)           Anchor_Log_SetLevel(level)

#define ANCHOR_TRACE(...)                Anchor_Log(Anchor_Log_Level_Trace, __FILE__, __LINE__, __VA_ARGS__)
#define ANCHOR_INFO(...)                 Anchor_Log(Anchor_Log_Level_Info, __FILE__, __LINE__, __VA_ARGS__)
#define ANCHOR_WARN(...)                 Anchor_Log(Anchor_Log_Level_Warn, __FILE__, __LINE__, __VA_ARGS__)
#define ANCHOR_ERROR(...)                Anchor_Log(Anchor_Log_Level_Error, __FILE__, __LINE__, __VA_ARGS__)
#define ANCHOR_CRITICAL(...)             Anchor_Log(Anchor_Log_Level_Critical, __FILE__, __LINE__, __VA_ARGS__)

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