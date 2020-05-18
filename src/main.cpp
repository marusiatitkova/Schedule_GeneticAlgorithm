#include <iostream>
#include <functional>
#include <iomanip>
#include "../include/Population.h"

using namespace std;

const double mutationRate = 0.02;
const int populationSize = 50;
const int MAX_ITERATIONS = 5000000;

std::ostream& operator<<(std::ostream& out, Day day) {
    switch (day) {
        case Monday:
            out << "MONDAY";
            break;
        case Tuesday:
            out << "TUESDAY";
            break;
        case Wednesday:
            out << "WEDNESDAY";
            break;
        case Thursday:
            out << "THURSDAY";
            break;
        case Friday:
            out << "FRIDAY";
            break;
        default: out << int(day); break;
    }
    return out;
}

int main() {
    vector<Course> courses = {Course("AI"),
                              Course("SQL"),
                              Course("System Programming"),
                              Course("Data Science"),
                              Course("Business Analytics"),
                              Course("Algebra"),
                              Course("Algorithms and Data Structures"),
                              Course("Object-oriented programming"),
                              Course("C++"),
                              Course("Java"),
                              Course("Cryptography"),
                              Course("English")};

    vector<Day> days = {Day::Monday, Day::Tuesday, Day::Wednesday, Day::Thursday, Day::Friday};
    const int CLASSES_PER_DAY = 4;

    vector<StudentGroup> groups = {StudentGroup("TTP", 56, generateCourses(courses)),
                                   StudentGroup("TK", 25, generateCourses(courses)),
                                   StudentGroup("MI", 29, generateCourses(courses))};

    vector<Professor> professors = {Professor("Tigra", generateCourses(courses)),
                                    Professor("Winnie the Pooh", generateCourses(courses)),
                                    Professor("Ia", generateCourses(courses)),
                                    Professor("Shrek", generateCourses(courses)),
                                    Professor("Donkey", generateCourses(courses)),
                                    Professor("Fiona", generateCourses(courses)),
                                    Professor("Gingy", generateCourses(courses)),
                                    Professor("Puss in Boots", generateCourses(courses)),
                                    Professor("Wolf", generateCourses(courses))};

    vector<Classroom> classrooms = {Classroom(43, 100),
                                    Classroom(39, 100),
                                    Classroom(312, 26),
                                    Classroom(316, 30),
                                    Classroom(201, 27),
                                    Classroom(205, 34),
                                    Classroom(309, 35),
                                    Classroom(45, 58),
                                    Classroom(30, 63)};


    Input input(courses, groups, professors, classrooms, days, CLASSES_PER_DAY);
    Population population(input, mutationRate, populationSize);

    int iterations = 0;

    while (!population.answerReady() && iterations < MAX_ITERATIONS) {
        iterations++;
        population.createNewPopulation();
        if (iterations % 100 == 0) {
            cout << iterations << "\n";
        }
    }

    cout << "population size = " << populationSize << "\n";
    cout << "mutation rate = " << mutationRate << "\n";
    cout << "iterations = " << iterations << "\n";
    cout << "answer is ready = " << population.answerReady() << "\n";

    auto schedule = population.getAnswer().schedule;

    for(const auto& [day, schedulePerLesson] : schedule) {
        cout << "#########################################\n";
        cout << "DAY: " << day << endl;
        for (const auto& group : groups) {
            cout << "GROUP: " << group.name << endl;
            for (const auto& [time, listOfClasses] : schedulePerLesson) {
                auto class_ = std::find_if(listOfClasses.begin(), listOfClasses.end(),
                        [group](const Class& testClass){return testClass.group == group;});
                cout << time.number + 1 << ". Course = " << class_->course.name << endl;
                cout << "Professor = " << class_->professor.name << endl;
                cout << "Classroom = " << class_->classroom.number << endl;
            }
            cout << "-------------------------------------\n";
        }
        cout << "#########################################\n";
    }

    return 0;
}