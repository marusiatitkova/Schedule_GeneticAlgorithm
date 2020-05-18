#pragma once

#include <string>
#include <vector>

//enum Type {
//    Lecture,
//    Practice
//};

enum Day {
    Monday,
    Tuesday,
    Wednesday,
    Thursday,
    Friday
};

struct Course {
    std::string name;

    explicit Course(std::string  _name) : name(std::move(_name)) {};

    bool operator == (const Course& other) const {
        return name == other.name;
    }
    bool operator != (const Course& other) const {
        return name != other.name;
    }
};

struct Professor {
    std::string name;
    std::vector<Course> courses;

    explicit Professor(std::string _name, std::vector<Course> _courses) :
            name(std::move(_name)), courses(std::move(_courses)){};

    bool operator == (const Professor& other) const {
        return name == other.name;
    }
};

struct Classroom {
    int number;
    int capacity;

    explicit Classroom(int _number, int _capacity) : number(_number), capacity(_capacity) {};

    bool operator == (const Classroom& other) const {
        return number == other.number;
    }
};

struct StudentGroup {
    std::string name;
    int size;
    std::vector<Course> courses;

    explicit StudentGroup(std::string _name, int _size, std::vector<Course> _courses) :
            name(std::move(_name)), size(_size), courses(std::move(_courses)){};

    bool operator == (const StudentGroup& other) const {
        return name == other.name;
    }
};

struct ClassTime {
    Day day;
    int number;

    explicit ClassTime (Day _day, int _number) : day(_day), number(_number) {};

};

struct Class {
    Course course;
    //Type type;
    StudentGroup group;
    Professor professor;
    Classroom classroom;
    ClassTime classTime;

    explicit Class(Course _course,
            StudentGroup _group, Professor _professor,
            const Classroom& _classroom, const ClassTime& _classTime) :
            course(std::move(_course)),
            group(std::move(_group)), professor(std::move(_professor)),
            classroom(_classroom), classTime(_classTime){};

};


