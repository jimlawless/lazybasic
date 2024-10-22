// Lazy BASIC
// by Jim Lawless
// License: MIT / X11
// Copyright (c) 2022 by James K. Lawless
// jimbo@radiks.net 
//
// To build, use the following GCC command:
//    gcc  lbas.c -o lbas.exe
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

char *value_of(char *);
int int_value_of(char *);
int find_variable(char *);
void error_if_null(char *,char *);

void do_print();
void do_let();
void do_if();
void do_goto();
void do_add();

int variables[26];
char *whitespace=" \t";
#define MAX_LINES (256)
int line_nbr[MAX_LINES];
char *lines[MAX_LINES];
int line_ct=0;
int line_ndx;

int main(int argc, char **argv)
{
    FILE *fp;
    char buff[256];
    char pause_buff[3];
    char *p;  
    int i;
    
    if(argc<2) {
        fprintf(stderr,"Jim L's Lazy BASIC interpreter...\n");
        fprintf(stderr,"Syntax: lbas filename\n");
        return 1;
    }
    
    if((fp=fopen(argv[1],"r"))==NULL) {
        fprintf(stderr,"Jim L's Lazy BASIC interpreter...\n");
        fprintf(stderr,"Cannot open input file %s\n",argv[1]);
        return 1;
    }
    
    while(fgets(buff,sizeof(buff)-1,fp)!=NULL) {
        p=strtok(buff,whitespace);
        if(p==NULL)
            break;
        i=atoi(p);
        if(i<=0) {
            fprintf(stderr,"Line number must be greater than zero. Found: %s\n",p);
            return 1;
        }
        
        if(line_ct > 0 ) {
            if(i <= line_nbr[line_ct-1]) {
                fprintf(stderr,"Invalid line number / line number out of sequence: %d %s\n",i,strtok(NULL,"\n"));
                exit(1);
            }
        }
        
        line_nbr[line_ct]=i;
        lines[line_ct]= strdup(strtok(NULL,"\n"));
        line_ct++;
    }
    fclose(fp);
    
    for(line_ndx=0;line_ndx<line_ct;line_ndx++) {
        strcpy(buff,lines[line_ndx]);
        p=strtok(buff,whitespace);
        if(!stricmp(p,"end"))
            break;
        else
        if(!stricmp(p,"rem"))
            continue;
        else
        if(!stricmp(p,"pause")) {
            fgets(pause_buff,sizeof(pause_buff)-1,stdin);
            continue;
        }
        else
        if(!stricmp(p,"print"))
            do_print();
        else
        if(!stricmp(p,"let"))
            do_let();
        else
        if(!stricmp(p,"if"))
            do_if();
        else
        if(!stricmp(p,"goto"))
            do_goto();
        else
        if(!stricmp(p,"add"))
            do_add();            
        else
            error_if_null(NULL,"Invalid command");
    }
    return 0;           
}
    // Return the value of an input string unless it represents a variable.
    // In the case of a variable, return the variable value. 
char *value_of(char *s) {
#define MAX_RING (4)
    static char ring[MAX_RING][12];
    static int ring_ndx=0;
    char *tmp;
    int ndx;
    ndx=find_variable(s);
    if(ndx<0)
        return s;        
    sprintf(ring[ring_ndx],"%d",variables[ndx]);
    tmp=ring[ring_ndx];
    ring_ndx=(ring_ndx+1)%MAX_RING;
    return tmp;
}
     // Return a varible value or the int value of a string
int int_value_of(char *s) {
    char b[12];
    int ndx;
    ndx=find_variable(s);
    if(ndx>=0)
        return variables[ndx];        
    return atoi(s);
}


    // Return index into variable array for specified variable or
    // -1 if not a valid variable name.
int find_variable(char *s) {
    char c;
    c=tolower(*s);
    if(strlen(s)==2) {
        if(s[1]=='%') {
            if(('a'<=c)&&('z'>=c)) {
                return c-'a';
            }
        }
    }
    return -1;
}

void error_if_null(char *p,char *msg) {
    if(p==NULL) {
        fprintf(stderr,"%s\n",msg);
        fprintf(stderr,"Line: %d\n",line_nbr[line_ndx]);
        fprintf(stderr,"%d %s\n\n",line_nbr[line_ndx],lines[line_ndx]);
        exit(1);
    }
}

void do_print() {
    int print_newline;
    char *p;
    char c;
    print_newline=1;
        // obtain the remaining string from strtok()
        // by using \n as the separator
    for(;;) {
            // obtain the remaining string from strtok()
            // by using \n as the separator
        p=strtok(NULL,"\n");

        if(p==NULL)
            break;
            // skip whitespace
        while((*p==' ')||(*p=='\t'))
            p++;
        c=*p;
        if(!c)
            break;
        if(c=='\"') 
            p=strtok(p+1,"\"");
        else
        if(c=='\'') 
            p=strtok(p+1,"'");
        else
            p=strtok(p,whitespace);
        if(p==NULL)
            break;
        if(!stricmp(p,";")) {
            print_newline=0;
            break;
        }
        printf("%s",value_of(p));
    }
    if(print_newline)
        printf("\n");
}

void do_let() {
    int v1;
    char *p=strtok(NULL,whitespace);
    error_if_null(p,"Variable name must follow LET");
    if((v1=find_variable(p))<0)
        error_if_null(NULL,"variable name must follow LET");
    p=strtok(NULL,whitespace);
    if((p==NULL)||(strcmp(p,"=")))
        error_if_null(NULL,"= must follow variable name for LET");
    p=strtok(NULL,whitespace);
    error_if_null(p,"Value must follow = for LET");
    variables[v1]=int_value_of(p);
}

void do_if() {
    int i1,i2;
    char if_op[3];
    char *p=strtok(NULL,whitespace);
    error_if_null(p,"Missing value 1 for IF");
    i1=int_value_of(p);
    p=strtok(NULL,whitespace);
    error_if_null(p,"Missing comparison operator for IF");
    if((strlen(p)>2)||((strcmp(p,"="))&&(strcmp(p,"<>"))&&(strcmp(p,">"))))
        error_if_null(NULL,"Invalid comparison operator for IF");
    strcpy(if_op,p);
    p=strtok(NULL,whitespace);
    error_if_null(p,"Missing value 2 for IF");
    i2=int_value_of(p);            
    if(!strcmp(if_op,"=")) {
        if(i1!=i2)
            line_ndx++;
    }
    else
    if(!stricmp(if_op,">")) {
        if(i1<=i2) 
            line_ndx++;
    }
    else {
        if(i1==i2) 
            line_ndx++;
    }
}

void do_goto() {
    int target;
    int j;
    char *p=strtok(NULL,whitespace);
    error_if_null(p,"Missing line number for GOTO");
    target=atoi(p);
    if(target==0)
        error_if_null(NULL,"Line number for GOTO cannot be zero or less");
    for(j=0;j<line_ct;j++) {
        if(line_nbr[j]==target)
            break;             
    }
    if(j>=line_ct) 
        error_if_null(NULL,"Line number for GOTO cannot be found");
    else
        line_ndx=j-1;
}

void do_add() {
    int v1;
    char *p=strtok(NULL,whitespace);
    error_if_null(p,"Variable name must follow ADD");
    if((v1=find_variable(p))<0) 
        error_if_null(NULL,"variable name must follow ADD");
    p=strtok(NULL,whitespace);
    error_if_null(p,"Value must follow variable for ADD");
    variables[v1]+= int_value_of(p);    
}
