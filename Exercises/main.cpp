#include <iostream>

#include "Helpers\RunTimeTimer.h"
#include "Logics\Logic.h"

int main(int argc, const char* argv[])
{
	RunTimeTimer runTimeTimer;

	std::string root = std::string((__FILE__));
	root.pop_back(); //m
	root.pop_back(); //a
	root.pop_back(); //i
	root.pop_back(); //n
	root.pop_back(); //.
	root.pop_back(); //c
	root.pop_back(); //c
	root.pop_back(); //p

	Logic logic(root);

	std::cout.precision(10);
	std::cout << "Program started." << std::endl;
	runTimeTimer.addStartTime(clock());

	if (argc == 1)
	{
		std::cout << "ERROR: Wrong argument usage. Read README.TXT or use -help argumentum." << std::endl;
		exit(1);
	}

	if (argv[1] != "-help")
	{
		for (int i = 1; i < argc; ++i)
		{
			logic.generateResult(argv[i]);
		}
	}
	else if (argv[1] == "-help")
	{
		std::cout << "<PROGRAMNAME> <INPUT_ARG1> <INPUT_ARG2> ..." << std::endl
			<< "In default you have to give exercise numbers in next arguments. " << std::endl;
	}

	runTimeTimer.addEndTime(clock());
	std::cout << "Program ended in " << runTimeTimer.getRunTimeInMS() << "." << std::endl;
	std::cin.get();

	return 0;
}
