/******************************************************************************
Project: M2-Team Common Library
Description: Definition for the DPI scaling.
File Name: M2DPIScaling.h
License: The MIT License
******************************************************************************/

#pragma once

#ifndef _M2_DPI_SCALING_
#define _M2_DPI_SCALING_

#include <Windows.h>

// Enables the Per-Monitor DPI Aware for the specified dialog using the 
// internal API from Windows.
// PS: You need to use this function in Windows 10 Threshold 1 or later.
// Parameters:
//   The function does not have parameters.
// Return value:
//   The function will return a INT. If failed. returns -1.
INT M2EnablePerMonitorDialogScaling();

#endif // _M2_DPI_SCALING_
