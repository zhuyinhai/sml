
#pragma once


// ----- version --------  
#define SML_VERSION_MAJOR 0U
#define SML_VERSION_MINOR 1U


// ----- namespace --------  
#ifndef SML_NAMESPACE_BEGIN 
#define SML_NAMESPACE_BEGIN namespace sml{
#endif

#ifndef SML_NAMESPACE_END
#define SML_NAMESPACE_END }
#endif

// ----- assertion --------  
#ifndef SML_ASSERT
// #define SML_ASSERT(expr) assert(expr)
#define SML_ASSERT(expr)
#endif

// ----- log trace --------  
#ifndef SML_LOG_ERROR
#define SML_LOG_ERROR 1
#endif

#ifndef SML_LOG_WARNING
#define SML_LOG_WARNING 1
#endif

#ifndef SML_LOG_DEBUG
#define SML_LOG_DEBUG 1
#endif

#if SML_LOG_ERROR
#define SML_ERROR(...) LogTraits<Log>::logError( __FILE__, __LINE__, ##__VA_ARGS__)  
#else
#define SML_ERROR
#endif

#if SML_LOG_WARNING
#define SML_WARNING(...) LogTraits<Log>::logWarning( __FILE__, __LINE__, ##__VA_ARGS__) 
#else
#define SML_WARNING
#endif

#if SML_LOG_DEBUG
#define SML_DEBUG(...) LogTraits<Log>::logDebug( __FILE__, __LINE__, ##__VA_ARGS__)
#else
#define SML_DEBUG
#endif

// ----- utility --------  
#ifndef SML_UNUSE
#define SML_UNUSE(parameter) (void)(parameter)
#endif
