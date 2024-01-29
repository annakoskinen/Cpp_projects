/* Course
 *
 * Luokassa voidaan muokata ja tulostaa kurssin tietoja.
 * Lisätyt metodit:
 * - sign_up_course: Ilmoittaa opiskelijan kurssille.
 * - print_signups: Tulostaa kaikki kurssin opiskelijat.
 *
 * Ohjelman kirjoittaja
 * Nimi: Anna Koskinen
 * Opiskelijanumero: 150185079
 * Käyttäjätunnus: tsanko
 * E-Mail: anna.i.koskinen@tuni.fi
 *
 * Muuta huomioitavaa: Projekti on kommentoitu suomeksi, vaikka pohjakoodi on englanniksi,
 * selkeyden vuoksi.
 *
 */

#include "course.hh"
#include <iostream>

Course::Course(const std::string& code, const std::string& name, int credits):
    course_code_(code), name_(name), credits_(credits)
{
}

Course::~Course()
{
}

void Course::print_info(bool print_new_line)
{
    std::cout << course_code_ << " : " << name_;
    if ( print_new_line )
    {
        std::cout << std::endl;
    }
}

void Course::print_long_info()
{
    std::cout << "* Course name: " << name_ << std::endl
              << "* Code: " << course_code_ << std::endl;
    print_staff();
}

void Course::print_staff()
{
    std::cout << "* Staff: " << std::endl;
    for (auto member : course_staff_ )
    {
        member->print();
    }
}

void Course::add_staff(Account *new_staff_member)
{
    // Checking if account is already a staff member
    for ( unsigned int i = 0; i < course_staff_.size(); ++i )
    {
        if ( course_staff_.at(i) == new_staff_member )
        {
            std::cout << STAFF_EXISTS << std::endl;
            return;
        }
    }

    course_staff_.push_back(new_staff_member);
    std::cout << STAFF_ADDED << std::endl;
}

const std::string Course::get_code() const
{
    return course_code_;
}

int Course::get_credits() const
{
    return credits_;
}

// Ilmoittaa parametrinä annetun opiskelijan kurssille.
void Course::sign_up_course(Account *new_sign_up)
{
    // Tarkistetaan löytyykö opiskelija jo kurssille ilmoittautuneista.
    for ( unsigned int i = 0; i < students_.size(); ++i )
    {
        // Jos löytyy, lopetetaan suoritus.
        if ( students_.at(i) == new_sign_up )
        {
            return;
        }
    }

    // Lisätään opiskelija vektoriin, jossa on kurssin opiskelijat.
    students_.push_back(new_sign_up);
}

// Tulostaa kaikki tietyn kurssin opiskelijat.
void Course::print_signups()
{
    // Tulostetaan tiedot opiskelijoista print -funktion avulla
    for(auto person : students_ ) {
        person->print();
    }
}





