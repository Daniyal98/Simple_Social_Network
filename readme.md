### Simple Social Network

A simple social network demonstration in C++ using Graph and Linked List. A csv file containing names of friends separated by a comma are provided. The file is read and a graph is generated. Each person is a node and has a Linked List containing the names of their friends. In this program, you can see:
1. The whole network.
2. Who has the most number of friends.
3. Who has the least number of friends.
4. Who has a specified number of friends.
5. Largest connected community of people.
6. Mutual friends of two given friends.
7. Run BFS on the graph starting with a person.

### How To Build

We build this project using cmake. Create a folder named build. Go into that folder and run `cmake ..`. This will generate a MakeFile. Just run `make` after that and a executable by the name simple_social_network will be generated. Just run the program by `./simple_social_network`