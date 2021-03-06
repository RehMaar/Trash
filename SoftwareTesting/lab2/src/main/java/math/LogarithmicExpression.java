package math;

public class LogarithmicExpression implements IExpression {

    private IFunctionsLog fn;

    public LogarithmicExpression() {
        this.fn = new LogarithmicFunctions();
    }

    public LogarithmicExpression(IFunctionsLog fn) {
		this.fn = fn;
    }
    
    public Double eval(Double x) {
        return (Math.pow      
                 (
                   (fn.lb(x) / fn.ln(x)
                       * Math.pow(fn.lb(x),2)
                   ), 3
                 )
                 * fn.log_3(x)
               )
               / Math.pow((fn.log_3(x) * fn.ln(x)), 2);
    }
}
