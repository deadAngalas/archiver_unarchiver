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

struct Node
{
  char data;
  int freq = 0;
  string code;
  Node *left = NULL;
  Node *right = NULL;
};

void PrintTree(Node *cur, int padding = 0)
{
  if(cur != NULL)
  {
    PrintTree(cur->right, padding+=5);
    cout << setw(padding) << "[" << cur->freq << ","  << cur->data << "]" << endl;
    PrintTree(cur->left, padding);
  }
}

class Huffman
{
  Node* arr;
  int uniqueCount = 0;
public:
  void SymbolRepetition();
  void ArraySort();
  int get_uniqueCount();
  Node* get_arr();
  void CreateTree();
  void TravelTree(Node* root, string code);
};

int Huffman::get_uniqueCount()
{
  return uniqueCount;
}

Node* Huffman::get_arr()
{
  return arr;
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

  char* tempSym = new char[N];
  char* tempFreq = new char[N];

  for(int k = 0; k < N; k++)
  {
    tempFreq[k] = 0;
  }

  for(int i = 0; i < fileSize; i++)
  {
    char currentChar = content[i];
    bool charFound = false;
    bool isStop = false;
    // check there is or not this symbol in array
    for(int j = 0; j < uniqueCount && isStop == false; j++)
    {
      if(tempSym[j] == currentChar)
      {
        charFound = true;
        tempFreq[j]++;
        isStop = true;
      }
    }
    // if it is unique symbol -> add it in array
    if(!charFound)
    {
      tempSym[uniqueCount] = currentChar;
      tempFreq[uniqueCount]++;
      uniqueCount++;
    }
  }

  arr = new Node[uniqueCount];

  for(int i = 0; i < uniqueCount; i++)
  {
    arr[i].data = tempSym[i];
    arr[i].freq = tempFreq[i];
  }

  delete[] tempFreq;
  delete[] tempSym;
}

void Huffman::ArraySort()
{
  Node buffer;
  int i, j;
  bool isSorted;

  for(i = 0; isSorted == false; i++)
  {
    isSorted = true;
    for(j = 0; j < uniqueCount-1-i; j++)
    {
      if(arr[j].freq > arr[j+1].freq)
      {
        isSorted = false;
        buffer = arr[j];
        arr[j] = arr[j+1];
        arr[j+1] = buffer;
      }
      else if(arr[j].freq == arr[j+1].freq && !arr[j+1].data)
      {
        isSorted = false;
        buffer = arr[j];
        arr[j] = arr[j+1];
        arr[j+1] = buffer;
      }
    }
  }
}

void Huffman::CreateTree()
{
  while(uniqueCount > 1)
  {
    Node* newNode = new Node;
    newNode->freq = arr[0].freq + arr[1].freq;
    newNode->left = new Node(arr[0]);
    newNode->right = new Node(arr[1]);
    newNode->data = '\0';

    Node* tempArr = new Node[uniqueCount-1];

    for (int i = 0; i < uniqueCount - 2; ++i)
    {
      tempArr[i] = arr[i+2];
    }
    delete[] arr;

    tempArr[uniqueCount-2] = *newNode;

    arr = new Node[uniqueCount-1];
    arr = tempArr;

    uniqueCount--;
    ArraySort();
  }
}

void Huffman::TravelTree(Node* cur, string code)
{
  if (cur != nullptr)
  {
    if (cur->data)
    {
      cur->code = code;
    }
    TravelTree(cur->left, code + "0");
    TravelTree(cur->right, code + "1");
  }
}

void CodeTableCreation(Node* cur, string Codes[], char Symbol[], int Frequency[], int& i)
{
  if(cur != nullptr)
  {
    if(cur->data)
    {
      Codes[i] = cur->code;
      Symbol[i] = cur->data;
      Frequency[i] = cur->freq;
      i++;
    }
    CodeTableCreation(cur->left, Codes, Symbol, Frequency, i);
    CodeTableCreation(cur->right, Codes,Symbol, Frequency, i);
  }
}

void CodeTableOutput(Node* cur, string Codes[])
{
  if(cur != nullptr)
  {
    if(cur->data)
    {
      cout << "Character: [" << cur->data << "]" << " Code: [" << cur->code << "]" << endl;
    }
    CodeTableOutput(cur->left, Codes);
    CodeTableOutput(cur->right, Codes);
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

void CompressFile(int count, string Codes[], char Symbol[], int& bitRemains, int& byteCount)
{
  ifstream original;
  ofstream compressed;

  original.open("t1.txt");

  if(!original)
  {
    cerr << "File is not opened!";
    system("pause>nul");
    exit(1);
  }

  compressed.open("t2.bin", ios::binary);

  if(!compressed)
  {
    cerr << "File is not created!";
    system("pause>nul");
    exit(1);
  }

  original.seekg(0, ios::end);
  int fileSize = original.tellg();
  original.seekg(0, ios::beg);

  char content[fileSize + 1];

  original.read(content, fileSize);
  original.close();
  content[fileSize] = '\0';

  bool charIsFound;

  char buffer = 0;   // Buferis bitu uzkrāšanai
  int bufferCount = 0; // Bitu skaitīšana buferī

  for(int i = 0; i < fileSize; i++)
  {
    char currentChar = content[i];
    bool charIsFound = false;

    for(int j = 0; j < count && charIsFound == false; j++)
    {
      if(currentChar == Symbol[j])
      {
        string CodeForChar = Codes[j];
        charIsFound = true;

        // nem katru elementu no CodeForChar in bit
        for(char bit : CodeForChar)
        {
          buffer <<= 1; // bitu nobide pa kreisi par 1 poziciju - To izmanto, lai atbrīvotu vietu jaunam bitam
          buffer |= (bit - '0'); // (bit - '0') bits apzīmē rakstzīmi "0" vai "1"
          /*
          Pārvērš bitu rakstzīmi ('0' vai '1') par veselu skaitli (0 vai 1)
          Tas iestata jaunu bitu bufera galējā labajā pozīcijā.
          */
          bufferCount++; // par cik ir aizpildits buffer

          // ja buffer ir pilns, tad to jaraksta faila
          if (bufferCount == 8)
          {
            byteCount++;
            compressed.put(buffer);
            buffer = 0;
            bufferCount = 0;
          }
        }
      }
    }
  }

  // ja palieka vel biti bufera, tad tos jaierakta fiala
  if(bufferCount > 0)
  {
    buffer <<= (8 - bufferCount);
    compressed.put(buffer);
  }
  bitRemains = bufferCount;

  compressed.close();
  cout << "File is successfully compressed!" << endl;
}

void ReadFromBinFile()
{
  ifstream binaryFile("t2.bin", ios::binary);

  if(!binaryFile)
  {
    cerr << "File is not opened!";
    system("pause>nul");
    exit(1);
  }

  char buffer;
  while(binaryFile.get(buffer))
  {
    for(int i = 7; i >= 0; i--)
    {
      cout << ((buffer >> i) & 1);
    }
  }

  binaryFile.close();
}

void DecompressFile(Node* root, int& bitRemains, int& byteCount)
{
  ifstream compressedFile("t2.bin", ios::binary);
  ofstream decompressedFile("t3.txt");

  if(!compressedFile || !decompressedFile)
  {
    cerr << "File is not opened!";
    system("pause>nul");
    exit(1);
  }

  Node* currentNode = root;

  char buffer;
  int bufferCount = 0;
  int newByteCount = byteCount;

  while(newByteCount > 0)
  {
    compressedFile.get(buffer);
    for(int i = 7; i >= 0; i--)
    {
      int bit = (buffer >> i) & 1;
      if(bit == 0)
      {
        currentNode = currentNode->left;
      }
      else
      {
        currentNode = currentNode->right;
      }
      if(currentNode->left == nullptr && currentNode->right == nullptr)
      {
        decompressedFile.put(currentNode->data);
        currentNode = root;
      }
    }
    newByteCount--;
  }

  if(bitRemains > 0)
  {
    buffer <<= (8 - bitRemains);
    for(int i = 7; i >= (8 - bitRemains); i--)
    {
      int bit = (buffer >> i) & 1;
      if(bit == 0)
      {
        currentNode = currentNode->left;
      }
      else
      {
        currentNode = currentNode->right;
      }
      if(currentNode->left == nullptr && currentNode->right == nullptr)
      {
        decompressedFile.put(currentNode->data);
        currentNode = root;
      }
    }
  }

  compressedFile.close();
  decompressedFile.close();

  cout << "File was successfully decompressed!" << endl;
}

void ReadFromDecompressed()
{
  ifstream decompressed("t3.txt");

  if (!decompressed)
  {
    cerr << "File is not opened!";
    system("pause>nul");
    exit(1);
  }

  string str;
  cout << "\tDecompressed file`s content:\n" << endl;
  while(!decompressed.eof())
  {
    getline(decompressed, str);
    cout << str;
  }

  decompressed.close();
}

int main()
{
  Huffman huf;
  huf.SymbolRepetition();
  huf.ArraySort();
  int count = huf.get_uniqueCount();
  char Symbol[count];
  int Frequency[count];
  string Codes[count];

  for(int i = 0; i < count; i++)
  {
    Symbol[i] = huf.get_arr()[i].data;
    Frequency[i] = huf.get_arr()[i].freq;
  }

  int i = 0;
  huf.CreateTree();
  huf.TravelTree(new Node(huf.get_arr()[0]), "");
  CodeTableCreation(new Node(huf.get_arr()[0]), Codes, Symbol, Frequency, i);

  enum KEYS { num1 = 49, num2 = 50, num3 = 51 , num4 = 52, num5 = 53, num6 = 54, num7 = 55, num8 = 56, num9 = 57 };
  // num10 = 45, num11 = 61, num12 = 112
  /*
  num10 = 45; it is   -
  num11 = 61; it is   =
  num12 = 112; it is  p
  */
  int choice;
  int isEncrypted = 0, isDecrypted = 0;
  int bitRemains = 0;
  int byteCount = 0;

  system("cls");
  cout << "\n\tArchiver & Unarchiver\n\n";
  cout << "\n Author: Vladislav Ryazancev\n Ver: 3.3.1\n Date (start): 24.11.2023 / 12:01\n Date (end): 07.12.2023 / 10:49\n\n";

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
      cout << "5. Tree\n";
      cout << "6. Code table\n";
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
          if(isEncrypted == 1)
          {
            ReadFromBinFile();
          }
          else cout << "There is no encrypted file!" << endl;
          break;
        }
        case num3:
        {
          if(isDecrypted == 1)
          {
            ReadFromDecompressed();
          }
          else cout << "There is no encrypted file!" << endl;
          break;
        }
        case num4:
        {
          for(int i = 0; i < count; i++)
          {
            cout << "Character: [" << Symbol[i] <<  "], Count: " << Frequency[i] << endl;
          }

          break;
        }
        case num5:
        {
          cout << "\tHuffman Tree:\n\n";
          PrintTree(new Node(huf.get_arr()[0]));
          break;
        }
        case num6:
        {
          CodeTableOutput(new Node(huf.get_arr()[0]), Codes);
          break;
        }
        case num7:
        {
          isEncrypted++;
          CompressFile(count, Codes, Symbol, bitRemains, byteCount);
          break;
        }
        case num8:
        {
          isDecrypted++;
          DecompressFile(new Node(huf.get_arr()[0]), bitRemains, byteCount);
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
