package math;

import java.io.*;

/**
 * Created by anki0216 on 03.04.2017.
 */
public class Logger implements Loggable {
    @Override
    public void log(Double x, Double y, String path){
        try(FileWriter writer = new FileWriter(path, true))
        {
            String text = x+" "+y+"\n";
            writer.write(text);
            writer.flush();
        }
        catch(IOException ex){
            System.out.println(ex.getMessage());
        }
    }
}
