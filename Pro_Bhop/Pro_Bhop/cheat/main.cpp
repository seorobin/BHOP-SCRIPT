#include "memory.h"
#include <thread>

namespace offsets
{
	constexpr auto localplayer = 0xD892CC;
	constexpr auto flags = 0x104;
	constexpr auto forcejump = 0x524BF4C;
}
int main() 
{
	auto mem = Memory("csgo.exe");

	std::cout << "process id:" << mem.GetprocessID() << std::endl;

	const auto client = mem.GetModuleAddress("client.dll");
	std::cout << "client.dll ->" << "0x" << std::hex << client << std::dec << std::endl;

	while (true)
	{
		const auto localplayer = mem.Read<uintptr_t>(client + offsets::localplayer);
		if (localplayer)
		{
			const auto onGround = mem.Read<bool>(localplayer + offsets::flags);
			if (GetAsyncKeyState(VK_SPACE) && onGround & (1 < 0))
				mem.Write<BYTE>(client + offsets::forcejump, 6);
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(5));
	}

}