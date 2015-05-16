
#pragma once

#include "sml/config.h"

#ifndef SML_NONCOPYABLE
#define SML_NONCOPYABLE(class_name) \
	class_name(const class_name&)=delete;\
	class_name& operator=(const class_name&)=delete;
#endif

#ifndef SML_CONFIG_TYPE
#define SML_CONFIG_TYPE \
	using Color  = typename Config::color_type;\
	using Name   = typename Config::name_type;\
	using Matrix = typename Config::matrix_type;\
	using Log    = typename Config::log_type; 
#endif


SML_NAMESPACE_BEGIN

using f32 = float;

SML_NAMESPACE_END