package math;

import math.IBaseLog;

public class LogarithmicBase implements IBaseLog {

	private final Double ln10 = 2.302585092994045684017991454684364207601101488628772976033;
	private Double eps;

	public LogarithmicBase( ) {
		this.eps = 0.0000001;
	}

	public LogarithmicBase(Double eps) {
		this.eps = eps;
	}

	public Double ln(Double x) {

		if (x <= 0) {
    		return Double.NaN;
		}

		Double result = 0.0, tmp = 1.0;

		if (x > 1) {
			while (x > 1) {
				result += ln10;
				x = x/10;
			}
		}

		for (Double n = 1.0; Math.abs(tmp) > eps; n++) {
			tmp = Math.pow((-1), (n+1)) * Math.pow((x - 1.0), n) / n ;
			result += tmp;
		}
		return result;
	}

}
