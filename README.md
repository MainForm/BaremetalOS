# BaremetalOS

This project is for studying how to develop an operating system running on ARM architecture.

### - Supported boards
- RaspberryPI4
- Realview-PB-A8 (tested only on qemu emulator)

### - Supported peripherals
- PL011
- GIC-400
- SP804

## Prerequisite

### - Install toolchain

- **Use the apt package manager (Linux only)**
    - aarch32 (for Realview-PB-A8)
  
        This method of installing the toolchain does not include GDB for this architecture.
        ```bash
        sudo apt install gcc-arm-none-eabi
        ```
    - aarch64 (for RaspberryPI4)

        ```bash
        sudo apt install crossbuild-essential-arm64
        ```
        
- **Download from official arm toolchain** (recommend)
    
    You can download the toolchain from the official ARM website, and you need to make sure it supports AArch64 and AArch32.

    Download : https://developer.arm.com/downloads/-/arm-gnu-toolchain-downloads


## Building

- **Set the variable in makefile**

    - TARGET_BOARD
        
        Set the board you want to install this OS.

        Make sure to set **TARGET_BORD** to one of the supported boards.
        
    - TOOLCHAIN_PREFIX

        It may change depending on how the toolchain is installed.
        Therefore, you must check the toolchain prefix.

- **Build the BaremetalOS**

    Make sure to run the command below from the top directory of the project.
    ```bash
    make
    ```

## Result files

The result files will be created in the build directory after the build.

- **build/kernel.elf**
- **build/output/image**

