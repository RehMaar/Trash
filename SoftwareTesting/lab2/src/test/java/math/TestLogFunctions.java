import org.junit.jupiter.api.*;
import static org.junit.jupiter.api.Assertions.*;

import math.IBase;
import math.LogarithmicFunctions;

class LogBaseStub implements IBase {
	public Double ln(Double x) {
		return Math.log(x);
	}
}

public class TestLogFunctions {

	LogarithmicFunctions fn;
	Double eps = 0.0001;

	@BeforeEach
	public void init() {
		fn = new LogarithmicFunctions(new LogBaseStub());
	}

	@Test
	public void testLb() {
		assertTrue(Math.abs(1.0 - (Double)fn.lb(2.0) ) <= eps);
		assertTrue(Math.abs(2.0 - (Double)fn.lb(4.0) ) <= eps);
		assertTrue(Math.abs(3.0 - (Double)fn.lb(8.0) ) <= eps);
		assertTrue(Math.abs(4.0 - (Double)fn.lb(16.0)) <= eps);
		assertTrue(Math.abs(5.0 - (Double)fn.lb(32.0)) <= eps);
	}

	@Test
	public void testLog3() {
		assertTrue(Math.abs(1.0 - (Double)fn.log_3(3.0)  ) <= eps);
		assertTrue(Math.abs(2.0 - (Double)fn.log_3(9.0)  ) <= eps);
		assertTrue(Math.abs(3.0 - (Double)fn.log_3(27.0) ) <= eps);
		assertTrue(Math.abs(4.0 - (Double)fn.log_3(81.0) ) <= eps);
		assertTrue(Math.abs(5.0 - (Double)fn.log_3(243.0)) <= eps);
	}
}
