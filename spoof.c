/**
 * Using CASIO fx-9860G SDK Library
 *
 * @file spoof.c
 */
#include "fxlib.h"

/**
 * AddIn_main (program main function)
 *
 * @param isAppli   : 1 = This application is launched by MAIN MENU.
 *                  : 0 = This application is launched by a strip in eACT application.
 * @param OptionNum : Strip number (0~3)
 *                    (This parameter is only used when isAppli parameter is 0.)
 *
 * @return int: 1 = No error / 0 = Error
 */
int AddIn_main(int isAppli, unsigned short OptionNum) {
	
	// clearing the whole vram and display driver
	Bdisp_AllClr_DDVRAM();

	menu();

	resetWindow();
	
	// @todo support reboot (if possible) or spoof reboot

    return 1;
}

/**
 * menu() displays the Reset menu.
 */
int menu() {
	unsigned int key, page = 0, temp;
	
	plotMenuPage( page );
	
	while( 1 ) {
        GetKey( &key );
		if ( key == KEY_CTRL_F6 ) {
			page < 1 ? page++ : page--;
			plotMenuPage( page );
		} else if ( key == KEY_CTRL_F2 && page == 1 ) {
			temp = confirmWindow();
			plotMenuPage( page );
			if ( temp == 1 ) {
				return 1;
			}
		}
	}
}

/**
 * plotMenuPage() plots a page of the reset page based on the given page parameter.
 *
 * @param int page: declares which page will be plotted.
 */
int plotMenuPage( int page ) {
	unsigned int i;
	unsigned char * menuItems[][7] = {
		{
			"*****   RESET   *****",
			"F1:Setup Data",
			"F2:Main Memory",
			"F3:Add-In",
			"F4:Storage Memory",
			"F5:Add-In&Storage",
			"F6:Next Page"
		},
		{
			"*****   RESET   *****",
			"F1:Main&Storage",
			"F2:Initialize All",
			"",
			"",
			"",
			"F6:Next Page"
		}
	};
	
	Bdisp_AllClr_DDVRAM();

	for ( i = 0 ; i < 7 ; ++i ) {
		locate( 1, i + 1 );
		Print( menuItems[page][i] );
	}
	
	// @todo buttons at the bottom need to be plotted
}

/**
 * confirmWindow() displays the 'Initialize All' reset confirmation window.
 *
 * @return int: returns which function button got pressed (1 or 6).
 */
int confirmWindow() {
	unsigned int key, i;
	unsigned int windowY[] = { 7, 4, 1, 5, 5 };
	unsigned char * windowItems[] = {
		"Reset OK?",
		"Initialize All",
		"",
		"Yes:[F1]",
		"No :[F6]"
	};
	
	PopUpWin( 5 );
	for ( i = 0 ; i < 5 ; ++i ) {
		locate( windowY[i], i + 2 );
		Print( windowItems[i] );
	}
	
	while( 1 ) {
        GetKey( &key );
		if ( key == KEY_CTRL_F1 ) {
			// loadingBar();
			return 1;
		} else if ( key == KEY_CTRL_F6 ) {
			return 6;
		}
    }
}

int loadingBar() {
	// @todo make this work
	unsigned int key;
	plotMenuPage( 1 );
	PopUpWin( 5 );
	locate( 3, 3 );
	Print( ( unsigned char* ) "One Moment Please" );

	Bdisp_PutDisp_DD();

	Sleep( 2000 );
	locate( 1, 1 );
	Print( ( unsigned char* ) "TEST" );
	plotMenuPage( 1 );
}

int resetWindow() {
	unsigned int key, i;
	unsigned int windowY[] = { 8, 4, 1, 1, 6 };
	unsigned char * windowItems[] = {
		"Reset!",
		"Initialize All",
		"",
		"",
		"Press:[EXIT]"
	};
	
	PopUpWin( 5 );
	for ( i = 0 ; i < 5 ; ++i ) {
		locate( windowY[i], i + 2 );
		Print( windowItems[i] );
	}
	
	while( 1 ) {
		GetKey( &key );
		if ( key == KEY_CTRL_EXIT ) {
			return 1;
		}
	}
}

#pragma section _BR_Size
unsigned long BR_Size;
#pragma section


#pragma section _TOP

/**
 * InitializeSystem
 *
 * @param isAppli   : 1 = Application / 0 = eActivity
 * @param OptionNum : Option Number (only eActivity)
 * 
 * @return int: 1 = No error / 0 = Error
 */
int InitializeSystem(int isAppli, unsigned short OptionNum) {
    return INIT_ADDIN_APPLICATION(isAppli, OptionNum);
}

#pragma section