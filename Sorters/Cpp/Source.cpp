#include <fstream>
#include <string>
#include <chrono>
#include <iostream>
#include "Windows.h"

#define FILES_AMOUNT 1000
#define FOLDERS_AMOUNT 50

int main()
{
	std::cout << "Started" << std::endl;
	// sleep 10 minutes to get virtual machine some time to wake up
	Sleep(600000);

	auto total = 0.0;
	for (auto k = 0; k < FOLDERS_AMOUNT; k++)
	{
		auto start = std::chrono::system_clock::now();

		for (auto i = 0; i < FILES_AMOUNT - 1; i++)
		{
			auto name1 = "C://Data//" + std::to_string(k) + "//" + std::to_string(i);

			std::ifstream file1_in(name1);
			int number1;
			file1_in >> number1;
			file1_in.close();

			for (auto j = i + 1; j < FILES_AMOUNT; j++)
			{
				auto name2 = "C://Data//" + std::to_string(k) + "//" + std::to_string(j);

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
		total += elapsed_seconds.count();
		std::cout << "folder " << k << " elapsed time: " << elapsed_seconds.count() << " average time: " << total / k << std::endl;

		// sleep 5 minutes just to relax
		Sleep(300000);
	}

	system("pause");
	return 0;
}