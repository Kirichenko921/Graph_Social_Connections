#include "GraphConnections.h"
#include<iostream>

int main()
{

	Graph connection;
	connection.addUser("A");
	connection.addUser("B");
	connection.addUser("C");
	connection.addUser("D");
	connection.addUser("E");
	connection.addUser("F");
	connection.addUser("G");
	connection.addUser("H");
	connection.addUser("I");
	connection.addUser("K");

	connection.addConnection("A", "C", 1);
	connection.addConnection("B", "C", 1);
	connection.addConnection("B", "H", 1);
	connection.addConnection("B", "J", 1);
	connection.addConnection("C", "E", 1);
	connection.addConnection("C", "H", 1);
	connection.addConnection("D", "I", 1);
	connection.addConnection("D", "J", 1);
	connection.addConnection("F", "I", 1);
	connection.addConnection("G", "H", 1);
	connection.addConnection("G", "K", 1);
	for (int i = 0; i < SIZE; i++)
		for (int j = 0; j < SIZE; j++)
			std::cout<<connection._matrix[i][j]<<"\n";
	
	std::cout << std::endl;
	//connection.findMinWayDFS();
	return 0;
}