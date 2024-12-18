﻿#include <iostream>
#include <stdio.h>
#include <wchar.h>
#include <windows.h>
#include "ConsoleColors.h"

using namespace std;

int ConsoleColors::EnableColor() {
    // Set output mode to handle virtual terminal sequences
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hOut == INVALID_HANDLE_VALUE)
    {
        return false;
    }
    HANDLE hIn = GetStdHandle(STD_INPUT_HANDLE);
    if (hIn == INVALID_HANDLE_VALUE)
    {
        return false;
    }

    DWORD dwOriginalOutMode = 0;
    DWORD dwOriginalInMode = 0;
    if (!GetConsoleMode(hOut, &dwOriginalOutMode))
    {
        return false;
    }
    if (!GetConsoleMode(hIn, &dwOriginalInMode))
    {
        return false;
    }

    DWORD dwRequestedOutModes = ENABLE_VIRTUAL_TERMINAL_PROCESSING | DISABLE_NEWLINE_AUTO_RETURN;
    DWORD dwRequestedInModes = ENABLE_VIRTUAL_TERMINAL_INPUT;

    DWORD dwOutMode = dwOriginalOutMode | dwRequestedOutModes;
    if (!SetConsoleMode(hOut, dwOutMode))
    {
        // we failed to set both modes, try to step down mode gracefully.
        dwRequestedOutModes = ENABLE_VIRTUAL_TERMINAL_PROCESSING;
        dwOutMode = dwOriginalOutMode | dwRequestedOutModes;
        if (!SetConsoleMode(hOut, dwOutMode))
        {
            // Failed to set any VT mode, can't do anything here.
            return -1;
        }
    }

    DWORD dwInMode = dwOriginalInMode | dwRequestedInModes;
    if (!SetConsoleMode(hIn, dwInMode))
    {
        // Failed to set VT input mode, can't do anything here.
        return -1;
    }
}

void ConsoleColors::DisableColor() {
    cout << "\033[0m" << flush;
}

void ConsoleColors::SetColor(Color color) {
    cout << "\033[48;5;" << color << "m" << flush;
}

void ConsoleColors::wprint(wstring message, int size)
{
    /*  wprint prints a string that can have any emoji or Unicode characters.
        When creating a wstring, put an L in front of it.
        For example, `wprint(L"Hi! 🔥");` prints `Hi! 🔥`.
        Your file must be saved in the UTF-8 (_with_ BOM/signature) encoding.
    */
#ifdef _WIN32
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD n_written;
    WriteConsoleW(handle, message.c_str(), size, &n_written, NULL);
#else
    std::wcout << message;
#endif
}