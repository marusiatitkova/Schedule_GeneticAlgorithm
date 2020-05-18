#pragma once

#include "Schedule.h"

struct Chromosome {
    Schedule schedule;
    double fitness;
    double likelihood;

    Chromosome() {
        fitness = 0.0;
        likelihood = 0.0;
    }

    double calcFitness () {
        int numOfFalse = 0;

        for (const auto & [day, schedulePerClassNumber] : schedule.schedule) {
            for (const auto & [classTime, classes] : schedulePerClassNumber) {
                for (int c1 = 0; c1 < classes.size(); c1++) {
                    for (int c2 = c1 + 1; c2 < classes.size(); c2++) {
                        if (classes[c1].professor == classes[c2].professor) {
                            if (classes[c1].course != classes[c2].course) {
                                numOfFalse++;
                            }
                        }
                        if (classes[c1].classroom == classes[c2].classroom) {
                            if (classes[c1].course != classes[c2].course) {
                                numOfFalse++;
                            }
                        }
                        if (classes[c1].group.size > classes[c2].classroom.capacity) {
                            numOfFalse++;
                        }
                    }
                }
            }
        }

        if (numOfFalse == 0) {
            fitness = -1.0;
        } else
            fitness = 1.0 / static_cast<double>(numOfFalse);

        return fitness;
    }
};

