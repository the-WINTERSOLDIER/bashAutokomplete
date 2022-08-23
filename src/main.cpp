#include<termios.h>
#include<unistd.h>
#include<iostream>
#include"trie.h"
#include<fstream>
#include <vector>
#include<string>

void write_string(std::string & command){

}
int main(int argc, char *argv[]){
    std::string usage="USAGE: bashAutokomplete <STR>\nbashAutokomplete command will cycle  through commands that have STR as prefix , using tab key.";
    // Validate cli args
    if (argc>2||argc<2){
        std::cout<<usage<<std::endl;
        exit(1);
    }

    trie word_list;
    std::fstream fo;
    fo.open("/home/anton/.bash_history",std::ios_base::in);
    std::string line;
    
    // Building Trie off of .bash_history
    while(getline(fo,line)){
         if(line[0]==' '){
             // skip if the first character of a command is space
            continue;
         }
         word_list.insert(line);
    }

    // Get prefix
    std::string prefix = argv[1]; 
    
    // Get list of all the suggestions
    std::vector<std::string> res= word_list.suggestions(prefix);
    
    // Variable to hold key press
    char input_char;

    // Unbuffered input logic i.e taking input without pressing enter/carrige return key
    // The termios functions describe a general terminal interface that is provided to control asynchronous communications ports. More info at  man termios
    struct termios old_settings={0};
    
    // Get current terminal settings
    if(tcgetattr(0,&old_settings)<0){
        // err handling
        perror("tcgetattr");
    }

    /* In canonical mode:
     * Input is made available line by line.  An input line is available when one of the line delimiters is typed (NL, EOL, EOL2; or EOF at the start of line).  Except in the case of EOF, the line delim‐
     *    iter is included in the buffer returned by read(2).
     */
    // Disabling Cannonical Mode
    old_settings.c_lflag &=~ICANON;
    old_settings.c_lflag &=~ECHO;
    
    /* c_cc[VMIN] > 0, c_cc[VTIME] == 0 (blocking read)
     * read(2) blocks until MIN bytes are available, and returns up to the number of bytes requested.
     */
    old_settings.c_cc[VMIN] = 1;
    old_settings.c_cc[VTIME] = 0;
    
    // enable unbuffered read settings
    if (tcsetattr(0,TCSANOW,&old_settings ) < 0){
        perror("tcsetattr");
    }
    
    auto itr = res.rbegin();
   
    // Variable for storing the final command 
    std::string final_command;

    // Escape sequence for clearing the line and moving to the start of the line 
    std::string clr_line = "\033[1K\r";

    // Output teh first Suggestion 
    write(1,(*itr).c_str(),(*itr).size()+1);
    final_command = (*itr); 
    itr++;    

    while(1){      
        if(read(0,&input_char,1) < 0){
            // read a key input or raise err
            perror("read()");
        }

        // Clear the line
        write(1,clr_line.c_str(),clr_line.size()+1);
       
        if(input_char == 9){
            // Check for Horizontal Tab presses
            
            // Cycle through vector
            if(itr == res.rend()){
                itr = res.rbegin();
                }
            
            write(1,(*itr).c_str(),(*itr).size()+1);
            final_command = (*itr); 
            itr++;    
        }
                
        else{
            break;
        }     
    }
    // Reset the settings
    old_settings.c_lflag |= ICANON;
    old_settings.c_lflag |= ECHO;
    if (tcsetattr(0, TCSADRAIN, &old_settings) < 0)
        perror ("tcsetattr ~ICANON");
    std::cout<<final_command<<std::endl;

}
