//#pragma comment(linker,"/MERGE:.rdata=.text")
//#pragma comment(linker,"/FILEALIGN:512 /SECTION:.text,EWRX /IGNORE:4078")
#pragma comment(<linker>, "/ENTRY:_123")
//#pragma comment(linker,"/NODEFAULTLIB")
//---------------------------------------------------------------------------
#pragma hdrstop
#include<iostream.h>
#include<windows.h>
#include <file.h>
char full_name[255];
File_Adr file,file_two,file_key;
void ___CPPdebugHook(){;};
//---------------------------------------------------------------------------

#pragma argsused
int main(int argc, char* argv[])
//WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
        /*int argc;
        char argv[4][256];
        //обработка командной строки
        for(int i=0,j=0;lpCmdLine[i];i++,j++){
                if(lpCmdLine[i]==' ')
                        if(argv[argc][0]!=0){
                                argv[argc][j]=0;
                                j=0;
                                argc++;}
                argv[argc][j]=lpCmdLine[i];
                }
        */

        int i,j,k,n;
        char pass[1024];
        //справка
        if(argc ==2)
                if(!strcmp(argv[1],"help")){
                        cout<<"Архиватор.\r\nБез парметров - открытие упакованного файла с вводом ключа вручную"<<
                        "\r\nОдин параметр - 1)адрес ключа для открытия файла\r\n2)адрес файла, который надо упаковать."<<endl;
                        return 0;}

        //получение сведения файла
        file=file_adr_split(argv[0]);
        if(argc>1)
                file_two=file_adr_split(argv[1]);
                else{
                //проверка на содержание другого файла
                int pos=file_find_string(argv[0], strcat("start","_"));
                if(pos==-1){
                        cout<<"Can`t find file for make achive.Stop working.";
                        cin>>pass;
                        return 1;}
                        else
                        file_two.fext[0]=0;
                }
        if(strcmp(file_two.fext,"key") && argc>1){
                //проверка на содержание другого файла
                int pos=file_find_string(argv[0], strcat("start","_"));
                if (pos!=-1){
                        cout<<"Error.This file is alredy achive.";
                        cin>>pass;
                        return -1;}
                char ext[8];
                //создаем зашифрованный файл
                cout<<"Enter the passcode:"<<endl;
                cin>>pass;
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
                cout<<"For this computer used onle? (yes/no):"<<endl;
                char ans[256];
                cin>>ans;
                if(!strcmp(ans,"yes") || !strcmp(ans,"y")){
                        // open key file
                        ofstream out(keyname,ios::out);
                        out<<pass<<endl;
                        out<<"yes";
                        out.close();
                        char VSNumber[4];
	                GetVolumeInformation("C:\\",NULL, NULL,(unsigned long*)VSNumber,NULL,NULL,NULL,NULL);
                        for(int k=0;pass[k];k++)
                                pass[k]=pass[k]^VSNumber[k%sizeof VSNumber];
                        }
                        else if(!strcmp(ans,"no") || !strcmp(ans,"n")){
                        // open key file
                        ofstream out(keyname,ios::out);
                        out<<pass<<endl;
                        out<<"no";
                        out.close();}
                        else{
                        cout<<"Error of answer. End of working.";
                        cin>>pass;
                        return 1;}
                add_to_file(argv[0],exename,false);
                //запись расширения
                add_to_file_string(strcat("start","_"),exename,true,0);
                add_to_file_string(ext,exename,true,0);
                add_to_file_string(strcat("end","_"),exename,true,0);
                //запись файла
                cout<<"Making...";
                add_to_file(argv[1],exename,pass,true,0);}

                else{
                //извлекаем пароль
                char ans[256];
                if(!strcmp(file_two.fext,"key")){
                        ifstream in (argv[1],ios::in);
                        in>>pass;
                        in>>ans;
                        in.close();}
                        else if (argc==1){
                        cout<<"Enter the passcode:"<<endl;
                        cin>>pass;
                        cout<<"For this computer used onle? (yes/no):"<<endl;
                        cin>>ans;
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
                cout<<"Openig...";
                add_to_file(argv[0],name_two,pass,false,pos2);}
        return 0;
}
//---------------------------------------------------------------------------

