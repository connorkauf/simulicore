// this file inc
#include "operators.hpp"

// system

// 3rd

// cla3p
#include "math_ops.hpp"

/*-------------------------------------------------*/
static const cla3p::Operation noOp = cla3p::Operation(cla3p::op_t::N);
/*-------------------------------------------------*/

void operator+=(cla3p::dns::RiVector& trg, const cla3p::dns::RiVector& src) { cla3p::ops::update(1, src, trg); }
void operator+=(cla3p::dns::RdVector& trg, const cla3p::dns::RdVector& src) { cla3p::ops::update(1, src, trg); }
void operator+=(cla3p::dns::RfVector& trg, const cla3p::dns::RfVector& src) { cla3p::ops::update(1, src, trg); }
void operator+=(cla3p::dns::CdVector& trg, const cla3p::dns::CdVector& src) { cla3p::ops::update(1, src, trg); }
void operator+=(cla3p::dns::CfVector& trg, const cla3p::dns::CfVector& src) { cla3p::ops::update(1, src, trg); }

void operator+=(cla3p::dns::RiMatrix& trg, const cla3p::dns::RiMatrix& src) { cla3p::ops::update(1, src, trg); }
void operator+=(cla3p::dns::RdMatrix& trg, const cla3p::dns::RdMatrix& src) { cla3p::ops::update(1, src, trg); }
void operator+=(cla3p::dns::RfMatrix& trg, const cla3p::dns::RfMatrix& src) { cla3p::ops::update(1, src, trg); }
void operator+=(cla3p::dns::CdMatrix& trg, const cla3p::dns::CdMatrix& src) { cla3p::ops::update(1, src, trg); }
void operator+=(cla3p::dns::CfMatrix& trg, const cla3p::dns::CfMatrix& src) { cla3p::ops::update(1, src, trg); }

cla3p::dns::RiVector operator+(cla3p::dns::RiVector& srcA, const cla3p::dns::RiVector& srcB) { return cla3p::ops::add(1, srcA, 1, srcB); }
cla3p::dns::RdVector operator+(cla3p::dns::RdVector& srcA, const cla3p::dns::RdVector& srcB) { return cla3p::ops::add(1, srcA, 1, srcB); }
cla3p::dns::RfVector operator+(cla3p::dns::RfVector& srcA, const cla3p::dns::RfVector& srcB) { return cla3p::ops::add(1, srcA, 1, srcB); }
cla3p::dns::CdVector operator+(cla3p::dns::CdVector& srcA, const cla3p::dns::CdVector& srcB) { return cla3p::ops::add(1, srcA, 1, srcB); }
cla3p::dns::CfVector operator+(cla3p::dns::CfVector& srcA, const cla3p::dns::CfVector& srcB) { return cla3p::ops::add(1, srcA, 1, srcB); }

cla3p::dns::RiMatrix operator+(cla3p::dns::RiMatrix& srcA, const cla3p::dns::RiMatrix& srcB) { return cla3p::ops::add(1, srcA, 1, srcB); }
cla3p::dns::RdMatrix operator+(cla3p::dns::RdMatrix& srcA, const cla3p::dns::RdMatrix& srcB) { return cla3p::ops::add(1, srcA, 1, srcB); }
cla3p::dns::RfMatrix operator+(cla3p::dns::RfMatrix& srcA, const cla3p::dns::RfMatrix& srcB) { return cla3p::ops::add(1, srcA, 1, srcB); }
cla3p::dns::CdMatrix operator+(cla3p::dns::CdMatrix& srcA, const cla3p::dns::CdMatrix& srcB) { return cla3p::ops::add(1, srcA, 1, srcB); }
cla3p::dns::CfMatrix operator+(cla3p::dns::CfMatrix& srcA, const cla3p::dns::CfMatrix& srcB) { return cla3p::ops::add(1, srcA, 1, srcB); }

cla3p::dns::RiVector operator*(cla3p::dns::RiMatrix& srcA, const cla3p::dns::RiVector& srcX) { return cla3p::ops::mult(1, noOp, srcA, srcX); }
cla3p::dns::RdVector operator*(cla3p::dns::RdMatrix& srcA, const cla3p::dns::RdVector& srcX) { return cla3p::ops::mult(1, noOp, srcA, srcX); }
cla3p::dns::RfVector operator*(cla3p::dns::RfMatrix& srcA, const cla3p::dns::RfVector& srcX) { return cla3p::ops::mult(1, noOp, srcA, srcX); }
cla3p::dns::CdVector operator*(cla3p::dns::CdMatrix& srcA, const cla3p::dns::CdVector& srcX) { return cla3p::ops::mult(1, noOp, srcA, srcX); }
cla3p::dns::CfVector operator*(cla3p::dns::CfMatrix& srcA, const cla3p::dns::CfVector& srcX) { return cla3p::ops::mult(1, noOp, srcA, srcX); }

cla3p::dns::RiMatrix operator*(cla3p::dns::RiMatrix& srcA, const cla3p::dns::RiMatrix& srcB) { return cla3p::ops::mult(1, noOp, srcA, noOp, srcB); }
cla3p::dns::RdMatrix operator*(cla3p::dns::RdMatrix& srcA, const cla3p::dns::RdMatrix& srcB) { return cla3p::ops::mult(1, noOp, srcA, noOp, srcB); }
cla3p::dns::RfMatrix operator*(cla3p::dns::RfMatrix& srcA, const cla3p::dns::RfMatrix& srcB) { return cla3p::ops::mult(1, noOp, srcA, noOp, srcB); }
cla3p::dns::CdMatrix operator*(cla3p::dns::CdMatrix& srcA, const cla3p::dns::CdMatrix& srcB) { return cla3p::ops::mult(1, noOp, srcA, noOp, srcB); }
cla3p::dns::CfMatrix operator*(cla3p::dns::CfMatrix& srcA, const cla3p::dns::CfMatrix& srcB) { return cla3p::ops::mult(1, noOp, srcA, noOp, srcB); }

/*-------------------------------------------------*/

