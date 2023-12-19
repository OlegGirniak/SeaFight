#pragma once
#include <vector>
#include <mysql_driver.h>
#include <mysql_connection.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include "Player.h"


class SqlService
{
	sql::mysql::MySQL_Driver* driver;
	sql::Connection* con;
	sql::Statement* stmt;
	sql::ResultSet* res;

public:

	SqlService()
	{
		driver = sql::mysql::get_mysql_driver_instance();
		con = driver->connect("tcp://127.0.0.1:3306", "root", "1234");
		con->setSchema("players");
		stmt = con->createStatement();
		res = nullptr;
	}

	~SqlService()
	{
		delete res;
		delete stmt;
		delete con;
	}

	std::vector<Player> ReadFromDataBase()
	{
		std::vector<Player> players;

		res = stmt->executeQuery("SELECT * FROM players");

		while (res->next()) 
		{
			std::string playerName = res->getString("name");
			std::string playerPassword = res->getString("password");
			int playerWins = res->getInt("countWins");

			Player player(playerName, playerPassword, playerWins);
			players.push_back(player);
		}

		for (const auto& player : players) 
		{
			std::cout << "Player Name: " << player.Name << ", ";
			std::cout << "Password: " << player.password << ", ";
			std::cout << "Wins: " << player.countWins << std::endl;
		}

		return players;
	}

	void WriteInDataBase(Player& player)
	{
		sql::Statement* stmt = con->createStatement();

		std::string query = "INSERT INTO players (name, password, countWins) VALUES ('" +player.Name + "', '" + player.password + "', " + std::to_string(player.countWins) + ")";
		stmt->executeUpdate(query);
	}

	void UpdatePlayerData(Player& player)
	{
		sql::Statement* stmt = con->createStatement();

		std::string query = "UPDATE players SET countWins = " + std::to_string(player.countWins) + " WHERE password = '" + player.password + "'";
		stmt->executeUpdate(query);

		
	}
};