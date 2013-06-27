/*************************************************************************
    > File Name: textquery.cpp
    > Author: wolf
    > Mail: tiandewei07@163.com 
    > Created Time: Thu 27 Jun 2013 03:12:07 PM CST
 ************************************************************************/

#include<iostream>
#include<fstream>
#include<sstream>
#include<vector>
#include<map>
#include<set>
#include<stdexcept>
#include<cstdlib>

using namespace std;

class TextQuery	{
public:
	//typedef to make declarations easier
	typedef std::vector<std::string>::size_type line_no;
	/*
	 * read_file builds internel data structures for the given file
	 * run_query finds the given word and returns set of lines on which it appears
	 * text_line returns a requested line from the input file
	 */
	 void read_file(std::ifstream &is)
	 { store_file(is); build_map();	 }
	 std::set<line_no> run_query(const std::string &) const;
	 std::string text_line(line_no) const;

private:
	 //utility functions used by read_file
	 void store_file(std::ifstream&); //store input file
	 void build_map(); //associated each word with a set of line numbers
	 //remember the whole input file
	 std::vector<std::string> lines_of_text;
	 //map word to set of the lines on which it occurs
	 std::map< std::string, std::set<line_no> > word_map;
};

// read input file: store each line as element in line_of_text
void TextQuery::store_file(ifstream &is)
{
	string textline;
	while(getline(is, textline))
		lines_of_text.push_back(textline);
}

// fine whitespace-separated words in the input vector
// and puts the word in word_map along with the line number
void TextQuery::build_map()
{
	//process each line from the input vector
	for(line_no line_num = 0; line_num != lines_of_text.size(); ++line_num)
	{
		//we will use line to read the text  a word at a time
		istringstream line(lines_of_text[line_num]);
		string word;
		while(line >> word)
			//add this line number to the set;
			//subscript will add word to the map  if it's not already there
			word_map[word].insert(line_num);
	}
}

set<TextQuery::line_no> TextQuery::run_query(const string &query_word) const
{
	//Note:must use find and not subscript the map directly
	//to avoid adding words to word_map
	map<string, set<line_no> >::const_iterator loc = word_map.find(query_word);
	if(loc == word_map.end())
		return set<line_no>(); //not found, return empty set
	else
		//fetch and return set of line numbers for this word
		return loc->second;
}

string TextQuery::text_line(line_no line) const
{
	if(line < lines_of_text.size())
		return lines_of_text[line];
	throw std::out_of_range("line number out of range");
}

string make_plural(size_t ctr, const string &word, const string &ending)
{
	return (ctr == 1) ? word: word +ending;
}

ifstream& open_file(ifstream &in, const string &file)
{
	in.close();
	in.clear();
	in.open(file.c_str());
	return in;
}


void print_results(const set<TextQuery::line_no> &locs, const string &sought, const TextQuery &file)
{
	//if the word was found, then print count and all occurences
	typedef set<TextQuery::line_no> line_nums;
	line_nums::size_type size = locs.size();
	cout << "\n" <<sought << " occurs " << size << " " << make_plural(size, "time", "s") << endl;
	//print each line in which the word appeared
	line_nums::const_iterator it = locs.begin();
	for(; it != locs.end(); it++)
	{
		cout << "\t(line " << (*it) +  1 << ")" << file.text_line(*it) << endl;
	}
}


int main(int argc, char *argv[])
{
	ifstream infile;
	if(argc < 2 || !open_file(infile, argv[1]))
	{
		cerr << "No input file!" << endl;
		return EXIT_FAILURE;
	}
	TextQuery tq;
	tq.read_file(infile);
	while(true)	{
		cout << " enter word to look for, or q to quit: ";
		string s;
		cin >> s;
		if(!cin || s == "q") break;
		set<TextQuery::line_no> locs = tq.run_query(s);
		print_results(locs, s, tq);
	}

	return 0;
}

