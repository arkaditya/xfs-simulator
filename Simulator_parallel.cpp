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

int main(int argc, char* argv[]){
	
	ifstream f;
	string line,data;
	vector<string> temp;
	string filename = argv[2];
	string argv1 = argv[1];
	vector<string> token;
	string c = " ";
	map<string,int>::iterator j;
	queue<File> fileQueue;
	
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