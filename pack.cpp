//#pragma comment(linker,"/MERGE:.rdata=.text")
//#pragma comment(linker,"/FILEALIGN:512 /SECTION:.text,EWRX /IGNORE:4078")
//#pragma comment(linker,"/ENTRY:New_WinMain")
//#pragma comment(linker,"/NODEFAULTLIB")
//---------------------------------------------------------------------------
#pragma hdrstop
#include<iostream.h>
#include<windows.h>
#include <file.h>
File_Adr file,file_two,file_key,file_exe;
char exename[1024];
char pass[1024];
bool add_file(char *dir, ffblk *file);
//---------------------------------------------------------------------------

#pragma argsused
int main(int argc, char* argv[])
{
        int i,j,k,n;
        char temp[256];
        char keyname[512];
        //�������
	if(argc ==2)
                if(!strcmp(argv[1],"help")){
                        cout<<"���������.\r\n��� ��������� - �������� ������������ ����� � ������ ����� �������"<<
                        "\r\n���� �������� - 1)����� ����� ��� �������� �����\r\n2)����� �����, ������� ���� ���������."<<endl;
                        return 0;}
        //������ ����������������� �����
        file=file_adr_split(argv[0]);
        file_two = file;
        strcpy(file_two.fname,"config");
        strcpy(file_two.fext,"ini");
        file_adr_join(file_two, temp);
        ifstream conf(temp, ios::in);
        char key_storage[256]; key_storage[0]=0;
        bool key_storage_status =  false;
        bool read_key_file = false;
        if(conf)
                while(conf)
                	{
                	conf>>temp;
                        if(!strcmp(temp,"key_storage_status"))
                        	{
                                conf>>temp;
                                conf>>temp;
                                if(!strcmp(temp,"enabled"))
                                	key_storage_status = true;
                                else
                                	key_storage_status = false;
                                }
                        if(!strcmp(temp,"key_storage"))
                        	{
                                conf>>temp;
                                conf>>key_storage;
                                }
                	}
        if(key_storage_status)
        	{
        	CharToOem("��������� ������: ",temp);
                cout<<temp<<key_storage<<endl;
                }
	//��������� �������� �����
        if(argc>1)
		{file_two=file_adr_split(argv[1]);}
        else{
                //�������� �� ���������� ������� �����
                int pos=file_find_string(argv[0], strcat("start","_"));
                if(pos==-1){
                	CharToOem("���������� �� ���� ����(�)  ��� ����� ��� �������� ������. ������ ���������.",temp);
                        cout<<temp;
                        cin>>pass;
                        return 1;}
                else
                	{
                        unsigned int pos1=file_find_string(argv[0], strcat("[+key_file","_]"));
                        unsigned int pos2=file_find_string(argv[0], strcat("[-key_file","_]"),pos1);
                        if(pos1 != -1 && pos2 != -1)
                        	{
                        	get_from_file(argv[0],temp,pos1+12,(pos2-pos1-12));
                                file_key = file_adr_split(temp);
                                read_key_file = true;
                        	CharToOem("�������������� ����� ����� � ",temp);
                        	cout<<temp<<file_key.fdir<<"..."<<endl;
                        	}
                        file_two.fext[0]=0;
                        }
                }
        //������ ����� ��������� �� ������ ���������
        if(strcmp(file_two.fext,"key") && argc>1){
                //�������� �� ���������� ������� �����
                int pos=file_find_string(argv[0], strcat("start","_"));
                if (pos!=-1){
                	CharToOem("������ ���� �������� �������. ��� �������� ������ ������ �������������� �������� ����������.",temp);
                        cout<<temp;
                        cin>>pass;
                        return -1;}
                char ext[8];
                //������� ������������� ����
                CharToOem("������� ������ (��� ��������):",temp);
                cout<<temp<<endl;
                cin>>pass;
                if(argv[1][strlen(argv[1])-1]=='\\')    //���� ��� ����� ������� ������� ����, ����� ������� ���� � ������ �����
                	argv[1][strlen(argv[1])-1]=0;	
		file_two=file_adr_split(argv[1]);
		strcpy(ext,file_two.fext);
		file_exe = file_two;
		strcpy(file_exe.fext,"exe");
                file_adr_join(file_exe,exename);
                if(!strcmp(ext,"exe") || !strcmp(ext,"EXE"))  //���� ���� exe,���������������, ����� ������������� ���� �� ����� ��� � ����
                        strcat(exename,".exe");
                //�������� ������
                file_key=file_two;
                if(key_storage_status)
                        strcpy(file_key.fdir, key_storage);
                strcpy(file_key.fext,"key");
_4:
                file_adr_join(file_key,keyname);
                ifstream tst (keyname);
                if(tst)
                	{
                        //���� ����������
                        randomize();
                        itoa(random(1000),temp,10);
                        strcpy(file_key.fname,file_two.fname);
                        strcat(file_key.fname,temp);
                        goto _4;
                        }
_2:
		CharToOem("����������, ����� ���� ���������� ������ �� ���� ����������? (yes/no):",temp);
                cout<<temp<<endl;
                char ans[256];
                Sleep(1000);
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
                        CharToOem("������ �����.",temp);
                	cout<<temp<<endl;
                        goto _2;}
                //������ ������ ����������
                add_to_file(argv[0],exename,false);
                //������ ����� �����
                if(key_storage_status)
                	{
			add_to_file_string(strcat("[+key_file","_]"),exename,true);
			add_to_file_string(keyname,exename,true);
			add_to_file_string(strcat("[-key_file","_]"),exename,true);
                        }
		//�����: ���������� ���� ��� �����
		if(ext[0]!=0)
			{//����
			char file_name[_MAX_PATH_NAME];
			strcpy(file_name,file_two.fname);
			strcat(file_name,".");
			strcat(file_name,file_two.fext);
			//������ ���� � �����
			add_to_file_string(strcat("start","_"),exename,true);
			add_to_file_string(file_name,exename,pass,true);
			add_to_file_string(strcat("end","_"),exename,true);
			//������ �����
			cout<<"Making...";
			add_to_file(argv[1],exename,pass,true,0,-1,-1);
			}
		else
			{//�����
                        cout<<"Making...";
			seach_dir(argv[1],add_file,true);  //������ ������ � �����
                        cout<<endl<<"ok";
                        getchar();
                        getchar();
			}
                return 0;
		}

		else{
		//��������� ������ �� ����� �� ���������
		char ans[256];
                if(read_key_file)
                	{
                        file_adr_join(file_key,keyname);
                        ifstream in (keyname,ios::in);
                        if(in)
                        	{
                                in>>pass;
                        	in>>ans;
                        	in.close();
                                goto _3;
                                }
                        else
                        	{
                        	CharToOem("���� �� ������",temp);
                                cout<<temp<<endl;
                                }
                        }
                //��������� ������ �� ���������� �����-�����
                if(argc > 1){
                    file_key = file_adr_split(argv[1]);
                    if(!strcmp(file_key.fext,"key")){
                	file_adr_join(file_key,keyname);
                        ifstream in (keyname,ios::in);
                        if(!in)
                                {
                                if(key_storage_status)
                                       	CharToOem("���� ��������� ��� ����������� � ���������",temp);
                                else
                                	CharToOem("���� ���������",temp);
                                cin>>temp;
                                return 3;}
                        in>>pass;
                        in>>ans;
                        in.close();}}
                //������ �� ���� ������
                else if (argc==1){
                        CharToOem("������� ������ ��� �������������:",temp);
                	cout<<temp<<endl;
                        cin>>pass;
                        CharToOem("����� ���������� ������ ��� ����� ����������? (yes/no):",temp);
                	cout<<temp<<endl;
                        cin>>ans;
                        file_key=file;}
_3:
		//��������� �����
                if(!strcmp(ans,"yes") || !strcmp(ans,"y")){
                        char VSNumber[4];
                        GetVolumeInformation("C:\\",NULL, NULL,(unsigned long*)VSNumber,NULL,NULL,NULL,NULL);
                        for(int k=0;pass[k];k++)
                                pass[k]=pass[k]^VSNumber[k%sizeof VSNumber];}
                //�������� ���������������� �����
                cout<<"Openig...";
                char name_two[1024];
                //����� ����� �����
		char file_name[1024];
		unsigned int pos1=file_find_string(argv[0], strcat("start","_"));
		unsigned int pos2=file_find_string(argv[0], strcat("end","_"),pos1);
		while(pos1!=-1 && pos2!=-1)
			{
			get_from_file(argv[0],file_name,pass,pos1+6,(pos2-pos1-6));
			file_two = file_adr_split(file_name);
			if(file_two.fdir[0]!=0)	//���� ���� ��������� ��������
                                make_folders(file.fdir,file_two.fdir);
                        char path[1024];
                        strcpy(path,file.fdir);
                        strcat(path,file_two.fdir);
                        if(strlen(path)!=0 && path[strlen(path)-1]!='\\')
                        	strcat(path,"\\");
                        strcpy(file_two.fdir, path);  //��������� � �� �� �����, ��� ����� �����
			file_adr_join(file_two,name_two);
                        //�� ������ ����� ��������
                        pos1=file_find_string(argv[0], strcat("start","_"),pos2);
                        static num=0;
                        num++;
                        char temp[_MAX_PATH_NAME];
                	CharToOem(name_two,temp);
			cout<<endl<<num<<" > "<<temp;
                        //�������� �����
			add_to_file(argv[0],name_two,pass,false,pos2+4,pos1-(pos2+4));
                        pos2=file_find_string(argv[0], strcat("end","_"),pos1);
			}
                cout<<endl<<"ok";
                getchar();
		}
        return 0;
}
//-----------���������� ������ �����---------------------------------------
bool add_file(char *dir, ffblk *file)
{
	if((file->ff_attrib & FA_DIREC) == 0)
     		{
                //������� ������������� ���� � �����
                char path[_MAX_PATH_NAME];
                File_Adr t;
                t = file_adr_split(exename);
                int i,j;
                for(i=0;t.fdir[i] == dir[i];i++);   //���������� � ����������� ������
                if(dir[i]=='\\')
                	i++;
                //i ��������� �� ������ ������,����������� �� ��������
                for(j=0;dir[i];i++,j++)
                	path[j] = dir[i];
                path[j]=0;
                if(path[strlen(path)-1]!='\\')
     			strcat(path,"\\");
                strcat(path,file->ff_name);
     		//������ ���� � �����
     		add_to_file_string(strcat("start","_"),exename,true);
     		add_to_file_string(path,exename,pass,true);
     		add_to_file_string(strcat("end","_"),exename,true);
     		//������ �����
     		char adr[_MAX_PATH_NAME];
     		strcpy(adr,dir);
     		if(adr[strlen(adr)-1]!='\\')
     			strcat(adr,"\\");
     		strcat(adr,file->ff_name);
                static num=0;
                num++;
                char temp[_MAX_PATH_NAME];
                CharToOem(adr,temp);
     		cout<<endl<<num<<" > "<<temp;
     		add_to_file(adr,exename,pass,true,0,-1,-1);
     		}
     return false; //���������� �����
}

