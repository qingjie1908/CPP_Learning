#include <fstream>
#include "/Users/qingjie/github/CPP_Learning/cpp_primer/15p9/15p93/TextQuery.h"
#include "/Users/qingjie/github/CPP_Learning/cpp_primer/15p9/15p93/QueryResult.h"
#include "/Users/qingjie/github/CPP_Learning/cpp_primer/15p9/15p93/Query.h"


// void runQueries(std::ifstream &infile)
// {
//     TextQuery tq(infile); //store the file and build query map

//     while(true){
//         std::cout << "enter word to look for, or q to quit: " << std::endl;
//         std::string s;
//         if(!(std::cin >> s) || s == "q") break;
//         QueryResult obj2 = tq.query(s);
//         //after query(), shared ptr in query() destroyed, but shared_ptr in obj2 exist
//         print(std::cout, obj2) << std::endl;
//     }
//     //after while loop, shared ptr in obj2 destroyed, memory freed;

//     //TexQuery has no data member of type shared_ptr, its only be created when call member func query()

// }

int main()
{
    std::ifstream input_file;
    input_file.open("/Users/qingjie/github/CPP_Learning/cpp_primer/15p9/15p93/15p93.txt");

    TextQuery text(input_file);

    Query q = Query("fiery") & Query("bird") | Query("wind");
    /*
    //direct construct Query("fiery"), Query("bird"),these two are temp obj1_fiery, obj2_bird
    WordQuery(string).
    Query(string).
    WordQuery(string).
    Query(string).

    //then use temp obj1,2 to construct two new Query obj into BinaryQuery And part
    //first use Query copy construct, inside it, call WordQuery::clone, return new WordQuery(*this), WordQuery copy construct, copy query_word
    BinaryQuery::construct.
    AndQuery::constrcut
    Query(p)
    //now AndQuery part finish, it hold 2 new Query lhs, rhs (tmep_obj3, temp_obj4)
    //note: since we define destructor in Query_base, so it will not generate synthesized move control
    //so when use temp obj1,2 to construct two two new Query obj into BinaryQuery And part, it not invoke Query move construct, but Query copy construct

    //direct construct Query("wind"), this is temp obj5
    WordQuery(string).
    Query(string).

    //then construct or query, travel to BinaryQuery
    //In BinaryQuery, copy construct two Query member by using previous temp objs
    //In lhs Query copy construct, travel to AndQuery::clone reutrn, AndQuery(*this), then travel to AndQuery synthesized copy construct
    //then travel to two Query::copy construct, in each Query::copy construct, call WordQuery::clone, return new WordQuery(*this), then travel to WordQuery::copy construct, then to Base::systhesize copy construct, then call WordQuery::string member query_word

    //then same process for "bird", then OrQuery::lhs (Query, which is AndQuery) finish

    //then go to OrQuery::rhs (Query, which is WordQuery)
    //first, Query::copy_construct, call clone(), then go to WordQuery::clone
    //clone return new WordQuery(*this) will call WordQuery::copy construct, then will call Base::synthsize copy construct first, then copy string query_word

    BinaryQuery::construct.
    OrQuery::construct.
    Query(p)

    //now OrQuery finish, which means Query q construct finish

    //now need to destruct the temp obj

    //first destrcut temp obj5 Query("wind")
    //go to ~Query(),
    //delete pointer, which will delete WordQuery("wind"), go to ~WordQuery()
    //which will go to ~Query_base(),
    //aftet these, string "wind" is be free, destrcuct  temp obj Query("wind") finish
    ~Query()
    ~WordQuery()
    ~Query_base()


    //now destruct Query (AndQuery) obj (temp obj4, temp obj3)
    //first Query::~, then delete p, go to AndQuery::~, then go to Binary::~
    //inside binary, destoye Query lhs(WordQuery), rhs(WordQuery);
    //so go Query::~, delete p; then go to WordQuery::~, then to Query_base::~

    ~Query()
    ~AndQuery()
    ~BinaryQuery()
    ~Query()
    ~WordQuery()
    ~Query_base()

    //now destrcut AndQuery::rhs
    ~Query()
    ~WordQuery()
    ~Query_base()

    //now AndQuery::lhs rhs destroyed
    //destroy AndQuery it self contained part (lhs,rhs) finished , destroy its base part
    ~Query_base()

    //now final destroy temp "firey" and temp "bird" (temp obj1, temp obj2)
    ~Query()
    ~WordQuery()
    ~Query_base()
    ~Query()
    ~WordQuery()
    ~Query_base()
    */

    QueryResult q_r = q.eval(text);

    std::cout << "Executing Query for: " << q << std::endl;
    
    print(std::cout, q_r);

    //ex 15.40, no match, just putput ff | bb
    Query q1 = Query("ff") | Query("bb");
    QueryResult q1_r = q1.eval(text);
    std::cout << "Executing Query for: " << q1 << std::endl;
    print(std::cout, q1_r);

    Query q2(std::move(q));

    q1 = std::move(q2);

    input_file.close();

    return 0;

    //output
    /*
    WordQuery(string).
    Query(string).
    WordQuery(string).
    Query(string).
    BinaryQuery::construct.
    AndQuery::constrcut
    Query(sp)
    WordQuery(string).
    Query(string).
    BinaryQuery::construct.
    OrQuery::construct.
    Query(sp)
    Executing Query for: Query::rep()
    BinaryQuery::rep()
    Query::rep()
    BinaryQuery::rep()
    Query::rep()
    Wordquery::rep()
    Query::rep()
    Wordquery::rep()
    Query::rep()
    Wordquery::rep()
    fiery & bird | wind
    element occurs 3 times: 
            (line 2) Her Daddy says when the wind blows
            (line 4) like a fiery bird in flight.
            (line 5) A beautiful fiery bird, he tells her,
    */

}