import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.*;
import java.io.*;


public class std {
    public static void main(String[] args) {

      BufferedReader reader;
      try {
        File folder = new File(args[0]);
        File[] listOfFiles = folder.listFiles();
        for (File f : listOfFiles) {
          ArrayList<Double> times = new ArrayList<Double>();      

          reader = new BufferedReader(new FileReader(args[0] + "/" + f.getName()));
          String line = reader.readLine();
          int i =0;
          while (line != null) {        
              times.add(Double.valueOf(line));
              line = reader.readLine();
          }
          reader.close();
          System.out.println(f.getName());
          double SD = calculateSD(times);
          System.out.format("Standard Deviation = %.2f\n", SD);
          int minIndex = times.indexOf(Collections.min(times));
          int maxIndex = times.indexOf(Collections.max(times));
        //  System.out.format("Min = %.2f\n", times.get(minIndex));
        //  System.out.format("Max = %.2f\n", times.get(maxIndex));
        }
       } catch (IOException e) {
         e.printStackTrace();
      }
     
    }

    public static double calculateSD(ArrayList<Double> numArray)
    {
        double sum = 0.0, standardDeviation = 0.0;
        int length = numArray.size();

        for(double num : numArray) {
            sum += num;
        }

        double mean = sum/length;

        for(double num: numArray) {
            standardDeviation += Math.pow(num - mean, 2);
        }
        System.out.format("Mean = %.2f\n", mean);

        return Math.sqrt(standardDeviation/length);
    }
}