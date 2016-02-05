#include <vector>
#include <algorithm>
#include <iostream>
#include <map>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <regex>
#include <stack>
#include <iomanip>
#include <cstdlib>

using namespace std;
//Debug
#ifdef DEBUG
#define Debug( x ) cerr << x
#else
#define Debug( x ) 
#endif

struct Tags {
	map<string, string> tagMaps;
};
//requirment
//if tag name and escape code are not valid, display error msg 

//tag name  canse-sensitive// invalid tag names
void validTagName(const string& s) { 
	if(s.size() < 2) {
		cerr << "config file error: Invalid tag name" <<endl;
		return;
	}
	for(string::size_type i = 1; i < s.size(); i++){ 
		if (!isdigit(s[i]) && !isalpha(s[i])){
			cerr << "config file error: Invalid tag name" <<endl;
			return;
		}
	}
}

bool valid_word(const string& word) {
	if (word.length() != 9 && word[0] != 'a')
		return false;

	for(string::size_type i = 1; i < word.size(); i++){ 
		if (!isdigit(word[i]))
			return false;
	}
	return true;
}

void mapTag(istream& is, Tags& t) { 
	string line;
	string tagMapName;
	string escapeCode;
	while(getline(is, line)) { // Note: getline throws away the newline char 
		bool tagNameExist = false;
		istringstream iss(line);
		if (!(iss >> tagMapName >> escapeCode)) {
			cerr << "config file error: Invalid line(at least 2 words)" <<endl;
		}
		validTagName(tagMapName);
		size_t found = escapeCode.find("\\e");
		if(found!=std::string::npos){
			escapeCode.replace(found, 2, "\033");
		}
		for(auto it = t.tagMaps.begin(); it != t.tagMaps.end(); it++) {
	   		if(it->first == tagMapName) {
	   		 	tagNameExist = true;
	   		 	cerr << "config file error: tagName exist" <<endl;
	   		}
   		}
		if(!tagNameExist) {
			t.tagMaps.insert(pair<string, string>(tagMapName,escapeCode));
		}
	}
}

// trim from end
static inline string &rtrim(string &s) {
        s.erase(find_if(s.rbegin(), s.rend(), not1(ptr_fun<int, int>(isspace))).base(), s.end());
    return s;
}

void parsesrTag(istream& cin, Tags& t) { 
	string line;
 	regex tag (R"(<(.+?)>)");
  	stack<string> mystack;
	string firstWord, lastWord;
	int countTags=0;
	while(getline(cin, line)) { // Note: getline throws away the newline char 
		if(cin.eof())
			return;	
		auto words_tagBegin = sregex_iterator(line.begin(), line.end(), tag);
	    auto words_tagEnd = sregex_iterator();
		string prefix = "", suffix = "";
		int countWord = 0;
		
		for (sregex_iterator i = words_tagBegin; i != words_tagEnd; ++i) {
	       smatch match = *i;
	       string tagname = match.str(1);
	        prefix = match.prefix(); //should replace for suffix as well.
			suffix = match.suffix();
			++countTags;
			istringstream iss(prefix);
			if(iss >> skipws >> firstWord) 
				++countWord;
			if(countWord == 0)
				prefix = "";
		
			if(countTags == 1 && (tagname.compare("text") != 0)) {
				cerr << "first tag error" <<endl;
		       	exit(1);
			}
	      	if(prefix.find(">")!=std::string::npos ||prefix.find("<")!=std::string::npos) {
				cerr << "prefix char error which has < or >" <<endl;
				exit(1);
	      	}
		   size_t found1 = prefix.find("&lt;");
		   size_t found2 = prefix.find("&gt;");
			if(found1!=std::string::npos){
				prefix.replace(found1, 4, "<");
			}
			if(found2!=std::string::npos){
				prefix.replace(found2, 4, ">");
			}
	       if (tagname[0] != '/') {       	
				if( tagname == "text") {
					if(firstWord.size() != 0) {
						cerr << "first tag error" <<endl;
			       		exit(1);
			       	}		
				}
		   		cout << prefix;
		   		bool tagNameExist = false;
		   		for(auto it = t.tagMaps.begin(); it != t.tagMaps.end(); it++) {
			   		if(it->first == tagname) {
			   		 	cout << it->second;
			       		mystack.push(it->first);
			       		tagNameExist = true;
			   		}
		   		}
		   		if(tagNameExist == false) {
			   		cerr << "error for tag name"<< endl;
		   			exit(1);
		   		}
	       }
	       else {
	       		if( tagname == "/text") {
					istringstream iss(suffix);
					iss >> skipws >> suffix;
					rtrim(suffix);
					if(suffix.size() != 0){
						cerr << "last tag error" <<endl;
			       		exit(1);
				    }		
				}
	       		if(mystack.empty()){
	       			cerr << "first name is not tag" << endl;
	       			exit(1);
				}
				else if(tagname == "/"+mystack.top()) {	       			
			   		cout << prefix;
	       			mystack.pop();
	       			if(mystack.empty()) {
	       				if(tagname == "/text") {
				      		istringstream iss1(suffix);
							iss1 >> skipws >> lastWord;
	       					if(lastWord != "") {
	       						cerr<< "closing tag error" << endl;
		       					exit(2); //finish parse   //not error
	       					}
	       					exit(2); //finish parse   //not error
	       				}
	       			}
	       			bool tagNameExist = false;
			   		for(auto it = t.tagMaps.begin(); it != t.tagMaps.end(); it++) {
				   		if(it->first == mystack.top()) {
				   		 	cout << it->second;
				       		tagNameExist = true;
				   		}
			   		}
			   		if(tagNameExist == false) {
				   		cerr << "error for tag name"<< endl;
			   			exit(1);
			   		}
	       		}
	       		else {
	       			cerr<< "tag name is not match, two cloasing tags" << endl;
	       			exit(1);
	       		}

	       	}
	   }
	  	if(suffix.find(">")!=std::string::npos ||suffix.find("<")!=std::string::npos) {
			cerr << "suffix char error which has < or >" <<endl;
			exit(1);
	  	}
		cout << suffix << endl;
	}
}

int main(int argc, char* argv[]) {
	vector<Tags> vt;
	Tags t;
	string inputLine;

	if (argc == 1) { 
		ifstream in("config.txt");
		if(!in) { 
			cerr << "unable to open " << argv[1] << endl; 
			return 2; 
		}
		mapTag(in, t); //check for config file
		Debug( "*** Debug is on. ***\n" );
		for(auto it = t.tagMaps.begin(); it != t.tagMaps.end(); it++)
			Debug(it->first << " " << it->second << "\n");
		Debug(endl);

	}
	else {
		if(argc > 2) {
		 cerr << "usage: " << argv[0] << "{source}{destination}\n"; 
		 return 1; 
		}
		ifstream in(argv[1]);
		if(!in) { 
			cerr << "unable to open " << argv[1] << endl; 
			return 2; 
		}
		mapTag(in, t); //check for config file
		Debug( "*** Debug is on. ***\n" );
		for(auto it = t.tagMaps.begin(); it != t.tagMaps.end(); it++)
			Debug(it->second << "<" << it->first << ">" << "\033[0;30m" << "\n");
		Debug(endl);
	}

	parsesrTag(cin, t);
	return 0;
}