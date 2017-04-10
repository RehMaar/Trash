package math;

import java.io.*;

public class Logger implements LoggerInterface {
    public void log(Double x, Double y, String path){
        try
        {
            FileWriter writer = new FileWriter(path, true);
            String text = x+" "+y+"\n";
            writer.write(text);
            writer.flush();
        }
        catch(IOException ex){
            System.out.println(ex.getMessage());
        }
    }
}
