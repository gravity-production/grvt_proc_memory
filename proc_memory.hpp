//
// Created by Alexandr on 2/8/2023.
//

#ifndef GMA2PATCH_PROC_MEMORY_HPP
#define GMA2PATCH_PROC_MEMORY_HPP

#include <fstream>
#include <windows.h>
#include <psapi.h>
#include <vector>
#include <algorithm>

typedef long long int BIN_OFFSET;

class proc_memory {
public:
	/**
	 * get_file_stream
	 * @param proc process handler
	 * @return std::ifstream object with exec dump
	 */
	static std::ifstream get_file_stream(HANDLE proc);
	/**
	 *
	 * @param proc
	 * @return std::vector<byte>
	 */
	static std::vector<byte> copy_exec_to_buffer(HANDLE proc);
	static std::vector<byte> copy_module_to_buffer(HANDLE proc, LPVOID base_address, DWORD size);
	static BIN_OFFSET get_sequence_offset(const std::vector<byte>& buffer, const std::vector<byte>& sequence);
};

#endif //GMA2PATCH_PROC_MEMORY_HPP
