import static org.junit.Assert.*;
import org.junit.*;


import math.LogarithmicFunctions;
import stub.LogBaseStub;


public class TestLogFunctions {

	private final Double eps = 0.0001;
	private LogarithmicFunctions fn;

	@Before
	public void init() {
		fn = new LogarithmicFunctions(new LogBaseStub());
	}

	@Test
    public void testLnEmptySet() {
        for (Double i = 0.0; i > -2.0; i = i - 0.1) {
			assertTrue(fn.ln(i).isNaN());
        }
    }

	@Test
    public void testLnResults() {
        Double eps = 0.0001;
		for (Double i = 0.01; i < 10; i += 0.1) {
			assertTrue(Math.abs(fn.ln(i) - Math.log(i)) <= eps);
		}
    }

	@Test
    public void testLbEmptySet() {
        for (Double i = 0.0; i > -2.0; i = i - 0.1) {
			assertTrue(fn.lb(i).isNaN());
        }
    }

    @Test
    public void testLbResults() {
        Double eps = 0.0001;
		for (Double i = 0.01; i < 10; i += 0.1) {
			assertTrue(Math.abs(fn.lb(i) - Math.log(i)/Math.log(2)) <= eps);
		}
    }

	@Test
	public void testLb1PowerOfTwo() {
		assertTrue(Math.abs(1.0 - (Double)fn.lb(2.0) ) <= eps);
	}

	@Test
	public void testLb2PowerOfTwo() {
		assertTrue(Math.abs(2.0 - (Double)fn.lb(4.0) ) <= eps);
	}

	@Test
	public void testLb3PowerOfTwo() {
		assertTrue(Math.abs(3.0 - (Double)fn.lb(8.0) ) <= eps);
	}

	@Test
	public void testLb4PowerOfTwo() {
		assertTrue(Math.abs(4.0 - (Double)fn.lb(16.0)) <= eps);
	}

	@Test
	public void testLb5PowerOfTwo() {
		assertTrue(Math.abs(5.0 - (Double)fn.lb(32.0)) <= eps);
	}


	@Test
    public void testLog3EmptySet() {
        for (Double i = 0.0; i > -2.0; i = i - 0.1) {
			assertTrue(fn.lb(i).isNaN());
        }
    }

    @Test
    public void testLog3Results() {
        Double eps = 0.0001;
		for (Double i = 0.01; i < 10; i += 0.1) {
			assertTrue(Math.abs(fn.log_3(i) - Math.log(i)/Math.log(3)) <= eps);
		}
    }

	@Test
	public void testLog31PowerOfThree() {
		assertTrue(Math.abs(1.0 - (Double)fn.log_3(3.0)  ) <= eps);
	}

	@Test
	public void testLog32PowerOfThree() {
		assertTrue(Math.abs(2.0 - (Double)fn.log_3(9.0)  ) <= eps);
	}

	@Test
	public void testLog33PowerOfThree() {
		assertTrue(Math.abs(3.0 - (Double)fn.log_3(27.0) ) <= eps);
	}

	@Test
	public void testLog34PowerOfThree() {
		assertTrue(Math.abs(4.0 - (Double)fn.log_3(81.0) ) <= eps);
	}

	@Test
	public void testLog35PowerOfThree() {
		assertTrue(Math.abs(5.0 - (Double)fn.log_3(243.0)) <= eps);
	}
}
