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
    tN2kZydroDeviceModel_autonomyCore=2,
    tN2kZydroDeviceModel_devKit=3,
    tN2kZydroDeviceModel_elrsReceiver=4,
    tN2kZydroDeviceModel_relay=5,
    tN2kZydroDeviceModel_torqlinkController=6,
    tN2kZydroDeviceModel_steeringController=7,
    tN2kZydroDeviceModel_outboardDrive=8
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

// Enumeration of steering controller setpoint modes
enum tN2kZydroSteeringSetpointMode {
    tN2kZydroSteeringSetpointMode_invalid=0,
    tN2kZydroSteeringSetpointMode_idle=1,
    tN2kZydroSteeringSetpointMode_position=2,
    tN2kZydroSteeringSetpointMode_velocity=3
};

// Enumeration of command types
enum tN2kZydroCommand {
   tN2kZydroCommand_invalid=0,
   tN2kZydroCommand_parameterGet=1,
   tN2kZydroCommand_parameterGetAll=2,
   tN2kZydroCommand_parameterSet=3,
   tN2kZydroCommand_parameterReset=4,
   tN2kZydroCommand_parameterResetAll=5
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
 * \param Target          Target throttle value (0 - 255, 128 = center)
 * \param ShiftGears      Boolean, whether to also shift engine gear in tandem with throttle if available.
 */
void SetN2kPGN65281(tN2kMsg &N2kMsg, unsigned char ThrottleID, tN2kZydroThrottleSetpointMode Mode, unsigned char Target, bool ShiftGears);
bool ParseN2kPGN65281(const tN2kMsg &N2kMsg, unsigned char &ThrottleID, tN2kZydroThrottleSetpointMode &Mode, unsigned char &Target, bool &ShiftGears);

/**************************************************************************
 * \brief PGN 65282: Zydro "Throttle Control Status"
 * 
 * This message is used to broadcast the status of a throttle & shift controller.
 * 
 * \param N2kMsg          Reference to a N2kMsg Object, 
 *                        Output: NMEA2000 message ready to be send.
 * \param ThrottleID      Integer ID for the throttle channel; typically 0 (all engines), 1 (port) or 2 (starboard).
 * \param Mode            Active setpoint mode, from a Zydro internal enumeration.
 * \param TargetValue     Target control value (0 - 255, 128 = center)
 * \param CurrentValue    Current control value (0 - 255, 128 = center)
 * \param CurrentGear     Current gear value (0 = disengaged, 1 = forward, 2 = reverse)
 */
void SetN2kPGN65282(tN2kMsg &N2kMsg, unsigned char ThrottleID, tN2kZydroThrottleSetpointMode Mode, unsigned char TargetValue, unsigned char CurrentValue, unsigned char CurrentGear);
bool ParseN2kPGN65282(const tN2kMsg &N2kMsg, unsigned char &ThrottleID, tN2kZydroThrottleSetpointMode &Mode, unsigned char &TargetValue, unsigned char &CurrentValue, unsigned char &CurrentGear);

/**************************************************************************
 * \brief PGN 65283: Zydro "Remote Control Input"
 *
 * This message encodes joystick axes and buttons from a controller.
 *
 * \param N2kMsg          Reference to a N2kMsg Object,
 *                        Output: NMEA2000 message ready to be send.
 * \param JoystickID      Integer ID for the joystick; typically 0.
 * \param Connected       Boolean representing if the joystick is currently connected.
 * \param Channel1        RC Channel 1 value (0 - 255, 128 = center)
 * \param Channel2        RC Channel 2 value (0 - 255, 128 = center)
 * \param Channel3        RC Channel 3 value (0 - 255, 128 = center)
 * \param Channel4        RC Channel 4 value (0 - 255, 128 = center)
 * \param Buttons         Bitmask of 16 digital button channels (bit 0 = button 1).
 */
void SetN2kPGN65283(tN2kMsg &N2kMsg, unsigned char JoystickID, bool Connected,
                    unsigned char Channel1, unsigned char Channel2,
                    unsigned char Channel3, unsigned char Channel4);
void SetN2kPGN65283(tN2kMsg &N2kMsg, unsigned char JoystickID, bool Connected,
                    unsigned char Channel1, unsigned char Channel2,
                    unsigned char Channel3, unsigned char Channel4,
                    uint16_t Buttons);
bool ParseN2kPGN65283(const tN2kMsg &N2kMsg, unsigned char &JoystickID, bool &Connected,
                      unsigned char &Channel1, unsigned char &Channel2,
                      unsigned char &Channel3, unsigned char &Channel4);
bool ParseN2kPGN65283(const tN2kMsg &N2kMsg, unsigned char &JoystickID, bool &Connected,
                      unsigned char &Channel1, unsigned char &Channel2,
                      unsigned char &Channel3, unsigned char &Channel4,
                      uint16_t &Buttons);

/**
 * \brief Pack 16 digital button states into the PGN 65283 button bitmask.
 * Bit 0 is Button1, bit 15 is Button16.
 */
uint16_t EncodeButtonBitmask(bool Button1, bool Button2, bool Button3, bool Button4,
                             bool Button5, bool Button6, bool Button7, bool Button8,
                             bool Button9, bool Button10, bool Button11, bool Button12,
                             bool Button13, bool Button14, bool Button15, bool Button16);

/**************************************************************************
 * \brief PGN 65284: Zydro "Steering Control Setpoint"
 *
 * This message is used to set a target for a steering controller.
 *
 * \param N2kMsg          Reference to a N2kMsg Object,
 *                        Output: NMEA2000 message ready to be send.
 * \param SteeringID      Integer ID for the steering channel; typically 0.
 * \param Mode            Setpoint mode (Position or Velocity)
 * \param Target          Target position or velocity (0 = full negative, 255 = full positive)
 */
void SetN2kPGN65284(tN2kMsg &N2kMsg, unsigned char SteeringID, tN2kZydroSteeringSetpointMode Mode, unsigned char Target);
bool ParseN2kPGN65284(const tN2kMsg &N2kMsg, unsigned char &SteeringID, tN2kZydroSteeringSetpointMode &Mode, unsigned char &Target);

/**************************************************************************
 * \brief PGN 65285: Zydro "Steering Control Status"
 *
 * This message is used to broadcast the status of a steering controller.
 *
 * \param N2kMsg          Reference to a N2kMsg Object,
 *                        Output: NMEA2000 message ready to be send.
 * \param SteeringID      Integer ID for the steering channel; typically 0.
 * \param Mode            Active setpoint mode.
 * \param TargetValue     Target position or velocity (0 = full negative, 255 = full positive)
 * \param CurrentValue    Current position or velocity (0 = full negative, 255 = full positive)
 */
void SetN2kPGN65285(tN2kMsg &N2kMsg, unsigned char SteeringID, tN2kZydroSteeringSetpointMode Mode, unsigned char TargetValue, unsigned char CurrentValue);
bool ParseN2kPGN65285(const tN2kMsg &N2kMsg, unsigned char &SteeringID, tN2kZydroSteeringSetpointMode &Mode, unsigned char &TargetValue, unsigned char &CurrentValue);

/**************************************************************************
 * \brief PGN 65286: Zydro "Engine Control"
 *
 * Command an engine / drive channel to enable (power/ignition on) or disable
 * (power/ignition off). Controllers may enforce a post-enable cooldown before
 * accepting throttle.
 *
 * \param N2kMsg          Reference to a N2kMsg Object,
 *                        Output: NMEA2000 message ready to be send.
 * \param EngineID        Integer ID for the engine channel; typically 0.
 * \param Enabled         true = enable / arm, false = disable / disarm.
 */
void SetN2kPGN65286(tN2kMsg &N2kMsg, unsigned char EngineID, bool Enabled);
bool ParseN2kPGN65286(const tN2kMsg &N2kMsg, unsigned char &EngineID, bool &Enabled);

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

