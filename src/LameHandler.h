#include <iostream>
#include"lame.h"

typedef void * (*THREADFUNCPTR)(void *);

using namespace std;

class LameHandler {
  private:
    int read, write;
    FILE *pcm;
    FILE *mp3;
    static const int PCM_SIZE = 8192;
    static const int MP3_SIZE = 8192;
    short int pcm_buffer[PCM_SIZE*2];
    unsigned char mp3_buffer[MP3_SIZE];
    lame_t lame;
    int ret_code;
    
  public:
    /* Constructor */
    LameHandler (string path);
    /* Destructor */
    ~LameHandler (void);
    /* Convert wav to mp3*/
    int ConvertWav2Mp3(void);
    void * ExecuteThread();
};
