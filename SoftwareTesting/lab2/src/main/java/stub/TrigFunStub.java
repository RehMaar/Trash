package stub;

import math.IFunctionsTrig;

/**
 * Created by anki0216 on 10.04.2017.
 */
public class TrigFunStub implements IFunctionsTrig {
    public Double sin(Double x){
        return Math.sin(x);
    }

    public Double cos(Double x){
        return Math.cos(x);
    }

    public Double tan(Double x){
        return  Math.tan(x);
    }

    public Double cot(Double x){
        return Math.cos(x)/Math.sin(x);
    }

    public Double sec(Double x){
        return 1/Math.cos(x);
    }
}
