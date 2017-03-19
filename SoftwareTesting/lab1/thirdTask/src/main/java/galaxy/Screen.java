package galaxy;
/*
 *  For  a  moment  it  seemed  that  nothing  was  happening,  then  a
 *  brightness glowed at the edge of the huge screen.  A red star the
 *  size  of  a  small  plate  crept  across,  it  followed  quickly
 *  by another one - a binary system.  Then a vast crescent sliced
 *  into the corner of the picture - a red glare shading away into
 *  the deep black, the night side of the planet.
 */

import java.lang.IllegalArgumentException;
import java.lang.Comparable;
import java.util.List;
import java.util.ArrayList;

import galaxy.*;

public class Screen {
    public enum ScreenState {
        IDLE, FST, SND, END
    }
    public enum ScreenSize {
        HUGE
    }
    
    private List<ScreenObject> screenObjects;
    private ScreenState state;
    private ScreenSize size;

    public Screen() {
        this.state = ScreenState.IDLE;
        this.screenObjects = new ArrayList<ScreenObject>();
        this.size = ScreenSize.HUGE;
    }

	public ScreenSize getSize() {
		return this.size;
	}

    public ScreenState getState() {
        return this.state;
    }

    public List<ScreenObject> getScreenObjects() {
        return this.screenObjects;
    }
    
	public void reset() {
        this.state = ScreenState.IDLE;
        this.screenObjects = new ArrayList<ScreenObject>();
        this.size = ScreenSize.HUGE;
	}

    public void changeState() {
        switch (this.state) {
            case IDLE: {
                    /* First object appeared. */
                    Shape obj = new Shape(Shape.ShapeColor.RED,
                                          Shape.ShapeRadiance.HIGH,
                                          Shape.ShapeSize.SMALL_PLATE_SIZE,
                                          Shape.ShapeType.STAR
                                          );
                    screenObjects.add(new ScreenObject(obj,
                                                       ScreenObject.Position.AT_EDGE,
                                                       ScreenObject.Action.GLOWING
                                                       )
                                     );
                    this.state = ScreenState.FST;
                }
                break;
            case FST: {
                    ScreenObject so = screenObjects.get(0);
                    so.move(ScreenObject.Position.NOT_AT_EDGE);
    				so.action(ScreenObject.Action.CREPTING);

                    Shape obj = new Shape(Shape.ShapeColor.NONE,
                                          Shape.ShapeRadiance.NONE,
                                          Shape.ShapeSize.NONE,
                                          Shape.ShapeType.BINARY_SYSTEM
                                          );
                    screenObjects.add(new ScreenObject(obj,
                                                       ScreenObject.Position.AT_EDGE,
                                                       ScreenObject.Action.CREPTING
                                                       )
                                     );
                    this.state = ScreenState.SND;
                }
                break;
            case SND: {
                    Shape obj = new Shape(Shape.ShapeColor.NONE,
                                          Shape.ShapeRadiance.NONE,
                                          Shape.ShapeSize.VAST,
                                          Shape.ShapeType.CRESCENT_OR_THE_NIGHT_SIDE_OF_THE_PLANET
                                          );
                    screenObjects.add(new ScreenObject(obj,
                                                       ScreenObject.Position.AT_CORNER,
                                                       ScreenObject.Action.SLICING
                                                       )
                                     );
                    this.state = ScreenState.END;
                }
                break;
            case END:
                break;
        }
    }
}
