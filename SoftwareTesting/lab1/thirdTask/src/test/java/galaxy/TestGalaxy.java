import java.util.*;

import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.DisplayName;
import static org.junit.jupiter.api.Assertions.*;

import galaxy.*;

class TestGalaxyModule {

    @Test
    void testScreenObject() {

        Screen screen = new Screen();
        List<ScreenObject> sos = screen.getScreenObjects();

        Shape starOld = new Shape(Shape.ShapeColor.RED,
                              Shape.ShapeRadiance.HIGH,
                              Shape.ShapeSize.SMALL_PLATE_SIZE,
                              Shape.ShapeType.STAR
                              );
        ScreenObject starOldObj= new ScreenObject(starOld,
                                               ScreenObject.Position.AT_EDGE,
                                               ScreenObject.Action.GLOWING
                                               );
        Shape star = new Shape(Shape.ShapeColor.RED,
                              Shape.ShapeRadiance.HIGH,
                              Shape.ShapeSize.SMALL_PLATE_SIZE,
                              Shape.ShapeType.STAR
                              );
        ScreenObject starObj= new ScreenObject(star,
                                               ScreenObject.Position.NOT_AT_EDGE,
                                               ScreenObject.Action.CREPTING
                                               );
        /* *Check new object. */
        Shape bs  = new Shape(Shape.ShapeColor.NONE,
                              Shape.ShapeRadiance.NONE,
                              Shape.ShapeSize.NONE,
                              Shape.ShapeType.BINARY_SYSTEM
                              );
        ScreenObject bsObj= new ScreenObject(bs,
                                             ScreenObject.Position.AT_EDGE,
                                             ScreenObject.Action.CREPTING
                                             );
        Shape cres = new Shape(Shape.ShapeColor.NONE,
                        Shape.ShapeRadiance.NONE,
                        Shape.ShapeSize.VAST,
                        Shape.ShapeType.CRESCENT_OR_THE_NIGHT_SIDE_OF_THE_PLANET
                       );
        ScreenObject cresObj = new ScreenObject(cres,
                              ScreenObject.Position.AT_CORNER,
                              ScreenObject.Action.SLICING
                             );
        /* For a moment it seemed that nothing was happening, */
        assertEquals(Screen.ScreenState.IDLE, screen.getState());
        assertEquals(Screen.ScreenSize.HUGE, screen.getSize());

        screen.changeState();
        /* then a brightness glowed at the edge of the huge screen. */
        assertEquals(Screen.ScreenState.FST, screen.getState());
        /* Check objects */
        assertEquals(1, sos.size());

        /* A red star the size of a small plate crept across, */

        assertTrue(starOldObj.compareTo(sos.get(0)) == 0);

        /* it followed quickly by another one - a binary system. */
        screen.changeState();
        assertEquals(Screen.ScreenState.SND, screen.getState());
        assertEquals(2, sos.size());
        assertEquals(Screen.ScreenSize.HUGE, screen.getSize());


        /* Check first object. */
        ScreenObject tmp  = sos.get(0);
        assertEquals(ScreenObject.Action.CREPTING, tmp.getAction());
        assertEquals(ScreenObject.Position.NOT_AT_EDGE, tmp.getPosition());
                     


        assertTrue(bsObj.compareTo(sos.get(1)) == 0);

		/* Then a vasr crescent sliced into the corner of the picture
		 * -- a red glare shading away into the deep black, the night
		 * side of the planet
		 */
        screen.changeState();
        assertEquals(Screen.ScreenState.END, screen.getState());
        assertEquals(3 ,sos.size());
        assertEquals(Screen.ScreenSize.HUGE, screen.getSize());


       	assertTrue(cresObj.compareTo(sos.get(2)) == 0);

        /* Check actions. */
        screen.changeState();
        assertEquals(Screen.ScreenState.END, screen.getState());
        assertTrue(starObj.compareTo(sos.get(0))  == 0);
        assertTrue(bsObj.compareTo(sos.get(1))   == 0);
       	assertTrue(cresObj.compareTo(sos.get(2)) == 0);
    }
}
