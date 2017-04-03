package math;

import java.lang.IllegalArgumentException;

import math.LogarithmicBase;

public class LogarithmicFunctions {

    private LogarithmicBase base;

    private Logger log_obj = new Logger();

    private Double y;

    public LogarithmicFunctions() {
        this.base = new LogarithmicBase();
    }

    public LogarithmicFunctions(Double eps) {
        this.base = new LogarithmicBase(eps);
    }

    public Double lb(Double x) {
        y =  base.ln(x) / base.ln(2.0);
        log_obj.log(x,y,"src/logs/lb.csv");
        return y;
    }

    public Double log_3(Double x) {
        y =  base.ln(x) / base.ln(3.0);
        log_obj.log(x,y,"src/logs/log_3.csv");
        return y;
    }

    public Double ln(Double x) {
        y = base.ln(x);
        log_obj.log(x,y,"src/logs/ln.csv");
        return y;
    }
}
