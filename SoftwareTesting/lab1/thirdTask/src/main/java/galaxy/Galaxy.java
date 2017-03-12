package galaxy;
/*
 *  For  a  moment  it  seemed  that  nothing  was  happening,  then  a
 *  brightness glowed at the edge of the huge screen.  A red star the
 *  size  of  a  small  plate  crept  across  it  followed  quickly
 *  b y another one - a binary system.  Then a vast crescent sliced
 *  into the corner of the picture - a red glare shading away into
 *  the deep black, the night side of the planet.
 */

import java.lang.IllegalArgumentException;
import java.util.Stack;

class Shape {
    public enum ShapeSize {
        SMALL_PLATE_SIZE, VAST, NONE
    }
    public enum ShapeColor {
        RED, RED_GLARE_SHADING_AWAY_INTO_THE_DEEP_BLACK, NONE
    }
    public enum ShapeType {
        STAR, BINARY_SYSTEM, CRESCENT
    }

    public ShapeSize size;
    public ShapeColor color;
    public ShapeType type;

    public Shape(ShapeColor color, ShapeSize size, ShapeType type) {
        this.size = size;
        this.color = color;
        this.type = type;
    }

    public void description() {
		System.out.println("Object type: [" + type + "] Properties: color[" + color + "] size[" + size + "]");
    }
}

class ScreenObject {

    public enum Position {
        NONE, EDGE, ANGLE
    }
    
    private Position pos;
    private Shape object;

    public ScreenObject(Shape object) {
        this.object = object;
        this.pos = Position.NONE;
    }

	void description() {
		object.description();
	}
    void move(Position newPos) {
        this.pos = newPos;
        System.out.println("[" + object.type + "] move to position [" + newPos + "]");
    }
}

class Screen {
    public enum ScreenState {
        IDLE, FST_OBJECT, SND_OBJECT, TRD_OBJECT, END
    }

    private Stack<ScreenObject> screenObjects;
    private ScreenState state;

    public Screen() {
		this.state = ScreenState.IDLE;
		this.screenObjects = new Stack();
    }

	public void run() {
		while (this.state != ScreenState.END) {
			this.changeState();
		}
	}

    public void changeState() {
        ScreenObject obj;
		switch (this.state) {
			case IDLE:
    			obj = new ScreenObject(new Shape(Shape.ShapeColor.RED, Shape.ShapeSize.SMALL_PLATE_SIZE, Shape.ShapeType.STAR));
    			this.screenObjects.push(obj);
				this.state = ScreenState.FST_OBJECT;
				break;
			case FST_OBJECT:
    			obj = new ScreenObject(new Shape(Shape.ShapeColor.NONE, Shape.ShapeSize.NONE, Shape.ShapeType.BINARY_SYSTEM));

				this.screenObjects.peek().description();
				this.screenObjects.peek().move(ScreenObject.Position.EDGE);

				this.screenObjects.push(obj);
    			this.state = ScreenState.SND_OBJECT;
    			break;
			case SND_OBJECT:
    			obj = new ScreenObject(new Shape(Shape.ShapeColor.RED_GLARE_SHADING_AWAY_INTO_THE_DEEP_BLACK,
    			                                              Shape.ShapeSize.VAST, Shape.ShapeType.CRESCENT));

				this.screenObjects.peek().description();
				this.screenObjects.peek().move(ScreenObject.Position.EDGE);

				this.screenObjects.push(obj);
    			this.state = ScreenState.TRD_OBJECT;
    			break;
			case TRD_OBJECT:
				this.screenObjects.peek().description();
				this.screenObjects.peek().move(ScreenObject.Position.ANGLE);
    			this.state = ScreenState.END;
    			break;
        	case END:
                break;
			default:
    				throw new IllegalArgumentException("Something wrong with you.");
		}
    }
}
