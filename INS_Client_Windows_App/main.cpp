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
// Copyright (c) 2018 Benjamin Minerd
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

#include <iostream>
#include <fstream>
#include <conio.h>

#include <Plat4m_Core/Plat4m.h>
#include <Plat4m_Core/AllocationMemoryLite/AllocationMemoryLite.h>
#include <Plat4m_Core/SystemWindows/SystemWindows.h>
#include <Plat4m_Core/SystemWindows/ProcessorWindows.h>
#include <Plat4m_Core/SystemWindows/SerialPortWindows.h>
#include <Plat4m_Core/Thread.h>
#include <Plat4m_Core/CallbackFunction.h>
#include <Plat4m_Core/CallbackFunctionParameter.h>
#include <Plat4m_Core/ComLinkTemplate.h>
#include <Plat4m_Core/ComProtocolPlat4m/ComProtocolPlat4mBinary.h>
#include <Plat4m_Core/ComProtocolPlat4m/ComProtocolPlat4mBinary.h>
#include <Plat4m_Core/InsServer/InsClient.h>

using namespace Plat4m;

static AllocationMemoryLite<40960> allocationMemory;

static SystemWindows systemWindows;

static ProcessorWindows processorWindows;

static SerialPortWindows serialPort("COM3");

static const SerialPort::Config serialPortConfig =
{
    115200,                                // .baudRate, 115.2 kb/s
    SerialPort::WORD_BITS_8,               // .wordBits
    SerialPort::STOP_BITS_1,               // .stopBits
    SerialPort::PARITY_BIT_NONE,           // .parityBit
    SerialPort::HARDWARE_FLOW_CONTROL_NONE // .hardwareFlowControl
};

static ComLinkTemplate<128, 128> comLink(serialPort);

static ComProtocolPlat4mBinary comProtocolPlat4mBinary(comLink);

static BinaryMessageFrameHandler binaryMessageFrameHandler(
                                                       comProtocolPlat4mBinary);

static InsClient insClient(comProtocolPlat4mBinary, binaryMessageFrameHandler);

//------------------------------------------------------------------------------
void threadCallback()
{
    printf("\nThread called!\n");
}

//------------------------------------------------------------------------------
void insMeasurementReadyCallback()
{
    Ins::Measurement insMeasurement;
    insClient.getMeasurement(insMeasurement);

    printf("\n"
           "Rotation (X,Y,Z): %f, %f, %f\n"
           "Rotation Rate (X,Y,Z): %f, %f, %f\n",
           insMeasurement.rotationXAngleDegrees,
           insMeasurement.rotationYAngleDegrees,
           insMeasurement.rotationZAngleDegrees,
           insMeasurement.rotationRateXAngularVelocityDps,
           insMeasurement.rotationRateYAngularVelocityDps,
           insMeasurement.rotationRateZAngularVelocityDps);
}

//------------------------------------------------------------------------------
int main(int argc, char* argv[])
{
    processorWindows.reset();

    Thread& thread = System::createThread(createCallback(&threadCallback),
                                          1000);
    thread.setEnabled(true);

    serialPort.setEnabled(true);
    serialPort.setConfig(serialPortConfig);

    insClient.setMeasurementReadyCallback(
                                  createCallback(&insMeasurementReadyCallback));
    insClient.setEnabled(true);

    comLink.setEnabled(true);

    systemWindows.run();

    return 0;
}
