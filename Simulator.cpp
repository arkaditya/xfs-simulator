#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <map>
#include <iterator>

using namespace std;

map<string,int> fileaccesscount; 
map<string,int> userownership;
map<string,int> filemodifytime;

void UserCount(vector<string>);
void LastModifiedTime(vector<string>);
void FilesAcccessed(vector<string>);

/*void fileCountMap(vector<string> data)
{

	try {
		//if ( tempHashMap.find(data) == tempHashMap.end() ) {
		if ( modifiedTime.count(data) == 0) {
			
			int count = 1;
			modifiedTime.insert(pair<string,int>(data,count));

		}
		else {

			int count  = modifiedTime.at(data);
			count++ ;
			modifiedTime.erase(data);
			modifiedTime.insert(pair <string,int> (data,count));

		}
	} catch(const out_of_range &e){

		cerr << "Exception at "	<< e.what() << endl;
	}
	
}*/
/*Get the no of files accessed on a specific day */
void FilesAcccessed(vector<string> data) {

	string temp = data.at(3) +  " " + data.at(2);  //Format of DD-M

	try{

		if ( fileaccesscount.count(temp) == 0) {
			int count = 1;
			fileaccesscount.insert(pair<string,int> (temp,count));
		} 
		else {

			int count = fileaccesscount.at(temp);
			count ++;
			fileaccesscount.erase(temp);
			fileaccesscount.insert(pair<string,int>(temp,count));
		}
	} catch ( const out_of_range &e){
		cerr << " Exception at " << e.what() << endl;
	}

}

void UserCount(vector<string> data)
{

	string temp = data.at(8);
	try {
		
		if ( userownership.count(temp) == 0) {
			int count  = 1;
			userownership.insert(pair<string,int>(temp,count));
		}
		else {

			int count = userownership.at(temp);
			count ++;
			userownership.erase(temp);
			userownership.insert(pair <string,int> (temp,count));
		}
	} catch (const out_of_range &e){
		cerr << " Exception at " << e.what() << endl;
	}

}

void LastModifiedTime(vector<string> data){

	char d = ':';
	stringstream ss(data.at(9));
	string temp;
	vector<string> timeformat;

	try {

			/*Extract the HH MM and SS and store it in timeformat vector*/
			while(getline(ss,temp,d)) {

				timeformat.push_back(temp);

				string hours = timeformat.at(0); 
				if ( filemodifytime.count(timeformat.at(0)) == 0) {
			
						int count = 1;
						filemodifytime.insert(pair<string,int>(hours,count));
						//cout << " NEW KEY "  << hours << endl;
					}
				else {

						int count  = filemodifytime.at(hours);
						count++ ;
						//cout << "UPDATING KEY " << hours  << " " << count << endl;
						filemodifytime.erase(hours);
						filemodifytime.insert(pair <string,int> (hours,count));
					}
			}

	} catch (const out_of_range &e){
		cerr << " Exception at " << e.what() << endl;
	}
}


int main(int argc, char* argv[]){
	
	ifstream f;
	string line,data;
	vector<string> temp;
	string filename = argv[2];
	string argv1 = argv[1];
	vector<string> token;
	string c = " ";
	map<string,int>::iterator j;
	
	try {
		
		f.open(filename);
		if ( argv1 == "-m" ){

			while(f){

				getline(f,line);
		
				if (line != "0"){

				//vector<string>::iterator i;
		
			//temp =  tokenize(line," ");
					stringstream ss(line);
			
					while(ss >> data){
		
						if (c.compare(data)) {
							token.push_back(data);
						}
					}
			
					if ( token.size() > 1 ) {

						if (token.at(7) == "Dec" && token.at(8) == "16" ){
							LastModifiedTime(token);
						}
					}
				}
				token.clear();
			}
			f.close();

			for ( j = filemodifytime.begin() ; j != filemodifytime.end() ; j++ ){
				cout << j->first << "," << j->second << endl;
			}
		}
	
		else if ( argv1 == "-u") {

			while(f){

				getline(f,line);
		
				if (line != "0"){

					stringstream ss(line);
			
					while(ss >> data){
		
						if (c.compare(data)) {
							token.push_back(data);
						}
					}
			
					if ( token.size() > 1 ) {

						UserCount(token);
					}
				}
				token.clear();
			}
			f.close();

			for ( j = userownership.begin() ; j != userownership.end() ; j++ ){
				cout << j->first << "," << j->second << endl;
			}
		}
		else if ( argv1 == "-a") {

			while(f){

				getline(f,line);
		
				if (line != "0"){

					stringstream ss(line);
			
					while(ss >> data){
		
						if (c.compare(data)) {
							token.push_back(data);
						}
					}
			
					if ( token.size() > 1 ) {

						FilesAcccessed(token);
					}
				}
				token.clear();
			}
			f.close();

			for ( j = fileaccesscount.begin() ; j != fileaccesscount.end() ; j++ ){
				cout << j->first << "," << j->second << endl;
			}
		}
	}
	catch (const invalid_argument &e){
		cerr << "USAGE: \n" << "\tSimulator.out -m TimeFormatted_Data\n" <<  "\tSimulator.out -u ExtractData_1\n" << endl;
	}

	return 0;
}