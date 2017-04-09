package stub;

import math.IBaseLog;
import math.LogarithmicFunctions;

public class LogBaseStub implements IBaseLog {
	public Double ln(Double x) {
		return x <= 0 ? Double.NaN : Math.log(x);
	}
}
