/*
 * Andy's Workshop NXA66 controller ATMega328p firmware
 * Copyright (c) 2017 Andy Brown. http://www.andybrown.me.uk
 * Please see website for licensing terms.
 */

#pragma once

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <avr/eeprom.h>
#include <avr/wdt.h>
#include <util/crc16.h>
 
#include "GpioPin.h"
#include "MillisecondTimer.h"
#include "Eeprom.h"
#include "Max7221.h"
#include "PowerOn.h"
#include "Switch.h"
#include "OutputEnable.h"
#include "OutputEnableSwitch.h"
#include "Vsp.h"
#include "VspSwitch.h"
#include "Encoder.h"
#include "ActionButton.h"
#include "PowerGood.h"
#include "Uart.h"
#include "Wire.h"
#include "FanSwitch.h"
#include "Mcp9700.h"
#include "Ina226.h"
#include "Meter.h"
#include "DataLogger.h"
#include "MenuItem.h"
#include "Limit.h"
#include "Calibration.h"
#include "Intensity.h"
#include "Log.h"
#include "FanThreshold.h"
#include "Reset.h"
#include "Temperature.h"
#include "Program.h"
