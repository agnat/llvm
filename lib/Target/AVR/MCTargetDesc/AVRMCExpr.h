//===-- AVRMCExpr.h - AVR specific MC expression classes --------*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#ifndef __INCLUDE_AVRMCEXPR_H__
#define __INCLUDE_AVRMCEXPR_H__

#include "llvm/MC/MCExpr.h"

namespace llvm
{

class AVRMCExpr : public MCTargetExpr
{
public:
  enum VariantKind {
    VK_AVR_None,

    VK_AVR_HI8,         // hi8()
    VK_AVR_LO8,         // lo8()
    VK_AVR_HLO8,        // hlo8() and hh8()
    VK_AVR_HHI8,        // hhi8()

    VK_AVR_PM_LO8,      // pm_lo8()
    VK_AVR_PM_HI8,      // pm_hi8()
    VK_AVR_PM_HLO8      // pm_hh8()
  };
public:
  static const AVRMCExpr *create(VariantKind Kind, const MCExpr *Expr,
                                 MCContext &Ctx);

  VariantKind getKind() const { return Kind; }
  char const* getName() const;
  const MCExpr *getSubExpr() const { return Expr; }

public: // MCTargetExpr
  void printImpl(raw_ostream &OS) const override;
  bool evaluateAsRelocatableImpl(MCValue &Res,
                                 const MCAsmLayout *Layout,
                                 const MCFixup *Fixup) const override;
  
  void visitUsedExpr(MCStreamer& streamer) const override;
  
  MCSection *findAssociatedSection() const override
  {
    return getSubExpr()->findAssociatedSection();
  }

  // There are no TLS AVRMCExprs at the moment.
  void fixELFSymbolsInTLSFixups(MCAssembler &Asm) const {}

  bool evaluateAsConstant(int64_t & Result) const;

  static bool classof(const MCExpr *E)
  {
    return E->getKind() == MCExpr::Target;
  }

public:
  static VariantKind getKindByName(StringRef Name);

private:
  int64_t evaluateAsInt64(int64_t Value) const;

  const VariantKind Kind;
  const MCExpr *Expr;
private:
  explicit AVRMCExpr(VariantKind _Kind, const MCExpr *_Expr) :
    Kind(_Kind), Expr(_Expr) {}
  ~AVRMCExpr() {}
};

} // end namespace llvm

#endif //__INCLUDE_AVRMCEXPR_H__
