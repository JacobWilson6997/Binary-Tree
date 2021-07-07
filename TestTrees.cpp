#include "binarytree.h"
#include "iostream"
#include <fstream>
//#include <ctime>



BinaryTree createTree(std::string file) {
	std::vector<int> pulledFile;
	std::fstream myFile(file, std::ios_base::in);

	int num;
	while (myFile >> num)
	{
		pulledFile.push_back(num);
	}
	
	myFile.close();
	//pulledFile.push_back(50);
	//pulledFile.push_back(30);
	//pulledFile.push_back(70);
	//pulledFile.push_back(20);
	//pulledFile.push_back(40);
	//pulledFile.push_back(60);
	//pulledFile.push_back(80);
	BinaryTree tree;
	for (int i = 0; i < pulledFile.size(); i++) {
		tree.insert(pulledFile[i]);
	}
	//tree.printTree();
	return tree;
}

int main()
{	
	BinaryTree tree;
	std::ofstream outputFile;
	outputFile.open("output.txt");
	std::vector<int> output;
	std::vector<int> empty;

	while (true) {
		std::cout << "Choose the option to be performed:\n" <<
					 "1. Create_Tree\n" <<
					 "2. Insertion\n" <<
					 "3. Deletion\n" <<
					 "4. Search\n" <<
					 "5. Traversal\n" <<
					 "6. Delete_Tree\n" <<
					 "7. Check_Balance\n" << std::endl;
		int input;
		int input2;
		std::cin >> input;

		if (input == 1) {
			std::cout << "Input name of text file." << std::endl;
			std::string input3;
			std::cin >> input3;
			tree.fall();
			output = empty;
			tree = createTree(input3);
			output = tree.printOrder(tree.root, 1, empty);
			std::cout << "Created Tree: ";

		} else if (input == 2) {
			std::cout << "input new node" << std::endl;
			std::cin >> input2;
			if (tree.find(tree.root, input2) == NULL) {
				tree.insert(input2);
				output = tree.printOrder(tree.root, 1, empty);
			}
			else {
				std::cout << "Node already exists." << std::endl;
			}
		} else if (input == 3) {
			std::cout << "Input node to delete." << std::endl;
			std::cin >> input2;
			TreeNode *cur = tree.find(tree.root, input2);
			tree.deleteNode(cur);
			std::cout << "Delete Tree: Tree Deleted" << std::endl;
			outputFile << "Delete Tree: Tree Deleted" << std::endl;
			continue;
		} else if (input == 4) {
			std::cout << "Input node to search.";
			std::cin >> input2;
			TreeNode* cur = tree.find(tree.root, input2);
			int level = 0;
			while(cur->parent != NULL) {
				cur = cur->parent;
				level++;
			}
			std::cout << "Position: " << level << std::endl;
			outputFile << "Position: " << level << std::endl;
			continue;
		} else if (input == 5) {
			std::cout << "Which order should the tree be printed in?\n" << 
						 "1.Pre_order\n" <<
						 "2.In_order\n" <<
						 "3.Post_order\n" << std::endl;
			std::cin >> input2;
			if (input2 == 1) {
				std::cout << "Printing pre order" << std::endl;
				outputFile << "Printing pre order" << std::endl;
			}else if (input2 == 2) {
				std::cout << "Printing in order" << std::endl;
				outputFile << "Printing in order" << std::endl;
			}else if (input2 == 3) {
				std::cout << "Printing post order" << std::endl;
				outputFile << "Printing post order" << std::endl;
			}
			tree.printOrder(tree.root, input2, empty);
			std::cout << std::endl;
		} else if (input == 6) {
			tree.fall();
			std::cout << "Tree Deleted" << std::endl;
			outputFile << "Tree Deleted" << std::endl;
			continue;
		} else if (input == 7) {
			int balanceFactor = tree.findBalanceFactor(tree.root);
			std::cout << "Check Balance: " << balanceFactor << std::endl;
			if (balanceFactor != 1 && balanceFactor != 0) {
				std::cout << "Balancing Tree" << std::endl;
				outputFile << "Balancing Tree" << std::endl;
				tree.root = tree.balanceTree(tree.root);
				output = tree.printOrder(tree.root, 1, empty);
			}
		}
		for (int i = 0; i < output.size(); i++) {
			std::cout << output[i] << " ";
			outputFile << output[i] << " ";
		}
		outputFile.close();
		std::cout << std::endl;
	}
}





























//const int COUNT = 10;  // size of tree
//const int MAXELE = 100;
//BinaryTree<int> tree1(0, MAXELE);
//BinaryTree<int> tree2(0, MAXELE);
//BinaryTree<int> tree3(0, MAXELE);
//BinaryTree<int> tree4(0, MAXELE);
//BinaryTree<int> tree5(0, MAXELE);


//int values[] = { 10,25,5,8,6,1,30,50,22,11,19,42,3,12,13,36,37,38 };
//int size = sizeof values / sizeof(int);

//for (int i = 0; i < size; i++) {
//	tree1.insert(values[i]);
//}
//tree1.printTree("Tree 1");
//std::cout << tree1.getFirst();
//
//int x;
//srand((int)time(0));
//for (int i = 0; i < COUNT; i++) {
//  tree2.insert(x=rand() % MAXELE);
//}
//tree2.printTree("Random tree");
//
//tree2.printShort("\nList of Keys: ");

//tree2.fall();
//tree2.printTree("\n Tree with Leaves Removed");

///* You can solve this however you want.  The problem is I really don't want my main program to see pointers, but I need to have a current pointer that keeps 
//moving throug the tree.  This code assumes a "current Node" is saved inside the tree.  getFirst sets is.  successor also sets it.  */
//tree1.getFirst();
//std::cout << "starting at " << tree1.getCurrNodeValue()<< std::endl;
//for (int i = 0; i < 10; i++)
//{   tree1.successor();  //Successor sets a class variable which is the successor node
//    std::cout <<  "The next sucessor is " << tree1.getCurrNodeValue() << std::endl;
//}


//tree1.printTree("Tree 3");

//std::cout << "\nclosest common between 1 and 50 " << tree1.closestCommon(1,50);
//std::cout << "\nclosest common between 19 and 22 " << tree1.closestCommon(19, 22);
//std::cout << "\nclosest common between 11 and 30 " << tree1.closestCommon(11, 30);
//std::cout << "\nclosest common between 15 and 30 " << tree1.closestCommon(15, 30);

//tree1.fall();
//tree1.printTree("tree1");
//std::cout << "The width of the tree1 is " << tree1.width() << std::endl;
//tree2.printTree("tree2");
//std::cout << "The width of the tree2 is " << tree2.width() << std::endl;

//tree2.printTree("Tree 2");
//tree2.flip();
//tree2.printTree("Flipped Tree 2");

//// The preOrder definition is the node value, the number of childen it has, followed by the preOrder definition of each child.
//// Thus, this tree is rooted at 8 and has two children.
//int preOrderI[] = {8, 2, 10, 1, 14, 1, 13, 0, 3, 2, 6, 2, 7, 0, 4, 0, 1, 0 };
//tree4.buildFromPreorder(preOrderI);
//tree4.printTree("tree from Preorder");
//tree4.makeEmpty();

//std::cout << "**********\n\n\n";
//int perfectBalanceI[] = { 2,5,7,9,12,14,15,16,21,56,69,80,82,83,84,74,90,95,99 };
//tree4.perfectBalance(perfectBalanceI, 0, sizeof(perfectBalanceI) / sizeof(int) - 1);
//tree4.printTree("Perfect Balance");

//if (tree4.isBST())
//std::cout << "Tree is a BST\n";
//else
//std::cout << "Tree is NOT a BST\n";

//tree4.fall();
//tree4.printTree("Curr Tree");

//if (tree4.isBST())
//std::cout << "Tree is a BST\n";
//else
//std::cout << "Tree is NOT a BST\n";

//tree2.printTree("Tree 2");
//if (tree2.isBST())
//std::cout << "Tree is a BST\n";
//else
//std::cout << "Tree is NOT a BST\n";

//int nodesI[] = {3,5,12,10,11,13,16};
//tree3.perfectBalance(nodesI, 0, sizeof(nodesI)/sizeof(int) -1);
//tree3.printTree("PerfectBalance from keys");

//for (int i = 0; i <COUNT; i++){
//int t = rand()%MAXELE;
//tree5.insert(t);
//}
//tree5.printTree("FindMaxComplete");
//tree5.getMaxCompleteSubtree();

//tree4.printTree("FindMaxComplete");
//tree4.getMaxCompleteSubtree();
//tree3.printTree("FindMaxComplete");
//tree3.getMaxCompleteSubtree();
