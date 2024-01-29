/* Class: Account
 * --------------
 * COMP.CS.110 Ohjelmointi 2: Rakenteet / Programming 2: Structures
 * -------------
 * Class representing a student or a staff account in the university system.
 *
 * */
#ifndef ACCOUNT_HH
#define ACCOUNT_HH

#include <string>
#include <vector>


class Course;

const std::string NO_SIGNUPS = "No signups found on this course.";
const std::string SIGNED_UP = "Signed up on the course.";
const std::string COMPLETED = "Course completed.";
const std::string GRADUATED = "Graduated, all courses completed.";

class Account
{
public:
    /**
     * @brief Account constructor
     * @param full_name as "firstname lastname"
     * @param account_number
     * @param duplicates tells the number of full namesakes
     * @param university_suffix is the e-mail suffix e.g. "tuni.fi"
     */
    Account(const std::string& full_name, int account_number, int duplicates,
            const std::string& university_suffix);

    /**
     * @brief Account destructor
     */
    ~Account();

    /**
     * @brief print account info on one line
     */
    void print() const;

    /**
     * @brief get_email
     * @return email linked to this account
     */
    std::string get_email() const;

    /**
     * @brief get_full_name
     * @return full name of this account
     */
    std::string get_full_name() const;

    /**
     * @brief get_account_number
     * @return account number linked to this account
     */
    int get_account_number() const;

    /**
     * @brief sign_up
     * @param course kurssi, jolle opiskelija halutaan ilmoittaa
     * @return false, jos opiskelija on valmistunut. Muuten true.
     * Ilmoittaa opiskelijan kurssille.
     */
    bool sign_up(std::string course);

    /**
     * @brief complete
     * @param course kurssi, jonka opiskelija haluaa suoritetuksi
     * Suorittaa opiskelijan meneillään olevan kurssin.
     */
    void complete(std::string course);

    /**
     * @brief current_study_state
     * @return vektori, joka sisältää opiskelijan meneillään olevat kurssit.
     * Palauttaa opiskelijan meneillään olevat kurssit.
     */
    std::vector<std::string>  current_study_state();

    /**
     * @brief completed_study_state
     * @return vektori, joka sisältää opiskelijan suoritetut kurssit.
     * Palauttaa opiskelijan suoritetut kurssit.
     */
    std::vector<std::string> completed_study_state();

    /**
     * @brief graduate
     * Opiskelija valmistuu ja kaikki kurssit suoritetaan.
     */
    void graduate();

private:
    std::string full_name_;
    std::string last_name_;
    std::string first_name_;
    std::string email_;
    const int account_number_;

    // Tieto siitä, onko opiskelija valmistunut
    bool graduated_ = false;

    // Vektori opiskelijan käynnissä oleville kursseille
    std::vector<std::string> uncompleted_courses_;

    // Vektori opiskelian suoritetuille kursseille
    std::vector<std::string> completed_courses_;
};

#endif // ACCOUNT_HH


