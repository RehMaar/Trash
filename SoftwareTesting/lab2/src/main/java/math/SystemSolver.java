package math;

public class SystemSolver {

    private IExpression log;
    private IExpression trig;

	public SystemSolver() {
		this.log = new LogarithmicExpression();
		this.trig = new TrigonometricExpression();
	}

	public SystemSolver(IExpression log, IExpression trig) {
		this.log  = log;
		this.trig = trig;
	}
	public Double solve(Double x) {
		return x <= 0 ? trig.eval(x) : log.eval(x);
	}
}
