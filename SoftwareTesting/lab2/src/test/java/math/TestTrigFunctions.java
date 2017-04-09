package math;

import org.junit.Before;
import org.junit.Test;

import static org.junit.Assert.assertTrue;

/**
 * Created by skyD9 on 09.04.2017.
 */
public class TestTrigFunctions {
    private TrigonometricFunctions fn;

    @Before
    public void init() {
        fn = new TrigonometricFunctions();
    }

    @Test
    public void testEraseCos1() {
        Double eps = 0.0001;
        for (Double i = Math.PI + Math.PI/6; i <= Math.PI  + 5*Math.PI/6 + eps ; i += Math.PI/6) {
            assertTrue(Math.abs(fn.calcCos(i) - Math.cos(i)) <= eps);
        }
    }

    @Test
    public void testEraseCos2() {
        Double eps = 0.0001;
        for (Double i = -3*Math.PI + Math.PI/6; i <= -3*Math.PI  + 5*Math.PI/6 + eps ; i += Math.PI/6) {
            assertTrue(Math.abs(fn.calcCos(i) - Math.cos(i)) <= eps);
        }
    }

    @Test
    public void testDecreaseCos1() {
        Double eps = 0.0001;
        for (Double i = Math.PI/6; i <= 5*Math.PI/6 + eps ; i += Math.PI/6) {
            assertTrue(Math.abs(fn.calcCos(i) - Math.cos(i)) <= eps);
        }
    }


    @Test
    public void testDecreaseCos2() {
        Double eps = 0.0001;
        for (Double i = 10*Math.PI+Math.PI/6; i <= 10*Math.PI+5*Math.PI/6 + eps ; i += Math.PI/6) {
            assertTrue(Math.abs(fn.calcCos(i) - Math.cos(i)) <= eps);
        }
    }

    @Test
    public void testTan1() {
        Double eps = 0.0001;
        for (Double i = 3*Math.PI/2+eps; i < 5*Math.PI/2 ; i += Math.PI/6) {
            assertTrue(Math.abs(fn.calcTan(i) - Math.tan(i)) <= eps);
        }
    }

    @Test
    public void testTan2() {
        Double eps = 0.0001;
        for (Double i = 5*Math.PI/2+eps; i < 7*Math.PI/2 ; i += Math.PI/6) {
            assertTrue(Math.abs(fn.calcTan(i) - Math.tan(i)) <= eps);
        }
    }

    @Test
    public void testTanInUndefinedPoints() {
        for (Double i = -5*Math.PI/2; i <= 5*Math.PI/2 ; i += Math.PI) {
            assertTrue(fn.calcTan(i).equals(Double.NaN));
        }
    }

    @Test
    public void testCot1() {
        Double eps = 0.0001;
        for (Double i = Math.PI/6; i <= 5*Math.PI/6 + eps ; i += Math.PI/6) {
            assertTrue(Math.abs(fn.calcCot(i) - Math.cos(i)/Math.sin(i)) <= eps);
        }
    }

    @Test
    public void testCot2() {
        Double eps = 0.0001;
        for (Double i = -4*Math.PI + Math.PI/6; i <= -4*Math.PI  + 5*Math.PI/6 + eps ; i += Math.PI/6) {
            assertTrue(Math.abs(fn.calcCot(i) - Math.cos(i)/Math.sin(i)) <= eps);
        }
    }

    @Test
    public void testCotInUndefinedPoints() {
        for (Double i = -5*Math.PI; i <= 5*Math.PI ; i += Math.PI) {
            assertTrue(fn.calcCot(i).equals(Double.NaN));
        }
    }


    @Test
    public void testSec1() {
        Double eps = 0.0001;
        for (Double i = 3*Math.PI/2+eps; i < 5*Math.PI/2 ; i += Math.PI/6) {
            assertTrue(Math.abs(fn.calcSec(i) - 1/Math.cos(i)) <= eps);
        }
    }

    @Test
    public void testSec2() {
        Double eps = 0.0001;
        for (Double i = 5*Math.PI/2+eps; i < 7*Math.PI/2 ; i += Math.PI/6) {
            assertTrue(Math.abs(fn.calcSec(i) - 1/Math.cos(i)) <= eps);
        }
    }

    @Test
    public void testSecInUndefinedPoints() {
        for (Double i = -5*Math.PI/2; i <= 5*Math.PI/2 ; i += Math.PI) {
            assertTrue(fn.calcSec(i).equals(Double.NaN));
        }
    }
}
