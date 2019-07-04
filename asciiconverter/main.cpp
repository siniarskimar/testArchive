#include <iostream>
#include <vector>
#include <sstream>

bool endProgram = false;

std::vector<std::string> splitString(std::string inStr, const char delim) {
	std::stringstream ss(inStr);
	std::string current = "";
	std::vector<std::string> split;
	while(std::getline(ss, current, delim)) {
		split.emplace_back(current);
	}
	return split;
}

void printCommands() {
	std::cout << "\nAvailable commands: \n" << std::endl;
	std::cout << "?; help - displays help" <<std::endl<<std::flush;
	std::cout << "to - converts characters into ASCII" <<std::endl;
	std::cout << "from - converts ASCII codes to characters (separated by spaces)" <<std::endl;
	std::cout << "end - closes the program\n" <<std::endl;
}

int main(){
	std::cout << "ASCII Converter" << std::endl;
	printCommands();
	std::string input;
	std::vector<std::string> args;
	while(!endProgram) {
		std::cout << "=> ";
		std::getline(std::cin, input);
		args = splitString(input, ' ');

		if(args[0] == "end")
			endProgram = true;
		else if(args[0] == "to") {
			for(int i = 1; i < args.size(); i++) {
				for(int ch = 0; ch < (args[i]).length(); ch++) {
					std::cout << (int)(args[i][ch]) << " ";
				}
				std::cout << std::endl;
			}
		} else if(args[0] == "from") {
			for(int i = 1; i < args.size(); i++) {
				std::cout << (char) (std::stoi(args[i]));
			}
			std::cout << std::endl;
		} else if(args[0] == "?" || args[0] == "help") {
			printCommands();
		} else {
			std::cout << "Unknown command: " << args[0] << std::endl;
		}
	}

	return 0;
}