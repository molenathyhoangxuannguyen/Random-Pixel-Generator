 /* Authors: Thy H. Nguyen

    Python version of Sierpinski's triangle by Jan Pearce; Conversion to C++ by Jesse W. Walker
	C-Turtle by Jesse  W.  Walker, Getrandom by Jan Pearce

 */

#include "CTurtle.hpp"   //This brings in the CTurtle library for use
#include <iostream> //for input & output
#include <random> //needed for Getrandom
#include <chrono> //needed for Getrandom's seed
namespace ct = cturtle;  //This makes it possible to use the CTurtle commands using ct::
using namespace std;

class Getrandom {
	/** Uses <random> and <chrono> from C++11 to return a random integer in range [1..size] */
public:
	Getrandom(int size) {
		auto seed = chrono::system_clock::now().time_since_epoch().count(); //gets a new seed for the randomness
		default_random_engine generator(seed);			//seeds our randomness
		uniform_int_distribution<int> intdist(1, size); //a distibution to make each in-range integer equally likely
		self_rand_int_ = intdist(generator);			//generates the randme number
	}
	int roll() {
		return self_rand_int_;
	}
private:
	int self_rand_int_;
};


void draw_triangle(ct::Point a, ct::Point b, ct::Point c, ct::Color color, ct::Turtle& myTurtle){
    myTurtle.fillcolor(color);
    myTurtle.penup();
    myTurtle.goTo(a.x, a.y);
    myTurtle.pendown();
    myTurtle.begin_fill();
    myTurtle.goTo(c.x, c.y);
    myTurtle.goTo(b.x, b.y);
    myTurtle.goTo(a.x, a.y);
    myTurtle.end_fill();
}

//getMid already defined as "middle" function in C-Turtle namespace :)

void sierpinski(ct::Point a, ct::Point b, ct::Point c, int degree, ct::Turtle& myTurtle){
    const std::string colormap[] = {"blue", "red", "green", "white", "yellow", "violet", "orange"};
    draw_triangle(a,b,c, {colormap[degree]}, myTurtle);
    if(degree > 0){
        sierpinski(a, ct::middle(a, b), ct::middle(a, c), degree - 1, myTurtle);
        sierpinski(b, ct::middle(a, b), ct::middle(b, c), degree - 1, myTurtle);
        sierpinski(c, ct::middle(c, b), ct::middle(a, c), degree - 1, myTurtle);
    }
}


class MondrianArt {

public:
    MondrianArt() {}
    // Constructor should initialize instance variables.

    void setup_turtle(ct::Point a, ct::Turtle& turtle) {
        /*PLEASE READ THIS NOTE:
        On the google doc, it is mentioned that:
        "These steps assume you start with the entire screen’s size as a rectangle, wherein the top left hand corner is the coordinate x=800, y=-600 and the bottom right is
        (This leaves you with a rectangle at x=-800, y=600 with a total  width of 1600 and height of 1200)"
        However, I saw that the screen to draw on was set up by Jessi with a display of 800 x 600 pixel.
        Therefore, the coordinate of (x,y) = (-800,600) is definitely NOT a point on the screen,
        and it is also NOT in the TOP LEFT HAND CORNER.  x= -800, y =600 is actually the top left hand corner. However, this point is NOT in the screen.
        Moreover, in the suggestion, there is
        "void  setup_turtle()
            // Moves the turtle to the top left hand side of the screen (goTo -400, -300 "
        Therefore, I decide to go to the point at the coordinate (-400, 300) as my top left hand corner, and draw a rectangle of
        the width of 800, and a height of 600.
        */

        // Moves the turtle to the top left hand side of the screen 
        turtle.penup();
        turtle.goTo(a.x, a.y);
        turtle.pendown();
        //This step below draws the largest rectangle with the width of 800 and the height of 600
        for (int i = 0; i < 2; i++) {
            turtle.forward(800);
            turtle.right(90);
            turtle.forward(600);
            turtle.right(90);
        }

    }
    void mondrian(ct::Point a, int width, int height, ct::Turtle& turtle) {
        // The recursive mondrian function that holds all the steps found above.
        turtle.speed(0);
        Getrandom color(8);
        turtle.pencolor({ colorList[color.roll()] });
        turtle.penup();
        turtle.goTo(a.x + width, a.y);
        turtle.right(90);
        turtle.pendown();
        turtle.forward(height);
        turtle.penup();
        turtle.goTo(a.x, a.y - height);
        turtle.left(90);
        turtle.pendown();
        turtle.forward(width);


        // I get the most right side of the rectangle, and the most down side of the rectangle, 
        //in other words, the boundary of the width and the height to draw the rectangles.

        if ((width > 400) && (height > 300))
        {
        

            Getrandom newwidth(width);
            Getrandom newheight(height);

            mondrian({ a.x, a.y }, newwidth.roll(), newheight.roll(), turtle);

            mondrian({ a.x, a.y - newheight.roll() }, newwidth.roll(), height - newheight.roll(), turtle);
            mondrian({ a.x + newwidth.roll(), a.y }, width - newwidth.roll(), newheight.roll(), turtle);
            mondrian({ a.x + newwidth.roll(), a.y - newheight.roll() }, width - newwidth.roll(), height - newheight.roll(), turtle);

        }
            
                    
             
       else if (width > 400) {
           Getrandom newwidth(width);
           turtle.pencolor({ "blue" });
            mondrian({ a.x, a.y }, newwidth.roll(), height, turtle);
           

        }
        
        else if (height > 300) {
            Getrandom newheight(height);
            mondrian({ a.x, a.y }, width, newheight.roll(), turtle);

        }
        else if ((width > 3) && (height > 2))
        {
            Getrandom newwidth(width);
            Getrandom newheight(height);

            mondrian({ a.x, a.y }, newwidth.roll(), newheight.roll(), turtle);

            mondrian({ a.x, a.y - newheight.roll() }, newwidth.roll(), height - newheight.roll(), turtle);
            mondrian({ a.x + newwidth.roll(), a.y }, width - newwidth.roll(), newheight.roll(), turtle);
            mondrian({ a.x + newwidth.roll(), a.y - newheight.roll() }, width - newwidth.roll(), height - newheight.roll(), turtle);


        }
        else if (width > 3) {
            Getrandom newwidth(width);
            mondrian({ a.x, a.y }, newwidth.roll(), height, turtle);
        }
        else if (height > 2) {
            Getrandom newheight(height);
            mondrian({ a.x, a.y }, width, newheight.roll(), turtle);
        }
        else {
            Getrandom color(8);
            turtle.fillcolor({ colorList[color.roll()] });
            turtle.begin_fill();
            
            turtle.penup();
            turtle.goTo(a.x, a.y);
            turtle.pendown();
            //This step below fills the smallest rectangle with random color
            for (int i = 0; i < 2; i++) {
                turtle.forward(width);
                turtle.right(90);
                turtle.forward(height);
                turtle.right(90);
            }
            turtle.end_fill();
        }
    
    }
    
    void reset(ct::Turtle& turtle) {
        // This is an optional method. Use it to keep creating pieces of art until you find one you like!
        turtle.reset();
    }
private:
    string colorList[9] = { "black","orange","brown","purple","green", "blue", "red", "yellow", "pink" };

};



int main() {
    ct::TurtleScreen scr; //makes screen
    ct::Turtle rt(scr);   //makes Turtle on screen

    ct::Point myPoints = { -400, 300 };
    //graphing commands go below here
    MondrianArt draw_modrian_art;
    draw_modrian_art.setup_turtle(myPoints, rt);
    draw_modrian_art.mondrian(myPoints, 800, 600, rt);
    /*
    if you want to see the original art created by Jessi, you can undo this comment

    Getrandom newrandom(4);
    ct::Point myPoints[] = { {-200, -100}, {0, 200}, {200, -100} };
    sierpinski(myPoints[0], myPoints[1], myPoints[2], newrandom.roll(), rt);
    */

    scr.exitonclick();  //exists graphics screen
    return 0;
}
