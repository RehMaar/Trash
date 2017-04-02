package math;

import math.LogarithmicExpression;
import math.TrigonometricExpression;

public class SystemSolver {

	private LogarithmicExpression log;
	private TrigonometricExpression trig;

	public SystemSolver() {
		this.log = new LogarithmicExpression();
		this.trig = new TrigonometricExpression();
	}
	
	public Double solve(Double x) {
		return x <= 0 ? trig.eval(x) : log.eval(x);
	}
}
