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

void SetN2kPGN65281(tN2kMsg &N2kMsg, unsigned char ThrottleID, tN2kZydroThrottleSetpointMode Mode, float Target, bool ShiftGears) {
    N2kMsg.SetPGN(65281L);
    N2kMsg.Priority=5;
    N2kMsg.Add2ByteUInt(ZydroProprietary);
    N2kMsg.AddByte((unsigned char)ThrottleID);
    N2kMsg.AddByte((unsigned char)Mode);
    N2kMsg.AddFloat(Target);
    N2kMsg.AddByte((unsigned char)ShiftGears);
}

bool ParseN2kPGN65281(const tN2kMsg &N2kMsg, unsigned char &ThrottleID, tN2kZydroThrottleSetpointMode &Mode, float &Target, bool &ShiftGears) {
  if (N2kMsg.PGN!=65281L) return false;
  int Index=0;
  if (N2kMsg.Get2ByteUInt(Index)!=ZydroProprietary) return false;
  ThrottleID=N2kMsg.GetByte(Index);
  Mode=(tN2kZydroThrottleSetpointMode)(N2kMsg.GetByte(Index));
  Target=N2kMsg.GetFloat(Index);
  ShiftGears=(bool)(N2kMsg.GetByte(Index));
  return true;
}

/**************************************************************************/
// PGN 65282: Zydro "Throttle Control Status"

void SetN2kPGN65282(tN2kMsg &N2kMsg, unsigned char ThrottleID, tN2kZydroThrottleSetpointMode Mode, float TargetValue, float CurrentValue, unsigned char CurrentGear) {
  N2kMsg.SetPGN(65282L);
  N2kMsg.Priority=5;
  N2kMsg.SetIsTPMessage(true);
  N2kMsg.Add2ByteUInt(ZydroProprietary);
  N2kMsg.AddByte((unsigned char)ThrottleID);
  N2kMsg.AddByte((unsigned char)Mode);
  N2kMsg.AddFloat(TargetValue);
  N2kMsg.AddFloat(CurrentValue);
  N2kMsg.AddByte(CurrentGear);
}

bool ParseN2kPGN65282(const tN2kMsg &N2kMsg, unsigned char &ThrottleID, tN2kZydroThrottleSetpointMode &Mode, float &TargetValue, float &CurrentValue, unsigned char &CurrentGear) {
  if (N2kMsg.PGN!=65282L) return false;
  int Index=0;
  if (N2kMsg.Get2ByteUInt(Index)!=ZydroProprietary) return false;
  ThrottleID=N2kMsg.GetByte(Index);
  Mode=(tN2kZydroThrottleSetpointMode)(N2kMsg.GetByte(Index));
  TargetValue=N2kMsg.GetFloat(Index);
  CurrentValue=N2kMsg.GetFloat(Index);
  CurrentGear=N2kMsg.GetByte(Index);
  return true;
}

/**************************************************************************/
// PGN 65283: Zydro "Remote Control Input"

void SetN2kPGN65283(tN2kMsg &N2kMsg, unsigned char JoystickID, bool Connected, float Channel1, float Channel2, float Channel3, float Channel4, float Channel5, float Channel6, float Channel7, float Channel8) {
  N2kMsg.SetPGN(65283L);
  N2kMsg.Priority=5;
  // N2kMsg.SetIsTPMessage(true);
  N2kMsg.Add2ByteUInt(ZydroProprietary);
  N2kMsg.AddByte((unsigned char)JoystickID);
  N2kMsg.AddByte((unsigned char)Connected);
  N2kMsg.AddByte(128 + (int)(127 * Channel1));
  N2kMsg.AddByte(128 + (int)(127 * Channel2));
  Channel3 = 0.0f;
  Channel4 = 0.0f;
  Channel5 = 0.0f;
  Channel6 = 0.0f;
  Channel7 = 0.0f;
  Channel8 = 0.0f;
  // N2kMsg.AddFloat(Channel2);
  // N2kMsg.AddFloat(Channel3);
  // N2kMsg.AddFloat(Channel4);
  // N2kMsg.AddFloat(Channel5);
  // N2kMsg.AddFloat(Channel6);
  // N2kMsg.AddFloat(Channel7);
  // N2kMsg.AddFloat(Channel8);
};

bool ParseN2kPGN65283(const tN2kMsg &N2kMsg, unsigned char &JoystickID, bool &Connected, float &Channel1, float &Channel2, float &Channel3, float &Channel4, float &Channel5, float &Channel6, float &Channel7, float &Channel8) {
  if (N2kMsg.PGN!=65283L) return false;
  int Index=0;
  if (N2kMsg.Get2ByteUInt(Index)!=ZydroProprietary) return false;
  JoystickID=N2kMsg.GetByte(Index);
  Connected=(bool)(N2kMsg.GetByte(Index));
  Channel1=(N2kMsg.GetByte(Index) - 128) / 128.0f;
  Channel2=(N2kMsg.GetByte(Index) - 128) / 128.0f;
  // Channel3=N2kMsg.GetFloat(Index);
  // Channel4=N2kMsg.GetFloat(Index);
  // Channel5=N2kMsg.GetFloat(Index);
  // Channel6=N2kMsg.GetFloat(Index);
  // Channel7=N2kMsg.GetFloat(Index);
  // Channel8=N2kMsg.GetFloat(Index);
  return true;
};

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
