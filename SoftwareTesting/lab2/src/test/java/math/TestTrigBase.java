package math;

import org.junit.Before;
import org.junit.Test;

import static org.junit.Assert.assertTrue;

/**
 * Created by skyD9 on 09.04.2017.
 */
public class TestTrigBase {
    private TrigonometricBase fn;

    @Before
    public void init() {
        this.fn = new TrigonometricBase();
    }



    @Test
    // Test from -PI/2 to Pi/2
    public void testErase1() {
        Double eps = 0.0001;
        for (Double i = -Math.PI/2; i <= Math.PI/2 ; i += Math.PI/4) {
            assertTrue(Math.abs(fn.calcSin(i) - Math.sin(i)) <= eps);
        }
    }

    // Test from 3PI/2 to 5Pi/2
    @Test
    public void testErase2() {
        Double eps = 0.0001;
        for (Double i = 3*Math.PI/2; i <= 5*Math.PI/2 ; i += Math.PI/4) {
            assertTrue(Math.abs(fn.calcSin(i) - Math.sin(i)) <= eps);
        }
    }

    // Test from PI/2 to 3Pi/2
    @Test
    public void testDecrease1() {
        Double eps = 0.0001;
        for (Double i = Math.PI/2; i <= 3*Math.PI/2 ; i += Math.PI/4) {
            assertTrue(Math.abs(fn.calcSin(i) - Math.sin(i)) <= eps);
        }
    }

    // Test from 3Pi/2 to PI/2
    @Test
    public void testDecrease2() {
        Double eps = 0.0001;
        for (Double i = -3*Math.PI/2; i <= -Math.PI/2 ; i += Math.PI/4) {
            assertTrue(Math.abs(fn.calcSin(i) - Math.sin(i)) <= eps);
        }
    }
}
