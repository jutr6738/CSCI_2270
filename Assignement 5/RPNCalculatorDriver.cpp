/****************************************************************/
/*                  RPN Calculator Driver File                  */
/****************************************************************/
/*      TODO: Implement driver as described in the writeup      */
/****************************************************************/

#include "RPNCalculator.hpp"
#include <iostream>
#include <string>
// you may include more libraries as needed

using namespace std;

/*
 * Purpose: Determine whether some user input string is a
 *          valid floating point number
 * @param none
 * @return true if the string s is a number
 */
bool isNumber(string s)
{
    if(s.size() == 1 && s == "-") return false;
    else if(s.size() > 1 && s[0] == '-') s = s.substr(1);

    bool point = false;
    for(int i = 0; i < s.size(); i++)
    {
      if(!isdigit(s[i]) && s[i] != '.') return false;
      if(s[i]=='.' and !point) point = true;
      else if(s[i]=='.' and point) return false;
    }

    return true;
}


int main()
{
  RPNCalculator calc;
  string input;

  cout << "Enter the operators and operands ('+', '*') in a postfix format" << endl;

  while(true)
  {
    cout << "#> ";
    getline(cin, input);
   
      if (isNumber(input))
      {
        calc.push (stof(input));
      }
      else if(input == "=")
      {
        if (calc.isEmpty())
        {
          cout << "No operands: Nothing to evaluate" << endl;
          return 0;
        }

        break;
      }

      else
      {
       calc.compute(input);
      }

  }

if (!calc.isEmpty())
{
  float final= calc.peek()->number; 
  calc.pop();
  if (!calc.isEmpty())
  {
    cout << "Invalid expression" << endl;
  }
  else{
    cout << final; 
  }
}

  return 0;
}
