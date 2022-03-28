#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

void wc(FILE *ofile, FILE *infile, char *inname) {
  // your code here:
  int lines,words,characters,flag;
  char ch;
  lines=words=characters=flag=0;

  if(ofile==NULL&&infile==NULL&&inname==NULL) return ;

  while((ch=fgetc(infile)) != EOF){
    if(ch=='\n')
        {
            if(flag!=1)
                ++words;
            ++lines;
            flag=1;
        }
    else{
        if(ch==' ')
        {
            if(flag!=1)
                ++words;
            flag=1;
        }
        else flag=0;
    }
    ++characters;
  }

  if(flag!=1) ++words;
  ++lines;

  if(ofile!=NULL)
    {fprintf(ofile,"lines:%d,words:%d,characters:%d",lines,words,characters);
     fclose(ofile);
    }
  else
    printf("lines:%d,words:%d,characters:%d",lines,words,characters);

  fclose(infile);

}

int main (int argc, char *argv[]) {

  char* out_file_name = NULL;
	char* inname = NULL;
	if(argc == 1) wc(NULL,NULL,NULL);
	else if(argc == 2){
		inname = argv[1];
		FILE *infile = fopen(inname,"r");
		if(!infile){
			perror("Input file opening failed");
			exit(1);
		}
		wc(NULL,infile,inname);
	}
	else if(argc == 3){
		inname = argv[1];
		FILE *infile = fopen(inname,"r");
		if(!infile){
			perror("Input file opening failed");
			exit(1);
		}
		FILE *out_file = fopen(argv[2],"w");
		if(!out_file){
			perror("Output file opening failed");
			exit(1);
		}
		wc(out_file,infile,inname);
	}
	else{
		printf("arguments error\n");
		exit(1);
	}


	/*FILE* infile=fopen("test_wc.txt","r");
	FILE* ofile=fopen("test_write.txt","w");
	wc(ofile,infile,NULL);*/

	return 0;

}
