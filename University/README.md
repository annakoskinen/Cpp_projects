University projektin kuvaus
 * Ohjelma toteuttaa yliopiston, joka sisältää opiskelijoita, opettajia ja kursseja.
 * Ohjelman käynnistyessä käyttäjältä odotetaan syötettä, jonka avulla yliopistoon lisätään, muokataan
 * tai tulostetaan tietoja.
 
 * Ohjelmalle voi antaa seuraavia käskyjä:
 * QUIT: Ohjelman suoritus päättyy arvoon EXIT_SUCCESS
 * NEW_ACCOUNT: Yliopistoon voidaan lisätä opiskelijoita tai henkilökuntaa. Parametrinä annetaan henkilön nimi. Henkilölle luodaan henkilönumero ja sähköpostiosoite.
 * PRINT_ACCOUNT: Tulostaa annetun henkilön tiedot.
 * PRINT_ACCOUNTS: Tulostaa kaikkien henkilöiden tiedot henkilönumeron mukaisessa järjestyksessä.
 * NEW_COURSE: Luo uuden kurssin. Parametreinä annetaan kurssin koodi ja nimi.
 * ADD_STAFF: Lisää annetulle kurssille opettajaksi annetun henkilön.
 * PRINT_COURSE: Tulostaa annetun kurssin tiedot: nimen, koodin ja opettajat.
 * PRINT_COURSES: Tulostaa kaikki kurssit kurssikoodin mukaisessa järjestyksessä.
 * HELP: Tulostaa kaikki käytössä olevat komennot lyhenteineen tai parametrinä annetun komennon
 * tiedot.
 * READ_FROM: Lukee annetusta tiedostosta komennot niiden parametreineen.
 * SIGN_UP: Ilmoittaa annetulle kurssille annetun opiskelijan.
 * COMPLETE: Lisää annetusta kurssista suorituksen annetulle opiskelijalle.
 * PRINT_STUDY_STATE: Tulostaa annetun opiskelijan opiskelutilanteen: meneillään olevat kurssit, suoritetut kurssit sekä suoritettujen kurssien opintopistemäärän. Kurssit tulostetaan ilmottautumis- ja suorittamisjärjestyksessä.
 * PRINT_COMPLETED: Tulostaa annetun opiskelijan kurssisuoritukset ja kokonaisopintopistemäärän. Kurssit tulostetaan suoritusjärjestyksessä.
 * PRINT_SIGNUPS: Tulostaa annetulle kurssille ilmoittautuneet opiskelijat. Opiskelijat tulostetaan ilmoittautumisjärjestyksessä.
 * GRADUATE: Annettu opiskelija valmistuu ja kaikki hänen kurssinsa merkitään suoritetuiksi.
