package stub;

import math.IExprLog;

/**
 * Created by anki0216 on 10.04.2017.
 */
public class LogExprStub implements IExprLog {
    public Double eval(Double x) {
        return Math.log(3) * Math.pow(Math.log(x),3) / Math.pow(Math.log(2), 9);
    }
}
