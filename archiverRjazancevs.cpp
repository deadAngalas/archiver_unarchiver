#include<iostream>
#include<iomanip>
#include<cstdlib>
#include<conio.h>
#include<fstream>
#define N 256

using namespace std;

void ProgEnd()
{
  system("cls");
  cout << "\n\n\t\t\tCLOSING...\n\n";
  cout <<"              ,---------------------------," << endl;
  cout <<"              |  ---------------------  |"<< endl;
  cout <<"              | |                       | |"<< endl;
  cout <<"              | |   Huffman             | |"<< endl;
  cout <<"              | |      Archiver         | |"<< endl;
  cout <<"              | |          Unarchiver   | |"<< endl;
  cout <<"              | |                       | |"<< endl;
  cout <<"              |  _____________________  |"<< endl;
  cout <<"              |___________________________|"<< endl;
  cout <<"            ,---_____     []     _______------,"<< endl;
  cout <<"            |      ______________           |"<< endl;
  cout <<"        ___________________________________   | ___"<< endl;
  cout <<"        |                                   |   |    )"<< endl;
  cout <<"        |  _ _ _                 [-------]  |   |   ("<< endl;
  cout <<"        |  o o o                 [-------]  |      _)_"<< endl;
  cout <<"        |__________________________________ |       "<< endl;
  cout <<"    -------------------------------------|      ( )"<< endl;
  cout <<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
  cout << endl;
}

class Huffman
{
  char* Symbols;
  int* Frequency;
  int uniqueCount = 0;
public:
  void SymbolRepetition();
  void ArraysSort();
  int get_uniqueCount();
  char* get_Symbols();
  int* get_Frequency();
};

int Huffman::get_uniqueCount()
{
  return uniqueCount;
}

char* Huffman::get_Symbols()
{
  return Symbols;
}

int* Huffman::get_Frequency()
{
 return Frequency;
}

void Huffman::SymbolRepetition()
{
  ifstream original;
  original.open("t1.txt");

  if(!original)
  {
    cerr << "File is not opened!";
    system("pause>nul");
    exit(1);
  }

  original.seekg(0, ios::end); // end file == file size
  int fileSize = original.tellg(); // current position
  original.seekg(0, ios::beg); // return file beginning

  char content[fileSize + 1];

  original.read(content, fileSize);
  original.close();
  content[fileSize] = '\0';

  Symbols = new char[N];
  Frequency = new int[N];

  for(int k = 0; k < N; k++)
  {
    Frequency[k] = 0;
  }

  for(int i = 0; i < fileSize; i++)
  {
    char currentChar = content[i];
    bool charFound = false;
    bool isStop = false;
    // check there is or not this symbol in array
    for(int j = 0; j < uniqueCount && isStop == false; j++)
    {
      if(Symbols[j] == currentChar)
      {
        charFound = true;
        Frequency[j]++;
        isStop = true;
      }
    }
    // if it is unique symbol -> add it in array
    if(!charFound)
    {
      Symbols[uniqueCount] = currentChar;
      Frequency[uniqueCount]++;
      uniqueCount++;
    }
  }
}

void Huffman::ArraysSort()
{
  int step = uniqueCount / 2;
  int bufChar;
  int bufInt;
  int i,j;
  int k = 1;

  while(step > 0)
  {
    for(i = step; i < uniqueCount; i++)
    {
      bufInt = Frequency[i];
      bufChar = Symbols[i];
      for(j = i; j >= step && Frequency[j-step] > bufInt; j = j - step)
      {
        Frequency[j] = Frequency[j-step];
        Symbols[j] = Symbols[j-step];
      }
      Frequency[j] = bufInt;
      Symbols[j] = bufChar;
    }
    step /= 2;
    k++;
  }
}

void OriginalPrint()
{
  ifstream original;
  string str;
  original.open("t1.txt");

  if(!original)
  {
    cerr << "File is not opened!";
    system("pause>nul");
    exit(1);
  }

  cout << "\tOriginal file`s content:\n" << endl;
  while(!original.eof())
  {
    getline(original, str);
    cout << str;
  }

  original.close();
}

struct Node
{
  char data;
  int freq;
  Node *left, *right;
};

Node *CreateNode()
{
  Node *newNode;
  newNode = new Node;
  cout << "\nEnter number to node: ";
  cin >> newNode->data;

  newNode->left = NULL;
  newNode->right = NULL;

  return newNode;
}

void PrintTree(Node *cur, int padding = 0)
{
  if(cur != NULL)
  {
    PrintTree(cur->right, padding+=5);
    cout << setw(padding) << "[" << cur->data << "]" << endl;
    PrintTree(cur->left, padding);
  }
}

int main()
{
  Node *root = NULL;

  Huffman huf;
  huf.SymbolRepetition();
  huf.ArraysSort();

  enum KEYS { num1 = 49, num2 = 50, num3 = 51 , num4 = 52, num5 = 53, num6 = 54, num7 = 55, num8 = 56, num9 = 57 };
  // num10 = 45, num11 = 61, num12 = 112
  /*
  num10 = 45; it is   -
  num11 = 61; it is   =
  num12 = 112; it is  p
  */
  int choice;

  system("cls");
  cout << "\n\tArchiver & Unarchiver\n\n";
  cout << "\n Author: Vladislav Ryazancev\n Ver: 3.3.1\n Date (start): 24.11.2023 / 12:01\n Date (end): xx.11.2023 / 16:13\n\n";

  do
    {
      system("pause>nul");
      system("cls");

      cout << "\n\t\tMENU\n\n";
      cout << "-------------- PRINT --------------\n";
      cout << "1. Original file\n";
      cout << "2. Encrypted file\n";
      cout << "3. Decrypted file\n";
      cout << "4. Frequency table\n";
      cout << "5. Code table\n";
      cout << "6. Tree\n";
      cout << "\n------------- ENCRYPT -------------\n";
      cout << "7. Encrypt file\n";
      cout << "\n------------- DECRYPT -------------\n";
      cout << "8. Decrypt file\n";
      cout << "\n-------------- STOP ---------------\n";
      cout << "9. Stop Program\n\n";
      cout << "-----------------------------------\n\n";

      choice = getch();

      switch(choice)
      {
        case num1:
        {
          OriginalPrint();
          break;
        }
        case num2:
        {

          break;
        }
        case num3:
        {

          break;
        }
        case num4:
        {
          int count = huf.get_uniqueCount();
          for(int i = 0; i < count; i++)
          {
            cout << "Character: [" << huf.get_Symbols()[i] <<  "], Count: " << huf.get_Frequency()[i] << endl;
          }
          break;
        }
        case num5:
        {

          break;
        }
        case num6:
        {
          if(root)
          {
            cout << "Tree elements:\n\n";
            PrintTree(root);
          }
          else cout << "Tree does not exists!\n";
          system("pause>nul");

        }
        case num7:
        {

          break;
        }
        case num8:
        {

          break;
        }
        case num9:
        {
          cout << "\nProgram is stopped! Goodbye!"; ProgEnd(); break;
          break;
        }
        default: cout << "Incorrect input!\n";
      }
    } while(choice != num9);

  system("pause>nul");
  return 0;
}
