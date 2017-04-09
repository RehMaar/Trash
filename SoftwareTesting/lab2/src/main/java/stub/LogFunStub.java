package stub;

import math.IFunctionsLog;

public class LogFunStub implements IFunctionsLog {
	public Double lb(Double x) {
		if (x <= 0)
    		throw new IllegalArgumentException("Given value is less then or equal to zero");
		return Math.log(x)/Math.log(2);
	}

	public Double ln(Double x) {
		if (x <= 0)
    		throw new IllegalArgumentException("Given value is less then or equal to zero");
		return Math.log(x);
	}

	public Double log_3(Double x) {
    	if (x <= 0)
    		throw new IllegalArgumentException("Given value is less then or equal to zero");
		return Math.log(x)/Math.log(3);
	}
}
