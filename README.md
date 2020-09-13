# AVR Shift Registers

## How to use this libray
  - First of all to make things easier, you will have to use CMake toolchain file from this project https://github.com/Rutherther/cmake-avr
  - Use `add_subdirectory` in CMakeLists.txt to add this library
  - Use `avr_target_link_libraries(<executable-name> avr_shift_registers)`

## How to test this project using simavr
  - There is an example in `simavr` subfolder
  - You can start `simavr` project using `cmake`. After running cmake
    - Use `make sim_simavr_shift_registers` to start simavr
    - Use `make gdb_simavr_shift_registers` to start simavr along with avr-gdb
    - Use visual studio code
