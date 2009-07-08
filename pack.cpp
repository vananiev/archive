//---------------------------------------------------------------------------
#include<stdio.h>
#include<windows.h>
#include <file.h>
char full_name[255];
File_Adr file,file_two,file_key;
//---------------------------------------------------------------------------
#pragma argsused
int main(int argc, char* argv[])
{
        int i,j,k,n;
        char pass[1024];
        //справка
        if(argc ==2)
                if(!strcmp(argv[1],"help")){
                        printf("Архиватор.\r\nБез парметров - открытие упакованного файла с вводом ключа вручную\r\nОдин параметр - 1)адрес ключа для открытия файла\r\n2)адрес файла, который надо упаковать.\n");
                        return 0;}

        //получение сведения файла
        file=file_adr_split(argv[0]);
        if(argc>1)
                file_two=file_adr_split(argv[1]);
                else{
                //проверка на содержание другого файла
                int pos=file_find_string(argv[0], strcat("start","_"),200000);
                if(pos==-1){
                        printf("Can`t find file for make achive.Stop working.");
                        scanf("%s",pass);
                        return 1;}
                        else
                        file_two.fext[0]=0;
                }
        if(strcmp(file_two.fext,"key") && argc>1){
                //проверка на содержание другого файла
                int pos=file_find_string(argv[0], strcat("start","_"),200000);
                if (pos!=-1){
                        printf("Error.This file is alredy achive.");
                        scanf("%s",pass);
                        return -1;}
                char ext[8];
                //создаем зашифрованный файл
                printf("Enter the passcode:\n");
                scanf("%s",pass);
                Sleep(100);
                file_two=file_adr_split(argv[1]);
                strcpy(ext,file_two.fext);
                strcpy(file_two.fext,"exe");
                char exename[1024];
                file_adr_join(file_two,exename);
                //создание пароля
                char keyname[512];
                file_key=file_two;
                strcpy(file_key.fext,"key");
                file_adr_join(file_key,keyname);
                printf("For this computer used onle? (yes/no):\n");
                char ans[256];
                scanf("%s",ans);
                if(!strcmp(ans,"yes") || !strcmp(ans,"y")){
                        // open key file
                        ofstream out(keyname,ios::out);
                        printf("%s/n",pass);
                        printf("yes");
                        out.close();
                        char VSNumber[4];
	                GetVolumeInformation("C:\\",NULL, NULL,(unsigned long*)VSNumber,NULL,NULL,NULL,NULL);
                        for(int k=0;pass[k];k++)
                                pass[k]=pass[k]^VSNumber[k%sizeof VSNumber];
                        }
                        else if(!strcmp(ans,"no") || !strcmp(ans,"n")){
                        // open key file
                        ofstream out(keyname,ios::out);
                        printf("%s/n",pass);
                        printf("no");
                        out.close();}
                        else{
                        printf("Error of answer. End of working.");
                        scanf("%s",pass);
                        return 1;}
                add_to_file(argv[0],exename,false);
                //запись расширения
                add_to_file_string(strcat("start","_"),exename,true,0);
                add_to_file_string(ext,exename,true,0);
                add_to_file_string(strcat("end","_"),exename,true,0);
                //запись файла
                printf("Making...");
                add_to_file(argv[1],exename,pass,true,0);}

                else{
                //извлекаем пароль
                char ans[256];
                if(!strcmp(file_two.fext,"key")){
                        ifstream in (argv[1],ios::in);
                        scanf("%s",pass);
                        scanf("%s",ans);
                        in.close();}
                        else if (argc==1){
                        printf("Enter the passcode:/n");
                        scanf("%s",pass);
                        printf("For this computer used onle? (yes/no):/n");
                        scanf("%s",ans);
                        file_two=file;}
                if(!strcmp(ans,"yes") || !strcmp(ans,"y")){
                        char VSNumber[4];
                        GetVolumeInformation("C:\\",NULL, NULL,(unsigned long*)VSNumber,NULL,NULL,NULL,NULL);
                        for(int k=0;pass[k];k++)
                                pass[k]=pass[k]^VSNumber[k%sizeof VSNumber];}
                //сведения распаковываемого файла
                char name_two[1024];
                //ПОИСК расширения
                char ext[8];
                int pos1=file_find_string(argv[0], strcat("start","_"),200000);
                int pos2=file_find_string(argv[0], strcat("end","_"),pos1);
                get_from_file(argv[0],ext,pos1,(pos2-pos1-3));
                strcpy(file_two.fext,ext);
                file_adr_join(file_two,name_two);
                //открытие файла
                printf("Openig...");
                add_to_file(argv[0],name_two,pass,false,pos2);}
        return 0;
}
//---------------------------------------------------------------------------

