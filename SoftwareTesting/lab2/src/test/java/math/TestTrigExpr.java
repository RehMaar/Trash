package math;

import org.junit.Before;
import org.junit.Test;
import static org.junit.Assert.assertTrue;

/**
 * Created by skyD9 on 09.04.2017.
 */
public class TestTrigExpr {
    private TrigonometricExpression expr;

    @Before
    public void init() {
        this.expr = new TrigonometricExpression();
    }

    private Double testExpr(Double x) {
        return  ((((Math.pow((1/Math.cos(x) - Math.cos(x)), 3)) -
                (Math.tan(x) - Math.tan(x))) * (1/Math.cos(x))) *
                (((((1/Math.cos(x)) + Math.tan(x)) + (Math.sin(x) * Math.cos(x)))
                / ((Math.pow(Math.cos(x)/Math.sin(x), 2)) / (1/Math.cos(x)))) + ((Math.sin(x)
                        / (1/Math.cos(x))) * (Math.cos(x)/Math.sin(x)))));
    }

    @Test
    public void testExprResults1() {
        Double eps = 0.0001;
        for (Double i = -4.0; i < -2; i += 0.1) {
            assertTrue(Math.abs(expr.eval(i) - this.testExpr(i)) <= eps);
        }
    }

    @Test
    public void testExprResults2() {
        Double eps = 0.0001;
        for (Double i = -7.5; i < -6.5; i += 0.1) {
            assertTrue(Math.abs(expr.eval(i) - this.testExpr(i)) <= eps);
        }
    }

    @Test
    public void testExprResults3() {
        Double eps = 0.0001;
        for (Double i = 2.0; i < 4; i += 0.1) {
            assertTrue(Math.abs(expr.eval(i) - this.testExpr(i)) <= eps);
        }
    }

    @Test
    public void testExprResults4() {
        Double eps = 0.0001;
        for (Double i = 5.0; i < 7.0; i += 0.1) {
            assertTrue(Math.abs(expr.eval(i) - this.testExpr(i)) <= eps);
        }
    }

    @Test
    public void testExprInUndefinedPoints() {
        for (Double i = -5 * Math.PI; i <= 5 * Math.PI ; i += Math.PI) {
            assertTrue(expr.eval(i).equals(Double.NaN));
        }
    }
}
