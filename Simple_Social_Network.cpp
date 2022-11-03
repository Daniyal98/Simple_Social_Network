#include <iostream>
#include <string>
#include <fstream>
using namespace std;
class FriendNode;


class Node
{
public:
	string name;
	Node *Next;
	Node();
};

Node::Node()
{
	name = "";
	Next = NULL;
}

void InsertNode(Node *&Array, string n, int &size)
{
	Node *temp = new Node[size];
	for (int i = 0; i < size; i++)
	{
		temp[i] = Array[i];
	}

	Array = NULL;
	Array = new Node[size + 1];
	for (int i = 0; i < size; i++)
	{
		Array[i] = temp[i];
	}
	Array[size].name = n;
	size++;
}


class LinkedList
{
public:
	Node *Head;
	LinkedList();
	void insert(Node *);
	Node* insert(int, string);
	void operator=(LinkedList);
};

LinkedList::LinkedList()
{
	Head = NULL;
}

void LinkedList::insert(Node *N)
{
	Node *CurrNode = Head;
	Node *NewNode = new Node;
	NewNode->name = N->name;
	if (Head == NULL)
	{
		Head = N;
		Head->Next = NULL;
	}

	else
	{
		while (true)
		{
			if (CurrNode == NULL)
			{
				CurrNode = NewNode;
				CurrNode->Next = NULL;
				break;
			}
			CurrNode = CurrNode->Next;
		}
	}


}

Node* LinkedList::insert(int index, string data) 
{
	if (index < 0) 
		return NULL;

	int currIndex = 1; 
	Node* currNode = Head; 
	while (currNode && index > currIndex) 
	{ 
		currNode = currNode->Next; currIndex++; 
	} 
	if (index > 0 && currNode == NULL) 
		return NULL;
	Node* newNode = new Node; 
	newNode->name = data; 
	if (index == 0) 
	{ 
		newNode->Next = Head; 
		Head = newNode; 
	}
	else 
	{ 
		newNode->Next = currNode->Next; 
		currNode->Next = newNode; 
	} 
	return newNode;
}

void LinkedList::operator=(LinkedList L)
{
	Node *CurrNode = L.Head;
	while (CurrNode != NULL)
	{
		*(this)->insert(0, CurrNode->name);
		CurrNode = CurrNode->Next;
	}
}

class FriendNode
{
public:
	string name;
	LinkedList Friends;
	void operator=(FriendNode);
};

void FriendNode::operator=(FriendNode N)
{
	name = N.name;
	Friends = N.Friends;
}

void insertName(string *&Array, string N, int &size)
{
	string *temp = new string[size];
	for (int i = 0; i < size; i++)
	{
		temp[i] = Array[i];
	}
	Array = NULL;
	Array = new string[size + 1];
	for (int i = 0; i < size; i++)
	{
		Array[i] = temp[i];
	}
	temp = NULL;
	Array[size] = N;
	size++;
}

bool CheckString(string *A, string n, int s)
{
	for (int i = 0; i < s; i++)
	{
		if (A[i] == n)
			return false;
	}
	return true;
}

class Queue
{
public:
	Node *Front;
	Node *Rear;
	int num;
	Queue();
	void Enqueue(Node *);
	string Dequeue();
	bool isEmpty();
};

Queue::Queue()
{
	Front = NULL;
	Rear = NULL;
	num = 0;
}

bool Queue::isEmpty()
{
	if (num)
		return false;

	else
		return true;
}

void Queue::Enqueue(Node *N)
{
	Node *newNode; 
	newNode = new Node; 
	newNode->name = N->name; 
	newNode->Next = NULL; 
	if (isEmpty()) 
	{ 
		Front = newNode; 
		Rear = newNode; }
	else 
	{ 
		Rear->Next = newNode; 
		Rear = newNode; 
	}
	num++;
}

string Queue::Dequeue()
{
	Node *temp;
	string n; 
	if (isEmpty()) 
		cout << "The queue is empty.\n"; 
	else
	{
		n = Front->name;
		temp = Front->Next;
		delete Front;
		Front = temp;
		num--;
	}
	return n;
}

class Graph
{
public:
	FriendNode *Array;
	int FriendsArraySize;
	Graph();
	void Populate();
	void InsertFriend(string, string);
	bool Check(string, string);
	void Display();
	void MostNumberOfFriends();
	void LeastNumberOfFriends();
	void SpecificNumberOfFriends(int);
	void MutualFriends(string, string);
	void Community();
	void BFS(string);
};

Graph::Graph()
{
	FriendsArraySize = 0;
	Array = new FriendNode[FriendsArraySize];
}

void Graph::Populate()
{
	string name1, name2;
	fstream File;
	File.open("../friends.csv", ios::in);
	if (File)
	{
		while (File.good())
		{
			getline(File, name1, ',');
			getline(File, name2, '\n');

			if (Check(name1, name2))
			{
				InsertFriend(name1, name2);
			}

			if (Check(name2, name1))
			{
				InsertFriend(name2, name1);
			}

		}
	}
}

bool Graph::Check(string n1, string n2)
{
	for (int i = 0; i < FriendsArraySize; i++)
	{
		if (Array[i].name == n1)
		{
			Array[i].Friends.insert(0, n2);
			return false;
		}
	}
	return true;
}

void Graph::InsertFriend(string n1, string n2)
{
	FriendNode *temp = new FriendNode[FriendsArraySize];
	for (int i = 0; i < FriendsArraySize; i++)
	{
		temp[i] = Array[i];
	}

	Array = NULL;
	Array = new FriendNode[FriendsArraySize + 1];

	for (int i = 0; i < FriendsArraySize; i++)
	{
		Array[i] = temp[i];
	}

	temp = NULL;
	Array[FriendsArraySize].name = n1;
	Array[FriendsArraySize].Friends.insert(0, n2);
	FriendsArraySize++;
}

void Graph::Display()
{
	for (int i = 0; i < FriendsArraySize - 1; i++)
	{
		cout << i + 1 << ") " << Array[i].name << endl;
		cout << "Friends of " << Array[i].name << " are the following:" << endl;
		Node *CurrNode = Array[i].Friends.Head;
		while (CurrNode != NULL)
		{
			cout << "-->";
			cout << CurrNode->name << endl;
			CurrNode = CurrNode->Next;
		}
	}
}

void Graph::MostNumberOfFriends()
{
	int MostFriends = 0;
	string GuyWithMostFriends = "";
	for (int i = 0; i < FriendsArraySize - 1; i++)
	{
		int count = 0;
		Node *CurrNode = Array[i].Friends.Head;
		while (CurrNode != NULL)
		{
			count++;
			CurrNode = CurrNode->Next;
		}
		if (count > MostFriends)
		{
			MostFriends = count;
			GuyWithMostFriends = Array[i].name;
		}
	}
	cout << GuyWithMostFriends << " has the most friends that is " << MostFriends << endl;
}

void Graph::LeastNumberOfFriends()
{
	int numberOfGuys = 0;
	string *SociallyAwkwardGuys = new string[numberOfGuys];
	int leastFriends = 999999;
	for (int i = 0; i < FriendsArraySize - 1; i++)
	{
		int count = 0;
		Node *CurrNode = Array[i].Friends.Head;
		while (CurrNode != NULL)
		{
			count++;
			CurrNode = CurrNode->Next;
		}
		if (count <= leastFriends)
		{
			leastFriends = count;
		}

	}

	for (int i = 0; i < FriendsArraySize - 1; i++)
	{
		int count = 0;
		Node *CurrNode = Array[i].Friends.Head;
		while (CurrNode != NULL)
		{
			count++;
			CurrNode = CurrNode->Next;
		}

		if (count <= leastFriends)
			insertName(SociallyAwkwardGuys, Array[i].name, numberOfGuys);
	}
	for (int i = 0; i < numberOfGuys; i++)
	{
		cout << SociallyAwkwardGuys[i] << ' ';
	}
	cout << "have the least number of friends that is " << leastFriends << endl;
}

void Graph::MutualFriends(string n1, string n2)
{
	int firstIndex = 0;
	int secondIndex = 0;
	int count = 0;
	int s = 0;
	string *StringArray = new string[s];
	for (int i = 0; i < FriendsArraySize; i++)
	{
		if (Array[i].name == n1)
		{
			firstIndex = i;
		}
	}

	for (int i = 0; i < FriendsArraySize; i++)
	{
		if (Array[i].name == n2)
		{
			secondIndex = i;
		}
	}

	Node *CurrNode1 = Array[firstIndex].Friends.Head;
	while (CurrNode1 != NULL)
	{
		Node *CurrNode2 = Array[secondIndex].Friends.Head;
		while (CurrNode2 != NULL)
		{
			if (CurrNode1->name == CurrNode2->name)
			{
				count++;
				insertName(StringArray, CurrNode1->name, s);
			}
			CurrNode2 = CurrNode2->Next;
		}
		CurrNode1 = CurrNode1->Next;
	}
	if (count == 0)
	{
		cout << "These two have no mutual friends" << endl;
	}
	else
	{
		cout << Array[firstIndex].name << " and " << Array[secondIndex].name << " have " << count << " mutual Friends that are " << endl;
		for (int i = 0; i < s; i++)
		{
			cout << "-->";
			cout << StringArray[i] << endl;
		}
	}
}

void Graph::SpecificNumberOfFriends(int n)
{
	cout << "People who have " << n << " Friends are " << endl;
	for (int i = 0; i < FriendsArraySize; i++)
	{
		int count = 0;
		Node *CurrNode = Array[i].Friends.Head;
		while (CurrNode != NULL)
		{
			count++;
			CurrNode = CurrNode->Next;
		}
		if (count == n)
		{
			cout << "-->" << Array[i].name << endl;
		}
	}
}

void Graph::Community()
{
	int checkedCount = 0;
	string *Checked = new string[checkedCount];
	for (int i = 0; i < FriendsArraySize; i++)
	{
		int count = 0;
		string *Com = new string[count];
		Node *CurrNode1 = Array[i].Friends.Head;
		while (CurrNode1 != NULL)
		{
			for (int j = 0; j < FriendsArraySize; j++)
			{
				if (CurrNode1->name == Array[j].name)
				{
					Node *CurrNode2 = CurrNode1;
					while (CurrNode2 != NULL)
					{
						Node *CurrNode3 = Array[j].Friends.Head;
						while (CurrNode3 != NULL)
						{
							if (CurrNode2->name == CurrNode3->name && CheckString(Checked, CurrNode2->name, checkedCount))
							{
								insertName(Com, CurrNode2->name, count);
								insertName(Checked, CurrNode2->name, checkedCount);
							}
							CurrNode3 = CurrNode3->Next;
						}
						CurrNode2 = CurrNode2->Next;
					}
				}
			}
		CurrNode1 = CurrNode1->Next;
		}
		cout << Array[i].name;
		for (int j = 0; j < count; j++)
		{
			cout << "-->" << Com[j];
		}
		cout << endl;
	}
}

void Graph::BFS(string n)
{
	string n1;
	int index = 0;
	bool *Visited = new bool[FriendsArraySize];
	for (int i = 0; i < FriendsArraySize; i++)
		Visited[i] = false;

	Queue Q;
	for (int i = 0; i < FriendsArraySize; i++)
	{
		if (Array[i].name == n)
			index = i;
	}
	int tempSize = 0;
	Node *temp = new Node[tempSize];
	Visited[index] = true;
	Node *CurrNode = Array[index].Friends.Head;
	
	Q.Enqueue(CurrNode);

	while (!Q.isEmpty())
	{
		string s = Q.Dequeue();
		cout << s << endl;
		while (CurrNode != NULL)
		{
			for (int i = 0; i < FriendsArraySize; i++)
			{
				if (Array[i].name == CurrNode->name)
				{
					if (!Visited[i])
					{
						Visited[i] = true;
						Q.Enqueue(CurrNode);
					}
				}
			}
			CurrNode = CurrNode->Next;
			/*if (CurrNode == NULL)
			{
				index++;
				CurrNode = Array[index].Friends.Head;
			}

			if (CurrNode->name == Array[FriendsArraySize - 1].name)
			{
				break;
			}*/
		}
	}
}



int main()
{
	Graph G;
	G.Populate();
	int choice;
	int input = 1;
	cout << "<----------WELCOME TO DANIYAL\'S SOCIAL NETWORK---------->" << endl << endl << endl << endl;
	while (input)
	{
	
		cout << "Press 1 to display the users of the whole network" << endl;
		cout << "Press 2 to see who has the most friends on this network" << endl;
		cout << "Press 3 to see who has the least number of friemds on this network" << endl;
		cout << "Press 4 to see who has a specified number of friends on this network" << endl;
		cout << "Press 5 to see the mutual friends of two given friends" << endl;
		cout << "Press 6 to see the largest connected community of people" << endl;
		cout << "Press 7 for BFS" << endl;
		cout << "Press 8 to exit" << endl;
		cin >> choice;
		if (choice == 1)
			G.Display();

		else if (choice == 2)
			G.MostNumberOfFriends();

		else if (choice == 3)
			G.LeastNumberOfFriends();

		else if (choice == 4)
		{
			int n;
			cout << "Enter the number of friends you want to search for:" << endl;
			cin >> n;
			G.SpecificNumberOfFriends(n);
		}

		else if (choice == 5)
		{
			string Person1;
			string Person2;
			cout << "Enter the name of first person:" << endl;
			cin >> Person1;
			cout << "Enter the name of second person:" << endl;
			cin >> Person2;
			G.MutualFriends(Person1, Person2);
		}

		else if (choice == 6)
		{
			G.Community();
		}

		else if (choice == 7)
		{
			G.BFS("Hassan");
		}

		else if (choice == 8)
		{
			input = 0;
			cout << "<-----------------------THANKS FOR USING OUR SOCIAL NETWORK---------------------->" << endl;
			cout << "-------------------------SEE YOU SOON------------------------>" << endl;
			cout << "<-----------------------GOODBYE------------------------------>" << endl;
		}

	}
	return 0;
}