cmake_minimum_required(VERSION 3.15)
project(GeneticSchedule)

set(CMAKE_CXX_STANDARD 17)

add_executable(GeneticSchedule src/main.cpp include/Class.h include/Schedule.h include/Chromosome.h src/Population.cpp include/Population.h include/Input.h include/Random.h)