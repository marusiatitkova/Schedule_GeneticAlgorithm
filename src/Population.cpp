#include "../include/Population.h"

const Chromosome CHROMOSOME_NOT_FOUND;

bool operator < (const ClassTime& lhs, const ClassTime& rhs) {
    return lhs.number < rhs.number;
}

Population::Population(Input input, double mutationRate, size_t populationSize) : scheduleInput(input), mutationRate_(mutationRate) {
    answerFound = false;

    population_.resize(populationSize);
    for (Chromosome& chromosome : population_) {
        chromosome.schedule = Schedule::generateRandomSchedule(input);
    }
    calcLikelihood();
}

void Population::calcLikelihood() {
    double sum = 0.0;
    for (Chromosome& chromosome : population_) {
        chromosome.fitness = chromosome.calcFitness();
        if (chromosome.fitness == -1.0) {
            answerFound = true;
            answer = chromosome.schedule;
            return;
        }
        sum += chromosome.fitness;
    }

    for (Chromosome& chromosome : population_) {
        chromosome.likelihood = chromosome.fitness / sum;
    }
}

void Population::createNewPopulation() {
    std::vector<Chromosome> newPopulation;
    newPopulation.reserve(population_.size());
    for (int i = 0; i < population_.size(); i++) {
        Chromosome parent1 = generateChromosome();
        Chromosome parent2 = generateChromosome();
        newPopulation.push_back(mutation(crossover(parent1, parent2)));
    }
    population_ = std::move(newPopulation);
    calcLikelihood();
}

Chromosome Population::crossover(const Chromosome &chromo1, const Chromosome &chromo2) const {
    const auto& schedule1 = chromo1.schedule.schedule;
    const auto& schedule2 = chromo2.schedule.schedule;
    Chromosome child;
    for (const auto& [day, schedulePerClassNumber] : schedule1) {
        if (getRandomBool()) {
            child.schedule.schedule[day] = crossoverLessons(schedule1.at(day), schedule2.at(day));
        } else
            child.schedule.schedule[day] = crossoverLessons(schedule2.at(day), schedule1.at(day));
    }

    return child;
}

Schedule::SchedulePerClassNumber Population::crossoverLessons(const Schedule::SchedulePerClassNumber &schedule1,
                                                              const Schedule::SchedulePerClassNumber &schedule2) const{
    Schedule::SchedulePerClassNumber child;
    for (const auto& [time, listOfClasses] : schedule1) {
        if(getRandomBool()) {
            child[time] = crossoverClasses(schedule1.at(time), schedule2.at(time));
        } else
            child[time] = crossoverClasses(schedule2.at(time), schedule1.at(time));
    }

    return child;
}

std::vector<Class> Population::crossoverClasses(const std::vector<Class>& classes1, const std::vector<Class>& classes2) const {
    std::vector<Class> child;
    int border = randomForVector(classes1);
    child.reserve(classes1.size());
    for(int i = 0; i < classes1.size(); i++) {
        if (i < border) {
            child.push_back(crossoverClassFields(classes1.at(i), classes2.at(i)));
        } else
            child.push_back(crossoverClassFields(classes2.at(i), classes1.at(i)));
    }

    return child;
}

Class Population::crossoverClassFields (const Class &class1, const Class &class2) const {
    Class child = class1;

    if(!getRandomBool()) {
        child.classroom = class2.classroom;
    }

    if(!getRandomBool() && class1.course == class2.course) {
        child.professor = class2.professor;
    }

    if(!getRandomBool()) {
        child.course = class2.course;
        child.professor = class2.professor;
    }

    return child;
}

Chromosome Population::mutation(Chromosome chromosome) const {
    for (auto& [day, schedulePerClassNumber] : chromosome.schedule.schedule) {
        for (auto& [time, listofclasses] : schedulePerClassNumber) {
            for (auto& groupClass : listofclasses) {
                if (getRandomProbability() < mutationRate_){
                    groupClass.classroom = getRandomVectorElement(scheduleInput.classrooms);
                }
                if (getRandomProbability() < mutationRate_) {
                    groupClass.professor = getRandomVectorElement(
                            Schedule::getProfessorsForCourse(groupClass.course, scheduleInput.professors));
                }
                if (getRandomProbability() < mutationRate_) {
                    groupClass.course = getRandomVectorElement(scheduleInput.courses);
                    groupClass.professor = getRandomVectorElement(
                            Schedule::getProfessorsForCourse(groupClass.course, scheduleInput.professors));
                }
            }
        }
    }
    return chromosome;
}

const Chromosome& Population::generateChromosome() {
    double sum = 0.0;
    double probability = getRandomProbability();
    for (const Chromosome& chromosome : population_) {
        sum += chromosome.likelihood;
        if (sum > probability) {
            return chromosome;
        }
    }
    std::cerr << "Sum = " << sum <<  " probability = "<< probability << "\n";
    printPopulation();
    std::cerr << " Chromosome not found\n";
    return CHROMOSOME_NOT_FOUND;
}

bool Population::answerReady() const {
    return answerFound;
}

const Schedule &Population::getAnswer() const {
    return answer;
}

void Population::printPopulation() {
    for (const auto &chromo : population_) {
        std::cout << chromo.likelihood << " " << chromo.fitness << "\n" ;
        std::cout << "#########################################\n";
        for (const auto&[day, schedulePerLesson] : chromo.schedule.schedule) {
            std::cout << "DAY: " << day << std::endl;
            for (const auto&[time, listOfClasses] : schedulePerLesson) {
                for (const auto &classes : listOfClasses) {
                    std::cout << time.number << " " << classes.course.name << " " << classes.professor.name << " "
                              << classes.classroom.number << " " << classes.group.name << std::endl;
                }
            }
            std::cout << "----------------------------------------\n";
        }
        std::cout << "############################################\n";
    }
}







