# Andy's Workshop NXA66 controller ATMega328p firmware
# Copyright (c) 2017 Andy Brown. http://www.andybrown.me.uk
# Please see website for licensing terms.

"""
Usage: scons [upload]

  [upload]
    specify this option to automatically upload to
    using avrdude to a USBASP connected MCU.

To do a 'clean' use the -c flag
To do a parallel build use the -jN flag
"""

import os

# source the environment

env=Environment(ENV=os.environ)

# compiler is avr-gcc

env.Replace(CC="avr-gcc")
env.Replace(CXX="avr-g++")
env.Replace(PROGSUFFIX=".elf")

# set up our options

env.Replace(CXXFLAGS=["-mmcu=atmega328p",
                      "-Os",
                      "-g",
                      "-DF_CPU=8000000",
                      "-std=c++1y",
                      "-Wall",
                      "-Werror",
                      "-Wextra",
                      "-pedantic-errors",
                      "-flto",
                      "-fno-rtti",
                      "-mcall-prologues",
                      "-ffunction-sections",
                      "-fdata-sections",
                      "-fno-exceptions"])

env.Replace(CFLAGS=["-mmcu=atmega328p",
                      "-Os",
                      "-g",
                      "-DF_CPU=8000000",
                      "-std=c99",
                      "-Wall",
                      "-Werror",
                      "-Wextra",
                      "-pedantic-errors",
                      "-flto",
                      "-mcall-prologues",
                      "-ffunction-sections",
                      "-fdata-sections",
                      "-fno-exceptions"])

env.Replace(LINKFLAGS=["-Wl,-Map,nxa66.map",
                       "-mrelax",
                       "-flto",
                       "-Wl,--gc-sections",
                       "-mmcu=atmega328p"])

# compile source code to .elf binary

elf=env.Program("nxa66",[ Glob("*.cpp"), Glob("*.c") ])
Decider('timestamp-newer')

# convert elf to hex flashable image

hexfile=env.Command("nxa66.hex",elf,"avr-objcopy -j .text -j .data -O ihex $SOURCE $TARGET")
env.Install("../bin",hexfile)
env.Alias("install","../bin")

# calculate size and generate assembly source

env.Command("nxa66.siz",elf,"avr-size $SOURCE | tee $TARGET")
env.Command("nxa66.lst",elf,"avr-objdump -S $SOURCE > $TARGET")

# upload target uses avrdude

flash_cmd="avrdude -c usbasp -p m328p -e -U flash:w:nxa66.hex"
fuse_cmd="avrdude -c usbasp -p m328p -e -U lfuse:w:0xe2:m -U hfuse:w:0xde:m"

upload=env.Alias("upload","nxa66.hex",flash_cmd)
fuse=env.Alias("fuse","nxa66.hex",fuse_cmd)

AlwaysBuild([upload,fuse])
