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

void importDataFromFile(string filename, 
                        vector<string> &names,
                        vector<int> &scores,
                        vector<char> &grades){
    ifstream files(filename);
    string lines;
    while(getline(files,lines)){
        int idx1 = lines.find(':');
        int idx2 = lines.substr(idx1,lines.size()).find(' ');
        string text = lines.substr(idx2+idx1+1,lines.size());
        const char *text2 = text.c_str();
        const char *format = "%d %d %d";
        int a,b,c; 
        sscanf(text2,format,&a,&b,&c);
        names.push_back(lines.substr(0,idx1));
        scores.push_back(a+b+c);
        grades.push_back(score2grade(a+b+c));
    }


}

void getCommand(string &command,string &key){
    cout << "Please input your command:" << endl;
    string lines;
    getline(cin,lines);
    int idx = lines.find(' ');
    command = lines.substr(0,idx);
    key = lines.substr(idx+1);
}

void searchName(vector<string> names,
                vector<int> scores,
                vector<char> grades,
                string key ){
    bool check = false;
    cout << "---------------------------------" << endl;
    for (unsigned i = 0;i < names.size();i++){
        if (key == toUpperStr(names[i])){
            cout << names[i] << "'s score = " << scores[i] << endl;
            cout << names[i] << "'s grade = " << grades[i] << endl;
            check = true;
            break;
        }

    } 
    if (!check) cout << "Cannot found." << endl;
    cout << "---------------------------------" << endl;
}

void searchGrade(vector<string> names,
                vector<int> scores,
                vector<char> grades,
                string key ){
    bool check = false;
    cout << "---------------------------------" << endl;
    for (unsigned i = 0;i < names.size();i++){
        string s;
        s += grades[i];
        if (key == s){
            cout << names[i] << " (" << scores[i] << ")"<< endl;
            check = true;
        }

    } 
    if (!check) cout << "Cannot found." << endl;
    cout << "---------------------------------" << endl;
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

