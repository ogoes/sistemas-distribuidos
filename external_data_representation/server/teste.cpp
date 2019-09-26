#include <iostream>
#include <string>
#include <cstdlib>
#include <cstring>

int main () {

	std::string a("abc");



	std::cout << strlen(a.c_str()) << std::endl;
	return 0;
}
