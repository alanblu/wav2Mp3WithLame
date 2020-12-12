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
#include<iterator> 
#include"lame.h"
#include <pthread.h>
//#include <experimental/filesystem>

//namespace fs = std::filesystem;

using namespace std;
//namespace fs = experimental::filesystem;
void convertLame1()
{
    int read, write;

    FILE *pcm = fopen("95_QuintupletsAfroDrums_730.wav", "rb");
    FILE *mp3 = fopen("testcase2.mp3", "wb");

    const int PCM_SIZE = 8192;
    const int MP3_SIZE = 8192;

    short int pcm_buffer[PCM_SIZE*2];
    unsigned char mp3_buffer[MP3_SIZE];

    lame_t lame = lame_init();
    lame_set_num_channels(lame,2);
    lame_set_brate(lame,128);
    lame_set_in_samplerate(lame, 44100);
    lame_set_mode(lame,(MPEG_mode)1);
    lame_set_VBR(lame, vbr_default);
    lame_set_quality(lame,2);
    int ret_code = lame_init_params(lame);

    if(ret_code < 0)
    {
	printf("ret_code < 0\n");
	return;
    }

    cout << "hola mundo"  << endl ;
    do {
        read = fread(pcm_buffer, 2*sizeof(short int), PCM_SIZE, pcm);
        if (read == 0)
        {
            write = lame_encode_flush(lame, mp3_buffer, MP3_SIZE);
        }
        else
        {
            write = lame_encode_buffer_interleaved(lame, pcm_buffer, read, mp3_buffer, MP3_SIZE);
        }
        fwrite(mp3_buffer, write, 1, mp3);
    } while (read != 0);

    lame_close(lame);
    fclose(mp3);
    fclose(pcm);
}

int list_dir(const char *path, vector<string> &listOfWavFiless) 
{
   struct dirent *entry;
   DIR *dir = opendir(path);
   const string wapExtension = ".WAV";
   const string wapExtension2 = ".wav";
   const int wavLenght = wapExtension.length();
   
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

   closedir(dir);
   return 0;
}

void *worker_thread(void *arg)
{
  printf("This is worker_thread()\n");
  convertLame1();
  pthread_exit(NULL);
}

int main(int argc, char *argv[]) 
{
    vector<string> allArgs;
    vector<string> filesToConvert;
    
    //list_dir("/home/alan/Documentos/Trabajo/C++Training/Para Empresa KA", filesToConvert);
    
    

    if (argc > 1) 
    {
      
      allArgs.assign(argv + 1, argv + argc);
      const string pathToFiles = allArgs[0];
      list_dir(pathToFiles.c_str(), filesToConvert);

    }
    else
    {
      cout << "There is no file to convert"<< endl;
    }

    
    for(const auto& value : filesToConvert)
    {
      cout << value  << endl ;
    }

    pthread_t my_thread;
    int ret;

    printf("In main: creating thread\n");
    ret =  pthread_create(&my_thread, NULL, &worker_thread, NULL);
    
    if(ret != 0) 
    {
      printf("Error: pthread_create() failed\n");
      exit(EXIT_FAILURE);
    }

    pthread_exit(NULL);
    return 0;
}
