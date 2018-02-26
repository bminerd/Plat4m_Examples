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
/// @file ApplicationInsServerApp.cpp
/// @author Ben Minerd
/// @date 12/13/2017
/// @brief ApplicationInsServerApp class source file.
///

//------------------------------------------------------------------------------
// Include files
//------------------------------------------------------------------------------

#include <ApplicationInsServerApp.h>
#include <Plat4m_Core/CallbackMethod.h>

using Plat4m::ApplicationInsServerApp;

using namespace Plat4m;

//------------------------------------------------------------------------------
// Private static data members
//------------------------------------------------------------------------------

const ProcessorSTM32F30x::Config ApplicationInsServerApp::myProcessorConfig =
{
    ProcessorSTM32F30x::CLOCK_SOURCE_EXTERNAL, // .clockSource
    72000000,                                  // .coreClockFrequencyHz, 72 MHz
    72000000,                                  // .ahbClockFrequencyHz,  72 MHz
    36000000,                                  // .apb1ClockFrequencyHz, 36 MHz
    72000000,                                  // .apb2ClockFrequencyHz, 72 MHz
    false,                                     // .isUsbOtgFs
    false,                                     // .isSdio
    false,                                     // .isRng
    false,                                     // .isEthernet
    FLASH_BASE                                 // .vectorTableAddress
};

const GpioPin::Config ApplicationInsServerApp::myLedGpioPinConfig =
{
    GpioPin::MODE_DIGITAL_OUTPUT_PUSH_PULL, // .mode
    GpioPin::RESISTOR_NONE                  // .resistor
};

const Uart::Config ApplicationInsServerApp::myUartConfig =
{
    115200,                          // .baudRate, 115.2 kb/s
    Uart::WORD_BITS_8,               // .wordBits
    Uart::STOP_BITS_1,               // .stopBits
    Uart::PARITY_NONE,               // .parity
    Uart::HARDWARE_FLOW_CONTROL_NONE // .hardwareFlowControl
};

const I2c::Config ApplicationInsServerApp::myImuI2cConfig =
{
    400000,             // .clockSpeedHz, 400 kb/s
    I2c::ADDRESS_BITS_7 // .addressBits
};

const Imu::Config ApplicationInsServerApp::myImuConfig =
{
    Imu::MEASUREMENT_MODE_CONTINUOUS, // .measurementMode
    2.0,                              // .accelMeasurementRangeAccelerationG
    104,                              // .accelMeasurementRateHz
    1000.0,                           // .gyroMeasurementRangeAngularVelocityDps
    104,                              // .gyroMeasurementRateHz
    0.0,                              // .magMeasurementRange
    0                                 // .magMeasurementRateHz
};

const ImuLSM6DS3::Config ApplicationInsServerApp::myImuLSM6DS3Config =
{
    // .accelAntiAliasingFilterBandwidth
    ImuLSM6DS3::ACCEL_ANTI_ALIASING_FILTER_BANDWIDTH_200_HZ,
    // .isAccelLowPassFilterEnabled
    true,
    // .accelLowPassFilterCutoffFrequency
    ImuLSM6DS3::ACCEL_LOW_PASS_FILTER_CUTOFF_FREQUENCY_ODR_XL_DIVIDE_BY_50,
    // .isGyroHighPassFilterEnabled
    false,
    // .gyroHighPassFilterCutoffFrequency
    ImuLSM6DS3::GYRO_HIGH_PASS_FILTER_CUTOFF_FREQUENCY_0_0081_HZ,
    // .readMode
    ImuLSM6DS3::READ_MODE_MAILBOX
};

//------------------------------------------------------------------------------
// Public constructors
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
ApplicationInsServerApp::ApplicationInsServerApp() :
    Application("INS_SERVER_APP", "INS_SERVER", "0.0.1"),
    myAllocationMemory(),
    mySystem(),
    myNucleoBoard(),
    myStImuEvalBoard(),
    myXNucleoBoard(),
    myProcessor(myNucleoBoard.getProcessor()),
    myInitializationThread(System::createThread(
       createCallback(this,
                      &ApplicationInsServerApp::initializationThreadCallback))),
    myLedGpioPin(myNucleoBoard.getGpioPin(
                                      BoardNucleoF303RE::GPIO_PIN_ID_USER_LED)),
    myImuI2c(myNucleoBoard.getI2c()),
    myGyroDataReadyExternalInterrupt(myNucleoBoard.getGpioPin(
                                    BoardNucleoF303RE::GPIO_PIN_ID_ARDUINO_A2)),
    myAccelDataReadyExternalInterrupt(myNucleoBoard.getGpioPin(
                                    BoardNucleoF303RE::GPIO_PIN_ID_ARDUINO_A3)),
    myImu(myStImuEvalBoard.getImu(myImuI2c,
                                  &myGyroDataReadyExternalInterrupt,
                                  &myAccelDataReadyExternalInterrupt)),
    myIns(myImu),
    myInterfaceUart(myNucleoBoard.getUart()),
    myInterfaceComLink(myInterfaceUart),
    myComProtocolPlat4m(myInterfaceComLink),
    myBinaryMessageFrameHandler(myComProtocolPlat4m),
    myImuServer(myComProtocolPlat4m,
                myBinaryMessageFrameHandler),
    myInsServer(myComProtocolPlat4m,
                myBinaryMessageFrameHandler),
    myLedThread(System::createThread(
                   createCallback(this, &ApplicationInsServerApp::ledThreadCallback),
                   500)),
    myImuThread(System::createThread(
                 createCallback(this, &ApplicationInsServerApp::imuThreadCallback))),
    myImuWaitCondition(System::createWaitCondition(myImuThread)),
    myIsImuAccelDataReady(false),
    myIsImuGyroDataReady(false)
{
}

//------------------------------------------------------------------------------
// Public virtual destructors
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
ApplicationInsServerApp::~ApplicationInsServerApp()
{
}

//------------------------------------------------------------------------------
// Private methods implemented from Application
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
void ApplicationInsServerApp::driverRun()
{
    initializeProcessor();

    myInitializationThread.setPriority(4);
    myInitializationThread.setEnabled(true);

    mySystem.run();
}

//------------------------------------------------------------------------------
// Private methods
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
void ApplicationInsServerApp::initializeProcessor()
{
    myProcessor.reset();
    myProcessor.setConfig(myProcessorConfig);
}

//------------------------------------------------------------------------------
void ApplicationInsServerApp::initializationThreadCallback()
{
    initializePeripherals();
    initializeSubsystems();
    initializeSystem();

    myInitializationThread.setEnabled(false);
}

//------------------------------------------------------------------------------
void ApplicationInsServerApp::initializePeripherals()
{
    GpioPinSTM32F30x::STM32F30xConfig gpioPinSTM32F30xConfig;
    gpioPinSTM32F30xConfig.outputSpeed = GpioPinSTM32F30x::OUTPUT_SPEED_50MHZ;

    myLedGpioPin.setEnabled(true);
    myLedGpioPin.configure(myLedGpioPinConfig);

    gpioPinSTM32F30xConfig.alternateFunction =
            GpioPinSTM32F30x::ALTERNATE_FUNCTION_7;
    gpioPinSTM32F30xConfig.outputType = GpioPinSTM32F30x::OUTPUT_TYPE_PUSH_PULL;
    myInterfaceUart.getTransmitGpioPin().setEnabled(true);
    myInterfaceUart.getTransmitGpioPin().setSTM32F30xConfig(
                                                        gpioPinSTM32F30xConfig);
    myInterfaceUart.getReceiveGpioPin()->setEnabled(true);
    myInterfaceUart.getReceiveGpioPin()->setSTM32F30xConfig(
                                                        gpioPinSTM32F30xConfig);

    myInterfaceUart.setEnabled(true);
    myInterfaceUart.setConfig(myUartConfig);

    gpioPinSTM32F30xConfig.alternateFunction =
            GpioPinSTM32F30x::ALTERNATE_FUNCTION_4;
    gpioPinSTM32F30xConfig.outputType =
            GpioPinSTM32F30x::OUTPUT_TYPE_OPEN_DRAIN;
    myImuI2c.getSclGpioPin().setEnabled(true);
    myImuI2c.getSclGpioPin().setSTM32F30xConfig(gpioPinSTM32F30xConfig);
    myImuI2c.getSdaGpioPin().setEnabled(true);
    myImuI2c.getSdaGpioPin().setSTM32F30xConfig(gpioPinSTM32F30xConfig);

    myImuI2c.setEnabled(true);
    myImuI2c.setConfig(myImuI2cConfig);
}

//------------------------------------------------------------------------------
void ApplicationInsServerApp::initializeSubsystems()
{
    myImu.setEnabled(true);
    myImu.setConfig(myImuConfig);
    myImu.setLSM6DS3Config(myImuLSM6DS3Config);

    myIns.setEnabled(true);
}

//------------------------------------------------------------------------------
void ApplicationInsServerApp::initializeSystem()
{
    myLedThread.setEnabled(true);

    myInterfaceComLink.setEnabled(true);

    myImuServer.setEnabled(true);
    myImuServer.addImu(myImu);

    ImuServer::Config imuServerConfig;
    imuServerConfig.outputRateDivisionFactor = 1;
    myImuServer.setConfig(imuServerConfig);

    myInsServer.setEnabled(true);
    myInsServer.addIns(myIns);

    myIns.setMeasurementReadyCallback(
        createCallback(this,
                       &ApplicationInsServerApp::imuAndInsMeasurementCallback));

    myImu.setAccelMeasurementReadyCallback(
          createCallback(this,
                   &ApplicationInsServerApp::imuAccelMeasurementReadyCallback));
    myImu.setGyroMeasurementReadyCallback(
          createCallback(this,
                    &ApplicationInsServerApp::imuGyroMeasurementReadyCallback));

    InsServer::Config insServerConfig;
    insServerConfig.outputRateDivisionFactor = 1;
    myInsServer.setConfig(insServerConfig);

    myImuThread.setPriority(3);
    myImuThread.setEnabled(true);
}

//------------------------------------------------------------------------------
void ApplicationInsServerApp::ledThreadCallback()
{
    myLedGpioPin.toggleLevel();
}

//------------------------------------------------------------------------------
void ApplicationInsServerApp::imuAccelMeasurementReadyCallback()
{
    myIsImuAccelDataReady = true;
    myImuWaitCondition.notifyFast();
}

//------------------------------------------------------------------------------
void ApplicationInsServerApp::imuGyroMeasurementReadyCallback()
{
    myIsImuGyroDataReady = true;
    myImuWaitCondition.notifyFast();
}

//------------------------------------------------------------------------------
void ApplicationInsServerApp::imuThreadCallback()
{
    myImuWaitCondition.wait();

    if (myIsImuAccelDataReady)
    {
        myIns.accelMeasurementReadyCallback();
        myIsImuAccelDataReady = false;
    }

    if (myIsImuGyroDataReady)
    {
        myIns.gyroMeasurementReadyCallback();
        myIsImuGyroDataReady = false;
    }
}

//------------------------------------------------------------------------------
void ApplicationInsServerApp::imuAndInsMeasurementCallback()
{
    // Put here until a better mechanism (ex. Observer pattern) exists for
    // Imu and Ins to notify their respective servers
    myImuServer.measurementReadyCallback();
    myInsServer.measurementReadyCallback();
}
