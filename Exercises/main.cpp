#include <iostream>

#include "Helpers\RunTimeTimer.h"
#include "Logics\Logic.h"

int main(int argc, const char* argv[])
{
	try
	{
		RunTimeTimer runTimeTimer;

		Logic logic("C:\\Users\\Márton\\Documents\\Visual Studio 2015\\Projects\\NAI exercises\\Exercises");
		//Logic logic;

		if (argc == 1)
		{
			throw "ERROR: Wrong argument count. Read README.TXT or use -help argumentum.";
		}

		if (argv[1] != "-help")
		{
			std::cout.precision(10);
			std::cout << "Program started." << std::endl;
			runTimeTimer.addStartTime(clock());

			if (argc == 3)
			{
				logic.generateResult(argv[1], argv[2]);
			}
			else
			{
				logic.generateResult(argv[1]);
			}

			runTimeTimer.addEndTime(clock());
			std::cout << "Program ended in " << runTimeTimer.getRunTimeInMS() << "." << std::endl;
			std::cin.get();
			
		}
		else if (argv[1] == "-help")
		{
			std::cout << "<PROGRAMNAME> <INPUT_ARG1>" << std::endl
				<< "<PROGRAMNAME> <INPUT_ARG1> <INPUT_ARG2>" << std::endl
				<< "You have to set the first argument as an exercise number," << std::endl
				<< "then if you want you can set the second agrument as an input file number." << std::endl;
		}
	}
	catch (std::string msg)
	{
		std::cout << msg.c_str() << std::endl
			<< "Read the help with the -help switch or the README.TXT file." << std::endl
			<< "The program will exit now." << std::endl;
		std::cin.get();
		exit(1);
	}

	return 0;
}
