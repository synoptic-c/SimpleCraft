#pragma once
#include<iostream>
#if defined(_DEBUG) || !defined(NDEBUG)
#define PRINT_ERROR(message)\
	do\
	{\
		std::cerr << "[" << __FILE__ << ":" << __LINE__ << "]" << message << "\n";\
	}while(0)
#define PRINT_ERROR_FILE(message, path)\
	do\
	{\
		PRINT_ERROR(message);\
		std::cerr << "File path:" << path << "\n";\
	}while(0)
#else
#define PRINT_ERROR(message) (void)0
#define PRINT_ERROR_FILE(message, path) (void)0
#endif