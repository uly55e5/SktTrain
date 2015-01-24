#include "jackaudioclient.h"

#include <iostream>

#include <jack/jack.h>
#include <exception>



jack_client_t *JackAudioClient::sJackClient=nullptr;
jack_port_t *JackAudioClient::sInputPort=nullptr;
jack_port_t *JackAudioClient::sOutputPort=nullptr;

JackAudioClient::JackAudioClient()
{
    open();
}

JackAudioClient*JackAudioClient::getInstance()
{
    static JackAudioClient instance;
    return &instance;
}

void JackAudioClient::playWav(const std::string &fileName)
{

}

void JackAudioClient::recordWav(const std::string &fileName)
{

}

void JackAudioClient::stop()
{

}

const AbstractAudioClient::StringList JackAudioClient::getAudioDevices(AbstractAudioClient::PortType type)
{
  std::cout << "Devices: " << std::endl;
  int flags;
  if(type==PortType::output)
    flags=JackPortIsPhysical|JackPortIsInput;
  else
    flags=JackPortIsPhysical|JackPortIsOutput;
  const char **ports;
  ports = jack_get_ports (sJackClient, NULL, NULL,
              flags);
  if (ports == NULL)
      throw std::exception();
  StringList result;
  int i=0;
  while(const char * s=ports[i])
    {
      std::cout << i << " : " << s << std::endl;
    result.push_back(s);
    i++;
    }
    return result;

}

uint32_t JackAudioClient::sampleRate()
{
  jack_nframes_t sr =	jack_get_sample_rate (sJackClient);
  std::cout << "Sample rate: " << sr << std::endl;
  return (uint32_t)sr;
}

void JackAudioClient::connectToDevice(const std::string &targetDevice, AbstractAudioClient::PortType targetType)
{
  std::cout << "Connect to: " << targetDevice << std::endl;
  jack_port_t *sourcePort;
  if(targetType==PortType::output)
    sourcePort=sOutputPort;
  else
    sourcePort=sInputPort;
  if (jack_connect (sJackClient, targetDevice.c_str(), jack_port_name (sourcePort)))
      throw std::exception();

}

JackAudioClient::~JackAudioClient()
{

    close();
}

void JackAudioClient::open()
{
    //const char **ports;
    const char *client_name = "skttrain";
    const char *server_name = nullptr;
    jack_options_t options = JackNullOption;
    jack_status_t status;

    sJackClient = jack_client_open (client_name, options, &status, server_name);
    if (sJackClient == nullptr)
        throw std::exception();

    // TODO set proccess callback
    jack_set_process_callback (sJackClient, JackAudioClient::process, 0);

    // TODO set shutdown callback
    jack_on_shutdown (sJackClient, JackAudioClient::jack_shutdown, 0);


    sInputPort = jack_port_register (sJackClient, "input",
                     JACK_DEFAULT_AUDIO_TYPE,
                     JackPortIsInput, 0);
    sOutputPort = jack_port_register (sJackClient, "output",
                      JACK_DEFAULT_AUDIO_TYPE,
                      JackPortIsOutput, 0);

    if ((sInputPort == NULL) || (sOutputPort == NULL))
        throw std::exception();


    if (jack_activate (sJackClient))
        throw std::exception();
}

void JackAudioClient::close()
{
    jack_client_close (sJackClient);
}

int JackAudioClient::process(jack_nframes_t nframes, void *arg)
{
    //std::cout << nframes << "..." << arg;
    jack_default_audio_sample_t *in, *out;

    in = (jack_default_audio_sample_t*) jack_port_get_buffer (sInputPort, nframes);
    out = (jack_default_audio_sample_t*) jack_port_get_buffer (sOutputPort, nframes);
    //std::memcpy (out, in,
    //    sizeof (jack_default_audio_sample_t) * nframes);

    return 0;
}

void JackAudioClient::jack_shutdown(void *arg)
{

}

