 void printString(char* chars);
 void readString(char* chars);
 void readSector(char* buffer, int sector);
 void handleInterrupt21(int ax, int bx, int cx, int dx);
 void readfile(char* fileName , char* buffer);
 void executeProgram(char* name, int segment);
 void terminate();
 void deleteFile(char* name);
 void writeSector(char*buffer, int sector);
 int mod(int a, int b);
 void writeFile(char* name, char* buffer, int secNum);
//=======================================================================================================================================//
 int main()
{
char buffer[13312];
makeInterrupt21();
interrupt(0x21, 7, "messag\0", 0, 0); //delete messag
interrupt(0x21, 3, "messag\0", buffer, 0); // try to read messag
interrupt(0x21, 0, buffer, 0, 0); //print out the contents of buffer
while(1);


  
 }

//============================================================================================================================================//

void printString(char * chars){

  int i=0;
  while(chars[i] != '\0')
  {

      interrupt(0x10, 0xE*256+chars[i], 0, 0, 0);
      i++;   
  }

 }


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


	switch(ax) {
            // bx = String 
        case 0:printString(bx); break;
        case 1:readString(bx); break; // bx = buffer to hold read string 
        case 2:readSector(bx,cx); break;  // bx = buffer to hold read string  // cx = sector number
        case 3:readfile(bx,cx); break; 
        case 4:executeProgram(bx,cx);  break; 
        case 5: terminate();break;   
        case 6: writeSector(bx,cx);break;
        case 7: deleteFile(bx); break;
        case 8: writeFile(bx,cx,dx); break;  
        // default: printString(" error!\0");     

}
}
//==========================================================================================================================================//
void readfile(char* fileName , char* buffer){
  int i;
  int j;
  int x;
  int m;
  int a=0;
  int found;
  int address=0;
  int Sec[26];
  char dir [512];
  readSector(dir,2);
  for(i = 0 ; i<16 ; i++){
            if(dir[i*32]!=0x0){
              for(j=0;j<6;j++){
                if(dir[j+32*i]==fileName[j]){
                  found = 1;
                }
                else{
                  found=0;
                  break;
                }

              }
            }

  if(found==1){
    x=i*32+6;
    for(m=0;m<26;m++){
      Sec[m]=dir[m+x];
    }
    while(Sec[a]!=0x0)
    {
      readSector(buffer+address,Sec[a]);
      a++;
      address+=512;
    }


  }

}

      }


//===========================================================================================================================================//
 void executeProgram(char* name, int segment){
  int i ;
  char buffer [13312];
  readfile(name,buffer);
  for(i=0 ; i<13312 ; i++){
    putInMemory(segment,i,buffer[i]);
  }
  launchProgram(segment);
 }
//=========================================================================================================================================//
 void terminate(){
  interrupt(0x21,4,"shell\0",0x2000,0); 
 }
//=========================================================================================================================================//
 void writeSector(char*buffer, int sector){
  int a=(mod(sector,18))+1;
  int b=mod((sector,18)/2);
  int c= sector/36;
  interrupt(0x13,3*256+1,buffer,c*256+a,b*256);
}
// //=========================================================================================================================
void deleteFile(char* name){
  //char array[];
  int i = 0;
  int found = 0;
  char buffer[512]; //to load directory
  int k = 0 ;
  int address=0;
  char map[512];
  //int bufferAddress=0;
  /*1. Load the directory sector into a 512 byte character array using readSector.*/
  readSector(buffer,2); //The Directory sits at sector 2.
  readSector(map,1); //The map sits at sector 1.
  
  while(i<16){
    if(buffer[k] != 0x00){   //A byte entry of 0x00 means that the sector is free.
        int j  = 0;
  /*2. Go through the directory trying to match the file name. If you do not find it, return.*/
        while(j<6){
        // printChar(buffer[j+k]);
            // printChar(filename[j]);
          if(name[j] == buffer[j+k]){
            found = 1;

          }
          else{
            found = 0;
            //break;
          }
          j++;
          
        }
        if(found==1){
          break;
        }
    }
    i++;
    k=k+32;
  }


  if(found == 0){
    printString("Not Found\0");
  }else{
    //Set the first byte of the file name to 0x00.
    int j=6;
    int b = buffer[j+k];
    buffer[k]=0x00;

    while(buffer[j+k] != 0x00){
      map[b]=0x00;
      j++;
      printString("Deleted\0");
    }
    writeSector(map,1); 
    writeSector(buffer,2); 
  } 
}
 //================================================================================================================================================//
void writeFile(char* name, char* buffer, int secNum){

  char directory[512];
  char map[512];
  char subBuff[512];
  int i =0;
  int j = 0 ;
  int s=0;
  int z=0;
  int k=0;
  int m =0;
  int nameLen, kVal;
  readSector(directory,2);
  readSector(map,1);
//2. Find a free directory entry (one that begins with 0x00).
  for(m=0;m<16;m++){
    if(directory[i]==0x00){
      break;
    }
    i+=32;
  }
  //Copy the name to that directory entry. If the name is less than 6 bytes, fill
  //in the remaining bytes with 0x00.
  for(j=0;j<name[j]!='\0';j++){
    directory[i+j]=name[j];
  }
  while(j<6){
    directory[i+j]=0x00;
    j++;
  }
  //Find a free sector by searching through the Map for a 0x00
  for(s=0;s<secNum;s++){
    z=0;
    while(map[z]!=0x0){
      z++;
    }
    //Set that sector to 0xFF in the Map.
    map[z]=0xFF;
    //Add that sector number to the file’s directory entry.
    directory[i+j+s]=z;
    //Write 512 bytes from the buffer holding the file to that sector.
    for(k=0;k<512;k++){
      kVal = s+1;
      subBuff[k] = buffer[k*kVal];
    }
    writeSector(subBuff,z);
    
  }
  writeSector(map,1);
  writeSector(directory,2);


}