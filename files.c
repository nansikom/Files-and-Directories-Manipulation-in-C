#include <sys/stat.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <limits.h>
/*
Name:Mary nansikombi
Date:10/30/2023.
Description: Creation of a struct to help store the movies.
Preconditions:Stores the title,year,language and rate
Post conditions:brings back our struct
*/
struct movie 
 {
    char* title;
    int  year;
    char* language;
    float  rate;
    struct movie *next;    

 };
 /*
Description: Creation of a struct to help store the movies.
Preconditions:Fucntion to dynamically allocate the tokens and set up the tokenizer were trying to find a way to better access and tokenise
the data and copying it,trying to save it as strings so it is passed in well and correctly.
Post conditions:return the curr movie which is our movie holder with all our tokenized data.Use -> to be able to access member variables of 
struct student.Curr movie is helping you to access member variables of struct movie and ur passing in this tokenizer to make sure u save the tokens 
or wherever ur at.
Code from our assignment1
*/


 // dynamically allocating memmory on the heap for an individual movie sturct takes a pointer to the current movie 
 //and uses a tokenizer to save the place where they stopped cutting the " " delimeters
 struct movie *createmovie( char *currline){
    struct movie *currmovie = malloc(sizeof (struct movie));
    // we want this to save where the tokenizer has actually stopped working from.
    char *saveptr;
    //ur trying to save the title into the struct ur in and using save ptr to keen the position where the tokenizer stopped working from with in the current line.U copy the token of title so u have it present in the struct
    char *token = strtok_r(currline, ",", &saveptr);
    currmovie->title = calloc(strlen(token) + 1, sizeof(char));
   strcpy(currmovie->title, token);


    token = strtok_r(NULL, ",", &saveptr);
    // converting year string into an integer.
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
     11
     
 }
 /*
Name:Mary nansikombi
Description:Processes the files
How it works:Opens  a file and iterates like its running  a linked list to ensure all the different movies are put into the linked list 
checks if head is null meaning no movie or nodes yet.Then after keeps uses the tail to add new node and make the new added node the movie
then move to the next node
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


// Read the file line by line
    while ((nread = getline(&currline, &len, movieFile)) != -1)
    {
        struct movie *newNode = createmovie(currline);
        //trying to see if this is the start of the linked list to see iif it has noo noodes
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
Function thats trying to print but needs to pass in a movie object to actually print.
*/
void printmovie(struct movie* amovie){
  printf("%s, %d, %s, %.1f\n", amovie->title,
               amovie->year,
               amovie->language,
               amovie->rate);
}
/*
* Print the linked list of students
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
Function that frees the list of movies by making sure it frees the entire linked list.
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
Description:Trying to set up the format for the year file,passing in the year,title and directory
How it works:opens the file and prints the year and title to it according to the directory.
File is opened for appending.
*/
 void processyears( const char * title, int year, const char *directory){
    //consist of only nine characters.
    char filename[9];
    snprintf(filename,sizeof(filename), "%04d.txt",year,directory);
   // FILE *file = fopen(filename, O_WRONLY |O_APPEND| O_CREAT, 0600);
    FILE *file = fopen(filename, "a");
    if (file == NULL){
        perror("Trouble opening the file");
       exit(EXIT_FAILURE);
    }
    chmod(filename,S_IRUSR| S_IWUSR | S_IRGRP);
    char formattedstring[100];
    sprintf(formattedstring, " %s\n" ,title);
    fprintf(file, "%s",formattedstring);
    fclose(file);

 }
 /*
 Descriptions Processes the years within the new directory that was created
 checking if the movie object is null and then trying to iterate it to pull out the year and the title for it till all the movies are
 done from the entire file of movies.
 */
 
 void processrealyears(struct movie *list,const char *directory){
    struct movie *movieoniterate = list;
    while (movieoniterate != NULL){
        int year = movieoniterate->year;
        const char *title = movieoniterate->title;
        processyears(title,year,directory);
        movieoniterate = movieoniterate->next;
    }
 }

/*
Description of what is going on in main:
User has options to pick from,checks if the file meets the file prefixes and starts with movies and ends with.csv
Sets rand to have our newly created directories to be assigned a random number.
Opens up the directory directory were actually searching in.
Uses stat.size to see wat is the bigges file in our directory.
Searches each file in directory and returns the size of a file by comparing largest file at the moment with the fileattribute almost
like using file on check with big file atm.
Returns our biggest file,stores it in our variable by string copying and later I start thinkin about making some new directory for our large 
file selection
*/
void main() {

   
    while (1){
    int choice;
    printf(" 1.Select 1 to process.\n");
    printf("2.Exit from the program .\n");
    printf(" Enter a choice from 1 or 2: .\n");
    scanf("%d", &choice);
    
    if (choice  == 1) {
         while(1){
     int option;
        printf(" Which file would you like to process: .\n");
        printf("Enter 1 to pick the largest file.\n");
        printf("Enter 2 to pick the smallest file.\n");
        printf("Enter 3 to specify the name of a file. \n");
        printf("Enter a choice from 1 to 3. \n");
    scanf("%d", &option);
    int filenotfound = 0;
    // code adopted from lecture slides on canvas https://canvas.oregonstate.edu/courses/1942597
    if (option == 1){
    off_t largestFileSize = -1;
    //int newestDirTime = -1; // Modified timestamp of newest subdir examined
    char targetFilePrefix[32] =  "movies_"; // Prefix we're looking for
    char targetFileExtension[] = ".csv";
    char largestFileName[256]; // Holds the name of the newest dir that contains prefix
    // am storing it in a variable that way I am actually able to process it
    char largestFilepath[256];
    memset(largestFileName, '\0', sizeof(largestFileName));
    DIR* dirToCheck; // Holds the directory we're starting in
    struct dirent *fileInDir; // Holds the current file  of the starting dir
    struct stat fileAttributes; // Holds information we've gained about subdir
    dirToCheck = opendir("."); // Open up the directory this program was run in
    const char *myonidusername = "nansikom";
    srand(time(NULL));
    int randomnumber = rand () % 100000;
    char directoryname [256];
    snprintf(directoryname, sizeof(directoryname),"%s.movies.%d", myonidusername,randomnumber);
    // trying to store our current directory using cwd function
    char originalDirectory[PATH_MAX];
    if (getcwd(originalDirectory,sizeof(originalDirectory))== NULL){
        perror("Failed to get current working directory");
        exit(EXIT_FAILURE);
    }
    if (dirToCheck > 0) { // Make sure the current directory could be openedmeaning there actually is a directory
       while ((fileInDir = readdir(dirToCheck)) != NULL) { // Check each entry in dir
            if(strstr(fileInDir->d_name, targetFilePrefix )  != NULL && 
             strlen(fileInDir->d_name) >= strlen(targetFilePrefix) + strlen(targetFileExtension) &&
                 strcmp(fileInDir->d_name + strlen(fileInDir->d_name)- strlen(targetFileExtension), targetFileExtension)==0)
          
          
 { // If entry has prefix
             
             printf("Found the file: %s\n", fileInDir->d_name);
             stat(fileInDir->d_name, &fileAttributes); // Get attributes of the entry
             if (S_ISREG(fileAttributes.st_mode)) {

                if (fileAttributes.st_size > largestFileSize) { // If this time is bigger
                    largestFileSize = fileAttributes.st_size;
                    memset(largestFileName, '\0', sizeof(largestFileName));
                    strcpy(largestFileName, fileInDir->d_name);
                    
                }
            }
        }
    }
}
closedir(dirToCheck); 
printf("Largest file found is: %s\n", largestFileName);
printf("Now processing largest file: %s\n",largestFileName);



/* trying to create wat is called a directory using our mkdir function.
changing the directory and going back to our new original directory
Im passing in the directory name and the largest file so that we start to actually process them.
*/
mode_t mode = S_IRWXU | S_IXGRP| S_IRGRP;
if (mkdir(directoryname, mode)==0){
   printf("Directory '%s' created successfully\n",directoryname);
   struct movie *largestFilemovie = processFile(largestFileName);
    
    
    
    if (chdir(directoryname)==0){
        printf("Changed to directory: %s\n",directoryname);
      //  mode_t mode = S_IRWXU | S_IXGRP| S_IRGRP;
        processrealyears(largestFilemovie ,directoryname );
    }
    if (chdir(originalDirectory)== -1){
        perror("Failed to return to original directory");
        exit(EXIT_FAILURE);
    }

    printf("Returned to the original directory: %s\n", originalDirectory);

    //return 0;


}
//error handling if you fail to creat directoy
   else{
    perror("Failed to create directory \n");
   }
    
    }

/*
Description of what is going on in this function:
User has actually chosen option 2
Sets rand to have our newly created directories to be assigned a random number for our smallest file.
Opens up the directory directory were act.
Uses stat.size to see wat is the smallest  file in our directory.
Searches each file in directory and returns the size of a file by comparing smallest file at the moment with the fileattribute almost
like using file on check with big file atm.
Returns our biggest file,stores it in our variable by string copying and later I start thinkin about making some new directory
 for my small file and also processing the year for it.
*/


     else if (option == 2){
     // off_t smallestFileSize = 200000000;
      off_t smallestFileSize = LLONG_MAX;
    //int newestDirTime = -1; // Modified timestamp of newest subdir examined
    char targetFilePrefix[32] =  "movies_"; // Prefix we're looking for
    char targetFileExtension[] = ".csv";
    char smallestFileName[256]; // Holds the name of the newest dir that contains prefix
    memset(smallestFileName, '\0', sizeof(smallestFileName));
    DIR* dirToCheck; // Holds the directory we're starting in
    struct dirent *fileInDir; // Holds the current subdir of the starting dir
    struct stat fileAttributes; // Holds information we've gained about subdir
    dirToCheck = opendir("."); // Open up the directory this program was run in
   const char *myonidusername = "nansikom";
    srand(time(NULL));
    int randomnumber = rand () % 100000;
    char directoryname [256];
    snprintf(directoryname, sizeof(directoryname),"%s.movies.%d", myonidusername,randomnumber);
    
    
    char originalDirectory[PATH_MAX];
    if (getcwd(originalDirectory,sizeof(originalDirectory))== NULL){
        perror("Failed to get current working directory");
        exit(EXIT_FAILURE);
    }
    
    mode_t mode = S_IRWXU | S_IXGRP;

    if (dirToCheck > 0) { // Make sure the current directory could be opened
       while ((fileInDir = readdir(dirToCheck)) != NULL) { // Check each entry in dir
              if(strstr(fileInDir->d_name, targetFilePrefix )  != NULL && 
                strlen(fileInDir->d_name) >= strlen(targetFilePrefix) + strlen(targetFileExtension) &&
                  strcmp(fileInDir->d_name + strlen(fileInDir->d_name)- strlen(targetFileExtension), targetFileExtension)==0)
          
 { // If entry has prefix
            // printf("Found the file: %s\n", fileInDir->d_name);
             stat(fileInDir->d_name, &fileAttributes); // Get attributes of the entry
             if (S_ISREG(fileAttributes.st_mode)) {

                if (fileAttributes.st_size < smallestFileSize) { // If this time is bigger
                    smallestFileSize = fileAttributes.st_size;
                    memset(smallestFileName, '\0', sizeof(smallestFileName));
                    strcpy(smallestFileName, fileInDir->d_name);
                    //printf("Largest file: %s, size: %d\n", fileInDir->d_name, newestDirTime);
                    //printf("Smallest file: %s, size: %ld bytes\n", fileInDir->d_name, (long)smallestFileSize);

                }
            }
        }
    }
}
   
    
closedir(dirToCheck); // Close the directory we opened
//printf("Largest file found is: %s\n", largestFileName);
printf("Smallest file found is: %s\n", smallestFileName);

printf("Now processing smallest file: %s\n",smallestFileName);

if (mkdir(directoryname, mode)==0){
   printf("Directory '%s' created successfully\n",directoryname);
   struct movie *smallestFilemovie = processFile(smallestFileName);
    if (chdir(directoryname)==0){
        printf("Changed to directory: %s\n",directoryname );
        processrealyears(smallestFilemovie ,directoryname );
    }
    if (chdir(originalDirectory)== -1){
        perror("Failed to return to original directory");
        exit(EXIT_FAILURE);
    }

    printf("Returned to the original directory: %s\n", originalDirectory);

    //return 0;





}
 else {
  
    perror("failed to create directory");
    }
/*
Here user has the option to input the file they want so that
We check to see if the file they have input actually exist or if the file they put does not exist.
If it exists when seraching our directory,we process it and create  a new directory for it which actually pulls up the year file
for it and the associated titles for it.
*/
      } 
    else  if (option == 3){
        char userfile[256];
        printf("Which file would you like to process.\n");
        scanf("%s", &userfile);
        DIR* dirToCheck; 
    struct stat fileAttributes; // Holds information we've gained about subdir
    dirToCheck = opendir("."); // Open up the directory this program was run in
   const char *myonidusername = "nansikom";
    srand(time(NULL));
    int randomnumber = rand () % 100000;
    
    int found = 0;
    char originalDirectory[PATH_MAX];
    if (getcwd(originalDirectory,sizeof(originalDirectory))== NULL){
        perror("Failed to get current working directory");
        exit(EXIT_FAILURE);
    }
    
    mode_t mode = S_IRWXU | S_IXGRP;
     
    if (dirToCheck == NULL){
        perror("Failed to open the current directory");
        exit(EXIT_FAILURE);
    }

    if (dirToCheck > 0) { 
    struct dirent *fileInDir;
       while ((fileInDir = readdir(dirToCheck)) != NULL) { 

                if (strcmp(fileInDir->d_name, userfile) == 0) { 
                    
                    found = 1;
                    break;
                    //strcpy(userfile, fileInDir->d_name);
                    
                }
            }
        
closedir(dirToCheck);   
if (found) {
    const char *myonidusername = "nansikom";
    srand(time(NULL));
    int randomnumber = rand () % 100000;
    
    char directoryname [256];
    snprintf(directoryname, sizeof(directoryname),"%s.movies.%d", myonidusername,randomnumber);
    //printf("File %s found in directory\n", userfile);
    
if (mkdir(directoryname, mode)==0){
   printf("Directory '%s' created successfully\n",directoryname);
   struct movie *filepoint = processFile(userfile);
    if (chdir(directoryname)==0){
        printf("Changed to directory: %s\n",directoryname );
        processrealyears(filepoint ,directoryname );
    }
    if (chdir(originalDirectory)== -1){
        perror("Failed to return to original directory");
        exit(EXIT_FAILURE);
    }

    printf("Returned to the original directory: %s\n", originalDirectory);

    
}
   
    

 
 }
 else {
        printf(" The File %s was not found.Try again \n", userfile);
        filenotfound = 1;
    }
    }

      }
       else {
            printf("Invalid choice please choose between 1 ,2 or 3\n");
        }
     if (!filenotfound){
        break;
     }
        
    }
    }
         
     else if (choice == 2){
            printf("Your out of the program\n");
            break;
     }
     else {
            printf("Invalid choice please choose between 1 or 2\n");
        }
    }
    }



    
