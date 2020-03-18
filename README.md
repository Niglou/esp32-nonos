# **ESP32 nonos**

## **Features**

Use esp32 in real-time without OS.

**! Warning !**  
**All parts are not done !**

## **Prerequies**

You'll need **xtensa-esp32-elf-gcc** to compile project.  
Instruction from https://docs.espressif.com/projects/esp-idf/en/latest/get-started/linux-setup-scratch.html  

Once you have the binaries, change the path of binaries in "Makefile"  
(default : ~/esp/xtensa-esp32-elf).

## **Compile**

`make` or `make build` will compile objects files in "builds" folder.

`make build /path/folder/project` to compile your project.

## **Flash**

You'll need **[esptool](https://github.com/espressif/esptool)**.  
Flash the binary at address `0x1000`.

For ESP32 (4MB) :  
`esptool.py -c esp32 write_flash 0x1000 project.bin`

For ESP32-PICO-D4 (4MB) :  
`esptool.py -c esp32 write_flash -sc 6,17,8,11,16 0x1000 project.bin`

Check *write_flash* options for others esp32 configurations.

## **Template**

You can use this [template](https://github.com/Niglou/esp32-nonos-template) as base program.
