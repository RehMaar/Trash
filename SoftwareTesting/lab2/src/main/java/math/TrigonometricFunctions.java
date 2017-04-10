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
        return ((Math.abs(x / Math.PI) - (double)((int)Math.abs(x / Math.PI)))< 1e-6) ? 1 : b.calcSin(2 * x) / (2*b.calcSin(x));
    }

    public Double calcTan(Double x){
        Double eps = 1e-6;
        return  Math.abs(calcCos(x)) < eps ? Double.NaN : b.calcSin(x)/calcCos(x);
    }

    public Double calcCot(Double x){
        Double eps = 1e-6;
        return Math.abs(b.calcSin(x)) < eps ? Double.NaN : calcCos(x)/b.calcSin(x);
    }

    public Double calcSec(Double x){
        Double eps = 1e-6;
        return Math.abs(calcCos(x)) < eps ? Double.NaN : 1/calcCos(x);
    }
}
