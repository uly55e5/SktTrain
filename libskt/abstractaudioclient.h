#ifndef AUDIOCLIENT_H
#define AUDIOCLIENT_H

#include <vector>
#include <string>
#include <fstream>
#include <inttypes.h>

class AbstractAudioClient
{
public:
  typedef std::vector<std::string> StringList;
  enum PortType {output,input} ;

   virtual ~AbstractAudioClient();
    static AbstractAudioClient * getInstance();
    virtual void playWav(const std::string& fileName)=0;
    virtual void recordWav(const std::string& filenName)=0;
    virtual void stop()=0;
    virtual const StringList getAudioDevices(PortType type)=0;
    virtual uint32_t sampleRate()=0;
    virtual void connectToDevice(const std::string& targetDevice, PortType targetType)=0;
protected:
    AbstractAudioClient();
    void writeWavHeader(std::fstream& stream);
    void readWavHeader(std::fstream& stream);


};

#endif // AUDIOCLIENT_H
