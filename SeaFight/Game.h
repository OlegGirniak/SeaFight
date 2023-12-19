#pragma once
#include "Player.h"
#include "Bot.h"
#include "PlayerMenu.h"

struct Game
{
	Player& player;
	Bot& bot;

	Game(Player& player, Bot& bot) : player(player), bot(bot) { }

    void StartGame()
    {
        PLayerMenu playerMenu;

        std::cout << "Paste ships:\n"
            << "1 - By yourself.\n"
            << "2 - Randomly.\n";

        int intPlayerMenu;
        std::cin >> intPlayerMenu;
        playerMenu = PLayerMenu(intPlayerMenu);

        switch (playerMenu)
        {
        case PLayerMenu::ByYourSelf:
        {
            player.field.ArrangementOfShips(player.PlayerShips);
        }
        break;
        case PLayerMenu::Randomly:
        {
            player.field.ArrangementOfShipsRandomly(player.PlayerShips);
        }
        break;
        default:
            std::cout << "Error\n";
            break;
        }

        bot.field.ArrangementOfShipsRandomly(bot.botShips);

        bool res = false;
        int cordX = 0, cordY = 0;
        int tempX = 0, tempY = 0;
        int firstCordX = 0, firstCordY = 0;
        int max = 0, min = INT_MAX;
        bool doBotHitShip = false;
        bool step = true;
        bool gameEnd = false;
        std::vector<Point> botPoints;
        std::vector<Point> playerPoints;
        std::vector<Point> tempBotPoints;
        std::vector<Point> tempPLayerPoints;

        player.EnemyField.Show();
        player.field.Show();


        do
        {
            std::cout << step ? "Player enetr cordX and cordY: " : "Bot is making a choice...\n";

            do
            {
                do
                {
                    if (step)
                    {
                        std::cout << player.Name << " - Enter cordX: ";
                        std::cin >> cordX;

                        std::cout << player.Name << " - Enter cordY: ";
                        std::cin >> cordY;

                       
                    }
                    else
                    {

                        if (doBotHitShip && botPoints.size() < 2)
                        {
                            // problem ?
                            do
                            {
                                cordX = std::rand() % (tempX + 2 - (tempX - 1)) + (tempX - 1);
                                cordY = std::rand() % (tempY + 2 - (tempY - 1)) + (tempY - 1);

                            } while (tempX == cordX && tempY == cordY ||
                                cordX == tempX + 1 && cordY == tempY + 1 || cordX == tempX + 1 && cordY == tempY - 1 ||
                                cordX == tempX - 1 && cordY == tempY + 1 || cordX == tempX - 1 && cordY == tempY - 1);
                        }

                        else if (botPoints.size() >= 2)
                        {
                            max = 0; min = INT_MAX;

                            if (DoCorXSame(botPoints))
                            {
                                for (int i = 0; i < botPoints.size(); i++)
                                {
                                    if (botPoints[i].y > max) max = botPoints[i].y;
                                    if (botPoints[i].y < min) min = botPoints[i].y;
                                }
                                max++;
                                min--;
                                cordX = firstCordX;
                                cordY = rand() % (max - min + 1) + min;
                            }
                            else
                            {
                                for (int i = 0; i < botPoints.size(); i++)
                                {
                                    if (botPoints[i].x > max) max = botPoints[i].x;
                                    if (botPoints[i].x < min) min = botPoints[i].x;
                                }
                                max++;
                                min--;
                                cordX = std::rand() % (max + 1 - min) + min;
                                cordY = firstCordY;
                            }
                        }

                        else
                        {
                            cordX = std::rand() % 10 + 1;
                            cordY = std::rand() % 10 + 1;
                        }
                    }

                } while ((cordX < 1 || cordX >= 12) || (cordY < 1 || cordY >= 12));

            } while (step ? player.EnemyField.ArrayField[cordX][cordY].Sign != CellType::Empty : bot.EnemyField.ArrayField[cordX][cordY].Sign != CellType::Empty);
            if (step)
            {
                if (bot.field.DoesMissed(cordX, cordY))
                {
                    player.EnemyField.ArrayField[cordX][cordY].Sign = CellType::Missed;
                    bot.field.ArrayField[cordX][cordY].Sign = CellType::Missed;
                    step = !step;
                }
                else if (bot.field.ArrayField[cordX][cordY].Sign == CellType::Ship)
                {
                    player.EnemyField.ArrayField[cordX][cordY].Sign = CellType::DamagedPartOfShip;
                    bot.field.ArrayField[cordX][cordY].Sign = CellType::DamagedPartOfShip;
                    Point point(cordX, cordY);
                    playerPoints.push_back(point);

                    if (DoBotShipIsDestroyed(playerPoints, tempPLayerPoints))
                    {
                        DestroyBotShip(tempPLayerPoints);
                    }
                }
            }
            else if (!step)
            {
                if (player.field.DoesMissed(cordX, cordY))
                {
                    bot.EnemyField.ArrayField[cordX][cordY].Sign = CellType::Missed;
                    player.field.ArrayField[cordX][cordY].Sign = CellType::Missed;
                    step = !step;
                }
                else if (player.field.ArrayField[cordX][cordY].Sign == CellType::Ship)
                {
                    bot.EnemyField.ArrayField[cordX][cordY].Sign = CellType::DamagedPartOfShip;
                    player.field.ArrayField[cordX][cordY].Sign = CellType::DamagedPartOfShip;
                    Point point(cordX, cordY);
                    tempX = cordX;
                    tempY = cordY;
                    botPoints.push_back(point);
                    if (botPoints.size() == 1)
                    {
                        firstCordX = cordX;
                        firstCordY = cordY;
                    }
                    doBotHitShip = true;

                    if (DoPlayerShipIsDestroyed(botPoints, tempBotPoints))
                    {
                        DestroyPlayerShip(tempBotPoints);
                        doBotHitShip = false;
                        firstCordX = 0;
                        firstCordY = 0;
                    }
                }
            }
            system("cls");
            player.EnemyField.Show();
            player.field.Show();

            if (step)
            {
                if (bot.field.CheckingVictory())
                {
                    gameEnd = true;
                    std::cout << player.Name << " won this battle\n";
                    player.countWins++;
                }
            }
            else if (!step)
            {
                if (player.field.CheckingVictory())
                {
                    gameEnd = true;
                    std::cout << bot.Name << " won this battle\n";
                    bot.field.Show();
                }
            }


        } while (!gameEnd);


        player.field.ClearField();
        player.EnemyField.ClearField();
        bot.field.ClearField();
        bot.EnemyField.ClearField();
    }



    std::vector<Point> AddPoint(std::vector<Point> points, Point point)
    {
        std::vector<Point> Array(points.size() - 1);
        for (int i = 0; i < points.size(); i++)
        {
            Array[i] = points[i];
        }
        Array[Array.size() - 1] = point;
        points = Array;
        return points;
    }

    std::vector<Point> DeletePoint(std::vector<Point> points, Point point)
    {
        std::vector<Point> Array(points.size() - 1);
        for (int i = 0, j = 0; i < points.size(); i++)
        {
            if (points[i] != point) //points[i] != point
            {
                Array[j] = points[i];
                j++;
            }
        }
        return Array;
    }

    std::vector<Point> CopyArrayOfPoints(std::vector<Point> points)
    {
        std::vector<Point> Array(points.size());
        for (int i = 0; i < Array.size(); i++)
        {
            Array[i] = points[i];
        }
        return Array;
    }

    bool DoBotShipIsDestroyed(std::vector<Point>& points, std::vector<Point>& tempPlayerPoints)
    {

        for (int i = 0; i < bot.botShips.size(); i++)
        {
            for (int j = 0; j < bot.botShips[i].Coordinates.size(); j++)
            {
                if (bot.botShips[i].Coordinates[j].x == points[points.size() - 1].x && bot.botShips[i].Coordinates[j].y == points[points.size() - 1].y)
                {
                    std::vector<Point> Array = CopyArrayOfPoints(points);
                    tempPlayerPoints = CopyArrayOfPoints(bot.botShips[i].Coordinates);

                    for (j = 0; j < bot.botShips[i].Coordinates.size(); j++)
                    {
                        for (int k = 0; k < points.size(); k++)
                        {
                            if (bot.botShips[i].Coordinates[j].x == points[k].x && bot.botShips[i].Coordinates[j].y == points[k].y)
                            {
                                tempPlayerPoints = DeletePoint(tempPlayerPoints, points[k]);
                                points = DeletePoint(points, points[k]);
                            }
                        }
                    }
                    if (tempPlayerPoints.size() == 0)
                    {
                        tempPlayerPoints = CopyArrayOfPoints(bot.botShips[i].Coordinates);
                        return true;
                    }
                    tempPlayerPoints.clear();
                    tempPlayerPoints.shrink_to_fit();
                    points = CopyArrayOfPoints(Array);
                    return false;
                }
            }
        }
        return false;
    }

    bool DoPlayerShipIsDestroyed(std::vector<Point>& points, std::vector<Point>& tempBotPoints)
    {
        for (int i = 0; i < player.PlayerShips.size(); i++)
        {
            for (int j = 0; j < player.PlayerShips[i].Coordinates.size(); j++)
            {
                if (player.PlayerShips[i].Coordinates[j].x == points[points.size() - 1].x && player.PlayerShips[i].Coordinates[j].y == points[points.size() - 1].y)
                {
                    std::vector<Point> Array = CopyArrayOfPoints(points);
                    tempBotPoints = CopyArrayOfPoints(player.PlayerShips[i].Coordinates);
                    for (j = 0; j < player.PlayerShips[i].Coordinates.size(); j++)
                    {
                        for (int k = 0; k < points.size(); k++)
                        {
                            if (player.PlayerShips[i].Coordinates[j].x == points[k].x && player.PlayerShips[i].Coordinates[j].y == points[k].y)
                            {
                                tempBotPoints = DeletePoint(tempBotPoints, points[k]);
                                points = DeletePoint(points, points[k]);
                            }
                        }
                    }
                    if (tempBotPoints.size() == 0)
                    {
                        tempBotPoints = CopyArrayOfPoints(player.PlayerShips[i].Coordinates);
                        return true;
                    }
                    tempBotPoints.clear();
                    tempBotPoints.shrink_to_fit();
                    points = CopyArrayOfPoints(Array);
                    return false;
                }
            }
        }
        return false;
    }

    void DestroyPlayerShip(std::vector<Point>& botPoints)
    {
        for (int i = 0; i < botPoints.size(); i++)
        {
            player.field.ArrayField[botPoints[i].x][botPoints[i].y].Sign = CellType::SunkenShip;
            bot.EnemyField.ArrayField[botPoints[i].x][botPoints[i].y].Sign = CellType::SunkenShip;
        }
        MissedAroundSunkenShipPlayerField(botPoints);
    }

    void DestroyBotShip(std::vector<Point>& playerPoints)
    {
        for (int i = 0; i < playerPoints.size(); i++)
        {
            bot.field.ArrayField[playerPoints[i].x][playerPoints[i].y].Sign = CellType::SunkenShip;
            player.EnemyField.ArrayField[playerPoints[i].x][playerPoints[i].y].Sign = CellType::SunkenShip;
        }
        MissedAroundSunkenShipBotField(playerPoints);
    }

    void MissedAroundSunkenShipPlayerField(std::vector<Point>& points)
    {
        for (int i = 0; i < points.size(); i++)
        {
            if (player.field.ArrayField[points[i].x + 1][points[i].y].Sign == CellType::Empty)
            {
                player.field.ArrayField[points[i].x + 1][points[i].y].Sign = CellType::Missed;
                bot.EnemyField.ArrayField[points[i].x + 1][points[i].y].Sign = CellType::Missed;
            }
            if (player.field.ArrayField[points[i].x - 1][points[i].y].Sign == CellType::Empty)
            {
                player.field.ArrayField[points[i].x - 1][points[i].y].Sign = CellType::Missed;
                bot.EnemyField.ArrayField[points[i].x - 1][points[i].y].Sign = CellType::Missed;
            }
            if (player.field.ArrayField[points[i].x][points[i].y + 1].Sign == CellType::Empty)
            {
                player.field.ArrayField[points[i].x][points[i].y + 1].Sign = CellType::Missed;
                bot.EnemyField.ArrayField[points[i].x][points[i].y + 1].Sign = CellType::Missed;
            }

            if (player.field.ArrayField[points[i].x][points[i].y - 1].Sign == CellType::Empty)
            {
                player.field.ArrayField[points[i].x][points[i].y - 1].Sign = CellType::Missed;
                bot.EnemyField.ArrayField[points[i].x][points[i].y - 1].Sign = CellType::Missed;
            }

            if (player.field.ArrayField[points[i].x + 1][points[i].y + 1].Sign == CellType::Empty)
            {
                player.field.ArrayField[points[i].x + 1][points[i].y + 1].Sign = CellType::Missed;
                bot.EnemyField.ArrayField[points[i].x + 1][points[i].y + 1].Sign = CellType::Missed;
            }

            if (player.field.ArrayField[points[i].x + 1][points[i].y - 1].Sign == CellType::Empty)
            {
                player.field.ArrayField[points[i].x + 1][points[i].y - 1].Sign = CellType::Missed;
                bot.EnemyField.ArrayField[points[i].x + 1][points[i].y - 1].Sign = CellType::Missed;
            }

            if (player.field.ArrayField[points[i].x - 1][points[i].y + 1].Sign == CellType::Empty)
            {
                player.field.ArrayField[points[i].x - 1][points[i].y + 1].Sign = CellType::Missed;
                bot.EnemyField.ArrayField[points[i].x - 1][points[i].y + 1].Sign = CellType::Missed;
            }

            if (player.field.ArrayField[points[i].x - 1][points[i].y - 1].Sign == CellType::Empty)
            {
                player.field.ArrayField[points[i].x - 1][points[i].y - 1].Sign = CellType::Missed;
                bot.EnemyField.ArrayField[points[i].x - 1][points[i].y - 1].Sign = CellType::Missed;
            }
        }
    }

    void MissedAroundSunkenShipBotField(std::vector<Point>& points)
    {
        for (int i = 0; i < points.size(); i++)
        {
            if (bot.field.ArrayField[points[i].x + 1][points[i].y].Sign == CellType::Empty)
            {
                bot.field.ArrayField[points[i].x + 1][points[i].y].Sign = CellType::Missed;
                player.EnemyField.ArrayField[points[i].x + 1][points[i].y].Sign = CellType::Missed;
            }
            if (bot.field.ArrayField[points[i].x - 1][points[i].y].Sign == CellType::Empty)
            {
                bot.field.ArrayField[points[i].x - 1][points[i].y].Sign = CellType::Missed;
                player.EnemyField.ArrayField[points[i].x - 1][points[i].y].Sign = CellType::Missed;
            }
            if (bot.field.ArrayField[points[i].x][points[i].y + 1].Sign == CellType::Empty)
            {
                bot.field.ArrayField[points[i].x][points[i].y + 1].Sign = CellType::Missed;
                player.EnemyField.ArrayField[points[i].x][points[i].y + 1].Sign = CellType::Missed;
            }

            if (bot.field.ArrayField[points[i].x][points[i].y - 1].Sign == CellType::Empty)
            {
                bot.field.ArrayField[points[i].x][points[i].y - 1].Sign = CellType::Missed;
                player.EnemyField.ArrayField[points[i].x][points[i].y - 1].Sign = CellType::Missed;
            }

            if (bot.field.ArrayField[points[i].x + 1][points[i].y + 1].Sign == CellType::Empty)
            {
                bot.field.ArrayField[points[i].x + 1][points[i].y + 1].Sign = CellType::Missed;
                player.EnemyField.ArrayField[points[i].x + 1][points[i].y + 1].Sign = CellType::Missed;
            }

            if (bot.field.ArrayField[points[i].x + 1][points[i].y - 1].Sign == CellType::Empty)
            {
                bot.field.ArrayField[points[i].x + 1][points[i].y - 1].Sign = CellType::Missed;
                player.EnemyField.ArrayField[points[i].x + 1][points[i].y - 1].Sign = CellType::Missed;
            }

            if (bot.field.ArrayField[points[i].x - 1][points[i].y + 1].Sign == CellType::Empty)
            {
                bot.field.ArrayField[points[i].x - 1][points[i].y + 1].Sign = CellType::Missed;
                player.EnemyField.ArrayField[points[i].x - 1][points[i].y + 1].Sign = CellType::Missed;
            }

            if (bot.field.ArrayField[points[i].x - 1][points[i].y - 1].Sign == CellType::Empty)
            {
                bot.field.ArrayField[points[i].x - 1][points[i].y - 1].Sign = CellType::Missed;
                player.EnemyField.ArrayField[points[i].x - 1][points[i].y - 1].Sign = CellType::Missed;
            }
        }

    }

    bool DoCorXSame(std::vector<Point> botBoints)
    {
        bool doesTrue = true;
        for (int i = 1; i < botBoints.size(); i++)
        {
            if (botBoints[0].x != botBoints[i].x)
            {
                doesTrue = false;
            }
        }
        return doesTrue;
    }
};