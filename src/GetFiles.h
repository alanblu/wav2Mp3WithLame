#include <iostream>
#include <dirent.h>
#include <vector>

using namespace std;

class GetFiles {
  private:
   struct dirent *entry;
   DIR *dir;
  
   const string wapExtension = ".WAV";
   const string wapExtension2 = ".wav";
   const int wavLenght = wapExtension.length();
    
  public:
    /* Constructor */
    GetFiles (const char *path);
    /* Destructor */
    ~GetFiles (void);
    /* Convert wav to mp3 */
    int GetWavFiles(vector<string> &listOfWavFiless);

};
