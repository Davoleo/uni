package net.davoleo.unipr;

public class Rectangle {
    protected int width;
    protected int height;
    
    public Rectangle() {
        width = 0;
        height = 0;
    }
    
    public Rectangle(int width, int height) {
        this.width = width;
        this.height = height;
    }
    
    public int perimeter() {
        return 2 * width + 2 * height;
    }
    
    public int area() {
        return height * width;
    }

    public static class Square extends Rectangle {
        public Square() {}

        public Square(int size) {
            super(size, size);
        }

        public double getInscribedCircleLength() {
            return height * Math.PI;
        }

        @Override
        public int perimeter() {
            return 4 * height;
        }
    }
}