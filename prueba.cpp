/* 
TASK
Write a C/C++ commandline application that encodes a set of WAV files to MP3

Requirements:
(1) application is called with pathname as argument, e.g. <applicationname> F:\MyWavCollection all WAV-files contained directly in that folder are to be encoded to MP3
(2) use all available CPU cores for the encoding process in an efficient way by utilizing multi-threading
(3) statically link to LAME encoder library
(4) application should be compilable and runnable on Windows and Linux
(5) the resulting MP3 files are to be placed within the same directory as the source WAV files, the filename extension should be changed appropriately to .MP3
(6) non-WAV files in the given folder shall be ignored
(7) multithreading shall be implemented in a portable way, for example using POSIX pthreads.
(8) frameworks such as Boost or Qt shall not be used
(9) the LAME encoder should be used with reasonable standard settings (e.g. quality based encoding with quality level "good")

Please try to send me you result (via Mail) as soon as possible. The hiring manager will be on vacation from December 14th 2020, returning on January 11th 2021.

If you have some questions concerning the task, please do not hesitate to contact me.

Looking forward to your answer. 
*/

#include <iostream>
#include <string>
#include <algorithm> 
#include <vector>
#include <filesystem>

//namespace fs = std::filesystem;

using namespace std;

int main(int argc, char *argv[]) 
{
    vector<string> allArgs;
    const string wapExtension = ".WAV"

    if (argc > 1) 
    {
      
      allArgs.assign(argv + 1, argv + argc);
      
      for (int idx = 0; idx < allArgs.size(); idx++) 
      {
        cout << allArgs[idx].length()  << endl ;
      }
    }
    else
    {
      cout << "There is no file to convert"<< endl;
    }

    cout << "Hello, World!\n";

    transform(allArgs[1].begin(), allArgs[1].end(), allArgs[1].begin(), ::toupper);
    cout << "String is  : " << allArgs[1] << endl;	
    return 0;
}
