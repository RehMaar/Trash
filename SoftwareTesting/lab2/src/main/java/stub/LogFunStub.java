package stub;

import math.IFunctionsLog;

public class LogFunStub implements IFunctionsLog {
	public Double lb(Double x) {
		return x <= 0 ? Double.NaN : Math.log(x)/Math.log(2);
	}

	public Double ln(Double x) {
		return x <= 0 ? Double.NaN : Math.log(x);
	}

	public Double log_3(Double x) {
		return x <= 0 ? Double.NaN : Math.log(x)/Math.log(3);
	}
}
