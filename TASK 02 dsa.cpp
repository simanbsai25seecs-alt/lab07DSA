
#include <iostream>
#include <string>
using namespace std;

struct Student {
	int studentID;
	string name;
	float GPA;
	Student* left;
	Student* right;

	Student(int id, string n, float gpa) {
		studentID = id;
		name = n;
		GPA = gpa;
		left = NULL;
		right = NULL;
	}
};

// Insert a student into the BST
Student* Insert(Student* root, int id, string name, float gpa) {
	if (root == NULL) {
		return new Student(id, name, gpa);
	}

	if (id < root->studentID) {
		root->left = Insert(root->left, id, name, gpa);
	}
	else if (id > root->studentID) {
		root->right = Insert(root->right, id, name, gpa);
	}
	else {
		cout << "Student ID already exists." << endl;
	}

	return root;
}

// Search for a student by ID
Student* Search(Student* root, int id) {
	if (root == NULL || root->studentID == id) {
		return root;
	}

	if (id < root->studentID) {
		return Search(root->left, id);
	}

	return Search(root->right, id);
}

// Display student details
void Display(Student* s) {
	if (s == NULL) {
		return;
	}

	cout << "Student ID: " << s->studentID << endl;
	cout << "Name: " << s->name << endl;
	cout << "GPA: " << s->GPA << endl;
}

// Display students sorted by ID
void Inorder(Student* root) {
	if (root == NULL) {
		return;
	}

	Inorder(root->left);
	Display(root);
	cout << "-------------------" << endl;
	Inorder(root->right);
}

// Count total students
int CountStudents(Student* root) {
	if (root == NULL) {
		return 0;
	}

	return 1 + CountStudents(root->left)
		+ CountStudents(root->right);
}

// Find the student with the smallest ID
Student* FindMin(Student* root) {
	while (root != NULL && root->left != NULL) {
		root = root->left;
	}

	return root;
}

// Delete a student by ID
Student* Delete(Student* root, int id) {
	if (root == NULL) {
		return NULL;
	}

	if (id < root->studentID) {
		root->left = Delete(root->left, id);
	}
	else if (id > root->studentID) {
		root->right = Delete(root->right, id);
	}
	else {
		// Node has no left child
		if (root->left == NULL) {
			Student* temp = root->right;
			delete root;
			return temp;
		}

		// Node has no right child
		if (root->right == NULL) {
			Student* temp = root->left;
			delete root;
			return temp;
		}

		// Node has two children
		Student* temp = FindMin(root->right);

		root->studentID = temp->studentID;
		root->name = temp->name;
		root->GPA = temp->GPA;

		root->right = Delete(root->right, temp->studentID);
	}

	return root;
}

// Find students with highest and lowest GPA
void FindGPA(Student* root, Student*& highest, Student*& lowest) {
	if (root == NULL) {
		return;
	}

	if (highest == NULL || root->GPA > highest->GPA) {
		highest = root;
	}

	if (lowest == NULL || root->GPA < lowest->GPA) {
		lowest = root;
	}

	FindGPA(root->left, highest, lowest);
	FindGPA(root->right, highest, lowest);
}

// Display students whose GPA is above the given limit
void AboveGPA(Student* root, float limit) {
	if (root == NULL) {
		return;
	}

	AboveGPA(root->left, limit);

	if (root->GPA > limit) {
		Display(root);
		cout << "-------------------" << endl;
	}

	AboveGPA(root->right, limit);
}

int main() {
	Student* root = NULL;
	int choice;

	// Insert some student records
	root = Insert(root, 104, "Ali", 3.5);
	root = Insert(root, 102, "Ahmed", 3.2);
	root = Insert(root, 106, "Sara", 3.9);
	root = Insert(root, 101, "Ayesha", 3.7);
	root = Insert(root, 105, "Usman", 2.8);

	do {
		cout << "\n===== Student Record System =====" << endl;
		cout << "1. Insert Student" << endl;
		cout << "2. Search Student" << endl;
		cout << "3. Delete Student" << endl;
		cout << "4. Display All Students" << endl;
		cout << "5. Count Students" << endl;
		cout << "6. Highest and Lowest GPA" << endl;
		cout << "7. Display Students Above GPA" << endl;
		cout << "0. Exit" << endl;

		cout << "Enter your choice: ";
		cin >> choice;

		if (choice == 1) {
			int id;
			string name;
			float gpa;

			cout << "Enter student ID: ";
			cin >> id;

			if (Search(root, id) != NULL) {
				cout << "Student ID already exists." << endl;
				continue;
			}

			cout << "Enter name (one word): ";
			cin >> name;

			cout << "Enter GPA: ";
			cin >> gpa;

			if (gpa < 0 || gpa > 4) {
				cout << "Invalid GPA. Enter a value from 0 to 4." << endl;
			}
			else {
				root = Insert(root, id, name, gpa);
				cout << "Student added successfully." << endl;
			}
		}
		else if (choice == 2) {
			int id;

			cout << "Enter student ID to search: ";
			cin >> id;

			Student* s = Search(root, id);

			if (s != NULL) {
				Display(s);
			}
			else {
				cout << "Student not found." << endl;
			}
		}
		else if (choice == 3) {
			int id;

			cout << "Enter student ID to delete: ";
			cin >> id;

			if (Search(root, id) != NULL) {
				root = Delete(root, id);
				cout << "Student deleted successfully." << endl;
			}
			else {
				cout << "Student not found." << endl;
			}
		}
		else if (choice == 4) {
			Inorder(root);
		}
		else if (choice == 5) {
			cout << "Total students: "
				<< CountStudents(root) << endl;
		}
		else if (choice == 6) {
			Student* highest = NULL;
			Student* lowest = NULL;

			FindGPA(root, highest, lowest);

			if (highest == NULL) {
				cout << "No student records available." << endl;
			}
			else {
				cout << "\nStudent with highest GPA:" << endl;
				Display(highest);

				cout << "\nStudent with lowest GPA:" << endl;
				Display(lowest);
			}
		}
		else if (choice == 7) {
			float limit;

			cout << "Enter GPA limit: ";
			cin >> limit;

			cout << "\nStudents with GPA above "
				<< limit << ":" << endl;

			AboveGPA(root, limit);
		}
		else if (choice != 0) {
			cout << "Invalid choice." << endl;
		}

	} while (choice != 0);

	cout << "Program ended." << endl;

	return 0;
}
