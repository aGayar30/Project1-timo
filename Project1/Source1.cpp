#include<iostream>
#include <vector>
#include <list>
#include <iterator>
#include <string>
#include <string.h>
#include<algorithm>
#include <queue>
#define NegInfinity -1000000000
using namespace std;

class Rout
{
public:

	string Desttown_name;
	int Distance;
	Rout(string D, int dist)
	{
		Desttown_name = D;
		Distance = dist;
	}
	string getDestTownName()
	{
		return Desttown_name;
	}
	void setDestTownName(string D_name)
	{
		Desttown_name = D_name;
	}
	int getDistance()
	{
		return Distance;
	}
	void setDistance(int Dist)
	{
		Distance = Dist;
	}
};

class Town
{
public:
	int town_id;
	string town_name;
	Town* previous;
	vector<Rout>Rlist;
	bool visited;
	Town()
	{
		town_id = 0;
		town_name = "";
	}
	Town(int id, string Tname)
	{
		town_id = id;
		town_name = Tname;
	}
	int getTownID()
	{
		return town_id;
	}
	string getTownName()
	{
		return town_name;
	}
	void setID(int id)
	{
		town_id = id;
	}
	void setTownName(string tname)
	{
		town_name = tname;
	}

	vector < Rout > getRoutList()
	{
		return Rlist;
	}

	void printEdgeList() {
		cout << "[";
		for (auto it = Rlist.begin(); it != Rlist.end(); it++) {
			cout << it->getDestTownName() << "(" << it->getDistance() << ") --> ";
		}
		cout << "]";
		cout << endl;
	}
};

class Graph
{
public:
	vector<Town>T;

	//adding town 
	void addTown(Town newT)
	{
		T.push_back(newT);
		cout << "\nTown added successfuly\n";
	}

	bool check_if_Townexist(string n)
	{
		for (int i = 0; i < T.size(); i++)
		{
			if (T.at(i).getTownName() == n)
			{
				return true;
			}
		}
		return false;
	}

	bool checkIfEdgeExistByName(string source, string destination) {
		Town t = getTownByName(source);
		vector < Rout > e;
		e = t.getRoutList();
		for (auto it = e.begin(); it != e.end(); it++) {
			if (it->getDestTownName() == destination) {
				return true;
				break;
			}
		}
		return false;
	}

	void addRoutByName(string source, string destination, int dist)
	{
		if (check_if_Townexist(source) && check_if_Townexist(destination) == true)
		{
			if (checkIfEdgeExistByName(source, destination) == true)
			{
				cout << "\nRout between " << source << " and " << destination << " Already Exist\n" << endl;
			}
			else
			{
				for (int i = 0; i < T.size(); i++)
				{
					if (T.at(i).getTownName() == source)
					{
						Rout e(destination, dist);
						T.at(i).Rlist.push_back(e);
					}
					else if (T.at(i).getTownName() == destination)
					{
						Rout e(source, dist);
						T.at(i).Rlist.push_back(e);
					}
				}
				cout << "\nRout between " << source << " and " << destination << " added Successfully\n";
			}
		}
		else
		{
			cout << "\nInvalid Town name entered.\n";
		}
	}

	Town getTownByName(string n)
	{
		Town temp;
		for (int i = 0; i < T.size(); i++)
		{
			temp = T.at(i);
			if (temp.getTownName() == n)
			{
				return temp;
			}
		}
		return temp;
	}

	void deleteRout(string source, string destination)
	{
		bool check = checkIfEdgeExistByName(source, destination);
		if (check == true)
		{
			for (int i = 0; i < T.size(); i++)
			{
				if (T.at(i).getTownName() == source)
				{
					for (auto it = T.at(i).Rlist.begin(); it != T.at(i).Rlist.end(); it++)
					{
						if (it->getDestTownName() == destination)
						{
							T.at(i).Rlist.erase(it);
							//cout<<"First erase"<<endl;
							break;
						}
					}
				}

				if (T.at(i).getTownName() == destination)
				{
					for (auto it = T.at(i).Rlist.begin(); it != T.at(i).Rlist.end(); it++)
					{
						if (it->getDestTownName() == source)
						{
							T.at(i).Rlist.erase(it);
							//cout<<"second erase"<<endl;
							break;
						}
					}
				}
			}
		}
	}

	void updateRoutByName(string source, string  destination, int newWeight)
	{
		bool check = checkIfEdgeExistByName(source, destination);
		if (check == true)
		{
			for (int i = 0; i < T.size(); i++)
			{
				if (T.at(i).getTownName() == source)
				{
					for (auto it = T.at(i).Rlist.begin(); it != T.at(i).Rlist.end(); it++)
					{
						if (it->getDestTownName() == destination)
						{
							it->setDistance(newWeight);
							break;
						}
					}
				}
				else if (T.at(i).getTownName() == destination)
				{
					for (auto it = T.at(i).Rlist.begin(); it != T.at(i).Rlist.end(); it++)
					{
						if (it->getDestTownName() == source)
						{
							it->setDistance(newWeight);
							break;
						}
					}
				}
			}
			cout << "Rout distance Updated Successfully \n";
		}
		else {
			cout << "Rout between " << getTownByName(source).getTownName() << " and " << getTownByName(destination).getTownName() << " DOES NOT Exist\n";
		}
	}
	void deleteTown(string town)
	{
		int vIndex = 0;
		for (int i = 0; i < T.size(); i++)
		{
			if (T.at(i).getTownName() == town)
			{
				vIndex = i;
			}
		}
		for (int i = 0; i < T.size(); i++)
		{
			for (auto it = T.at(i).Rlist.begin(); it != T.at(i).Rlist.end(); it++)
			{
				if (it->getDestTownName() == town)
				{
					T.at(i).Rlist.erase(it);
					break;
				}
			}
		}
		T.erase(T.begin() + vIndex);
		cout << "\nTown Deleted Successfully" << endl;
	}
	void updateTown(string oldN, string newN)
	{
		for (int i = 0; i < T.size(); i++)
		{
			if (T.at(i).getTownName() == oldN)
			{
				T.at(i).setTownName(newN);
				break;
			}
		}
		cout << "Town Updated Successfully " << endl;
	}
	int getIndex(vector<Town> t, string K)
	{
		auto it = find(t.begin(), t.end(), K);
		// If element was found
		if (it != t.end())
		{
			// calculating the index
			// of K
			int index = it - t.begin();
			return index;
		}
	}

	void printGraph()
	{
		for (int i = 0; i < T.size(); i++)
		{
			Town temp;
			temp = T.at(i);
			cout << temp.getTownName() << " --> ";
			temp.printEdgeList();
		}
	}

};


int main()
{
	int operation;
	int num_town;
	int num_routs;
	int distance;
	int Arrdist[10000] = {};
	int index1, index2;
	string name;
	string t1;
	string t2;
	string town1;
	string town2;
	string Arrtown1[10000] = {};
	string Arrtown2[10000] = {};
	Graph g;
	Town t;

	// interface 
	cout << "&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&\n";
	cout << "&                             &\n";
	cout << "& Welcome to mini WASALNI App &\n";
	cout << "&                             &\n";
	cout << "&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&\n\n";

	cout << "please enter the number of Towns: \n";
	cin >> num_town;

	int q = 0;
	do // q will increase only when the input is valid
	{
		cout << "\nPlease Enter the name of the Town " << q + 1 << "\n";
		cin >> name;
		if (g.check_if_Townexist(name))
		{
			cout << "\nERROR : Town already exist\n";
			continue;
		}
		else {
			t.setTownName(name);
			g.addTown(t);
		}
		q++;
	} while ((q < num_town));

	cout << "\nPlease enter the number of Routs.\n";
	cin >> num_routs;

	int x = 0;
	do // x will increase only when the input is valid
	{
		cout << "\nROUT NO. " << x + 1 << "\nEnter The First Town Then The Second Town Then The Distance between them\n";
		cin >> t1;
		if (!(g.check_if_Townexist(t1)))
		{
			cout << "\nERROR : Town do not exist , Please enter valid one\n";
			continue;
		}
		else
		{
			cin >> t2;
			if (!(g.check_if_Townexist(t2)))
			{
				cout << "\nERROR : Town do not exist , Please enter valid one\n";
				continue;
			}
			else
			{
				cin >> distance;
				g.addRoutByName(t1, t2, distance);
			}
		}
		x++;
	} while (x < num_routs);

	do {
		cout << "\nPlease Select operation number you want to perform , OR Enter 0 to EXIT.\n";
		cout << "***\n";
		cout << "\n1. Add Town\n";
		cout << "2. Update Town\n";
		cout << "3. Delete Town\n";
		cout << "4. Add Rout\n";
		cout << "5. Update Rout\n";
		cout << "6. Delete Rout\n";
		cout << "7. Display MAP\n";
		cout << "8. Show the shortest Rout between two towns\n";
		cout << "0. Exit Program\n";

		cin >> operation;
		switch (operation)
		{
		case 0:
			break;
		case 1:
			cout << "\n*ADD TOWN*\n";
			cout << "\n-Enter Town name-\n";
			cin >> name;
			if (g.check_if_Townexist(name))
			{
				cout << "\nERROR : Town already exist\n";
			}
			else {
				t.setTownName(name);
				g.addTown(t);
			}
			break;
		case 2:
			cout << "*UPDATE TOWN*\n";
			cout << "-Enter name of Town to update -\n";
			cin >> t1;
			if (!(g.check_if_Townexist(t1)))
			{
				cout << "\nERROR : Town Don't exist\n";
			}
			else {
				cout << "\n-Enter the new Town Name -";
				cin >> t2;
				if ((g.check_if_Townexist(t2)))
				{
					cout << "\nERROR : Town already exist\n";
				}
				else {
					g.updateTown(t1, t2);
				}
			}
			break;
		case 3:
			cout << "*DELETE TOWN*\n";
			cout << "-Enter the Name of the Town to Delete -\n ";
			cin >> name;
			if (!g.check_if_Townexist(name))
			{
				cout << "\nERROR : Town Doesn't exist\n";
			}
			else {
				g.deleteTown(name);
			}
			break;
		case 4:
			cout << "*ADD ROUT*\n";
			cout << "\n-Enter source town name-\n";
			cin >> t1;
			if (!(g.check_if_Townexist(t1)))
			{
				cout << "\nERROR : Town Don't exist\n";
			}
			else {
				cout << "\n-Enter destination Town name-\n";
				cin >> t2;
				if (!(g.check_if_Townexist(t2)))
				{
					cout << "\nERROR : Town Don't exist\n";
				}
				else {
					cout << "\nEnter Distance of Rout:\n ";
					cin >> distance;
					g.addRoutByName(t1, t2, distance);
				}
			}
			break;
		case 5:
			cout << "*UPDATE ROUT*\n";
			cout << "\n-Enter source town name-\n";
			cin >> t1;
			if (!(g.check_if_Townexist(t1)))
			{
				cout << "\nERROR : Town Don't exist\n";
			}
			else {
				cout << "\n-Enter destination Town name-\n";
				cin >> t2;
				if (!(g.check_if_Townexist(t2)))
				{
					cout << "\nERROR : Town Don't exist\n";
				}
				else {
					cout << "\nEnter UPDATED Distance of Rout:\n ";
					cin >> distance;
					g.updateRoutByName(t1, t2, distance);
				}
			}
			break;
		case 6:
			cout << "*DELETE ROUT*\n";
			cout << "\n-Enter source town name-\n";
			cin >> town1;
			if (!(g.check_if_Townexist(town1)))
			{
				cout << "\nERROR : Town Don't exist\n";
			}
			else {
				cout << "\n-Enter destination Town name-\n";
				cin >> town2;
				if (!(g.check_if_Townexist(town2)))
				{
					cout << "\nERROR : Town Don't exist\n";
				}
				else {
					g.deleteRout(town1, town2);
					cout << "\nRout Between " << town1 << " and " << town2 << " Deleted Successfully.\n";
				}
			}
			break;
		case 7:
			cout << "--> Displaying MAP\n";
			g.printGraph();
			break;
		case 8:
			cout << "--> Displaying shortest Rout between 2 towns\n";
			cout << "\n-Enter source town name-\n";
			cin >> town1;
			if (!(g.check_if_Townexist(town1)))
			{
				cout << "\nERROR : Town Don't exist\n";
			}
			else {
				index1 = g.getIndex(g.T, town1);
				cout << "\n-Enter destination Town name-\n";
				cin >> town2;
				if (!(g.check_if_Townexist(town2)))
				{
					cout << "\nERROR : Town Don't exist\n";
				}
				else {
					index2 = g.getIndex(g.T, town2);
				}
			}
			break;
		default:
			cout << "\nERROR : Enter VALID Operation number\n";
		}
	} while (operation != 0);
	return 0;
}