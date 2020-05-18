cmake_minimum_required(VERSION 3.15)
project(GeneticSchedule)

set(CMAKE_CXX_STANDARD 17)

add_executable(GeneticSchedule main.cpp Class.h Schedule.h Chromosome.h Population.cpp Population.h Input.h Random.h)