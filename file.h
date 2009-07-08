#include <fstream.h>
#include <dir.h>

class File_Adr{
	public:
	char fdir[255];
	char fname[255];
	char fext[8];};
//*******************************************************************************************************
int add_to_file(char from[255], char to[255],bool add=false,unsigned int seek=0)
{
	char data;
        ofstream out;
	// open to stream
        if (add){
	        out.open(to, ios::out| ios::binary|ios::app);
                if (!out) return 2;}
                else{
                out.open(to, ios::out| ios::binary|ios::trunc);
                if (!out) return 2;}
        //open from
	ifstream in (from,ios::in|ios::binary);
	if (!in)  return 1;
	// copy
        in.seekg(seek,ios::beg);
	do
	{
		in.get(data);
                out.put(data);
        }while(in);
	in.close();
        out.close();
	return 0;
}
//*******************************************************************************************************
int add_to_file(char from[255], char to[255],char* pass,bool add=false,unsigned int seek=0)
{
	char data;
        int len;
        ofstream out;
        union {
                unsigned int sum;
                unsigned char c[4];};
        sum=-34186*14373; //?????
        for(len=0;pass[len];len++)
                sum *= pass[len];
	// open to stream
        if (add){
	        out.open(to, ios::out| ios::binary|ios::app);
                if (!out) return 2;}
                else{
                out.open(to, ios::out| ios::binary|ios::trunc);
                if (!out) return 2;}
        //open from
	ifstream in (from,ios::in|ios::binary);
	if (!out)  return 1;
	// copy
        in.seekg(seek,ios::beg);
	for(int k=0;in;k++)
	{
		in.get(data);
                //XOR
                out.put(data^pass[k%len]^c[k%4]);
        }
	in.close();
        out.close();
	return 0;
}
//*******************************************************************************************************
int add_to_file_string(char* string, char to[255],bool add=false,unsigned int seek=0)
{
        ofstream out;
	// open to stream
        if (add)
	        out.open(to, ios::out| ios::binary|ios::app);
                else
                out.open(to, ios::out| ios::binary|ios::trunc);
	if (!out) return 1;
	// copy
	out.seekp(seek,ios::beg);
        for(int k=0;string[k];k++)
                out.put(string[k]);
        out.close();
	return 0;
}
//*******************************************************************************************************
int add_to_file_string(char* string, char to[255],char* pass,bool add=false,unsigned int seek=0)
{
	char data;
        int len;
        union {
                unsigned int sum;
                unsigned char c[4];};
        sum=-34186*14373; //?????
        for(len=0;pass[len];len++)
                sum *= pass[len];
        ofstream out;
	// open to stream
        if (add)
	        out.open(to, ios::out| ios::binary|ios::app);
                else
                out.open(to, ios::out| ios::binary|ios::trunc);
	if (!out) return 1;
	// copy
	out.seekp(seek,ios::beg);
        for(int k=0;string[k];k++)
	{
                //XOR
                out.put(string[k]^pass[k%len]^c[k%4]);
        }
        out.close();
	return 0;
}
//*******************************************************************************************************
int file_find_string(char* file,char* string,unsigned int from_pos=0)
{
        char data;
        int len;
        for(len=0;string[len];len++);
        ifstream in(file, ios::in| ios::binary);
        in.seekg(from_pos,ios::beg);
        int i=0,k=0,pos=0;
        while(in){
                in.get(data);
                pos++;
                if(data==string[k])
                        for(i=1;string[i];i++){
                                in.get(data);
                                pos++;
                                if(data!=string[i]){
                                        k=0;
                                        break;}}
                if(string[i]=='\0') return from_pos+pos;;
                }
        in.close();
        return -1;
}
//*******************************************************************************************************
int file_find_string(char* file,char* string,char* pass,unsigned int from_pos=0)
{
        char data;
        int len;
        int pass_len;
        union {
                unsigned int sum;
                unsigned char c[4];};
        sum=-34186*14373; //?????
        for(pass_len=0;pass[pass_len];pass_len++)
                sum *=  pass[pass_len];
        //??????, ?? ??        for(len=0;string[len];len++)
                string[len]=string[len]^pass[len%pass_len]^c[len%4];
        ifstream in(file, ios::in| ios::binary);
        in.seekg(from_pos,ios::beg);
        int i=0,k=0,pos=0;
        while(in){
                in.get(data);
                pos++;
                if(data==string[k])
                        for(i=1;string[i];i++){
                                in.get(data);
                                pos++;
                                if(data!=string[i]){
                                        k=0;
                                        break;}}
                if(string[i]=='\0') return from_pos+pos;;
                }
        in.close();
        return -1;
}
//*******************************************************************************************************
int get_from_file(char* file,char *string,int pos=0,unsigned int len=-1)
{
        char data;
        ifstream in(file, ios::in| ios::binary);
        in.seekg(pos,ios::beg);
        unsigned int i=0;
        while(in && i<len){
                in.get(data);
                string[i]=data;
                i++;
                }
        in.close();
        string[--i]=0;
        return 0;
}
//*******************************************************************************************************
int get_from_file(char* file,char *string,char* pass,unsigned int pos=0,unsigned int len=-1)
{
        char data;
        ifstream in(file, ios::in| ios::binary);
        in.seekg(pos,ios::beg);
        int pass_len;
        union {
                unsigned int sum;
                unsigned char c[4];};
        sum=-34186*14373; //?????
        for(pass_len=0;pass[pass_len];pass_len++)
                sum *=  pass[pass_len];
        unsigned int i=0;
        while(in && i<len){
                in.get(data);
                data=(data^pass[i%pass_len]^c[i%4]);
                string[i]=data;
                i++;
                }
        in.close();
        string[--i]=0;
        return 0;
}
//*******************************************************************************************************
File_Adr file_adr_split(char full_name[255])
{
	int i,j,k,n;
	File_Adr file;
        //??????
        for(i=strlen(full_name)-1; i>=0 && full_name[i]!='\\'; i--);
        j=0;
        file.fdir[j] = 0;
        if(i!=-1)
                for (;j<i+1;j++)
                        file.fdir[j]=full_name[j];
        file.fdir[j]='\0';
        //??
        file.fname[0] = 0;
        for (j=i+1,k=0;full_name[j]!='.' && full_name[j];j++,k++)
                file.fname[k]=full_name[j];
        file.fname[k]='\0';
        //???
        k=0;
        file.fext[k] = 0;
        if(full_name[j])
                for (n=j+1,k=0;full_name[n];n++,k++)
                        file.fext[k]=full_name[n];
        file.fext[k]='\0';
	return file;
}

//*******************************************************************************************************
void file_adr_join(File_Adr file,char* name)
{
	int i,j,k,n;
        //??????
        for(i=0,k=0;file.fdir[i];i++,k++)
                    name[k]=file.fdir[i];
        //??
        for(i=0;file.fname[i];i++,k++)
                    name[k]=file.fname[i];
        name[k++]='.';
        //???
        for(i=0;file.fext[i];i++,k++)
                    name[k]=file.fext[i];
        name[k]=0;
}



//*******************************************************************************************************
char f[1024][MAXPATH];
int seach_dir(char *path,bool (*func)(char*),bool SeachInSubdir=false)
{
	int done;
	const int dir_deep=32; //max DEEP dir
	struct ffblk file;
	int count=0;
	char dir[dir_deep][MAXPATH];
	int objcount=0;

	setdisk(toupper(path[0])-'A');
	if (chdir(path)) return 0;

	//seach file
	done=findfirst("*.*",&file,0);
	count=0;
	while(!done && count<dir_deep)
	{
		if (file.ff_name[0]=='.')
		{
			done=findnext(&file);
			continue;
                }
		//make dir adr
		strcpy(f[count],path);
		if(f[count][strlen(dir[count])-1]!='\\')
                	strcat(f[count],"\\");
		strcat(f[count],file.ff_name);
//call func
		if((*func)(f[count])) return objcount+=count;
		done=findnext(&file);
		count++;
	}
        
        //seach directory

	done=findfirst("*.",&file,17);
	count=0;
	while(!done && count<dir_deep)
	{
		if (file.ff_name[0]=='.')
		{
			done=findnext(&file);
			continue;
                }
		//make dir adr
		strcpy(dir[count],path);
		if(dir[count][strlen(dir[count])-1]!='\\')
                	strcat(dir[count],"\\");
		strcat(dir[count],file.ff_name);
//call func
		if((*func)(dir[count])) return objcount+=count;
		done=findnext(&file);
		count++;
	}
        objcount+=count;
        //seach in found directoryes
        if(SeachInSubdir)
	        for(int i=0; i<count; i++)  objcount+=seach_dir(dir[i],func,SeachInSubdir);
	
	//number of subdirs
	return objcount;
}//seach_dir
//*******************************************************************************************************
bool split_str(char *Str,  char* divider,  char* res, int NumOfStr = 2, int LenOfStr = 256)
{
        int n=0;
        int i=0;
        int j=0;
        bool more = true;
        bool ans = true;
        while(Str[n]){
                        if(more && ((unsigned char) Str[n] != (unsigned char)divider[0]))
                                    {*(res+i*LenOfStr+j) = Str[n];
                                    j++;
                                    n++;
                                    if(j >= LenOfStr) {
                                                ans = false;
                                                more = false;}
                                    }
                        else{
                                if(more == false)
                                        {more = true;
                                        j=LenOfStr;}
                                *(res+i*LenOfStr+j) = 0;
                                j=0;
                                i++;
                                if(i >= NumOfStr) return false;
                                for(int m=0; (unsigned char) Str[n] == (unsigned char)divider[m];m++,n++)
                                        if(Str[n] == 0) return true;
                                }
                }
        return ans; //false - если строка обрезана, не помещаясь в LenOfStr, или не хватило строк.
}
//*******************************************************************************************************
char* DosToAnsi(char * s)
{
        for(int i=0;s[i];i++)
                {if(s[i]>=0xFFFFFF80 && s[i]<=0xFFFFFFAF) //АБВ-ЭЮЯ,абв-мноп
                        s[i]+=0x00000040;
                else if(s[i]>=0xFFFFFFE0 && s[i]<=0xFFFFFFEF) //рст-эюя
                        s[i]+=0x00000010;
                }
        return s;
}
//*******************************************************************************************************
char* AnsiToDos(char * s)
{
        for(int i=0;s[i];i++)
                {if(s[i]>=0xFFFFFFC0 && s[i]<=0xFFFFFFEF) //АБВ-ЭЮЯ,абв-мноп
                        s[i]-=0x00000040;
                else if(s[i]>=0xFFFFFFF0 && s[i]<=0xFFFFFFFF) //рст-эюя
                        s[i]-=0x00000010;
                }
        return s;
}
//*******************************************************************************************************
