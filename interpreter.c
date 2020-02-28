#include "interpreter.h"
#include "shellmemory.h"

#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include "kernel.h"


int quitProgram = 0;

void signifyError(char *f){
    printf("Error: %s not found\n", f);
}

char **tokenize(char *str)
{
    size_t num_tokens = 1;
    int flag = 0;
    for (size_t i = 0; i < strlen(str); i++)
    {
        if (flag == 0 && str[i] == ' ')
        {
            num_tokens = num_tokens + 1;
            flag = 1;
        }
        if (str[i] != ' ')
        {
            flag = 0;
        }
    }
    char **ret_arr =
        (char **)malloc(sizeof(char *) * (num_tokens + 1));

    if (ret_arr == NULL)
    {
        perror("malloc");
        return NULL;
    }
    flag = 0;
    int ignore_flag = 0;
    char *modified_str = (char *)str;
    size_t counter = 0;
    const size_t length_str = strlen(str);
    for (size_t i = 0; i < length_str; i++)
    {
        if (modified_str[i] == '\n' || modified_str[i] == '\r')
            modified_str[i] = ' ';
        if (modified_str[i] == '"')
        {
            ignore_flag = ignore_flag ^ 0x1;
        }
        if (flag == 0 && modified_str[i] != ' ')
        {
            ret_arr[counter] = &(modified_str[i]);
            counter = counter + 1;
            flag = 1;
        }
        if (modified_str[i] == '\\' && modified_str[i + 1] == ' ')
        {
            i++;
            continue;
        }
        if (flag == 1 && modified_str[i] == ' ' && ignore_flag == 0)
        {
            modified_str[i] = '\0';
            flag = 0;
            continue;
        }
    }
    ret_arr[counter] = NULL;

    for (size_t i = 0; i < counter; ++i)
    {
        if (ret_arr[i][0] == '\"' &&
            ret_arr[i][strlen(ret_arr[i] - 1)] == '\"')
        {
            ret_arr[i][strlen(ret_arr[i]) - 1] = '\0';
            ret_arr[i] = ret_arr[i] + 1;
        }
    }

    return ret_arr;
}

int in_file_flag = 0;

int interpret(char *raw_input);

int help()
{
    printf(""
           "COMMAND         DESCRIPTION\n"
           "help            Displays all the commands\n"
           "quit            Exits / terminates the shell with \"Bye!\"\n"
           "set VAR STRING  Assigns a value to shell memory\n"
           "print VAR       Displays the STRING assigned to VAR\n"
           "run SCRIPT.TXT  Executes the file SCRIPT.TXT\n");
    return 0;
}

int quit()
{
    printf("Bye!\n");
    if (quitProgram && in_file_flag == 0)
    {
        shell_memory_destory();
        exit(0);
    }
    else{
        quitProgram = 1;
    }

    return 0;
}

int runScript(const char *path)
{
    quitProgram = 1 ;
    FILE *file = fopen(path, "r");
//    if (file == NULL)
//    {
//        printf("Script not found.\n");
//        return 1;
//    }
//    int enter_flag_status = in_file_flag;
//    in_file_flag = 1;
//
//    while (!feof(file))
//    {
//        char *line = NULL;
//        size_t linecap = 0;
//        getline(&line, &linecap, file);
//
//        int status = interpret(line);
//        free(line);
//        if (status != 0)
//        {
//            break;
//            return status;
//        }
//    }
//    fclose(file);
//    in_file_flag = enter_flag_status;
////    in_file_flag = 0;
//    return 0;
    int errCode = 0;
    char line[1000]={0};
    if (file == NULL)
    {
        printf("Script not found.\n");
        return 1;
    }
    int enter_flag_status = in_file_flag;
    in_file_flag = 1;

    if (file != NULL) {
        while (fgets(line, 500, file) && errCode == 0) {
            errCode = interpret(line);
            memset(line, '\0', 999);
        }
    }
    in_file_flag = enter_flag_status;
//    in_file_flag = 0;
    return errCode;

}

int set(const char *key, const char *value)
{
    int status = shell_memory_set(key, value);
    if (status != 0)
        printf("set: Unable to set shell memory.\n");
    return status;
}

int print(const char *key)
{
    const char *value = shell_memory_get(key);
    if (value == NULL)
    {
        printf("print: Undefined value.\n");
        return 1;
    }
    printf("%s\n", value);
    return 0;
}
int exec(char *file1, char *file2, char *file3){
    FILE *p1, *p2, *p3;
    int result;

   if(file2 !=NULL){
       if (strcmp(file1, file2) == 0) {
       printf("Error: %s already loaded\n", file1);
       return 1;
       }
       else{
           if(file3 !=NULL){
               if (strcmp(file1, file3) == 0 || strcmp(file2, file3) == 0){
                   printf("Error: %s already loaded\n", file3);
                   return 1;
               }
               else{
                   p1 = fopen(file1,"rt");
                   p2 = fopen(file2, "rt");
                   p3 = fopen(file3, "rt");
                   if(p1==NULL) {
                       signifyError(file1);
                       return 1;
                   }
                   if(p2==NULL){
                       signifyError(file2);
                       return 1;
                   }
                   if(p3 ==NULL){
                       signifyError(file3);
                       return 1;
                   }
                   result = myInit(p1);
                   result =myInit(p2);
                   result =myInit(p3);
//                   if(result == 0){
                       scheduler();
//                   }
//                   printf("3 files loaded\n");
                   return 0;

               }
           }
           else{
               p1 = fopen(file1,"rt");
               p2 = fopen(file2, "rt");
               if(p1==NULL) {
                   signifyError(file1);
                   return 1;
               }
               if(p2==NULL){
                   signifyError(file2);
                   return 1;
               }
                result = myInit(p1);
                result = myInit(p2);
//               if(result == 0){
                   scheduler();
//               }
//               printf("2 files loaded\n");
               return 0;
           }

       }
    }
   else {
       p1 = fopen(file1,"rt");
       if(p1==NULL) {
           signifyError(file1);
           return 1;
       }
       result = myInit(p1);
//       if (result != 0){
//           return 1;
//       }
//       if(result == 0){
           scheduler();
//       }
//       printf(" 1 file loaded\n");
       return 0;
   }
}

int interpret(char *raw_input)
{
    char **tokens = tokenize(raw_input);

    if (tokens[0] == NULL)
        return 0; // empty command

    if (strcmp(tokens[0], "help") == 0)
    {
        if (tokens[1] != NULL)
        {
            printf("help: Malformed command\n");
            free(tokens);
            return 1;
        }
        free(tokens);
        return help();
    }

    if (strcmp(tokens[0], "quit") == 0)
    {
        if (tokens[1] != NULL)
        {
            printf("quit: Malformed command\n");
            free(tokens);
            return 1;
        }
        if (in_file_flag == 0) {
            free(raw_input);
        }
        free(tokens);
        return quit();
    };

    if (strcmp(tokens[0], "set") == 0)
    {
//        if (!(tokens[1] != NULL && tokens[2] != NULL && tokens[3] == NULL))
        if (!(tokens[1] != NULL && tokens[2] != NULL))
        {
            printf("set: Malformed command\n");
            free(tokens);
            return 1;
        }
        int status = set(tokens[1], tokens[2]);
        free(tokens);
        return status;
    }

    if (strcmp(tokens[0], "print") == 0)
    {
        if (!(tokens[1] != NULL && tokens[2] == NULL))
        {
            printf("print: Malformed command\n");
            free(tokens);
            return 1;
        }
        int status = print(tokens[1]);
        free(tokens);
        return status;
    }

    if (strcmp(tokens[0], "run") == 0)
    {
        if (!(tokens[1] != NULL && tokens[2] == NULL))
        {
            printf("run: Malformed command\n");
            free(tokens);
        }
        int result = runScript(tokens[1]);
        free(tokens);
        return result;
    }
    if (strcmp(tokens[0], "exec")==0){
        if(!(tokens[1] != NULL)){
            printf("exec: Malformed command\n");
            free(tokens);
            return 1;
        }
        int result = exec(tokens[1],tokens[2],tokens[3]);
        free(tokens);
        return result;
    }

    printf("Unrecognized command \"%s\"\n", tokens[0]);
    free(tokens);
    return 1;

}
