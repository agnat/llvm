//===-- AVRSubtarget.cpp - AVR Subtarget Information ----------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file implements the AVR specific subclass of TargetSubtargetInfo.
//
//===----------------------------------------------------------------------===//

#include "AVRSubtarget.h"
#include "AVR.h"
#include "llvm/Support/TargetRegistry.h"

#define DEBUG_TYPE "avr-subtarget"

#define GET_SUBTARGETINFO_TARGET_DESC
#define GET_SUBTARGETINFO_CTOR
#include "AVRGenSubtargetInfo.inc"

using namespace llvm;

void AVRSubtarget::anchor() { }

AVRSubtarget::AVRSubtarget(const std::string &TT, const std::string &CPU,
                           const std::string &FS, AVRTargetMachine &TM) :
  AVRGenSubtargetInfo(TT, CPU, FS),
  InstrInfo(),
  FrameLowering(),
  TLInfo(TM),
  TSInfo(*getDataLayout()),
  
  // Supported instructions
  HasLPM(false), HasLPMX(false), HasELPM(false), HasELPMX(false),
  HasSPM(false), HasSPMX(false),
  HasMUL(false), HasFMUL(false),
  HasMOVW(false),
  HasDES(false),
  HasBREAK(false),
  SupportsRMW(false),
  
  // Other features
  HasSRAM(false),
  HasEIND(false),
  IsTiny(false),
  IsMega(false)
{
  // Parse features string.
  ParseSubtargetFeatures(CPU, FS);
}

