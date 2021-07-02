/*
 * PROJECT:   Mouri Optimization Plugin
 * FILE:      MouriOptimizationPlugin.h
 * PURPOSE:   Private definition for Mouri Optimization Plugin
 *
 * LICENSE:   The MIT License
 *
 * DEVELOPER: Mouri_Naruto (Mouri_Naruto AT Outlook.com)
 */

#ifndef MOURI_OPTIMIZATION_PLUGIN
#define MOURI_OPTIMIZATION_PLUGIN

#include <Mile.Windows.h>
#include <NSudoContext.h>

/**
 * @brief Prints the final result to the NSudo user interface.
 * @param Context The NSudo context.
 * @param hr The HResult object containing the error code.
 * @param FailedPoint The failed point string.
*/
void MoPrivatePrintFinalResult(
    _In_ PNSUDO_CONTEXT Context,
    _In_ Mile::HResult const& hr,
    _In_ LPCWSTR FailedPoint);

/**
 * @brief Prints the pruge scan result to the NSudo user interface.
 * @param Context The NSudo context.
 * @param ByteSize The numeric byte size value to be converted.
*/
void MoPrivatePrintPurgeScanResult(
    _In_ PNSUDO_CONTEXT Context,
    _In_ std::uint64_t ByteSize);

#define MO_PRIVATE_PURGE_MODE_SCAN  1
#define MO_PRIVATE_PURGE_MODE_PURGE 2

/**
 * @brief Parses the purge mode from context plugin command arguments or the
 *        user input.
 * @param Context The NSudo context.
 * @return The purge mode, it can be zero or one of the following values.
 *         MO_PRIVATE_PURGE_MODE_SCAN
 *             Do scanning.
 *         MO_PRIVATE_PURGE_MODE_PURGE
 *             Do purging.
*/
DWORD MoPrivateParsePurgeMode(
    _In_ PNSUDO_CONTEXT Context);

#endif // !MOURI_OPTIMIZATION_PLUGIN
