import java.io.*;

public class Main
{
	public static void main(String[]args) throws IOException, InterruptedException {
		System.out.println("Started");
		Thread.sleep(600000);

		final short FILES_AMOUNT = 1000;
		final short FOLDERS_AMOUNT = 50;
		double total = 0.0;
		for (int k = 0; k < FOLDERS_AMOUNT; k++)
		{
			long startTime = System.currentTimeMillis();

			for (int i = 0; i < FILES_AMOUNT - 1; i++)
			{
				String name1 = "C://Data//" + k + "//" + i;
				BufferedReader reader1 = new BufferedReader(new FileReader(name1));
				int number1 = Integer.parseInt(reader1.readLine());
				reader1.close();
	
				for (int j = i + 1; j < FILES_AMOUNT; j++)
				{
					String name2 = "C://Data//" + k + "//" + j;
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
			total += estimatedTime;
			System.out.println("folder " + k + " elapsed time: " + estimatedTime + " average time: " + (total / k));

			Thread.sleep(300000);
		}

	  System.in.read();
	}
}
