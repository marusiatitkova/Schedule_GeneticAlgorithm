#pragma once

#include <random>

static std::mt19937& random_generator_seed() {
    std::random_device randomDevice;
    static std::mt19937 generator(randomDevice());
    return generator;
};

static double getRandomProbability() {
    std::uniform_real_distribution<double> distribution(0.0, 1.0);
    return distribution(random_generator_seed());
}

static bool getRandomBool() {
    std::uniform_int_distribution<int> randomBool(0,1);
    return randomBool(random_generator_seed());
}

template <typename T>
static int randomForVector(const std::vector<T>& vec) {
    std::uniform_int_distribution<int> border(0, vec.size() - 1);
    return border(random_generator_seed());
}

template <typename T>
static const T& getRandomVectorElement(const std::vector<T>& vec) {
    int pos = randomForVector(vec);
    return vec[pos];
}


static std::vector<Course> generateCourses(const std::vector<Course>& courses) {
    std::vector<Course> res;
    std::uniform_int_distribution<int> numberOfCourses(1,courses.size() - 1);
    int size = numberOfCourses(random_generator_seed());
    std::sample(courses.begin(), courses.end(), std::back_inserter(res),
               size, random_generator_seed());
    return res;
}