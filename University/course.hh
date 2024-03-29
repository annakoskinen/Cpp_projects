﻿/* Class: Course
 * -------------
 * COMP.CS.110 Ohjelmointi 2: Rakenteet / Programming 2: Structures
 * -------------
 * Class representing a single course, with name and code, staff and students.
 *
 * */
#ifndef COURSE_HH
#define COURSE_HH

#include "account.hh"
#include <string>
#include <vector>

//const std::string STUDENT_ADDED = "A new student has been added.";
const std::string STAFF_ADDED = "A new staff member has been added.";
const std::string STAFF_EXISTS = "Error: Staff member already added on this course.";
const std::string STUDENT_EXISTS = "Error: Student already added on this course.";
const std::string STUDENT_COMPLETED = "Error: Student already completed this course.";


class Course
{
public:
    /**
     * @brief Course
     * @param code unique code for the course, used as id
     * @param name
     * @param credits
     */
    Course( const std::string& code, const std::string& name, int credits = 5);

    /**
     * @brief Course destructor
     */
    ~Course();

    /**
     * @brief print_info
     * @param print_new_line
     * Print short course info, if print_new_line, pring also a newline
     * at the end.
     */
    void print_info(bool print_new_line);

    /**
     * @brief print_long_info
     * Print longer course info with staff.
     */
    void print_long_info();

    /**
     * @brief print_staff
     * Print all staff of the course.
     */
    void print_staff();

    /**
     * @brief add staff
     * @param new_staff
     * Add a staff member to course.
     */
    void add_staff(Account* new_staff_member);

    /**
     * @brief get_code
     * @return the course code.
     */
    const std::string get_code() const;

    /**
     * @brief get_credits
     * @return the amount of credits this course is valued.
     */
    int get_credits() const;

    /**
     * @brief sign_up
     * @param new_sign_up opiskelija, joka ilmoitetaan kurssille
     * Ilmoittaa opiskelijan kurssille.
     */
    void sign_up_course(Account* new_sign_up);

    /**
     * @brief print_signups
     * Tulostaa kurssille ilmoittautuneet opiskelijat.
     */
    void print_signups();

private:
    std::string course_code_;
    std::string name_;
    int credits_;
    std::vector<Account*> course_staff_;

    // Vektori, joka sisältää tiedon tietyn kurssin opiskelijoista.
    std::vector<Account*> students_;
};

#endif // COURSE_HH


