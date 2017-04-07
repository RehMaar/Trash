/**
 * Created by skyD9 on 02.04.2017.
 */
package math;
public class TrigonometricFunctions {
    TrigonometricBase b = new TrigonometricBase();
    public Double calcSin(Double x){
        return b.calcSin(x);
    }
    public Double calcCos(Double x){
        return b.calcSin(2 * x) / (2*b.calcSin(x));
    }
    public Double calcTan(Double x){
        return b.calcSin(x)/calcCos(x);
    }
    public Double calcCot(Double x){
        return calcCos(x)/b.calcSin(x);
    }
    public Double calcSec(Double x){
        return 1/calcCos(x);
    }
}
