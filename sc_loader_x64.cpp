// sc_loader_x64.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <windows.h>
#include <tchar.h>

typedef void (*shellcode_t)();
using namespace std;
int _tmain(int argc, TCHAR* argv[])
{
    HANDLE hFile;
    size_t nfile_size;
    DWORD dwBytesRead = 0;

    if (argc != 2) {
        cout << "Usage:" << argv[0] << " file_name" << endl;
        exit(-1);
    }
    hFile = CreateFile(argv[1], // name of the write
        GENERIC_READ,            // open for reading
        0,                       // do not share
        NULL,                    // default security
        OPEN_ALWAYS,           // create new file only
        FILE_ATTRIBUTE_NORMAL,   // normal file
        NULL);                   // no attr. template

    nfile_size = GetFileSize(hFile, NULL);
   
    shellcode_t shellcode = (shellcode_t) VirtualAlloc(0, nfile_size+2, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
    
    
    *((uint8_t*)(shellcode)) = 0xCC;

    ReadFile(hFile, (uint8_t*)(shellcode)+1, nfile_size, &dwBytesRead, NULL);

    CloseHandle(hFile);

    shellcode();
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
