#include <fstream>
#include <string>
#include <iostream>

#define FILES_AMOUNT 1000
#define FOLDERS_AMOUNT 50

int main()
{
	for (auto j = 0; j < FOLDERS_AMOUNT; j++)
	{
		for (auto i = 0; i < FILES_AMOUNT-1; i++)
		{
			std::ifstream file1("C://Data//" + std::to_string(j) + "//" + std::to_string(i));
			std::ifstream file2("C://Data//" + std::to_string(j) + "//" + std::to_string(i+1));
			int number1, number2;
			file1 >> number1;
			file2 >> number2;

			if (number1 > number2)
			{
				std::cout << "Not sorted: Files = " << i << " and " << i + 1
				<< " in folder = " << j
				<< " numbers = " << number1 << " and " << number2 << std::endl;

				file1.close();
				file2.close();

				system("pause");
				return 1;
			}

			file1.close();
			file2.close();
		}
		std::cout << "folder " << j << " sorted" << std::endl;
	}

	std::cout << "all folders sorted" << std::endl;

	system("pause");
	return 0;
}