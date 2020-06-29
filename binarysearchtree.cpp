// Specification of ADT Dictionary as ADT Binary Search Tree
//     data object: a bunch of texting abbreviations and their meanings 
//     operations: create, destroy
//                 search the dictionary for an item given its text
//                 insert a new item into the dictionary
//                 remove an item from the dictionary given its text
//   associated operations: input and output
// filename binarysearchtree.h
// date October 24, 2018


#include "binarysearchtree.h"
#include <fstream>

// recursive helper functions

// searches a binary search tree for a certain text
// pre: treep is assigned a pointer to a root node of a binary search tree
//      targetText is assigned
// post: if targetText is found in the tree whose root node is treep
//          then the item in the root node is copied into anItem and
//          returns true; otherwise, returns false
// usage: isFound = searchHelper(root, targetText, anItem);
bool searchHelper(TreeNode* treep, const Key& targetText, Item& anItem) throw (Exception)
{
   if (treep != nullptr)
   {
      if (targetText == treep -> item)
      {
         anItem = treep -> item;
         return true;
      } else if (targetText < treep -> item) {
         return searchHelper(treep -> leftChild, targetText, anItem);
      } else {
         return searchHelper(treep -> rightChild, targetText, anItem);
      }
   } else {
      return false;
   }
}


//finds the inorder successor fot the node passed into the function
//pre: a binary search tree exists, is not empty and one of its nodes is passed into the function
//post: the inorder successor item is returned or nullptr is returned
//usage: getInorderSucessorItem(root, anItem);
void getInorderSucessorItem(TreeNode* treep, Item& newItem)
{
	if (treep->leftChild == nullptr)
		newItem = treep->item;
	else
		getInorderSucessorItem(treep->leftChild, newItem);
}
//an Item is added to the correct spot in the binary search tree
//pre: A binary tree exists and an item that will be added into the tree is already chosen
//post: the item has been added into the tree, potentially in the right spot
//addHelper(root, anItem);
void addHelper(TreeNode*& treep, const Item& newItem) throw (Exception)
{
	//figure out where to throw is already there and is full
	if (treep != nullptr)
	{
		if (newItem == treep -> item)
		{
			throw Exception("Item is already in the tree");
		}
		else if (newItem < treep -> item) 
		{
			addHelper(treep -> leftChild, newItem);
		} else 
		{
			addHelper(treep -> rightChild, newItem);
		}
	} 
	else 
	{
		treep = new (nothrow) TreeNode(newItem, nullptr, nullptr);
	}
}


// TreeNode* deleteTreeNode(TreeNode* treep) 
// {
	// if (treep->leftChild == nullptr && treep->rightChild == nullptr)
    // {
        // delete treep;
        // treep = nullptr;
        // return treep;
    // }
    // else if ((treep->leftChild != nullptr && treep->rightChild == nullptr) ||(treep->rightChild != nullptr && treep->leftChild == nullptr))
	// {
		// if (treep->leftChild != nullptr) 
		// {
			// TreeNode *tempPtr = treep->leftChild;
			// delete treep;
			// treep = nullptr;
			// return tempPtr;
		// }
		// else
		// {
			// TreeNode *tempPtr = treep->rightChild;
			// delete treep;
			// treep = nullptr;
			// return tempPtr;
		// }
    // }
    // else
    // {
        // Item newItem;
        // getInorderSucessorItem(treep->rightChild, newItem);
        // treep = deleteHelper(treep, newItem);
        // treep->item = newItem;
        // return treep;
    // }
    // return nullptr;
// }

// TreeNode* deleteHelper(TreeNode* treep, const Key& targetText) throw (Exception)
// {
	// if (treep == nullptr)
	// {
		// throw Exception("your texting abbreviation is not in the binary search tree");
	// }
	// else if (treep->item == targetText)
	// {
		// return deleteHelper(treep);
	// }
	// else if (targetText < treep->item)
	// {
		// TreeNode *temp = deleteHelper(treep->leftChild, targetText);
		// treep->leftChild = temp;
		// return treep;
		
	// else 
	// {
		// TreeNode *tempPtr = deleteHelper(treep->rightChild, targetText);
		// treep->rightChild = tempPtr;
        // return treep;
	// }
	// return treep;
// }


//recursive helper for rebalancing a tree
//pre: rebalance has been called
//post: tree has been rebalanced and is output to file
//usage: root = readTree(inputFile, length);
TreeNode* readTree(ifstream& inputFile, int length) throw (Exception)
{
    if (length != 0)
    {
        TreeNode *leftChild = readTree(inputFile, length / 2);

        Item item;
        inputFile >> item;
        TreeNode *treep = new (nothrow) TreeNode(item, leftChild, nullptr);
        if (treep == nullptr)
        {
            throw Exception("Your computer ran out of memory.");
        }

        treep->rightChild = readTree(inputFile, (length - 1) / 2);

        return treep;
    }
    else
    {
        return nullptr;
    }
}
//recursive helper for inorder traversal
//pre: inorderTraverse has been called
//post: a binary tree is in order
//usage: inorderHelper(output, root);
void inorderHelper(ostream& output, TreeNode *treep)
{
	if (treep != nullptr)
	{
		inorderHelper(output, treep->leftChild);
		output << treep->item;
		inorderHelper(output, treep->rightChild);
	}
}	


// displays a dictionary
// pre: output has been opened if it is a file
//      rightHandSideDictionary has been assigned items
// post: output contains each item on a separate line in the format with headings.

// usage: outfile << myDictionary;    
ostream& operator<< (ostream& output, const BinarySearchTree& rightHandSideDictionary)
{
	return output;
}

// inputs items into a dictionary
// pre: input has been opened if it is a file
//      items are arranged in the following format
//      2
//      lol
//      laugh out loud
//      ttyl
//      talk to you later
// post: if there is room, 
//       all items in the input have been stored in rightHandSideDictionary
// usage: infile >> myDictionary;
istream& operator>> (istream& input, BinarySearchTree& rightHandSideDictionary)
{
	return input;
}

// creates a new dictionary
// post: BinarySearchTree object exists but is empty
// usage: BinarySearchTree myDictionary;	
BinarySearchTree::BinarySearchTree()
{
	numberOfItems = 0;
}

// destroys a dictionary
// pre: BinarySearchTree object exists
// post: all memory for BinarySearchTree object has been freed
// usage: automatically done at the end of scope
BinarySearchTree::~BinarySearchTree()
{
	
}

// searchs for a meaning with a given text
// pre targetText has been assigned a value not already in the hash table
// post if an item with texting abbreviationthe same as targetText is found then
//          isFound is true and theItem is that item
//       else isFound is false
// usage  myDictionary.searchForMeaning(targetText, anItem, isFound);
void BinarySearchTree::searchForMeaning(const Key& targetText, Item& anItem, bool& isFound)
{
	isFound = searchHelper(root, targetText, anItem);
}

// inserts a new text' item into the dictionary
// pre: newItem has been assigned
// post: if there is room in the BinarySearchTree object and newItem's text
//            is not already there then newItem is appropriately added
//       else it throws an exception for either a full dictionary or
//            a message that it is already there
// usage: myDictionary.addNewEntry(myItem, isFull, isAlreadyThere);
void BinarySearchTree::addNewEntry(const Item& newItem) throw (Exception)
{
	addHelper(root, newItem);
	numberOfItems++;
}

// removes the item associated with a given text from the dictionary
// pre: targetText is assigned
// post: if BinarySearchTree object is not empty and 
//           targetText is found in Dictionary object, isFound is true
//           and the associated Item object (text and meaning) has been 
//           removed from the Dictionary object 
//       else isFound is false or isEmpty is true depending
// usage: myDictionary.deleteEntry(myText, isEmpty, isFound);
// void BinarySearchTree::deleteEntry(const Key& targetText, bool& isEmpty, bool& isFound)
// {
	// deleteHelper(root, targetText);
	// numberOfItems--;
// }

//rebalances a binary tree
//pre: a binary tree exists and is potentially unbalanced
//post: binary tree is now balanced
//usage aBinarySearchTree.rebalance(inFile, length);
void BinarySearchTree::rebalance(ifstream& inputFile, const int length) throw (Exception)
{
    root = readTree(inputFile, length);
    numberOfItems = length;
}

//override function of inorder traversal to include output to a file
//pre: aBinarySearchTree exists
//post: tree is output in inorder 
//usage: aBinarySearchTree.inorderTraverse(output);
void BinarySearchTree::inorderTraverse(ostream &output)
{
	output << numberOfItems << endl;
	inorderHelper(output, root);
}