import static junit.framework.Assert.*;
import org.junit.Test;


public class TestCalc {

    private boolean EPS_Equals(double a, double b, double EPS)
    {
        return Math.abs(b - a) < EPS;
    }

    @Test
    public void testCalcSec1() {

        Calc tester = new Calc();
        try {

            final double EPS = 1.0e-5, INF = 1.0e8;
            assertTrue("test first interval. sec(-PI) = -1", EPS_Equals(1/Math.cos(-Math.PI), tester.calcSec(-Math.PI), EPS));}
        catch (Exception e){
            System.out.println("Error: " + e);
        }
    }

    @Test
    public void testCalcSec2() {
        Calc tester = new Calc();
        try {

            final double EPS = 1.0e-5, INF = 1.0e8;
            assertTrue("test first interval. sec(PI) = -1", EPS_Equals(1/Math.cos(Math.PI), tester.calcSec(Math.PI), EPS));
        }
        catch (Exception e){
            System.out.println("Error: " + e);
        }
    }

    @Test
    public void testCalcSec3() {
        Calc tester = new Calc();
        try {

            final double EPS = 1.0e-5, INF = 1.0e8;
            assertTrue("test first interval. sec(3PI) = -1", EPS_Equals(1/Math.cos(3*Math.PI), tester.calcSec(3*Math.PI), EPS));
        }
        catch (Exception e){
            System.out.println("Error: " + e);
        }
    }

    @Test
    public void testCalcSec4() {
        Calc tester = new Calc();
        try {

            final double EPS = 1.0e-5, INF = 1.0e8;
            assertTrue("test second interval. sec(0) = 1", EPS_Equals(1/Math.cos(0.0), tester.calcSec(0.0), EPS));
        }
        catch (Exception e){
            System.out.println("Error: " + e);
        }
    }

    @Test
    public void testCalcSec5() {
        Calc tester = new Calc();
        try {

            final double EPS = 1.0e-5, INF = 1.0e8;
            assertTrue("test second interval. sec(2PI) = 1", EPS_Equals(1/Math.cos(2*Math.PI), tester.calcSec(2*Math.PI), EPS));
        }
        catch (Exception e){
            System.out.println("Error: " + e);
        }
    }

    @Test
    public void testCalcSec6() {
        Calc tester = new Calc();
        try {

            final double EPS = 1.0e-5, INF = 1.0e8;
            assertTrue("test second interval. sec(-2PI) = 1", EPS_Equals(1/Math.cos(-2*Math.PI), tester.calcSec(-2*Math.PI), EPS));
        }
        catch (Exception e){
            System.out.println("Error: " + e);
        }
    }

    @Test
    public void testCalcSec7() {
        Calc tester = new Calc();
        try {

            final double EPS = 1.0e-5, INF = 1.0e8;
            assertTrue("testing in undefined point sec(Pi/2)", EPS_Equals(INF, tester.calcSec(Math.PI / 2), EPS));
        }
        catch (Exception e){
            System.out.println("Error: " + e);
        }
    }

    @Test
    public void testCalcSec8() {
        Calc tester = new Calc();
        try {

            final double EPS = 1.0e-5, INF = 1.0e8;
            assertTrue("testing in undefined point sec(-Pi/2)", EPS_Equals(INF, tester.calcSec(-Math.PI / 2), EPS));
        }
        catch (Exception e){
            System.out.println("Error: " + e);
        }
    }

    @Test
    public void testCalcSec9() {
        Calc tester = new Calc();
        try {

            final double EPS = 1.0e-5, INF = 1.0e8;
            assertTrue("testing in undefined point sec(3*Pi/2)", EPS_Equals(INF, tester.calcSec(Math.PI / 2 * 3), EPS));
        }
        catch (Exception e){
            System.out.println("Error: " + e);
        }
    }
    @Test
    public void testCalcSec10() {
        Calc tester = new Calc();
        try {

            final double EPS = 1.0e-5, INF = 1.0e8;
            assertTrue("test second interval. sec(2PI) = 1", EPS_Equals(1/Math.cos(5*Math.PI/6), tester.calcSec(5*Math.PI/6), EPS));
        }
        catch (Exception e){
            System.out.println("Error: " + e);
        }
    }

    @Test
    public void testCalcSec11() {
        Calc tester = new Calc();
        try {

            final double EPS = 1.0e-5, INF = 1.0e8;
            assertTrue("test second interval. sec(2PI) = 1", EPS_Equals(1/Math.cos(17*Math.PI/6), tester.calcSec(17*Math.PI/6), EPS));
        }
        catch (Exception e){
            System.out.println("Error: " + e);
        }
    }

    @Test
    public void testCalcSec12() {
        Calc tester = new Calc();
        try {

            final double EPS = 1.0e-5, INF = 1.0e8;
            assertTrue("test second interval. sec(-2PI) = 1", EPS_Equals(1/Math.cos(-5*Math.PI/6), tester.calcSec(-5*Math.PI/6), EPS));
        }
        catch (Exception e){
            System.out.println("Error: " + e);
        }
    }


    @Test
    public void testCalcSec13() {
        Calc tester = new Calc();
        try {

            final double EPS = 1.0e-5, INF = 1.0e8;
            assertTrue("test second interval. sec(2PI) = 1", EPS_Equals(1/Math.cos(5*Math.PI/6), tester.calcSec(5*Math.PI/6), EPS));
        }
        catch (Exception e){
            System.out.println("Error: " + e);
        }
    }

    @Test
    public void testCalcSec14() {
        Calc tester = new Calc();
        try {

            final double EPS = 1.0e-5, INF = 1.0e8;
            assertTrue("test second interval. sec(2PI) = 1", EPS_Equals(1/Math.cos(Math.PI/3), tester.calcSec(Math.PI/3), EPS));
        }
        catch (Exception e){
            System.out.println("Error: " + e);
        }
    }

    @Test
    public void testCalcSec15() {
        Calc tester = new Calc();
        try {

            final double EPS = 1.0e-5, INF = 1.0e8;
            assertTrue("test second interval. sec(-2PI) = 1", EPS_Equals(1/Math.cos(7*Math.PI/3), tester.calcSec(7*Math.PI/3), EPS));
        }
        catch (Exception e){
            System.out.println("Error: " + e);
        }
    }

    @Test
    public void testCalcSec16() {
        Calc tester = new Calc();
        try {

            final double EPS = 1.0e-5, INF = 1.0e8;
            assertTrue("test second interval. sec(-2PI) = 1", EPS_Equals(1/Math.cos(10*Math.PI/3), tester.calcSec(10*Math.PI/3), EPS));
        }
        catch (Exception e){
            System.out.println("Error: " + e);
        }
    }
}
