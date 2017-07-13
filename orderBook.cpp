#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <unordered_set>
#include <unordered_map>
#include <vector>
using namespace std;

class orderBook
{
  public:
  explicit orderBook(string);
  void showDeleteOrderId() const;
  void buildBook() const;

  private:
  unordered_set<string> deleteOrderId;
  string bookFileName;
  string delimiter = "|";
};

// function to initialize list of orderId for Delete operation using unordered set
// the set will be used later to remove its Add operation counterpart
orderBook::orderBook(string orderBookFileName)
    : bookFileName(orderBookFileName)
{
  string inputLine;
  ifstream myFile;
  myFile.open(bookFileName);
  while(getline(myFile, inputLine))
    {
      stringstream ss(inputLine);
      string word;
      vector<string> parsedLine;
      while(getline(ss, word, '|'))
        {
          parsedLine.push_back(word);
        }
      if(parsedLine[1] == "D")
        {
          deleteOrderId.insert(parsedLine[2]);
        }
    }
  myFile.close();
}

void orderBook::buildBook() const
{
  unordered_map<string, int> sizeMap; // keep track of order size
  unordered_map<string, int> countMap; // keep track of order count
  string inputLine;
  ifstream myFile;
  myFile.open(bookFileName);
  while(getline(myFile, inputLine))
    {
      stringstream ss(inputLine);
      string word;
      vector<string> parsedLine;
      while(getline(ss, word, '|'))
        {
          parsedLine.push_back(word);
        }
      if(parsedLine[1] == "D") // ignore Delete op as we've already processed them during init
        {
          continue;
        }
      else if(parsedLine[1] == "A") // ignore Add op corresponding to Delete op
        {
          auto found = deleteOrderId.find(parsedLine[3]);
          if(found != deleteOrderId.end())
            {
              continue;
            }
        }
      // key = symbol|side|price
      string key = parsedLine[0] + delimiter + parsedLine[2] + delimiter + parsedLine[5];
      sizeMap[key] += stoi(parsedLine[4]);
      countMap[key]++;
    }
  myFile.close();

  // print out the book by going through the sizeMap and countMap
  for(auto it = sizeMap.begin(); it != sizeMap.end(); ++it)
    {
      cout << it->first << "|" << it->second << "|" << countMap[it->first] << endl;
    }
}

void orderBook::showDeleteOrderId() const
{
  for(string s : deleteOrderId)
    {
      cout << s << endl;
    }
}

int main()
{
  orderBook myBook("orderBookInput.txt");
  // myBook.showDeleteOrderId();
  myBook.buildBook();
}
