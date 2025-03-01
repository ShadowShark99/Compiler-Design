#include <iostream>
#include <string>
#include <fstream>
#include <vector>
using namespace std;

bool isReserved(string token)
{
  const string RESERVED[6] = {"TAGS", "BEGIN", "SEQUENCE", "INTEGER", "DATE", "END"};
  for (int i = 0; i < 6; i++)
  {
    if (token == RESERVED[i])
    {
      return true;
    }
  }
  return false;
}

bool isWhiteSpace(char c)
{
  const int WHITESPACE[6] = {32, 9, 10, 13, 11, 12};
  if (c < 0)
    return true;
  for (int i = 0; i < 6; i++)
  {
    if (c == WHITESPACE[i])
    {
      return true;
    }
  }
  return false;
}

bool hyphenRules(string token)
{
  int n = token.size();
  if (token[n - 1] == '-')
  {
    return false;
  }
  char prev = token[0];
  for (int i = 1; i < n; i++)
  {
    if (token[i] == '-' && prev == '-')
    {
      return false;
    }
    prev = token[i];
  }
  return true;
}

bool isNum(string token)
{
  int n = token.size();
  for (int i = 0; i < n; i++)
  {
    if (token[i] < 48 || token[i] > 57)
    {
      return false;
    }
  }
  return true;
}

void printTokenType(string token, bool &programSuccess)
{
  int n = token.size();
  if (isReserved(token))
  {
    cout << token << " is a " << "Reserved Word" << endl;
  }
  else if (token[0] >= 65 && token[0] <= 90 && hyphenRules(token))
  {
    cout << token << " is a " << "TypeRef" << endl;
  }
  else if (token[0] >= 97 && token[0] <= 122 && hyphenRules(token))
  {
    cout << token << " is a " << "Identifier" << endl;
  }
  else if (token[0] >= 49 && token[0] <= 57 && isNum(token)) // first char is not 0
  {
    cout << token << " is a " << "Number" << endl;
  }
  else if (token == "::=")
  {
    cout << token << " is a " << "ASSIGN" << endl;
  }
  else if (token == "..")
  {
    cout << token << " is a " << "Range_Seperator" << endl;
  }
  else if (token == "{")
  {
    cout << token << " is a " << "LCURLY" << endl;
  }
  else if (token == "}")
  {
    cout << token << " is a " << "RCURLY" << endl;
  }
  else if (token == ",")
  {
    cout << token << " is a " << "COMMA" << endl;
  }
  else if (token == "(")
  {
    cout << token << " is a " << "LPAREN" << endl;
  }
  else if (token == ")")
  {
    cout << token << " is a " << "RPAREN" << endl;
  }
  else if (token == "|")
  {
    cout << token << " is a " << "VERTICAL LINE" << endl;
  }
  else
  {
    cout << token << " is a " << "Invalid Token" << endl;
    programSuccess = false;
  }
}

int main()
{
  // const string RESERVED[6] = {"TAGS", "BEGIN", "SEQUENCE", "INTEGER", "DATE", "END"};
  const string TOKENS[10] = {"Range_Seperator", "ASSIGN", "LCURLY", "RCURLY", "COMMA", "LPAREN", "RPAREN", "TypeRef", "Identifier", "Number"};
  // const int WHITESPACE[6] = {32, 9, 10, 13, 11, 12};
  const string Range_Seperator = "..";
  const string ASSIGN = "::=";
  const string LCURLY = "{";
  const string RCURLY = "}";
  const string COMMA = ",";
  const string LPAREN = "(";
  const string RPAREN = ")";
  cout << "Enter the program file name: " << endl;
  ifstream inFS;
  string program;
  cin >> program;
  inFS.open(program);

  bool programSuccess = true;
  while (!inFS.is_open())
  {
    cout << "Could not open file\n Enter a new file:" << endl;
    cin >> program;
    inFS.open(program);
  }

  while (!inFS.eof())
  {
    string line;
    getline(inFS, line);
    int n = line.size();
    // cout << "the line is " << n << " characters long" << endl;
    string token = "";
    // vector<string> tokens;
    for (int i = 0; i < n; i++)
    {
      if (isWhiteSpace(line[i]))
      {

        if (token != "")
        {
          // cout << "token size is " << token.size() << endl;
          // cout << token << endl;
          // cout << ((token == "items") ? "\n\n\nitems found\n\n\n" : "");
          // tokens.push_back(token);
          printTokenType(token, programSuccess);
          if (!programSuccess)
          {
            break;
          }
        }
        token = "";
      }
      else
      {
        // string itemstest = "\n\n\nitems found\n" + to_string(line[i]) + "\n\n\n";
        // cout << ((token == "items") ? itemstest : "");
        token += line[i];
      }
    }
    if (token != "")
    {
      // cout << "token size is " << token.size() << endl;
      // cout << token << endl;
      // tokens.push_back(token);
      bool commaAtEnd = false;
      int n = token.size();
      if (n > 1 && token[n - 1] == ',')
      {
        token = token.substr(0, n - 1);
        commaAtEnd = true;
      }
      printTokenType(token, programSuccess);
      if (commaAtEnd)
      {
        printTokenType(",", programSuccess);
      }
    }
    if (!programSuccess)
    {
      break;
    }
  }

  cout << (programSuccess ? "SUCCESS" : "FAILURE") << endl;
  return 0;
}