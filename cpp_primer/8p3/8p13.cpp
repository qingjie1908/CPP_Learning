#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <fstream>

struct PersonInfo {
    std::string name;
    std::vector<std::string> phones;
};

bool valid(const std::string &phone_number) // we dont change phone number
{
    bool bit;
    if (!phone_number.empty()) {
        //phone number only contains digits, 2323-3223 is not valid, neither 233xxas
        for (auto ch : phone_number) {
            if (!isdigit(ch)) {
                bit = false;
                break;
            } else {
                bit = true;
            }
        }
    } else {
        bit = false;
    }

    return bit;
}

std::string format(std::string phone_number)
{
    std::string pre_fix = "010-";
    pre_fix.append(phone_number);
    return pre_fix;
}

int main()
{
    //read PersonInfo from file
    /*
    morgan 2015552368 8625550123
    drew 9735550130
    lee 6095550132 2015550175 8005550000
    */
    std::string new_file_path = std::filesystem::current_path();
    new_file_path.append("/file_8p13.txt");

    std::fstream file_p;
    file_p.open(new_file_path);

    std::string readline; //hold each line from input file
    std::vector<PersonInfo> people; //hold all the records from the input file

    //first get all data from input file and store in people
    while(getline(file_p, readline)){ //the forth newline will also be read, loop four times
        std::stringstream p_info;
        //p_info to hold each people info
        // the forth newline will also be read
        if (!readline.empty()){
            p_info.str(readline);
            std::cout << "getline from input file: " << readline << std::endl;

            PersonInfo info; // create object to hold current line record's data
        //first get name

        p_info >> info.name;

        //get remaining phone numbers
        std::string p_number;
        while(p_info >> p_number){
            info.phones.push_back(p_number);
        }

        people.push_back(info);
        //p_info will be destroyed each while loop, no need p_info.clear() to reset its state
        }
    }

    std::cout << "Total got " << people.size() << " Person info from input file." << std::endl;
    std::cout << "========" << std::endl; 

    file_p.close(); //close file stream

    //now process people
    for (const auto &entry : people){ //process each person info
        std::ostringstream formatted, badNums;
        for (auto const &nums :entry.phones) { //for each person's each number
            if (!valid(nums)) {
                badNums << " " << nums; //string in badNums
            } else
                // write to formatted string
                formatted << " " << format(nums);
        }
        if (badNums.str().empty()){//no bad number
            std::cout << "People info: " << std::endl;
            std::cout << "valid info: " << entry.name << " " << formatted.str() << std::endl;
        } 
        else{ //print both bad and valid
            std::cout << "People info: " << std::endl;
            std::cerr << "input error: " << entry.name << " invalid number(s) " << badNums.str() << std::endl;
            std::cout << "valid info: " << entry.name << " " << formatted.str() << std::endl;
        }
    }

    return 0;
}