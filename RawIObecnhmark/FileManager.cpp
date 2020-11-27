//
//  Benchmark.cpp
//  RawIObecnhmark
//
//  Created by Игорь Шамрин on 23.11.2020.
//

#include "FileManager.hpp"
#include <random>

int FileManager::random(int min, int max) {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> distrib(min, max);
	return distrib(gen);
}

void FileManager::turnOffCache() {
	if (fcntl(fd, F_NOCACHE) == -1)
		throw std::system_error(errno, std::system_category(), "cache disabling failed");
}

void FileManager::readInRandomPlace() {
	// Для файла 32 гб и блока 4096 байт
	std::size_t offset = random(0, 16677216);
	offset *= blockSize;
	
	if (pread(fd, &vector[0], blockSize, offset) != vector.size())
		throw std::system_error(errno, std::system_category(), "read failed");
}

