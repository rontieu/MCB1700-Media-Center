#include <stdio.h>                                  
#include <ctype.h>                    
#include <string.h>                   
#include <stdbool.h>
#include "LPC17xx.H"             
#include "LED.h"
#include "GLCD.h"
#include "KBD.h"
#include <ctype.h>

/////////////////////////////////// IMAGES /////////////////////////////////// 

#include "Eagle.c"
#include "Panda.c"
#include "Cat.c"
#include "MusicNote.c"

/////////////////////////////////// DEFINITIONS /////////////////////////////////// 

#define __F0        0											 /* Font index 6x8 */
#define __F1        1											 /* Font index 16x24 */

/////////////////////////////////// ITM Stimulus Port definitions for printf /////////////////////////////////// 

#define ITM_Port8(n)    (*((volatile unsigned char *)(0xE0000000+4*n)))
#define ITM_Port16(n)   (*((volatile unsigned short*)(0xE0000000+4*n)))
#define ITM_Port32(n)   (*((volatile unsigned long *)(0xE0000000+4*n)))

#define DEMCR           (*((volatile unsigned long *)(0xE000EDFC)))
#define TRCENA          0x01000000

/////////////////////////////////// INITIALIZING VARIABLES /////////////////////////////////// 

int location,location2; 
uint32_t joystick;

/////////////////////////////////// DELAY /////////////////////////////////// 

void buttonDelay(){
	int a=0;
	for(a=0;a<2000000;a++){
	}
}

void musicDelay(){
	int a=0;
	for(a=0;a<10000000;a++){
	}
}

/////////////////////////////////// PHOTO GALLERY /////////////////////////////////// 

void dispImage(int i){
	location2 = i;				// reads initial value based on which image was selected to be displayed first
	while(1){
		GLCD_Clear(Black);    
		GLCD_SetTextColor(BluePurple);
		GLCD_DisplayString(0, 35, __F0, "Ron Tieu 500686482");
		GLCD_SetTextColor(LightBlue);
		GLCD_DisplayString(9, 4, __F1, "EXIT-SELECT");
		GLCD_DisplayString(7, 0, __F1, "LEFT           RIGHT");
		GLCD_DisplayString(6, 0, __F1, "<-                ->");
		while(1){	//while loop for photo display
			joystick = get_button();
			if(joystick == KBD_SELECT){           // If select is pressed
				buttonDelay();					  // Exit photo gallery
				return;
			}
			else if(joystick == KBD_LEFT){     //if left pressed
				location2--;	
				buttonDelay();
			}
			else if(joystick == KBD_RIGHT){   //if pressed pressed
				location2++;
				buttonDelay();
			}
			if(location2 > 2){   //positions changes from 2 to 0 on right press
				location2 = 0;
			}
			if(location2 < 0){   //position changes from 0 to 2 on left press
				location2 = 2;
			}
			switch(location2){
				case 0: 		//location 0 mapped to Cat		
						GLCD_SetTextColor(White1);		
						GLCD_DisplayString(1, 2, __F1, "Displayed: Cat     ");
						GLCD_Bitmap(80,55,150,150,(unsigned char*)CAT1_pixel_data); 
						break;
						
					case 1:  		//location 1 mapped to Eagle
						GLCD_SetTextColor(White1);		
						GLCD_DisplayString(1, 2, __F1, "Displayed: Eagle   ");
						GLCD_Bitmap(80,55,150,150,(unsigned char*)EAGLE1_pixel_data);
						break;
					
					case 2:  		//location 2 mapped to Panda
						GLCD_SetTextColor(White1);		
						GLCD_DisplayString(1, 2, __F1, "Displayed: Panda     ");
						GLCD_Bitmap(80,55,150,150,(unsigned char*)PANDA1_pixel_data);
						break;
			}
		}
	}
}

void galMenu(){
	GLCD_Clear(Black);                       
	GLCD_SetBackColor(Black);
	GLCD_SetTextColor(White1);
	GLCD_DisplayString(1, 4, __F1, "Photo Gallery");
	GLCD_SetTextColor(BluePurple);
	GLCD_DisplayString(0, 35, __F0, "Ron Tieu 500686482");
}	


void gallery(){
	while(1){
		galMenu();				// Show initial gallery menu
		while(1){
			joystick = get_button();
			if(joystick == KBD_SELECT){           //If button is pushed
				buttonDelay();
				if(location2 == 0){    //Cat
						dispImage(0);
						break;
				}
				if(location2 == 1){    //Eagle
						dispImage(1);
						break;
				}
				if(location2 == 2){    //Panda
						dispImage(2);
						break;
				}
				if(location2 == 3){    //Exit to main menu
						location=1;
						return;
				}
			}
			else if(joystick == KBD_UP){     //if up pressed
				location2--;
				buttonDelay();
			}
			else if(joystick == KBD_DOWN){   //if down pressed
				location2++;
				buttonDelay();
			}				
			if(location2 > 3){   //positions changes from 3 to 0 on uppress
				location2 = 0;
			}
			if(location2 < 0){   //position changes from 0 to 3 on downpress
				location2 = 3;
			}

			switch(location2){	// Move menu arrow + change colours based on value of location
				case 0: 				
					GLCD_SetTextColor(LightBlue);
					GLCD_DisplayString(4, 1, __F1, "->Cat");
					GLCD_SetTextColor(DarkBlue);
					GLCD_DisplayString(5, 1, __F1, "  Eagle");
					GLCD_DisplayString(6, 1, __F1, "  Panda");
					GLCD_DisplayString(8, 1, __F1, "  EXIT");
					break;
				
				case 1: 				
					GLCD_SetTextColor(LightBlue);
					GLCD_DisplayString(5, 1, __F1, "->Eagle");
					GLCD_SetTextColor(DarkBlue);
					GLCD_DisplayString(4, 1, __F1, "  Cat");
					GLCD_DisplayString(6, 1, __F1, "  Panda");
					GLCD_DisplayString(8, 1, __F1, "  EXIT");
					break;

				case 2: 				
					GLCD_SetTextColor(LightBlue);
					GLCD_DisplayString(6, 1, __F1, "->Panda");
					GLCD_SetTextColor(DarkBlue);
					GLCD_DisplayString(4, 1, __F1, "  Cat");
					GLCD_DisplayString(5, 1, __F1, "  Eagle");
					GLCD_DisplayString(8, 1, __F1, "  EXIT");
					break;

				case 3: 				
					GLCD_SetTextColor(LightBlue);
					GLCD_DisplayString(8, 1, __F1, "->EXIT");
					GLCD_SetTextColor(DarkBlue);
					GLCD_DisplayString(4, 1, __F1, "  Cat");
					GLCD_DisplayString(5, 1, __F1, "  Eagle");
					GLCD_DisplayString(6, 1, __F1, "  Panda");
					break;				
			}
		}
	}
}

/////////////////////////////////// MUSIC /////////////////////////////////// 

void music(){
	GLCD_Clear(Black);    
	GLCD_SetTextColor(BluePurple);
	GLCD_DisplayString(0, 35, __F0, "Ron Tieu 500686482");
	GLCD_SetTextColor(White1);
	GLCD_DisplayString(1, 2, __F1, "Audio Playing...    ");
	GLCD_SetTextColor(LightBlue);		
	GLCD_DisplayString(9, 4, __F1, "EXIT-SELECT");
	GLCD_Bitmap(80,55,150,150,(unsigned char*)MUSIC1_pixel_data);	// Displays music player image
	mainAudio();	// Calls mainAudio function which plays audio from USB connection
	musicDelay();
}

///////////////////////////////////  MAIN MENU /////////////////////////////////// 

void menu(void){
	GLCD_Clear(Black);                       
	GLCD_SetBackColor(Black);
	GLCD_SetTextColor(BluePurple);
	GLCD_DisplayString(0, 35, __F0, "Ron Tieu 500686482");
	GLCD_SetTextColor(White1);
	GLCD_DisplayString(1, 4, __F1, "Media Center");	
}

/////////////////////////////////////// MAIN CODE ///////////////////////////////////////////

int main (void){
	KBD_Init();   //Joystick Initialization
	GLCD_Init();
	location = 0;
	while(1){
		menu();				// Show 
		while(1){
			joystick = get_button();
			if(joystick == KBD_SELECT){           //If button is pushed
				buttonDelay();
				if(location == 0){    //Music Player
					music();
					location = 0;
					break;
				}
				if(location == 1){    //Photo Gallery
					location2=0;
					gallery();
					location = 1;
					break;
				}
				if(location == 2){ 	//Games
					game1();
					location = 2;
					break;
				}
			}
			else if(joystick == KBD_UP){     //if up pressed
				location--;
				buttonDelay();
			}
			else if(joystick == KBD_DOWN){   //if down pressed
				location++;
				buttonDelay();
			}				
			if(location > 2){   //positions changes from 2 to 0
				location = 0;
			}
			if(location < 0){   //position changes from 0 to 2
				location = 2;
			}
			
			switch(location){  // Move menu arrow + change colours based on value of location
				case 0: 		//Music Player			
					GLCD_SetTextColor(LightBlue);
					GLCD_DisplayString(4, 1, __F1, "->Music Player");
					GLCD_SetTextColor(DarkBlue);
					GLCD_DisplayString(6, 1, __F1, "  Photo Gallery");
					GLCD_DisplayString(8, 1, __F1, "  Direction Game");
					break;
				
				case 1:  		//Photo Gallery
					GLCD_SetTextColor(LightBlue);
					GLCD_DisplayString(6, 1, __F1, "->Photo Gallery");
					GLCD_SetTextColor(DarkBlue);
					GLCD_DisplayString(4, 1, __F1, "  Music Player");
					GLCD_DisplayString(8, 1, __F1, "  Direction Game");
					break;
				
				case 2:  		// Games
					GLCD_SetTextColor(LightBlue);
					GLCD_DisplayString(8, 1, __F1, "->Direction Game");
					GLCD_SetTextColor(DarkBlue);
					GLCD_DisplayString(6, 1, __F1, "  Photo Gallery");
					GLCD_DisplayString(4, 1, __F1, "  Music Player");
					break;
			}
		}
	}
}

