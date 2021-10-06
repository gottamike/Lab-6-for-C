#include<iostream>
#include<stdio.h>
#include<ostream>
#include<vector>
#include<fstream>
#include<string>
#include<sstream>
#include<cstring>
#include<iomanip>


using namespace std;

// creating an enumerated type
enum Gender{male, female, nonbinary};

// creating a class
class Person{

	private:
		// private variables
		int age;
		string firstName;
		Gender gender;
		string lastName;
		string phoneNumber;
	public:
		// constructor for person
		Person(string first, string last, int a, Gender gen, string num){
			firstName = first;
			lastName = last;
			age = a;
			gender = gen;
			phoneNumber = num;
		}
		// get methods to access variables
		string getFirstName(){
			return firstName;
		}
		string getLastName(){
			return lastName;
		}
		int getAge(){
			return age;
		}
		string getPhone(){
			return phoneNumber;
		}
		Gender getGender(){
			return gender;
		}

		
};

// function that puts people into a vector of type Person
vector<Person>  pushPeople(vector<Person> singlePerson, ifstream &infile){
        string line;
        size_t pos = 0;
        std::string delimiter = " ";
        while(getline(infile, line)){
                string first;
                string last;
                int a;
                int gen;
                string num;
                int count = 0;
                std::string token;

		// using a sort of "string token" that I found on stack overflow
                
		while ((pos = line.find(delimiter)) != std::string::npos) {
			token = line.substr(0, pos);
			string specialToken = line.substr(2, 25);
                        if (count == 0) {
                                first = token;
                        } else if (count == 1) {
                                last = token;
                        } else if (count == 2) {
                                a = stoi(token);
                        } else if (count == 3) {
                                gen = stoi(token);
                        } else if (count == 4) {
				cout << "test";
                                num = token;
                        } else {
			}
                       	num = specialToken;;
			line.erase(0, pos + delimiter.length());	
			count++;
			
                }
		
		// this allows me to convert back to genders, not integers
                Gender gender;

                if (gen == 0){
                        gender = male;
                }
                else if (gen == 1){
                        gender = female;
                }
                else {
                        gender = nonbinary;
                }

		// pushing people to my vector
                Person p(first, last, a, gender, num);
                singlePerson.push_back(p);
        }
	       return singlePerson;
}

// function that finds number of women in list
void numberofWomen(vector<Person> allPeople){
        int numWomen;

        for (unsigned int i = 0; i < allPeople.size(); i++){
                if (allPeople[i].getGender() == 1){
                numWomen ++;
                }
        }
        cout << "Number of women in list: " << numWomen << endl;
}

//function that finds people over 50 in list
void peopleOverFifty(vector<Person> allPeople){
	int numPeople;

	for (unsigned int i = 0; i < allPeople.size(); i++){
		if (allPeople[i].getAge() > 50){
			numPeople++;
		}
	}
	cout << "Number of people over 50 in list: " << numPeople << endl;
}

// function that finds women, and their area code using substr method
void numWomenArea(vector<Person> allPeople){
	int womenArea = 0;
	string areaCode = "406";
	for (unsigned int i = 0; i < allPeople.size(); i++){
		if (allPeople[i].getPhone().substr(0, 3) == areaCode && allPeople[i].getGender() == 1){
			womenArea++;
		}
	}
	cout << "Number of women with 406 area code: " << womenArea << endl;
}

// similiar approach as last function
void peopleoverFiftyArea(vector<Person> allPeople){
	int numPeople = 0;
	string areaCode = "406";
        for (unsigned int i = 0; i < allPeople.size(); i++){
                if (allPeople[i].getPhone().substr(0, 3) == areaCode && allPeople[i].getAge() > 50){
                        numPeople++;
                }
        }

	cout << "Number of people over 50 with 406 area code: " << numPeople << endl;

}	

// I had to use a built in fixed and set precision method from C++ but otherwise its the same as the last functions
void percentageofWomen(vector<Person> allPeople){
        double womenArea = 0;
	double allWomen = 0;
        string areaCode = "406";
        for (unsigned int i = 0; i < allPeople.size(); i++){
                if (allPeople[i].getPhone().substr(0, 3) == areaCode && allPeople[i].getGender() == 1){
                        womenArea++;
                }
		if (allPeople[i].getGender() == 1){
			allWomen++;
		}

        }
	double answer = (womenArea/allWomen) * 100;
	cout << "Percentage of women with 406 area code: " << fixed << setprecision(2) << answer << "%" << endl;
}

// honestly this is sort of getting repetitive at this point
void percentageofPeople(vector<Person> allPeople){
	double peopleFifty = 0;
	double everyone = 0;
	string areaCode = "406";

	for (unsigned int i = 0; i < allPeople.size(); i++){
		if (allPeople[i].getAge() > 50){
			everyone++;
		}
		if (allPeople[i].getAge() > 50 && allPeople[i].getPhone().substr(0,3) == areaCode){
			peopleFifty++;
		}
	
	}
	double answer = (peopleFifty/everyone) * 100;
	cout << "Percentage of people over 50 in list with 406 area code: " << fixed << setprecision(2) << answer << "%" << endl;

}
int main(){
	// creating a vector of type Person
	vector<Person> singlePerson;
	//opening a file
	ifstream infile;
	infile.open("/public/lab6/people.txt");
	// call to my push function
	vector<Person> allPeople = pushPeople(singlePerson, infile);
	allPeople.pop_back();

	// calls to my other functions, they all do individual printing
	numberofWomen(allPeople);
	peopleOverFifty(allPeople);
	numWomenArea(allPeople);
	peopleoverFiftyArea(allPeople);
	percentageofWomen(allPeople);
	percentageofPeople(allPeople);

	return 0;
}

