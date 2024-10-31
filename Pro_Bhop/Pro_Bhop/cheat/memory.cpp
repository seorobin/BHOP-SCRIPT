#include "memory.h"
#include<TlHelp32.h>
#include <process.h>
#include <cstring>

Memory::Memory(const char* processName){
	PROCESSENTRY32 entry;
	entry.dwSize = sizeof(PROCESSENTRY32);

	const auto snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

	while (Process32Next(snapshot, &entry))
	{
		if (!strcmp(processName, entry.szExeFile))
		{
			this->id = entry.th32ProcessID;
			this->Process = OpenProcess(PROCESS_ALL_ACCESS, FALSE, this->id);
			break;
		}
	}
	if (snapshot)
		CloseHandle(snapshot);
}
Memory::Memory() {
	if (this->Process)
		CloseHandle(this->Process);
}

DWORD Memory::GetprocessID() {
	return this->id;
}

HANDLE Memory::GetprocessHandle() {
	return this->Process;
}

uintptr_t Memory::GetModuleAddress(const char* moduleName) {
	MODULEENTRY32 entry;
	entry.dwSize = sizeof(LPMODULEENTRY32);
	const auto snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, this->id);
	uintptr_t result = 0;

	while (Module32Next(snapshot, &entry))
	{
		if (!strcmp(moduleName, entry.szModule)) 
		{
			result = reinterpret_cast<uintptr_t>(entry.modBaseAddr);
			break;
		}
	}

	if (snapshot)
		CloseHandle(snapshot);
	return result;
}

