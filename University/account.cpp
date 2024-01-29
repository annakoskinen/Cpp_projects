/* Account
 *
 * Luokassa voidaan muokata käyttäjien, opiskelijoiden tai opettajien, tietoja.
 * Luokkaan lisättyjä metodeja ovat:
 * - sign_up: Ilmoittaa käyttäjän kurssille.
 * - complete: Suorittaa meneillään olevan kurssin.
 * - current_study_state: Palauttaa vektorin käyttäjän meneillään olevista kursseista.
 * - complete_study_state: Palauttaa vektorin käyttäjän suoritetuista kursseista.
 * - graduate: Opiskelijan valmistuminen. Suorittaa kaikki meneillään olevat kurssit.
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

#include "account.hh"
#include "utils.hh"
#include "course.hh"
#include <iostream>
#include <algorithm>

Account::Account(const std::string& full_name, int account_number,
                 int duplicates, const std::string& university_suffix):
    full_name_(full_name),
    last_name_(""),
    first_name_(""),
    account_number_(account_number)
{
    std::vector<std::string> name = Utils::split(full_name_, ' ');
    last_name_ = name.back();
    first_name_ = name.front();

    // Constructing e-mail address
    email_ = Utils::to_lower(first_name_);
    email_ += ".";
    if ( duplicates > 0 )
    {
        email_ += std::to_string(duplicates);
        email_ += ".";
    }
    email_ += Utils::to_lower(last_name_);
    email_ += "@";
    email_ += university_suffix;
}

Account::~Account()
{
}

void Account::print() const
{
    std::cout << account_number_ << ": "
              << first_name_ << " "
              << last_name_  << ", "
              << email_ << std::endl;
}

std::string Account::get_email() const
{
    return email_;
}

std::string Account::get_full_name() const
{
    return full_name_;
}

int Account::get_account_number() const
{
    return account_number_;
}

// Ilmoittaa opiskelijan parametrinä annetulle kurssille.
// Palauttaa totuusarvon false, jos opiskelija on valmistunut. Muuten true.
bool Account::sign_up(std::string course)
{
    // Tarkistetaan, onko opiskelija valmistunut.
    if(graduated_) {
        return false;
    }

    // Luodaan iteraattorit kurssien etsimiseen kurssivektoreista.
    std::vector<std::string>::iterator iter;
    iter = find(uncompleted_courses_.begin(), uncompleted_courses_.end(), course);
    std::vector<std::string>::iterator iter_2;
    iter_2 = find(completed_courses_.begin(), completed_courses_.end(), course);

    // Tarkistetaan löytyykö kurssia suoritetuista kursseista.
    if ( iter_2 != completed_courses_.end() ) {
        std::cout << STUDENT_COMPLETED << std::endl;
    }

    // Tarkistetaan myös meneillään olevat kurssit.
    else if ( iter == uncompleted_courses_.end() ) {

        // Jos kurssia ei löydy, lisätään se vektoriin
        uncompleted_courses_.push_back(course);

        std::cout << SIGNED_UP << std::endl;
    }
    else {
        std::cout << STUDENT_EXISTS << std::endl;
    }
    return true;
}

// Suorittaa opiskelijan parametrinä annetun kurssin.
void Account::complete(std::string course)
{
    // Luodaan iteraattori kurssin etsimiseen meneillään olevista kursseista.
    std::vector<std::string>::iterator iter;
    iter = find(uncompleted_courses_.begin(), uncompleted_courses_.end(), course);

    // Tarkistetaan, onko kurssi vektorissa.
    if ( iter == uncompleted_courses_.end() ) {
        std::cout << NO_SIGNUPS << std::endl;
    }

    // Jos kurssia ei löydy, lisätään se suoritettujen kurssien vektoriin.
    else {
        completed_courses_.push_back(course);
        uncompleted_courses_.erase(iter);
        std::cout << COMPLETED << std::endl;
    }
}

// Palauttaa meneillään olevien kurssien vektorin tulostamista varten.
std::vector<std::string> Account::current_study_state()
{
    return uncompleted_courses_;
}

// Palauttaa suoritettujen kurssien vektorin tulostamista varten.
std::vector<std::string> Account::completed_study_state()
{
    return completed_courses_;
}

// Opiskelijan valmistuminen. Suoritetaan meneillään olevat kurssit.
void Account::graduate()
{
    // Tarkistetaan, onko opiskelija jo valmistunut.
    if(!graduated_) {

        // Merkitään opiskelija valmistuneeksi ja suoritetaan kaikki kurssit.
        graduated_ = true;

        for(auto& course : uncompleted_courses_) {
            completed_courses_.push_back(course);
        }
        uncompleted_courses_.clear();
    }

    // Teksti valmistumisesta tulostetaan, vaikka opiskelija olisi jo valmistunut.
    std::cout << GRADUATED << std::endl;
}



