/*
 * N2kZydro.h
 * 
 * Copyright (c) 2019-2025 Chris Dalke, www.zydromarine.com, 
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS 
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
*/

/****************************************************************************
 * \file   N2kZydro.h
 * \brief  Collection of functions for handling NMEA2000 Zydro Marine messages
 *
 * This is collection of functions for handling NMEA2000 Zydro Marine messages.
 * This is a set of non-standard, open messages used by Zydro products to 
 * supplement standard NMEA 2000 PGNs.
 * 
 * This file contains functions to create and parse messages. Each PGN has a
 * a function to SetN2kPGN<id> and ParseN2kPGN<id>.
 * 
 * If you do not send any Zydro-specific messages you do not need this library.
 * 
 * \note  These are non-standard open messages created and used by Zydro Marine!
 *        see the [Zydro Marine Website] (https://www.zydromarine.com/)
 * 
 * \authors Chris Dalke
*/

#ifndef _N2kZydro_H_
#define _N2kZydro_H_

#include "N2kMsg.h"
#include "N2kTypes.h"
#include <stdint.h>

// Enumeration of different device types
enum tN2kZydroDeviceModel {
    tN2kZydroDeviceModel_invalid=0,
    tN2kZydroDeviceModel_estop=1,
    tN2kZydroDeviceModel_autonomyCore=2
};

// Enumeration of health status of a device
enum tN2kZydroDeviceHealth {
    tN2kZydroDeviceHealth_invalid=0,
    tN2kZydroDeviceHealth_pending=1,
    tN2kZydroDeviceHealth_healthy=2,
    tN2kZydroDeviceHealth_unhealthy=3,
    tN2kZydroDeviceHealth_emergencyStop=4
};

// Enumeration of throttle controller modes
enum tN2kZydroThrottleSetpointMode {
    tN2kZydroThrottleSetpointMode_invalid=0,
    tN2kZydroThrottleSetpointMode_idle=1,
    tN2kZydroThrottleSetpointMode_throttlePercentage=2,
    tN2kZydroThrottleSetpointMode_rpm=3
};

// Enumeration of command types
enum tN2kZydroCommand {
   tN2kZydroCommand_invalid=0
   tN2kZydroCommand_parameterGet=1,
   tN2kZydroCommand_parameterGetAll=2,
   tN2kZydroCommand_parameterSet=3,
   tN2kZydroCommand_parameterReset=4,
   tN2kZydroCommand_parameterResetAll=5,
};

/**************************************************************************
 * \brief PGN 65280: Zydro "Product Heartbeat"
 * 
 * This message is broadcast periodically by all Zydro products to provide
 * a heartbeat used for auto-detection purposes.
 * 
 * \param N2kMsg          Reference to a N2kMsg Object, 
 *                        Output: NMEA2000 message ready to be send.
 * \param SID             Sequence identifier. In most cases you can use just 0xff for SID. See \ref secRefTermSID. \n
 *                        \n
 *                        The sequence identifier field is used to tie different PGNs data together to the same 
 *                        sampling or calculation time.
 * \param ModelID         Zydro-specific product model ID, from a Zydro internal enumeration.
 * \param Health          Health status for the device, from a Zydro internal enumeration.
 */
void SetN2kPGN65280(tN2kMsg &N2kMsg, unsigned char SID, tN2kZydroDeviceModel ModelID, tN2kZydroDeviceHealth Health);
bool ParseN2kPGN65280(const tN2kMsg &N2kMsg, unsigned char &SID, tN2kZydroDeviceModel &ModelID, tN2kZydroDeviceHealth &Health);

/**************************************************************************
 * \brief PGN 65281: Zydro "Throttle Control Setpoint"
 * 
 * This message is used to set a target for a throttle & shift controller.
 * 
 * \param N2kMsg          Reference to a N2kMsg Object, 
 *                        Output: NMEA2000 message ready to be send.
 * \param ThrottleID      Integer ID for the throttle channel; typically 0 (all engines), 1 (port) or 2 (starboard).
 * \param Mode            Setpoint mode, from a Zydro internal enumeration.
 * \param Target          Target throttle value, as double. In throttle percentage mode, this is -1.0 to 1.0, in RPM mode this is an RPM.
 * \param ShiftGears      Boolean, whether to also shift engine gear in tandem with throttle if available.
 */
void SetN2kPGN65281(tN2kMsg &N2kMsg, unsigned char ThrottleID, tN2kZydroThrottleSetpointMode Mode, float Target, bool ShiftGears);
bool ParseN2kPGN65281(const tN2kMsg &N2kMsg, unsigned char &ThrottleID, tN2kZydroThrottleSetpointMode &Mode, float &Target, bool &ShiftGears);

/**************************************************************************
 * \brief PGN 65282: Zydro "Throttle Control Status"
 * 
 * This message is used to broadcast the status of a throttle & shift controller.
 * 
 * \param N2kMsg          Reference to a N2kMsg Object, 
 *                        Output: NMEA2000 message ready to be send.
 * \param ThrottleID      Integer ID for the throttle channel; typically 0 (all engines), 1 (port) or 2 (starboard).
 * \param Mode            Active setpoint mode, from a Zydro internal enumeration.
 * \param TargetValue     Target setpoint value.
 * \param CurrentValue    Current control value.
 * \param CurrentGear     Current gear value (0 = disengaged, 1 = forward, 2 = reverse)
 */
void SetN2kPGN65282(tN2kMsg &N2kMsg, unsigned char ThrottleID, tN2kZydroThrottleSetpointMode Mode, float TargetValue, float CurrentValue, unsigned char CurrentGear);
bool ParseN2kPGN65282(const tN2kMsg &N2kMsg, unsigned char &ThrottleID, tN2kZydroThrottleSetpointMode &Mode, float &TargetValue, float &CurrentValue, unsigned char &CurrentGear);

/**************************************************************************
 * \brief PGN 65283: Zydro "Remote Control Input"
 * 
 * This message encodes raw joystick inputs from a controller.
 * 
 * \param N2kMsg          Reference to a N2kMsg Object, 
 *                        Output: NMEA2000 message ready to be send.
 * \param JoystickID      Integer ID for the joystick; typically 0.
 * \param Connected       Boolean representing if the joystick is currently connected.
 * \param Channel1        RC Channel 1 value (-1.0 to 1.0)
 * \param Channel2        RC Channel 2 value (-1.0 to 1.0)
 * \param Channel3        RC Channel 3 value (-1.0 to 1.0)
 * \param Channel4        RC Channel 4 value (-1.0 to 1.0)
 * \param Channel5        RC Channel 5 value (-1.0 to 1.0)
 * \param Channel6        RC Channel 6 value (-1.0 to 1.0)
 * \param Channel7        RC Channel 7 value (-1.0 to 1.0)
 * \param Channel8        RC Channel 8 value (-1.0 to 1.0)
 */
void SetN2kPGN65283(tN2kMsg &N2kMsg, unsigned char JoystickID, bool Connected, float Channel1, float Channel2, float Channel3, float Channel4, float Channel5, float Channel6, float Channel7, float Channel8);
bool ParseN2kPGN65283(const tN2kMsg &N2kMsg, unsigned char &JoystickID, bool &Connected, float &Channel1, float &Channel2, float &Channel3, float &Channel4, float &Channel5, float &Channel6, float &Channel7, float &Channel8);

/**************************************************************************
 * \brief PGN 65290: Zydro "Generic Command"
 * 
 * Encodes a generic command.
 * 
 * \param N2kMsg          Reference to a N2kMsg Object, 
 *                        Output: NMEA2000 message ready to be send.
 * \param TargetID        Target device for the command. If 0, the command should be interpreted as a broadcast to all devices.
 * \param Command         Command type, from the tN2kZydroCommand enumeration.
 * \param Param1          First parameter for the command. The meaning of this parameter is command-specific.
 * \param Param2          Second parameter for the command. The meaning of this parameter is command-specific.
 * \param Param2          Third parameter for the command. The meaning of this parameter is command-specific.
 * \param Param2          Fourth parameter for the command. The meaning of this parameter is command-specific.
 */
void SetN2kPGN65290(tN2kMsg &N2kMsg, unsigned char TargetID, tN2kZydroCommand Command, uint64_t Param1, uint64_t Param2, uint64_t Param3, uint64_t Param4);
bool ParseN2kPGN65290(const tN2kMsg &N2kMsg, unsigned char &TargetID, tN2kZydroCommand &Command, uint64_t &Param1, uint64_t &Param2, uint64_t &Param3, uint64_t &Param4);

/**************************************************************************
 * \brief PGN 65291: Zydro "Get Parameter"
 * 
 * Response to a request to read the value of a parameter.
 * 
 * \param N2kMsg          Reference to a N2kMsg Object, 
 *                        Output: NMEA2000 message ready to be send.
 * \param ParamId         Identifier for a parameter.
 * \param ParamType       Data type of the parameter.
 * \param ParamValue      Value of the parameter (cast to a uint64).
 * \param IsPersisted     If true, the parameter value is persisted to EEPROM. If false, the parameter value is reset each boot. Device-specific.
 */
void SetN2kPGN65291(tN2kMsg &N2kMsg, uint64_t ParamId, uint64_t ParamType, uint64_t ParamValue, bool IsPersisted);
bool ParseN2kPGN65291(const tN2kMsg &N2kMsg, uint64_t &ParamId, uint64_t &ParamType, uint64_t &ParamValue, bool &IsPersisted);

/**************************************************************************
 * \brief PGN 65292: Zydro "Set Parameter"
 * 
 * Write the value of a parameter.
 * 
 * \param N2kMsg          Reference to a N2kMsg Object, 
 *                        Output: NMEA2000 message ready to be send.
 * \param TargetID        Target device for the command. If 0, the command should be interpreted as a broadcast to all devices.
 * \param ParamId         Identifier for a parameter.
 * \param ParamType       Data type of the parameter.
 * \param ParamValue      Value of the parameter (cast to a uint64).
 */
void SetN2kPGN65292(tN2kMsg &N2kMsg, unsigned char TargetID, uint64_t ParamId, uint64_t ParamType, uint64_t ParamValue);
bool ParseN2kPGN65292(const tN2kMsg &N2kMsg, unsigned char &TargetID, uint64_t &ParamId, uint64_t &ParamType, uint64_t &ParamValue);

/**************************************************************************/
#endif

