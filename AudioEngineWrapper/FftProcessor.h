#pragma once

#include "SignalGeneratorWrapper.h"
#include "AudioEngineWrapper.h"

namespace AudioEngineWrapper
{
  public ref class FftProcessor
  {
  public:

    array<double>^ GetMagnitude(SignalGenerator^ generator);

    array<double>^ GetMagnitude(AudioEngineService^ engine);
  };
}

