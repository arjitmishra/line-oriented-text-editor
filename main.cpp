//C++ line-oriented text editor that reads a text file and allows basic editing commands.
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <filesystem> 
using namespace std;

//Vector to store the commands available
static vector<string> commands{
				"commands available are :-",
				"list  - list each line in n:xxx format",
				"del n - delete line at n",
				"ins n - insert a line at n",
				"save  - saves to disk",
				"quit  - quits the editor and returns to the command line",
};

//Function to check if string contains only digits.
bool is_digits(string str)
{
    for (char ch : str) {
        if (!isdigit(ch)){
            return false;
        }
    }
    return true;
}

//Display each line present in file.
void displayLines(vector<string> &lines)
{
	for(int i=0;i<lines.size();i++)
		{
			cout<< i+1 << ": "<<lines[i]<<endl;
		}	
}

//Delete nth line from file.
void deleteLine(vector<string> &lines, int &line_number)
{
	if(line_number>=0&&line_number<lines.size())
	{
		lines.erase(lines.begin()+line_number);
		cout<< "line no. "<< line_number+1 << " is deleted." << endl;
	}
	else{
		cout << "Line " << line_number << " does not exists." << endl;
	}
}

//Insert line in file.
void insertLine(vector<string> &lines, int &line_number)
{
	string line_text;
	cout << "Enter text for line inserted" << endl;
	cout << ">>";
	getline(cin, line_text);

	if(line_number>=0&&line_number<lines.size())
	{
		lines.insert(lines.begin() + line_number, line_text);
		cout<< "line is inserted at "<< line_number+1 << "." << endl;
	}
	else{
		lines.push_back(line_text);
		cout << line_number+1<<" was beyond the the numbers of lines currently present, Hence line was added at the end." << endl;
	}
}

//Gets the line number and calls the respective function for delete or insertion.
void lineOperation(vector<string> &lines,string &user_input)
{
	try{
		size_t spacePos = user_input.find(' ');
		int line_number=stoi(user_input.substr(spacePos+1))-1;
		if(is_digits(user_input.substr(spacePos+1))==false){
			cout<< "Invalid line number" <<endl;
			return;
		}
		if(user_input.substr(0,3) == ("del"))
		{
			deleteLine(lines,line_number);
		}
		else{
			insertLine(lines,line_number);
		}
	} catch(const invalid_argument& e) {
		cout << "Invalid command." << endl;
	}
}

//Saves file.
void saveFile(const string &filename,vector<string> &lines,const filesystem::path& p)
{
	ofstream file(filename);
	if (!file) {
		cout << "Error: Unable to save file." << endl;
		return;
	}
	for (const auto& l : lines) {
		file << l << endl;
	}
	cout << "File " << p.filename() << " saved." << endl;
}

//This function handles all the operation on file.
void lineEditor(const string& filename) {
    vector<string> lines;
	const filesystem::path p(filename); 
    ifstream file(filename);
	if(p.extension()!=".txt")
	{
		cout<<"File is not of .txt format."<<endl;
		return;
	}
    if (!file) {
        cout << "Error: File " << p.filename() << " not found at '" << filename << "'." <<  endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        lines.push_back(line);
    }
	
	for (const string& command : commands)
	{
        cout << command << '\n';
	}

    while (true) {
        string user_input;
        cout << ">> ";
        getline(cin, user_input);

        if (user_input.compare("list") == 0) {
            displayLines(lines);
        } 
		else if(user_input.substr(0,3) == ("del")||user_input.substr(0,3) == ("ins"))
		{
			lineOperation(lines,user_input);
		}
		else if(user_input.compare("save") == 0)
		{
			saveFile(filename,lines,p);
		}
		else if(user_input.compare("quit") == 0)
		{
			break;
		}
		else if(user_input.compare("show") == 0)
		{
			for (const string& command : commands)
			{
				cout << command << '\n';
			}
		}
		else {
            cout << "Invalid command. Try 'show' to see commands available." << endl;
        }
    }
}

//Entry to program.
int main(int argc, char* argv[]) 
{ 
	if (argc != 2) {
        cout << "'Usage: lineEditor <filePath>' is not followed" << endl;
        return 1;
    }
	lineEditor(argv[1]);
	return 0; 
}