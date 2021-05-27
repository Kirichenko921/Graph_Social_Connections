#pragma once
#include <iostream>
#include <vector>
#define SIZE 11
class Graph
{
public:
    Graph();
    void addUser(std::string user);// добавление пользователя
    void addConnection(std::string user1, std::string user2, int connection);// добавление связи
    
    void searchThreeHandshakes(); // поиск минимального расстояния между двумя вершинами
    void searchThreeHandshakesInner(bool visited[], std::string to,int indexTo, int currentPath, int arrCountPaths[]);// поиск минимального расстояния между двумя вершинами внутренння функция
    ~Graph()
    {}

private:
    bool connectionExists( std::string user1,  std::string user2);// проверка наличия связи
    bool userExists( std::string user); // проверка наличия юзера
    std::string _users[SIZE]; // хранилище имён (вершин графа)
    int _matrix[SIZE][SIZE]; // матрица смежности
   
    std::string _connections; // хранилище связей (рёбер графа)
    int _usersCount; // количество пользоателей

};