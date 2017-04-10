package stub;

import math.IExprTrig;

/**
 * Created by anki0216 on 10.04.2017.
 */
public class TrigExprStub implements IExprTrig {
    public Double eval(Double x) {
        return  ((((Math.pow((1/Math.cos(x) - Math.cos(x)), 3)) -
                (Math.tan(x) - Math.tan(x))) * (1/Math.cos(x))) *
                (((((1/Math.cos(x)) + Math.tan(x)) + (Math.sin(x) * Math.cos(x)))
                        / ((Math.pow(Math.cos(x)/Math.sin(x), 2)) / (1/Math.cos(x)))) + ((Math.sin(x)
                        / (1/Math.cos(x))) * (Math.cos(x)/Math.sin(x)))));
    }
}
