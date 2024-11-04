#include <Windows.h>
#include <stdio.h>

int Error(const char* msg) {
	printf("%s (%u)\n", msg, ::GetLastError());
	return 1;
}

int main(int argc, const char* argv[]) {
	if (argc < 3) {
		printf("Usage: eid_8_test.exe <pid> <path to dll>\n");
		return 0;
	}

	HANDLE hProcess = ::OpenProcess(PROCESS_VM_WRITE | PROCESS_VM_OPERATION | PROCESS_CREATE_THREAD,FALSE, atoi(argv[1]));
	if (!hProcess)
		return Error("OpenProcess failed");

	void* buffer = ::VirtualAllocEx(hProcess, nullptr, 1 << 12, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
	if (!buffer)
		return Error("VirtualAllocEx failed");

	if (!::WriteProcessMemory(hProcess, buffer, argv[2], ::strlen(argv[2]) + 1, nullptr))
		return Error("WriteProcessMemory failed");

	DWORD tid;
	HANDLE hThread = ::CreateRemoteThread(hProcess, nullptr, 0, (LPTHREAD_START_ROUTINE)::GetProcAddress(::GetModuleHandle(L"kernel32"), "LoadLibraryA"), buffer, 0, &tid);
	if (!hThread)
		return Error("CreateRemoteThread failed");

	printf("Thread %u created successfully!\n", tid);
	if (WAIT_OBJECT_0 == ::WaitForSingleObject(hThread, 10000))
		printf("Thread exited.\n");
	else
		printf("Thread still running.\n");

	::VirtualFreeEx(hProcess, buffer, 0, MEM_RELEASE);

	::CloseHandle(hThread);
	::CloseHandle(hProcess);

	return 0;
}