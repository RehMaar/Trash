package math;

import math.LogarithmicBase;
import math.IBaseLog;
import math.IFunctionsLog;

public class LogarithmicFunctions implements IFunctionsLog {

    private IBaseLog base;

    public LogarithmicFunctions() {
        this.base = new LogarithmicBase();
    }

    public LogarithmicFunctions(IBaseLog base) {
        this.base = base;
    }

    public Double lb(Double x) {
        return base.ln(x) / base.ln(2.0);
    }

    public Double log_3(Double x) {
        return base.ln(x) / base.ln(3.0);
    }

    public Double ln(Double x) {
        return base.ln(x);
    }

}
