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

JackAudioClient& JackAudioClient::getInstance()
{
    static JackAudioClient instance;
    return instance;
}

void JackAudioClient::play()
{

}

void JackAudioClient::record()
{

}

void JackAudioClient::stop()
{

}

JackAudioClient::~JackAudioClient()
{
    close();
}

void JackAudioClient::open()
{
    const char **ports;
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

    // TODO get sample rate
    jack_nframes_t sr =	jack_get_sample_rate (sJackClient);
    std::cout << "Sample rate: " << sr << std::endl;

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


    ports = jack_get_ports (sJackClient, NULL, NULL,
                JackPortIsPhysical|JackPortIsOutput);
    if (ports == NULL)
        throw std::exception();

    if (jack_connect (sJackClient, ports[0], jack_port_name (sInputPort)))
        throw std::exception();

    delete ports;

    ports = jack_get_ports (sJackClient, NULL, NULL,
                JackPortIsPhysical|JackPortIsInput);
    if (ports == NULL)
        throw std::exception();

    if (jack_connect (sJackClient, jack_port_name (sOutputPort), ports[0]))
        throw std::exception();

    delete ports;
}

void JackAudioClient::close()
{
    jack_client_close (sJackClient);
}

int JackAudioClient::process(jack_nframes_t nframes, void *arg)
{
    std::cout << nframes << "..." << arg;
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

