//
// Created by Alexandr on 2/8/2023.
//

#include "proc_memory.hpp"
std::ifstream proc_memory::get_file_stream(HANDLE proc)
{
	char* filename = new char[100];
	//todo fix hardcoded length
	if (GetModuleFileNameEx(proc, nullptr, filename, 100)==0)
		throw std::runtime_error("Getting gma2onpc path failed");
	std::ifstream proc_file(filename, std::ios::in | std::ios::binary);
	delete[]filename;
	return proc_file;
}

std::vector<byte> proc_memory::copy_exec_to_buffer(HANDLE proc)
{
	std::ifstream process_file = get_file_stream(proc);
	std::vector<byte> exec_buffer;
	exec_buffer.assign(std::istreambuf_iterator<char>(process_file), std::istreambuf_iterator<char>());
	process_file.close();
	return exec_buffer;
}
BIN_OFFSET proc_memory::get_sequence_offset(const std::vector<byte>& buffer, const std::vector<byte>& sequence)
{
	auto element = std::search(buffer.begin(), buffer.end(), sequence.begin(), sequence.end());
	if (element==buffer.end())
		throw std::runtime_error("Offset not found");

	return std::distance(buffer.begin(), element);
}
std::vector<byte> proc_memory::copy_module_to_buffer(HANDLE proc, LPVOID base_address, DWORD size)
{
	std::vector<byte> module_buffer(size);
	if (ReadProcessMemory(proc, base_address, module_buffer.data(), size,
			nullptr)==0)
		throw std::runtime_error("Runtime buffer creating error");
	return module_buffer;
}