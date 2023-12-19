#pragma once
#include <vector>
#include <iostream>
#include "Cell.h"
#include "CellType.h"
#include "Ship.h"
#include "TypeOfShip.h"
#include "DirectionOfShip.h"

struct Field
{
	Cell ArrayField[12][12];

    Field()
    {
        for (int i = 0; i < 12; i++)
        {
            for (int j = 0; j < 12; j++)
            {

                if (j == 0 || j == 11)
                    ArrayField[i][j] = CellType::Boarder;

                else if (i == 0 || i == 11)
                    ArrayField[i][j] = CellType::Boarder;

                else ArrayField[i][j] = CellType::Empty;
            }
        }
    }

    void ArrangementOfShips(std::vector<Ship> playerShips)
    {
        int oneDeckShips = 4;
        int twoDecksShips = 3;
        int threeDecksShips = 2;
        int fourDecksShips = 1;
        TypeOfShip typeOfShip;
        DirectionOfShip directionOfShip;

        while (oneDeckShips != 0 || twoDecksShips != 0 || threeDecksShips != 0 || fourDecksShips != 0)
        {
            std::cout << "You have:\n"
                << "1 - Ship with ONE deck - " << oneDeckShips << ".\n"
                << "2 - Ship with TWO decks - " << twoDecksShips << ".\n"
                << "3 - Ship with THREE decks - " << threeDecksShips << ".\n"
                << "4 - Ship with FOUR decks - " << fourDecksShips << ".\n";

            int intTypeOfShip;

            std::cin >> intTypeOfShip;

            typeOfShip = static_cast<TypeOfShip>(intTypeOfShip);

            if (true)
            {
                if (typeOfShip == TypeOfShip::OneDeck && oneDeckShips != 0 ||
                    typeOfShip == TypeOfShip::TwoDecks && twoDecksShips != 0 ||
                    typeOfShip == TypeOfShip::ThreeDecks && threeDecksShips != 0 ||
                    typeOfShip == TypeOfShip::FourDecks && fourDecksShips != 0)
                {
                    system("cls");
                    std::cout << "Enter X:";
                    int cordX;
                    std::cin >> cordX;

                    while (cordX < 1 || cordX > 12 - 1)
                    {
                        std::cout << "Enter X:";
                        std::cin >> cordX;
                    }

                    std::cout << "Enter Y:";
                    int cordY;
                    std::cin >> cordY;

                    while (cordY < 1 || cordY > 12 - 1)
                    {
                        std::cout << "Enter Y:";
                        int cordY;
                        std::cin >> cordY;
                    }

                    if (DoEmpty(cordX, cordY) && DoEmptyAroundFirstCordiantes(cordX, cordY))
                    {
                        if (typeOfShip != TypeOfShip::OneDeck)
                        {
                            Ship ship;
                            std::cout << "Choose a direction:\n"
                                << "1 - Up.\n"
                                << "2 - Down.\n"
                                << "3 - Right.\n"
                                << "4 - Left.\n";

                            std::cout << "Enter Direction of ship: ";
                            int intDirectionShip;
                            std::cin >> intDirectionShip;
                            directionOfShip = static_cast<DirectionOfShip>(intDirectionShip);

                        }

                        switch (typeOfShip)
                        {
                        case TypeOfShip::OneDeck:
                        {
                            if (oneDeckShips > 0)
                            {
                                if (DoesShipIsInputed(cordX, cordY, DirectionOfShip::Up, typeOfShip, playerShips))
                                {
                                    oneDeckShips--;
                                    Show();
                                }
                                else std::cout << "Error\n";
                            }

                        }
                        break;
                        case TypeOfShip::TwoDecks:
                        {
                            if (twoDecksShips > 0)
                            {
                                if (DoesShipIsInputed(cordX, cordY, directionOfShip, typeOfShip, playerShips))
                                {
                                    twoDecksShips--;
                                    Show();
                                }
                                else std::cout << "Error\n";
                            }
                        }
                        break;
                        case TypeOfShip::ThreeDecks:
                        {
                            if (threeDecksShips > 0)
                            {
                                if (DoesShipIsInputed(cordX, cordY, directionOfShip, typeOfShip, playerShips))
                                {
                                    threeDecksShips--;
                                    Show();
                                }
                                else std::cout << "Error\n";
                            }

                        }
                        break;
                        case TypeOfShip::FourDecks:
                        {
                            if (fourDecksShips > 0)
                            {
                                if (DoesShipIsInputed(cordX, cordY, directionOfShip, typeOfShip, playerShips))
                                {
                                    fourDecksShips--;

                                    Show();
                                }
                                else std::cout << "Error\n";
                            }

                        }
                        break;
                        default:
                            std::cout << "Error\n";
                            break;
                        }
                    }
                    else std::cout << "Error\n";
                }

            }
            else std::cout << "Error\n";
        }
    }

    void ArrangementOfShipsRandomly(std::vector<Ship>& ships)
    {
        srand(time(nullptr));

        int oneDeckShips = 4;
        int twoDecksShips = 3;
        int threeDecksShips = 2;
        int fourDecksShips = 1;
        TypeOfShip typeOfShip;
        DirectionOfShip directionOfShip;

        while (oneDeckShips != 0 || twoDecksShips != 0 || threeDecksShips != 0 || fourDecksShips != 0)
        {


            typeOfShip = static_cast<TypeOfShip>(std::rand() % 4 + 1);

            int cordX = std::rand() % 10 + 1;

            int cordY = std::rand() % 10 + 1;

            if (DoEmpty(cordX, cordY) && DoEmptyAroundFirstCordiantes(cordX, cordY))
            {
                Ship ship;


                directionOfShip = static_cast<DirectionOfShip>(std::rand() % 4 + 1);

                switch (typeOfShip)
                {

                case TypeOfShip::OneDeck:
                {
                    if (oneDeckShips > 0)
                    {
                        if (DoesShipIsInputed(cordX, cordY, directionOfShip, typeOfShip, ships)) oneDeckShips--;
                    }
                }
                break;

                case TypeOfShip::TwoDecks:
                {
                    if (twoDecksShips > 0)
                    {
                        if (DoesShipIsInputed(cordX, cordY, directionOfShip, typeOfShip, ships)) twoDecksShips--;
                    }
                }
                break;


                case TypeOfShip::ThreeDecks:
                {
                    if (threeDecksShips > 0)
                    {
                        if (DoesShipIsInputed(cordX, cordY, directionOfShip, typeOfShip, ships)) threeDecksShips--;
                    }
                }
                break;

                case TypeOfShip::FourDecks:
                {
                    if (fourDecksShips > 0)
                    {
                        if (DoesShipIsInputed(cordX, cordY, directionOfShip, typeOfShip, ships)) fourDecksShips--;
                    }

                }
                break;
                }
            }
        }
    }

    Ship CreateShips(int cordX, int cordY, DirectionOfShip direction, TypeOfShip typeOfShip)
    {
        std::vector<Point> coordinates((int)typeOfShip);
        Ship newShip(coordinates);

        switch (direction)
        {
        case DirectionOfShip::Up:
        {
            for (int i = 0; i < newShip.Coordinates.size(); i++)
            {
                newShip.Coordinates[i] = Point(cordX, cordY);
                cordX--;
            }
        }
        break;
        case DirectionOfShip::Down:
        {
            for (int i = 0; i < newShip.Coordinates.size(); i++)
            {
                newShip.Coordinates[i] = Point(cordX, cordY);
                cordX++;
            }
        }
        break;
        case DirectionOfShip::Right:
        {
            for (int i = 0; i < newShip.Coordinates.size(); i++)
            {
                newShip.Coordinates[i] = Point(cordX, cordY);
                cordY++;
            }
        }
        break;
        case DirectionOfShip::Left:
        {
            for (int i = 0; i < newShip.Coordinates.size(); i++)
            {
                newShip.Coordinates[i] = Point(cordX, cordY);
                cordY--;
            }
        }
        break;
        default:
            std::cout << "Error choice\n";
            break;
        }
        return newShip;
    }

    bool DoesShipIsInputed(int cordX, int cordY, DirectionOfShip direction, TypeOfShip typeOfShip, std::vector<Ship>& arrayofShips)
    {
        Ship ship;
        ship = CreateShips(cordX, cordY, direction, typeOfShip);

        if (DoesItPossibleToInputShip(ship))
        {
            arrayofShips = AddShip(ship, arrayofShips);
            InputShip(ship);
            return true;
        }
        return false;
    }

    std::vector<Ship>& AddShip(Ship& ship, std::vector<Ship>& ships)
    {
        ships.push_back(ship);

        return ships;
    }

    void ClearField()
    {
        for (int i = 0; i < 12; i++)
        {
            for (int j = 0; j < 12; j++)
            {
                if (j == 0)
                {
                    ArrayField[i][0].Sign = CellType::Boarder;
                }
                else if (j == 11)
                {
                    ArrayField[i][11].Sign = CellType::Boarder;
                }
                else if (i == 0 || i == 11)
                {
                    ArrayField[i][j].Sign = CellType::Boarder;
                }
                else ArrayField[i][j].Sign = CellType::Empty;
            }
        }
    }

    void Show()
    {
        std::cout << "     ";
        for (size_t i = 1; i < 12 - 1; i++)
        {
            std::cout << i << " ";
        }
        std::cout << std::endl;

        for (size_t i = 0; i < 12; i++)
        {
            if (i == 0 || i == 11)
            {
                std::cout << "   ";
            }
            if (i > 0 && i < 10)
            {
                std::cout << " " << i << " ";
            }
            if (i == 10)
            {
                std::cout << i << " ";
            }

            for (size_t j = 0; j < 12; j++)
            {
                switch (ArrayField[i][j].Sign)
                {
                case CellType::Boarder:
                {
                    std::cout << "# ";
                }
                break;

                case CellType::Empty:
                {
                    std::cout << "  ";
                }
                break;

                case CellType::Ship:
                {
                    std::cout << "O ";
                }
                break;

                case CellType::DamagedPartOfShip:
                {
                    std::cout << "@ ";
                }
                break;

                case CellType::SunkenShip:
                {
                    std::cout << "X ";
                }
                break;

                case CellType::Missed:
                {
                    std::cout << ": ";
                }
                break;

                }
            }
            std::cout << std::endl;
        }
    }

    bool DoEmpty(int cordX, int cordY)
    {
        for (int i = 0; i < 12; i++)
        {
            for (int j = 0; j < 12; j++)
            {
                if (i == cordX && j == cordY && ArrayField[i][j].Sign == CellType::Empty) return true;
            }
        }
        return false;
    }

    bool DoEmptyAroundFirstCordiantes(int cordX, int cordY)
    {
        if (ArrayField[cordX][cordY - 1].Sign != CellType::Ship && ArrayField[cordX][cordY + 1].Sign != CellType::Ship &&
            ArrayField[cordX - 1][cordY].Sign != CellType::Ship && ArrayField[cordX + 1][cordY].Sign != CellType::Ship &&
            ArrayField[cordX - 1][cordY - 1].Sign != CellType::Ship && ArrayField[cordX - 1][cordY + 1].Sign != CellType::Ship &&
            ArrayField[cordX + 1][cordY - 1].Sign != CellType::Ship && ArrayField[cordX + 1][cordY + 1].Sign != CellType::Ship)
        {
            return true;
        }
        return false;
    }

    bool DoesItPossibleToInputShip(Ship& ship)
    {

        for (int i = 0; i < ship.Coordinates.size(); i++)
        {
            if (ArrayField[ship.Coordinates[i].x][ship.Coordinates[i].y].Sign != CellType::Empty || !DoEmptyAroundFirstCordiantes(ship.Coordinates[i].x, ship.Coordinates[i].y))
            {
                return false;
            }
        }
        return true;
    }

    void InputShip(Ship& ship)
    {
        for (int i = 0; i < ship.Coordinates.size(); i++)
        {
            if (ArrayField[ship.Coordinates[i].x][ship.Coordinates[i].y].Sign == CellType::Empty)
            {
                ArrayField[ship.Coordinates[i].x][ship.Coordinates[i].y].Sign = CellType::Ship;
            }
        }
    }

    bool DoesMissed(int cordX, int cordY)
    {
        if (ArrayField[cordX][cordY].Sign == CellType::Empty)
        {
            return true;
        }
        return false;
    }

    bool CheckingVictory()
    {
        for (int i = 0; i < 12; i++)
        {
            for (int j = 0; j < 12; j++)
            {
                if (ArrayField[i][j].Sign == CellType::Ship)
                {
                    return false;
                }
            }
        }
        return true;
    }
};