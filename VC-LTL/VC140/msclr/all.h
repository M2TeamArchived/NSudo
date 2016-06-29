/***
*all.h
*
*       Copyright (c) Microsoft Corporation. All rights reserved.
*
*Purpose:   Header file to include all MSL functionality
*
*       [Public]
*
****/

#pragma once

#if !defined (_INC_MSCLR_ALL)

#ifndef __cplusplus_cli
#error ERROR: msclr libraries are not compatible with /clr:oldSyntax
#endif  /* __cplusplus_cli */

#include <msclr\appdomain.h>
#include <msclr\auto_gcroot.h>
#include <msclr\auto_handle.h>
#include <msclr\event.h>
#include <msclr\lock.h>
#include <msclr\gcroot.h>
#include <msclr\com\ptr.h>

#define _INC_MSCLR_ALL

#endif  /* !defined (_INC_MSCLR_ALL) */
