#include "SignalGenerator.h"
#include <numbers>
#include <cmath>

namespace AudioEngine
{
    SignalGenerator::SignalGenerator(double time, size_t sampleRate, double freq)
        : m_size(time* sampleRate), m_sampleRate(sampleRate), m_freq(freq)
    {

    }

    const std::vector<double>& SignalGenerator::CreateSignal(const SignalType type)
    {
        switch (type)
        {
        case SignalType::Sin:
            return CreateSin();
        case SignalType::Dirac:
            return CreateDirac();
        case SignalType::Square:
            return CreateSquare();
        case SignalType::Sum:
            return CreateSum();
        case SignalType::SquareWithSums:
            return CreateSquareWithSums();
        default:
            throw std::exception("unknown type");
        }
    }

    const std::vector<double>& SignalGenerator::GetLastBuffer() const noexcept
    {
        return m_buffer;
    }

    size_t SignalGenerator::GetSampleRate() const noexcept
    {
        return m_sampleRate;
    }

    const std::vector<double>& SignalGenerator::CreateSin()
    {
        m_buffer = std::vector<double>(m_size);

        for (size_t i = 0; i < m_size; i++)
        {
            m_buffer[i] = std::sin(((double)i / m_sampleRate) * 2 * std::numbers::pi * m_freq) * 100;
        }

        return m_buffer;
    }

    const std::vector<double>& SignalGenerator::CreateDirac()
    {
        m_buffer = std::vector<double>(m_size);

        m_buffer[1000] = 1000;

        return m_buffer;
    }

    const std::vector<double>& SignalGenerator::CreateSquare()
    {
        m_buffer = std::vector<double>(m_size);

        for (size_t i = 0; i < m_size; i++)
        {
            m_buffer[i] = std::sin(((double)i / m_sampleRate) * 2 * std::numbers::pi * m_freq) * 100 > 0 ? 1 : -1;
        }

        return m_buffer;
    }

    const std::vector<double>& SignalGenerator::CreateSum()
    {
        m_buffer = std::vector<double>(m_size);

        for (size_t i = 0; i < m_size; i++)
        {
            m_buffer[i] = (std::sin(((double)i / m_sampleRate) * 2 * std::numbers::pi * m_freq) * 100) +
                (std::sin(((double)i / m_sampleRate) * 2 * std::numbers::pi * m_freq * 100) * 50);
        }

        return m_buffer;
    }

    const std::vector<double>& SignalGenerator::CreateSquareWithSums()
    {
        m_buffer = std::vector<double>(m_size);

        for (size_t i = 0; i < m_size; i++)
        {
            double freq = 5;
            double amplitude = 100;

            for (size_t j = 1; j < 20; j += 2)
            {
                m_buffer[i] += std::sin(((double)i / m_sampleRate) * 2 * std::numbers::pi * freq * j) * (amplitude / j);
            }
        }

        return m_buffer;
    }
}
