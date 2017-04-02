import java.lang.IllegalArgumentException;


public class LogarithmicFunctions {

    private LogarithmicBase base;

    public LogarithmicFunctions() {
        this.base = new LogarithmicBase();
    }

    public LogarithmicFunctions(Double eps) {
        this.base = new LogarithmicBase(eps);
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
