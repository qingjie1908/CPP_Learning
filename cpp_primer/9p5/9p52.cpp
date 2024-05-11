#include <iostream>
#include <string>
#include <stack>

std::string process_exprs(std::string &exprs)
{
    std::stack<char> stack_char;
    auto expr_begin = exprs.begin();
    while(expr_begin != exprs.end()){ //copy exprs into stack_char
        stack_char.push(*expr_begin);
        ++expr_begin;
    }

    std::stack<char> stack_char_reverse; // stack to store element poped by stack_char
    
    //first, check numbers of '(' and ')' are the same in stack_char
    int open_p_num = 0;
    int close_p_num = 0;

    while(!stack_char.empty()){ //check every char in stack_char

        if(stack_char.top() == '('){
            ++open_p_num;

            //first store the element which will be poped later by stack_char
            //since we dont want to () in result, we dont store '(' or ')'
            //directly pop
            //stack_char_reverse.push(stack_char.top());

            //then pop out the element to check next stack_char.top()
            stack_char.pop();
        } else if(stack_char.top() == ')'){
            ++close_p_num;

            //first store the element which will be poped later by stack_char
            //since we dont want to () in result, we dont store '(' or ')'
            //directly pop
            //stack_char_reverse.push(stack_char.top());

            //then pop out the element to check next stack_char.top()
            stack_char.pop();
        } else { // char in stack_char is neither '(' or ')', so we save them

            //first store the element which will be poped later by stack_char
            stack_char_reverse.push(stack_char.top());

            //then pop out the element to check next stack_char.top()
            stack_char.pop();
        }
    }

    //after previous while loop
    //we got the number of open and close parenthesis
    //also store all other char in stack_char_reverse

    if(open_p_num == close_p_num){ //paried, which means it's valid expression
        //now stack_char is empty
        //we need to pop item from stack_char_reverse
        //and save them in stack_char
        //this time, after save, stack_char does not contain open or close parenthesis
        while(!stack_char_reverse.empty()){
            //first restore element from stack_char_reverse back to stack_char
            stack_char.push(stack_char_reverse.top());

            //then pop this element in stack_char_reverse so that we can move on to next element
            stack_char_reverse.pop();
        }
        //after previous while loop
        //stack_char_reverse is empty
        //stack_char back to orginal except without parenthesis
    } else {
        std::cerr << "this is not a valid expression since they don't have paird open-close parenthesis." << std::endl;
    }
    
    //now we return the valid expression without parenthesis
    std::string valid_expr;
    auto begin =  valid_expr.begin();

    while(!stack_char.empty()){
        begin = valid_expr.insert(begin, stack_char.top()); //insert element before begin, and return begin point to the insert element

        stack_char.pop(); //move on to next char
    }

    return valid_expr;

}

int main()
{
    
    

    std::string expr1 = "12+(23 * 12)-23 / (9 -5)+5";
    std::string expr2 = "12+34-56-((78-9)+10)";
    std::string expr3 = "(12+34)-(56-((78-9)+10))";
    std::string expr4 = "((12+34-(56-10)-1"; //invalid expression
    std::string expr5 = "12+34)-(56-10)-1"; //invalid expression

    std::cout << process_exprs(expr1) << std::endl;
    std::cout << process_exprs(expr2) << std::endl;
    std::cout << process_exprs(expr3) << std::endl;
    std::cout << process_exprs(expr4) << std::endl;
    std::cout << process_exprs(expr5) << std::endl;

    return 0;
}