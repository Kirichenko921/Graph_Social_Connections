#include "GraphConnections.h"

Graph::Graph() {
	for (int i = 0; i < SIZE; i++)
		for (int j = 0; j < SIZE; j++)
			_matrix[i][j] = 0;        //в конструктооре  матрицу заполняем нолями - связей пока нет
	_usersCount = 0;
}

void Graph::addUser(std::string user)// добавление пользователя
{
	if (userExists(user)) // проверяем наличия ника в базе
	{
		std::cout << "\nThis nickname is busy. Please enter a different nickname!\n";
		return;
	}
	_users[_usersCount] = user;
	_usersCount++;
}

void Graph::addConnection(const std::string user1, const  std::string user2, const int connection)// добавление связи по нику
{
	int  index1 = 0, index2 = 0;
	for (int i = 0, count = 0; i < SIZE; ++i)
	{
		if (_users[i] == user1)
		{
			index1 = i;
			count++;
		}
		if (_users[i] == user2)
		{
			index2 = i;
			count++;
		}
		if (count == 2)
			break;
	}
	_matrix[index1][index2] = connection;
	_matrix[index2][index1] = connection;
}

bool Graph::connectionExists(const std::string user1, const std::string user2)// проверка наличия связи
{
	int  index1 = 0, index2 = 0;
	for (int i = 0, count = 0; i < SIZE; ++i)
	{
		if (_users[i] == user1)
		{
			index1 = i;
			count++;
		}
		if (_users[i] == user2)
		{
			index2 = i;
			count++;
		}
		if (count == 2)
			break;
	}
	return _matrix[index1][index2] > 0;
}

bool Graph::userExists(const std::string user) // проверка наличия юзера
{
	for (int i = 0; i < _usersCount; i++)
		if (_users[i] == user)
			return true;
	return false;
}

void Graph::searchThreeHandshakes()
{
	int pairsThreeHandshakes[SIZE][SIZE];// хранилище связей для пар которые имеют связь через три рукопожатия
	for (int i = 0; i < _usersCount; i++)
		for (int j = 0; j < _usersCount; j++)
			pairsThreeHandshakes[i][j] = 0; // заполнем нолями - таких свзей пока незнаем
	std::vector< bool> visited; // список посещенных вершин
	for (int i = 0; i < _usersCount; i++)
		visited.push_back(false);  //все пользователи (вершины) непосещённе
	std::vector<int> countConnections; // количество связей каждого следующего пользователя 
	for (int i = 0; i < _usersCount; i++)
		countConnections.push_back(0);  // пока заполняем нолями
	int allThird[SIZE]; // хранилище индексов пользователей найденных связей 
	int indexThird = 0;  // индекс  для добавления в хранилище
	for (int i = 0; i < SIZE; i++)
		allThird[i] = -1;              // заполняем отрицательным значением
	for (int i = 0; i < _usersCount; i++) // находим связи через три рукопожатия для каждого пользователя
	{
		int countHandshakes = 0; // счётчик рукопожатий        
		searchThreeHandshakesInner(visited, i, countHandshakes, countConnections, allThird, indexThird); // запуск алгоритма 
		for (int k = 0; k < SIZE; k++) // заполняем хранилище связей
		{
			if (allThird[k] == -1)  // если связей больше нет - выходим
				break;
			if (pairsThreeHandshakes[allThird[k]][i] == 1) // если связь уже есть в хранилище не добавляем
			{
				allThird[k] = -1;
			}
			else
			{
				pairsThreeHandshakes[i][allThird[k]] = 1;
				allThird[k] = -1;
			}
		}
		indexThird = 0;
	}
	for (int i = 0; i < SIZE; i++)  // выводим наличие связей на экран
	{
		for (int j = 0; j < SIZE; j++)
		{
			if (pairsThreeHandshakes[i][j] == 1)
				std::cout << "\n" << _users[i] << " < 3 handshakes > " << _users[j] << std::endl;
		}
	}
}

void Graph::searchThreeHandshakesInner(std::vector<bool> visited, int indexTo, int countHandshakes, std::vector<int> countConnections, int allThird[], int& indexThird)
{
	if (countHandshakes == 3) // если попали к третьей непрерывной связи
	{
		allThird[indexThird++] = indexTo;
		return;
	}

	int countUser = 0;  // количество пользователей имеющих связь с текущим пользователем
	std::vector <int> relatedUserIndexes; // индексы пользователей имеющих связь с текущим пользователем
	for (int i = 0, j = 0; i < SIZE; i++) // поиск пользователя для следующего шага 
	{
		if (connectionExists(_users[indexTo], _users[i]) && !visited[i]) // если существует связь и она ведёт к не посещённому пользователю
		{

			relatedUserIndexes.push_back(i);                       // сохраняем индекс 
			++j;
			++countUser;                                     // и увеличиваем счётчик
		}
	}
	if (countUser > 0) // если у вершины есть связи отмечаем как посещённую
	{
		visited[indexTo] = true;
	}
	countConnections[indexTo] = countUser;
	for (int i = 0; i < countUser; i++) // переходим в следующую вершину если такая есть
	{
		searchThreeHandshakesInner(visited, relatedUserIndexes[i], countHandshakes + 1, countConnections, allThird, indexThird);
		--countConnections[indexTo];
		if (!countConnections[indexTo])  // если проверили все связи помечаем ка непосещённую
		{
			visited[indexTo] = false;

		}
	}

}

