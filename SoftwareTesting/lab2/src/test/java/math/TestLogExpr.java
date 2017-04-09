import java.lang.IllegalArgumentException;

import static org.junit.Assert.*;
import org.junit.*;

import math.LogarithmicExpression;
import stub.LogFunStub;

public class TestLogExpr {

	private LogarithmicExpression expr;

	@Before
	public void init() {
		this.expr = new LogarithmicExpression(new LogFunStub());
	}

	@Test
	public void testEmptySet1() {
    	assertTrue(!expr.eval(1.1).isNaN());
    	assertTrue(expr.eval(1.0).isNaN());
    	assertTrue(!expr.eval(0.9).isNaN());
	}

	@Test
	public void testEmptySetNegativeArgument() {
		for (Double i = 0.0; i > 2.0; i = i - 0.1) {
			assertTrue(expr.eval(i).isNaN());
		}
	}

	@Test
	public void testNegative() {
		for (Double i = 0.1; i < 1.0; i = i + 0.1) {
    		assertTrue(expr.eval(i) < 0.0);
		}
	}
	
	@Test
	public void testPositive() {
		for (Double i = 1.1; i < 10.0; i = i + 0.1) {
    		assertTrue(expr.eval(i) > 0.0);
		}
	}

	private Double testExpr(Double x) {
		return Math.log(3) * Math.pow(Math.log(x),3) / Math.pow(Math.log(2), 9);
	}

	@Test
	public void testExprResults() {
        Double eps = 0.0001;
		for (Double i = 0.01; i < 10; i += 0.1) {
			assertTrue(Math.abs(expr.eval(i) - this.testExpr(i)) <= eps);
		}
	}
}
