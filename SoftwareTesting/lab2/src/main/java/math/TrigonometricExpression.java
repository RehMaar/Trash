/**
 * Created by skyD9 on 02.04.2017.
 */
public class TrigonometricExpression {
    public Double eval(Double x) {
        TrigonometricFunctions f = new TrigonometricFunctions();
        TrigonometricBase b = new TrigonometricBase();
        return (Math.pow((f.calcSec(x)-f.calcCos(x)),3)-
                (f.calcTan(x)-f.calcTan(x)))*
                f.calcSec(x)*
                (((f.calcSec(x)+f.calcTan(x)+f.calcCos(x)*b.calcSin(x))/
                        (Math.pow(f.calcCot(x),2)/f.calcSec(x)))+
                b.calcSin(x)/f.calcSec(x)* f.calcCot(x));
    }
}
