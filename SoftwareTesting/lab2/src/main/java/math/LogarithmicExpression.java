package math;

import math.LogarithmicFunctions;

public class LogarithmicExpression {

    LogarithmicFunctions fn;

    public LogarithmicExpression() {
        this.fn = new LogarithmicFunctions();
    }
    
    public Double eval(Double x) {
        return (Math.pow
                (
                    (  fn.lb(x)
                     / fn.ln(x)
                     * Math.pow(fn.lb(x),2)
                    ),
                    3
                 ) * fn.log_3(x)
                )
                / Math.pow((fn.log_3(x) * fn.ln(x)), 2);
    }

    public static void main(String[] args) {
		LogarithmicExpression expr = new LogarithmicExpression();

		for (Double i = 0.1; i < 2.0; i += 0.1) {
			System.out.println(i + ": " + expr.eval(i));
		}
    }
}
