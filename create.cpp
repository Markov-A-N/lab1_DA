#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdlib>

int main(int argc, char *argv[]) {
	std::ofstream file(argv[1]);
	srand(time(0));
	size_t size = atoi(argv[2]);
	char value[65];
	for (register int i = 0; i < size; i++) {
		file << rand() % 65535 << " ";
		for (register int j = 0; j < 64; j++) {
			value[j] = (char) (rand() % 26 + 97);
		}
		value[64] = '\0';
		file << value << "\n";
	}
	return 0;
}