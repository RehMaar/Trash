package stub;

import math.IBaseLog;
import math.LogarithmicFunctions;

public class LogBaseStub implements IBaseLog {
	public Double ln(Double x) {
		if (x <= 0)
    		throw new IllegalArgumentException("Given value is less then or equal to zero");
		return Math.log(x);
	}
}
