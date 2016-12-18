/*
 * Andy's Workshop NXA66 controller ATMega328p firmware
 * Copyright (c) 2017 Andy Brown. http://www.andybrown.me.uk
 * Please see website for licensing terms.
 */

#pragma once

#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <avr/eeprom.h>

#include "GpioPin.h"
#include "MillisecondTimer.h"
#include "Max7221.h"
#include "PowerOn.h"
#include "OutputEnable.h"
#include "Vsp.h"
#include "PowerGood.h"
#include "Wire.h"
#include "Ina226.h"
#include "Voltmeter.h"
#include "Program.h"
