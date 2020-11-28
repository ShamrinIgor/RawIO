//
//  Benchmark.hpp
//  RawIObecnhmark
//
//  Created by Игорь Шамрин on 23.11.2020.
//

#ifndef Benchmark_h
#define Benchmark_h

#include <vector>
#include <random>
#include <boost/align.hpp>
#include <fcntl.h>
#include <cerrno>
#include <system_error>

class FileManager {
	int fd;
	std::size_t blockSize;
	std::vector<char, boost::alignment::aligned_allocator<char, 4096>> vector;

	int random(int min, int max);

public:
	/// Конструктор Benchmark
	/// @param path  путь к файлу
	/// @param blockSize размер блока
	FileManager(std::string_view path, std::size_t blockSize):
	blockSize(blockSize), vector(blockSize) {
		if ((fd = open(std::string(path).c_str(), O_RDONLY)) == -1)
			throw std::system_error(errno, std::system_category(), "open failed");
	}

	~FileManager() {
		close(fd);
	}

	/// Прочитать файл в случайном месте
	void readInRandomPlace();
	/// Функция отключения кэша файловой системы
	void turnOffCache();
};


#endif /* Benchmark_h */

