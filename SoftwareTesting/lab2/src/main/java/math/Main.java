package math;

/**
 * Created by anki0216 on 03.04.2017.
 */
public class Main {
    public static void main(String[] args) {
        SystemSolver s = new SystemSolver();
        for (Double i = -0.1; i < 1.0; i += 0.1) {
            System.out.println(i + " " + s.solve(i));
        }
    }
}
