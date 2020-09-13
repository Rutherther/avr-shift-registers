cmake_minimum_required(VERSION 3.18)

set(AVR_UPLOADTOOL avrdude)
set(AVR_PROGRAMMER usbasp)
set(AVR_UPLOADTOOL_PORT usb)

project(SIMAVR_SR)

set(AVR_MCU atmega8)
set(AVR_H_FUSE 0xd9)
set(AVR_L_FUSE 0xc3)

set(CMAKE_BUILD_TYPE Release)

set(MCU_SPEED "4000000UL")

if(DEFINED ENV{AVR_FIND_ROOT_PATH})
    set(CMAKE_FIND_ROOT_PATH $ENV{AVR_FIND_ROOT_PATH})
else(DEFINED ENV{AVR_FIND_ROOT_PATH})
    if(EXISTS "/opt/local/avr")
      set(CMAKE_FIND_ROOT_PATH "/opt/local/avr")
    elseif(EXISTS "/usr/avr")
      set(CMAKE_FIND_ROOT_PATH "/usr/avr")
    elseif(EXISTS "/usr/lib/avr")
      set(CMAKE_FIND_ROOT_PATH "/usr/lib/avr")
    elseif(EXISTS "/usr/local/CrossPack-AVR")
      set(CMAKE_FIND_ROOT_PATH "/usr/local/CrossPack-AVR")
    else(EXISTS "/opt/local/avr")
      message(FATAL_ERROR "Please set AVR_FIND_ROOT_PATH in your environment.")
    endif(EXISTS "/opt/local/avr")
endif(DEFINED ENV{AVR_FIND_ROOT_PATH})
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
# not added automatically, since CMAKE_SYSTEM_NAME is "generic"
set(CMAKE_SYSTEM_INCLUDE_PATH "${CMAKE_FIND_ROOT_PATH}/include")
set(CMAKE_SYSTEM_LIBRARY_PATH "${CMAKE_FIND_ROOT_PATH}/lib")

message(STATUS "Set CMAKE_FIND_ROOT_PATH to ${CMAKE_FIND_ROOT_PATH}")
message(STATUS "Set CMAKE_SYSTEM_INCLUDE_PATH to ${CMAKE_SYSTEM_INCLUDE_PATH}")
message(STATUS "Set CMAKE_SYSTEM_LIBRARY_PATH to ${CMAKE_SYSTEM_LIBRARY_PATH}")

set(CMAKE_C_FLAGS_RELEASE "-O3 -g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -g")

add_definitions("-DF_CPU=${MCU_SPEED}")
add_definitions("-fpack-struct")
add_definitions("-fshort-enums")
add_definitions("-Wall")
# add_definitions("-Werror")
# http://gcc.gnu.org/onlinedocs/gcc-4.8.2/gcc/Alternate-Keywords.html#Alternate-Keywords
# [...]-pedantic and other options cause warnings for many GNU C extensions. You can prevent such warnings within
# one expression by writing __extension__ before the expression. __extension__ has no effect aside from this.[...] 
 add_definitions("-pedantic")
 add_definitions("-pedantic-errors")
 add_definitions("-funsigned-char")
 add_definitions("-funsigned-bitfields")
 add_definitions("-ffunction-sections")
 add_definitions("-c")
 add_definitions("-std=gnu99")

add_subdirectory(../ src/sr)

add_vcd_trace(
  simavr_shift_registers
  "SIPO_SRCLR,0,PORTB"
  "SIPO_SRCLK,1,PORTB"
  "SIPO_SER,2,PORTB"
  "SIPO_OE,3,PORTB"
  "SIPO_RCLK,4,PORTB"
  "DDR_SIPO_SRCLR,0,DDRB"
  "DDR_SIPO_SRCLK,1,DDRB"
  "DDR_SIPO_SER,2,DDRB"
  "DDR_SIPO_OE,3,DDRB"
  "DDR_SIPO_RCLK,4,DDRB"
)

include_directories(../src)

add_avr_executable(
    simavr_shift_registers
    main.c
    ${simavr_shift_registers_VCD_TRACE_FILE}
)

avr_target_link_libraries(simavr_shift_registers avr_shift_registers)