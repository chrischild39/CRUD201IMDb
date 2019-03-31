#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <strings.h>
#include <ncurses.h>


// array of structs to hold information for every movie record
typedef struct record {

  char  tconst[15];
  char  titletype[15];
  char  primaryTitle[300];
  char  originalTitle[300];
  char  isAdult[3];
  char  startYear[5];
  char  endYear[5];
  char  runtimeMinutes[5];
  char  genres[300];

} record;

// array of structs to hold information for the users movie database
typedef struct userstuff {

  char num[5];
  char title[300];
  char minutes[5];
  char time[15];
  char object[30];

} userstuff;

/* Hash Table for indexing */
typedef struct item {

	char title[300];
  char minutes[5];
	struct item * next;

} item;
  //-----------------------------------------------------
/*Function Declarations*/
int mainmenu(struct item * chain[], int size, char * user_option, char * filename);
int removemovie(struct item * chain[], int size, char * user_option, char * filename);
int addmovie(struct item * chain[], int size, char * user_option, char * filename);
int updatemovie(struct item * chain[], int size, char * user_option, char * filename);
int search(struct item * chain[], int size, char * input, char * filename);
int num(char * t, int size);
int checkfile(char * filename);
int getlin(char * filename);
int findmatch(char * filename, int j, char * title, char * minutes);
int findmatch1(char * filename, int j, char * title);

//function to check if the users file is empty;
int checkfile(char * filename){

  FILE *user = NULL;
  user = fopen( filename , "r" );

  int check = 0;
  if (NULL != user) {
    fseek (user, 0, SEEK_END);
    check = ftell(user);
    if (check == 0){
      fclose(user);
      return 0;
    }
    else {
      fclose(user);
      return 1;
    }
  }
  return 0;
}

int getlin(char * filename){
  FILE *user = NULL;
  user = fopen( filename , "r" );
  char str[1000];
  int j = 0;

  while (fgets(str, sizeof(str), user) != NULL) {
      j++;
  }

  fclose(user);

  return j;
}

int findmatch(char * filename, int j, char * title, char * minutes) {
  FILE *user = NULL;
  user = fopen( filename , "r" );
  int place = 0;

  char * token;
  char str1[1000];

  for(int i = 0; i < j; i++){
    fgets(str1, 1000, user);
    token = strtok(str1, "\t");
    if (strncmp(title, token, 300) == 0) {
      place++;
    }
    token = strtok(NULL, "\t");
    if (strncmp(minutes, token, 5) == 0) {
      place++;
    }
  }
  fclose(user);

  return place;
}
int findmatch1(char * filename, int j, char * title){

  FILE *user = NULL;
  user = fopen( filename , "r" );
  int place = 0;

  char * token;
  char str1[1000];

  for(int i = 0; i < j; i++){
    fgets(str1, 1000, user);
    token = strtok(str1, "\t");
    if (strcasecmp(title, token) == 0) {
      place++;
    }
  }
  fclose(user);

  return place;

}
//function to loop through menu options until quit
int mainmenu(struct item * chain[], int size, char * user_option, char * filename) {

  wclear(stdscr);
  initscr();
  //Welcomes user to the Program and gives them options of what they can do
  printw("     Hello! Welcome to the IMDb Movie Database!              \n");
  printw("          What would you like to do?                         \n");
  printw("      Options: 'add movie' - 'remove movie'                  \n");
  printw("               'update movie'                                \n");
  printw("               'quit'                                        \n");
  refresh();
  printw("     /  \n");
  printw("      / \n");
  printw("       |: ");
  getnstr(user_option, 300);
  refresh();

  if (strcasecmp(user_option, "add movie") == 0 ){
    wclear(stdscr);
    endwin();
    addmovie(chain, size, user_option, filename);
  }
  else if (strcasecmp(user_option, "remove movie") == 0 ){
    wclear(stdscr);
    endwin();
    removemovie(chain, size, user_option, filename);

  }

  else if (strcasecmp(user_option, "update movie") == 0 ){
    wclear(stdscr);
    endwin();
    updatemovie(chain, size, user_option, filename);
  }

  else if (strcasecmp(user_option, "quit") == 0 ){
    printw("     Thanks for using the IMDb Movie Database!     \n");
    printw("                 HAVE A GOOD DAY!                  \n");
    wclear(stdscr);
    endwin();
    return(0);
  }
  else {
    printw("     Sorry! That is not an option. Please try agian     \n");
    endwin();
    wclear(stdscr);
    mainmenu(chain, size, user_option, filename);
  }
  return 0;
}
int removemovie(struct item * chain[], int size, char * user_option, char * filename) {

  wclear(stdscr);
  char movie[301];

  initscr();
  printw("      What movie would you like to remove?                             \n");
  printw("      Instructions: Search for a movie using the EXACT title.                 \n");
  //printw("                    Use the most specific word to search the movie.    \n");
  //printw("                    If the word is a noun, CAPITALIZE the first letter.\n");
  refresh();
  printw("     / \n");
  printw("      / \n");
  printw("       |: ");
  getnstr(movie, 300);
  refresh();

  printw("\n       What is your file name?                          \n");
  printw("       If you do not have one enter the name you would like.           \n");
  printw("       If you are making a file, make sure the file ends with .txt     \n");
  printw("     / \n");
  printw("      / \n");
  printw("       |: ");
  getnstr(filename, 99);

  int j = getlin(filename);
  int place = findmatch1(filename, j, movie);

  if ( j == 0 || place == 0 ){
    printw("\n      That Movie is not in your file.         \n");
    printw("        Options: 'quit' - back to main menu      \n");
    printw("                 'exit' - end program           \n");
    printw("     / \n");
    printw("      / \n");
    printw("       |: ");
    getnstr(user_option, 300);
    if (strcasecmp(user_option, "exit") == 0 ){
      printw("     Thanks for using the IMDb Movie Database!     \n");
      printw("                 HAVE A GOOD DAY!                  \n");
      wclear(stdscr);
      endwin();
      return(0);

    }
    else if (strcasecmp(user_option, "quit") == 0 ){
      wclear(stdscr);
      endwin();
      mainmenu(chain, size, user_option, filename);
    }
    else {
      printw("     Sorry! That is not an option.     \n");
      printw("     Redirecting to Main Menu...       \n");
      wclear(stdscr);
      endwin();
      mainmenu(chain, size, user_option, filename);
    }
  }
  else {

    struct userstuff * array = malloc( j * sizeof( userstuff ));

    char * token;
    char str2[1000];
    FILE * user = NULL;
    user = fopen(filename, "r" );
    for(int i = 0; i < j; i++) {
      fgets(str2, 1000, user);
      token = strtok(str2, "\t");
      strncpy(array[i].title, token, 300);
      token = strtok(NULL, "\t");
      strncpy(array[i].minutes, token, 5);
      token = strtok(NULL, "\t");
      strncpy(array[i].time, token, 15);
      token = strtok(NULL, "\t");
      strncpy(array[i].object, token, 30);
    }
    fclose (user);

    user = fopen(filename, "w" );
    for(int i = 0; i < j; i++) {
      if (strncmp(array[i].title,movie, 300) != 0){
        fprintf(user,"%s\t%s\t%s\t%s\t\n", array[i].title,array[i].minutes,array[i].time,array[i].object);
      }
    }
    fclose(user);
    printw("\n      Movie Removed.                           \n");
    printw("\n      What would you like to do now?         \n");
    printw("        Options: 'quit' - back to main menu      \n");
    printw("                 'exit' - end program \n");
    printw("     / \n");
    printw("      / \n");
    printw("       |: ");
    getnstr(user_option, 300);
    if (strcasecmp(user_option, "exit") == 0 ){
      printw("     Thanks for using the IMDb Movie Database!     \n");
      printw("                 HAVE A GOOD DAY!                  \n");
      wclear(stdscr);
      endwin();
      return(0);

    }
    else if (strcasecmp(user_option, "quit") == 0 ){
      wclear(stdscr);
      endwin();
      mainmenu(chain, size, user_option, filename);
    }
    else {
      printw("     Sorry! That is not an option.     \n");
      printw("     Redirecting to Main Menu...       \n");
      wclear(stdscr);
      endwin();
      mainmenu(chain, size, user_option, filename);
    }
  }
  return 0;
}

int addmovie(struct item * chain[], int size, char * user_option, char * filename) {

  wclear(stdscr);
  char movie[301];
  int num = 0;

  initscr();
  //printw("     Hello! Welcome to the IMDb Movie Database!             \n");
  printw("      What would movie would you like to search for?          \n");
  printw("      Instructions: Search for a movie using ONE word.        \n");
  printw("                    Use the most specific word to search the movie.    \n");
  printw("                    If the word is a noun, CAPITALIZE the first letter.\n");
  refresh();
  printw("     / \n");
  printw("      / \n");
  printw("       |: ");
  getnstr(movie, 300);
  refresh();
  //finds the movie items they searched for
  int bol = search(chain, size, movie, filename);
  //reruns the function if no movies are found
  if ( bol == 0) {
    printw("     No Records Match That Search.     \n");
    wclear(stdscr);
    endwin();
    mainmenu(chain, size, user_option, filename);
  }

  printw("      We found some moives that contain that word.                   \n");
  printw("      Which movie would you like to add?                             \n");
  //printw("      Enter 'quit' at any time to go back to the main menu.          \n");
  printw("      Instructions: Enter the NUMBER to the LEFT of the movie        \n");
  printw("                    if that movie is the one you would like          \n");
  printw("                    to add to your database.                         \n");
  refresh();
  printw("     / \n");
  printw("      / \n");
  printw("       |: ");
  scanw("%d", &num);

  printw("\n       What is your file name?                          \n");
  printw("       If you do not have one enter the name you would like.           \n");
  printw("       If you are making a file, make sure the file ends with .txt     \n");
  printw("     / \n");
  printw("      / \n");
  printw("       |: ");
  getnstr(filename, 99);
  //grabs the record that will be added to users file

  FILE *index = NULL;
  index = fopen( "title.index.tsv" , "r");
  char number[5];
  char  title[300];
  char  minutes[5];
  char  time[15];
  char  object[30];
  char str[1000];
  char * token;
  for (int i = 0; i <= num; i++){
    fgets(str, 1000, index);
    if (i == num) {
      token = strtok(str, "\t");
      strncpy(number, token, 5);
      token = strtok(NULL, "\t");
      strncpy(title, token, 300);
      token = strtok(NULL, "\t");
      strncpy(minutes, token, 5);
      break;
    }
  }
  //printw("working");
  fclose(index);

  //checks to see if the user has that movie in their file

  int check = checkfile(filename);

    if ( check == 0){
      FILE *user = NULL;
      user = fopen( filename , "w" );

      printw("\n     When did you get the movie?           \n");
      printw("     Enter a Date in aa/bb/cccc format     \n");
      printw("     / \n");
      printw("      / \n");
      printw("       |: ");
      getnstr(time, 14);
      refresh();
      printw("\n           What do you have the movie on?  \n");
      printw("           Ex: DVD, Download etc.             \n");
      printw("     / \n");
      printw("      / \n");
      printw("       |: ");
      getnstr(object, 29);
      refresh();
      fprintf(user,"%s\t%s\t%s\t%s\t\n",title,minutes,time,object);
      fclose(user);
    }

    else {


      int j = getlin(filename);
    //  printw("%d\n", j);
  //    printw("%s\t%s\n",title,minutes);
      int place = findmatch(filename, j, title, minutes);
//      printw("%d\n", place);

      // if the user does not have the movie in their file
      struct userstuff * array1 = malloc( (j+1) * sizeof( userstuff ));

      if (place < 2){

      printw("\n     When did you get the movie? Enter a Date in aa/bb/cccc format     \n");
      printw("     / \n");
      printw("      / \n");
      printw("       |: ");
      getnstr(time, 14);
      refresh();
      printw("\n     What do you have the movie on? Ex: DVD, Download etc.             \n");
      printw("     / \n");
      printw("      / \n");
      printw("       |: ");
      getnstr(object, 29);
      refresh();

      char str2[1000];
      FILE * user = NULL;
      user = fopen(filename, "r" );
      for(int i = 0; i < j+1; i++) {
        if ( i == j ) {
          strncpy(array1[i].title, title, 300);
          strncpy(array1[i].minutes, minutes, 5);
          strncpy(array1[i].time, time, 15);
          strncpy(array1[i].object, object, 30);
          break;
        }
        fgets(str2, 1000, user);
        token = strtok(str2, "\t");
        strncpy(array1[i].title, token, 300);
        token = strtok(NULL, "\t");
        strncpy(array1[i].minutes, token, 6);
        token = strtok(NULL, "\t");
        strncpy(array1[i].time, token, 15);
        token = strtok(NULL, "\t");
        strncpy(array1[i].object, token, 30);
      }
      fclose (user);
      user = fopen(filename, "w" );
      for(int i = 0; i < j+1; i++) {
        fprintf(user,"%s\t%s\t%s\t%s\t\n", array1[i].title,array1[i].minutes,array1[i].time,array1[i].object);
      }
      fclose(user);
    }
    else {
      printw("\n      You Aleady Have that Movie.         \n");
      printw("        Options: 'quit' - back to main menu      \n");
      printw("                 'exit' - quit program \n");
      printw("     / \n");
      printw("      / \n");
      printw("       |: ");
      getnstr(user_option, 300);
      if (strcasecmp(user_option, "exit") == 0 ){
        printw("     Thanks for using the IMDb Movie Database!     \n");
        printw("                 HAVE A GOOD DAY!                  \n");
        wclear(stdscr);
        endwin();
        return(0);

      }
      else if (strcasecmp(user_option, "quit") == 0 ){
        wclear(stdscr);
        endwin();
        mainmenu(chain, size, user_option, filename);
      }
      else {
        printw("     Sorry! That is not an option.     \n");
        printw("     Redirecting to Main Menu...       \n");
        wclear(stdscr);
        endwin();
        mainmenu(chain, size, user_option, filename);
      }
    }
  }
  printw("\n      Movie Added.                           \n");
  printw("      What would you like to do now?           \n");
  printw("      Options: 'quit' - back to main menu      \n");
  printw("               'exit' - quit program \n");
  printw("     / \n");
  printw("      / \n");
  printw("       |: ");
  getnstr(user_option, 300);

  if (strcasecmp(user_option, "exit") == 0 ){
    printw("     Thanks for using the IMDb Movie Database!     \n");
    printw("                 HAVE A GOOD DAY!                  \n");
    wclear(stdscr);
    endwin();
    return(0);

  }
  else if (strcasecmp(user_option, "quit") == 0 ){
    wclear(stdscr);
    endwin();
    mainmenu(chain, size, user_option, filename);
  }
  else {
    printw("     Sorry! That is not an option.     \n");
    printw("     Redirecting to Main Menu...       \n");
    wclear(stdscr);
    endwin();
    mainmenu(chain, size, user_option, filename);
  }

  return 0;
}

int updatemovie(struct item * chain[], int size, char * user_option, char * filename){

  wclear(stdscr);
  char movie[301];

  initscr();
  printw("      What movie would you like to Update?                             \n");
  printw("      Instructions: Search for a movie using the EXACT title.                 \n");
  refresh();
  printw("     / \n");
  printw("      / \n");
  printw("       |: ");
  getnstr(movie, 300);
  refresh();

  printw("\n       What is your file name?                          \n");
  printw("       If you do not have one enter the name you would like.           \n");
  printw("       If you are making a file, make sure the file ends with .txt     \n");
  printw("     / \n");
  printw("      / \n");
  printw("       |: ");
  getnstr(filename, 99);

  int j = getlin(filename);
  int place = findmatch1(filename, j, movie);

  if ( j == 0 || place == 0 ) {
    printw("\n      That Movie is not in your file.         \n");
    printw("        Options: 'quit' - back to main menu      \n");
    printw("                 'exit' - end program \n");
    printw("     / \n");
    printw("      / \n");
    printw("       |: ");
    getnstr(user_option, 300);
    if (strcasecmp(user_option, "exit") == 0 ){
      printw("     Thanks for using the IMDb Movie Database!     \n");
      printw("                 HAVE A GOOD DAY!                  \n");
      wclear(stdscr);
      endwin();
      return(0);

    }
    else if (strcasecmp(user_option, "quit") == 0 ){
      wclear(stdscr);
      endwin();
      mainmenu(chain, size, user_option, filename);
    }
    else {
      printw("     Sorry! That is not an option.     \n");
      printw("     Redirecting to Main Menu...       \n");
      wclear(stdscr);
      endwin();
      mainmenu(chain, size, user_option, filename);
    }
  }

  else {
    printw("\n       What would you like to update?                          \n");
    printw("       Options: 'title' - movie title                            \n");
    printw("                'minutes' - length of movie                      \n");
    printw("                'time' - date when you got the moive             \n");
    printw("                'object' - how you have aquired the movie        \n");
    printw("     / \n");
    printw("      / \n");
    printw("       |: ");
    getnstr(user_option, 300);

    if (strcasecmp(user_option, "title") == 0 ){

      char title[300];

      printw("      What would you like the new title to be?                         \n");
      printw("      Instructions: Enter the new title you would like for your movie. \n");
      refresh();
      printw("     / \n");
      printw("      / \n");
      printw("       |: ");
      getnstr(title, 300);
      refresh();

      struct userstuff * array = malloc( j * sizeof( userstuff ));

      char * token;
      char str2[1000];
      FILE * user = NULL;
      user = fopen(filename, "r" );
      for(int i = 0; i < j; i++) {
        fgets(str2, 1000, user);
        token = strtok(str2, "\t");
        strncpy(array[i].title, token, 300);
        token = strtok(NULL, "\t");
        strncpy(array[i].minutes, token, 5);
        token = strtok(NULL, "\t");
        strncpy(array[i].time, token, 15);
        token = strtok(NULL, "\t");
        strncpy(array[i].object, token, 30);
        if (strncmp(array[i].title, movie, 300) == 0) {
          strncpy(array[i].title, title, 300);
        }
      }
      fclose (user);

      user = fopen(filename, "w" );
      for(int i = 0; i < j; i++) {
          fprintf(user,"%s\t%s\t%s\t%s\t\n", array[i].title,array[i].minutes,array[i].time,array[i].object);
      }
      fclose(user);

    }
    else if (strcasecmp(user_option, "minutes") == 0 ){

      char minutes[5];

      printw("      How many minutes would you like it to be?                             \n");
      printw("      Instructions: Enter the new minutes you would like for your movie. \n");
      refresh();
      printw("     / \n");
      printw("      / \n");
      printw("       |: ");
      getnstr(minutes, 5);
      refresh();

      struct userstuff * array = malloc( j * sizeof( userstuff ));

      char * token;
      char str2[1000];
      FILE * user = NULL;
      user = fopen(filename, "r" );
      for(int i = 0; i < j; i++) {
        fgets(str2, 1000, user);
        token = strtok(str2, "\t");
        strncpy(array[i].title, token, 300);
        token = strtok(NULL, "\t");
        strncpy(array[i].minutes, token, 5);
        token = strtok(NULL, "\t");
        strncpy(array[i].time, token, 15);
        token = strtok(NULL, "\t");
        strncpy(array[i].object, token, 30);
        if (strncmp(array[i].title, movie, 300) == 0) {
          strncpy(array[i].minutes, minutes, 5);
        }
      }
      fclose (user);

      user = fopen(filename, "w" );
      for(int i = 0; i < j; i++) {
          fprintf(user,"%s\t%s\t%s\t%s\t\n", array[i].title,array[i].minutes,array[i].time,array[i].object);
      }
      fclose(user);

    }
    else if (strcasecmp(user_option, "time") == 0 ){

      char time[15];

      printw("      What new date did you aquire the movie?                             \n");
      printw("      Instructions: Enter the new date you would like for your movie. \n");
      refresh();
      printw("     / \n");
      printw("      / \n");
      printw("       |: ");
      getnstr(time, 15);
      refresh();

      struct userstuff * array = malloc( j * sizeof( userstuff ));

      char * token;
      char str2[1000];
      FILE * user = NULL;
      user = fopen(filename, "r" );
      for(int i = 0; i < j; i++) {
        fgets(str2, 1000, user);
        token = strtok(str2, "\t");
        strncpy(array[i].title, token, 300);
        token = strtok(NULL, "\t");
        strncpy(array[i].minutes, token, 5);
        token = strtok(NULL, "\t");
        strncpy(array[i].time, token, 15);
        token = strtok(NULL, "\t");
        strncpy(array[i].object, token, 30);
        if (strncmp(array[i].title, movie, 300) == 0) {
          strncpy(array[i].time, time, 15);
        }
      }
      fclose (user);

      user = fopen(filename, "w" );
      for(int i = 0; i < j; i++) {
          fprintf(user,"%s\t%s\t%s\t%s\t\n", array[i].title,array[i].minutes,array[i].time,array[i].object);
      }
      fclose(user);

    }
    else if (strcasecmp(user_option, "object") == 0 ){
      char object[30];

      printw("      What new way did you aquire this movie?                             \n");
      printw("      Instructions: Enter the new format you would like for your movie. \n");
      refresh();
      printw("     / \n");
      printw("      / \n");
      printw("       |: ");
      getnstr(object, 29 );
      refresh();

      struct userstuff * array = malloc( j * sizeof( userstuff ));

      char * token;
      char str2[1000];
      FILE * user = NULL;
      user = fopen(filename, "r" );
      for(int i = 0; i < j; i++) {
        fgets(str2, 1000, user);
        token = strtok(str2, "\t");
        strncpy(array[i].title, token, 300);
        token = strtok(NULL, "\t");
        strncpy(array[i].minutes, token, 5);
        token = strtok(NULL, "\t");
        strncpy(array[i].time, token, 15);
        token = strtok(NULL, "\t");
        strncpy(array[i].object, token, 30);
        if (strncmp(array[i].title, movie, 300) == 0) {
          strncpy(array[i].object, object, 30);
        }
      }
      fclose (user);

      user = fopen(filename, "w" );
      for(int i = 0; i < j; i++) {
          fprintf(user,"%s\t%s\t%s\t%s\t\n", array[i].title,array[i].minutes,array[i].time,array[i].object);
      }
      fclose(user);
    }

  }

  printw("\n      Movie Updated.                         \n");
  printw("      What would you like to do now?           \n");
  printw("      Options: 'quit' - back to main menu      \n");
  printw("               'exit' - end program \n");
  printw("     / \n");
  printw("      / \n");
  printw("       |: ");
  getnstr(user_option, 300);

  if (strcasecmp(user_option, "exit") == 0 ){
    printw("     Thanks for using the IMDb Movie Database!     \n");
    printw("                 HAVE A GOOD DAY!                  \n");
    wclear(stdscr);
    endwin();
    return(0);

  }
  else if (strcasecmp(user_option, "quit") == 0 ){
    wclear(stdscr);
    endwin();
    mainmenu(chain, size, user_option, filename);
  }
  else {
    printw("     Sorry! That is not an option.     \n");
    printw("     Redirecting to Main Menu...       \n");
    wclear(stdscr);
    endwin();
    mainmenu(chain, size, user_option, filename);
  }
  return 0;
}

/*function to make the index key for the hash*/
int num(char * t, int size){
  int len = strlen(t);
  int sum = 0;

  for (int i = 0; i < len; i++) {
    if(t[i] != ';' && t[i] != ':' && t[i] != ',') {
      if ( i > 0){
        sum = (sum * i) + t[i];
      }
      else {
        sum = sum + t[i];

      }
    }
  }
  if( sum < 0){
    sum = sum * -1;
  }

  return sum % size;

}
//function to search for the hashtable
int search(struct item * chain[], int size, char * input, char * filename) {

  FILE *index = NULL;
  index = fopen( "title.index.tsv" , "w");
  if (index == NULL) {
    printf("Error Opening Index for Writing");
  return 0;
  }

  char * token;
  int key = num(input, size);
  item * temp = chain[key];

  if(temp == NULL) {
    fclose(index);
    return 0;
  }

  int j = 0;

  while(temp != NULL) {

    char str[300];
    strncpy(str, temp->title, 300);
    token = strtok(str, " ");

    while(token != NULL) {
      int len = strlen(token);
      /* get the first token */
      if (strcasecmp(token, input) == 0) {
        fprintf(index, "%d:\t%s\t%s\t\n", j, temp->title, temp->minutes); j++;
        break;
      }
      else if (token[len-1] == ';' || token[len-1] == ':' || token[len-1] == ','){
        char * t = token;
        t[len - 1] = '\0';
        if ( strcasecmp(t, input) == 0 ){
          fprintf(index, "%d:\t%s\t%s\t\n", j, temp->title, temp->minutes); j++;
          break;
        }
        else {
          token = strtok(NULL, " ");
        }
      }
      else {
        token = strtok(NULL, " ");
      }
    }
    temp = temp->next;
  }

  fclose(index);
  return j;
}

int main(void){

//Opening files for the reading and writing of temp information
  FILE *basic = NULL;
  basic = fopen("title.basics.tsv", "r");
  if (basic == NULL){
    printf("Error Openeing File");
    return 0;
  }
  FILE *index = NULL;
  index = fopen("title.index.tsv", "w");
  if (index == NULL) {
    printf("Error Opening Index for Writing");
    return 0;
  }
  FILE *tempar = NULL;
  tempar = fopen("title.temp.tsv", "w");
  if (tempar == NULL) {
    printf("Error Opening Temp for Writing");
    return 0;
  }
  //------------------------------------------

//variables for the first loop to put all the records into a matrix, separating cols
  fclose(basic);
  char file[] = "title.basics.tsv";
  int lines = getlin(file);
  char str[4096];
  int count = 0;
  basic = fopen("title.basics.tsv", "r");
//initialization and allocation of the array of structs that will hold my matrix
  struct record * movie;
  movie = malloc(lines * sizeof( record ));

//variable that temp stores strings between tabs for storage in matrix
  char * token;
  int j = 0;
    // get the first peice of the record
  for (int i = 0; i < lines; i++){
    fgets(str, 1000, basic);
        if (str[10] == 'm') {
      token = strtok(str, "\t");
    // walk through other peices of the record
        strncpy(movie[j].tconst, token, 15);
        token = strtok(NULL, "\t");
        strncpy(movie[j].titletype, token, 15);
        token = strtok(NULL, "\t");
        strncpy(movie[j].primaryTitle, token, 300);
        token = strtok(NULL, "\t");
        strncpy(movie[j].originalTitle, token, 300);
        token = strtok(NULL, "\t");
        strncpy(movie[j].isAdult, token, 3);
        token = strtok(NULL, "\t");
        strncpy(movie[j].startYear, token, 5);
        token = strtok(NULL, "\t");
        strncpy(movie[j].endYear, token, 5);
        token = strtok(NULL, "\t");
        strncpy(movie[j].runtimeMinutes, token, 5);
        token = strtok(NULL, "\n");
        strncpy(movie[j].genres, token, 300);
        j++;
//count of all records to ensure matrix is correct
      count++;
    }
  }

//test to ensure information is the same as the basics table (NOT NECESSARY)

    //initialization of hashtable including the size of the hashtable
    int size = 10001;
    struct item * chain[size];
    //index of the hashtable
    int key = 0;
    //variables for words that should not be indexed, constants
    const char the[] = "the";
    const char a[] = "a";
    const char of[] = "of";
    const char and[] = "and";
    const char four[] = "for";
    const char or[] = "or";
    const char in[] = "in";
    const char an[] = "an";
    const char o[] = "o";
    const char as[] = "as";
    const char but[] = "but";
    const char to[] = "to";
    const char on[] = "on";
    const char into[] = "into";
    const char onto[] = "onto";
    const char fi[] = "if";
    const char with[] = "with";
    //initialization of the hashtable to NULL / containing no items
    for (int i=0; i < size; i++) {
      chain[i] = NULL;
    }
    //loading the hashtable beginning
    for (int i = 0; i < count; i++) {
        // looping through every movie record / creating a temp string
        // since strtok modifies original string
        char * t;
        char temp[300];
        strcpy( temp , movie[i].primaryTitle );
        //get the first word of the title
        t = strtok(temp, " ");
        //walk through other words in title until end of title
        while( t != NULL ) {
          //compare the word to see if it is relevant to hash or not
          if (strcasecmp( t , the ) != 0 && strcasecmp( t , a ) != 0 && strcasecmp( t , four ) != 0 && strcasecmp( t , or ) != 0 && strcasecmp( t , in ) != 0 && strcasecmp( t , and ) != 0 && strcasecmp( t , an ) != 0 && strcasecmp( t , of ) != 0 && strcasecmp( t , o ) != 0 && strcasecmp( t , as ) != 0 && strcasecmp( t , but ) != 0 && strcasecmp( t , to ) != 0 && strcasecmp( t , on ) != 0 && strcasecmp( t , into ) != 0 && strcasecmp( t , onto ) != 0 && strcasecmp( t , fi ) != 0 && strcasecmp( t , with ) != 0) {
            //hashing the function to get the index it should be insterted into
            key = num(t, size);
            //allocation of node to be inserted into the hashtable
            struct item * newNode = malloc(sizeof(struct item));
            strncpy(newNode->title, movie[i].primaryTitle, 300);
            strncpy(newNode->minutes, movie[i].runtimeMinutes, 5);
            newNode->next = NULL;
            //if the number of items does not equal 0, the list contains elements at that index
            if (chain[key] != NULL){
              struct item * new = chain[key];
              while(new->next){
                new = new->next;
              }
              new->next = newNode;
              t = strtok(NULL, " ");
            }
            //else the number of items is 0, the list is empty at the given index
            else {
              chain[key] = newNode;
              t = strtok(NULL, " ");
            }
          }
          //if not relevent scan the next word in the title
          else {
            t = strtok(NULL, " ");
          }
        }

      }

      //closeing all files
      fclose(index);
      fclose(basic);
      fclose(tempar);

      //hashing and indexing complete starting GUI

      char user_option[301];
      char filename[99];

      mainmenu(chain, size, user_option, filename);


  return 0;
}
