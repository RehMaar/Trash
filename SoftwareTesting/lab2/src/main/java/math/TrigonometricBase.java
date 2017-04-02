/**
 * Created by skyD9 on 02.04.2017.
 */
package math;
public class TrigonometricBase {
    private Double CalibrateX(Double x) {
        double del = Math.PI * 2;
        if (x < 0)
            del *= -1;
        while (Math.abs(x) > 30.0) {
            x -= del;
        }
        return x;
    }

    public Double calcSin(Double x) {
        x = CalibrateX(x);
        Double xn = x;
        Double prevSum = 0.0;
        Double sum = x;
        final Double EPS = 1e-10, INF = 1.0e8;


        for (Integer n = 1; Math.abs(Math.abs(sum) - Math.abs(prevSum)) > EPS; n++) {
            prevSum = sum;
            xn *= (-x*x)/((2*n+1)*2*n);
            sum += xn;
        }
        return Math.abs(sum) > INF ? INF : sum;

    }
}
