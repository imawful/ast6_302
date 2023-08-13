// Name: Kevin Barrios
// NSHE ID: 2001697903
// Assignment 6 mario kart
//  implement a binary min heap to use a 
//   priority q that will simulate racers getting
//   closer to a finish line 
#include "priorityQ.h"
#include "priorityQ.cpp"
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
struct Racer
{
	std::string racerName;
	bool seen;
	bool finished;
};
void formatName(std::string&);
int main()
{
	//define some variables 
	std::string tempStr;
	int racerCount = 0;
	int intervalCount = 0;
	int updateCount = 0;
	int racersRank = 0;
	std::vector<std::string> racerVec;
	std::vector<double> priorityVec;
	
	//create unordered_map and priorty queue to store racers
	priorityQ<std::string, double> racerQ;
	std::unordered_map<std::string, Racer> racerMap;
	
	//loop to read in racers at beggining 
	for(cin>>tempStr; tempStr != "END"; cin>>tempStr)
	{
		formatName(tempStr);
		racerQ.push_back(tempStr, 50);
		racerMap[tempStr] = {tempStr, 0, 0};
		racerCount++;
	}
	
	//while racers are still in race 
	while(!racerQ.isEmpty())
	{
		//before we enter interval 
		//output current interval 
		std::cout << "Interval " << ++intervalCount << std::endl;
		//check if leading racer has distance of 0 or less 
		while(racerQ.get_front_priority() <= 0 && racerCount != 0)
		{
			racerMap[racerQ.get_front_key()].finished = true;
			std::cout << ++racersRank << " " << racerQ.get_front_key() << std::endl;
			racerQ.pop_front();
			racerCount--;
		}
		//start of interval loop 
		for(cin>>tempStr; tempStr != "DONE"; cin>>tempStr)
		{
			formatName(tempStr); // gets rid of case sensitive 
			// if value is racer
			if(racerMap.find(tempStr) != racerMap.end())
			{
				//check if racer has finished 
				if(racerMap[tempStr].finished)
					//output that racer has finished and move on...
					std::cout << "Racer has already finished the race!" << std::endl;
				// if racer has not finished, check if has not been seen 
				else if(racerMap[tempStr].seen != true)
				{
					//racer has not been seen so we update it to be seen 
					// and push the name into our vector 
					racerMap[tempStr].seen = true;
					racerVec.push_back(tempStr);
				}
				// else racer has been seen 
				else 
					std::cout << "Already updated " << tempStr << " in this interval!\n";
			}
			// if value not racer, then if value is valid priority
			else if(priorityVec.size() + 1 == racerVec.size())
				// push priority to vector to match with racer at same index 
				priorityVec.push_back(stod(tempStr));
			
			//see if we need to update 
			if(updateCount < priorityVec.size() && priorityVec.size() >=1 && priorityVec.size() == racerVec.size())
			{
				//perform update 
				std::cout << "Updating " << racerVec[updateCount] << std::endl;
				racerQ.decrease_priority(racerVec[updateCount], priorityVec[updateCount]);
				++updateCount;
			}
			
			//interval ends if we update all current racers
			if(updateCount == racerCount)
				break;
		}
		//end of interval loop (interval over) 
		
		// reset all updated racers seen to false 
		for(auto & daisy : racerVec)
			racerMap[daisy].seen = false;
		// clear out vectors and reset update count for new interval
		racerVec.clear();
		priorityVec.clear();
		updateCount = 0;
	}

	return 0;
}
void formatName(std::string & s)
{
	for(auto& daisy : s)
		daisy = tolower(daisy);
}