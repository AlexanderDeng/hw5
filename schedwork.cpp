

#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
// add or remove necessary headers as you please
#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID 
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;


// Add prototypes for any helper functions here

bool schedHelper(const AvailabilityMatrix& avail, DailySchedule& sched, const size_t dailyNeed, const size_t maxShifts, unsigned int row, unsigned int col, std::vector<int>& tracker);

bool noRepeats(DailySchedule& vec, unsigned int p, unsigned int dailyNeed, unsigned int q); 

// Add your implementation of schedule() and other helper functions here

bool schedule(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched
)
{
    if(avail.size() == 0U){
        return false;
    }
    sched.clear();
    for (unsigned int i = 0; i < avail.size(); i++)
    {
        std::vector<Worker_T> schedCol;
        for (unsigned int k = 0; k < dailyNeed; k++)
        {
            schedCol.push_back(INVALID_ID); 
        }
        sched.push_back(schedCol); 
    }
    std::vector<int> tracker;  
    for (unsigned int i = 0; i < avail[0].size(); i++)
    {
        tracker.push_back(maxShifts); 
    }
    return schedHelper(avail, sched, dailyNeed, maxShifts, 0, 0, tracker); 
}

bool schedHelper(const AvailabilityMatrix& avail, DailySchedule& sched, const size_t dailyNeed, const size_t maxShifts, unsigned int row, unsigned int col, std::vector<int>& tracker)
{
    if (row == avail.size() - 1 && col == dailyNeed)
    {
      return true; 
    }
    if (col == dailyNeed)
    {
      row++;
      col = 0;
    } 

    if (sched[row][col] != INVALID_ID) //if position already filled 
    {
        return schedHelper(avail, sched, dailyNeed, maxShifts, row, (col + 1), tracker); //recurse and advance 
    }
    for (unsigned int i = 0; i < avail[0].size(); i++)
    {
      sched[row][col] = i; //tries all nurses at that slot 
      tracker[i] -= 1;   
      if(avail[row][i] == 1 && tracker[i] >= 0 && noRepeats(sched, row, dailyNeed, i)) //if valid
      {
        if (schedHelper(avail, sched, dailyNeed, maxShifts, row, (col + 1), tracker))
        {
          return true; 
        }
      }
      tracker[i] += 1;
      sched[row][col] = INVALID_ID; //reset if not valid path 
    }
    return false;
}

bool noRepeats(DailySchedule& sched, unsigned int p, unsigned int dailyNeed, unsigned int q) 
{
    unsigned int count = 0; 
    for (unsigned int i = 0; i < dailyNeed; i++) 
    {
        if (sched[p][i] == q)
        {
            ++count; 
        }
        if (count != 1 && count != 0) //this means that a duplicate has been placed
        {
            return false; 
        }
    }
    return true; 
}




//x at sched[3][1] should correspond to a 1 at avail[3][x]
//x at sched[2][1] should correspond to a 1 at avail[2][x] 