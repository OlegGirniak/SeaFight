#include <iostream>
#include <functional>
#include <string>
#include <algorithm>

#include "Game.h"
#include "SqlService.h"
#include "MainMenuChoice.h"

#include <cryptopp/sha.h>
#include <cryptopp/hex.h>



std::string sha256(std::string& input) 
{
    CryptoPP::SHA256 hash;
    std::string digest;

    CryptoPP::StringSource(input, true, new CryptoPP::HashFilter(hash, new CryptoPP::HexEncoder(new CryptoPP::StringSink(digest))));

    return digest;
}

Player& SignUp(std::vector<Player>& players)
{
    bool ifReservedPassword = false;

    std::string login;
    std::string password;


    do
    {
        std::cout << "enter login: ";
        std::cin >> login;

        std::cout << "enter password: ";
        std::cin >> password;
        password = sha256(password);

        for (auto& player : players)
        {
            if (player.password == password)
            {
                ifReservedPassword = true;
                break;
            }
        }

        if (ifReservedPassword)
        {
            system("cls");
            std::cout << "enter again\n";
        }

    } while (ifReservedPassword);


    Player newPlayer(login, password, 0);
    players.push_back(newPlayer);

    return players[players.size() - 1];
}

Player& SignIn(std::vector<Player>& players)
{

    std::string login;
    std::string password;

    while (true)
    {
        std::cout << "enter login: ";
        std::cin >> login;

        std::cout << "enter password: ";
        std::cin >> password;
        password = sha256(password);


        for (auto& player : players)
        {
            if (player.password == password && player.Name == login)
            {
                return player;
            }
        }

        system("cls");
        std::cout << "enter again\n";
    }
}



int main()
{
    SqlService sql;
    Player currentPlayer;

    std::vector<Player> players = sql.ReadFromDataBase();

    int mainMenuChoice = 0;

    while (mainMenuChoice < 1 || mainMenuChoice > 3)
    {
        std::cout << "1 - SignUp\n2 - SignIn\n3 - Show rating\n4 - Exit\n";
        std::cin >> mainMenuChoice;
    }
    
    MainMenuChoice playerChoice = MainMenuChoice(mainMenuChoice);

    switch (playerChoice)
    {
    case MainMenuChoice::SignUp:
        currentPlayer =  SignUp(players);
        break;
    case MainMenuChoice::SignIn:
        currentPlayer = SignIn(players);
        break;
    case MainMenuChoice::ShowRating:
    {
        std::vector<Player> sortedPlayers = players;
        std::sort(sortedPlayers.begin(), sortedPlayers.end(), std::greater<>());

        int i = 1;
        for (auto& player : sortedPlayers)
        {
            std::cout << i++ << " - " << player.Name << " has " << player.countWins << " wins\n";
        }
    }
    break;

    case MainMenuChoice::Exit:
        return 0;
        break;
    default:
        break;
    }

    Bot bot("Bot andriy");
    Game game(currentPlayer, bot);

    game.StartGame();

    switch (playerChoice)
    {
    case MainMenuChoice::SignUp:
        sql.WriteInDataBase(currentPlayer);
        break;
    case MainMenuChoice::SignIn:
        sql.UpdatePlayerData(currentPlayer);
        break;
    default:
        break;
    }
}
