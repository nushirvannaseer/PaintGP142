////BGI graphics for visual studio
///*
// * CSE/ENGR 142 GP142_Demo
// *
// * 1/25/95
// * Author(s):         Larry Ruzzo
// * Email Address(s):  ruzzo@cs.washington.edu
// *
// * This program is a demo of some of the features of 
// * GP142 --- the CSE/ENGR 142 Graphics Package.
// * It includes simple drawing commands, keyboard and mouse 
// * interaction, and a simple animation.
// *
// * Revision history:
// * 11/18/97 Dan Boren  - Removed calls to obsolete function GP142_undo()
// *      
// */
// 
//#include "GP142.h"
//#include <stdio.h>
//#include <math.h>
//#include <cstdlib>
//#include <vector> 
//#include <iostream>
//#include "Polygon.h"
//#include "Shape.h"
//#include "Circle.h"
//#include "Triangle.h"
//#include "nPolygon.h"
//#include "Rect.h"
//#include "OpenShape.h"
//#include "Text.h"
////#include "CImg.h"
//
//
//#define PI 3.1415926535
//#define ANIMATE_MSG "Select \"Animate\"\nOn the \"Run\" Menu"
//#define TEXT_SIZE 20
//
//using namespace std;
//
//
//
//
////You will use the following 5 functions do to all work
//
////A) DRAWING FUNCTIONS
////the two drawing functions that you will use to make all shapes
//void draw_line(int x1, int y1, int x2, int y2, int color=WHITE, int width=1){
//	GP142_lineXY (color,x1,y1,x2,y2,width);
//}
//
//void draw_circle(int x, int y, int radius, int color = GREEN) {
//	GP142_circleXY(color, x, y, radius);
//}
//
////B) EVENT HANDLERS
////Mouse handler
//void handle_mouse(int x, int y){
//    GP142_printfXY(YELLOW,x,y,9,"Mouse at (%d,%d)", x, y);
//}
//
////Keyboard handler
//void handle_kbd(char c)
//{
//	//put the character anywhere you want to.
//	//I'm putting it on the origin
//	GP142_printfXY(WHITE, 0, 0,   TEXT_SIZE, "%c", c);
//}
//
////periodic handler you will not need to use because we're not doing animation
//void demo_handle_periodic(void){};
//
//
///******************************************************************************
// *
// * The Main Program
// * ----------------
// *
// * The main program takes care of initialization and cleanup, and the high-level
// * control of all actions in the program, but most of the detail work is 
// * relegated to sub-functions, so that the structure of main stays clear and 
// * simple.
// *
// */
//int main(void)
//{             
//	//std::vector<int> abc(5);
//    int quit = 0;           /* has user signaled quit yet?                      */
//    int mouse_x, mouse_y;
//    char key_pressed;
//	
//
//    GP142_open();           /* Open and initialize the GP142 Graphics Window    */
//    
//	/*for (int i = -492; i < 493; i++)
//	{
//		for (int j = -364; j < 365; j++)
//		{
//			GP142_pixelXY(WHITE, i, j);
//		}
//	}*/
//
//	int pcount=0;
//	int points[4];
//	//Circle c(GREEN, BLUE, 15);	
//	Triangle t(3, WHITE, BLACK);
//	nPolygon n(3, WHITE, BLACK);
//	line l(2, WHITE, false);
//	//Rectangle r(2, WHITE, BLACK);
//	curve curv(WHITE, true);
//	//Text tex(1, WHITE);
//	Text tex(1, GREEN);
//	while (true)
//	{
//		Circle c(GREEN, BLUE);
//		c.draw();
//		false;
//		//GP142_printfXY(WHITE, 0,0, 10, i);
//	}
//
//	
//
//   
//  //  //The Event Loop  
//   /* while (!quit) {
//
//		for (int i = 345; i > 0; i--)
//		{
//			GP142_printfXY(WHITE, -492, i, 15, "|");
//		}
//		
//		 
//
//        switch (GP142_await_event(&mouse_x, &mouse_y, &key_pressed)) {
//            case GP142_QUIT:
//                quit = 1;   /* set flag to terminate loop                */
//            //    break;
//   
//			// GP142_MOUSE:
//            //    handle_mouse(mouse_x,mouse_y);
//	/*
//				points[2*pcount]=mouse_x;
//				points[2*pcount+1]=mouse_y;
//				pcount++;
//
//				if(pcount==2)
//				{
//					pcount=0;
//					draw_line(points[0],points[1],
//						      points[2],points[3]);
//				}
//
//				
//
//
//				draw_circle(mouse_x,mouse_y,10);
//
//				
//				
//
//                break;
//               
//            case GP142_KBD:
//				//Keyboard handler
//                handle_kbd(key_pressed);
//                break;
// 
//            default:
//                break;
//        }
//    }
//
//        */
//    GP142_close();          /* Clean up and close graphics window           */
//    
//    return 0;
//}
//
//
//
//
//
//
//
///*
//				points[2*pcount]=mouse_x;
//				points[2*pcount+1]=mouse_y;
//				pcount++;
//
//				if(pcount==2)
//				{
//					pcount=0;
//					draw_line(points[0],points[1],
//						      points[2],points[3]);
//				}*/
//
//
//
//				//draw_circle(mouse_x,mouse_y,10);
//
//
