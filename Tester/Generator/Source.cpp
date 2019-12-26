#include <fstream>
#include <ctime>
#include <string>
#include <unordered_set>
#include <direct.h>
#include <iostream>

#define FILES_AMOUNT 1000
#define FOLDERS_AMOUNT 50

int main()
{
	if (_mkdir("C://Data") != 0)
	{
		std::cout << "failed to create root folder" << std::endl;
		system("pause");
		return 1;
	}

	for (auto i = 0; i < FOLDERS_AMOUNT; i++)
	{
		std::string path = "C://Data//" + std::to_string(i);
		if (_mkdir(path.c_str()) != 0)
		{
			std::cout << "failed to create folder " << i << std::endl;
			system("pause");
			return 2;
		}

		// fill the set with random numbers
		std::unordered_set<int> numbers;

		srand(time(nullptr));

		while (numbers.size() < FILES_AMOUNT)
		{
			auto random = rand() % 9999 + 1;
			numbers.insert(random);
		}

		// create files
		auto count = 0;
		for (const auto &number : numbers)
		{
			std::ofstream file("C://Data//" + std::to_string(i) + "//" + std::to_string(count));
			file << number;
			file.close();
			count++;
		}

		std::cout << "folder " << i << " ready" << std::endl;
	}

	std::cout << "all folders ready" << std::endl;
	system("pause");

	return 0;
}