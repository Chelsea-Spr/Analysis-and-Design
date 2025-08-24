// Project2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <unordered_map>

using namespace std;

struct Course {

string courseNumber;

string courseTitle;

vector<string> prerequisites;

}; class HashTable {
private:

unordered_map<string, Course> table; public:

	void insert(const Course& course) {

		table[course.courseNumber] = course;

	}



	Course search(const string& courseNumber) {

		if (table.count(courseNumber)) {

			return table.at(courseNumber);

		}

		return Course();

	}



	vector<Course> getAllCourses() {

		vector<Course> courses;

		for (const auto& pair : table) {

			courses.push_back(pair.second);

		}

		return courses;

	}

}; void loadCourses(HashTable& hashTable) {

	string fileName = "CS 300 ABCU_Advising_Program_Input.csv";


	ifstream file(fileName);

	if (!file.is_open()) {

		cout << "Error: Unable to open file " << fileName << endl;

		return;

	}



	string line;

	while (getline(file, line)) {

		stringstream ss(line);

		Course course;

		string prerequisite;


		getline(ss, course.courseNumber, ',');

		getline(ss, course.courseTitle, ',');


		while (getline(ss, prerequisite, ',')) {

			prerequisite.erase(0, prerequisite.find_first_not_of(" \t\n\r\f\v"));

			prerequisite.erase(prerequisite.find_last_not_of(" \t\n\r\f\v") + 1);

			if (!prerequisite.empty()) {

				course.prerequisites.push_back(prerequisite);

			}

		}


		hashTable.insert(course);

	}



	file.close();

	cout << "Course data loaded successfully from " << fileName << endl;

}void printAllCourses(HashTable& hashTable) {

	vector<Course> courses = hashTable.getAllCourses();



	sort(courses.begin(), courses.end(), [](const Course& a, const Course& b) {

		return a.courseNumber < b.courseNumber;

		});



	for (const auto& course : courses) {

		cout << course.courseNumber << ": " << course.courseTitle << endl;

	}

}void printCourseInfo(HashTable& hashTable) {

	string courseNumber;

	cout << "Enter the course number: ";

	cin >> courseNumber;



	Course course = hashTable.search(courseNumber);



	if (course.courseNumber.empty()) {

		cout << "Course not found: " << courseNumber << endl;

	}
	else {

		cout << course.courseNumber << ": " << course.courseTitle << endl;

		if (!course.prerequisites.empty()) {

			cout << "Prerequisites: ";

			for (size_t i = 0; i < course.prerequisites.size(); ++i) {

				cout << course.prerequisites[i];

				if (i < course.prerequisites.size() - 1) {

					cout << ", ";

				}

			}

			cout << endl;

		}
		else {

			cout << "No prerequisites." << endl;

		}

	}

}int getMenuChoice() {

	int choice;

	cout << "\nMenu:" << endl;

	cout << "1. Load Data" << endl;

	cout << "2. Print All Courses" << endl;

	cout << "3. Find Course" << endl;

	cout << "9. Exit" << endl;

	cout << "Enter your choice: ";

	cin >> choice;

	return choice;

}int main() {

	HashTable courses;

	int choice;


	do {

		choice = getMenuChoice();



		switch (choice) {

		case 1:

			loadCourses(courses);

			break;

		case 2:

			printAllCourses(courses);

			break;

		case 3:

			printCourseInfo(courses);

			break;

		case 9:

			cout << "Exiting program. Goodbye!" << endl;

			break;

		default:

			cout << "Invalid choice. Please try again." << endl;

			break;

		}

	} while (choice != 9);



	return 0;

}