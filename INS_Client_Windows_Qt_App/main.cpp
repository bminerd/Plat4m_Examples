/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the QtCore module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include <QApplication>
#include <QLabel>
#include <QSurfaceFormat>

#ifndef QT_NO_OPENGL
#include "mainwidget.h"
#include "mainwidgetkalman.h"
#endif

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
#include <Plat4m_Core/ImuServer/ImuClient.h>
#include <Plat4m_Core/InsServer/InsClient.h>

using namespace Plat4m;

static AllocationMemoryLite<4096000> allocationMemory;

static SystemWindows systemWindows;

static ProcessorWindows processorWindows;

static SerialPortWindows serialPort("COM4");

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

static ImuClient imuClient(comProtocolPlat4mBinary, binaryMessageFrameHandler);

static InsClient insClient(comProtocolPlat4mBinary, binaryMessageFrameHandler);

static MainWidget* widget = 0;
static MainWidgetKalman* widgetKalman = 0;

//------------------------------------------------------------------------------
void threadCallback()
{
    printf("\nThread called!\n");
}

//------------------------------------------------------------------------------
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QSurfaceFormat format;
    format.setDepthBufferSize(24);
    QSurfaceFormat::setDefaultFormat(format);

    app.setApplicationName("cube");
    app.setApplicationVersion("0.1");

#ifndef QT_NO_OPENGL
    widget = new MainWidget(insClient);
    widget->show();
    widget->resize(800, 600);
    widget->move(200, 200);

    widgetKalman = new MainWidgetKalman(imuClient);
    widgetKalman->show();
    widgetKalman->resize(800, 600);
    widgetKalman->move(1000, 200);

#else
    QLabel note("OpenGL Support required");
    note.show();
#endif

    // Plat4m initialization

    Thread& thread = System::createThread(createCallback(&threadCallback),
                                          1000);
    thread.setEnabled(true);

    serialPort.setEnabled(true);
    serialPort.setConfig(serialPortConfig);

    insClient.setEnabled(true);
    imuClient.setEnabled(true);

    comLink.setEnabled(true);

    return app.exec();
}
