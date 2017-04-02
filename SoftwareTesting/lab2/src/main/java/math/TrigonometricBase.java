/**
 * Created by skyD9 on 02.04.2017.
 */
public class TrigonometricBase {
    public Double calcSin(Double x){
        Double stx,sint,e;
        Integer i,fakt,z;

        e=1e-10; //accuracy
        stx= x;  //x in rate
        fakt= 1;  //factorial value
        sint= 0.0;  //first element
        i= 1;  //counter
        z= 1;  //sigh of element

        while (stx/fakt>=e) {  // while element don't less than accuracy
            sint=sint + z * stx / fakt;
            i=i+2;
            stx=stx * x * x;
            fakt=fakt * (i - 1) * i;
            z=z * (-1); //change sigh
        }
        return sint;
    }
}
