/**
 * Created by skyD9 on 02.04.2017.
 */
package math;
public class TrigonometricExpression {

    private Logger log_obj = new Logger();

    private Double y;

    public Double eval(Double x){
        TrigonometricFunctions f = new TrigonometricFunctions();
        y= (Math.pow((f.calcSec(x)-f.calcCos(x)),3)-
                (f.calcTan(x)-f.calcTan(x)))*
                f.calcSec(x)*
                (((f.calcSec(x)+f.calcTan(x)+f.calcCos(x)*f.calcSin(x))/
                        (Math.pow(f.calcCot(x),2)/f.calcSec(x)))+
                f.calcSin(x)/f.calcSec(x)* f.calcCot(x));
        log_obj.log(x,y,"src/logs/trig_eval.csv");
        return y;
    }
}
