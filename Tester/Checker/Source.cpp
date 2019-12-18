#include <fstream>
#include <string>
#include <unordered_set>
#include <iostream>

#define FILES_AMOUNT 1000

int main()
{
	for (auto i = 0; i < FILES_AMOUNT-1; i++)
	{
		std::ifstream file1("..//..//Data//" + std::to_string(i) + ".txt");
		std::ifstream file2("..//..//Data//" + std::to_string(i+1) + ".txt");
		int number1, number2;
		file1 >> number1;
		file2 >> number2;

		if (number1 > number2)
		{
			std::cout << "Not sorted: Files = " << i << " and " << i + 1
			<< " numbers = " << number1 << " and " << number2 << std::endl;
			
			file1.close();
			file2.close();
			
			return 1;
		}

		file1.close();
		file2.close();
	}

	std::cout << "Sorted" << std::endl;

	return 0;
}