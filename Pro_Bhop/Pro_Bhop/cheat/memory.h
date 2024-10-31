#pragma once
#include <Windows.h>
#include <iostream>

class Memory
{
	private:
		DWORD id = 0; // id of process
		HANDLE Process = NULL; // handle the process
	
	public:
		Memory(const char* processName);
		Memory();

		DWORD GetprocessID();
		HANDLE GetprocessHandle();

		uintptr_t GetModuleAddress(const char* moduleName);

		template <typename T>
		T Read(uintptr_t adress) {
			T value;
			ReadprocessMemory(this->process, (LPCVOID)adress, &value, sizeof(T), NULL);
			return value;
		}
		template <typename T>
		bool Write(uintptr_t adress, T value){
			return writeprocessmemory(this->Process, (LPVOID)adress, &value, sizeof(T), NULL);
		}


};