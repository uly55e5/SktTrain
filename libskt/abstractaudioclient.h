#ifndef AUDIOCLIENT_H
#define AUDIOCLIENT_H


class AbstractAudioClient
{
protected:
    AbstractAudioClient();
public:
    virtual ~AbstractAudioClient();
    static AbstractAudioClient * getInstance();
    virtual void play()=0;
    virtual void record()=0;
    virtual void stop()=0;
};

#endif // AUDIOCLIENT_H
