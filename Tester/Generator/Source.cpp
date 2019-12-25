#include <fstream>
#include <ctime>
#include <string>
#include <unordered_set>

#define FILES_AMOUNT 1000

int main()
{
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
		std::ofstream file("..//..//Data//" + std::to_string(count));
    file << number;
		file.close();
		count++;
	}

	return 0;
}