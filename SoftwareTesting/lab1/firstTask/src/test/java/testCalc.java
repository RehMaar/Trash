import static junit.framework.Assert.*;
import org.junit.Test;


public class testCalc {

    private boolean EPS_Equals(double a, double b, double EPS)
    {
        return Math.abs(b - a) < EPS;
    }

    @Test
    public void testCalcSec() {

        Calc tester = new Calc();
        try {

            final double EPS = 1.0e-5, INF = 1.0e8;
            assertTrue("at test 1:", EPS_Equals(1.0, tester.calcSec(0.0), EPS));
            assertTrue("at test 2:", EPS_Equals(-1.0, tester.calcSec(3.0), EPS));
            assertTrue("at test 3:", EPS_Equals(INF, tester.calcSec(Math.PI / 2), EPS));
            assertTrue("at test 4:", EPS_Equals(INF, tester.calcSec(Math.PI / 2 * 3), EPS));
            assertTrue("at test 5:", EPS_Equals(1/Math.cos(6000000.0), tester.calcSec(6000000.0), EPS));
        }
        catch (Exception e){
        }
    }
}
