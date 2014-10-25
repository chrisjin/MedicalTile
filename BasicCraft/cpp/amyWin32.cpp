#include"amyWin32.h"
#include"windows.h"
void amyFolder::Open(const char* name,bool isiter)
{
	WIN32_FIND_DATAA FindFileData;
	char foldername[MAX_PATH];
	char filename[MAX_PATH];
	strcpy(foldername,name);
	strcpy(filename,foldername);
	strcat(filename,"\\*.*");
	HANDLE hFind; 
	hFind=FindFirstFileA(filename,&FindFileData);   
	if(hFind==INVALID_HANDLE_VALUE)                               //如果hFind句柄创建失败，输出错误信息   
	{  
		FindClose(hFind);   
		return;    
	}  
	else   
	{  
		while(FindNextFileA(hFind,&FindFileData)!=0)                            //当文件或者文件夹存在时   
		{  
			if((FindFileData.dwFileAttributes&FILE_ATTRIBUTE_DIRECTORY)!=0
				&&strcmp(FindFileData.cFileName,".")==0
				||strcmp(FindFileData.cFileName,"..")==0)        //判断是文件夹&&表示为"."||表示为"."   
			{  
				continue;  
			}  
			if((FindFileData.dwFileAttributes&FILE_ATTRIBUTE_DIRECTORY)!=0&&isiter==1)      //判断如果是文件夹   
			{  
				char DirAdd[MAX_PATH];  
				strcpy(DirAdd,foldername);  
				strcat(DirAdd,"\\");  
				strcat(DirAdd,FindFileData.cFileName);       //拼接得到此文件夹的完整路径   
				Open(DirAdd);                                  //实现递归调用   
			}  
			if((FindFileData.dwFileAttributes&FILE_ATTRIBUTE_DIRECTORY)==0)    //如果不是文件夹   
			{  
				char DirAdd[MAX_PATH]; 
				strcpy(DirAdd,foldername);  
				strcat(DirAdd,"\\");  
				strcat(DirAdd,FindFileData.cFileName);       //拼接得到此文件夹的完整路径  
				OnFindFile(DirAdd);
			}  
		}  
		FindClose(hFind);  
	}  

}

void amyFolder::OnFindFile(const char* name)
{

}