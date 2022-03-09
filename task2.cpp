#include <iostream>
#include <fstream>
#include <cstring>
using std::cin;
using std::cout;
using std::endl;

const int MAX_SIZE = 10;

enum Game
{
    dummy = 0,
    CSGO,
    LOL,
    Dota,
    Valorant,
    Overwatch
};

struct Player
{
    char name [64];
    char team [32];
    Game game;
    int wins;
    int losses;
    double ratioWL;

    void createPlayer()
    {
        cout << "Enter name: ";
        cin.getline(name,32);
        cout << "Enter team: ";
        cin.getline(team,32);
        int userInput;
        cout << "Choose Game:" << "\n1.CS:GO" << "\n2.LOL" << "\n3.Dota" << "\n4.Valorant" << "\n5.Overwatch" << endl;
        cin >> userInput;
        game = (Game)(userInput);
        cout << "Wins: ";
        cin >> wins;
        while(wins < 0)
        {
            cout << "Wins must be a non-negative!" << "/nWins: ";
            cin >> wins;
        }
        cout << "Losses: ";
        cin >> losses;
        while(losses < 0)
        {
            cout << "Losses must be a non-negative!" << "/nLosses: ";
            cin >> losses;
        }
        cout << "Win to Loss ration is calculated automatically!" << endl;
        ratioWL = (double)wins/(double)losses;
        cin.ignore();
    }

    void printPlayer()
    {
        cout << "Player name: " << name << endl;
        cout << "Player team: " << team << endl;
        cout << "Player game: " << game << endl;
        cout << "Wins: " << wins << endl;
        cout << "Losses: " << losses << endl;
        cout << "W/L ratio: " << ratioWL << endl;
    }

};

const char* enumToStr(int game)
{
    switch (game)
    {
    case 1: return "CSGO";
    case 2: return "LOL";
    case 3: return "Dota";
    case 4: return "Valorant";
    case 5: return "Overwatch";
    default: return "Invalid value!";
    }
}

void writePlayer(Player player, std::ofstream& out)
{
    out << "Player name: " << player.name << '\n';
    out << "Player team: " << player.team << '\n';
    out << "Player game: " << player.game << '\n';
    out << "Wins: " << player.wins << '\n';
    out << "Losses: " << player.losses << '\n';
    out << "W/L ratio: " << player.ratioWL << '\n';
    out << "______________________________________" << '\n';
}

void writeClassPlayer(Player player[], int size, std::ofstream& out)
{
    for (int i = 0; i < size; i++)
    {
    out << "Player name: " << player[i].name << '\n';
        out << "Player team: " << player[i].team << '\n';
        out << "Player game: " << enumToStr(player[i].game) << '\n';
        out << "Wins: " << player[i].wins << '\n';
        out << "Losses: " << player[i].losses << '\n';
        out << "W/L ratio: " << player[i].ratioWL << '\n';
        out << "______________________________________" << '\n';
    }
}

int main()
{
    // Player p;
    // p.createPlayer();
    // cout << endl << "Player List:" << endl;
    // p.printPlayer();

    std::ofstream out;
    out.open("player.txt");
    out << "Player List: " << '\n';
    // writePlayer(p, out);
    

    Player players [MAX_SIZE];
    int size;
    cout << "How many players would you like to add(MAX 10): ";
    cin >> size;
    cin.ignore();

    for(int i = 0; i < size; i++)
    {
        players[i].createPlayer();
    }

    for(int i = 0; i < size; i++)
    {
        players[i].printPlayer();
    }

    if(size != 0) writeClassPlayer(players, size, out);

    out.close();

    return 0;
}