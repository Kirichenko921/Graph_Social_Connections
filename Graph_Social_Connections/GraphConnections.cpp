#include "GraphConnections.h"
#include <iostream>

#define VERYBIGINT 1000000000
Graph::Graph() {
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            _matrix [i][j] = 0;
    _usersCount = 0;
}

void Graph::addUser ( std::string user)// добавление пользователя
{
    if (userExists(user))
    {
        std::cout << "\nThis nickname is busy. Please enter a different nickname!\n";
        return ;
    }
    _users[_usersCount] = user;
    _usersCount++;
    }

void Graph::addConnection(std::string user1,  std::string user2, int connection)// добавление связи
{
    int  index1 = 0, index2 = 0;
    for (int i = 0, count = 0 ; i < SIZE; ++i)
    {
        if (_users[i] == user1)
        {
            index1 = i;
            count++;
        }
        if ( _users[i] == user2)
        {
            index2 = i;
            count++;
        }
        if (count == 2)
            break;
    }
    _matrix [index1][index2] = connection;
    _matrix [index2][index1] = connection;
}

bool Graph::connectionExists(std::string user1, std::string user2)// проверка наличия связи
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
    return _matrix[index1][index2] >0;
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
    bool visited[SIZE]; // список посещенных вершин
    for (int i = 0; i < SIZE; i++)
        visited[i] = false;
    int arrCountPaths[SIZE];
    for (int i = 0; i < SIZE; i++)
        arrCountPaths[i] = 0;
    for (int i = 0; i < _usersCount; i++) {
        std::cout << "\nAll dating couples through three handshakes for " << _users[i] << ":\n";
        int currentPath = 0; //текущая длина пути
   
           
    searchThreeHandshakesInner(visited, _users[i],i ,currentPath ,arrCountPaths); // запуск алгоритма 
    }
   
}

void Graph::searchThreeHandshakesInner(bool visited[], std::string current, int indexTo,  int currentPath, int arrCountPaths[])
{
    if (currentPath == 3) // если попали к третьей непрерывной связи
    {
        std::cout << "\t\t- " << _users[indexTo] << std::endl;
       
       return;
    }
     std::string usersToVisit[SIZE]; // очередь пользователей для обхода от текущего пользователя
    int countUser = 0;  // количество пользователей имеющих связь с текущим пользователем
    std::vector <int> relatedUserIndexes; // индексы пользователей имеющих связь с текущим пользователем
    for (int i = 0, j = 0; i < SIZE; i++) // поиск пользователя для следующего шага 
    {
        if (connectionExists(_users[indexTo], _users[i]) && !visited[i]) // если существует связь и она ведёт к не посещённому пользователю
        {
            usersToVisit[j] = _users[i];                           // добавляем в очередь 
            relatedUserIndexes.push_back(i);                       // сохраняем индекс 
            ++j;
            ++countUser;                                     // и увеличиваем счётчик
        }
    }
    if (countUser > 0)
    {
        visited[indexTo] = true;
    }
    arrCountPaths[indexTo] = countUser;
    for (int i = 0; i < countUser; i++) // переходим в следующую вершину если такая есть
    {
        searchThreeHandshakesInner(visited, usersToVisit[i],relatedUserIndexes[i], currentPath+1, arrCountPaths);
        --arrCountPaths[indexTo];
        if (!arrCountPaths[indexTo])
        {
            visited[indexTo] = false;
           
        }
    }

}

