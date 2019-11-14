#ifndef _CTELCOM_S7BINARYTRANSPORT_H_
#define _CTELCOM_S7BINARYTRANSPORT_H_
/*
 *********************************************************************
  Project:  PSI BT Framework++
 
  (C) Copyright PSI BT AG Duesseldorf (Germany) 2000
                    All Rights Reserved
 *********************************************************************
*/

#include "TransType.h"

class EncodingRules;

/** 
  Binary transport type for integers.

  Die Länge ist entweder 2 oder 4 Byte.
  Im Konstruktor kann die Reihenfolge für die Worte und
  die einzelnen Bytes festgelegt werden.
  Nur positive Zahlen werde codiert.
*/
class CTelcom_S7BinaryTransport : public TransType  
{
public:
  enum ByteOrder { HL, LH };
  CTelcom_S7BinaryTransport(ByteOrder byteOrder = LH, ByteOrder wordOrder = LH): 
    byteOrder(byteOrder), wordOrder(wordOrder) { }

	virtual void pack(const PrimitiveTE &e, const EncodingRules &er, 
		              std::ostream &out);

	virtual void unpack(PrimitiveTE & e, const EncodingRules &er,
		                std::istream &in);
private:
  ByteOrder wordOrder;
  ByteOrder byteOrder;

  void packInteger(const PrimitiveTE &e, std::ostream &out);
  void unpackInteger(PrimitiveTE &e, std::istream &in);
  void packNumber(const PrimitiveTE &e, std::ostream &out);
  void unpackNumber(PrimitiveTE &e, std::istream &in);
  void swapBytes(char buf[], int len);
};

#endif
