package math;

import java.util.*;
import java.io.*;
import java.util.function.*;

/**
 * Created by skyD9 on 09.04.2017.
 */

class Commands {
	public ArrayList<Function<Double, Double>> ops;
	public enum Opcodes {
		LN, LB, LOG3, LOGEXPR, SIN, COS, TAN, COT, SEC, TRIGEXPR, SYSTEM
	}

	private LogarithmicFunctions    lfn;
	private LogarithmicExpression   lexpr;
	private TrigonometricFunctions  tfn;
	private TrigonometricExpression texpr;
	private SystemSolver syssolve;
	
	public Commands() {
    	lfn   = new LogarithmicFunctions();
		lexpr = new LogarithmicExpression();
		tfn   = new TrigonometricFunctions();
		texpr = new TrigonometricExpression();
		syssolve = new SystemSolver();

		ops = new ArrayList<Function<Double, Double>>();
		ops.add(x -> lfn.ln(x));
		ops.add(x -> lfn.lb(x));
		ops.add(x -> lfn.log_3(x));
		ops.add(x -> lexpr.eval(x));
		ops.add(x -> tfn.calcSin(x));
		ops.add(x -> tfn.calcCos(x));
		ops.add(x -> tfn.calcTan(x));
		ops.add(x -> tfn.calcCot(x));
		ops.add(x -> tfn.calcSec(x));
		ops.add(x -> texpr.eval(x));
		ops.add(x -> syssolve.solve(x));
	}
}
 
public class Main {

    private Logger l = new Logger();


	public void logResults(Logger l, String name, Function<Double, Double> f, Double min, Double max, Double step) {
		for (Double i = min; i < max; i = i + step) {
            this.l.log(i, f.apply(i), name);
		}
	}

	public void evalResults(Function<Double, Double> f, Double min, Double max, Double step) {
    	System.out.println("[");
		for (Double i = min; i < max; i = i + step) {
    		System.out.println("(" + i + "," + f.apply(i) + ")");
		}
    	System.out.println("]");
	}

	public int getExprIndex(String name) {
		switch (name) {
			case "ln"       : return (int)Commands.Opcodes.LN.ordinal();
			case "lb"       : return (int)Commands.Opcodes.LB.ordinal();
			case "log3"     : return (int)Commands.Opcodes.LOG3.ordinal();
			case "logexpr"  : return (int)Commands.Opcodes.LOGEXPR.ordinal();
			case "sin"      : return (int)Commands.Opcodes.SIN.ordinal();
			case "cos"      : return (int)Commands.Opcodes.COS.ordinal();
			case "tan"      : return (int)Commands.Opcodes.TAN.ordinal();
			case "sec"      : return (int)Commands.Opcodes.SEC.ordinal();
			case "cot"      : return (int)Commands.Opcodes.COT.ordinal();
			case "trigexpr" : return (int)Commands.Opcodes.TRIGEXPR.ordinal();
			case "system"   : return (int)Commands.Opcodes.SYSTEM.ordinal();
			default    : return -1;
		}
	}

	public void run() {

    	String[] tokens = null;
    	String line     = null;

		Commands cmd = new Commands();
		Scanner sc   = new Scanner(System.in);
		while (true) {
    		System.out.print(">> ");
			try {
    			if (sc.hasNext()) 
    				line = sc.nextLine();
    		    else
    		    	return;
			} catch ( IOError e ) {
				System.err.println("I/O Error.");
				continue;
			}
			if (line == null)
    			continue;
    		tokens = line.split(" ");
    		if (tokens.length == 0) {
				continue;
    		}
    		switch (tokens[0]) {
    			case "help":  {
        			usage();
        			continue;
    			}
    			case "eval" : {
					if (tokens.length != 5) {
						System.err.println("Not enough arguments.");
						continue;
					}
					int index = getExprIndex(tokens[1]);
					if (index == -1) {
						System.err.println("Not such function.");
						continue;
					}
					Double min = Double.valueOf(tokens[2]);
					Double max = Double.valueOf(tokens[3]);
					Double step = Double.valueOf(tokens[4]);
					Function<Double, Double> fn = cmd.ops.get(index);
        			evalResults(fn, min, max, step);
    				break;
    			}
    			case "log" : {
					if (tokens.length != 6) {
						System.err.println("Not enough arguments.");
						continue;
					}
					int index = getExprIndex(tokens[2]);
					if (index == -1) {
						System.err.println("Not such function.");
						continue;
					}
					Double min = Double.valueOf(tokens[3]);
					Double max = Double.valueOf(tokens[4]);
					Double step = Double.valueOf(tokens[5]);
					Function<Double, Double> fn = cmd.ops.get(index);
					logResults(l, tokens[1], fn, min, max, step);
    				break;
    			}
    			default: {
        			System.err.println("No such command.");
    				continue;
    			}
    		}
		}
	}

	public void usage() {
		System.err.println("command [help]\n" +
			"help -- print this message\n" +
			"Commands:\n" +
			"eval name min max step -- evaluate function from `min` to `max` with `step`\n" +
		    "log filename expr min max step -- log results of evaluation to the `filename`\n" +
		    "	Functions: sin, cos, tan, cot, sec,\n" +
		    "    ln, lb, log3, logexpr, trigexpr, system\n" +
		);
	}

    /* main [help|options]
     */
    public static void main(String[] args) {
        Main m = new Main();
		if (args.length > 0 && args[0].equals("help")) {
			m.usage();
			return;
		}
		m.run();
    }
}
