/*
 * Assuming capital letters to be non-terminals and
 * Small letter to be terminals
 * # to be epsilon
 */

#include <stdio.h>
#include <string.h>

char terminals[20];
char nonTerminals[20];
char epsilons[20];
char productions[20][20];
int terminalCount;
int nonTerminalCount;
int productionCount;

char calculatingFirstFor;

void print() {
    int i;
    printf("----PRODUCTIONS----\n");
    for( i = 0; i < productionCount; i++) {
        printf("%s\n", productions[i]);
    }
    
    printf("----TERMINALS----\n");
    for( i = 0; i < terminalCount; i++) {
        printf("%c\n", terminals[i]);
    }
    
    printf("----NON-TERMINALS----\n");
    for( i = 0; i < nonTerminalCount; i++) {
        printf("%c\n", nonTerminals[i]);
    }
}

int isTerminal(char c) {
    int i;
    for( i = 0; i < terminalCount; i++) {
        if(c == terminals[i])
            return 1;
    }
    return 0;
}

void first(char c) {
    if(isTerminal(c)){
        printf("%c\n", c);
    }
    
    int i, j;
    for( i = 0; i < productionCount; i++){
        if( c == productions[i][0] ) {
            for(j = 3; j < strlen(productions[i]); j++) {
                
                /*
                 * First charcter in the production
                 * or charcter after |
                 */
                if(j == 3 || productions[i][j-1] == '|') {
                    //Khud ka epsilon
                    if(productions[i][j] == '#'){
                        if(c == calculatingFirstFor){
                        printf("%c\n", productions[i][j]);}
                    }
                    
                    if(isTerminal(productions[i][j]) == 1) {
                        printf("%c\n", productions[i][j]);    
                    } else {
                        //Non-terminals
                        first(productions[i][j]);
                        int k;
                        for(k = 0; k < productionCount; k++) {
                            if((productions[k][0] == productions[i][j]) && epsilons[k] == '#'){
                                if((j+1) < strlen(productions[i]) && productions[i][j+1] != '|'){
                                    first(productions[i][j+1]);
                                }
                                else{
                                    printf("#\n");
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

void follow(char c) {
    if(c == 'S'{
        //For the start symbol
        printf("$\n");
        return;
    }
    
    int i, j;
    for(i = 0; i < productionCount; i++) {
        for(j = 3; j < strlen(productions[i]); j++) {
            if(productions[i][j] == c){
                if((j+1) != strlen(productions[i]) && productions[i][j+1] != '|') {
                    first(productions[i][j+1]);
                } else {
                    first(productions[i][0]);
                }
            } 
        }
    }
}

int main() {
     
    int i, j;
    printf("Enter the number of productions\n");
    scanf("%d", &productionCount);
    printf("Enter the productions\n");
    
    //Reading the productions and calculating terminals and non-terminals
    for( i = 0; i < productionCount; i++) {
        scanf("%s", productions[i]);
        nonTerminals[nonTerminalCount++] = productions[i][0];
        for(j = 3; j < strlen(productions[i]); j++) {
            if(productions[i][j] >= 'a' && productions[i][j] <= 'z') {
                terminals[terminalCount++] = productions[i][j];
            }
            if(productions[i][j] == '#') {
                //i-th production has epsilon
                epsilons[i] = '#';
            }
        }
    }    
    
    
    for(i = 0; i < productionCount; i++) {
        calculatingFirstFor = nonTerminals[i];
        printf("------ FIRST OF %c ------\n", nonTerminals[i]);
        first(nonTerminals[i]);
        printf("------ FOLLOW OF %c ------\n", nonTerminals[i]);
        follow(nonTerminals[i]);
    }
    return 0;
}
/*
S->Bb|Cd                                                                                                                                                                        
B->aB|#                                                                                                                                                                         
C->cC|#    
*/
