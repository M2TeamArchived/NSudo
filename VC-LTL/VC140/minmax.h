//
// minmax.h
//
//      Copyright (c) Microsoft Corporation. All rights reserved.
//
// Familiar min() and max() macros
//
#pragma once
#define _INC_MINMAX



#ifndef max
    #define max(a ,b) (((a) > (b)) ? (a) : (b))
#endif

#ifndef min
    #define min(a, b) (((a) < (b)) ? (a) : (b))
#endif
