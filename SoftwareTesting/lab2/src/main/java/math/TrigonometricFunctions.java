/**
 * Created by skyD9 on 02.04.2017.
 */
package math;
public class TrigonometricFunctions {
    TrigonometricBase b = new TrigonometricBase();
    private Logger log_obj = new Logger();
    private Double y;
    public Double calcSin(Double x){
        y = b.calcSin(x);
        log_obj.log(x,y,"src/logs/sin.csv");
        return y;
    }
    public Double calcCos(Double x){
        y = b.calcSin(2 * x) / (2*b.calcSin(x));
        log_obj.log(x,y,"src/logs/cos.csv");
        return y;
    }
    public Double calcTan(Double x){
        y = b.calcSin(x)/calcCos(x);
        log_obj.log(x,y,"src/logs/tan.csv");
        return y;
    }
    public Double calcCot(Double x){
        y = calcCos(x)/b.calcSin(x);
        log_obj.log(x,y,"src/logs/cot.csv");
        return y;
    }
    public Double calcSec(Double x){
        y = 1/calcCos(x);
        log_obj.log(x,y,"src/logs/sec.csv");
        return y;
    }
}
