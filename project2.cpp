/* Author: Jorge Moreno
   Instructor: Professor Sweany
   Date: 11/15/17
   Description: This program was created to simulate a disease that is transmitted throughout a population on an island. Given
   user inputted values different simulations can be created for this disease and this program will run until everyone has recovered
   and noone left on the island is infected or infectious. */

#include <iostream>
#include <cstdlib>
#include "islands.h"
using namespace std;

int transmit(int transProb,int &dayz,int &numInfected,int &numInfectious,int &numHealthy,int &numRecovered,int &islandsNum,islands **island);
void createInfected(int numInfected, int islandsNum, islands **island);

int main()
{
   cout << endl;
   cout <<" ============================================" << endl;
   cout <<" ||            Outbreak Simulator          ||" << endl;
   cout <<" ||          created by Jorge Moreno       ||" << endl;
   cout <<" ============================================" << endl;
   cout << endl;
   
  int humanID=1;    //variable holds a humans id number
  int numInfected =0; //variable holds the number of infected humans
  int numInfectious =0;  //variable holds the number of infectious humans
  int numHealthy =0;  //variable holds the number of healthy humans
  int numRecovered =0;  //variable holds the number of recovered humans
  int infectedPeriod =0;  //variable holds the length in days for the infected period
  int infectiousPeriod =0;  //variable holds the length in days for the infectious period
  int transProb =0;  //variable holds the transmission probability percentage as a whole number
  int rateContact =0;  //variable holds the amount of contacts a human can make daily
  int populationT =0;  //variable holds the total population for every island
  int islandsNum;  //variable holds the number of islands in the nation
  int infectedtemp;  //temp variable to hold the infected period
  int infectioustemp;  //temp variable to hold the infectious period
  int dayz =0;  //temp holds the amount of days the while loop has looped
  int count =-1;  //counter variable
  int *peopleNum;  //pointer for the number of people in an island
  islands **island;  //pointer for the islands class
  
  //The following is asking the user for variable values to begin the simulations
  //=============================================================================
  
  cout << "Please enter the number of current islands." << endl;  
  cin >> islandsNum;
  
  peopleNum = new int[islandsNum];
  for(int a=0;a<islandsNum;a++)
  {
	cout << "Please enter the population for island #: " << a+1 << endl;
    cin >> peopleNum[a];
  }
  //get the total overall population
  for(int a=0;a<islandsNum;a++)
  {
	  populationT += peopleNum[a];
  }
  cout << "Total population: " << populationT << endl;
 
  cout << "Please enter the length of the infected period (in days)" << endl;
  cin >> infectedPeriod;
  infectedtemp = infectedPeriod;
  
  cout << "Please enter the length of the infectious period (in days)" << endl;
  cin >> infectiousPeriod;
  infectioustemp = infectiousPeriod;
  
  cout << "Please enter the transmission probability for the disease. (This number will be a percentage.)" << endl;
  cin >> transProb;
  
  cout << "Please enter the maximum number of contacts a person can make every day." << endl;
  cin >> rateContact;
  
  cout << "Please enter the number of people that will be initially infected." << endl;
  cin >> numInfected;
  
   //initial people that are healthy
  numHealthy = populationT - numHealthy;

  island = new islands*[islandsNum];  //dynamic array for island class
  for(int a=0;a<islandsNum;a++)
  {
	  island[a] = new islands(peopleNum[a],humanID,infectedPeriod,infectiousPeriod,rateContact,infectedtemp,infectioustemp);
  }
  
  createInfected(numInfected,islandsNum,island);  //function to create the initial infected humans
  
  while(count != 0)  //while loop runs until there are no more infected/infectious humans
  {
	  count = transmit(transProb, dayz, numInfected, numInfectious, numHealthy, numRecovered, islandsNum, island); //main function that transmits the disease
  }
  for(int a=0;a<islandsNum;a++)
  {
	  delete island[a];  //free the island array memory
  }
  delete [] peopleNum;  //free the number of people array memory
  delete [] island;  //free the island array memory
  
  return 0; 
}

int transmit(int transProb,int &dayz,int &numInfected,int &numInfectious,int &numHealthy,int &numRecovered,int &islandsNum,islands **island) //function transmits the disease through the population
{
	int count =0; 
	for(int a=0;a<islandsNum;a++) //for loop runs through each island to create contacts between humans and transmit the disease
	{
		count = island[a]->createContacts(transProb,dayz);
	}
	if(count >0) //used to determine when the program will stop
	{
		return -1;
	}
	else
	{
		return 0;
	}
}

void createInfected(int numInfected, int islandsNum, islands **island) //function creates the initial infected humans
{
	int count =-1;
	for(int x=0;x<numInfected;x++) //for loop loops until the number of infected people has been reached
	{
		while(count !=0)
		{
			int tempIslandN = rand() % islandsNum; //variable will hold a temporary number for a random island
			std::cout << "Temp island num: " << tempIslandN << std::endl;
			int tempHumanN = rand()% (island[tempIslandN]-> populationN -1);  //variable will hold a temporary number for a random human
			if(island[tempIslandN]->getHumanStatus(tempHumanN) == "Healthy") //If the random human is healthy, make him infected
			{
				island[tempIslandN]->becomeInfected(tempHumanN); //calling function to make the human infected
				count =0;
			}
			else
			{
				count =-1;
			}
		}
	}
}
