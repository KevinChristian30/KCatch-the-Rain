#include <stdio.h>
#include <windows.h>

#define BUFFERSIZE 255

namespace utility{

  void clear(){

    system("cls");

  }

  void animateString(const char* string, short delay){

    size_t len = strlen(string);
    for (size_t i = 0; i < len; i++){

      printf("%c", string[i]);
      Sleep(delay);

    }

  }

  const HANDLE OUTPUTHANDLE = GetStdHandle(STD_OUTPUT_HANDLE); 
  void moveCursor(short x, short y){

    COORD coordinate = {x, y};
    SetConsoleCursorPosition(OUTPUTHANDLE, coordinate);

  }

}

namespace playMenu{

  #define WIDTH 30
  #define HEIGHT 20

  const char map[HEIGHT + 1][WIDTH + 1] = {

    "#                            #",
    "#                            #",
    "#                            #",
    "#                            #",
    "#                            #",
    "#                            #",
    "#                            #",
    "#                            #",
    "#                            #",
    "#                            #",
    "#                            #",
    "#                            #",
    "#                            #",
    "#                            #",
    "#                            #",
    "#                            #",
    "#                            #",
    "#                            #",
    "#                            #",
    "#                            #",

  };

  void displayMap(){

    for (unsigned short i = 0; i < HEIGHT; i++) printf("%s\n", map[i]);

  }

  class Cup{

    public:

      short posX, posY;
      const int cupWidth = 9;
    
      Cup(short posX, short posY){

        this->posX = posX;
        this->posY = posY;

      }

      void render(char toRender = '#'){

        utility::moveCursor(posX, posY);
        printf("%c", toRender);
        
        utility::moveCursor(posX, posY + 1);
        printf("%c", toRender);

        for (int i = 0; i < cupWidth; i++){

          utility::moveCursor(posX + i, posY + 1);
          printf("%c", toRender);
        
        }

        utility::moveCursor(posX + cupWidth, posY + 1);
        printf("%c", toRender);
        
        utility::moveCursor(posX + cupWidth, posY);
        printf("%c", toRender);
        
      }

  };

  Cup cup = Cup(10, 3);
  void loop(){

    while (true){

      utility::clear();
      displayMap();
      cup.render();
      getchar();

    }

  }

}

namespace exitMenu{

  void loadLogo(){

    char menu[][82] = {
      "                                        .                            \n",
      "                                       ...                                      \n",
      "                                      .....                                     \n",
      "                                    ....*...                                    \n",
      "                                   .....,.....                                  \n",
      "                                  ....,***,....                                 \n",
      "                                ...***********..                                \n",
      "                             ...,*.....***....,*....                            \n",
      "                            ..**,***.,**,**..***,**..                           \n",
      "                      ...   ...*,*****..*.,*******...    ..                     \n",
      "  ..................****,..    ........***........    ...****...................\n",
      "   ....**..*..***..******..      ...,*******....      ..*******.,**..*..**,...  \n",
      "     .....***,**,...****,..  . ...,*****,****#/.....  ..,****....******.....    \n",
      "       .....*********..........,,******,, &&/*****,.........****,*****.....     \n",
      "        ..***...,**.************,**,,*#&&#**,,**,************.**,...***..       \n",
      "          ..******,..,********,,,* &&&&(,,,,****,,,*********..**,*,**...        \n",
      "          ..,*,*,*,..,,*,*,,,** &&&&&(**,*,*,,,,,*,*%&(*,*,....*,*,*,,.         \n",
      "           ..***,......****,, &&&&&#**,,,,,,***&&&&&&(****.......***,..         \n",
      "             ...    ...****, &&&&&/,,****&%&&&&&&&&&,,****..     ...            \n",
      "             ...    ,..**** &&&&&&*,,********,&&&&& *,***,..    ...             \n",
      "          ...,*,... ...*,*,&&&&&&&&(*,**,***,&&&&& /*,**,*.. ...,.*...          \n",
      "          ..******,....***%&&%(,,******,,,*&&&&&& /**,****....**,****.          \n",
      "          ..****,*,..,******,,**,**,,***,&&&&& (***,,******...**,****.          \n",
      "        ..,**...**,.************,,,****&&&/(**,,,***********..**....**..        \n",
      "      .....,,*,*,***........,***,***,&& /*,,,***,***,.......,***,***,,...       \n",
      "     ....,******....****..  .....*%#(***********,.......****,...,****,*....\n",
      "   ....***.*..**,.,******..    & ,..,*******,....    ..,******.,,*..*.,**,...\n",
      "  .................*****,..   ........****,......    ...*****.................\n",
      "                     ....  ....*,****..*,..,****,*..   ....\n",           
      "                           ...**,***.******,*******.. \n",                   
      "                             ...,**....***...,**,..\n",                    
      "                                ...**********,..\n",                     
      "                                  .....,,......\n",                       
      "                                   .....*....\n",                          
      "                                    ....*...\n",                            
      "                                     .....\n",                               
      "                                       ..\n"                                
    };

    for (int i = 0; i < 37; i++) {

      for (int j = 0; j < 82; j++) printf("%c", menu[i][j]);
      Sleep(10);

    }
    
    utility::animateString("\nWonderful things can be achieved when there is teamwork, hard work, and perseverance\n", 10);

  }

  void exitApp(){

    utility::clear();
    loadLogo();
    getchar();
    exit(0);

  }

}

namespace mainMenu{

  const char LOGO[5][BUFFERSIZE]  = {

    " .       ___          .           _            _______ _                  .___                ", 
    "/   / .'   \\   ___  _/_     ___  /           '   /    /        ___       /   \\   ___  ` , __  ",
    "|_-'  |       /   `  |    .'   ` |,---.          |    |,---. .'   `      |__-'  /   ` | |'  `.",
    "|  \\  |      |    |  |    |      |'   `          |    |'   ` |----'      |  \\  |    | | |    |",
    "/   \\  `.__, `.__/|  \\__/  `._.' /    |          /    /    | `.___,      /   \\ `.__/| / /    |",
                                                                                      
  };

  void display(){

    for (short i = 0; i < 5; i++) printf("%s\n", LOGO[i]);
    puts("1. Play");
    puts("2. Exit");

  }

  void getInput(char* storage){

    printf(">> ");
    scanf("%s", storage);
    getchar();

  }

  void route(const char* input){

    if (strncmp(input, "1", BUFFERSIZE) == 0){ // Play Menu

      playMenu::loop();

    } else if (strncmp(input, "2", BUFFERSIZE) == 0){ // Exit Menu

      exitMenu::exitApp();

    }

  }

  void loop(){

    char input[BUFFERSIZE];
    while(true){

      utility::clear();
      display();
      getInput(input);
      route(input);

    }
    

  }

}

int main(){

  mainMenu::loop();

  return 0;
}
