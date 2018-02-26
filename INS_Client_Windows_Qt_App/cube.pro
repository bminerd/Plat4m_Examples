QT       += core gui widgets

TARGET = cube
TEMPLATE = app

SOURCES += main.cpp \
    geometryengine.cpp \
    main.cpp \
    mainwidget.cpp \
    ../Plat4m_Core/Accel.cpp \
    ../Plat4m_Core/Adc.cpp \
    ../Plat4m_Core/AllocationMemory.cpp \
    ../Plat4m_Core/AnalogInput.cpp \
    ../Plat4m_Core/Application.cpp \
    ../Plat4m_Core/Board.cpp \
    ../Plat4m_Core/Bootloader.cpp \
    ../Plat4m_Core/Button.cpp \
    ../Plat4m_Core/ByteArray.cpp \
    ../Plat4m_Core/ByteArrayParser.cpp \
    ../Plat4m_Core/Can.cpp \
    ../Plat4m_Core/ComInterface.cpp \
    ../Plat4m_Core/ComInterfaceDevice.cpp \
    ../Plat4m_Core/ComLink.cpp \
    ../Plat4m_Core/Compass.cpp \
    ../Plat4m_Core/ComProtocol.cpp \
    ../Plat4m_Core/CurrentSensor.cpp \
    ../Plat4m_Core/Dac.cpp \
    ../Plat4m_Core/DacIc.cpp \
    ../Plat4m_Core/DigitalFilter.cpp \
    ../Plat4m_Core/Display.cpp \
    ../Plat4m_Core/EnableLine.cpp \
    ../Plat4m_Core/ExternalInterrupt.cpp \
    ../Plat4m_Core/Font.cpp \
    ../Plat4m_Core/GpioPin.cpp \
    ../Plat4m_Core/Gyro.cpp \
    ../Plat4m_Core/HardwareTimer.cpp \
    ../Plat4m_Core/I2c.cpp \
    ../Plat4m_Core/I2cDevice.cpp \
    ../Plat4m_Core/Imu.cpp \
    ../Plat4m_Core/InputCaptureTimer.cpp \
    ../Plat4m_Core/Ins.cpp \
    ../Plat4m_Core/Interrupt.cpp \
    ../Plat4m_Core/InterruptPolicy.cpp \
    ../Plat4m_Core/IoExpander.cpp \
    ../Plat4m_Core/MasterSlaveBus.cpp \
    ../Plat4m_Core/Module.cpp \
    ../Plat4m_Core/Mutex.cpp \
    ../Plat4m_Core/MutexLock.cpp \
    ../Plat4m_Core/PowerSupply.cpp \
    ../Plat4m_Core/Processor.cpp \
    ../Plat4m_Core/PwmOutput.cpp \
    ../Plat4m_Core/QueueDriver.cpp \
    ../Plat4m_Core/RotaryEncoder.cpp \
    ../Plat4m_Core/RotarySwitch.cpp \
    ../Plat4m_Core/SerialPort.cpp \
    ../Plat4m_Core/SlaveDevice.cpp \
    ../Plat4m_Core/Spi.cpp \
    ../Plat4m_Core/SpiDevice.cpp \
    ../Plat4m_Core/Subsystem.cpp \
    ../Plat4m_Core/System.cpp \
    ../Plat4m_Core/Thread.cpp \
    ../Plat4m_Core/Timer.cpp \
    ../Plat4m_Core/Uart.cpp \
    ../Plat4m_Core/Ui.cpp \
    ../Plat4m_Core/UiAction.cpp \
    ../Plat4m_Core/UiInput.cpp \
    ../Plat4m_Core/UiState.cpp \
    ../Plat4m_Core/Usb.cpp \
    ../Plat4m_Core/WaitCondition.cpp \
    ../Plat4m_Core/ComProtocolPlat4m/AsciiMessage.cpp \
    ../Plat4m_Core/ComProtocolPlat4m/AsciiMessageHandler.cpp \
    ../Plat4m_Core/ComProtocolPlat4m/BinaryMessage.cpp \
    ../Plat4m_Core/ComProtocolPlat4m/BinaryMessageFrameHandler.cpp \
    ../Plat4m_Core/ComProtocolPlat4m/BinaryMessageHandler.cpp \
    ../Plat4m_Core/ComProtocolPlat4m/BinaryMessageHandlerGroup.cpp \
    ../Plat4m_Core/ComProtocolPlat4m/BinaryMessageServer.cpp \
    ../Plat4m_Core/ComProtocolPlat4m/ComProtocolPlat4mAscii.cpp \
    ../Plat4m_Core/ComProtocolPlat4m/ComProtocolPlat4mBinary.cpp \
    ../Plat4m_Core/ComProtocolPlat4m/Frame.cpp \
    ../Plat4m_Core/ComProtocolPlat4m/FrameHandler.cpp \
    ../Plat4m_Core/ComProtocolPlat4m/Message.cpp \
    ../Plat4m_Core/ComProtocolPlat4m/Packet.cpp \
    ../Plat4m_Core/ComProtocolPlat4m/PacketFrameHandler.cpp \
    ../Plat4m_Core/ImuServer/ImuClient.cpp \
    ../Plat4m_Core/ImuServer/ImuGetConfigAsciiMessage.cpp \
    ../Plat4m_Core/ImuServer/ImuGetConfigBinaryMessage.cpp \
    ../Plat4m_Core/ImuServer/ImuGetConfigResponseAsciiMessage.cpp \
    ../Plat4m_Core/ImuServer/ImuGetConfigResponseBinaryMessage.cpp \
    ../Plat4m_Core/ImuServer/ImuGetMeasurementAsciiMessage.cpp \
    ../Plat4m_Core/ImuServer/ImuGetMeasurementBinaryMessage.cpp \
    ../Plat4m_Core/ImuServer/ImuMeasurementAsciiMessage.cpp \
    ../Plat4m_Core/ImuServer/ImuMeasurementBinaryMessage.cpp \
    ../Plat4m_Core/ImuServer/ImuServer.cpp \
    ../Plat4m_Core/ImuServer/ImuServerGetConfigAsciiMessage.cpp \
    ../Plat4m_Core/ImuServer/ImuServerGetConfigBinaryMessage.cpp \
    ../Plat4m_Core/ImuServer/ImuServerGetConfigResponseAsciiMessage.cpp \
    ../Plat4m_Core/ImuServer/ImuServerGetConfigResponseBinaryMessage.cpp \
    ../Plat4m_Core/ImuServer/ImuServerMeasurementAsciiMessage.cpp \
    ../Plat4m_Core/ImuServer/ImuServerSetConfigAsciiMessage.cpp \
    ../Plat4m_Core/ImuServer/ImuServerSetConfigBinaryMessage.cpp \
    ../Plat4m_Core/ImuServer/ImuServerSetConfigResponseAsciiMessage.cpp \
    ../Plat4m_Core/ImuServer/ImuServerSetConfigResponseBinaryMessage.cpp \
    ../Plat4m_Core/ImuServer/ImuSetConfigAsciiMessage.cpp \
    ../Plat4m_Core/ImuServer/ImuSetConfigBinaryMessage.cpp \
    ../Plat4m_Core/ImuServer/ImuSetConfigResponseAsciiMessage.cpp \
    ../Plat4m_Core/ImuServer/ImuSetConfigResponseBinaryMessage.cpp \
    ../Plat4m_Core/InsServer/InsClient.cpp \
    ../Plat4m_Core/InsServer/InsMeasurementBinaryMessage.cpp \
    ../Plat4m_Core/InsServer/InsServer.cpp \
    ../Plat4m_Core/InsServer/InsServerGetConfigBinaryMessage.cpp \
    ../Plat4m_Core/InsServer/InsServerGetConfigResponseBinaryMessage.cpp \
    ../Plat4m_Core/InsServer/InsServerSetConfigBinaryMessage.cpp \
    ../Plat4m_Core/InsServer/InsServerSetConfigResponseBinaryMessage.cpp \
    ../Plat4m_Core/SystemWindows/MutexWindows.cpp \
    ../Plat4m_Core/SystemWindows/ProcessorWindows.cpp \
    ../Plat4m_Core/SystemWindows/QueueDriverWindows.cpp \
    ../Plat4m_Core/SystemWindows/SerialPortWindows.cpp \
    ../Plat4m_Core/SystemWindows/SystemWindows.cpp \
    ../Plat4m_Core/SystemWindows/ThreadWindows.cpp \
    ../Plat4m_Core/SystemWindows/WaitConditionWindows.cpp

SOURCES += \
    mainwidget.cpp \
    geometryengine.cpp

HEADERS += \
    mainwidget.h \
    geometryengine.h \
    geometryengine.h \
    mainwidget.h \
    ../Plat4m_Core/Accel.h \
    ../Plat4m_Core/Adc.h \
    ../Plat4m_Core/AllocationMemory.h \
    ../Plat4m_Core/AnalogInput.h \
    ../Plat4m_Core/Application.h \
    ../Plat4m_Core/Array.h \
    ../Plat4m_Core/ArrayN.h \
    ../Plat4m_Core/Board.h \
    ../Plat4m_Core/Bootloader.h \
    ../Plat4m_Core/Buffer.h \
    ../Plat4m_Core/BufferN.h \
    ../Plat4m_Core/Button.h \
    ../Plat4m_Core/ByteArray.h \
    ../Plat4m_Core/ByteArrayN.h \
    ../Plat4m_Core/ByteArrayParser.h \
    ../Plat4m_Core/Callback.h \
    ../Plat4m_Core/CallbackFunction.h \
    ../Plat4m_Core/CallbackFunctionParameter.h \
    ../Plat4m_Core/CallbackMethod.h \
    ../Plat4m_Core/CallbackMethod2Parameters.h \
    ../Plat4m_Core/CallbackMethodParameter.h \
    ../Plat4m_Core/Can.h \
    ../Plat4m_Core/ComInterface.h \
    ../Plat4m_Core/ComInterfaceDevice.h \
    ../Plat4m_Core/ComInterfaceDeviceTemplate.h \
    ../Plat4m_Core/ComLink.h \
    ../Plat4m_Core/ComLinkTemplate.h \
    ../Plat4m_Core/Compass.h \
    ../Plat4m_Core/ComProtocol.h \
    ../Plat4m_Core/Crc.h \
    ../Plat4m_Core/CurrentSensor.h \
    ../Plat4m_Core/Dac.h \
    ../Plat4m_Core/DacIc.h \
    ../Plat4m_Core/DigitalFilter.h \
    ../Plat4m_Core/Display.h \
    ../Plat4m_Core/EnableLine.h \
    ../Plat4m_Core/EncryptedMemory.h \
    ../Plat4m_Core/ErrorTemplate.h \
    ../Plat4m_Core/ExternalInterrupt.h \
    ../Plat4m_Core/Font.h \
    ../Plat4m_Core/GpioPin.h \
    ../Plat4m_Core/GpioPort.h \
    ../Plat4m_Core/Gyro.h \
    ../Plat4m_Core/HardwareTimer.h \
    ../Plat4m_Core/I2c.h \
    ../Plat4m_Core/I2cDevice.h \
    ../Plat4m_Core/Imu.h \
    ../Plat4m_Core/InputCaptureTimer.h \
    ../Plat4m_Core/Ins.h \
    ../Plat4m_Core/Interrupt.h \
    ../Plat4m_Core/InterruptPolicy.h \
    ../Plat4m_Core/IoExpander.h \
    ../Plat4m_Core/List.h \
    ../Plat4m_Core/MasterSlaveBus.h \
    ../Plat4m_Core/Memory.h \
    ../Plat4m_Core/MemoryRegion.h \
    ../Plat4m_Core/Module.h \
    ../Plat4m_Core/Mutex.h \
    ../Plat4m_Core/MutexLock.h \
    ../Plat4m_Core/Plat4m.h \
    ../Plat4m_Core/Point.h \
    ../Plat4m_Core/PowerSupply.h \
    ../Plat4m_Core/Processor.h \
    ../Plat4m_Core/PwmOutput.h \
    ../Plat4m_Core/Queue.h \
    ../Plat4m_Core/QueueDriver.h \
    ../Plat4m_Core/RotaryEncoder.h \
    ../Plat4m_Core/RotarySwitch.h \
    ../Plat4m_Core/SerialPort.h \
    ../Plat4m_Core/SlaveDevice.h \
    ../Plat4m_Core/Spi.h \
    ../Plat4m_Core/SpiDevice.h \
    ../Plat4m_Core/Subsystem.h \
    ../Plat4m_Core/System.h \
    ../Plat4m_Core/Thread.h \
    ../Plat4m_Core/Timer.h \
    ../Plat4m_Core/Uart.h \
    ../Plat4m_Core/Ui.h \
    ../Plat4m_Core/UiAction.h \
    ../Plat4m_Core/UiInput.h \
    ../Plat4m_Core/UiState.h \
    ../Plat4m_Core/Usb.h \
    ../Plat4m_Core/WaitCondition.h \
    ../Plat4m_Core/ComProtocolPlat4m/AsciiMessage.h \
    ../Plat4m_Core/ComProtocolPlat4m/AsciiMessageHandler.h \
    ../Plat4m_Core/ComProtocolPlat4m/AsciiMessageHandlerTemplate.h \
    ../Plat4m_Core/ComProtocolPlat4m/BinaryMessage.h \
    ../Plat4m_Core/ComProtocolPlat4m/BinaryMessageFrameHandler.h \
    ../Plat4m_Core/ComProtocolPlat4m/BinaryMessageHandler.h \
    ../Plat4m_Core/ComProtocolPlat4m/BinaryMessageHandlerGroup.h \
    ../Plat4m_Core/ComProtocolPlat4m/BinaryMessageHandlerTemplate.h \
    ../Plat4m_Core/ComProtocolPlat4m/BinaryMessageServer.h \
    ../Plat4m_Core/ComProtocolPlat4m/ComProtocolPlat4mAscii.h \
    ../Plat4m_Core/ComProtocolPlat4m/ComProtocolPlat4mBinary.h \
    ../Plat4m_Core/ComProtocolPlat4m/Frame.h \
    ../Plat4m_Core/ComProtocolPlat4m/FrameHandler.h \
    ../Plat4m_Core/ComProtocolPlat4m/Message.h \
    ../Plat4m_Core/ComProtocolPlat4m/Packet.h \
    ../Plat4m_Core/ComProtocolPlat4m/PacketFrameHandler.h \
    ../Plat4m_Core/AllocationMemoryLite/AllocationMemoryLite.h \
    ../Plat4m_Core/ImuServer/ImuClient.h \
    ../Plat4m_Core/ImuServer/ImuGetConfigAsciiMessage.h \
    ../Plat4m_Core/ImuServer/ImuGetConfigBinaryMessage.h \
    ../Plat4m_Core/ImuServer/ImuGetConfigMessage.h \
    ../Plat4m_Core/ImuServer/ImuGetConfigResponseAsciiMessage.h \
    ../Plat4m_Core/ImuServer/ImuGetConfigResponseBinaryMessage.h \
    ../Plat4m_Core/ImuServer/ImuGetConfigResponseMessage.h \
    ../Plat4m_Core/ImuServer/ImuGetMeasurementAsciiMessage.h \
    ../Plat4m_Core/ImuServer/ImuGetMeasurementBinaryMessage.h \
    ../Plat4m_Core/ImuServer/ImuGetMeasurementMessage.h \
    ../Plat4m_Core/ImuServer/ImuMeasurementAsciiMessage.h \
    ../Plat4m_Core/ImuServer/ImuMeasurementBinaryMessage.h \
    ../Plat4m_Core/ImuServer/ImuMeasurementMessage.h \
    ../Plat4m_Core/ImuServer/ImuServer.h \
    ../Plat4m_Core/ImuServer/ImuServerBinaryMessages.h \
    ../Plat4m_Core/ImuServer/ImuServerGetConfigAsciiMessage.h \
    ../Plat4m_Core/ImuServer/ImuServerGetConfigBinaryMessage.h \
    ../Plat4m_Core/ImuServer/ImuServerGetConfigMessage.h \
    ../Plat4m_Core/ImuServer/ImuServerGetConfigResponseAsciiMessage.h \
    ../Plat4m_Core/ImuServer/ImuServerGetConfigResponseBinaryMessage.h \
    ../Plat4m_Core/ImuServer/ImuServerGetConfigResponseMessage.h \
    ../Plat4m_Core/ImuServer/ImuServerMeasurementAsciiMessage.h \
    ../Plat4m_Core/ImuServer/ImuServerMeasurementMessage.h \
    ../Plat4m_Core/ImuServer/ImuServerSetConfigAsciiMessage.h \
    ../Plat4m_Core/ImuServer/ImuServerSetConfigBinaryMessage.h \
    ../Plat4m_Core/ImuServer/ImuServerSetConfigMessage.h \
    ../Plat4m_Core/ImuServer/ImuServerSetConfigResponseAsciiMessage.h \
    ../Plat4m_Core/ImuServer/ImuServerSetConfigResponseBinaryMessage.h \
    ../Plat4m_Core/ImuServer/ImuServerSetConfigResponseMessage.h \
    ../Plat4m_Core/ImuServer/ImuSetConfigAsciiMessage.h \
    ../Plat4m_Core/ImuServer/ImuSetConfigBinaryMessage.h \
    ../Plat4m_Core/ImuServer/ImuSetConfigMessage.h \
    ../Plat4m_Core/ImuServer/ImuSetConfigResponseAsciiMessage.h \
    ../Plat4m_Core/ImuServer/ImuSetConfigResponseBinaryMessage.h \
    ../Plat4m_Core/ImuServer/ImuSetConfigResponseMessage.h \
    ../Plat4m_Core/ImuServer/LowPassFilter_IRR.h \
    ../Plat4m_Core/InsServer/InsClient.h \
    ../Plat4m_Core/InsServer/InsMeasurementBinaryMessage.h \
    ../Plat4m_Core/InsServer/InsMeasurementMessage.h \
    ../Plat4m_Core/InsServer/InsServer.h \
    ../Plat4m_Core/InsServer/InsServerBinaryMessages.h \
    ../Plat4m_Core/InsServer/InsServerGetConfigBinaryMessage.h \
    ../Plat4m_Core/InsServer/InsServerGetConfigMessage.h \
    ../Plat4m_Core/InsServer/InsServerGetConfigResponseBinaryMessage.h \
    ../Plat4m_Core/InsServer/InsServerGetConfigResponseMessage.h \
    ../Plat4m_Core/InsServer/InsServerSetConfigBinaryMessage.h \
    ../Plat4m_Core/InsServer/InsServerSetConfigMessage.h \
    ../Plat4m_Core/InsServer/InsServerSetConfigResponseBinaryMessage.h \
    ../Plat4m_Core/InsServer/InsServerSetConfigResponseMessage.h \
    ../Plat4m_Core/SystemWindows/MutexWindows.h \
    ../Plat4m_Core/SystemWindows/ProcessorWindows.h \
    ../Plat4m_Core/SystemWindows/QueueDriverWindows.h \
    ../Plat4m_Core/SystemWindows/SerialPortWindows.h \
    ../Plat4m_Core/SystemWindows/SystemWindows.h \
    ../Plat4m_Core/SystemWindows/ThreadWindows.h \
    ../Plat4m_Core/SystemWindows/WaitConditionWindows.h

RESOURCES += \
    shaders.qrc \
    textures.qrc

# install
target.path = $$[QT_INSTALL_EXAMPLES]/opengl/cube
INSTALLS += target

DISTFILES +=