
#pragma once

void trace_output(const char* file, int line, const char* format, ...);

#if defined(_DEBUG)
#define TRACE(fmt, ...) trace_output( __FILE__, __LINE__, fmt, ##__VA_ARGS__)
#else
#define TRACE
#endif