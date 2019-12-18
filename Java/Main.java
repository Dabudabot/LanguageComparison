


public static void main() {

  const short FILES_AMOUNT = 1000;

  for (short i = 0; i < FILES_AMOUNT - 1; i++)
  {
    int number1;
    BufferedReader reader1 = new BufferedReader(new FileReader("..//Data//" + i + ".txt"));
    number1 = Integer.parseInt(reader1.readLine());

    for (short j = i+1; j < FILES_AMOUNT; j++)
    {
      int number2;
      BufferedReader reader2 = new BufferedReader(new FileReader("..//Data//" + j + ".txt"));
      number2 = Integer.parseInt(reader2.readLine());
      reader2.close();

      if (number1 > number2)
			{
        BufferedWriter writer2 = new BufferedWriter(new FileWriter("..//Data//" + j + ".txt"));
        writer2.write(number1);
        writer2.close();

				number1 = number2;
      }
    }

    reader1.close();
    BufferedWriter writer1 = new BufferedWriter(new FileWriter("..//Data//" + i + ".txt"));
    writer1.write(number1);
    writer1.close();
    
  }
}