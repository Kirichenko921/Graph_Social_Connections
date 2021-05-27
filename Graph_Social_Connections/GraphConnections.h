#pragma once
#include <iostream>
#include <vector>
#define SIZE 20  // возможное количество пользователей, по желанию, можно увеличить. Ну или уменьшить 
class Graph
{
public:
	Graph();
	void addUser(std::string user);// добавление пользователя
	void addConnection(const std::string user1, const std::string user2, const int connection);// добавление связи
	void searchThreeHandshakes(); // поиск пар знакомств через три рукопожатия  
	~Graph()
	{}

private:
	// поиск минимального расстояния между двумя вершинами внутренння функция
	void searchThreeHandshakesInner(std::vector<bool> visited, int indexTo, int countHandshakes, std::vector<int> countConnections, int allThird[], int& indexThird);

	bool connectionExists(const std::string user1, const std::string user2);// проверка наличия связи
	bool userExists(const std::string user); // проверка наличия юзера
	std::string _users[SIZE]; // хранилище имён (вершин графа)
	int _matrix[SIZE][SIZE]; // матрица смежности - наличия или отсутствие связи
   // матрица  заполняется числами.Чтобы вывести наименование связи создать сеттер который принимает значение из матрицы 
   //и инициализирует переменную _connections и геттер который возвращает значение этой переменной 
	std::string _connections; //наименование (рёбер графа)
	int _usersCount; // количество пользоателей

};

// в программе используется ник пользователя, чтобы заполнить ФИО, возраст и т.п  - создать структуру для пользователя.
//добавить в функцию addUser аполнение полей этой структуры