#include "pch.h"
#include "SignalGeneratorWrapper.h"
#include "Utils.h"

namespace AudioEngineWrapper
{
    SignalGenerator::SignalGenerator(double time, unsigned int sampleRate, double freq) 
        : m_generator(new AudioEngine::SignalGenerator(time, sampleRate, freq))
    {

    }

    array<double>^ SignalGenerator::Generate(SignalType type)
    {
        try
        {
            auto buffer = m_generator->CreateSignal((AudioEngine::SignalType)type);
            return Utils::ConvertToMananged(buffer, buffer.size());
        }
        catch (const std::exception& e)
        {
            throw gcnew System::Exception(gcnew System::String(e.what()));
        }
    }

    SignalGenerator::~SignalGenerator()
    {
        delete m_generator;
        m_generator = nullptr;
    }

    SignalGenerator::!SignalGenerator()
    {
        if (m_generator != nullptr)
        {
            delete m_generator;
        }
    }

    std::vector<double> SignalGenerator::GetBuffer()
    {
      return m_generator->GetLastBuffer();
    }

    int SignalGenerator::SampleRate::get()
    {
        return (int)m_generator->GetSampleRate();
    }
}
