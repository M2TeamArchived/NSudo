/*
 * PROJECT:   Mouri Internal Library Essentials
 * FILE:      Mile.Windows.Storage.cpp
 * PURPOSE:   Storage Implementation for Windows
 *
 * LICENSE:   Apache-2.0 License
 *
 * DEVELOPER: Mouri_Naruto (Mouri_Naruto AT Outlook.com)
 */

#include "Mile.Windows.Storage.h"

#include "Mile.Windows.Core.h"

#include <strsafe.h>

namespace
{
    /**
     * @brief The internal content of the file enumerator handle.
    */
    typedef struct _FILE_ENUMERATOR_OBJECT
    {
        HANDLE FileHandle;
        CRITICAL_SECTION CriticalSection;
        PFILE_ID_BOTH_DIR_INFO CurrentFileInfo;
        BYTE FileInfoBuffer[32768];
    } FILE_ENUMERATOR_OBJECT, * PFILE_ENUMERATOR_OBJECT;

    using Mile::Windows::Storage::FILE_ENUMERATOR_HANDLE;
}

FILE_ENUMERATOR_HANDLE Mile::Windows::Storage::CreateFileEnumerator(
    _In_ HANDLE FileHandle)
{
    if (!FileHandle || FileHandle == INVALID_HANDLE_VALUE)
    {
        ::SetLastError(ERROR_INVALID_PARAMETER);
        return nullptr;
    }

    PFILE_ENUMERATOR_OBJECT Object = reinterpret_cast<PFILE_ENUMERATOR_OBJECT>(
        Mile::HeapMemory::Allocate(sizeof(FILE_ENUMERATOR_OBJECT)));
    if (!Object)
    {
        ::SetLastError(ERROR_NOT_ENOUGH_MEMORY);
        return nullptr;
    }

    Object->FileHandle = FileHandle;
    Mile::CriticalSection::Initialize(&Object->CriticalSection);

    return Object;
}

BOOL Mile::Windows::Storage::CloseFileEnumerator(
    _In_ FILE_ENUMERATOR_HANDLE FileEnumeratorHandle)
{
    if (!FileEnumeratorHandle)
    {
        ::SetLastError(ERROR_INVALID_PARAMETER);
        return FALSE;
    }

    PFILE_ENUMERATOR_OBJECT Object =
        reinterpret_cast<PFILE_ENUMERATOR_OBJECT>(FileEnumeratorHandle);

    Mile::CriticalSection::Delete(&Object->CriticalSection);

    return Mile::HeapMemory::Free(Object);
}

BOOL Mile::Windows::Storage::QueryFileEnumerator(
    _In_ FILE_ENUMERATOR_HANDLE FileEnumeratorHandle,
    _Out_ PFILE_ENUMERATOR_INFORMATION FileEnumeratorInformation)
{
    if ((!FileEnumeratorHandle) || (!FileEnumeratorInformation))
    {
        ::SetLastError(ERROR_INVALID_PARAMETER);
        return FALSE;
    }

    BOOL Result = FALSE;

    PFILE_ENUMERATOR_OBJECT Object =
        reinterpret_cast<PFILE_ENUMERATOR_OBJECT>(FileEnumeratorHandle);

    Mile::CriticalSection::Enter(&Object->CriticalSection);

    if (!Object->CurrentFileInfo)
    {
        Object->CurrentFileInfo =
            reinterpret_cast<PFILE_ID_BOTH_DIR_INFO>(Object->FileInfoBuffer);

        Result = ::GetFileInformationByHandleEx(
            Object->FileHandle,
            FILE_INFO_BY_HANDLE_CLASS::FileIdBothDirectoryRestartInfo,
            Object->CurrentFileInfo,
            sizeof(Object->FileInfoBuffer));
    }
    else if (!Object->CurrentFileInfo->NextEntryOffset)
    {
        Object->CurrentFileInfo =
            reinterpret_cast<PFILE_ID_BOTH_DIR_INFO>(Object->FileInfoBuffer);

        Result = ::GetFileInformationByHandleEx(
            Object->FileHandle,
            FILE_INFO_BY_HANDLE_CLASS::FileIdBothDirectoryInfo,
            Object->CurrentFileInfo,
            sizeof(Object->FileInfoBuffer));
    }
    else
    {
        Object->CurrentFileInfo = reinterpret_cast<PFILE_ID_BOTH_DIR_INFO>(
            reinterpret_cast<ULONG_PTR>(Object->CurrentFileInfo)
            + Object->CurrentFileInfo->NextEntryOffset);
    }

    if (Result)
    {
        PFILE_ID_BOTH_DIR_INFO CurrentFileInfo = Object->CurrentFileInfo;

        FileEnumeratorInformation->CreationTime.dwLowDateTime =
            CurrentFileInfo->CreationTime.LowPart;
        FileEnumeratorInformation->CreationTime.dwHighDateTime =
            CurrentFileInfo->CreationTime.HighPart;

        FileEnumeratorInformation->LastAccessTime.dwLowDateTime =
            CurrentFileInfo->LastAccessTime.LowPart;
        FileEnumeratorInformation->LastAccessTime.dwHighDateTime =
            CurrentFileInfo->LastAccessTime.HighPart;

        FileEnumeratorInformation->LastWriteTime.dwLowDateTime =
            CurrentFileInfo->LastWriteTime.LowPart;
        FileEnumeratorInformation->LastWriteTime.dwHighDateTime =
            CurrentFileInfo->LastWriteTime.HighPart;

        FileEnumeratorInformation->ChangeTime.dwLowDateTime =
            CurrentFileInfo->ChangeTime.LowPart;
        FileEnumeratorInformation->ChangeTime.dwHighDateTime =
            CurrentFileInfo->ChangeTime.HighPart;

        FileEnumeratorInformation->FileSize =
            CurrentFileInfo->EndOfFile.QuadPart;

        FileEnumeratorInformation->AllocationSize =
            CurrentFileInfo->AllocationSize.QuadPart;

        FileEnumeratorInformation->FileAttributes =
            CurrentFileInfo->FileAttributes;

        FileEnumeratorInformation->EaSize =
            CurrentFileInfo->EaSize;

        FileEnumeratorInformation->FileId =
            CurrentFileInfo->FileId;

        ::StringCbCopyNW(
            FileEnumeratorInformation->ShortName,
            sizeof(FileEnumeratorInformation->ShortName),
            CurrentFileInfo->ShortName,
            CurrentFileInfo->ShortNameLength);

        ::StringCbCopyNW(
            FileEnumeratorInformation->FileName,
            sizeof(FileEnumeratorInformation->FileName),
            CurrentFileInfo->FileName,
            CurrentFileInfo->FileNameLength);
    }

    Mile::CriticalSection::Leave(&Object->CriticalSection);

    return Result;
}
