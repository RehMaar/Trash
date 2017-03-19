package galaxy;

public class ScreenObject implements Comparable<ScreenObject> {

    public enum Position {
        NONE, AT_EDGE, AT_CORNER, NOT_AT_EDGE
    }

    public enum Action {
        NONE, GLOWING, CREPTING, SLICING
    }
    private Position pos;
    private Action act;
    private Shape obj;

    public ScreenObject(Shape obj, Position pos, Action act) {
        this.obj = obj;
        this.pos = pos;
        this.act = act;
    }

    public Shape getShape() {
        return this.obj;
    }

    public Position getPosition() {
        return this.pos;
    }

    public Action getAction() {
        return this.act;
    }

    public void move(Position newPos) {
        this.pos = newPos;
    }
	public void action(Action newAct) {
		this.act = newAct;
	}
    public int compareTo(ScreenObject o) {
        return this.obj.compareTo(o.getShape()) != 0 ? 1 :
               this.pos != o.pos ? 1 :
               this.act != o.act ? 1 : 0;
    }
}
