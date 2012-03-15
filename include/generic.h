#pragma once

#define DEBUG_PRINT

#ifdef DEBUG_PRINT
    #define FUNC_LOG()    std::cout << __PRETTY_FUNCTION__ << std::endl;
#else
    #define FUNC_LOG()
#endif

