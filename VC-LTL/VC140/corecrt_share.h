//
// corecrt_share.h
//
//      Copyright (c) Microsoft Corporation. All rights reserved.
//
// Defines the file sharing modes for the sopen() family of functions.  These
// declarations are split out to support the Windows build.
//
#pragma once



#define _SH_DENYRW      0x10    // deny read/write mode
#define _SH_DENYWR      0x20    // deny write mode
#define _SH_DENYRD      0x30    // deny read mode
#define _SH_DENYNO      0x40    // deny none mode
#define _SH_SECURE      0x80    // secure mode



#if !__STDC__
    #define SH_DENYRW _SH_DENYRW
    #define SH_DENYWR _SH_DENYWR
    #define SH_DENYRD _SH_DENYRD
    #define SH_DENYNO _SH_DENYNO
#endif
