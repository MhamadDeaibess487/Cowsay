
#include <stdio.h>
#include <unistd.h>
#include <string.h>
void update (){printf("\033[2J\033[1;1H");}
int affiche_vache(int argc , char* argv[]){
    char ears[]="^__^";
    char eyes[]="oo";
    char tung[]="__";
    char tail[]="\\/\\";
    FILE*f;
    char mot[128]="";
    if(argc<2){return 1;}
    f=fopen(argv[1],"r");
    if (f==NULL){return 1;}
    char c;
    char temp[2]="";
    fscanf(f,"%c",&c);
    while(!feof(f)){
    if(c==' '){
    strcpy(mot,"");
    temp[0]='\0';
    }else{
    temp[0]=c;
    temp[1]='\0'; 
    }
    printf("  \"%s\"\n",mot);
    printf("        \\   %s\n",ears);
    printf("         \\  (%s)\\_______\n",eyes);
    printf("            (%s)\\       )%s\n",tung,tail);
    printf("             %c  ||----w |\n",c);
    printf("                ||     ||\n");
    strcat(mot,temp);
    fscanf(f,"%c",&c);
    sleep(1);
    update();
    }
    fclose(f);
    return 0;
   }
int main(int argc,char*argv[]){
    affiche_vache(argc,argv);
}
