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

/// Класс отвечающий за работу с большим файлом
class FileManager {
	int fd; /**< Файловый дискрпитор */
	std::size_t blockSize; /**< Размер блока */
	std::vector<char, boost::alignment::aligned_allocator<char, 4096>> vector; /**< Вектор с выравниванием 4096 байт */

	/// Генератор случайно числа в диапозоне
	/// @param min начало диапозона
	/// @param max конец даипозона
	int random(int min, int max) const;

public:
	/// Конструктор FileManaged
	/// @param path  путь к файлу
	/// @param blockSize размер блока
	FileManager(std::string_view path, std::size_t blockSize):
	blockSize(blockSize), vector(blockSize) {
		if ((fd = open(std::string(path).c_str(), O_RDONLY)) == -1)
			throw std::system_error(errno, std::system_category(), "open failed");
	}

	FileManager(const FileManager& manager)=delete;

	/// Деструктор FileManaged
	~FileManager() {
		close(fd);
	}

	/// Прочитать файл в случайном месте
	void readInRandomPlace();
	/// Функция отключения кэша файловой системы
	void turnOffCache() const;
};


#endif /* Benchmark_h */

