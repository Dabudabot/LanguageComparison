#include <fstream>
#include <string>

#define FILES_AMOUNT 1000

int main()
{
	for (auto i = 0; i < FILES_AMOUNT - 1; i++)
	{
		std::fstream file1("..//..//Data//" + std::to_string(i) + ".txt", std::fstream::in | std::fstream::out);
		int number1;
		file1 >> number1;

		for (auto j = i + 1; j < FILES_AMOUNT; j++)
		{
			std::fstream file2("..//..//Data//" + std::to_string(j) + ".txt", std::fstream::in | std::fstream::out);
			int number2;
			file1 >> number2;

			if (number1 > number2)
			{
				file2 << number1;
				number1 = number2;
			}

			file2.close();
		}

		file1 << number1;
		file1.close();
	}

	return 0;
}