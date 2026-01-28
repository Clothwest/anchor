#include "Scanner.h"

#include <stdio.h>
#include <stdlib.h>

#include <windows.h>

static long s_CountLines(const char *filePath);

void Tloc_Scan(const char *path, bool recursive, bool verbose)
{
	if (!path)
		return;

	char *searchPath = (char *)malloc(MAX_PATH);
	if (!searchPath)
		return;

	snprintf(searchPath, MAX_PATH, "%s\\*.*", path);

	WIN32_FIND_DATAA fd;
	HANDLE hFind = FindFirstFileA(searchPath, &fd);

	if (hFind == INVALID_HANDLE_VALUE)
	{
		printf("Failed to list directory: %s\n", path);
		return;
	}

	do
	{
		if (strcmp(fd.cFileName, ".") == 0 || strcmp(fd.cFileName, "..") == 0)
			continue;

		char *fullPath = searchPath;
		snprintf(fullPath, MAX_PATH, "%s\\%s", path, fd.cFileName);

		if (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{
			if (recursive)
			{
				Tloc_Scan(fullPath, recursive, verbose);
			}
		}
		else
		{
			long lines = s_CountLines(fullPath);
			if (verbose)
			{
				printf("%-40s : %ld\n", fd.cFileName, lines);
			}
		}
	} while (FindNextFileA(hFind, &fd));

	free(searchPath);
	FindClose(hFind);
}

long s_CountLines(const char *filePath)
{
	FILE *file = fopen(filePath, "rb");
	if (!file)
		return 0;

	long lines = 0;
	char *buffer = (char *)malloc(4096);
	if (!buffer)
		return 0;
	size_t n;

	while ((n = fread(buffer, 1, 4096, file)) > 0)
	{
		for (size_t i = 0; i < n; i++)
		{
			if (buffer[i] == '\n')
				lines++;
		}
	}

	free(buffer);
	fclose(file);
	return lines;
}
