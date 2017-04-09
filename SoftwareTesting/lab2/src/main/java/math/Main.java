package math;

/**
 * Created by skyD9 on 09.04.2017.
 */
public class Main {
    public static void main(String[] args){
        TrigonometricFunctions a = new TrigonometricFunctions();
        Logger l = new Logger();
        l.log(Math.PI,a.calcCot(Math.PI),"logs/main.csv");
    }
}
