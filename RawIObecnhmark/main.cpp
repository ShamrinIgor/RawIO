//
//  main.cpp
//  RawIObecnhmark
//
//  Created by Игорь Шамрин on 23.11.2020.
//

#include <iostream>
#include <benchmark/benchmark.h>
#include "FileManager.hpp"

std::string path = "/Users/igor/Projects/Course4/RawIObecnhmark/bigFile";
FileManager manager = FileManager(path, 4096);
FileManager managerWithoutCache = FileManager(path, 4096);

static void BM_openWithCache(benchmark::State& state) {
	for (auto _ : state)
		manager.readInRandomPlace();
}

static void BM_openWithoutCache(benchmark::State& state) {
	manager.turnOffCache();
	for (auto _ : state)
		manager.readInRandomPlace();
}

int main(int argc, const char * argv[]) {
	managerWithoutCache.turnOffCache();
	BENCHMARK(BM_openWithCache);
	BENCHMARK(BM_openWithoutCache);
	benchmark::RunSpecifiedBenchmarks();
	return 0;
}
