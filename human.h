/* Header file for the human population class. */
#include <iostream>
#include <cstdlib>


class human //human class that holds an individuals information and functions
{
  public:
  int id;  //variable holds the individual humans id
  int daysinfectedcount;  //variable holds the total number of days infected
  int daysinfectiouscount;  //variable holds the total number of days infectious
  int daysinfected;  //variable holds the number of days infected a human has been
  int daysinfectious; //variable holds the number of days infectious a human has been
  int daysrecovered; //variable holds the number of days recovered a human has been
  int infectedMax;  //max number of people infected
  int infectiousMax;  //max number of people infectious
  std::string hStatus;  //variable holds the human's health status
  
  human(int &humanID, int numinfected, int numinfectious, int infectedtemp, int infectioustemp) //constructor
  { 
  	hStatus = "Healthy";
	id = humanID;
	humanID++;
  	daysinfectedcount = numinfected;
	daysinfectiouscount = numinfectious;
	infectedMax = infectedtemp;
	infectiousMax = infectioustemp;
  }
  void becomeInfected() //function makes a human infected
  {
	hStatus = "Infected";
	daysinfected =1;
	std::cout << "Human #: " << id << " has become infected." << std::endl;
  }
  void becomeInfectious() //function makes a human infectious
  {
	hStatus = "Infectious";
	daysinfectious = 1;
    std::cout << "Human #: " << id << " has become infectious." << std::endl;
  }
  void becomeRecovered() //function makes a human recovered
  {
	hStatus = "Recovered";
	daysrecovered=1;
	std::cout << "Human #: " << id << " has now recovered." << std::endl;
  }
  
  void statusChange() //changes a humans status from infectious to recovered
  {
	  daysinfectious = daysinfectious +1;
	  if(daysinfectious >= infectiousMax)
	  {
		  hStatus = "Recovered";
	  }
  }
  
  void statusChange2() //changes a humans status from infected to infectious
  {
	  daysinfected = daysinfected +1;
	  if(daysinfected >= infectedMax)
	  {
		  hStatus = "Infectious";
	  }
  }
	  
	  
  void showDaysInfected() //changes the number of days infected to 0
  {
	if(daysinfected > 0)
	{
		if(daysinfected < daysinfectedcount)
		{
			daysinfected++;
		}
		else if(daysinfected == daysinfectedcount)
		{
			daysinfected = 0;
			hStatus = "Recovered";
		}
	}
  }
  void showDaysInfectious() //changes the number of days infectious to 0
  {
	if(daysinfectious > 0)
	{
		if(daysinfectious < daysinfectiouscount)
		{
			daysinfectious++;
		}
		else if(daysinfectious == daysinfectiouscount)
		{
			daysinfectious = 0;
			hStatus = "Recovered";
		}
	}
  }
};
