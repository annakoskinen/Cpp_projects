/* University
 *
 * Luokassa voidaan muokata ja tulostaa tietoja yliopiston sisällöstä eli opiskelijoista, opettajista ja
 * kursseista.
 * Itse toteutetut metodit:
 * - sign_up: Ilmoittaa opiskelijan kurssille. Tulostaa virheilmoituksen vääristä parametreistä.
 * - complete: Suorittaa opiskelijan kurssin. Tulostaa virheilmoituksen vääristä parametreistä.
 * - print_signups: Tulostaa kurssin opiskelijat. Tulostaa virheilmoituksen vääristä parametreistä.
 * - print_completed: Tulostaa opiskelijan kaikki kurssit ja opintopistemäärän. Tulostaa virheilmoituksen
 * vääristä parametreistä.
 * - print_study_state: Tulostaa tiedon opiskelijan meneillään olevista ja suoritetuista kursseista.
 * Tulostaa virheilmoituksen vääristä parametreistä.
 * - graduate: Suorittaa kaikki opiskelijan kaikki kurssit. Tulostaa virheilmoituksen vääristä parametreistä.
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


#include "university.hh"
#include <iostream>

University::University(const std::string& email_suffix):
    running_number_(111111), email_suffix_(email_suffix)
{
}

University::~University()
{
    for ( auto course : courses_ )
    {
        delete course.second;
    }

    for ( auto account : accounts_ )
    {
        delete account.second;
    }
}

void University::new_course(Params params)
{
    std::string code = params.at(0);
    std::string name = params.at(1);
    if ( courses_.find(code) != courses_.end() )
    {
        std::cout << ALREADY_EXISTS << std::endl;
        return;
    }
    else
    {
        std::cout << NEW_COURSE << std::endl;
    }

    Course* n_course = new Course(code, name);
    courses_.insert({n_course->get_code(), n_course});
}

void University::print_courses(Params)
{
    for ( auto course : courses_ )
    {
        course.second->print_info(true);
    }
}

void University::print_course(Params params)
{
    std::string code = params.at(0);
    if ( courses_.find(code) == courses_.end() )
    {
        std::cout << CANT_FIND << code << std::endl;
        return;
    }

    courses_.at(code)->print_long_info();
}

void University::new_account(Params params)
{
    std::string full_name = params.at(0);
    int num = 0;
    for ( std::map<int, Account*>::iterator iter = accounts_.begin();
          iter != accounts_.end();
          ++iter )
    {
        if ( iter->second->get_full_name() == full_name )
        {
            std::string email = iter->second->get_email();
            num = Utils::numeric_part(email);
            if(num == 0)
            {
                ++num;
            }
            ++num;
        }
    }

    int account_number = running_number_++;
    Account* n_account = new Account(full_name, account_number, num,
                                     email_suffix_);
    accounts_.insert({account_number, n_account});
    std::cout << NEW_ACCOUNT << std::endl;
    n_account->print();
}

void University::print_accounts(Params)
{
    for ( auto account : accounts_ )
    {
        account.second->print();
    }
}

void University::print_account(Params params)
{
    int account = std::stoi(params.at(0));
    std::map<int, Account*>::iterator iter = accounts_.find(account);
    if ( iter == accounts_.end() )
    {
        std::cout << CANT_FIND << account << std::endl;
        return;
    }
    iter->second->print();
}

void University::add_staff(Params params)
{
    std::string code = params.at(0);
    int account = std::stoi(params.at(1));
    if ( courses_.find(code) == courses_.end() )
    {
        std::cout << CANT_FIND << code << std::endl;
        return;
    }
    if ( accounts_.find(account) == accounts_.end() )
    {
        std::cout << CANT_FIND << account << std::endl;
        return;
    }

    courses_.at(code)->add_staff(accounts_.at(account));
}

// Ilmoittaa käyttäjän kurssille.
// Parametrinä vektori params, jonka tulee sisältää kurssikoodi ja opiskelijanumero.
// Jos parametreissä on virhe, tulostuu virheilmoitus.
void University::sign_up(Params params)
{
    // Tallenetaan parametreinä annetut tiedot muuttujiin.
    std::string course_code = params.at(0);
    int student_number = std::stoi(params.at(1));

    // Tarkistetaan löytyykö parametreinä annetut tiedot kursseista ja käyttäjistä.
    // Tulostetaan mahdollinen virheilmoitus.
    if(courses_.find(course_code) == courses_.end()) {
        std::cout << CANT_FIND << course_code << std::endl;
    }
    else if(accounts_.find(student_number) == accounts_.end()) {
        std::cout << CANT_FIND << student_number << std::endl;
    }
    else {
        // Kutsutaan funktiota sign_up, joka lisää kurssin käyttäjän kursseihin.
        // Tulostetaan virheilmoitus, jos opiskelija on valmistunut.
        if(!accounts_.at(student_number)->sign_up(course_code)) {
            std::cout << ALREADY_GRADUATED << std::endl;
        }

        // Kutsutaan funktiota sign_up_course, joka lisää käyttäjän kurssin kävijäksi.
        courses_.at(course_code)->sign_up_course(accounts_.at(student_number));
    }
}

// Suorittaa kurssin, jolle opiskelija on aikaisemmin ilmoittautunut.
// Parametrinä vektori params, jonka tulee sisältää kurssikoodi ja opiskelijanumero.
void University::complete(Params params)
{
    // Tallenetaan parametreinä annetut tiedot muuttujiin.
    std::string course_code = params.at(0);
    int student_number = std::stoi(params.at(1));

    // Tarkistetaan löytyykö parametreinä annetut tiedot kursseista ja käyttäjistä.
    // Tulostetaan mahdollinen virheilmoitus.
    if(courses_.find(course_code) == courses_.end()) {
        std::cout << CANT_FIND << course_code << std::endl;
    }
    else if(accounts_.find(student_number) == accounts_.end()) {
        std::cout << CANT_FIND << student_number << std::endl;
    }
    else {
        // Kutsutaan funktiota complete, jonka avulla opiskelijan kurssi suoritetaan.
        accounts_.at(student_number)->complete(course_code);
    }
}

// Tulostaa nykyiset kurssille ilmoittautuneet henkilöt.
// Parametrinä vektori params, jonka tulee sisältää kurssikoodi.
void University::print_signups(Params params)
{
    // Tallenetaan parametrinä annettu kurssikoodi.
    std::string course_code = params.at(0);

    // Tarkistetaan löytyykö haluttua kurssia kaikista kursseista.
    // Tulostetaan mahdollinen virheilmoitus.
    if(courses_.find(course_code) == courses_.end()) {
        std::cout << CANT_FIND << course_code << std::endl;
    }
    else {
        // Kutsutaan funktiota print_signups, jonka avulla ilmoittauneet tulostetaan.
        courses_.at(course_code)->print_signups();
    }
}

// Tulostaa opiskelijan suoritetut kurssit ja opintopistemäärän.
// Parametrinä vektori params, jonka tulee sisältää opiskelijanumero
void University::print_completed(Params params)
{
    // Tallennetaan parametrinä annettu opiskelijanumero.
    int student_number = std::stoi(params.at(0));

    // Tarkistetaan löytyykö käyttäjää kaikista käyttäjistä.
    // Tulostetaan mahdollinen virheilmoitus.
    if(accounts_.find(student_number) == accounts_.end()) {
        std::cout << CANT_FIND << student_number << std::endl;
    }
    else {
        // Luodaan kokonaispintopistemäärälle muuttuja credits.
        int credits = 0;

        // Tallennetaan suoritetut kurssit vektoriin kutsumalla funktiota completed_study_state
        std::vector<std::string> completed = accounts_.at(student_number)->completed_study_state();

        // Käydään suoritetut kurssit läpi ja tulostetaan tiedot.
        for(auto& course : completed) {

            // Haetaan kurssin opintopistemäärä ja lisätään se kokonaisopintopistemäärään.
            int course_credits = courses_.at(course)->get_credits();
            credits += course_credits;

            // Tulostetaan tiedot print_info funktion avulla.
            courses_.at(course)->print_info(true);
        }

        // Tulostetaan opiskelijan opintopistemäärä.
        std::cout << "Total credits: " << credits << std::endl;
    }
}

// Tulostaa opiskelijan meneillään olevat sekä suoritetut kurssit ja opintopistemäärän.
// Parametrinä vektori params, jonka tulee sisältää opiskelijanumero
void University::print_study_state(Params params)
{
    // Tallennetaan parametrinä annettu opiskelijanumero.
    int student_number = std::stoi(params.at(0));

    // Tarkistetaan löytyykö käyttäjää kaikista käyttäjistä.
    // Tulostetaan mahdollinen virheilmoitus.
    if(accounts_.find(student_number) == accounts_.end()) {
        std::cout << CANT_FIND << student_number << std::endl;
    }
    else {
        std::cout << "Current:" << std::endl;

        // Tallennetaan nykyiset kurssit vektoriin kutsumalla funktiota current_study_state
        std::vector<std::string> uncompleted = accounts_.at(student_number)->current_study_state();

        // Käydään meneillään olevat kurssit läpi ja tulostetaan tiedot.
        for(auto& course : uncompleted) {
            courses_.at(course)->print_info(true);
        }

        // Luodaan opintopistemäärälle muuttuja credits.
        int credits = 0;

        std::cout << "Completed:" << std::endl;

        // Tallennetaan suoritetut kurssit vektoriin kutsumalla funktiota current_study_state
        std::vector<std::string> completed = accounts_.at(student_number)->completed_study_state();

        // Käydään suoritetut kurssit läpi ja tulostetaan tiedot.
        for(auto& course : completed) {

            // Haetaan kurssin opintopistemäärä ja lisätään se kokonaisopintopistemäärään.
            int course_credits = courses_.at(course)->get_credits();
            credits += course_credits;

            courses_.at(course)->print_info(true);
        }

        // Tulostetaan opiskelijan opintopistemäärä.
        std::cout << "Total credits: " << credits << std::endl;
    }
}

// Suorittaa kaikki kurssit, joille opiskelija on ilmoittautunut.
// Valmistumisen jälkeen opiskelija ei voi enää ilmoittautua kursseille.
// Parametrinä vektori params, jonka tulee sisältää opiskelijanumero.
void University::graduate(Params params)
{
    // Tallennetaan parametrinä annettu opiskelijanumero.
    int student_number = std::stoi(params.at(0));

    // Tarkistetaan löytyykö käyttäjää kaikista käyttäjistä.
    // Tulostetaan mahdollinen virheilmoitus.
    if(accounts_.find(student_number) == accounts_.end()) {
        std::cout << CANT_FIND << student_number << std::endl;
    }
    else {
        // Kutsutaan funktiota graduate, jolla opiskelijan valmistuminen suoritetaan.
        accounts_.at(student_number)->graduate();
    }
}
