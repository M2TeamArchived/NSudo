/*
 * PROJECT:   Mouri Internal Library Essentials
 * FILE:      Mile.Windows.Core.cpp
 * PURPOSE:   Core Implementation for Windows
 *
 * LICENSE:   The MIT License
 *
 * DEVELOPER: Mouri_Naruto (Mouri_Naruto AT Outlook.com)
 */

#include "Mile.Windows.Core.h"

#pragma region Implementations for Windows (Win32 Style)

Mile::HResultFromLastError Mile::CloseHandle(
    _In_ HANDLE hObject)
{
    return ::CloseHandle(hObject);
}

#pragma endregion

#pragma region Implementations for Windows (C++ Style)

std::wstring Mile::GetHResultMessage(
    HResult const& Value)
{
    std::wstring Message{ L"Failed to get formatted message." };

    LPWSTR RawMessage = nullptr;
    DWORD RawMessageSize = ::FormatMessageW(
        FORMAT_MESSAGE_ALLOCATE_BUFFER |
        FORMAT_MESSAGE_FROM_SYSTEM |
        FORMAT_MESSAGE_IGNORE_INSERTS,
        nullptr,
        Value,
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
        reinterpret_cast<LPTSTR>(&RawMessage),
        0,
        nullptr);
    if (RawMessageSize)
    {
        Message = std::wstring(RawMessage, RawMessageSize);

        ::LocalFree(RawMessage);
    }

    return Message;
}

std::wstring Mile::ToUtf16String(
    std::string const& Utf8String)
{
    std::wstring Utf16String;

    int Utf16StringLength = ::MultiByteToWideChar(
        CP_UTF8,
        0,
        Utf8String.c_str(),
        static_cast<int>(Utf8String.size()),
        nullptr,
        0);
    if (Utf16StringLength > 0)
    {
        Utf16String.resize(Utf16StringLength);
        Utf16StringLength = ::MultiByteToWideChar(
            CP_UTF8,
            0,
            Utf8String.c_str(),
            static_cast<int>(Utf8String.size()),
            &Utf16String[0],
            Utf16StringLength);
        Utf16String.resize(Utf16StringLength);
    }

    return Utf16String;
}

std::string Mile::ToUtf8String(
    std::wstring const& Utf16String)
{
    std::string Utf8String;

    int Utf8StringLength = ::WideCharToMultiByte(
        CP_UTF8,
        0,
        Utf16String.data(),
        static_cast<int>(Utf16String.size()),
        nullptr,
        0,
        nullptr,
        nullptr);
    if (Utf8StringLength > 0)
    {
        Utf8String.resize(Utf8StringLength);
        Utf8StringLength = ::WideCharToMultiByte(
            CP_UTF8,
            0,
            Utf16String.data(),
            static_cast<int>(Utf16String.size()),
            &Utf8String[0],
            Utf8StringLength,
            nullptr,
            nullptr);
        Utf8String.resize(Utf8StringLength);
    }

    return Utf8String;
}

#pragma endregion
