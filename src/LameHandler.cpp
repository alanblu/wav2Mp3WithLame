
#include"LameHandler.h"

using namespace std;

LameHandler::LameHandler()
{
    pcm = fopen("testcase.wav", "rb");
    mp3 = fopen("testcase4.mp3", "wb");

    /* Set all the standars parameters */
    lame = lame_init();
    lame_set_num_channels(lame,2);
    lame_set_brate(lame,128);
    lame_set_in_samplerate(lame, 44100);
    lame_set_mode(lame,(MPEG_mode)1);
    lame_set_VBR(lame, vbr_default);
    lame_set_quality(lame,2);
    ret_code = lame_init_params(lame);
}

LameHandler::~LameHandler()
{
    /* Close all the files */
    lame_close(lame);
    fclose(mp3);
    fclose(pcm);
}

int LameHandler::ConvertWav2Mp3(void)
{
    if(ret_code < 0)
    {
        /* Failure */
	printf("ret_code < 0\n");
	return -1;
    }

    cout << "hola mundo 2"  << endl ;
    
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
    
    /* Sucess */
    return 0;
}

void * LameHandler::ExecuteThread()
{
    std::cout << "Task :: execute from Thread ID : " << pthread_self()
            << std::endl;
    ConvertWav2Mp3();
    return NULL;
}

