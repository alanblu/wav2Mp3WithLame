#include <string>
#include "GetFiles.h"

using namespace std;

GetFiles::GetFiles(const char *path)
{
  dir = opendir(path);
}

GetFiles::~GetFiles()
{
   closedir(dir);  
}

int GetFiles::GetWavFiles(vector<string> &listOfWavFiless)
{
   if (dir == NULL) 
   {
      return -1;
   }
   while ((entry = readdir(dir)) != NULL) 
   {
      string fileInDirectory = string(entry->d_name);
      
      if ( ( string::npos != fileInDirectory.find(wapExtension) || string::npos != fileInDirectory.find(wapExtension2) ) 
        && ( (fileInDirectory.length() - fileInDirectory.find(wapExtension) == wavLenght || (fileInDirectory.length() -          fileInDirectory.find(wapExtension2)) ) ) )
      {
         listOfWavFiless.push_back(fileInDirectory); 
      }
      
   }
   return 0;
}
