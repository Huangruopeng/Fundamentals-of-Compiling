#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <windows.h>

using namespace std;


typedef struct{
	string id;
	string type; 
}idInfo;

int main()
{   idInfo temp;
    do{
        
        switch (state)
        {
            case 0:
                token="";
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
                              state=1;break;//设置标识符状态 
                    
                    case '0': case '1': case '2': case '3': case '4': 
                    case '5': case '6': case '7': case '8': case '9':
                              state=2;break;//设置常数状态
                    
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
                              state=23;
                              break;
                    case '%': 
                              state=0;
                              temp.id='%';
                              temp.type='-';
                              return temp；
                              break;
                    case ',':
                              state=0;
                              temp.id=',';
                              temp.type='-';
                              return temp;
                              break;
                    case ';':
                              state=0;
                              temp.id=';';
                              temp.type='-';
                              return temp;
                              break;
                    case ':':
                              state=0;temp.id=':';temp.type='-';return temp;break;
                    case '(':
                              state=0;temp.id='(';temp.type='-';return temp;break;
                    case ')':
                              state=0;temp.id=')';temp.type='-';return temp;break;                    
                    case '{':
                              state=0;temp.id='{';temp.type='-';return temp;break;         
                    case '}':
                              state=0;temp.id='}';temp.type='-';return temp;break;          
                    case '[':
                              state=0;temp.id='[';temp.type='-';return temp;break;
                    case ']':
                              state=0;temp.id=']';temp.type='-';return temp;break;
                    case '"':
                              state=0;temp.id='"';temp.type='-';return temp;break;
                    case '\'':
                              state=0;temp.id='\'';temp.type='-';return temp;break; 
                    case '.':
                              state=0;temp.id='.';temp.type='_';return temp;break;     
                    case '\n':
                              state=0;temp.id='\n';temp.type='-';return temp;break;    

                    default:
                              state=24;break;
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
                         {temp.id='iskey';
                          temp.type='-';
                          return temp;
                         }
                        else
                        { identry=table_insert();
                          temp.id='ID';
                          temp.type='identry';
                          return temp;
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

                        case "E":
                                  state=5;break;                      
                    
                        default:
                                  retract();
                                  state=0;
                                  temp.id='NUM';
                                  temp.type=token;//字符串转数字  SToI
                                  return temp;                                
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
                                 temp.id='NUM';
                                 temp.type=token;//字符串转浮点数 SToF
                                 return temp;
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
                       temp.id='NUM';
                       temp.type=token; //字符串转浮点数 SToF
                   }
                   break;
            
            case 8:
                    

                   
        

            default:
                break;
        }

    }
}