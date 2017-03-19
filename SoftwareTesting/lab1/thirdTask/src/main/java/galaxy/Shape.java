package galaxy;

public class Shape implements Comparable<Shape> {
    public enum ShapeSize {
        SMALL_PLATE_SIZE, VAST, NONE
    }
    public enum ShapeColor {
        RED, RED_GLARE_SHADING_AWAY_INTO_THE_DEEP_BLACK, NONE
    }
    public enum ShapeType {
        STAR, BINARY_SYSTEM, CRESCENT_OR_THE_NIGHT_SIDE_OF_THE_PLANET
    }
    public enum ShapeRadiance {
        NONE, HIGH
    }
    public ShapeSize size;
    public ShapeColor color;
    public ShapeType type;
    public ShapeRadiance radiance;

    public Shape(ShapeColor color, ShapeRadiance radiance, ShapeSize size, ShapeType type) {
        this.color    = color;
        this.radiance = radiance;
        this.size     = size;
        this.type     = type;
    }

    public ShapeSize getSize() {
        return this.size;
    }
    public ShapeColor getColor() {
        return this.color;
    }
    public ShapeType getType() {
        return this.type;
    }
    public ShapeRadiance getRadiance() {
        return this.radiance;
    }

    public int compareTo(Shape o) {
        return this.size     != o.size     ? 1 :
               this.color    != o.color    ? 1 :
               this.type     != o.type     ? 1 :
               this.radiance != o.radiance ? 1 : 0;
    }
    
}
