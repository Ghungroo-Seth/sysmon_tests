#include <Windows.h>
#include <stdio.h>


int main(int argc, const char* argv[]) {

    FILETIME ft1 = { 0 };

    LPCWSTR fileName = { L"eid_2_test_file.txt" };

    HANDLE hFile = CreateFileW(fileName, GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

    if (hFile == INVALID_HANDLE_VALUE)
    {
        printf("Could not create the file: %lu\n", GetLastError());
    }
    else {
        printf("eid_2_test_file.txt was created.\n");
    }

    // random date from 2022 
    ft1.dwLowDateTime = 2821551380;
    ft1.dwHighDateTime = 30938252;

    if (!SetFileTime(hFile, &ft1, NULL, NULL)) {
        printf("Could not change file creation time: %lu\n", GetLastError());
    }
    else {
        printf("eid_2_test_file.txt Timestomped!\n");
    }
    CloseHandle(hFile);
    return 0;
}