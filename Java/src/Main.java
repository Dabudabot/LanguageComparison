import java.io.*;

public class Main
{
	public static void main(String[]args)  throws IOException {

	  final short FILES_AMOUNT = 1000;
	  
	  long startTime = System.currentTimeMillis();

	  for (int i = 0; i < FILES_AMOUNT - 1; i++)
	  {
		String name1 = "..//Data//" + i + ".txt";
		BufferedReader reader1 = new BufferedReader(new FileReader(name1));
		int number1 = Integer.parseInt(reader1.readLine());
		reader1.close();

		for (int j = i + 1; j < FILES_AMOUNT; j++)
		{
		  String name2 = "..//Data//" + j + ".txt";
		  BufferedReader reader2 = new BufferedReader(new FileReader(name2));
		  int number2 = Integer.parseInt(reader2.readLine());

		  reader2.close();

		  if (number1 > number2)
		  {
			BufferedWriter writer2 = new BufferedWriter(new FileWriter(name2));
			writer2.write(String.valueOf(number1));
			writer2.close();
			number1 = number2;
		  }
		}
		
		BufferedWriter writer1 = new BufferedWriter(new FileWriter(name1));
		writer1.write(String.valueOf(number1));
		writer1.close();
	  }
	  
	  double estimatedTime = (System.currentTimeMillis() - startTime) / 1000.0;
	  
	  System.out.println("elapsed time: " + estimatedTime);

	  System.in.read();
	}
}
