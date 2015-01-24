#ifndef JACKAUDIOCLIENT_H
#define JACKAUDIOCLIENT_H

#include <jack/jack.h>

#include "abstractaudioclient.h"

class JackAudioClient : public AbstractAudioClient
{
private:
    JackAudioClient();
public:
    static JackAudioClient * getInstance();
    void playWav(const std::string& fileName);
    void recordWav(const std::string& fileName);
    void stop();
    const StringList getAudioDevices(PortType type);
    uint32_t sampleRate();
    void connectToDevice(const std::string& targetDevice, PortType targetType);






    ~JackAudioClient();
    void open();
    void close();
    static int process (jack_nframes_t nframes, void *arg);
    static void jack_shutdown (void *arg);


    static jack_client_t *sJackClient;
    static jack_port_t *sInputPort;
    static jack_port_t *sOutputPort;

};

#endif // JACKAUDIOCLIENT_H
