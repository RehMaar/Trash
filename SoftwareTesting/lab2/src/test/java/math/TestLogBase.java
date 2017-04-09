import static org.junit.Assert.*;
import org.junit.*;

import java.lang.IllegalArgumentException;
import math.LogarithmicBase;

public class TestLogBase {

    private LogarithmicBase fn;

	@Before
	public void init() {
        this.fn = new LogarithmicBase();
	}

	@Test
    public void testBaseEmptySet() {
        for (Double i = 0.0; i > -2.0; i = i - 0.1) {
            assertTrue(fn.ln(i).isNaN());
        }
    }

    @Test
    public void testBaseResults() {
        Double eps = 0.0001;
		for (Double i = 0.01; i < 10; i += 0.1) {
			assertTrue(Math.abs(fn.ln(i) - Math.log(i)) <= eps);
		}
    }
}
