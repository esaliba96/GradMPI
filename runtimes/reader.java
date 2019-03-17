import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;

public class reader {
	public static void main(String[] args) {
		BufferedReader reader;
		try {
			reader = new BufferedReader(new FileReader("time"));
			String line = reader.readLine();
			int i =0;
         while (line != null) {			
            if (i == Integer.valueOf(args[0])) {
               System.out.println(line.split("time")[1].trim());
            }
            i++;
            if (i > 2) i =0;
            // read next line
				line = reader.readLine();
			}
			reader.close();
		} catch (IOException e) {
			e.printStackTrace();
		}
	}
}