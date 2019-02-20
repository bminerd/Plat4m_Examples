cmake_minimum_required (VERSION 2.6)
project (Blinky_SystemLite_STM32F30x_App C CXX ASM)

set(PLAT4M_CORE_DIR     ${PROJECT_SOURCE_DIR}/../Plat4m_Core)
set(PLAT4M_MATH_DIR     ${PROJECT_SOURCE_DIR}/../Plat4m_Math)
set(PLAT4M_CONTROLS_DIR ${PROJECT_SOURCE_DIR}/../Plat4m_Controls)
set(PLAT4M_CMAKE_DIR    ${PROJECT_SOURCE_DIR}/../Plat4m_CMake)

include(${PLAT4M_CMAKE_DIR}/Plat4mMacros.cmake)

set(CMAKE_ASM_FLAGS "${CMAKE_ASM_FLAGS} -DSTM32F303xE -DUSE_STDPERIPH_DRIVER -DHSE_VALUE=8000000")
set(CMAKE_C_FLAGS   "${CMAKE_C_FLAGS}   -DSTM32F303xE -DUSE_STDPERIPH_DRIVER -DHSE_VALUE=8000000")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DSTM32F303xE -DUSE_STDPERIPH_DRIVER -DHSE_VALUE=8000000")

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -T\"${PROJECT_SOURCE_DIR}/Atollic/STM32F303RE_FLASH.ld\"")

include_directories(${PROJECT_SOURCE_DIR})
include_directories(${PROJECT_SOURCE_DIR}/Atollic)
include_directories(${PROJECT_SOURCE_DIR}/../)
include_directories(${PLAT4M_CORE_DIR}/STM32F30x)
include_directories(${PLAT4M_CORE_DIR}/STM32F30x/STM32F30x_DSP_StdPeriph_Lib_V1.2.3/Libraries/CMSIS/Include)
include_directories(${PLAT4M_CORE_DIR}/STM32F30x/STM32F30x_DSP_StdPeriph_Lib_V1.2.3/Libraries/CMSIS/Device/ST/STM32F30x/Include)
include_directories(${PLAT4M_CORE_DIR}/STM32F30x/STM32F30x_DSP_StdPeriph_Lib_V1.2.3/Libraries/STM32F30x_StdPeriph_Driver/inc)

set(source_files main.cpp
                 ${PROJECT_SOURCE_DIR}/Atollic/startup_stm32f303xe.s
                 ${PLAT4M_CORE_DIR}/Module.cpp
                 ${PLAT4M_CORE_DIR}/Processor.cpp
                 ${PLAT4M_CORE_DIR}/GpioPort.h
                 ${PLAT4M_CORE_DIR}/GpioPin.cpp
                 ${PLAT4M_CORE_DIR}/System.cpp
                 ${PLAT4M_CORE_DIR}/Thread.cpp
                 ${PLAT4M_CORE_DIR}/Mutex.cpp
                 ${PLAT4M_CORE_DIR}/WaitCondition.cpp
                 ${PLAT4M_CORE_DIR}/AllocationMemory.cpp
                 ${PLAT4M_CORE_DIR}/QueueDriver.cpp
                 ${PLAT4M_CORE_DIR}/STM32F30x/ProcessorSTM32F30x.cpp
                 ${PLAT4M_CORE_DIR}/STM32F30x/GpioPortSTM32F30x.cpp
                 ${PLAT4M_CORE_DIR}/STM32F30x/GpioPinSTM32F30x.cpp
                 ${PLAT4M_CORE_DIR}/STM32F30x/STM32F30x_DSP_StdPeriph_Lib_V1.2.3/Libraries/STM32F30x_StdPeriph_Driver/src/stm32f30x_rcc.c
                 ${PLAT4M_CORE_DIR}/SystemLite/SystemLite.cpp
                 ${PLAT4M_CORE_DIR}/SystemLite/ThreadLite.cpp
                 ${PLAT4M_CORE_DIR}/SystemLite/MutexLite.cpp
                 ${PLAT4M_CORE_DIR}/SystemLite/WaitConditionLite.cpp
                 ${PLAT4M_CORE_DIR}/SystemLite/SystemLiteCortexM/SystemLiteCortexM.cpp)

add_executable(Blinky_STM32F30x_App ${source_files})
