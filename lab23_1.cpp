#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<cstdlib>

using namespace std;

char score2grade(int score){
    if(score >= 80) return 'A';
    if(score >= 70) return 'B';
    if(score >= 60) return 'C';
    if(score >= 50) return 'D';
    else return 'F';
}

string toUpperStr(string x){
    string y = x;
    for(unsigned i = 0; i < x.size();i++) y[i] = toupper(x[i]);
    return y;
}

void importDataFromFile(string namefile,vector<string> &search_name,vector<int> &scores , vector<char> &grades){
    ifstream source(namefile);
    string txtline;char name[100];int score;int score2;int score3;
    char format[] = "%[^:]: %d %d %d";
    while(getline(source,txtline)){
        const char* txtline_modi = txtline.c_str();
        sscanf(txtline_modi,format,name,&score,&score2,&score3);
        search_name.push_back(name);
        int sum = score+score2+score3;
        scores.push_back(sum);
        grades.push_back(score2grade(sum));
    }
}

void getCommand(string &command,string &key){
    cout << "Please input your command:" << "\n";
    string input;
    vector<string> use;
    getline(cin,input);
    int start = 0;
    int end = input.find_first_of(" ");
    use.push_back(input.substr(start,end-start));
    start = end+1;
    use.push_back(input.substr(start,input.size()-start));
    command = use[0];
    if (use.size() == 1){
        key = "";
    }else{key = use[1];}
    use.clear();
}

void searchName(vector<string> name , vector<int> scores , vector<char> grades , string key){
    bool notfound = 1;
    cout << "---------------------------------" << "\n";
    for (size_t i = 0 ;i < name.size() ;i++){
        if (toUpperStr(name[i]) == key){                       
            cout << name[i] << "'s score = " << scores[i] << "\n";
            cout << name[i] << "'s grade = " << grades[i] << "\n";
            notfound = 0;
        }
            
    }                  
    if (notfound) cout << "Cannot found." << endl;
    cout << "---------------------------------" << "\n"; 
}

void searchGrade(vector<string> name , vector<int> scores , vector<char> grades , string key){
   cout << "---------------------------------" << "\n";     
   bool notfound = 1;
   for (size_t i=0;i<name.size();i++){
    if (grades[i] == key[0]){
        cout <<  name[i] << " (" << scores[i] << ")" << endl;notfound = 0; 
    }
   } 
   if (notfound) cout << "Cannot found." << endl;
   cout << "---------------------------------" << "\n"; 
}

int main(){
    string filename = "name_score.txt";
    vector<string> names;
    vector<int> scores;
    vector<char> grades; 
    importDataFromFile(filename, names, scores, grades);
    
    do{
        string command, key;
        getCommand(command,key);
        command = toUpperStr(command);
        key = toUpperStr(key);
        if(command == "EXIT") break;
        else if(command == "GRADE") searchGrade(names, scores, grades, key);
        else if(command == "NAME") searchName(names, scores, grades, key);
        else{
            cout << "---------------------------------\n";
            cout << "Invalid command.\n";
            cout << "---------------------------------\n";
        }
    }while(true);
    
    return 0;
}
