#include <stdio.h> 
#include <dirent.h> 

int main(void) 
{ 
	struct dirent *direntry; // Pointer for directory entry 

	// opendir() returns a pointer of DIR type. 
	DIR *dir = opendir("."); // replace "." with a directory path to list files in the given directory ["." is used for current directory]

	if (dir == NULL) // opendir returns NULL if couldn't open directory 
		printf("Could not open current directory" );
    else{
        printf("Regular files are :\n");
        while ((direntry = readdir(dir)) != NULL){
            if(direntry->d_type == DT_REG)
                printf("%s\n", direntry->d_name);
        } 		     
    } 
	closedir(dir);    
    dir = opendir("."); 

	if (dir == NULL) // opendir returns NULL if couldn't open directory 
		printf("Could not open current directory" );
    else{
        printf("Files starting with S are :\n");
        while ((direntry = readdir(dir)) != NULL){
            if(direntry->d_name[0] == 'S')
                printf("%s\n", direntry->d_name);
        } 		     
    } 
	closedir(dir);	 
	return 0; 
} 
