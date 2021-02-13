/* Muistipeli
 *
 * Kuvaus:
 *  Ohjelma toteuttaa muistipelin. Pelissä on vaihteleva määrä kortteja ja
 * pelaajia. Pelin alussa käyttäjältä kysytään myäs siemenluku, koska kortit
 * arvotaan satunnaisesti pelilaudalle.
 *  Joka kierroksella vuorossa oleva pelaaja antaa kahden kortin
 * koordinaatit (yhteensä neljä lukua), minkä jälkeen kyseiset kortit
 * käännetään näkyviin ja kerrotaan, ovatko ne parit vai ei.
 * Jos pelaaja sai parit, kortit poistetaan pelilaudalta, pelaajan
 * pistesaldoa kasvatetaan, ja hän saa uuden vuoron. Jos pelaaja ei saanut
 * pareja, kortit käännetään takaisin piiloon, ja vuoro siirtyy seuraavalle
 * pelaajalle.
 *  Ohjelma tarkistaa pelaajan antamat koordinaatit. Koordinaattien pitää
 * olla sellaiset, että niiden määrä kortti löytyy pelilaudalta.
 *  Muutosten jälkeen pelilauta tulostetaan aina uudelleen. Kortit kuvataan
 * kirjaimina alkaen A:sta niin pitkälle, kuin kortteja on. Kun pelilauta
 * tulostetaan, näkyvissä oleva kortti kuvataan kyseisellä kirjaimella.
 * Piiloon käännettyä korttia kuvaa risuaita (#), ja laudalta poistetun
 * kortin kohdalle tulostetaan piste.
 *  Peli päättyy, kun kaikki parit on löydetty, ja pelilauta on tyhjä.
 * Tällöin kerrotaan, kuka tai ketkä voittivat eli saivat eniten pareja.
 *
 * Ohjelman kirjoittaja
 * Nimi: Aleksi Iso-Seppälä
 * Opiskelijanumero: H292168
 * Käyttäjätunnus: fsalis
 * E-Mail: aleksi.iso-seppala@tuni.fi
 *
 * */

#include <player.hh>
#include <card.hh>
#include <iostream>
#include <vector>
#include <random>

using namespace std;

const string INPUT_AMOUNT_OF_CARDS = "Enter the amount of cards (an even number): ";
const string INPUT_SEED = "Enter a seed value: ";
const string INPUT_AMOUNT_OF_PLAYERS = "Enter the amount of players (one or more): ";
const string INPUT_CARDS = "Enter two cards (x1, y1, x2, y2), or q to quit: ";
const string INVALID_CARD = "Invalid card.";
const string FOUND = "Pairs found.";
const string NOT_FOUND = "Pairs not found.";
const string GIVING_UP = "Why on earth you are giving up the game?";
const string GAME_OVER = "Game over!";

using Game_row_type = vector<Card>;
using Game_board_type = vector<vector<Card>>;

// Muuntaa annetun numeerisen merkkijonon vastaavaksi kokonaisluvuksi
// (kutsumalla stoi-funktiota).
// Jos annettu merkkijono ei ole numeerinen, palauttaa nollan
// (mikä johtaa laittomaan korttiin myöhemmin).
unsigned int stoi_with_check(const string& str)
{
    bool is_numeric = true;
    for(unsigned int i = 0; i < str.length(); ++i)
    {
        if(not isdigit(str.at(i)))
        {
            is_numeric = false;
            break;
        }
    }
    if(is_numeric)
    {
        return stoi(str);
    }
    else
    {
        return 0;
    }
}

// Täyttää pelilaudan (kooltaan rows * columns) tyhjillä korteilla.
void init_with_empties(Game_board_type& g_board, unsigned int rows, unsigned int columns)
{
    g_board.clear();
    Game_row_type row;
    for(unsigned int i = 0; i < columns; ++i)
    {
        Card card;
        row.push_back(card);
    }
    for(unsigned int i = 0; i < rows; ++i)
    {
        g_board.push_back(row);
    }
}

// Etsii seuraavan tyhjän kohdan pelilaudalta (g_board) aloittamalla
// annetusta kohdasta start ja jatkamalla tarvittaessa alusta.
// (Kutsutaan vain funktiosta init_with_cards.)
unsigned int next_free(Game_board_type& g_board, unsigned int start)
{
    // Selvitetään annetun pelilaudan rivien ja sarakkeiden määrät
    //
    // Finding out the number of rows and columns of the game board
    unsigned int rows = g_board.size();
    unsigned int columns = g_board.at(0).size();

    // Aloitetaan annetusta arvosta
    //
    // Starting from the given value
    for(unsigned int i = start; i < rows * columns; ++i)
    {
        if(g_board.at(i / columns).at(i % columns).get_visibility() == EMPTY) // vaihdettu
        {
            return i;
        }
    }
    // Jatketaan alusta
    //
    // Continuing from the beginning
    for(unsigned int i = 0; i < start; ++i)
    {
        if(g_board.at(i / columns).at(i % columns).get_visibility() == EMPTY)
        {
            return i;
        }
    }
    // Tänne ei pitäisi koskaan päätyä
    //
    // You should never reach this
    std::cout << "No more empty spaces" << std::endl;
    return rows * columns - 1;
}

// Alustaa annetun pelilaudan (g_board) satunnaisesti arvotuilla korteilla
// annetun siemenarvon (seed) perusteella.
void init_with_cards(Game_board_type& g_board, int seed)
{
    // Selvitetään annetun pelilaudan rivien ja sarakkeiden määrät
    //
    // Finding out the number of rows and columns of the game board
    unsigned int rows = g_board.size();
    unsigned int columns = g_board.at(0).size();

    // Arvotaan täytettävä sijainti
    //
    // Drawing a cell to be filled
    std::default_random_engine randomEng(seed);
    std::uniform_int_distribution<int> distr(0, rows * columns - 1);
    // Hylätään ensimmäinen satunnaisluku (joka on aina jakauman alaraja)
    //
    // Wiping out the first random number (that is always the lower bound of the distribution)
    distr(randomEng);

    // Jos arvotussa sijainnissa on jo kortti, valitaan siitä seuraava tyhjä paikka.
    // (Seuraava tyhjä paikka haetaan kierteisesti funktion next_free avulla.)
    //
    // If the drawn cell is already filled with a card, next empty cell will be used.
    // (The next empty cell is searched for circularly, see function next_free.)
    for(unsigned int i = 0, c = 'A'; i < rows * columns - 1; i += 2, ++c)
    {
        // Lisätään kaksi samaa korttia (parit) pelilaudalle
        //
        // Adding two identical cards (pairs) in the game board
        for(unsigned int j = 0; j < 2; ++j)
        {
            unsigned int cell = distr(randomEng);
            cell = next_free(g_board, cell);
            g_board.at(cell / columns).at(cell % columns).set_letter(c);
            g_board.at(cell / columns).at(cell % columns).set_visibility(HIDDEN);
        }
    }
}

// Tulostaa annetusta merkistä c koostuvan rivin,
// jonka pituus annetaan parametrissa line_length.
// (Kutsutaan vain funktiosta print.)
void print_line_with_char(char c, unsigned int line_length)
{
    for(unsigned int i = 0; i < line_length * 2 + 7; ++i)
    {
        cout << c;
    }
    cout << endl;
}

// Tulostaa vaihtelevankokoisen pelilaudan reunuksineen.
void print(const Game_board_type& g_board)
{
    // Selvitetään annetun pelilaudan rivien ja sarakkeiden määrät
    //
    // Finding out the number of rows and columns of the game board
    unsigned int rows = g_board.size();
    unsigned int columns = g_board.at(0).size();

    print_line_with_char('=', columns);
    cout << "|   | ";
    for(unsigned int i = 0; i < columns; ++i)
    {
        cout << i + 1 << " ";
    }
    cout << "|" << endl;
    print_line_with_char('-', columns);
    for(unsigned int i = 0; i < rows; ++i)
    {
        cout << "| " << i + 1 << " | ";
        for(unsigned int j = 0; j < columns; ++j)
        {
            g_board.at(i).at(j).print();
            cout << " ";
        }
        cout << "|" << endl;
    }
    print_line_with_char('=', columns);
}

// Kysyy käyttäjältä tulon ja sellaiset tulon tekijät, jotka ovat
// mahdollisimman lähellä toisiaan. Palauttaa tulon (tätä hyödynnetään myöhemmin pelin lopettamiseen).
unsigned int ask_product_and_calculate_factors(unsigned int& smaller_factor, unsigned int& bigger_factor)
{
    unsigned int product = 0;
    while(not (product > 0 and product % 2 == 0))
    {
        cout << INPUT_AMOUNT_OF_CARDS;
        string product_str = "";
        getline(std::cin, product_str);
        product = stoi_with_check(product_str);
    }

    for(unsigned int i = 1; i * i <= product; ++i)
    {
        if(product % i == 0)
        {
            smaller_factor = i;
        }
    }
    bigger_factor = product / smaller_factor;
    return product;
}


// Kysyy pelaajien määrän ja luo pelaajat. Palauttaa vektorin, johon pelaajat on sijoitettu.
vector<Player> ask_and_create_players(){

    unsigned int amount_of_players = 0;
    while( amount_of_players <= 0 ){

        cout << INPUT_AMOUNT_OF_PLAYERS;
        string product_str = "";
        getline(cin, product_str);
        amount_of_players = stoi_with_check(product_str);
    }

    vector<Player> players = {};
    string player_name = "";
    cout << "List " << amount_of_players << " players: ";

    for (unsigned int i = 1; i <= amount_of_players; ++i){
        cin >> player_name;
        Player player = Player(player_name);
        players.push_back(player);
    }

    return players;
}

// funktio tarkistaa, ovatko annetut syötteet hyväksyttäviä.
// palauttaa false, jos koordinaatit ovat virheelliset.
bool are_coordinates_valid(vector<unsigned int> coordinates, unsigned int board_y,
                           unsigned int board_x, Game_board_type& g_board){

    if (coordinates.size() != 4){
        return false;
    }
    unsigned int y1 = coordinates.at(0);
    unsigned int x1 = coordinates.at(1);
    unsigned int y2 = coordinates.at(2);
    unsigned int x2 = coordinates.at(3);

    if (x1-1 > board_x or x2-1 > board_x or y1-1 > board_y or y2-1 > board_y){
        return false;
    }
    if (x1 == 0 or x2 == 0 or y1 == 0 or y2 == 0){
        return false;
    }
    if (g_board.at(x1-1).at(y1-1).get_visibility() != HIDDEN){
        return false;
    }
    if (g_board.at(x2-1).at(y2-1).get_visibility() != HIDDEN){
        return false;
    }
    if (x1 == x2 and y1 == y2){
        return false;
    }
    return true;
}

// funktio lukee käyttäjän syötteet ja palauttaa ne vektorina. Jos syöte on "q"
// palauttaa funktio tämän ja pääohjelma osaa lopettaa ohjelman.
vector<string> read_input(string player_name){

    vector<string> input_in_vector = {};
    string input = "";

    cout << player_name << ": " << INPUT_CARDS;
    for (int i=1; i<=4; ++i){
        cin >> input;

        // Jos input on q (quit), palauttaa funktio tämän kirjaimen jolloin main funktio
        // osaa lopettaa ohjelman.
        if (input == "q"){
            input_in_vector = {};
            input_in_vector.push_back(input);
            break;
        }
        input_in_vector.push_back(input);

    }
    return input_in_vector;
}

// funktio muuttaa vektorissa olevat syötteet merkkijonosta numeroiksi funktion stoi_with_check avulla
vector<unsigned int> string_to_int(vector<string> vector_as_string){

    vector<unsigned int> vector_as_int;
    for (auto coordinate : vector_as_string){
        unsigned int coordinate_as_int = stoi_with_check(coordinate);
        vector_as_int.push_back(coordinate_as_int);
    }
    return vector_as_int;
}
// kääntää kortin.
void turn_card(vector<unsigned int> coordinates, Game_board_type& g_board){

    unsigned int x1 = coordinates.at(0);
    unsigned int y1 = coordinates.at(1);
    unsigned int x2 = coordinates.at(2);
    unsigned int y2 = coordinates.at(3);

    g_board.at(y1-1).at(x1-1).set_visibility(OPEN);
    g_board.at(y2-1).at(x2-1).set_visibility(OPEN);
    return;
}
// tarkistaa onko käännetyt kortit parit, jos kortit eivät olleet parit, kääntää kortit takaisin
// ja palauttaa arvon false. Jos kortit olivat parit, poistaa kortit laudalta ja palauttaa arvon true
bool are_there_pairs(vector<unsigned int> coordinates, Game_board_type& g_board){

    unsigned int x1 = coordinates.at(0);
    unsigned int y1 = coordinates.at(1);
    unsigned int x2 = coordinates.at(2);
    unsigned int y2 = coordinates.at(3);

    if (g_board.at(y1-1).at(x1-1).get_letter() == g_board.at(y2-1).at(x2-1).get_letter()){
        g_board.at(y1-1).at(x1-1).set_visibility(EMPTY);
        g_board.at(y2-1).at(x2-1).set_visibility(EMPTY);
        return true;
    }
    else{
        g_board.at(y1-1).at(x1-1).set_visibility(HIDDEN);
        g_board.at(y2-1).at(x2-1).set_visibility(HIDDEN);
        return false;
    }
}
int main()
{
    Game_board_type game_board;

    unsigned int factor1 = 1;
    unsigned int factor2 = 1;
    unsigned int amount_of_cards = ask_product_and_calculate_factors(factor1, factor2);
    init_with_empties(game_board, factor1, factor2);

    string seed_str = "";
    std::cout << INPUT_SEED;
    std::getline(std::cin, seed_str);

    int seed = stoi_with_check(seed_str);
    init_with_cards(game_board, seed);

    vector<Player> players = ask_and_create_players();

    print(game_board);
    Player* in_turn = 0;
    unsigned long int index = 0;
    for (;;){
        in_turn = &players.at(index);
        string player_name = in_turn->get_name();

        auto coordinates_in_string = read_input(player_name);
        if (coordinates_in_string.size() == 1 and coordinates_in_string.at(0) == "q"){
            cout << GIVING_UP << endl;
            break;
        }
        vector<unsigned int> coordinates_in_int = string_to_int(coordinates_in_string);
        if (not are_coordinates_valid(coordinates_in_int, factor1, factor2, game_board)){
            cout << INVALID_CARD << endl;
            continue;
        }

        turn_card(coordinates_in_int, game_board);
        print(game_board);
        if (are_there_pairs(coordinates_in_int, game_board)){
              in_turn->add_card();
              cout << FOUND << endl;
        }
        else{
            ++index;
            cout << NOT_FOUND << endl;
            if ( index == players.size()){
                index = 0;
            }
        }
        for (auto player : players){
            player.print();
        }
        print(game_board);

        // lasketaan parien määrä kaikilla pelaajilla. Jos pareja on yhtä suuri määrä
        // kuin on kortteja, kun ne jaetaan luvulla 2, pelilaudan on oltava tyhjä
        // ja peli voidaan lopettaa.
        unsigned int total_pairs = 0;
        for (auto player : players){
            total_pairs += player.number_of_pairs();
        }
        if (total_pairs == (amount_of_cards/2)){
            cout << GAME_OVER << endl;

            // käydään läpi kaikki pelaajat ja sijoitetaan henkilöt,
            // joilla oli eniten pareja, vektoriin winners.
            unsigned int most_pairs = 0;
            vector<Player> winners = {};
            for (auto player : players){
                if (most_pairs < player.number_of_pairs()){
                    most_pairs = player.number_of_pairs();
                    winners.clear();
                    winners.push_back(player);
                    continue;
                }
                if (most_pairs == player.number_of_pairs()){
                    winners.push_back(player);
                    continue;
                }
            }

            // jos voittajia on yksi, tulostetaan pelaajan nimi, jos voittajia on useampia,
            // tulostetaan voittajien määrä ja heidän saamat parinsa.
            if (winners.size() > 1){
                cout << "Tie of " << winners.size() << " players with " << most_pairs << " pairs." << endl;
            }
            else{
                cout << winners.at(0).get_name() << " has won with " << most_pairs << " pairs." << endl;
            }
            break;
        }
    }


    return EXIT_SUCCESS;
}

