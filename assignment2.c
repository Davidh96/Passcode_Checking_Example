/*This program gets a code entered by a user and allows the user to encrypt it and compare it to the access code, 
decrypt an encrypted code and count the amount of times a user enters in a code correctly or incorrectly
*/
//David Hunt
//09/03/2015
#include <stdio.h>
#include <stdlib.h>
#define SIZE 4

//Prototypes
void entercode(int *);
void encrypt(int *, int *, int *, int *, int *);
void decrypt(int *, int *);
void correctincorrect(int *, int *);
int checknum(int);
void endprogram(void);

main()
{
    
    int menuitem,usercode[SIZE],ecode[SIZE],dcode[SIZE],access_code[SIZE]={4,5,2,3},correct,incorrect;
    //These variables are set to zero so that the user is unable to encrypt or decrypt when the program starts
    int ecount=0,dcount=0;
    menuitem=correct=incorrect=0;
   
    //Loop the menu until the user enters 5
    while(menuitem!=5)
    {
        
        //This is to stop the program from accepting a letter as a menu option in certain circumstances
        menuitem=0;
        
        //This is the menu
        printf("\nEnter in the number corresponding to your menu choice\n");
        printf("\n1. Enter code \n2. Encrypt code and verify if correct  \n3. Decrypt code \n4. Display the number of times code was entered successfully and incorrectly\n5. Exit\n");
        scanf("%d",&menuitem);
        flushall();
        
        //This switch statement 
        switch(menuitem)
        {
            
            case 1:
            {
                
                //Call function entercode()
                entercode(usercode);
                
                //The code can now be encrypted but not decrypted
                ecount=1;
                
                break;
                
            }//end case 1
            
            case 2:
            {
                
                //If the code has already been encrypted the user is greated with this message
                if(ecount==2)
                {
                    
                    printf("\nTHE CODE IS ALREADY ENCRYPTED\n");
                    
                }//end if
                
                //If a code has been entered and not encrypted then the user can encrypt
                if(ecount==1)
                {
                    
                    //Call the encrypt() function which returns a value that either allows(c)/dissalows(i) the user to decrypt.
                    encrypt(usercode,ecode,access_code,&correct,&incorrect);
                    
                    //This tells the program that the code has been encrypted and cannot be encryped again and that the code can now be decrypted
                    ecount=2;
                    dcount=1;
                    
                }//end if
                
                //If the user has not entered a code then they are greated with this message
                if(ecount==0)
                {
                    
                    printf("\nYOU MUST ENTER A CODE IN FIRST\n");
                    
                }//end if
                
                break;
                
            }//end case 2
            
            case 3:
            {
                
                //If the code has been encrypted then the user is able to decrypt
                if(dcount==1)
                {
                    
                    //Call the function decrypt()
                    decrypt(ecode,dcode);
                    
                    //Code can now be encrypted but not decrypted
                    ecount=1;
                    dcount=0;
                    
                }//end if
                
                //If the user has not encrypted the code they get this error message
                else
                {
                    
                    printf("\nYOU MUST ENCRYPT YOUR CODE BEFORE DECRYPTING\n");
                    
                }//end else
                
                break;
                
            }//end case 3
            
            case 4:
            {
                
                //Call the function correctincorrect()
                correctincorrect(&correct,&incorrect);
                
                break;
                
            }//end case 4
            
            case 5:
            {
                
                //call the function endprogram()
                endprogram();
                
            }//end case 5
            
            default:
            {
                
                //If the user enters in an unaccepted number/charachter then they recieve this error message
                printf("\nERROR! YOU MUST ENTER A VALID MENU ITEM\n");
                
                break;
                
            }//end default
        
        }//end switch
        
    }//end while 
      
}//end main()

//entercode() gets the digits entered by a user and sends them to checknum() before adding them to usercode array
void entercode(int *usercode)
{
    
    int i,tmp;
    
    //Loops so that the user enters in 4 numbers
    for(i=0;i<SIZE;i++)
    {
        
        //This stops(in certain instances) chars to be accepted as a digit
        tmp=10;
        
        //Gets the each digit from the user
        printf("Enter in digit no.%d: ",i+1);
        scanf("%d",&tmp);
        flushall();
        
        //Sends tmp to checknum() to check if a single digit has been entered and if it is valid, if so the digit is added to the usercode array
        *(usercode+i)=checknum(tmp);
        
    }//end for
    
}//end entercode

//encrypt() encrypts an entered code
void encrypt(int *usercode, int *ecode, int *access_code,int *correct,int *incorrect)
{
    
    int i,chk=0,tmp;
    
    //Swaps the elements
    for(i=0;i<SIZE-2;i++)
    {
        
        //This will swap the 1st digit with the 3rd digit for the first loop and the 2nd digit with the 4th digit in the second loop
        tmp=*(usercode+i);
        *(ecode+i)=*(usercode+(i+2));
        *(ecode+(i+2))=tmp;
        
    }//end for
    
    for(i=0;i<SIZE;i++)
    {
        
        //Adds 1 to digits
        *(ecode+i)=*(ecode+i)+1;
        
        //If the digit becomes 10 then it becomes 0
        if(*(ecode+i)==10)
        {
            
            *(ecode+i)=0;
            
        }//end if
        
    }//end for
    
    //This loop compares the encrypted code to the access code
    for(i=0;i<SIZE;i++)
    {
        
        //If the digits are the same then add 1 to chk
        if(*(ecode+i)==*(access_code+i))
        {
            
            chk++;
            
        }//end if
        
    }//end for
    
    //If chk is 4 then the encrypted code is the same as the access_code
    if(chk==4)
    {
        
        printf("\nCORRECT CODE\n");
        
        //Records that the code was entered in correctly
        (*correct)++;
        
    }//end if
    
    //If chk is NOT equal to 4 then the wrong code was entered
    else
    {
        
        printf("\nERROR CODE\n");
        
        //Records that the code was entered in incorrectly
        (*incorrect)++;
        
    }//end else
    
}//end encrypt()

//decrypt() decrypts an encrypted code
void decrypt(int *ecode, int *dcode)
{
    
    int i,tmp;
    
    //This takes 1 from each digit
    for(i=0;i<SIZE;i++)
    {
        
        *(ecode+i)=*(ecode+i)-1; 
        
        //If the answer is  -1 then it is changed to 9
        if(*(ecode+i)==-1)
        {
            
            *(ecode+i)=9;
            
        }//end if
        
    }//end for 
    
    //This puts the number back into its original sequence
    for(i=0;i<SIZE-2;i++)
    {
        
        //Swaps the 3rd and 1st element for the first loop, then the 2nd and 4th element in the second loop
        tmp=*(ecode+i);
        *(dcode+i)=*(ecode+(i+2));
        *(dcode+(i+2))=tmp;
        
    }//end for
    
    printf("\nCODE DECRYPTED\n");
    
}//end decrypt()

//correctincorrect displays the amount of times the user enters a code that when encrypted is the same as the access code
void correctincorrect(int *correct,int *incorrect)
{
    
    printf("\n(i)The amount of times the correct access code has been entered: %d",*correct);
    printf("\n(ii)The amount of times the incorrect access code has been entered: %d\n",*incorrect);

}//end correctincorrect()

//checknum() checks each number the user enters to ensure it is only one digit
int checknum(int num)
{
    
    //If the number is above 9 or less than 0 then the user will be asked to enter a new number
    while(num>9 || num<0)
    {
        
        printf("ERROR! YOU MUST ENTER IN A SINGLE DIGIT: ");
        scanf("%d",&num);
        flushall();
        
    }//end while
    
    //Once a valid number has been entered it is returned back to entercode()
    return(num);  
    
}//end checknum()

//endprogram() ends the program
void endprogram(void)
{
    
    //Tells the user that the program is ending
    printf("The program has been ended");
    
    //Ends program
    exit(0);
    
}//end endprogram()