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

#include "N2kTypes.h"
#include "N2kZydro.h"
#include <string.h>

#define ZydroProprietary 0x3600 // Random placeholder number

/**************************************************************************/
// PGN 65280: Zydro "Product Heartbeat"

void SetN2kPGN65280(tN2kMsg &N2kMsg, unsigned char SID, tN2kZydroDeviceModel ModelID, tN2kZydroDeviceHealth Health) {
    N2kMsg.SetPGN(65280L);
    N2kMsg.Priority=5;
    N2kMsg.Add2ByteUInt(ZydroProprietary);
    N2kMsg.AddByte(SID);
    N2kMsg.AddByte((unsigned char)ModelID);
    N2kMsg.AddByte((unsigned char)Health);
}

bool ParseN2kPGN65280(const tN2kMsg &N2kMsg, unsigned char &SID, tN2kZydroDeviceModel &ModelID, tN2kZydroDeviceHealth &Health) {
  if (N2kMsg.PGN!=65280L) return false;
  int Index=0;
  if (N2kMsg.Get2ByteUInt(Index)!=ZydroProprietary) return false;
  SID=N2kMsg.GetByte(Index);
  ModelID=(tN2kZydroDeviceModel)(N2kMsg.GetByte(Index));
  Health=(tN2kZydroDeviceHealth)(N2kMsg.GetByte(Index));
  return true;
}

/**************************************************************************/
// PGN 65281: Zydro "Throttle Control Setpoint"

void SetN2kPGN65281(tN2kMsg &N2kMsg, unsigned char ThrottleID, tN2kZydroThrottleSetpointMode Mode, unsigned char Target, bool ShiftGears) {
    N2kMsg.SetPGN(65281L);
    N2kMsg.Priority=5;
    N2kMsg.Add2ByteUInt(ZydroProprietary);
    N2kMsg.AddByte((unsigned char)ThrottleID);
    N2kMsg.AddByte((unsigned char)Mode);
    N2kMsg.AddByte(Target);
    N2kMsg.AddByte((unsigned char)ShiftGears);
}

bool ParseN2kPGN65281(const tN2kMsg &N2kMsg, unsigned char &ThrottleID, tN2kZydroThrottleSetpointMode &Mode, unsigned char &Target, bool &ShiftGears) {
  if (N2kMsg.PGN!=65281L) return false;
  int Index=0;
  if (N2kMsg.Get2ByteUInt(Index)!=ZydroProprietary) return false;
  ThrottleID=N2kMsg.GetByte(Index);
  Mode=(tN2kZydroThrottleSetpointMode)(N2kMsg.GetByte(Index));
  Target=N2kMsg.GetByte(Index);
  ShiftGears=(bool)(N2kMsg.GetByte(Index));
  return true;
}

/**************************************************************************/
// PGN 65282: Zydro "Throttle Control Status"

void SetN2kPGN65282(tN2kMsg &N2kMsg, unsigned char ThrottleID, tN2kZydroThrottleSetpointMode Mode, unsigned char TargetValue, unsigned char CurrentValue, unsigned char CurrentGear) {
  N2kMsg.SetPGN(65282L);
  N2kMsg.Priority=5;
  N2kMsg.Add2ByteUInt(ZydroProprietary);
  N2kMsg.AddByte((unsigned char)ThrottleID);
  N2kMsg.AddByte((unsigned char)Mode);
  N2kMsg.AddByte(TargetValue);
  N2kMsg.AddByte(CurrentValue);
  N2kMsg.AddByte(CurrentGear);
}

bool ParseN2kPGN65282(const tN2kMsg &N2kMsg, unsigned char &ThrottleID, tN2kZydroThrottleSetpointMode &Mode, unsigned char &TargetValue, unsigned char &CurrentValue, unsigned char &CurrentGear) {
  if (N2kMsg.PGN!=65282L) return false;
  int Index=0;
  if (N2kMsg.Get2ByteUInt(Index)!=ZydroProprietary) return false;
  ThrottleID=N2kMsg.GetByte(Index);
  Mode=(tN2kZydroThrottleSetpointMode)(N2kMsg.GetByte(Index));
  TargetValue=N2kMsg.GetByte(Index);
  CurrentValue=N2kMsg.GetByte(Index);
  CurrentGear=N2kMsg.GetByte(Index);
  return true;
}

/**************************************************************************/
// PGN 65283: Zydro "Remote Control Input"

void SetN2kPGN65283(tN2kMsg &N2kMsg, unsigned char JoystickID, bool Connected,
                    unsigned char Channel1, unsigned char Channel2,
                    unsigned char Channel3, unsigned char Channel4,
                    uint16_t Buttons) {
  N2kMsg.SetPGN(65283L);
  N2kMsg.Priority=5;
  N2kMsg.SetIsTPMessage(true);
  N2kMsg.Add2ByteUInt(ZydroProprietary);
  N2kMsg.AddByte((unsigned char)JoystickID);
  N2kMsg.AddByte((unsigned char)Connected);
  N2kMsg.AddByte(Channel1);
  N2kMsg.AddByte(Channel2);
  N2kMsg.AddByte(Channel3);
  N2kMsg.AddByte(Channel4);
  N2kMsg.Add2ByteUInt(Buttons);
}

void SetN2kPGN65283(tN2kMsg &N2kMsg, unsigned char JoystickID, bool Connected,
                    unsigned char Channel1, unsigned char Channel2,
                    unsigned char Channel3, unsigned char Channel4) {
  // Fits a single CAN frame: proprietary(2)+id(1)+connected(1)+axes(4).
  N2kMsg.SetPGN(65283L);
  N2kMsg.Priority=5;
  N2kMsg.Add2ByteUInt(ZydroProprietary);
  N2kMsg.AddByte((unsigned char)JoystickID);
  N2kMsg.AddByte((unsigned char)Connected);
  N2kMsg.AddByte(Channel1);
  N2kMsg.AddByte(Channel2);
  N2kMsg.AddByte(Channel3);
  N2kMsg.AddByte(Channel4);
}

bool ParseN2kPGN65283(const tN2kMsg &N2kMsg, unsigned char &JoystickID, bool &Connected,
                      unsigned char &Channel1, unsigned char &Channel2,
                      unsigned char &Channel3, unsigned char &Channel4,
                      uint16_t &Buttons) {
  if (N2kMsg.PGN!=65283L) return false;
  int Index=0;
  if (N2kMsg.Get2ByteUInt(Index)!=ZydroProprietary) return false;
  JoystickID=N2kMsg.GetByte(Index);
  Connected=(bool)(N2kMsg.GetByte(Index));
  Channel1=N2kMsg.GetByte(Index);
  Channel2=N2kMsg.GetByte(Index);
  Channel3=N2kMsg.GetByte(Index);
  Channel4=N2kMsg.GetByte(Index);
  // Joystick-only frames omit the button bitmask.
  if (Index + 2 <= N2kMsg.DataLen) {
    Buttons=N2kMsg.Get2ByteUInt(Index);
  } else {
    Buttons=0;
  }
  return true;
}

bool ParseN2kPGN65283(const tN2kMsg &N2kMsg, unsigned char &JoystickID, bool &Connected,
                      unsigned char &Channel1, unsigned char &Channel2,
                      unsigned char &Channel3, unsigned char &Channel4) {
  uint16_t Buttons=0;
  return ParseN2kPGN65283(N2kMsg, JoystickID, Connected, Channel1, Channel2, Channel3, Channel4, Buttons);
}

uint16_t EncodeButtonBitmask(bool Button1, bool Button2, bool Button3, bool Button4,
                             bool Button5, bool Button6, bool Button7, bool Button8,
                             bool Button9, bool Button10, bool Button11, bool Button12,
                             bool Button13, bool Button14, bool Button15, bool Button16) {
  uint16_t mask = 0;
  if (Button1)  mask |= (uint16_t)(1u << 0);
  if (Button2)  mask |= (uint16_t)(1u << 1);
  if (Button3)  mask |= (uint16_t)(1u << 2);
  if (Button4)  mask |= (uint16_t)(1u << 3);
  if (Button5)  mask |= (uint16_t)(1u << 4);
  if (Button6)  mask |= (uint16_t)(1u << 5);
  if (Button7)  mask |= (uint16_t)(1u << 6);
  if (Button8)  mask |= (uint16_t)(1u << 7);
  if (Button9)  mask |= (uint16_t)(1u << 8);
  if (Button10) mask |= (uint16_t)(1u << 9);
  if (Button11) mask |= (uint16_t)(1u << 10);
  if (Button12) mask |= (uint16_t)(1u << 11);
  if (Button13) mask |= (uint16_t)(1u << 12);
  if (Button14) mask |= (uint16_t)(1u << 13);
  if (Button15) mask |= (uint16_t)(1u << 14);
  if (Button16) mask |= (uint16_t)(1u << 15);
  return mask;
}

/**************************************************************************/
// PGN 65284: Zydro "Steering Control Setpoint"

void SetN2kPGN65284(tN2kMsg &N2kMsg, unsigned char SteeringID, tN2kZydroSteeringSetpointMode Mode, unsigned char Target) {
  N2kMsg.SetPGN(65284L);
  N2kMsg.Priority=3;
  N2kMsg.Add2ByteUInt(ZydroProprietary);
  N2kMsg.AddByte((unsigned char)SteeringID);
  N2kMsg.AddByte((unsigned char)Mode);
  N2kMsg.AddByte(Target);
}

bool ParseN2kPGN65284(const tN2kMsg &N2kMsg, unsigned char &SteeringID, tN2kZydroSteeringSetpointMode &Mode, unsigned char &Target) {
  if (N2kMsg.PGN!=65284L) return false;
  int Index=0;
  if (N2kMsg.Get2ByteUInt(Index)!=ZydroProprietary) return false;
  SteeringID=N2kMsg.GetByte(Index);
  Mode=(tN2kZydroSteeringSetpointMode)(N2kMsg.GetByte(Index));
  Target=N2kMsg.GetByte(Index);
  return true;
}

/**************************************************************************/
// PGN 65285: Zydro "Steering Control Status"

void SetN2kPGN65285(tN2kMsg &N2kMsg, unsigned char SteeringID, tN2kZydroSteeringSetpointMode Mode, unsigned char TargetValue, unsigned char CurrentValue) {
  N2kMsg.SetPGN(65285L);
  N2kMsg.Priority=5;
  N2kMsg.Add2ByteUInt(ZydroProprietary);
  N2kMsg.AddByte((unsigned char)SteeringID);
  N2kMsg.AddByte((unsigned char)Mode);
  N2kMsg.AddByte(TargetValue);
  N2kMsg.AddByte(CurrentValue);
}

bool ParseN2kPGN65285(const tN2kMsg &N2kMsg, unsigned char &SteeringID, tN2kZydroSteeringSetpointMode &Mode, unsigned char &TargetValue, unsigned char &CurrentValue) {
  if (N2kMsg.PGN!=65285L) return false;
  int Index=0;
  if (N2kMsg.Get2ByteUInt(Index)!=ZydroProprietary) return false;
  SteeringID=N2kMsg.GetByte(Index);
  Mode=(tN2kZydroSteeringSetpointMode)(N2kMsg.GetByte(Index));
  TargetValue=N2kMsg.GetByte(Index);
  CurrentValue=N2kMsg.GetByte(Index);
  return true;
}

/**************************************************************************/
// PGN 65286: Zydro "Engine Control"

void SetN2kPGN65286(tN2kMsg &N2kMsg, unsigned char EngineID, bool Enabled) {
  N2kMsg.SetPGN(65286L);
  N2kMsg.Priority=3;
  N2kMsg.Add2ByteUInt(ZydroProprietary);
  N2kMsg.AddByte((unsigned char)EngineID);
  N2kMsg.AddByte((unsigned char)(Enabled ? 1 : 0));
}

bool ParseN2kPGN65286(const tN2kMsg &N2kMsg, unsigned char &EngineID, bool &Enabled) {
  if (N2kMsg.PGN!=65286L) return false;
  int Index=0;
  if (N2kMsg.Get2ByteUInt(Index)!=ZydroProprietary) return false;
  EngineID=N2kMsg.GetByte(Index);
  Enabled=(N2kMsg.GetByte(Index) != 0);
  return true;
}

/**************************************************************************/
// PGN 65290: Zydro "Generic Command"

void SetN2kPGN65290(tN2kMsg &N2kMsg, unsigned char TargetID, tN2kZydroCommand Command, uint64_t Param1, uint64_t Param2, uint64_t Param3, uint64_t Param4) {
  N2kMsg.SetPGN(65290L);
  N2kMsg.Priority=5;
  N2kMsg.SetIsTPMessage(true);
  N2kMsg.Add2ByteUInt(ZydroProprietary);
  N2kMsg.AddByte((unsigned char)TargetID);
  N2kMsg.AddByte((unsigned char)Command);
  N2kMsg.AddUInt64(Param1);
  N2kMsg.AddUInt64(Param2);
  N2kMsg.AddUInt64(Param3);
  N2kMsg.AddUInt64(Param4);
};

bool ParseN2kPGN65290(const tN2kMsg &N2kMsg, unsigned char &TargetID, tN2kZydroCommand &Command, uint64_t &Param1, uint64_t &Param2, uint64_t &Param3, uint64_t &Param4) {
  if (N2kMsg.PGN!=65290L) return false;
  int Index=0;
  if (N2kMsg.Get2ByteUInt(Index)!=ZydroProprietary) return false;
  TargetID=N2kMsg.GetByte(Index);
  Command=(tN2kZydroCommand)(N2kMsg.GetByte(Index));
  Param1=N2kMsg.GetUInt64(Index);
  Param2=N2kMsg.GetUInt64(Index);
  Param3=N2kMsg.GetUInt64(Index);
  Param4=N2kMsg.GetUInt64(Index);
  return true;
};

/**************************************************************************/
// PGN 65291: Zydro "Get Parameter"

void SetN2kPGN65291(tN2kMsg &N2kMsg, uint64_t ParamId, uint64_t ParamType, uint64_t ParamValue, bool IsPersisted) {
  N2kMsg.SetPGN(65291L);
  N2kMsg.Priority=5;
  N2kMsg.SetIsTPMessage(true);
  N2kMsg.Add2ByteUInt(ZydroProprietary);
  N2kMsg.AddUInt64(ParamId);
  N2kMsg.AddUInt64(ParamType);
  N2kMsg.AddUInt64(ParamValue);
  N2kMsg.AddByte((unsigned char)IsPersisted);
};

bool ParseN2kPGN65291(const tN2kMsg &N2kMsg, uint64_t &ParamId, uint64_t &ParamType, uint64_t &ParamValue, bool &IsPersisted) {
  if (N2kMsg.PGN!=65291L) return false;
  int Index=0;
  if (N2kMsg.Get2ByteUInt(Index)!=ZydroProprietary) return false;
  ParamId=N2kMsg.GetUInt64(Index);
  ParamType=N2kMsg.GetUInt64(Index);
  ParamValue=N2kMsg.GetUInt64(Index);
  IsPersisted=(bool)N2kMsg.GetByte(Index);
  return true;
};

/**************************************************************************/
// PGN 65292: Zydro "Set Parameter"

void SetN2kPGN65292(tN2kMsg &N2kMsg, unsigned char TargetID, uint64_t ParamId, uint64_t ParamType, uint64_t ParamValue) {
  N2kMsg.SetPGN(65292L);
  N2kMsg.Priority=5;
  N2kMsg.SetIsTPMessage(true);
  N2kMsg.Add2ByteUInt(ZydroProprietary);
  N2kMsg.AddByte(TargetID);
  N2kMsg.AddUInt64(ParamId);
  N2kMsg.AddUInt64(ParamType);
  N2kMsg.AddUInt64(ParamValue);
};

bool ParseN2kPGN65292(const tN2kMsg &N2kMsg, unsigned char &TargetID, uint64_t &ParamId, uint64_t &ParamType, uint64_t &ParamValue) {
  if (N2kMsg.PGN!=65292L) return false;
  int Index=0;
  if (N2kMsg.Get2ByteUInt(Index)!=ZydroProprietary) return false;
  TargetID=N2kMsg.GetByte(Index);
  ParamId=N2kMsg.GetUInt64(Index);
  ParamType=N2kMsg.GetUInt64(Index);
  ParamValue=N2kMsg.GetUInt64(Index);
  return true;
};
