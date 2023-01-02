//Created by SniperJF
//Dedicated to all the competitive gamers out there.
//Compile as: g++ ast12.cpp -lncurses

/*
 * Name: Javier Perez, 2001333771, Assignment 12
 * Description: This program
 * Input: Input comes from the keyboard varies depending on the users choices
 * Output: Various output starting with a welcome screen and maps depending on the users
 * choice.
*/
//#include<iostream>    //cin/cout NOT USED. DO NOT ENABLE!
#include<fstream>       //File Streams
#include<ncurses.h>     //N Curses Library
#include<stdlib.h>      //srand
#include<time.h>        //time

//using namespace std;

void initCurses();
void endCurses();

/*
 * CharMap: Creates the definition for how a map is to be constructed
 * and printed according to the assignments requirements.
 * constructors: CharMap(char *arg)
 *               CharMap(char** c, std::string m, int w, int h)
 * public members: CharMap(char *arg)
 *                 CharMap(char** c, std::string m, int w, int h)
 *                 ~CharMap()
 *                 print()
 *                 mapNape
 *                 width
 *                 height
 * static members: N/A
*/
class CharMap {
  public:
    CharMap(char *arg);
    CharMap(char** c, std::string m, int w, int h) : 
        map(c), mapName(m), width(w), height(h){}
    ~CharMap();

    void print();
    char ** map;
    std::string mapName;
    int width;
    int height;
};

//Your Code Here

int main(int argc, char **argv){
//	srand(time(NULL)); //Comment out to always have the same RNG for debugging
    CharMap *map = (argc == 2) ? new CharMap(argv[1]) : NULL; //Read in input file
    if(map == NULL){printf("Invalid Map File\n"); return 1;}  //close if no file given
    initCurses(); // Curses Initialisations
    map->print();

    //Your Code Here

    delete map; map = NULL;
    printw("\ngg ez\n");
    endCurses(); //END CURSES
    return 0;
}

/*
 * initCurses: Initializes the library curses functions in order
 * to begin constructing maps using the curses functions.
 * parameters: no parameters
 * return value: void function - no return value
*/
void initCurses(){
    // Curses Initialisations
	initscr();
	raw();
	keypad(stdscr, TRUE);
	noecho();
	printw("Welcome - Press Q to Exit\n");
}

/*
 * endCurses: Calls three different functions in order to end the
 * initializations of the curses library
 * parameters: no parameters
 * return value: void function - no return value
*/
void endCurses(){
	refresh();
	getch(); //Make user press any key to close
	endwin();
}


//CharMap Functions
/*
 * CharMap(char * arg): Constructor for CharMap class the constructs the map
 * defined by the compilers second argument.
 * Parameters: char *arg
 * return value: Constructor - no return value
*/
CharMap::CharMap(char *arg){
    char temp;
    std::ifstream fin(arg);
    fin >> mapName;
    fin >> height;
    fin >> temp;
    fin >> width;
    map = new char*[height]; //Allocate our 2D array
    for(int i=0; i<height; i++){
        map[i] = new char[width];
        for(int j=0; j<width; j++) //Read into our array while we're at it!
            fin >> (map[i][j]) >> std::noskipws; //dont skip whitespace
        fin >> std::skipws; //skip it again just so we skip linefeed
    }
    //for(int i=0; i<height; i++){ //Uncomment if you have issues reading
    //    for(int j=0; j<width; j++) printf("%c", map[i][j]); printf("\n");};
}

/* 
 * ~CharMap(): Deconstructor for CharMap class that deallocates any memory
 * created during the constrution of the maps.
 * Parameters: Deconstructor - no parameters
 * return value: Deconstructor - no return value
*/
CharMap::~CharMap(){
    if(map == NULL) return;
    for(int i=0; i<height; i++)
        delete [] map[i];
    delete [] map;
}

/*
 * print: prints out the map onto the console using characters specified
 * in the assignment.
 * parameters: no parameters:
 * return value: Void function - no return value
*/
void CharMap::print(){ //call only after curses is initialized!
    printw("Read Map: '%s' with dimensions %dx%d!\n", 
            mapName.c_str(), height, width);
    //Note the c_str is required for C++ Strings to print with printw
    for(int i=0; i<height; i++){
        for(int j=0; j<width; j++)
            printw("%c", map[i][j]);
        printw("\n");
    }   
}
