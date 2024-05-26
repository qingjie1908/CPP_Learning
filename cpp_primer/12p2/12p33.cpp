#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <set>
#include <memory>
#include <string>

//this is a example code in the text book

class QueryResult; // declaration needed for return type in the query function
class TextQuery {
public:
    using line_no = std::vector<std::string>::size_type; 
    TextQuery(std::ifstream&);
    QueryResult query(const std::string&) const;
private:
    std::shared_ptr<std::vector<std::string>> file; // input file 
    // map of each word to the set of the lines in which that word appears 
    std::map<std::string, std::shared_ptr<std::set<line_no>>> wm;
};

// read the input file and build the map of lines to line numbers
TextQuery::TextQuery(std::ifstream &is): file(new std::vector<std::string>) {
    std::string text;
    while (getline(is, text)) { // for each line in the file
        file->push_back(text); // remember this line of text 
        int n = file->size() - 1; // the current line number
        std::istringstream line(text); // separate the line into words
        std::string word;
        while (line >> word) { // for each word in that line
            // if word isn’t already in wm,subscripting adds a new entry
            auto &lines = wm[word]; // lines is a shared_ptr
            if (!lines) // that pointer is null the first time we see word
                lines.reset(new std::set<line_no>);  // allocate a new set
            lines->insert(n); // insert this line number
        } 
    }
}
 
class QueryResult {
friend std::ostream& print(std::ostream&, const QueryResult&); 
public:
    using line_no = std::vector<std::string>::size_type; 
    QueryResult(std::string s, std::shared_ptr<std::set<line_no>> p,
                std::shared_ptr<std::vector<std::string>> f): 
                sought(s), lines(p), file(f) { }
private:
    std::string sought; // word this query represents 
    std::shared_ptr<std::set<line_no>> lines; // lines it’s on 
    std::shared_ptr<std::vector<std::string>> file; // input file
};

QueryResult
TextQuery::query(const std::string &sought) const 
{
    // we’llreturnapointertothissetifwedon’tfindsought
    static std::shared_ptr<std::set<line_no>> nodata(new std::set<line_no>);
    // use find and not a subscript to avoid adding words to wm!
    auto loc = wm.find(sought);
    if (loc == wm.end())
        return QueryResult(sought, nodata, file); // not found 
    else
        return QueryResult(sought, loc->second, file);
}


std::string make_plural(size_t size, const std::string& word, const std::string& s)
{
    return size > 1 ? (word + s) : word;
}

std::ostream &print(std::ostream & os, const QueryResult &qr) 
{
    // if the word was found, print the count and all occurrences
    os << qr.sought << " occurs " << qr.lines->size() << " "
    << make_plural(qr.lines->size(), "time", "s") << std::endl; // print each line in which the word appeared
    for (auto num : *qr.lines) // for every element in the set
        // don’t confound the user with text lines starting at 0 
        os << "\t(line " << num + 1 << ") "
        << *(qr.file->begin() + num) << std::endl; 
    
    return os;
}

void runQueries(std::ifstream &infile)
{
    TextQuery tq(infile); //store the file and build query map

    while(true){
        std::cout << "enter word to look for, or q to quit: " << std::endl;
        std::string s;
        if(!(std::cin >> s) || s == "q") break;
        QueryResult obj2 = tq.query(s);
        //after query(), shared ptr in query() destroyed, but shared_ptr in obj2 exist
        print(std::cout, obj2) << std::endl;
    }
    //after while loop, shared ptr in obj2 destroyed, memory freed;

    //TexQuery has no data member of type shared_ptr, its only be created when call member func query()

}



int main()
{
    std::ifstream input_file;
    input_file.open("/Users/qingjie/github/CPP_Learning/cpp_primer/12p2/12p27.txt");

    runQueries(input_file);

    input_file.close();

    //
    //from the output we can know it does not count occurrence of word in file, it counts line occrrence
    //second it will ignore "word" append with some punctuations
    /*
    enter word to look for, or q to quit: 
    qingjie
    qingjie occurs 2 times
            (line 1) this is qingjie
            (line 7)     qingjie is qingjie!

    enter word to look for, or q to quit: 
    is
    is occurs 4 times
            (line 1) this is qingjie
            (line 2) this is apple;
            (line 4) "qingjie is here!
            (line 7)     qingjie is qingjie!

    enter word to look for, or q to quit: 
    q
    */

}
  