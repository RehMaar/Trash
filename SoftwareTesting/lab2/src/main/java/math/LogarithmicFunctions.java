package math;

import java.lang.IllegalArgumentException;

import math.LogarithmicBase;
import math.IBase;

public class LogarithmicFunctions {

    private IBase base;

    public LogarithmicFunctions() {
        this.base = new LogarithmicBase();
    }

    public LogarithmicFunctions(IBase base) {
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
