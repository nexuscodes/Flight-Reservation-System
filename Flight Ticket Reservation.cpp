#include<bits/stdc++.h>
#include <boost/date_time.hpp>
using namespace std;

/* HOW TO USE
The given cpp programs accpets the following queries :

1. Add an airline : to add the airline in the directory

Query Description : "ADD_AIRLINE airlineID airlineName source destination totalSeats 'days on which it is available'";
eg : "ADD_AIRLINE BC107 Viscara Mumbai Delhi 160 Monday Tuesday"

2. search flights:

description : "SEARCH_FLIGHTS Source Destination DD MM YYYY"
eg : "SEARCH_FLIGHTS Mumbai Delhi 30 10 2019"

3 Book Tickets

description : "BOOKSEATS Flightid DD MM YYYY USERNAME";
eg : "BOOKSEATS BC107  29 10 2019 AYUSH"

4 Show Flights Booked By user
description : "SHOW_FLIGHTS_BOOKED UserName"

*/
// END OF HOW TO uSE
const string DAYS[] = {"sunday", "monday", "tuesday", "wednesday", "thursday", "friday", "saturday"};
map<string, int> dayToDayNumber;
map<string, vector<pair<string, string>>> flightBookedByUser;

void mapDaytoDayNumber()
{
	for(int i = 0; i < 7; i++)
	{
		dayToDayNumber[DAYS[i]] = i;
	}
	return;
}

int getDayOfWeekIndex(int day, int month, int year) 
{
    boost::gregorian::date d(year, month, day);
    return d.day_of_week();
}
class Airline
{
	public :
	string airlineName;
	string source;
	string destination;
	int availableDays[7] = {0};
	vector<char> seatAllocation;
	map<string, vector<char>> eachDayAllocation;
	map<int, string> seatUser;
	int totalSeats;

	Airline(vector<string> details)
	{
		airlineName = details[2];
		source = details[3];
		destination = details[4];
		totalSeats = stoi(details[5]);

		for(int i = 6; i < (int)input.size(); i++)
		{
			transform(input[i].begin(), input[i].end(), input[i].begin(), ::tolower);
			availableDays[dayToDayNumber[input[i]]] = 1;
		}
		seatAllocation.resize(totalSeats);
	}

	void bookSeats(vector<string> input)
	{
		int seatsTobook = input[2];
		string date = input[3] + " " + input[4] + " " + input[5];
		int indexDay = getDayOfWeekIndex(stoi(input[3]), stoi(input[4]), stoi(input[5]));
		string userName = input[6];

		if(!isAvailable[indexOay])
		{
			cout<<"Flight Not Available On This Date\n";
			return;
		}
		int cnt = 0;
		for(int i = 0; i < totalSeats; i++)
		{
			if(eachDayAllocation[date][i] != 'R') cnt++;
		}

		if(cnt < seatsTobook)
		{
			cout<<"Required Seats Not Available\n";
			return 0;
		}

		for(int i = 0; i < totalSeats; i++)
		{
			if(eachDayAllocation[date][i] != 'R')
			{
				eachDayAllocation[date][i] = 'R';
				seatsTobook--;
			}
			if(!seatsTobook) break;
		}

		flightBookedByUser[userName].push_back({input[1], date});
		cout<<"Seats Booked\n";
	}
}

map<string, Airline*> myMap;
bool isAvailable(string src, string dest, int day, string id)
{
	if(myMap[id]->source != src) return false;
	if(myMap[id]->destination != dest) return false;
	if(myMap[id]->availableDays[day] != 1) return false;

	return true;
}

void searchFlight(vector<string> input)
{
	string src = input[1];
	string dest = input[2];
	int day = stoi(input[3]);
	int month = stoi(input[4]);
	int year = stoi(input[5]);
	string userName = input[6];
	int indexOay = getDayOfWeekIndex(day, month, year);

	int atleastOne = 0;
	for(auto it : myMap)
	{
		if(isAvailable(src, dest, indexOay, it.first))
		{
			atleastOne = 1;
			cout<<it.first<<" "<<myMap[it.first]->airlineName<<'\n';
		}
	}

	if(!atleastOne)
	{
		cout<<"No Flight Available\n";
	}
}

void showFlightsBookedBy(vector<string> input)
{
	string userName = input[1];

	for(auto it : flightBookedByUser[userName])
	{
		cout<<it.first<<" on "<<it.second<<'\n';
	}
	return;
}
vector<string> breakString(string input)
{
	string word = "";
	int n = (int)input.size();

	vector<string> ret;

	for(int i = 0; i < n; i++)
	{
		while(i < n && input[i] != ' ')
		{
			word += input[i];
			i++;
		}
		ret.push_back(word);
		word = "";
	}

	return ret;
}

int main()
{
	mapDaytoDayNumber();
	
	int totalCommands;

	string input;
	getline(cin, input);

	totalCommands = stoi(input);

	for(int i = 0; i < totalCommands; i++)
	{
		getline(cin, input);
		vector<string> query = breakString(input);
		if(query[i] == "ADD_AIRLINE")
		{
			if(myMap.find(query[1]) == myMap.end())
			{
				myMap[query[1]] = new Airline(query);
			}
			else
			{
				cout<<"Airline ALready Present\n";
			}
		}
		if(query[i] == "SEARCH_FLIGHTS") // then source, destination, date(dd mm yyyy)
		{
			searchFlight(query);
		}

		if(query[i] == "BOOKSEATS")
		{
			myMap[query[1]]->bookSeats(query);
		}

		if(query[i] == "SHOW_FLIGHTS_BOOKED")
		{
			showFlightsBookedBy(query);
		}
	}
}