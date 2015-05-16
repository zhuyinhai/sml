
#include "test_d3d11/trace.h"

#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <wchar.h>

#include <windows.h>


void trace_output(const char* file, int line, const char* format, ...)
{
	char buffer[256];

	va_list ap;
	va_start(ap, format);
	vsprintf_s(buffer, _countof(buffer), format, ap);
	va_end(ap);

	char text[_countof(buffer)];
	_snprintf_s(text, _countof(text), "%s [%s:line %d]\n", buffer, file, line);

	::OutputDebugStringA(text);
}