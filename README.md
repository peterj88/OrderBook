The purpose of the program is to process open (limit) order book, giving a set of "A"dd and "D"elete operation. 
This is done in a batch fashion.<br>
The input is a flat file, pipe delimited.
The output would be level-2 book with total size and order count at each price level.

Example input file, (Symbol,Operation,Side,OrderId,OrderSize,Price): <br>
ABB|A|S|123456|5000|21.1300<br>
ABB|D|123456<br>
IBM|A|B|123457|1000|100.0000<br>
IBM|A|B|123458|1000|100.0000<br>

Expected output would be:

IBM|B|100|2000|2

Explanation of output:
The Add and Delete operation cancel out the ABB symbol.
IBM has 2 order totaling 2000 shares at price of 100.000 on Buy side

Program note:
Program is written in modern C++. C++ 11 or newer is required to compile this program.
The input file is assumed to be in the same directory as executable.
The input file is assumed to be named "orderBookInput.txt".
