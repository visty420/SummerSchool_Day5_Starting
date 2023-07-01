#pragma once

#include <vector>
#include "ImportExport.h"

namespace AudioEngine
{
	enum class AUDIOENGINE_API SignalType
	{
		Sin,
		Dirac,
		Square,
		Sum,
	};

	class AUDIOENGINE_API SignalGenerator
	{
	public:
		SignalGenerator(double time, size_t sampleRate, double freq);

		std::vector<double> CreateSignal(const SignalType type);

		const std::vector<double>& GetLastBuffer() const noexcept;

		size_t GetSampleRate() const noexcept;

	private:
		std::vector<double> CreateSin();
		std::vector<double> CreateDirac();
		std::vector<double> CreateSquare();
		std::vector<double> CreateSum();
		std::vector<double> CreateSumFiltered();

		const size_t m_size;
		const size_t m_sampleRate;
		const double m_freq;

		std::vector<double> m_buffer;
	};
}
