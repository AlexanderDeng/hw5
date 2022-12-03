// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#include "wordle.h"
#include "dict-eng.h"
#include <string>
using namespace std;


// Add prototypes of helper functions here

void solveHelper(std::string& in, std::string& floating, const std::set<string>&dict, int dashes, unsigned int position, std::set<std::string>& foundWords); 

bool containsFloating(std::string& in, std::string& floating); 

// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
  string inCopy = in; 
  string floatingCopy = floating; 
  std::set<std::string> foundWords; 
  int dashCount = 0; 
  for (unsigned int k = 0; k < inCopy.length(); k++) //this just counts the number of dashes
  {
    if (inCopy[k] == '-')
    {
      dashCount++; 
    }
  }
  solveHelper(inCopy, floatingCopy, dict, dashCount, 0, foundWords); 
  return foundWords; 
}

// Define any helper functions here

void solveHelper(std::string& in, std::string& floating, const std::set<string>&dict, int dashes, unsigned int position, std::set<std::string>& foundWords)
{
  if (dashes == 0) //if no dashes, all floating characters are in the word, and the word is in dict
  {
    if (containsFloating(in, floating) && dict.find(in) != dict.end())
    {
      foundWords.insert(in); //if all valid requirements then insert the word in the set 
      return; 
    }
    else //if no dashes but either floating letters haven't all been used or not a word, it's not valid and just return
    {
      return; 
    }
  }
  else if (in[position] == '-') //if current letter needs to be filled 
  {
    for (char letter = 'a'; letter <= 'a' + 25; letter++) //try all letters  
    {
      in[position] = letter; //try all letters 
      solveHelper(in, floating, dict, dashes - 1, position + 1, foundWords); 
      in[position] = '-'; //reset 
    }
  }
  else if (dashes > 0 && position < in.length() - 1)
  {
    solveHelper(in, floating, dict, dashes, position + 1, foundWords); 
  }
}

bool containsFloating(std::string& in, std::string& floating)
{
  for (unsigned int i = 0; i < floating.length(); i++)
  {
    if (in.find(floating[i]) == string::npos)
    {
      return false; 
    }
  }
  return true; 
}


//isValid(in, floating, dict): if word has no "-", contains the floating and pivot characters, return true

//set solveHelper(in, int = 0): takes the "in" and 0 to start returns a string
//make a copy of in 
  //if isValid, add in to the set, otherwise 
  //if current letter position is a "-" 
    //for loop replacing it with every letter 
    //recursive call with modified copy of in and int++ 
  //otherise, recursive call with int++ 

