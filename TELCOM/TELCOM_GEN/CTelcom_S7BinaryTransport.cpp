/*
 *********************************************************************
  Project:  PSI BT Framework++
 
  (C) Copyright PSI BT AG Duesseldorf (Germany) 2000
                    All Rights Reserved
 *********************************************************************
*/

#include "ccdep.h"
#include "CTelcom_S7BinaryTransport.h"
#include "PrimitiveTE.h"

#include "exceptions.h"

#include <iostream>
#include <algorithm>

using namespace std;

const int MAX_LEN = 4;

void CTelcom_S7BinaryTransport::pack(const PrimitiveTE &e, const EncodingRules &er, 
		              std::ostream &out)
{
	switch(e.getType()) {
	case PrimitiveTE::tInteger: 
		packInteger(e, out); 
		break;
  case PrimitiveTE::tNumber:
		packNumber(e, out); 
		break;
  default:
    throw EConvertError("transport type is applicable for integers and numbers only", e.getPath());
	}
}

void CTelcom_S7BinaryTransport::unpack(PrimitiveTE & e, const EncodingRules &er,
		                std::istream &in)
{
	switch(e.getType()) {
	case PrimitiveTE::tInteger: 
		unpackInteger(e, in);
		break;
	case PrimitiveTE::tNumber: 
		unpackNumber(e, in);
		break;
  default:
    throw EConvertError("transport type is applicable for integers and numbers only", e.getPath());
  }
}

void CTelcom_S7BinaryTransport::packInteger(const PrimitiveTE &e, std::ostream &out)
{
	long x = e.asInteger();
	int len = e.getLen();

  if (len > MAX_LEN) throw 
    EConvertError("invalid elementh's length", e.getPath());	

  // if (x < 0) throw EConvertError("negativ values are not allowed", e.getPath());

	char buf[MAX_LEN];

  for (int i=0; i<len; ++i)
  {
    buf[i] = x & 0xff;
    x >>= 8;
  }
  if (x > 0) throw EElemOverflow(e.getPath(), e.asString());

  swapBytes(buf, len);

  out.write(buf, len);
}

void CTelcom_S7BinaryTransport::packNumber(const PrimitiveTE &e, std::ostream &out)
{
	float x = (float)e.asNumber();
	int len = e.getLen();

  if (len > MAX_LEN) throw 
    EConvertError("invalid elementh's length", e.getPath());	


	char buf[MAX_LEN];
  memcpy(buf, &x, sizeof(buf));

  swapBytes(buf, len);

  out.write(buf, len);
}


void CTelcom_S7BinaryTransport::unpackInteger(PrimitiveTE &e, std::istream &in)
{
	int len = e.getLen();

  char buf[MAX_LEN];

  in.read(buf, len);

  swapBytes(buf, len);

  long n =0;
  for (int i=0; i<len; ++i)
  {
    unsigned char x = buf[i];
    n += (x << i*8);
  }
  e.set(n);
}

void CTelcom_S7BinaryTransport::unpackNumber(PrimitiveTE &e, std::istream &in)
{
	int len = e.getLen();

  if (len > MAX_LEN) throw 
    EConvertError("invalid elementh's length", e.getPath());	

  char buf[MAX_LEN];

  in.read(buf, len);

  swapBytes(buf, len);

  float n =0;
  memcpy(&n, buf, sizeof(buf));

  e.set((double)n);
}

void CTelcom_S7BinaryTransport::swapBytes(char buf[], int len)
{
  // ggf Worte umtauschen
  if (wordOrder == HL)
  {
    for (int i=0; i<len-2; ++i)
    {
      std::swap(buf[i], buf[i+2]);
    }
  }

  // ggf. Bytes umtauschen
  if (byteOrder == HL) 
  {
    for (int i=0; i<len-1; ++i) 
    {
      std::swap(buf[i], buf[i+1]);
      i += 1;
    }
  }
}