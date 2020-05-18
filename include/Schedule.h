#pragma once

#include <map>
#include <algorithm>
#include "Input.h"
#include "Random.h"

struct Schedule {
    typedef std::map<ClassTime, std::vector<Class>> SchedulePerClassNumber;
    std::map<Day, SchedulePerClassNumber> schedule;

    static Schedule generateRandomSchedule (const Input& input) {
        Schedule newSchedule;
        for (const Day& day : input.days) {
            for (int i = 0; i < input.CLASSES_PER_DAY; i++) {
                for (const StudentGroup& group : input.groups) {
                    const Course& course = getRandomVectorElement(group.courses);
                    Professor professor = getRandomVectorElement(getProfessorsForCourse(course, input.professors));
                    std::vector<Classroom> filtered;
                    std::copy_if(input.classrooms.begin(), input.classrooms.end(), std::back_inserter(filtered),
                            [group](const Classroom& room){return room.capacity >= group.size;});
                    Classroom room = getRandomVectorElement(filtered);
                    ClassTime classTime(day, i);
                    newSchedule.schedule[day][classTime].push_back(Class(course, group, professor, room, classTime));
                }
            }
        }
        return newSchedule;
    }

//    /// Было static const Professor&
//    static Professor getRandomProfessor(const std::vector<Professor>& professors, const Course& course) {
//        std::vector<Professor> filtered;
//        std::copy_if(professors.begin(), professors.end(), std::back_inserter(filtered),
//                     [course](const Professor& prof){return std::count(prof.courses.begin(), prof.courses.end(), course) != 0;});
//        return getRandomVectorElement(filtered);
//    }

    static std::vector<Professor> getProfessorsForCourse (const Course& course, const std::vector<Professor>& professors) {
        std::vector<Professor> fitted;
        for (const auto& p : professors) {
            if (std::count(p.courses.begin(), p.courses.end(), course) != 0) {
                fitted.push_back(p);
            }
        }
        return fitted;
    }
};
