//
//  main.cpp
//  RawIObecnhmark
//
//  Created by Игорь Шамрин on 23.11.2020.
//

#include <iostream>
#include <benchmark/benchmark.h>
#include "FileManager.hpp"
#include <optional>

std::optional<FileManager> manager;
std::optional<FileManager> managerWithoutCache;
const int blockSize = 4096;

static void BM_openWithCache(benchmark::State& state) {
	for (auto _ : state) {
		for (uint64_t i = 0; i < 8388608; i++)
			manager->readInRandomPlace();
	}
}

static void BM_openWithoutCache(benchmark::State& state) {
	for (auto _ : state) {
		for (uint64_t i = 0; i < 8388608; i++)
			manager->readInRandomPlace();
	}
}

int main(int argc, const char * argv[]) {
	const char *path = argv[1];
	manager.emplace(path, blockSize);
	managerWithoutCache.emplace(path, blockSize);
	managerWithoutCache->turnOffCache();
	BENCHMARK(BM_openWithCache);
	BENCHMARK(BM_openWithoutCache);
	benchmark::RunSpecifiedBenchmarks();
	return 0;
}
