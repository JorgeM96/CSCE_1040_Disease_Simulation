   /* Header for the islands class. */
#include <cstdlib>
#include "human.h"
    
class islands   //class that holds information and function for the islands in the nation
{
  public:

  int populationN;  //variable holds the population number
  int humanContacts;  //variable holds the number of contacts humans make
  human **humanPop; //variable is a pointer for the human class
  
  islands(int peopleNum, int &humanID, int infectedPeriod, int infectiousPeriod, int rateContact, int infectedtemp, int infectioustemp) //constructor
  { 
    //setting variable equal to variables passed from main
    humanContacts = rateContact;
	populationN = peopleNum;
	humanPop = new human*[populationN];
	
	for(int a=0;a<populationN;a++) 
	{
		humanPop[a] = new human(humanID, infectedPeriod, infectiousPeriod,infectedtemp,infectioustemp); //human dynamic array
	}
  }
  
  ~islands()  //deconstructor
  {
	  for(int a=0;a<populationN;a++) //freeing memory from dynamic array
	  {
		  delete humanPop[a];
	  }
	  delete [] humanPop;
  }
  
  std::string getHumanStatus(int tempHumanN) //function returns the health status for a human
  {
	  return humanPop[tempHumanN]->hStatus;
  }
  
  void becomeInfected(int tempHumanNum) //function makes a human infected
  {
	  humanPop[tempHumanNum]->becomeInfected();
  }

  int createContacts(int transProb, int &dayz) //Main function that transmits the disease through people making contact with each other
  {
	dayz++;  //this variable increases the day number as the function is called
	std::cout << std::endl << std::endl << "================== Day #: "<< dayz << " =================" << std::endl;
	for(int a=0;a<populationN;a++) //loops until the popularion number has been reached
	{
		for(int b=0;b<humanContacts;b++) //loops until the max number of contacts is reached
		{
			int count = -1;
			while(count!=0)
			{
				int tempN = rand() % populationN; //temporary variable holds a random number
		
				if(humanPop[a]->id != humanPop[tempN]->id) //make sure the two humans are not the same
				{
					//std::cout << "Human's ID #: " << humanPop[a]->id << " is contacting Human ID #: " << humanPop[tempN]->id << std::endl;
					if(humanPop[a]->hStatus == "Infectious" || humanPop[tempN]->hStatus == "Infectious") //if one is infectious there is a chance the other will become infectious
					{
						int tRate = rand() % 100 + 1;
						//std::cout << std::endl << "Transmission probability: " << tRate << std::endl;
						if(tRate <= transProb)
						{
							if(humanPop[a]->hStatus == "Healthy") //infected the other human
							{
								std::cout << "Human ID #: " << humanPop[tempN]->id << " Infected Human ID #: " << humanPop[a]->id << std::endl;
								humanPop[a]->becomeInfected();
							}
							else if(humanPop[tempN]->hStatus == "Healthly") //infected the other human
							{
								std::cout << "Human ID #: " << humanPop[a]->id << "Infected Human ID #: " << humanPop[tempN]->id << std::endl;
								humanPop[tempN]->becomeInfected();
							}
							count = 0;
						}
						else  //tRate was greater therefore noone became infected
						{
							count =0;
						}
					}
					else 
					{
						//std::cout << "Both humans were non-infectious." << std::endl;
						count =0;
					}	
				}
				else
				{
					count = -1;
				}
			}	
		}	
	}

   //variables hold the number of people with the given status
  int healthyNum =0;
  int infectedNum=0;
  int infectiousNum=0;
  int recoveredNum=0;
  
  for(int a=0;a<populationN;a++) //change a humans status to the next level
  {
	  if(humanPop[a]->hStatus == "Infectious")
	  {
		  humanPop[a]->statusChange();
	  }
	  if(humanPop[a]->hStatus == "Infected")
	  {
		  humanPop[a]->statusChange2();
	  }
  }
  
  //This for loop increase the number of people with the given status
  //==========================================================================
  
  for(int a=0;a<populationN;a++)
  {
	  if(humanPop[a]->hStatus == "Healthy")
	  {
		  healthyNum++;
	  }
	   if(humanPop[a]->hStatus == "Infected")
	  {
		  infectedNum++;
	  }
	   if(humanPop[a]->hStatus == "Infectious")
	  {
		  infectiousNum++;
	  }
	   if(humanPop[a]->hStatus == "Recovered")
	  {
		  recoveredNum++;
	  }
  }

  //Cout statements showing the number of humans with their status at the end of each day
  std::cout << std::endl;
  std::cout << "/////////////////////////////////" << std::endl;
  std::cout << "Number of Healthy Humans: " << healthyNum << std::endl;
  std::cout << "Number of Infected Humans: " << infectedNum << std::endl;
  std::cout << "Number of Infectious Humans: " << infectiousNum << std::endl;
  std::cout << "Number of Recovered Humans: " << recoveredNum << std::endl;
  std::cout << "/////////////////////////////////"<< std::endl;
	
  if(infectiousNum > 0 || infectedNum >0) //This program will keep running until there are no more infected/infectious people left
  {
	  return 1;
  }
  else
  {
	  return 0;
  }
 }
};

