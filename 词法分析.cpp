#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <iostream>
//#include <string>


using namespace std;
#define bufferlengh 4095
#define halflength 2047
#define tokenlength 100
#define keywordsnum 32
#define tablelength 150


FILE *file=NULL,*output=NULL,*error_file=NULL;

//统计量 
int NumSpace,NumKeyword,NumRow,NumAriOprt,NumLogOprt,NumError;


int state;
char C;
int iskey;
//string token;
char token[tokenlength];
//int lexemebegin;
int tokenptr;
int tableptr;
int forward;
char buffer[bufferlengh];

char table[tablelength][30];
char keywords[keywordsnum][15]={
"auto","break","case","char","const","continue","default","do"
,"double","else","enum","extern","float","for","goto","if","int","long",
"register","return","short","signed","sizeof","fstatic","struct","switch",
"typedef","union","unsigned","void","volatile","while"};

void initial()
{   state=0;
    NumSpace=0;NumKeyword=0;NumRow=0;NumAriOprt=0;NumLogOprt=0;NumError=0;
	forward=0;tokenptr=0;tableptr=0;
}
//填充缓冲区
void fillbuffer(int p)
{   int i;
	for(i=0;i<=halflength&&!feof(file);i++)
		buffer[p+i]=fgetc(file);
	if(feof(file)) buffer[p+i]='\0';
}

void get_char()
{ 	C=buffer[forward];
	if(forward==halflength){
		fillbuffer(halflength+1);
		forward++;
	}
	else if(forward==bufferlengh){
		fillbuffer(0);
		forward=0;
	}
	else forward++;  
	
}

void get_nbc()
{  while(1)
	 {if(C==' '||C=='\n'||C=='	'){
	 	 if(C=='\n')
	 	  NumRow++;
		  
		 get_char();
		// forward--;
		 
	  }
	  else
	   break;	 
	 }	
}

void cat()
{   token[tokenptr++]=C;
}

bool letter() //判断字符C是否为字母
{   return ((C>='a'&&C<='z')||(C>='A'&&C<='Z'));
}

bool digit() //判断字符C是否为数字
{  return (C>='0'&&C<='9');
}

void retract() //缓冲区指针回退
{   if(forward==0)
		forward=bufferlengh;
	else
		forward--;
}

int reserve()
{   int i;
	for(i=0;i<keywordsnum;i++)
	   if(strcmp(token,keywords[i])==0)
		  return i;
	if(i==keywordsnum)
	    return -1;	
}

int table_insert()
{   strcpy(table[tableptr],token);
	return tableptr++;
}

void error()
{  printf("error:illegal character\n");
}


typedef struct{
	string id;
	string type; 
	//string s;
}idInfo;

void my_return(idInfo temp)
{
	//输出控制台 和文件
	printf("< %s , %s >\n",temp.id.c_str(),temp.type.c_str()); 
}

int main()
{   char filename[30];
	printf("Please input the filename(e.g. test1.cpp)：\n");
	scanf("%s",filename);
	file=fopen(filename,"r");
	
	while(output==NULL)
		output=fopen("output.txt","w");
	while(error_file==NULL)
		error_file=fopen("error_file.txt","w");
	while(file==NULL){
		printf("The file don't exist,please input again：\n");
		scanf("%s",filename);
		file=fopen(filename,"r");
	}
	printf("\nThe result of Lexical analyze:\n");
	initial();
	fillbuffer(0);
	get_nbc();

    idInfo temp;
    
    do{       
        switch (state)
        {
            case 0:
                memset(token,0,100);//token='';
                tokenptr=0;
                get_char();
                get_nbc();

                
                switch (C)
                {
                    case 'a': case 'b': case 'c': case 'd': case 'e':
                    case 'f': case 'g': case 'h': case 'i': case 'j':
                    case 'k': case 'l': case 'm': case 'n': case 'o':
                    case 'p': case 'q': case 'r': case 's': case 't':
                    case 'u': case 'v': case 'w': case 'x': case 'y':
                    case 'z':
			        case 'A': case 'B': case 'C': case 'D': case 'E':
                    case 'F': case 'G': case 'H': case 'I': case 'J':
                    case 'K': case 'L': case 'M': case 'N': case 'O':
                    case 'P': case 'Q': case 'R': case 'S': case 'T':
                    case 'U': case 'V': case 'W': case 'X': case 'Y':
                    case 'Z':
                              state=1;break;// 
                    
                    case '0': case '1': case '2': case '3': case '4': 
                    case '5': case '6': case '7': case '8': case '9':
                              state=2;break;//
                    
                    case '<': 
                              state=8;
                              break;
                    case '>':
                              state=9;
                              break;
                    case '=':
                              state=10;
                              break;
                    case '+': 
                              state=11;
                              break;
                    case '-': 
                              state=12;
                              break;
                    case '/': 
                              state=13;
                              break;
                    case '|': 
                              state=17;
                              break;
                    case '&': 
                              state=18;
                              break;
                    case '!':
                              state=19;
                              break;
                    case '#': 
                              state=20;
                              break;
                    case '*':
                              state=21;
                              break;
                    case ':':
                              state=22;
                              break;
                    case '%': 
                              state=0;
                              temp.id ="%";
                              temp.type="-";
                              my_return(temp);
                              break;
                    case ',':
                              state=0;
                              temp.id=',';
                              temp.type='-';
                              my_return(temp);
                              break;
                    case ';':
                              state=0;
                              temp.id=';';
                              temp.type='-';
                               my_return(temp);
                              break;
                    
                    case '(':
                              state=0;temp.id='(';temp.type='-';my_return(temp);break;
                    case ')':
                              state=0;temp.id=')';temp.type='-';my_return(temp);break;                    
                    case '{':
                              state=0;temp.id='{';temp.type='-';my_return(temp);break;         
                    case '}':
                              state=0;temp.id='}';temp.type='-';my_return(temp);break;          
                    case '[':
                              state=0;temp.id='[';temp.type='-';my_return(temp);break;
                    case ']':
                              state=0;temp.id=']';temp.type='-';my_return(temp);break;
                    case '"':
                              state=0;temp.id='"';temp.type='-';my_return(temp);break;
                    case '\'':
                              state=0;temp.id='\'';temp.type='-';my_return(temp);break; 
                    case '.':
                              state=0;temp.id='.';temp.type='_';my_return(temp);break;     
                    case '\n':
                              state=0;temp.id='\n';temp.type='-';my_return(temp);break;    

                    default:
                              state=23;break;
                }
            
                break;

            case 1:
                    cat();
                    get_char();
                    if( letter() || digit() )                      
					    state=1;
                    else
                    {  retract();
                       state=0;
                       iskey=reserve();
                       if(iskey!=-1)
                         { string str(keywords[iskey]);
						   //temp.id=str;
						   temp.id=str;//strcpy(temp.id,keywords[iskey].);
                           temp.type="-";
                           my_return(temp);
                         }
                        else
                        { int identry=table_insert();
                          temp.id="ID";
                          
                          string st(table[identry]);
                          temp.type=st;
                         // printf("***%s***\n",st.c_str());
                          my_return(temp);
                        }

                    }
                    break;
            
            case 2:
                    cat();
                    get_char();
                    
                    switch (C)
                    {
                        case '0': case '1': case '2': case '3': case '4': 
                        case '5': case '6': case '7': case '8': case '9':
                                  state=2;break;
                                   
                        case '.':
                                  state=3;break;

                        case 'E':
                                  state=5;break;                      
                    
                        default:
                                  retract();
                                  state=0;
                                  temp.id="NUM";
                                  temp.type=token;//字符串转数字  SToI
                                  my_return(temp);                                
                                  break;
                    }
                    break;
            
            case 3:
                    cat();
                    get_char();
                    if( digit())
                     state=4;
                    else{
                        error();
                        state=0;
                    }
                    break;
            
            case 4:
                    cat();
                    get_char();
                    
                    switch (C)
                    {
                        case '0': case '1': case '2': case '3': case '4': 
                        case '5': case '6': case '7': case '8': case '9':
                                  state=4;break;
                                 
                        case 'E':
                                 state=5;break;
                        default:
                                 retract();
                                 state=0;
                                 temp.id="NUM";
                                 temp.type=token;//字符串转浮点数 SToF
                                 my_return(temp);
                            break;               
                    }
                    break;
            
            case 5:
                    cat();
                    get_char();
                    
                    switch (C)
                    {
                        case '0': case '1': case '2': case '3': case '4': 
                        case '5': case '6': case '7': case '8': case '9':
                                  state=7;break;
                                 
                        case '+':case '-':
                                 state=6;break;
                        default:
                                 retract();
                                 error();
                                 state=0;
                                 break;               
                    }
                    break;

            case 6:
                   cat();
                   get_char();
                   if( digit() ) state=7;
                   else{
                       retract();
                       error();
                       state=0;
                   }
                   break;

            case 7:
                   cat();
                   get_char();
                   if( digit() ) state=7;
                   else{
                       retract();
                       state=0;
                       temp.id="NUM";
                       temp.type=token; //字符串转浮点数 SToF
                   }
                   break;
            
            case 8:
                  cat();
                  get_char();
                  
                  switch (C)
                  {
                      case '=':
                          cat();
                          state=0;
                          temp.id="relop";
                          temp.type="LE";
                          my_return(temp);
                          break;
                      case '>':
                          cat();
                          state=0;
                          temp.id="relop";
                          temp.type="NE";
                          my_return(temp);
                          break;                  
                      default:
                          retract();
                          state=0;
                          temp.id="relop";
                          temp.type="LT";
                          my_return(temp);
                          break;
                  }
                  break;
            
            case 9://'>'
                   cat();
                   get_char();
                   if(C=='='){
                       cat();
                       state=0;
                       temp.id="relop";
                       temp.type="GE";
                       my_return(temp);
                   }
                   else{
                       retract();
                       state=0;
                       temp.id="relop"; temp.type="-";
                       my_return(temp);
                   }
                   break;
            
            case 10://'='
                   // cat();
                    get_char();
                    if(C=='='){
                        cat();
                        state=0;
                        temp.id="==";temp.type="-";
                        my_return(temp);
                    }
                    else{
                        retract();
                        state=0;
                        temp.id="relop";temp.type="EQ";
                        my_return(temp);
                    }
                    break;

            case 11://'+'
                    cat();
                    get_char();
                    if(C=='+'){
                        cat();
                        state=0;
                        temp.id="++";temp.type="-";
                        my_return(temp);
                    }
                    else if(C=='='){
                        cat();
                        state=0;
                        temp.id="+=";temp.type="-";
                        my_return(temp);
                    }
                    else{
                        retract();
                        state=0;
                        temp.id="+";temp.type="-";
                        my_return(temp);
                    }
                    break;
            
            case 12://'-'
                    cat();
                    get_char();
                    if(C=='-'){
                        cat();
                        state=0;
                        temp.id="--";temp.type="-";
                        my_return(temp);
                    }
                    else if(C=='='){
                        cat();
                        state=0;
                        temp.id="-=";temp.type="-";
                        my_return(temp);
                    }
                    else{
                        retract();
                        state=0;
                        temp.id="-";temp.type="-";
                        my_return(temp);
                    }
                    break;
            case 13://'/'
                    cat();
                    get_char();
                    if(C=='*') state=14;
                    else if(C=='/') state=16;
                    else if(C=='='){
                        state=0;
                        temp.id="/=";temp.type="-";
                        my_return(temp);
                    }
                    else{
                        state=0;
                        temp.id="/";temp.type="-";
                        my_return(temp);
                    }
                    break;
            
            case 14://'/*'
                    cat();
                    get_char();
                    if(C=='*') state=15;
                    else{
                        state=14;
                    }
                    break;
            
            case 15://'*/'
                   cat();
                   get_char();
                   if(C=='/') state=0;
                   else state=14;
                   break;
            
            case 16:// '//'
                   cat();
                   if(C=='\n') state=0;
                   else state=16;
                   break;
            
            case 17:// '|'
                  cat();
                  get_char();
                  if(C=='|'){
                      cat();
                      state=0;
                      temp.id="||";temp.type="-";
                      my_return(temp);
                  }
                  else{
                      state=0;
                  }
                  break;
            
            case 18: // '&'
                  cat();
                  get_char();
                  if(C=='&'){
                      cat();
                      state=0;
                      temp.id="&&";temp.type="-";
                      my_return(temp);
                  }
                  else{
                      state=0;
                  }
                  break;

            case 19: // '!'
                  cat();
                  get_char();
                  if(C=='='){
                      cat();
                      state=0;
                      temp.id="!=";temp.type="NE";
                      my_return(temp);
                  }
                  else{
                  	  retract();                 	  
                      state=0;
                      temp.id="!";temp.type="-";
                      my_return(temp);
                  }
                  break;

            case 20://  '#'
                  //cat();
                  
                  get_char();
			      while(C!='\n')
				      get_char();
				  temp.id="#";
				  temp.type="header";
                  my_return(temp);
			     // retract();
                  state=0;
                  break;
            case 21:// '*'
                  cat();
                  get_char();
                  if(C=='='){
                      cat();
                      state=0;
                      temp.id="*=";temp.type="-";
                      my_return(temp);
                  }
                  else{
                      state=0;
                      temp.id="*";temp.type="-";
                      my_return(temp);
                  }
                  break;

            case 22:// ':'
                cat();
                get_char();
                if(C=='='){
                    cat();
                    state=0;
                    temp.id="assign-op";temp.type="-";
                    my_return(temp);
                }
                else{
                    state=0;
                }
                break;


            case 23:// 'other'
                error();
                state=0;
                break;
            }
          /* string ss(token);
          printf("^^^%s^^^\n",ss.c_str());*/
          

    }while(C!=EOF);
}


