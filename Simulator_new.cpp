
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <map>
#include <iterator>

using namespace std;
extern "C" 
{
    #include <string.h>
    #include <sys/time.h>
}


map<string,int> fileaccesscount; 
map<string,int> userownership;
map<string,int> filemodifytime;
map<string,int> fileaccesstime;

int count;
int snapshotId,nlink;
long inode,generation_id,fileSize,generation_id2,blocksize;
string fileset,misc,userId,groupId,mode,accessTime,modifyTime,changeTime,metafile;

string access_day, access_month, access_date, access_time, access_year,modify_day, modify_month, modify_date, modify_time, modify_year,change_day, change_month, change_date, change_time,change_year;

//void UserCount(vector<string>);
//void LastModifiedTime(vector<string>);
//void FilesAcccessed(vector<string>);

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
void FilesAcccessed(string date,string month) {

	string temp = date +  " " + month;  //Format of DD-M

	try{

;		
		if ( fileaccesscount.count(temp) == 0) {
			
			count = 1;
			fileaccesscount[temp] = count;
		} 
		else {

			count = fileaccesscount[temp];
			count ++;			
			fileaccesscount[temp] = count;
		}
	} catch ( const out_of_range &e){
		cerr << " Exception at " << e.what() << endl;
	}

}

void UserCount(string data)
{


	try {
		
		if ( userownership.count(data) == 0) {
			int count  = 1;
			userownership[data] = count;
		}
		else {

			int count = userownership[data];
			count ++;			
			userownership[data]=count;
		}
	} catch (const out_of_range &e){
		cerr << " Exception at " << e.what() << endl;
	}

}

void LastAccessTime(string access_date,string access_month,string access_time,ofstream& file2)
{
	char d = ':';
	std::vector<string> access_timeformat;
	string temp,hours;

	stringstream s2(access_time);
	try 
	{
		while(getline(s2,temp,d)) {

			access_timeformat.push_back(temp);
			hours = access_timeformat.at(0);				
		}

		if ( fileaccesstime.count(access_timeformat.at(0)) == 0) 
		{
				
			int count = 1;
			fileaccesstime[hours]  = count;
			//cout << " NEW KEY "  << hours << endl;
		}
		else 
		{
			int count  = fileaccesstime[hours];
			count++ ;
			fileaccesstime[hours] = count;
			//cout << "UPDATING KEY " << hours  << " " << count << endl;						
		}

		file2 << hours << "," << fileaccesstime[hours] << endl;
	} catch (const out_of_range &e){
		cerr << " Exception at " << e.what() << endl;
	}

}

void LastModifiedTime(string modify_date,string modify_month,string modify_time,ofstream& file1,ofstream& indexAnalysis){

	char d = ':';
	
	string temp,hours;
	struct timeval start_time,end_time;
	vector<string> modify_timeformat;
	double t1;

	try {

			/*Extract the HH MM and SS and store it in timeformat vector*/
			stringstream ss(modify_time);
			gettimeofday(&start_time, NULL);
			while(getline(ss,temp,d)) {

				modify_timeformat.push_back(temp);
				hours = modify_timeformat.at(0);
			 }

			if ( filemodifytime.count(modify_timeformat.at(0)) == 0) {
			
				int count = 1;
				filemodifytime[hours]  = count;
						//cout << " NEW KEY "  << hours << endl;
			}
			else {

				int count  = filemodifytime[hours];
				count++ ;
				filemodifytime[hours] = count;
						//cout << "UPDATING KEY " << hours  << " " << count << endl;						
			}
			gettimeofday(&end_time, NULL);
			t1 = (double)(((double)end_time.tv_sec - (double)start_time.tv_sec) + \
    					((double)(end_time.tv_usec - start_time.tv_usec)));

		//file1 << hours << "," << filemodifytime[hours] << endl;
		indexAnalysis << hours << "," << t1 << endl;

	} catch (const out_of_range &e){
		cerr << " Exception at " << e.what() << endl;
	}
}


int main(int argc, char* argv[]){
	
	ifstream f;
	ofstream file1("ModifyTime.txt", ios::out);  //Output stream
	ofstream file2("AccessTime.txt", ios::out);
	ofstream file3("Index_Time_FormattedData.txt", ios::out);
	string line,data;
	vector<string> temp;
	struct timeval start, end;
	string filename = argv[2];
	string argv1 = argv[1];
	vector<string> token;
	string c = " ";
	double t1;
	map<string,int>::iterator j;
	string outdata ;
	
	try {
		
		
		ifstream infile(filename);
		
		if ( argv1 == "-m" ){

			gettimeofday(&start, NULL);
			while(getline(infile,line)){
						//vector<string>::iterator i;
		
			//temp =  tokenize(line," ");
				stringstream ss(line);
			
				if ( !(ss >> inode >> access_day >> access_month >> access_date >> access_time >> access_year >>
					modify_day >> modify_month >> modify_date >> modify_time >> modify_year >> fileSize >>
					change_day  >> change_month >> change_date >> change_time >> change_year >> metafile))
					{
						break;
					}		
					LastModifiedTime(modify_date,modify_month,modify_time,file1,file3);
					LastAccessTime(access_date,access_month,access_time,file2);																
			}
			gettimeofday(&end, NULL);			

			// cout << "==================  Modify Time =================" << endl;
			// for ( j = filemodifytime.begin() ; j != filemodifytime.end() ; j++ ){
			// 	cout << j->first << "," << j->second << endl;
			// }

			// cout << "===================  Access Time =================" << endl;
			// for ( j = fileaccesstime.begin() ; j != fileaccesstime.end() ; j++ ){
			// 	cout << j->first << "," << j->second << endl;
			// }

			/*cout << "READ AND INDEX TIME: " << endl;
			t1 = (double)(((double)end.tv_sec - (double)start.tv_sec) + \
    					((double)(end.tv_usec - start.tv_usec)/1000000));	
    		cout << t1 << "  seconds " << endl;*/
		}

		else if ( argv1 == "-u") {

			gettimeofday(&start, NULL);
			while(getline(infile,line)){
		
			
				stringstream ss(line);				
					
				if ( !(ss >> inode >> generation_id >> snapshotId >> fileSize >> fileset >> generation_id2 >> 
					misc >> nlink >> userId >> groupId >> mode >> accessTime >> modifyTime >> changeTime >> metafile))
					{
						break;
					}			
				UserCount(userId);					
			}			
			gettimeofday(&end, NULL);

			for ( j = userownership.begin() ; j != userownership.end() ; j++ ){
					cout << j->first << "," << j->second << endl;
				}
			
			cout << "READ AND INDEX TIME: " << endl;
			t1 = (double)(((double)end.tv_sec - (double)start.tv_sec) + \
    					((double)(end.tv_usec - start.tv_usec)/1000000));	

    		cout << t1 << "  seconds " << endl;
		}
		else if ( argv1 == "-a") {

			while(getline(infile,line)){

				stringstream ss(line);
					
				if ( !(ss >> inode >> access_day >> access_month >> access_date >> access_time >> access_year >>
					modify_day >> modify_month >> modify_date >> modify_time >> modify_year >> fileSize >>
					change_day  >> change_month >> change_date >> change_time >> change_year >> metafile))
				{
					break;
				}

				FilesAcccessed(access_date,access_time);	
			}						

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