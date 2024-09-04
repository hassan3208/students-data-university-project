#include <iostream>
#include <fstream>
#include <string>
#include "classes.h"

using namespace std;

int main() {
	avltree tree;
	int choice;
	string filename = "saved_students.csv";


	int numstudents = countrows(filename);
	student* students = structure(filename, numstudents);
	if (students != nullptr) {
		for (int i = 0; i < numstudents; ++i) {
			tree.insert(students[i]);
		}
		delete[] students;
	}
	else
	{
		cout << "\nno student found in record\n";
	}

	while (true) {
		displaymenu();
		cout << "enter your choice: ";
		cin >> choice;

		switch (choice) {
		case 1:
			system("cls");
			insertstudent(tree);
			break;
		case 2:
			system("cls");
			deletestudent(tree);
			break;
		case 3:
			system("cls");
			searchstudent(tree);
			break;
		case 4:
			system("cls");
			cout << "id\tname\t\tmath\tscience\tenglish\thistory\tgeography\tpercentage\n";
			tree.preorder();
			break;
		case 5:
			system("cls");
			update(tree);
			break;
		case 6:
			savefile(tree);
			return 0;
		default:
			cout << "invalid choice, please try again.\n";
		}
	}


	system("pause");
	return 0;
}