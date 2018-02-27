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
/// @file ApplicationInsServerApp.h
/// @author Ben Minerd
/// @date 12/13/2017
/// @brief ApplicationInsServerApp class header file.
///

#ifndef PLAT4M_APPLICATION_INS_SERVER_APP_H
#define PLAT4M_APPLICATION_INS_SERVER_APP_H

//------------------------------------------------------------------------------
// Includes
//------------------------------------------------------------------------------

#include <Plat4m_Core/Application.h>
#include <Plat4m_Core/AllocationMemoryLite/AllocationMemoryLite.h>
#include <Plat4m_Core/SystemFreeRtos/SystemFreeRtosCortexM.h>
#include <Plat4m_Core/BoardNucleoF303RE/BoardNucleoF303RE.h>
#include <Plat4m_Core/BoardStevalMKI160V1/BoardStevalMKI160V1.h>
#include <Plat4m_Core/BoardXNucleoIKS01A1/BoardXNucleoIKS01A1.h>
#include <Plat4m_Core/STM32F30x/ExternalInterruptSTM32F30x.h>
#include <Plat4m_Core/STM32F30x/UartSTM32F30x.h>
#include <Plat4m_Core/STM32F30x/I2cSTM32F30x.h>
#include <Plat4m_Core/ImuLSM6DS3/ImuLSM6DS3.h>
#include <Plat4m_Core/InsImu/InsImu.h>
#include <Plat4m_Core/STM32F30x/UartSTM32F30x.h>
#include <Plat4m_Core/ComInterfaceDevice.h>
#include <Plat4m_Core/ImuServer/ImuServer.h>
#include <Plat4m_Core/InsServer/InsServer.h>
#include <Plat4m_Core/Thread.h>
#include <Plat4m_Core/ComInterfaceDeviceTemplate.h>
#include <Plat4m_Core/ComLinkTemplate.h>
#include <Plat4m_Core/ComProtocolPlat4m/ComProtocolPlat4mBinary.h>
#include <Plat4m_Core/ComProtocolPlat4m/BinaryMessageFrameHandler.h>
#include <Plat4m_Core/WaitCondition.h>

//------------------------------------------------------------------------------
// Namespaces
//------------------------------------------------------------------------------

namespace Plat4m
{

//------------------------------------------------------------------------------
// Classes
//------------------------------------------------------------------------------

class ApplicationInsServerApp : public Application
{
public:

    //--------------------------------------------------------------------------
    // Public constructors
    //--------------------------------------------------------------------------

    ApplicationInsServerApp();

    //--------------------------------------------------------------------------
    // Public virtual destructors
    //--------------------------------------------------------------------------

    virtual ~ApplicationInsServerApp();

private:

    //--------------------------------------------------------------------------
    // Private static data members
    //--------------------------------------------------------------------------

    // Constants

    static const ProcessorSTM32F30x::Config myProcessorConfig;

    static const GpioPin::Config myLedGpioPinConfig;

    static const Uart::Config myUartConfig;

    static const I2c::Config myImuI2cConfig;

    static const Imu::Config myImuConfig;

    static const Accel::Config myImuAccelConfig;

    static const Gyro::Config myImuGyroConfig;

    static const ImuLSM6DS3::Config myImuLSM6DS3Config;

    static const AngleRadians myXRotationAngleRadians;

    static const AngleRadians myYRotationAngleRadians;

    static const AngleRadians myZRotationAngleRadians;

    //--------------------------------------------------------------------------
    // Private data members
    //--------------------------------------------------------------------------

    AllocationMemoryLite<48000> myAllocationMemory;

    SystemFreeRtosCortexM mySystem;

    BoardNucleoF303RE myNucleoBoard;

    BoardStevalMKI160V1 myStImuEvalBoard;

    BoardXNucleoIKS01A1 myXNucleoBoard;

    ProcessorSTM32F30x& myProcessor;

    Thread& myInitializationThread;

    GpioPinSTM32F30x& myLedGpioPin;

    I2cSTM32F30x& myImuI2c;

    ExternalInterruptSTM32F30x myGyroDataReadyExternalInterrupt;

    ExternalInterruptSTM32F30x myAccelDataReadyExternalInterrupt;

    ImuLSM6DS3& myImu;

    InsImu myIns;

    UartSTM32F30x& myInterfaceUart;

    ComInterfaceDeviceTemplate<128, 128> myInterfaceComInterfaceDevice;

    ComLinkTemplate<256, 256> myInterfaceComLink;

    ComProtocolPlat4mBinary myComProtocolPlat4m;

    BinaryMessageFrameHandler myBinaryMessageFrameHandler;

    ImuServer myImuServer;

    InsServer myInsServer;

    Thread& myLedThread;

    Thread& myImuThread;

    WaitCondition& myImuWaitCondition;

    bool myIsImuAccelDataReady;

    bool myIsImuGyroDataReady;

    //--------------------------------------------------------------------------
    // Private methods implemented from Application
    //--------------------------------------------------------------------------

    void driverRun();

    //--------------------------------------------------------------------------
    // Private methods
    //--------------------------------------------------------------------------

    void initializeProcessor();

    void initializationThreadCallback();

    void initializePeripherals();

    void initializeSubsystems();

    void initializeSystem();

    void ledThreadCallback();

    void imuAccelMeasurementReadyCallback();

    void imuGyroMeasurementReadyCallback();

    void imuThreadCallback();

    void imuAndInsMeasurementCallback();
};

}; // namespace Plat4m

#endif // PLAT4M_APPLICATION_INS_SERVER_APP_H

