import static org.junit.jupiter.api.Assertions.*;
import org.junit.jupiter.api.*;

import java.lang.IllegalArgumentException;
import math.LogarithmicBase;

public class TestLogBase {

    private LogarithmicBase fn;

	@BeforeEach
	public void init() {
        this.fn = new LogarithmicBase();
	}
	
	@Test
    public void testBaseNegative() {
    	try {
            Double res = fn.ln(-1.0);
    	} catch (IllegalArgumentException e) {
        	return;
    	}
    	fail("No exception on negative value");
    }

	@Test
    public void testBaseZero() {
    	try {
            Double res = fn.ln(0.0);
    	} catch (IllegalArgumentException e) {
        	return;
    	}
    	fail("No exception on zero value");
    }

    @Test
    public void testBaseResults() {
        Double eps = 0.0001;
		for (Double i = 0.01; i < 10; i += 0.1) {
			assertTrue(Math.abs(fn.ln(i) - Math.log(i)) <= eps);
		}
    }
}
