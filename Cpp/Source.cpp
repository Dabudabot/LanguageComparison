#include <fstream>
#include <string>
#include <chrono>
#include <iostream>

#define FILES_AMOUNT 1000

int main()
{
	auto start = std::chrono::system_clock::now();
	
	for (auto i = 0; i < FILES_AMOUNT - 1; i++)
	{
		auto name1 = "..//Data//" + std::to_string(i) + ".txt";
		
		std::ifstream file1_in(name1);
		int number1;
		file1_in >> number1;
		file1_in.close();

		for (auto j = i + 1; j < FILES_AMOUNT; j++)
		{
			auto name2 = "..//Data//" + std::to_string(j) + ".txt";

			std::ifstream file2_in(name2);
			int number2;
			file2_in >> number2;
			file2_in.close();

			if (number1 > number2)
			{
				std::ofstream file2_out(name2);
				file2_out << number1;
				file2_out.close();
				number1 = number2;
			}
		}

		std::ofstream file1_out(name1);
		file1_out << number1;
		file1_out.close();
	}

	auto end = std::chrono::system_clock::now();

	std::chrono::duration<double> elapsed_seconds = end - start;

	std::cout << "elapsed time: " << elapsed_seconds.count() << std::endl;

	return 0;
}