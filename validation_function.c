#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdbool.h>
#include "shop.h"

//================================
bool badFirst(char value[])
{
    int i;
    bool wrong = false;
    if(strlen(value)<1){
        printf("missing first name\n");//if there is no input
        return true;
    }
    for (i = 0; i < strlen(value) && wrong == 0; i++) {
        if(!isalpha(value[i])){
            printf("first name can't have non alpha chracrers\n");//if there is wrong characters
            wrong = true;
            }
    }
    return wrong;
}
//================================
bool badLast(char value[])
{
    int i;
    bool wrong = false;
    if(strlen(value)<1){
        printf("missing last name\n");//if there is no input
        return true;
    }
    for (i = 0; i < strlen(value) && wrong == 0; i++) {
        if(!isalpha(value[i])){
            printf("last name can't have non alpha chracrers\n");//if there is wrong characters
            wrong = true;
            }
    }
    return wrong;
}
//===================================
bool badId(char value[])
{
    int i;
    bool wrong = false;
    if(strlen(value)<1){
        printf("missing ID\n");//if there is no input
        return true;
    }
    if(strlen(value)!=9){
        printf("ID must have 9 digit\n");//if there is wrong number of characters
        wrong = true;
    }
    for (i = 0; i < strlen(value) && wrong == 0; i++) {
        if(!isdigit(value[i])){
            printf("ID can't have non digit chracrers\n");//if there is wrong characters
            wrong = true;
            }
    }
    return wrong;
}
//================================
bool badPhone(char value[])
{
    int i;
    bool wrong = false;
    if(strlen(value)<1){
        printf("missing Debt\n");//if there is no input
        return true;
    }
    for (i = 0; i < strlen(value) && wrong == 0; i++) {
        if(!isdigit(value[i])){
            printf("Phone can't have non digit chracrers\n");//if there is wrong characters
            wrong = true;
        }
    }
    return wrong;
}
//================================
bool badDebt(char value[])
{
    int i;
    bool wrong = false;
    if(strlen(value)<1){//if there is no input
        printf("missing Debt\n");
        return true;
    }
    for (i = 0; i < strlen(value) && wrong == 0; i++) {
        if(!isdigit(value[i]) && value[i] != '.' && value[i] != '-' && value[i] != '+'){
                printf("Debt can't have non digit chracrers\n");//if there is wrong characters
                wrong = true;
            }
    }
    return wrong;
}
//==============================
bool badDate(char value[])//check if date ok. we assume years between 1950 -> 2022 are right
{
   int i,leap;
   bool wrong = false;
   int daytab[][13] ={//from the ansi c book
    {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
     {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
    }; 
   unsigned int date[3];
   char t[MAX];
    if(strlen(value)<1){
        printf("missing Date\n");//if there is no input
        return true;
    }
    for (i = 0; i < strlen(value)-1 && wrong == false; i++) {
        if(!isdigit(value[i]) && value[i] != '/'){
            printf("Date can't have non digit chracrers\n");//if there is wrong characters
            wrong = true;
        }
    }
    strcpy(t,value);
    date[0]= atoi(strtok(t,"/"));
    for(i=1;i<3;i++){
        date[i]=atoi(strtok(NULL,"/"));
    }
    if(date[2]>2022 || date[2]<1950){
        printf("year not make sense\n");//right years
        wrong = true;
    }
    if(date[1]>12 || date[1]<1){
        printf("month not make sense\n");//only 12 month
        wrong = true;
    }
    leap = (((date[2]%4 == 0) && (date[2]%100 != 0)) || (date[2]%400 == 0));
    if(date[0]>daytab[leap][date[1]] || date[0]<1){//each month has different number of days
        printf("day not make sense\n");
        wrong = true;
    }
    return wrong;
}