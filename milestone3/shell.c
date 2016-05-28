// void core (char* buff);
// int div(int a, int b);
// void prnt(char* buff);
// void clear(char* buff, int len);
// int main () {
// 		char buffer[180];
// 		prnt("welcome");
// 		interrupt(0x21,1,buffer,0,0);	
// 		prnt("\r\n");
// 		prnt("--> ");
// 		core(buffer);
// 		clear(buffer,180);
// }
// void core (char* buff){
// 	int i,x,index;
// 	char fileName[7];
// 	char fileName1[7];
// 	char fileName2[7];
// 	int a = 1;
// 	int c=0;
// 	int createIndex = 0;
// 	char createBuff[512];
// 	char buffFile[13312];
// 	char rembuff[180];
// 	int sectors;
// 	int j =0;
// 	int length = 0;


// 	for (x = 0; x <180; x++){

// 		if(buff[x] != 0x0 && buff[x] != '\r' && buff[x] != '\n'
// 		 && buff[x] != '-' && buff[x] != '>'){
// 			break;
// 		}
// 	}

//    //view
// 	if (buff[x]=='v' && buff[x+1]=='i' && buff[x+2]=='e' && buff[x+3]=='w'){
// 		x = x + 5;

// 		for(i=0;i<6;i++){
// 			fileName[i] = buff[x+i];
// 		}
// 		fileName[6] = "\0";
		
// 		interrupt(0x21, 3, fileName, buffFile, 0);

// 		prnt(buffFile);
// 		prnt("--> ");
		
// 	}
// 	// execute
// 	if (buff[x]=='e' && buff[x+1]=='x' && buff[x+2]=='e' && buff[x+3]=='c' && buff[x+4]=='u'
// 	 && buff[x+5]=='t'&& buff[x+6]=='e'){
// 		x = x + 8;

// 		for(i=0;i<6;i++){
// 			fileName[i] = buff[x+i];
// 		}
// 		fileName[6] = "\0";

// 		interrupt(0x21, 4, fileName, 0x2000, 0);

// 		//copy
// 		if (buff[x]=='c' && buff[x+1]=='o' && buff[x+2]=='p' && buff[x+3]=='y'){
// 		index = x+5;
// 		j = 0;
// 		while(buff[index] != 0x20 && buff[index] != 0x0){
// 			fileName1[j] = buff[index];
// 			index++;
// 			j++;
// 		}
// 		fileName1[6] = '\0';

// 		j = 0;
// 		index++;
// 		while(buff[index] != 0x20 && buff[index] != 0x0){
// 			fileName2[j] = buff[index];
// 			index++;
// 			j++;
// 		}
// 		fileName2[6] = '\0';
		
// 		interrupt(0x21,3,fileName1,buffFile,0);
// 		while(buffFile[length] != 0x0){
// 			length++;
// 		}		
// 		sectors = div(length,512);

// 		interrupt(0x21,8,fileName2,buffFile,sectors+1);
		
// 	}
// 	}
// 	//delete
// 	if (buff[x]=='d' && buff[x+1]=='e' && buff[x+2]=='l' && buff[x+3]=='e'&& buff[x+4]=='t' && buff[x+5]=='e'){
// 		x = x + 7;

// 		for(i=0;i<6;i++){
// 			fileName[i] = buff[x+i];
// 		}
// 		fileName[6] = "\0";

// 		interrupt(0x21,7,fileName,0,0);
// 	}
//     // create
// 	 if (buff[x]=='c' && buff[x+1]=='r' && buff[x+2]=='e' && buff[x+3]=='a'&& buff[x+4]=='t' && buff[x+5]=='e'){
// 		x = x + 7;
// 		for(i=0;i<6;i++){
// 			fileName[i] = buff[x+i];
// 		}
// 		fileName[6] = "\0";
// 		while(a){
// 			/* Get user input */
// 			clear(rembuff,180);
//         	interrupt(0x21,1,rembuff,0,0);
// 			prnt("\r\n");

// 			if (rembuff[2] == 0x0){
// 				prnt("\r\n");
// 				a = 0;
// 				break;
// 			}
// 			else{

// 				for(i=0;i<180;i++){
// 					if(rembuff[i] == 0x0 || rembuff[i] == '\0'||rembuff[i]=='\r'||rembuff[i]=='\n'||rembuff[i]=='\t'){
// 						rembuff[i] = 0x20;
// 					}
// 					createBuff[i+180*createIndex] = rembuff[i];
// 				}
// 				c++;
// 				createIndex++;
// 			}
// 		}	
// 		sectors = div(c/512);
// 		interrupt(0x21,8,fileName,createBuff,c);

// 	}

// 	}

// 	int div(int a, int b){
//     int q = 0;
//     while(q*b <=a){
//         q = q+1;
//     }
//     return q-1;

// }
// void prnt(char* buff){
// 	interrupt(0x21,0,buff,0,0);
// }
// void clear(char* buff, int len){
// 	int i;
// 	for(i=0;i<len;i++){
// 		buff[i] = 0x0;
// 	}
// }



