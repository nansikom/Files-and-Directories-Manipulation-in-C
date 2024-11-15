#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// creation of a struct movie with tiltle year language and rate this is where we are initialising our struct.
struct movie 
 {
    char *title;
    int  year;
    char* language;
    float  rate;
    struct movie *next;    

 };

 /*
 namen:Mary Nansikombi
 description:function that allocated memory for the structs and splits all lines into delimeters cut through by tokenizers(strtok)
 how it does it:allocates memory for the struct using malloc, uses a save ptr to know where the tokenizer stopped cutting from.saves address and starts cutting delim
 delimeters again from there.
 Uses fucntions like atoi to convert these integers to strings,strcpy to copy integers since we always need a copy of the string.
 code is also adopted from example code file provided on assignment page in main.c https://canvas.oregonstate.edu/courses/1942597/assignments/9344788
 */
 
 struct movie *createmovie( char *currline){
    struct movie *currmovie = malloc(sizeof (struct movie));
    // we want this to save where the tokenizer has actually stopped working from.
    char *saveptr;
    //ur trying to save the title into the struct ur in and using save ptr to keen the position where the tokenizer stopped working from with in the current line.U copy the token of title so u have it present in the struct
    char *token = strtok_r(currline, ",", &saveptr);
    currmovie->title = calloc(strlen(token) + 1, sizeof(char));
   strcpy(currmovie->title, token);
  // printf("recorded title;Q%sQ\n",currmovie->title);fflush(stdout);


    token = strtok_r(NULL, ",", &saveptr);
    // converting year into an integer.
    currmovie->year = atoi(token);

    token = strtok_r(NULL, ",", &saveptr);
    // ur trying to copy token of langauage in the struct and using save ptr to know where in the struct it has stopped.
    currmovie->language = calloc(strlen(token) + 1, sizeof(char));
    strcpy(currmovie->language, token);

    token = strtok_r(NULL, "\n", &saveptr);
    //currmovie->rate = calloc(strlen(token) + 1, sizeof(char));
    currmovie->rate = atof(token);
     currmovie->next = NULL;
     return currmovie;
 }
/*
name:Mary Nansikombi
description:Trying to process the file by taking in arguments like file path
Initialising of our linked list by first checking if head is null so we start from the beginning
Ensuring we iterate it by using p =p->next till we realise our list is done
closing the file.
*/
struct  movie *processFile(char *filepath){
    FILE *movieFile = fopen(filepath, "r");
    
    char *currline = NULL;
    size_t len = 0;

    ssize_t nread;
    char *token;
    //The head of the linked list
    struct movie * head = NULL;
    //the tail of the linked list
    struct movie *tail = NULL;

//getline(&currline, &len, movieFile);
// Read the file line by line
    while ((nread = getline(&currline, &len, movieFile)) != -1)
    {
        struct movie *newNode = createmovie(currline);
        //trying to see if this is the start of the linked list to see iif it has noo noodes
      //  printf("title is Q%sQ\n", newNode->title);fflush(stdout);
        if (head == NULL){
            head = newNode;
            tail = newNode;

        }
        //try and tag the newr nodes to the tail by connecting new nodes to the tail and updating it to be the tail so the new node becomes the tail
        else {
            tail->next = newNode;
            tail = newNode;

        }
    }
    free(currline);
    fclose(movieFile);
    return head;
}

/*
* Print data for the given movie
using our elements from the struct to print the given information.
we want to print the year,language and rate we use this -> to acess our membe variables in the struct
Not this is from one movie
*/

void printmovie(struct movie* amovie){
  printf("%s, %d, %s, %.1f\n", amovie->title,
               amovie->year,
               amovie->language,
               amovie->rate);
}
/*
*Print the linked list of students
This function does something similar only issue or difference is it actually prints the whole thing without leaving anything behind with in our linked list.
It prints all our individual movie nodes until all of them are actually done within our linked list.
*/

void printmovielist(struct movie *list)
{
    while (list != NULL)
    {
        printmovie(list);
        list = list->next;
    }
}

/*
Name:Mary Nansikombi
Search function basically works by taking in a year as an argument checks if our linked list is Null and looks for
all movies with in the year specified by the user.Works by comparing year of user and year in linked list to ensure we are printing
movies recieved with in that year.
uses the list thing to help us access our member variables with in the struct.
Post conditions:Returns the movies with in a given year.else returns none if no were found.
*/
/*void searchmovielist(struct movie* list, int year) {
    int count = 0;

    while (list != NULL) {
        if (list->year == year) {
            printf("%s\n", list->title); fflush(stdout);
            count++;
        }
        list = list->next;
    }

    if (count == 0) {
        printf("No movies found for the specified year %d.\n", year);
    }
}*/
void searchmovielist(struct movie* list, int year){
    int count = 0;
    while (list != NULL){
        if (list->year == year){
            printf("%s\n", list->title); fflush(stdout);
            count++;
            }
            list = list->next;

        }
        if (count == 0){
            printf("No movies found for the specified year %d.\n",year);

        }
    }

/*
brings out all movies based off the user specified language.uses strstr to compare if any elements within the linked list have the user input
checks if the linked list is null.Uses a different pointer to point to the start of the linked list since the other one is done so u need another pointer to help u access ur variables
comares languaege from user and the one in the linked list and prints out all the movies related to that language.
*/

void languagelist(struct movie* list,  const char *userlang){
struct movie *p = list;
int count =0;
    while(p !=NULL){
       
       if(strstr(p->language, userlang) != NULL){
        printf(" %s, %d, %.1f\n",  p->title,p->year,p->language,p->rate);
        count = 1;
    } 
        
        
        p = p->next;
    }
    if (!count){
        printf("sorry no movie exist dear %d\n",userlang);
    }
} 
 
       
/*
Description
Prints the highest rated movies with in our linked list
Works by using of our two pointers
One that is checking and excanging if the rate being checked is higher than the one in linked list
Loops our years with in our range.
makes sure we have our pointer to iterate.
checks if were with in the range of years and if the rate on check is  higher than the highest rate with in that year
if it is , we exchange them ou to make sure current->rate is our highest.
go to the next node after doing all ur exchanges.
movie variable holds for us our results to print out the highest results of the movie within that year that had the highest rate.
*/

void highrates(struct movie *head){
for(int i=1900;i<2030; i++){
    struct movie *movie =NULL;
    //pointer to current.
    struct movie *current =head;
    float highestrate = 0;
      //movie = NULL;
       
       while(current){
         if(current->year == i  && current->rate >highestrate)
{
        highestrate = current->rate;
        movie = current;
        
}
current = current->next;
}
       if (movie!=NULL){
printf(" %s, %d, %.1f\n", movie->title, movie->year, movie->rate);
  }

  
  }
  }

/*freeees the movie list
*/


void freeMovieList(struct movie *list){
    while (list != NULL){
    struct movie *temp = list;
    list = list->next;
    free(temp->title);
    free(temp->language);
    free(temp);
    }
}



/*
Next steps write down the code for the user input.
create conditions to jump to certain functions when a codition is chosen
in the function make sure to store user input with in a variable
Use string compare to search all the different kind of nodes and start maybe putting them in a count and print out all of the recorded movie structs for all the movies
*/
int main (int argc, char *argv[]){
     if (argc < 2)
    {
        printf("You must provide the name of the file to process\n");
        printf("Example usage: ./students movies.csv\n");
        return EXIT_FAILURE;
    }
    struct movie *list = processFile(argv[1]);
    //printmovielist(list);
    //return EXIT_SUCCESS;
    //printf("title is Q%sQ\n", newNode->title);fflush(stdout);
    if (list != NULL)
    {
        printmovielist(list);
        
       // freeMovieList(list);
    }
    
    // Clean up and free memory here if needed
    //head = NULL;
    //char* title;
    //int  year;
   // char* language;
  // float  rate
    const char *movie_file = "movies.csv";
    FILE* file  = fopen("movies.csv","r");
     if (file == NULL){
        printf("This file doesnt exist");
        return 1;
     }

  int moviecount = -1;
    char buffer [1024];
    
    while (fgets (buffer, sizeof(buffer), file) != NULL){
        moviecount++;
    }
    //fclose(file);
        
     printf("Processed file %s and parsed data for %d movies \n",movie_file, moviecount);
 
    while (1){
    int choice;
    printf(" 1.Show movies released in the specified year.\n");
    printf(" 2.Show highest rated movie for each year.\n");
    printf("3.Show the title and year of release of all movies in a specific language .\n");
    printf("4.Exit from the program .\n");
    printf(" Enter a choice from 1 to 4: .\n");
    scanf("%d", &choice);
    if (choice  == 1) {
        int year;
        printf("Enter the year for which you want to see the movie .\n");
        scanf("%d", &year);
        searchmovielist(list,year);
        
    } else if (choice == 2 ) {
        float rate;
        printf(" highest rated movie for each year .\n"); 
        //scanf("%f", &rate);
        int year;
        highrates(list);
        
    } else if  (choice == 3) {
         char userlang[100];
         //int numMovies = sizeof(movies) / sizeof(movies[0]);
         printf("Title and year of release of all movies in a specific lanuage .\n");
         scanf("%s", userlang);
         languagelist(list,userlang);
         
    } else if (choice == 4){
            printf("Your out of the program");
            break;
    }
    
    


    }
    return EXIT_SUCCESS;
}


    
    

   
