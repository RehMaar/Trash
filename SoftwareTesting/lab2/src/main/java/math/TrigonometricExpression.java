/**
 * Created by skyD9 on 02.04.2017.
 */
package math;

public class TrigonometricExpression implements IExpression {

    public Double eval(Double x){
        TrigonometricFunctions f = new TrigonometricFunctions();
        return ((((Math.pow((f.calcSec(x) - f.calcCos(x)), 3)) -
                (f.calcTan(x) - f.calcTan(x)))
                * f.calcSec(x)) * ((((f.calcSec(x) + f.calcTan(x)) + (f.calcSin(x)
                * f.calcCos(x))) / ((Math.pow(f.calcCot(x), 2)) / f.calcSec(x))) +
                ((f.calcSin(x) / f.calcSec(x)) * f.calcCot(x))));
    }
}
