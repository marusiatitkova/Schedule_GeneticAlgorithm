#pragma once

#include "Class.h"

struct Input {

    Input(const std::vector<Course>& _courses, const std::vector<StudentGroup>& _groups,
            const std::vector<Professor>& _professors, const std::vector<Classroom>& _classrooms,
            const std::vector<Day>& _days, const int& classes_per_day) : courses(_courses), groups(_groups),
            professors(_professors), classrooms(_classrooms), days(_days), CLASSES_PER_DAY(classes_per_day) {};

    const std::vector<Course>& courses;
    const std::vector<StudentGroup>& groups;
    const std::vector<Professor>& professors;
    const std::vector<Classroom>& classrooms;
    const std::vector<Day>& days;

    int CLASSES_PER_DAY;
};
