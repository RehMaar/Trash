package math;

public class SystemSolver {

	private LogarithmicExpression log;
	private TrigonometricExpression trig;

	private Logger log_obj = new Logger();
	private Double y;

	public SystemSolver() {
		this.log = new LogarithmicExpression();
		this.trig = new TrigonometricExpression();
	}
	
	public Double solve(Double x) {
		y =  x <= 0 ? trig.eval(x) : log.eval(x);
		log_obj.log(x,y,"src/logs/main.csv");
		return y;
	}
}
