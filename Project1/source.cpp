#include <iostream>
#include <fstream>
#include <sstream>
#define QUANTITY_OF_MOVIE 250
using namespace std;
class Movie {
private:
	int ID;
	string Name;
	float Point;
	int Year;

public:
	Movie(int ID, string Name, float Point, int Year) : ID(ID), Name(Name), Point(Point), Year(Year) {}
	Movie() {}

	int getID() {
		return ID;
	}

	string getName() {
		return Name;
	}
	float getPoint() {
		return Point;
	}

	int getYear() {
		return Year;
	}
	void setPoint(float Point) {
		this->Point = Point;
	}
	
	void printMovie() { //prints details about the movie
		cout << endl << "Name of the movie: " << Name << endl;
		cout << "Release year of the movie: " << Year << endl;
		cout << "ID: " << ID << endl;
		cout << "Point: " << Point<<endl;
		cout << "***********************************************************************************" << endl;
	}
};

void idValidityChecker(int &id) {	
	if (id > QUANTITY_OF_MOVIE + 1 || id < 1) {    // checks whether given ID by user is valid or not
		while (id > QUANTITY_OF_MOVIE + 1 || id < 1) {
			cout << "Please enter a valid ID (between 1-251)" << endl;
			cin >> id;
		}		// as long as user enters invalid ID, loop continues			
	}	
}
int vote_quantityValidityChecker(int vote_quantity) { 
	if (vote_quantity > 10 || vote_quantity < 1) {    // checks whether given quantity by user is valid or not
		do {
			cout << "Please enter a valid quantity. (between 1-10)" << endl;
			cin >> vote_quantity;
		} while (vote_quantity > 10 || vote_quantity < 1);		// as long as user enters invalid quantity, loop continues	
		return vote_quantity;
	}
	else return vote_quantity;
}
void voteCalculator(Movie movies[], int id) {
	int vote;
	int temp = 0;
	int vote_quantity;
	idValidityChecker(id);
	
	cout << "Please enter how many votings that you want to do: ";
	cin >> vote_quantity;

	for (int i = 0; i < vote_quantityValidityChecker(vote_quantity); i++) {  //adds all the votes each other until the vote quantity 
		cin >> vote;
		if (vote > 10 || vote < 0) { //checks if given vote is valid or not
			do {
				cout << "Please enter a valid point (between 1-10)" << endl;
				cin >> vote;
			} while (vote > 10 || vote < 0);
		}
		temp += vote; //adds all the votes 
	}
	movies[(id)-1].setPoint((movies[(id)-1].getPoint() + temp) / (vote_quantity + 1)); //calculates average point
	cout << "New point is : " << movies[id - 1].getPoint() << endl;

}
void GUI(Movie movies[]) {
	int option;	// for specifying by user which option user wants to do
	do {
		cout << "Welcome to the Movie Market. Please select an option." << endl
			<< "0 - Vote the selected movie. (up to 10)"<<endl
			<< "1 - Get movie details by ID" << endl
			<< "2 - List movies between the years entered" << endl
			<< "3 - Change the point of a movie" << endl
			<< "4 - Get movie details starting with the entered letter" << endl
			<< "5 - Exit" << endl;
		
		cin >> option;
		switch (option)
		{
		case 0:

			int id;
			cout << "Please enter an ID to vote up the movie: ";
			cin >> id;		
			voteCalculator(movies,id);
			break;

		case 1:
			
			cout << "Please enter an ID: ";
			cin >> id;			
			idValidityChecker(id);
			movies[(id) - 1].printMovie();
			break;

		case 2:
			int year1, year2;
			cout << "Please enter two spesific years in order to list the movies between them." << endl;
			cin >> year1;
			cin >> year2;

			for (int i = 0; i <= QUANTITY_OF_MOVIE; i++) {
				if (movies[i].getYear() >= year1 && movies[i].getYear() <= year2 ||
					movies[i].getYear() >= year2 && movies[i].getYear() <= year1) { //lists the movies which are in between entered years
					movies[i].printMovie();
				}
			}
			break;

		case 3:
			float new_point;
			cout << "Please enter a valid ID in order to change the point of a movie: " << endl;
			cin >> id;
			idValidityChecker(id);
			cout << "Please enter new point.";
			cin >> new_point;
			movies[(id) - 1].setPoint(new_point); //the value which entered by user will be assigned as new point of the movie
			cout << "Changes has been saved. New details about the movie: " << endl;
			movies[(id) - 1].printMovie();
			break;


		case 4:
			char letter;
			cout << "Please enter a letter to see details starting with the entered letter: ";
			cin >> letter;

			for (int i = 0; i < QUANTITY_OF_MOVIE; i++) //searches all the movies in the array one by one, prints details those matched with entered character
			{
				if (movies[i].getName()[0] == letter) 
					movies[i].printMovie();
			}
			break;

		default:
			break;
		}
	} while (option!=5); 
	
}

int main() {
	Movie movies[QUANTITY_OF_MOVIE];
	ifstream read_file;
	read_file.open("movies.txt");
	if (!read_file.is_open()) {
		cerr << "File could not be opened" << endl;
		exit(1);
	}
	string line;	
	string Name;
	string Point;
	string Year;
	int i = 0;

	while (getline(read_file, line)) {

		stringstream line_stream(line);
		getline(line_stream, Point, ';');
		getline(line_stream, Name, '(');
		getline(line_stream, Year, ')');

		int int_year = stoi(Year);     //converts the year from string to integer
		float fl_point = stof(Point); //converts the point from string to float
		Movie movie(i + 1, Name, fl_point, int_year);
		movies[i] = movie; //adds all the elements from text file to the movies[] array whose type is Movie
		i++;		
	}
	read_file.close();
	GUI(movies);
}