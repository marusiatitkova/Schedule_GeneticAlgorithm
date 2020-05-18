#pragma once

#include <iostream>
#include "Chromosome.h"
#include "Random.h"

class Population {
public:
    Population(Input input, double mutationRate, size_t populationSize);

    void createNewPopulation();

    bool answerReady() const;

    const Schedule& getAnswer() const;

private:
    Chromosome mutation(Chromosome chromosome) const;

    Chromosome crossover(const Chromosome& chromo1, const Chromosome& chromo2) const;

    Schedule::SchedulePerClassNumber crossoverLessons(const Schedule::SchedulePerClassNumber& schedule1, const Schedule::SchedulePerClassNumber& schedule2) const;

    std::vector<Class> crossoverClasses(const std::vector<Class>& classes1, const std::vector<Class>& classes2) const;

    Class crossoverClassFields(const Class& class1, const Class& class2) const;

    void calcLikelihood();

    const Chromosome& generateChromosome();

    Input scheduleInput;
    std::vector<Chromosome> population_;
    double mutationRate_;

    bool answerFound;
    Schedule answer;

    void printPopulation();
};

bool operator < (const ClassTime& lhs, const ClassTime& rhs);