 void printString(char* chars);
 void readString(char* chars);
 void readSector(char* buffer, int sector);
 void handleInterrupt21(int ax, int bx, int cx, int dx);


//=======================================================================================================================================//
 int main()
{
	//task 2
	// char line[80];
	// printString("Enter a line: \0");
	// readString(line);
	// printString(line);

	// //task 3
	// char buffer[512];
	// readSector(buffer, 30);
	// printString(buffer);

// 	//task4
// 	makeInterrupt21();
// 	interrupt(0x21,0,0,0,0);

//task5
	char line[80];
	makeInterrupt21();
	interrupt(0x21,1,line,0,0);
	interrupt(0x21,0,line,0,0);
	return 0;
 }

//======================================================================================================================================//



// void printString(char line[80])
// {
// 	int n  = sizeof(line) / sizeof(int);
	
// 	int others=0xB800;
// 	int a =0x8000;
// 	for ( i = 0; i < n; i++ )
// 	 {
//         putInMemory(0xB000, a, line[i]);
//         a++;
//         putInMemory(0xB000, a, 0x7);
//         a++;
//         if (line[i]=="0xd")
//         {
//         	others = 
//         }

//      }

// }
//============================================================================================================================================//

void printString(char * chars){

  int i=0;
  while(chars[i] != '\0')
  {

      interrupt(0x10, 0xE*256+chars[i], 0, 0, 0);
      i++;   
  }

 }

 //===========================================================================================================================================//


  // void readString(char* chars)
  // {
  // 	char x = interrupt(0x16, 0xE*256+0.0, 0, 0, 0);
  // 	int i = 0;
  // 	while(chars[i] != 0xd)
  // 	{

  // 		 chars[i]=x;
  // 		 interrupt(0x10,0xE*256+chars[i],0x0,0x0,0x0);
  //         x = interrupt(0x16, 0xE*256+0.0, 0, 0, 0);
  //         i++; 

  //         if(chars[i]==0xd)
  //         {
  //         	chars[i]==
  //         }

  // 	}

  // }


//=========================================================================================================================================//
  
 void readString(char* arr){ 
    char endLine = 0xa; 
    char endString = 0x0; 
    char back = 0x8; 

    // while loop set up 
    int i = 0; 
    char x = interrupt(0x16, 0, 0, 0, 0);
    interrupt(0x10, 0xe*256+x, 0, 0, 0);

    // exit key: enter
    while(x!=0xd){ 

        // decrements i (up to 0) if a backspace is entered, otherwise increments i
        // deals with what is in the char array         
        if(x==back&&i>0) 
        	i--;
        else 
        {
        	if(x==back)
        	 i=0;
        
        else {
        	arr[i]=x; 
        	i++;
        }   
        }
        // get next input letter and write it to screen 
        x = interrupt(0x16, 0, 0, 0, 0); 
        interrupt(0x10, 0xe*256+x, 0, 0, 0);

        // clear the display when backspace is clicked 
        if(x==back){
            interrupt(0x10, 0xe*256+endString, 0, 0, 0);
            interrupt(0x10, 0xe*256+x, 0, 0, 0);
        }
    }
      arr[i] = endLine; 
   	  arr[i+1] = endString; 
    // Writes a new line character to the screen 
    interrupt(0x10, 0xe*256+endLine, 0, 0, 0); 
}


//=========================================================================================================================================//
 void readSector(char* buffer, int sector){ 
    int ax = 2 * 256 + 1; 

    int bx = buffer; // address where the data should be stored to 

    int ch = sector/36; //0 // track number 
    int cl = mod(sector,18)+1;  //13; // relative sector number 
    int cx = ch * 256 + cl;    

    int dh = mod(sector/18,2); //1; // head number
    int dl = 0; // device number; 0=floppy
    int dx = dh * 256 + dl; 

    //printString(bx);

    interrupt(0x13, ax, bx, cx, dx); 
    //printString((char)buffer);
}


int mod(int a, int b){ 
        while(a>=b)
            a=a-b;
        return a; 
    }

//=======================================================================================================================================//

void handleInterrupt21(int ax, int bx, int cx, int dx){


	if(ax==0) {
            // bx = String 
            printString(bx); 
        } else if(ax==1) {
            // bx = buffer to hold read string 
            readString(bx);
        } else if(ax==2) {
            // bx = buffer to hold read string
            // cx = sector number
            readSector(bx,cx); 
        }  else if(ax==3) {
            printString("Invalid use of Int 21\0"); 
        }

}