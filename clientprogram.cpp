/*

1 November 2018
Description: This is a client program that tests the member functions of abstract
data type Binary Tree. It creates a full tree of height 3 and a degenerate tree of height 4. It also
runs the ordering functions for each tree.
clang++ -std=c++11 client.cpp binarytree.cpp exception.cpp treenode.cpp item.cpp key.cpp -o gotree
*/


#include "binarysearchtree.h"
#include "exception.h"
#include <string>
#include <fstream>
using namespace std;

//opens an input file with a chosen name
//pre filename is assigned
//post if filename exists in the same directory as the program, it is opened
//      with its file pointer at the beginning of the file
//      else an error message is printed
//usage openInputFile(infile, filename);
void openInputFile(ifstream& inputFile);

//opens an output file with a chosen name
//pre filename is assigned
//post if filename exists in the same directory as the program, it is opened
//      with its file pointer at the beginning of the file
//      else an error message is printed
//usage OpenInputFile(outfile, filename);
void openOutputFile(ofstream &outputFile, string filename);


//prints an exception message
//pre except has been thrown
//post except is printed to the screen with two newlines before and after
//usage PrintExceptionMessage(except);
void printExceptionMessage(const Exception& except);

//runs necessary functions for complete tree height 4
//pre: infile exists and aTree exists;
//post: runs make, print, and runOrders
//usage: runCompleteTreeHeight4(infile, aTree);
void createBinarySearchTree(ifstream& infile, BinarySearchTree& aSearchTree, bool& isInitialLoad) throw (Exception);

//runs order traversals
//pre: a tree exists
//post: order traversals are printed for aTree
//usage: runOrders(mytree);
void runOrders(BinaryTree& aTree);

//displays the menu of options and accepts a user's input to execute actions
//pre: a BinarySearchTree exists 
//post: options have been selected and their actions executed until the user chose to exit.
//usage: Menu(aSearchTree);
void Menu(BinarySearchTree& aSearchTree, ifstream& inputFile, bool& isInitialLoad);

//calls the searchForMeaning function on the Binary Search Tree
//pre: A BinarySearchTree exists
//post: The user has entered a textingAbbreviation and it has either been found or the user was told it was not present.
//usage: findFunction(aSearchTree);
void findFunction(BinarySearchTree& aSearchTree);

//calls the addNewEntry function and adds an item into the Binary Search Tree 
//pre: A BinarySearchTree exists and has items in it.
//post: The item that the user has given has been input into the BinarySearchTree
//usage: insertFunction(aSearchTree);
void insertFunction(BinarySearchTree& aSearchTree);

//Gives the inorder reading of all of the items in the Binary Search Tree 
//pre: A BinarySearchTree exists and has entries in it 
//post: All of the entries are printed in inorder fashion on the screen.
//usage: listFunction(aSearchTree);
void listFunction(BinarySearchTree aSearchTree);

//Prints the BinarySearchTree in an aesthetic fashion 
//pre: A BinarySearchTree exists and is non-empty
//post: outputs the tree as in the example below
//
//  					  bar
//                  foo
//                        geeU
//  root ->  queue
//                        stack
//                  list
//                        array
//nodes at the same level are indented the same.
//Viewer must rotate head 90 degrees in order to look like a cs tree
//usage: printPrettyFunction(aSearchTree)
void printPrettyFunction(BinarySearchTree aSearchTree);

//outputs the tree into the associate .dat file
//pre: 
//post: 
//usage: 
void saveFunction(BinarySearchTree& aSearchTree);

//
//
//
//
void rebalanceTree(BinarySearchTree& aBinarySearchTree, bool& isInitialLoad);


int main()
{
	bool isInitialLoad = true;
	ifstream inputFile;
	BinarySearchTree aSearchTree;
	openInputFile(inputFile);
	
	createBinarySearchTree(inputFile, aSearchTree, isInitialLoad);
	inputFile.close();
	Menu(aSearchTree, inputFile, isInitialLoad);
	
    return 0;
}

//opens an input file with a chosen name
//pre filename is assigned
//post if filename exists in the same directory as the program, it is opened
//      with its file pointer at the beginning of the file
//      else an error message is printed
//usage openInputFile(infile, filename);
void openInputFile(ifstream& inputFile)
{
   inputFile.open("dictionary.dat");
   if (inputFile.fail())
   {
      cout << "File failed to open!!!!" << endl;
      exit(1);
   }
}


//opens an output file with a chosen name
//pre filename is assigned
//post if filename exists in the same directory as the program, it is opened
//      with its file pointer at the beginning of the file
//      else an error message is printed
//usage OpenInputFile(outfile, filename);
void openOutputFile(ofstream &outputFile, string filename)
{
    outputFile.open(filename);
    if (outputFile.fail())
    {
        cout << "Failed to open file." << endl;
        exit(1);
    }
}

//prints an exception message
//pre except has been thrown
//post except is printed to the screen with two newlines before and after
//usage PrintExceptionMessage(except);
void printExceptionMessage(const Exception& except)
{
   cout << endl << endl;
   cout << except.what();
   cout << endl << endl;
}

//runs necessary functions for complete tree height 4
//pre: infile exists and aTree exists;
//post: runs make, print, and runOrders
//usage: runCompleteTreeHeight4(infile, aTree);
void createBinarySearchTree(ifstream& inputFile, BinarySearchTree& aSearchTree, bool& isInitialLoad) throw (Exception)
{
	if (isInitialLoad == true) 
	{
		int expectedItems;
		inputFile >> expectedItems;
		for (int i=0; i < expectedItems; i++)
		{
			Item tempItem;
			inputFile >> tempItem;
			try 
			{
				aSearchTree.addNewEntry(tempItem);
			}
			catch (Exception except)
			{
				printExceptionMessage(except);
			}
		}
		isInitialLoad = false;
	}
	else 
	{
		cout << endl;
		
		int expectedItems;
		inputFile >> expectedItems;
		try {
			aSearchTree.rebalance(inputFile, expectedItems);
		}
		catch (Exception except)
		{
			printExceptionMessage(except);
		}
	}
}
	



//displays the menu of options and accepts a user's input to execute actions
//pre: a BinarySearchTree exists and is non-empty
//post: options have been selected and their actions executed until the user chose to exit.
//usage: Menu(aSearchTree);
void Menu(BinarySearchTree& aSearchTree, ifstream& inputFile, bool& isInitialLoad)
{
	char input;
	char newline;
	cout << "Your options are: " << endl;
	cout << "f: find the meaning of a texting abbreviation" << endl;
	cout << "i: insert a new item (texting abbreviation and meaning) into the dictionary" << endl;
	cout << "l: list the items in the entire dictionary on the screen in inorder fashion" << endl;
	cout << "p: print the tree in pretty fashion (showing only the texting abbreviations)" << endl;
	cout << "r: re-balance the tree" << endl;
	cout << "s: save the dictionary to the file in sorted order-inorder--ready to be read" << endl;
	cout << "e: exit the program which automatically does option s" << endl;
	//cout << "d: delete an item from the tree" endl;
	cout << "Enter your option > ";
	cin.get(input);
	cin.get(newline);
	switch (input) 
	{
		case 'f' : 
		{
			findFunction(aSearchTree);
			cout << "\n______________________________" << endl;
			Menu(aSearchTree, inputFile, isInitialLoad);
			break;
		}
		case 'i' : 
		{
			insertFunction(aSearchTree);
			cout << "\n______________________________" << endl;
			Menu(aSearchTree, inputFile, isInitialLoad);
			break;
		}
		case 'l' :
		{	
			listFunction(aSearchTree);
			cout << "\n______________________________" << endl;
			Menu(aSearchTree, inputFile,isInitialLoad);
			break;
		}
		case 'p' :
		{
			printPrettyFunction(aSearchTree);
			cout << "\n______________________________" << endl;
			Menu(aSearchTree, inputFile, isInitialLoad);
			break;
		}
		case 'r' :
		{
			int length;
			rebalanceTree(aSearchTree, isInitialLoad);
			cout << "______________________________" << endl;
			Menu(aSearchTree, inputFile, isInitialLoad);
			break;
		}
		case 's' :
		{
			saveFunction(aSearchTree);
			cout << "______________________________" << endl;
			Menu(aSearchTree, inputFile, isInitialLoad);
			break;
		}
		case 'e' :
		{
			saveFunction(aSearchTree);
			cout << "______________________________" << endl;
			cout << "Thank you" << endl;
			break;
		}
		// case 'd' :
		// {
			// deleteFuntion(aSearchTree);
			// break;
		// }
		default :
		{
			cout << "please enter a valid option" << endl;
			Menu(aSearchTree, inputFile, isInitialLoad);
			break;
		}
	}
}

//calls the searchForMeaning function on the Binary Search Tree
//pre: A BinarySearchTree exists and is non-empty
//post: The user has entered a textingAbbreviation and it has either been found or the user was told it was not present.
//usage: findFunction(aSearchTree);
void findFunction(BinarySearchTree& aSearchTree)
{
	string theKey;
	char newline;
	bool isFound = false;
	Item anItem;
	cout << "What is your desired key?" << endl << ">";
	cin >> theKey ;
	cin.get(newline);
	aSearchTree.searchForMeaning(theKey, anItem, isFound);
	if (isFound)
		cout << anItem << endl;
	else
		cout << "Item was not in binary search tree" << endl;
}

//calls the addNewEntry function and adds an item into the Binary Search Tree 
//pre: A BinarySearchTree exists and is non-empty
//post: The item that the user has given has been input into the BinarySearchTree
//usage: insertFunction(aSearchTree);
void insertFunction(BinarySearchTree& aSearchTree)
{
	char newline;
	Item newItem;
	cout << "enter the item for entry in the format 'texting abbreviation' *new line* 'associated meaning'" << endl;
	cin >> newItem;
	aSearchTree.addNewEntry(newItem);
}

//Gives the inorder reading of all of the items in the Binary Search Tree 
//pre: A BinarySearchTree exists and is non-empty
//post: All of the entries are printed in inorder fashion on the screen.
//usage: listFunction(aSearchTree);
void listFunction(BinarySearchTree aSearchTree)
{
	cout << "Here is the inorder list of the tree" << endl;
	aSearchTree.inorderTraverse(cout);
}

//Prints the BinarySearchTree in an aesthetic fashion 
//pre: A BinarySearchTree exists and is non-empty
//post: outputs the tree as in the example below
//
//  					  bar
//                  foo
//                        geeU
//  root ->  queue
//                        stack
//                  list
//                        array
//nodes at the same level are indented the same.
//Viewer must rotate head 90 degrees in order to look like a cs tree
//usage: printPrettyFunction(aSearchTree)
void printPrettyFunction(BinarySearchTree aSearchTree)
{
	cout << "Here is the stylistic print of the search tree" << endl;
	aSearchTree.prettyDisplay();
}



//outputs the tree into the associate .dat file
//pre: a Binary Search Tree exists
//post: The Binary Search Tree has been written onto dictionary.dat
//usage: saveFunction(aSearchTree, outFile);
void saveFunction(BinarySearchTree& aSearchTree)
{
	cout << "We are saving your Binary Search Tree...." << endl;
	ofstream outFile;
	openOutputFile(outFile, "dictionary.dat");
	aSearchTree.inorderTraverse(outFile);
	outFile.close();
	cout << "SAVED SUCCESSFULLY" << endl;
}

//
//pre: a Binary Search tree exists and is potentially unbalanced
//post: binary search tree is now balanced
//Usage: rebalanceTree(aSearchTree, isInitialLoad);
void rebalanceTree(BinarySearchTree& aBinarySearchTree, bool& isInitialLoad)
{
	cout << "rebalancing tree......" << endl;
	ofstream outFile;
	ifstream inputFile;
	openOutputFile(outFile, "dictionary.dat");
	aBinarySearchTree.inorderTraverse(outFile);
	outFile.close();
	openInputFile(inputFile);
	createBinarySearchTree(inputFile, aBinarySearchTree, isInitialLoad);
	inputFile.close();
	cout << "tree has beem rebalanced" << endl << endl;
}