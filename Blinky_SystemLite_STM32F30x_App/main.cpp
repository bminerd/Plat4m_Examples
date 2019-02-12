//------------------------------------------------------------------------------
//       _______    __                           ___
//      ||  ___ \  || |             __          //  |
//      || |  || | || |   _______  || |__      //   |    _____  ___
//      || |__|| | || |  // ___  | ||  __|    // _  |   ||  _ \/ _ \
//      ||  ____/  || | || |  || | || |      // /|| |   || |\\  /\\ \
//      || |       || | || |__|| | || |     // /_|| |_  || | || | || |
//      || |       || |  \\____  | || |__  //_____   _| || | || | || |
//      ||_|       ||_|       ||_|  \\___|       ||_|   ||_| ||_| ||_|
//
//
// The MIT License (MIT)
//
// Copyright (c) 2017 Benjamin Minerd
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//------------------------------------------------------------------------------

///
/// @file main.cpp
/// @author Ben Minerd
/// @date 11/20/2017
/// @brief Main source file for Blinky_SystemLite_STM32F30x_App.
///

#include <Plat4m_Core/Plat4m.h>
#include <Plat4m_Core/AllocationMemoryLite/AllocationMemoryLite.h>
#include <Plat4m_Core/SystemLite/SystemLiteCortexM/SystemLiteCortexM.h>
#include <Plat4m_Core/STM32F30x/ProcessorSTM32F30x.h>
#include <Plat4m_Core/STM32F30x/GpioPortSTM32F30x.h>
#include <Plat4m_Core/STM32F30x/GpioPinSTM32F30x.h>
#include <Plat4m_Core/CallbackFunction.h>

using namespace Plat4m;

static SystemLiteCortexM system;

static AllocationMemoryLite<256> allocationMemory;

static ProcessorSTM32F30x processor(3.3, 8000000);

static const ProcessorSTM32F30x::Config processorConfig =
{
	ProcessorSTM32F30x::CLOCK_SOURCE_EXTERNAL, // .clockSource
	72000000, 								   // .coreClockFrequencyHz, 72 MHz
	72000000, 								   // .ahbClockFrequencyHz,  72 MHz
	36000000, 								   // .apb1ClockFrequencyHz, 36 MHz
	72000000, 								   // .apb2ClockFrequencyHz, 72 MHz
	false,									   // .isUsbOtgFs
	false,									   // .isSdio
	false,									   // .isRng
	false,									   // .isEthernet
	FLASH_BASE								   // .vectorTableAddress
};

static GpioPortSTM32F30x ledGpioPort(GpioPortSTM32F30x::ID_A);

static GpioPinSTM32F30x ledGpioPin(ledGpioPort, GpioPinSTM32F30x::ID_5);

//------------------------------------------------------------------------------
void ledThreadCallback()
{
	ledGpioPin.toggleLevel();
}

//------------------------------------------------------------------------------
int main()
{
	// Configure Processor

	processor.reset();
	processor.setConfig(processorConfig);

	// Configure LED GpioPin

	GpioPin::Config gpioConfig;
	gpioConfig.mode     = GpioPin::MODE_DIGITAL_OUTPUT_PUSH_PULL;
	gpioConfig.resistor = GpioPin::RESISTOR_PULL_DOWN;

	ledGpioPin.enable(true);
	ledGpioPin.configure(gpioConfig);

	Thread& thread = System::createThread(createCallback(&ledThreadCallback),
										  500);
	thread.setEnabled(true);

	system.enableSystemClock(72000000);
	system.run();

    return 0;
}
