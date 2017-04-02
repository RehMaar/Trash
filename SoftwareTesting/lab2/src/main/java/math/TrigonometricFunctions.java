/**
 * Created by skyD9 on 02.04.2017.
 */
public class TrigonometricFunctions {
    TrigonometricBase b = new TrigonometricBase();
    public Double calcCos(Double x){
        return b.calcSin(2 * x)/(2*b.calcSin(x));
    }
    public Double calcTan(Double x){
        TrigonometricFunctions f = new TrigonometricFunctions();
        return b.calcSin(x)/f.calcCos(x);
    }
    public Double calcCot(Double x){
        TrigonometricFunctions f = new TrigonometricFunctions();
        return f.calcCos(x)/b.calcSin(x);
    }
    public Double calcSec(Double x){
        TrigonometricFunctions f = new TrigonometricFunctions();
        return 1/f.calcCos(x);
    }
}
