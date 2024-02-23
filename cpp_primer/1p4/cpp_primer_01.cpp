#include<iostream>
int main()
{
	// currval is the numebr we're counting; we'll read new values into val
	int currVal = 0, val = 0;
	// read first number and ensure that we have data to process
	if (std::cin >> currVal)
	{
		int cnt = 1; // store the count for the current value we're processing
		while (std::cin >> val)
		{
			// read the remaining numebrs
			if (val == currVal) //if the values are the same
				++cnt; //add 1 to cnt
			else 
			{
				//otherwise, print the count for the previous value
				std::cout << currVal << " occurs " << cnt << " times" << std::endl;
				currVal = val; // remember the new value
				cnt = 1;
			}
		} //while loop ends here
		// remember to print the count for the last value in the life
		std::cout << currVal << " occurs " << cnt << " times" << std::endl;
	} // outermost if statement ends here
	return 0;
}
