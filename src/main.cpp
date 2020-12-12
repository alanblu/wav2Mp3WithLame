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
#include <dirent.h>
#include <sys/types.h>
#include <iterator> 
#include <pthread.h>
#include "LameHandler.h"
#include "GetFiles.h"
//#include <experimental/filesystem>



//namespace fs = std::filesystem;

using namespace std;

int CreateThreadInLameHandle()
{
    /***** Create a New Thread From non static member function******/
    LameHandler * taskPtr = new LameHandler();
    // Thread id
    pthread_t threadId;
    // Create a thread and pass class member function Task::execute as argument i.e. thread function
    // type cast it with a function pointer of type = void * (*)(void *).
    // As member function takes this pointer of same class as first argument i.e. this pointer
    // So, pass the pointer to the object of class task as argument to thread function
    int err = pthread_create(&threadId, NULL, (THREADFUNCPTR) &LameHandler::ExecuteThread,taskPtr);
    // Check if thread is created successfully
    if (err)
    {
        std::cout << "Thread creation failed  " ;
        return err;
    }
    // Do some stuff in Main Thread
    std::cout << "Waiting for thread " << threadId << " to exit" << std::endl;
    // Wait for thread to exit, pass thread id as first argument
    err = pthread_join(threadId, NULL);
    if (err)
    {
        return err;
    }
    delete taskPtr;
    return 0;
}

int main(int argc, char *argv[]) 
{
    vector<string> allArgs;
    vector<string> filesToConvert;
    
    //LameHandler lameHandlInst;
       
    //lameHandl.ConvertWav2Mp3();

    if (argc > 1) 
    {
      
      allArgs.assign(argv + 1, argv + argc);
      const string pathToFiles = allArgs[0];
      GetFiles *WapFiles = new GetFiles(pathToFiles.c_str());
      WapFiles->GetWavFiles(filesToConvert);

    }
    else
    {
      cout << "There is no file to convert"<< endl;
    }

    
    for(const auto& value : filesToConvert)
    {
      cout << value  << endl ;
    }


    CreateThreadInLameHandle();


    pthread_exit(NULL);
    return 0;
}
