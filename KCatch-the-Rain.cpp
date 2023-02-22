#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <time.h>
#include <vector>

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

  int bulletsPassed = 0, bulletsCollected = 0;

  void resetGame(){

    bulletsPassed = bulletsCollected = 0;


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

        for (int i = 0; i < cupWidth; i++){

          utility::moveCursor(posX + i, posY + 1);
          printf("%c", toRender);
        
        }
        
      }

      void clear(){

        render(' ');

      }

      void update(char input){

        if (input == 'a' || input == 'A'){ // Left

          if (posX - 1 > 0) posX--;

        } else if (input == 'd' || input == 'D') { // Right

          if (posX + cupWidth < WIDTH - 1) posX++;

        }

      }

  };

  Cup cup = Cup(10, 17);

  class Bullet{

    public:
      
      short posX, posY;
      bool isActive;

      Bullet(short posX, short posY){

        this->posX = posX;
        this->posY = posY;
        this->isActive = true;

      }

      void render(char symbol = 'o'){

        utility::moveCursor(posX, posY);
        printf("%c", symbol);

      }

      void clear(){

        render(' ');

      }

      bool drop(){

        if (posY + 1 < HEIGHT) {

          if (posY + 1 == cup.posY && posX >= cup.posX && posX <= cup.posX + cup.cupWidth){

            utility::moveCursor(WIDTH + 1, HEIGHT - 1);
            printf("Raindrops Collected: %d\n", bulletsCollected++);
            isActive = false;
            return false;

          }

          posY++;
          return true;

        }

        isActive = false;

        bulletsPassed++;
        utility::moveCursor(WIDTH + 1, HEIGHT);
        printf("Raindrops Passed: %d\n", bulletsPassed);

        return false;

      }

  };

  char getInput(){

    if (kbhit()){

      char input = getch();
      return input;

    }

    return ' ';

  }

  void loop(){

    std::vector<Bullet*> bullets;

    struct timespec ts;
    clock_gettime(CLOCK_REALTIME, &ts);
    unsigned long long int bulletsThen = ts.tv_nsec / 1000000;
    unsigned long long int bulletsNow = ts.tv_nsec / 1000000;
    unsigned long long int bulletsGenerationThen = ts.tv_nsec / 1000000;
    unsigned long long int bulletsGenerationNow = ts.tv_nsec / 1000000;

    utility::clear();
    displayMap();
    utility::moveCursor(WIDTH + 1, HEIGHT);
    printf("Raindrops Passed: %d\n", bulletsPassed);

    utility::moveCursor(WIDTH + 1, HEIGHT - 1);
    printf("Raindrops Collected: %d\n", bulletsCollected);

    cup.render();

    char input = ' ';
    while (true){

      input = getInput();
      if (input != ' ') {
        cup.clear();
        cup.update(input);
        cup.render();
      }

      struct timespec ts;
      clock_gettime(CLOCK_REALTIME, &ts);
      bulletsNow = ts.tv_nsec / 1000000;
      bulletsGenerationNow = ts.tv_nsec / 1000000;

      if (bulletsGenerationNow - bulletsGenerationThen >= (unsigned long long int) 900){

        bulletsGenerationThen = bulletsGenerationNow;

        short randomNumber = (rand() % (WIDTH - 2)) + 1;
        bullets.push_back(new Bullet(randomNumber, 0));
        
      }

      if (bulletsNow - bulletsThen >= 200){

        bulletsThen = bulletsNow;

        short count = 0;
        for (Bullet* bullet : bullets){

          if (!bullet->isActive) continue;

          bullet->clear();
          if (!bullet->drop()) {
            continue;
          } else {
           bullet->render();
          }

          count++;

        } 

      }

      if (bulletsPassed >= 50){
        break;
      }

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

      playMenu::resetGame();
      playMenu::loop();
      utility::clear();
      printf("You Collected %d Rain Drops!", playMenu::bulletsCollected);

      getchar();

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

  srand(time(NULL));
  mainMenu::loop();

  return 0;
}
