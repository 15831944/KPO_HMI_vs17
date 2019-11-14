/*
****************************************
 File: Telcom_In

 TAM (Telegram Access Model) Classes
 generated on Mon Sep 16 11:10:48 IST 2019

*****************************************/

#include "Telcom_In.h"
#include <strstream>
// class: TEHeaderType
void TEHeaderType::load(std::istream & in, const string &_path_) throw (ETAMError)
{
	set(MessageLength, readField(in, _path_ +"MessageLength"), _path_ +"MessageLength");
	set(MessageId, readField(in, _path_ +"MessageId"), _path_ +"MessageId");
	set(MessageCount, readField(in, _path_ +"MessageCount"), _path_ +"MessageCount");
	set(UnitNo, readField(in, _path_ +"UnitNo"), _path_ +"UnitNo");
}
void TEHeaderType::serialize(std::ostream & out, const string &_path_) throw (ETAMError)
{
	writeField(out, MessageLength.asString(), _path_ +"MessageLength");
	writeField(out, MessageId.asString(), _path_ +"MessageId");
	writeField(out, MessageCount.asString(), _path_ +"MessageCount");
	writeField(out, UnitNo.asString(), _path_ +"UnitNo");
}
// class: Head
void Head::load(std::istream & in, const string &_path_) throw (ETAMError)
{
	set(MessageLength, readField(in, _path_ +"MessageLength"), _path_ +"MessageLength");
	set(MessageId, readField(in, _path_ +"MessageId"), _path_ +"MessageId");
	set(MessageCount, readField(in, _path_ +"MessageCount"), _path_ +"MessageCount");
	set(UnitNo, readField(in, _path_ +"UnitNo"), _path_ +"UnitNo");
}
void Head::serialize(std::ostream & out, const string &_path_) throw (ETAMError)
{
	writeField(out, MessageLength.asString(), _path_ +"MessageLength");
	writeField(out, MessageId.asString(), _path_ +"MessageId");
	writeField(out, MessageCount.asString(), _path_ +"MessageCount");
	writeField(out, UnitNo.asString(), _path_ +"UnitNo");
}
// class: LFL200
void LFL200::load(std::istream & in, const string &_path_) throw (ETAMError)
{
	Header.load(in, _path_ +"Header"+ "/" );
	set(Status, readField(in, _path_ +"Status"), _path_ +"Status");
	set(RcvMsgId, readField(in, _path_ +"RcvMsgId"), _path_ +"RcvMsgId");
	set(ErrInf, readField(in, _path_ +"ErrInf"), _path_ +"ErrInf");
	set(ErrMess, readField(in, _path_ +"ErrMess"), _path_ +"ErrMess");
}
void LFL200::serialize(std::ostream & out, const string &_path_) throw (ETAMError)
{
	Header.serialize(out, _path_ +"Header"+ "/" );
	writeField(out, Status.asString(), _path_ +"Status");
	writeField(out, RcvMsgId.asString(), _path_ +"RcvMsgId");
	writeField(out, ErrInf.asString(), _path_ +"ErrInf");
	writeField(out, ErrMess.asString(), _path_ +"ErrMess");
}
// class: LFL201
void LFL201::load(std::istream & in, const string &_path_) throw (ETAMError)
{
	Header.load(in, _path_ +"Header"+ "/" );
	{
		CreateTime.clear();
		for (int _i_=0; _i_<8; _i_++)
		{
			std::ostrstream _ostr_;
			_ostr_ << "CreateTime[" << _i_ << "]" << std::ends;
			CreateTime.push_back(IntegerVal());
			set(CreateTime[_i_], readField(in, _path_ +_ostr_.str()), _path_ +_ostr_.str());
			_ostr_.freeze(0);
		}
	}
	set(Address, readField(in, _path_ +"Address"), _path_ +"Address");
}
void LFL201::serialize(std::ostream & out, const string &_path_) throw (ETAMError)
{
	Header.serialize(out, _path_ +"Header"+ "/" );
	{
		IntegerVal _tmp;
		for (int _i_=0; _i_<8; _i_++)
		{
			std::ostrstream _ostr_;
			_ostr_ << "CreateTime[" << _i_ << "]" << std::ends;
			if (_i_ < CreateTime.size())
			{
				writeField(out, CreateTime[_i_].asString(), _path_ +_ostr_.str());
			}
			else
			{
				writeField(out, _tmp.asString(), _path_ +_ostr_.str());
			}
			_ostr_.freeze(0);
		}
	}
	writeField(out, Address.asString(), _path_ +"Address");
}
// class: LFL203
void LFL203::load(std::istream & in, const string &_path_) throw (ETAMError)
{
	Header.load(in, _path_ +"Header"+ "/" );
	{
		CreateTime.clear();
		for (int _i_=0; _i_<8; _i_++)
		{
			std::ostrstream _ostr_;
			_ostr_ << "CreateTime[" << _i_ << "]" << std::ends;
			CreateTime.push_back(IntegerVal());
			set(CreateTime[_i_], readField(in, _path_ +_ostr_.str()), _path_ +_ostr_.str());
			_ostr_.freeze(0);
		}
	}
	set(HeatId, readField(in, _path_ +"HeatId"), _path_ +"HeatId");
	set(TreatId, readField(in, _path_ +"TreatId"), _path_ +"TreatId");
	set(LadleId, readField(in, _path_ +"LadleId"), _path_ +"LadleId");
	set(CarNo, readField(in, _path_ +"CarNo"), _path_ +"CarNo");
	set(ProdOrderId, readField(in, _path_ +"ProdOrderId"), _path_ +"ProdOrderId");
	set(SteelGradeCode, readField(in, _path_ +"SteelGradeCode"), _path_ +"SteelGradeCode");
	set(AimTemp, readField(in, _path_ +"AimTemp"), _path_ +"AimTemp");
	set(AimWeight, readField(in, _path_ +"AimWeight"), _path_ +"AimWeight");
	set(HeatIdCust, readField(in, _path_ +"HeatIdCust"), _path_ +"HeatIdCust");
	set(TreatIdCust, readField(in, _path_ +"TreatIdCust"), _path_ +"TreatIdCust");
	{
		Spare.clear();
		for (int _i_=0; _i_<5; _i_++)
		{
			std::ostrstream _ostr_;
			_ostr_ << "Spare[" << _i_ << "]" << std::ends;
			Spare.push_back(IntegerVal());
			set(Spare[_i_], readField(in, _path_ +_ostr_.str()), _path_ +_ostr_.str());
			_ostr_.freeze(0);
		}
	}
}
void LFL203::serialize(std::ostream & out, const string &_path_) throw (ETAMError)
{
	Header.serialize(out, _path_ +"Header"+ "/" );
	{
		IntegerVal _tmp;
		for (int _i_=0; _i_<8; _i_++)
		{
			std::ostrstream _ostr_;
			_ostr_ << "CreateTime[" << _i_ << "]" << std::ends;
			if (_i_ < CreateTime.size())
			{
				writeField(out, CreateTime[_i_].asString(), _path_ +_ostr_.str());
			}
			else
			{
				writeField(out, _tmp.asString(), _path_ +_ostr_.str());
			}
			_ostr_.freeze(0);
		}
	}
	writeField(out, HeatId.asString(), _path_ +"HeatId");
	writeField(out, TreatId.asString(), _path_ +"TreatId");
	writeField(out, LadleId.asString(), _path_ +"LadleId");
	writeField(out, CarNo.asString(), _path_ +"CarNo");
	writeField(out, ProdOrderId.asString(), _path_ +"ProdOrderId");
	writeField(out, SteelGradeCode.asString(), _path_ +"SteelGradeCode");
	writeField(out, AimTemp.asString(), _path_ +"AimTemp");
	writeField(out, AimWeight.asString(), _path_ +"AimWeight");
	writeField(out, HeatIdCust.asString(), _path_ +"HeatIdCust");
	writeField(out, TreatIdCust.asString(), _path_ +"TreatIdCust");
	{
		IntegerVal _tmp;
		for (int _i_=0; _i_<5; _i_++)
		{
			std::ostrstream _ostr_;
			_ostr_ << "Spare[" << _i_ << "]" << std::ends;
			if (_i_ < Spare.size())
			{
				writeField(out, Spare[_i_].asString(), _path_ +_ostr_.str());
			}
			else
			{
				writeField(out, _tmp.asString(), _path_ +_ostr_.str());
			}
			_ostr_.freeze(0);
		}
	}
}
// class: LFL204
void LFL204::load(std::istream & in, const string &_path_) throw (ETAMError)
{
	Header.load(in, _path_ +"Header"+ "/" );
	{
		CreateTime.clear();
		for (int _i_=0; _i_<8; _i_++)
		{
			std::ostrstream _ostr_;
			_ostr_ << "CreateTime[" << _i_ << "]" << std::ends;
			CreateTime.push_back(IntegerVal());
			set(CreateTime[_i_], readField(in, _path_ +_ostr_.str()), _path_ +_ostr_.str());
			_ostr_.freeze(0);
		}
	}
	set(HeatId, readField(in, _path_ +"HeatId"), _path_ +"HeatId");
	set(TreatId, readField(in, _path_ +"TreatId"), _path_ +"TreatId");
	set(LadleId, readField(in, _path_ +"LadleId"), _path_ +"LadleId");
	set(CarNo, readField(in, _path_ +"CarNo"), _path_ +"CarNo");
	{
		Spare.clear();
		for (int _i_=0; _i_<5; _i_++)
		{
			std::ostrstream _ostr_;
			_ostr_ << "Spare[" << _i_ << "]" << std::ends;
			Spare.push_back(IntegerVal());
			set(Spare[_i_], readField(in, _path_ +_ostr_.str()), _path_ +_ostr_.str());
			_ostr_.freeze(0);
		}
	}
}
void LFL204::serialize(std::ostream & out, const string &_path_) throw (ETAMError)
{
	Header.serialize(out, _path_ +"Header"+ "/" );
	{
		IntegerVal _tmp;
		for (int _i_=0; _i_<8; _i_++)
		{
			std::ostrstream _ostr_;
			_ostr_ << "CreateTime[" << _i_ << "]" << std::ends;
			if (_i_ < CreateTime.size())
			{
				writeField(out, CreateTime[_i_].asString(), _path_ +_ostr_.str());
			}
			else
			{
				writeField(out, _tmp.asString(), _path_ +_ostr_.str());
			}
			_ostr_.freeze(0);
		}
	}
	writeField(out, HeatId.asString(), _path_ +"HeatId");
	writeField(out, TreatId.asString(), _path_ +"TreatId");
	writeField(out, LadleId.asString(), _path_ +"LadleId");
	writeField(out, CarNo.asString(), _path_ +"CarNo");
	{
		IntegerVal _tmp;
		for (int _i_=0; _i_<5; _i_++)
		{
			std::ostrstream _ostr_;
			_ostr_ << "Spare[" << _i_ << "]" << std::ends;
			if (_i_ < Spare.size())
			{
				writeField(out, Spare[_i_].asString(), _path_ +_ostr_.str());
			}
			else
			{
				writeField(out, _tmp.asString(), _path_ +_ostr_.str());
			}
			_ostr_.freeze(0);
		}
	}
}
// class: LFL205
void LFL205::load(std::istream & in, const string &_path_) throw (ETAMError)
{
	Header.load(in, _path_ +"Header"+ "/" );
	{
		CreateTime.clear();
		for (int _i_=0; _i_<8; _i_++)
		{
			std::ostrstream _ostr_;
			_ostr_ << "CreateTime[" << _i_ << "]" << std::ends;
			CreateTime.push_back(IntegerVal());
			set(CreateTime[_i_], readField(in, _path_ +_ostr_.str()), _path_ +_ostr_.str());
			_ostr_.freeze(0);
		}
	}
	set(HeatId, readField(in, _path_ +"HeatId"), _path_ +"HeatId");
	set(TreatId, readField(in, _path_ +"TreatId"), _path_ +"TreatId");
	set(LadleId, readField(in, _path_ +"LadleId"), _path_ +"LadleId");
	set(CarNo, readField(in, _path_ +"CarNo"), _path_ +"CarNo");
	set(ActionFlag, readField(in, _path_ +"ActionFlag"), _path_ +"ActionFlag");
	{
		Spare.clear();
		for (int _i_=0; _i_<5; _i_++)
		{
			std::ostrstream _ostr_;
			_ostr_ << "Spare[" << _i_ << "]" << std::ends;
			Spare.push_back(IntegerVal());
			set(Spare[_i_], readField(in, _path_ +_ostr_.str()), _path_ +_ostr_.str());
			_ostr_.freeze(0);
		}
	}
}
void LFL205::serialize(std::ostream & out, const string &_path_) throw (ETAMError)
{
	Header.serialize(out, _path_ +"Header"+ "/" );
	{
		IntegerVal _tmp;
		for (int _i_=0; _i_<8; _i_++)
		{
			std::ostrstream _ostr_;
			_ostr_ << "CreateTime[" << _i_ << "]" << std::ends;
			if (_i_ < CreateTime.size())
			{
				writeField(out, CreateTime[_i_].asString(), _path_ +_ostr_.str());
			}
			else
			{
				writeField(out, _tmp.asString(), _path_ +_ostr_.str());
			}
			_ostr_.freeze(0);
		}
	}
	writeField(out, HeatId.asString(), _path_ +"HeatId");
	writeField(out, TreatId.asString(), _path_ +"TreatId");
	writeField(out, LadleId.asString(), _path_ +"LadleId");
	writeField(out, CarNo.asString(), _path_ +"CarNo");
	writeField(out, ActionFlag.asString(), _path_ +"ActionFlag");
	{
		IntegerVal _tmp;
		for (int _i_=0; _i_<5; _i_++)
		{
			std::ostrstream _ostr_;
			_ostr_ << "Spare[" << _i_ << "]" << std::ends;
			if (_i_ < Spare.size())
			{
				writeField(out, Spare[_i_].asString(), _path_ +_ostr_.str());
			}
			else
			{
				writeField(out, _tmp.asString(), _path_ +_ostr_.str());
			}
			_ostr_.freeze(0);
		}
	}
}
// class: LFL206
void LFL206::load(std::istream & in, const string &_path_) throw (ETAMError)
{
	Header.load(in, _path_ +"Header"+ "/" );
	{
		CreateTime.clear();
		for (int _i_=0; _i_<8; _i_++)
		{
			std::ostrstream _ostr_;
			_ostr_ << "CreateTime[" << _i_ << "]" << std::ends;
			CreateTime.push_back(IntegerVal());
			set(CreateTime[_i_], readField(in, _path_ +_ostr_.str()), _path_ +_ostr_.str());
			_ostr_.freeze(0);
		}
	}
	set(HeatId, readField(in, _path_ +"HeatId"), _path_ +"HeatId");
	set(TreatId, readField(in, _path_ +"TreatId"), _path_ +"TreatId");
	set(CarNo, readField(in, _path_ +"CarNo"), _path_ +"CarNo");
	{
		Spare.clear();
		for (int _i_=0; _i_<5; _i_++)
		{
			std::ostrstream _ostr_;
			_ostr_ << "Spare[" << _i_ << "]" << std::ends;
			Spare.push_back(IntegerVal());
			set(Spare[_i_], readField(in, _path_ +_ostr_.str()), _path_ +_ostr_.str());
			_ostr_.freeze(0);
		}
	}
}
void LFL206::serialize(std::ostream & out, const string &_path_) throw (ETAMError)
{
	Header.serialize(out, _path_ +"Header"+ "/" );
	{
		IntegerVal _tmp;
		for (int _i_=0; _i_<8; _i_++)
		{
			std::ostrstream _ostr_;
			_ostr_ << "CreateTime[" << _i_ << "]" << std::ends;
			if (_i_ < CreateTime.size())
			{
				writeField(out, CreateTime[_i_].asString(), _path_ +_ostr_.str());
			}
			else
			{
				writeField(out, _tmp.asString(), _path_ +_ostr_.str());
			}
			_ostr_.freeze(0);
		}
	}
	writeField(out, HeatId.asString(), _path_ +"HeatId");
	writeField(out, TreatId.asString(), _path_ +"TreatId");
	writeField(out, CarNo.asString(), _path_ +"CarNo");
	{
		IntegerVal _tmp;
		for (int _i_=0; _i_<5; _i_++)
		{
			std::ostrstream _ostr_;
			_ostr_ << "Spare[" << _i_ << "]" << std::ends;
			if (_i_ < Spare.size())
			{
				writeField(out, Spare[_i_].asString(), _path_ +_ostr_.str());
			}
			else
			{
				writeField(out, _tmp.asString(), _path_ +_ostr_.str());
			}
			_ostr_.freeze(0);
		}
	}
}
// class: LFL209
void LFL209::load(std::istream & in, const string &_path_) throw (ETAMError)
{
	Header.load(in, _path_ +"Header"+ "/" );
	{
		CreateTime.clear();
		for (int _i_=0; _i_<8; _i_++)
		{
			std::ostrstream _ostr_;
			_ostr_ << "CreateTime[" << _i_ << "]" << std::ends;
			CreateTime.push_back(IntegerVal());
			set(CreateTime[_i_], readField(in, _path_ +_ostr_.str()), _path_ +_ostr_.str());
			_ostr_.freeze(0);
		}
	}
	set(HeatId, readField(in, _path_ +"HeatId"), _path_ +"HeatId");
	set(TreatId, readField(in, _path_ +"TreatId"), _path_ +"TreatId");
	set(CarNo, readField(in, _path_ +"CarNo"), _path_ +"CarNo");
	set(SampleType, readField(in, _path_ +"SampleType"), _path_ +"SampleType");
	set(SampleCounter, readField(in, _path_ +"SampleCounter"), _path_ +"SampleCounter");
	{
		Spare.clear();
		for (int _i_=0; _i_<5; _i_++)
		{
			std::ostrstream _ostr_;
			_ostr_ << "Spare[" << _i_ << "]" << std::ends;
			Spare.push_back(IntegerVal());
			set(Spare[_i_], readField(in, _path_ +_ostr_.str()), _path_ +_ostr_.str());
			_ostr_.freeze(0);
		}
	}
}
void LFL209::serialize(std::ostream & out, const string &_path_) throw (ETAMError)
{
	Header.serialize(out, _path_ +"Header"+ "/" );
	{
		IntegerVal _tmp;
		for (int _i_=0; _i_<8; _i_++)
		{
			std::ostrstream _ostr_;
			_ostr_ << "CreateTime[" << _i_ << "]" << std::ends;
			if (_i_ < CreateTime.size())
			{
				writeField(out, CreateTime[_i_].asString(), _path_ +_ostr_.str());
			}
			else
			{
				writeField(out, _tmp.asString(), _path_ +_ostr_.str());
			}
			_ostr_.freeze(0);
		}
	}
	writeField(out, HeatId.asString(), _path_ +"HeatId");
	writeField(out, TreatId.asString(), _path_ +"TreatId");
	writeField(out, CarNo.asString(), _path_ +"CarNo");
	writeField(out, SampleType.asString(), _path_ +"SampleType");
	writeField(out, SampleCounter.asString(), _path_ +"SampleCounter");
	{
		IntegerVal _tmp;
		for (int _i_=0; _i_<5; _i_++)
		{
			std::ostrstream _ostr_;
			_ostr_ << "Spare[" << _i_ << "]" << std::ends;
			if (_i_ < Spare.size())
			{
				writeField(out, Spare[_i_].asString(), _path_ +_ostr_.str());
			}
			else
			{
				writeField(out, _tmp.asString(), _path_ +_ostr_.str());
			}
			_ostr_.freeze(0);
		}
	}
}
// class: LFL211
void LFL211::load(std::istream & in, const string &_path_) throw (ETAMError)
{
	Header.load(in, _path_ +"Header"+ "/" );
	{
		CreateTime.clear();
		for (int _i_=0; _i_<8; _i_++)
		{
			std::ostrstream _ostr_;
			_ostr_ << "CreateTime[" << _i_ << "]" << std::ends;
			CreateTime.push_back(IntegerVal());
			set(CreateTime[_i_], readField(in, _path_ +_ostr_.str()), _path_ +_ostr_.str());
			_ostr_.freeze(0);
		}
	}
	set(HeatId, readField(in, _path_ +"HeatId"), _path_ +"HeatId");
	set(TreatId, readField(in, _path_ +"TreatId"), _path_ +"TreatId");
	set(CarNo, readField(in, _path_ +"CarNo"), _path_ +"CarNo");
	set(MeasType, readField(in, _path_ +"MeasType"), _path_ +"MeasType");
	set(MeasNo, readField(in, _path_ +"MeasNo"), _path_ +"MeasNo");
	set(Temp, readField(in, _path_ +"Temp"), _path_ +"Temp");
	set(ConcO2, readField(in, _path_ +"ConcO2"), _path_ +"ConcO2");
	set(ConcAl, readField(in, _path_ +"ConcAl"), _path_ +"ConcAl");
	set(ConcC, readField(in, _path_ +"ConcC"), _path_ +"ConcC");
	set(ConcFeO, readField(in, _path_ +"ConcFeO"), _path_ +"ConcFeO");
	set(ConcMnO, readField(in, _path_ +"ConcMnO"), _path_ +"ConcMnO");
	{
		Spare.clear();
		for (int _i_=0; _i_<5; _i_++)
		{
			std::ostrstream _ostr_;
			_ostr_ << "Spare[" << _i_ << "]" << std::ends;
			Spare.push_back(IntegerVal());
			set(Spare[_i_], readField(in, _path_ +_ostr_.str()), _path_ +_ostr_.str());
			_ostr_.freeze(0);
		}
	}
}
void LFL211::serialize(std::ostream & out, const string &_path_) throw (ETAMError)
{
	Header.serialize(out, _path_ +"Header"+ "/" );
	{
		IntegerVal _tmp;
		for (int _i_=0; _i_<8; _i_++)
		{
			std::ostrstream _ostr_;
			_ostr_ << "CreateTime[" << _i_ << "]" << std::ends;
			if (_i_ < CreateTime.size())
			{
				writeField(out, CreateTime[_i_].asString(), _path_ +_ostr_.str());
			}
			else
			{
				writeField(out, _tmp.asString(), _path_ +_ostr_.str());
			}
			_ostr_.freeze(0);
		}
	}
	writeField(out, HeatId.asString(), _path_ +"HeatId");
	writeField(out, TreatId.asString(), _path_ +"TreatId");
	writeField(out, CarNo.asString(), _path_ +"CarNo");
	writeField(out, MeasType.asString(), _path_ +"MeasType");
	writeField(out, MeasNo.asString(), _path_ +"MeasNo");
	writeField(out, Temp.asString(), _path_ +"Temp");
	writeField(out, ConcO2.asString(), _path_ +"ConcO2");
	writeField(out, ConcAl.asString(), _path_ +"ConcAl");
	writeField(out, ConcC.asString(), _path_ +"ConcC");
	writeField(out, ConcFeO.asString(), _path_ +"ConcFeO");
	writeField(out, ConcMnO.asString(), _path_ +"ConcMnO");
	{
		IntegerVal _tmp;
		for (int _i_=0; _i_<5; _i_++)
		{
			std::ostrstream _ostr_;
			_ostr_ << "Spare[" << _i_ << "]" << std::ends;
			if (_i_ < Spare.size())
			{
				writeField(out, Spare[_i_].asString(), _path_ +_ostr_.str());
			}
			else
			{
				writeField(out, _tmp.asString(), _path_ +_ostr_.str());
			}
			_ostr_.freeze(0);
		}
	}
}
// class: LFL212
void LFL212::load(std::istream & in, const string &_path_) throw (ETAMError)
{
	Header.load(in, _path_ +"Header"+ "/" );
	{
		CreateTime.clear();
		for (int _i_=0; _i_<8; _i_++)
		{
			std::ostrstream _ostr_;
			_ostr_ << "CreateTime[" << _i_ << "]" << std::ends;
			CreateTime.push_back(IntegerVal());
			set(CreateTime[_i_], readField(in, _path_ +_ostr_.str()), _path_ +_ostr_.str());
			_ostr_.freeze(0);
		}
	}
	set(HeatId, readField(in, _path_ +"HeatId"), _path_ +"HeatId");
	set(TreatId, readField(in, _path_ +"TreatId"), _path_ +"TreatId");
	set(AimTemp, readField(in, _path_ +"AimTemp"), _path_ +"AimTemp");
	{
		Spare.clear();
		for (int _i_=0; _i_<5; _i_++)
		{
			std::ostrstream _ostr_;
			_ostr_ << "Spare[" << _i_ << "]" << std::ends;
			Spare.push_back(IntegerVal());
			set(Spare[_i_], readField(in, _path_ +_ostr_.str()), _path_ +_ostr_.str());
			_ostr_.freeze(0);
		}
	}
}
void LFL212::serialize(std::ostream & out, const string &_path_) throw (ETAMError)
{
	Header.serialize(out, _path_ +"Header"+ "/" );
	{
		IntegerVal _tmp;
		for (int _i_=0; _i_<8; _i_++)
		{
			std::ostrstream _ostr_;
			_ostr_ << "CreateTime[" << _i_ << "]" << std::ends;
			if (_i_ < CreateTime.size())
			{
				writeField(out, CreateTime[_i_].asString(), _path_ +_ostr_.str());
			}
			else
			{
				writeField(out, _tmp.asString(), _path_ +_ostr_.str());
			}
			_ostr_.freeze(0);
		}
	}
	writeField(out, HeatId.asString(), _path_ +"HeatId");
	writeField(out, TreatId.asString(), _path_ +"TreatId");
	writeField(out, AimTemp.asString(), _path_ +"AimTemp");
	{
		IntegerVal _tmp;
		for (int _i_=0; _i_<5; _i_++)
		{
			std::ostrstream _ostr_;
			_ostr_ << "Spare[" << _i_ << "]" << std::ends;
			if (_i_ < Spare.size())
			{
				writeField(out, Spare[_i_].asString(), _path_ +_ostr_.str());
			}
			else
			{
				writeField(out, _tmp.asString(), _path_ +_ostr_.str());
			}
			_ostr_.freeze(0);
		}
	}
}
// class: LFL213
void LFL213::load(std::istream & in, const string &_path_) throw (ETAMError)
{
	Header.load(in, _path_ +"Header"+ "/" );
	{
		CreateTime.clear();
		for (int _i_=0; _i_<8; _i_++)
		{
			std::ostrstream _ostr_;
			_ostr_ << "CreateTime[" << _i_ << "]" << std::ends;
			CreateTime.push_back(IntegerVal());
			set(CreateTime[_i_], readField(in, _path_ +_ostr_.str()), _path_ +_ostr_.str());
			_ostr_.freeze(0);
		}
	}
	set(HeatId, readField(in, _path_ +"HeatId"), _path_ +"HeatId");
	set(TreatId, readField(in, _path_ +"TreatId"), _path_ +"TreatId");
	{
		AimDepTime.clear();
		for (int _i_=0; _i_<8; _i_++)
		{
			std::ostrstream _ostr_;
			_ostr_ << "AimDepTime[" << _i_ << "]" << std::ends;
			AimDepTime.push_back(IntegerVal());
			set(AimDepTime[_i_], readField(in, _path_ +_ostr_.str()), _path_ +_ostr_.str());
			_ostr_.freeze(0);
		}
	}
	{
		Spare.clear();
		for (int _i_=0; _i_<5; _i_++)
		{
			std::ostrstream _ostr_;
			_ostr_ << "Spare[" << _i_ << "]" << std::ends;
			Spare.push_back(IntegerVal());
			set(Spare[_i_], readField(in, _path_ +_ostr_.str()), _path_ +_ostr_.str());
			_ostr_.freeze(0);
		}
	}
}
void LFL213::serialize(std::ostream & out, const string &_path_) throw (ETAMError)
{
	Header.serialize(out, _path_ +"Header"+ "/" );
	{
		IntegerVal _tmp;
		for (int _i_=0; _i_<8; _i_++)
		{
			std::ostrstream _ostr_;
			_ostr_ << "CreateTime[" << _i_ << "]" << std::ends;
			if (_i_ < CreateTime.size())
			{
				writeField(out, CreateTime[_i_].asString(), _path_ +_ostr_.str());
			}
			else
			{
				writeField(out, _tmp.asString(), _path_ +_ostr_.str());
			}
			_ostr_.freeze(0);
		}
	}
	writeField(out, HeatId.asString(), _path_ +"HeatId");
	writeField(out, TreatId.asString(), _path_ +"TreatId");
	{
		IntegerVal _tmp;
		for (int _i_=0; _i_<8; _i_++)
		{
			std::ostrstream _ostr_;
			_ostr_ << "AimDepTime[" << _i_ << "]" << std::ends;
			if (_i_ < AimDepTime.size())
			{
				writeField(out, AimDepTime[_i_].asString(), _path_ +_ostr_.str());
			}
			else
			{
				writeField(out, _tmp.asString(), _path_ +_ostr_.str());
			}
			_ostr_.freeze(0);
		}
	}
	{
		IntegerVal _tmp;
		for (int _i_=0; _i_<5; _i_++)
		{
			std::ostrstream _ostr_;
			_ostr_ << "Spare[" << _i_ << "]" << std::ends;
			if (_i_ < Spare.size())
			{
				writeField(out, Spare[_i_].asString(), _path_ +_ostr_.str());
			}
			else
			{
				writeField(out, _tmp.asString(), _path_ +_ostr_.str());
			}
			_ostr_.freeze(0);
		}
	}
}
// class: LFL217
void LFL217::load(std::istream & in, const string &_path_) throw (ETAMError)
{
	Header.load(in, _path_ +"Header"+ "/" );
	{
		CreateTime.clear();
		for (int _i_=0; _i_<8; _i_++)
		{
			std::ostrstream _ostr_;
			_ostr_ << "CreateTime[" << _i_ << "]" << std::ends;
			CreateTime.push_back(IntegerVal());
			set(CreateTime[_i_], readField(in, _path_ +_ostr_.str()), _path_ +_ostr_.str());
			_ostr_.freeze(0);
		}
	}
	set(HeatId, readField(in, _path_ +"HeatId"), _path_ +"HeatId");
	set(TreatId, readField(in, _path_ +"TreatId"), _path_ +"TreatId");
	set(CarNo, readField(in, _path_ +"CarNo"), _path_ +"CarNo");
	set(DelayCode, readField(in, _path_ +"DelayCode"), _path_ +"DelayCode");
	{
		DelayStartTime.clear();
		for (int _i_=0; _i_<8; _i_++)
		{
			std::ostrstream _ostr_;
			_ostr_ << "DelayStartTime[" << _i_ << "]" << std::ends;
			DelayStartTime.push_back(IntegerVal());
			set(DelayStartTime[_i_], readField(in, _path_ +_ostr_.str()), _path_ +_ostr_.str());
			_ostr_.freeze(0);
		}
	}
	{
		DelayEndTime.clear();
		for (int _i_=0; _i_<8; _i_++)
		{
			std::ostrstream _ostr_;
			_ostr_ << "DelayEndTime[" << _i_ << "]" << std::ends;
			DelayEndTime.push_back(IntegerVal());
			set(DelayEndTime[_i_], readField(in, _path_ +_ostr_.str()), _path_ +_ostr_.str());
			_ostr_.freeze(0);
		}
	}
	{
		Spare.clear();
		for (int _i_=0; _i_<5; _i_++)
		{
			std::ostrstream _ostr_;
			_ostr_ << "Spare[" << _i_ << "]" << std::ends;
			Spare.push_back(IntegerVal());
			set(Spare[_i_], readField(in, _path_ +_ostr_.str()), _path_ +_ostr_.str());
			_ostr_.freeze(0);
		}
	}
}
void LFL217::serialize(std::ostream & out, const string &_path_) throw (ETAMError)
{
	Header.serialize(out, _path_ +"Header"+ "/" );
	{
		IntegerVal _tmp;
		for (int _i_=0; _i_<8; _i_++)
		{
			std::ostrstream _ostr_;
			_ostr_ << "CreateTime[" << _i_ << "]" << std::ends;
			if (_i_ < CreateTime.size())
			{
				writeField(out, CreateTime[_i_].asString(), _path_ +_ostr_.str());
			}
			else
			{
				writeField(out, _tmp.asString(), _path_ +_ostr_.str());
			}
			_ostr_.freeze(0);
		}
	}
	writeField(out, HeatId.asString(), _path_ +"HeatId");
	writeField(out, TreatId.asString(), _path_ +"TreatId");
	writeField(out, CarNo.asString(), _path_ +"CarNo");
	writeField(out, DelayCode.asString(), _path_ +"DelayCode");
	{
		IntegerVal _tmp;
		for (int _i_=0; _i_<8; _i_++)
		{
			std::ostrstream _ostr_;
			_ostr_ << "DelayStartTime[" << _i_ << "]" << std::ends;
			if (_i_ < DelayStartTime.size())
			{
				writeField(out, DelayStartTime[_i_].asString(), _path_ +_ostr_.str());
			}
			else
			{
				writeField(out, _tmp.asString(), _path_ +_ostr_.str());
			}
			_ostr_.freeze(0);
		}
	}
	{
		IntegerVal _tmp;
		for (int _i_=0; _i_<8; _i_++)
		{
			std::ostrstream _ostr_;
			_ostr_ << "DelayEndTime[" << _i_ << "]" << std::ends;
			if (_i_ < DelayEndTime.size())
			{
				writeField(out, DelayEndTime[_i_].asString(), _path_ +_ostr_.str());
			}
			else
			{
				writeField(out, _tmp.asString(), _path_ +_ostr_.str());
			}
			_ostr_.freeze(0);
		}
	}
	{
		IntegerVal _tmp;
		for (int _i_=0; _i_<5; _i_++)
		{
			std::ostrstream _ostr_;
			_ostr_ << "Spare[" << _i_ << "]" << std::ends;
			if (_i_ < Spare.size())
			{
				writeField(out, Spare[_i_].asString(), _path_ +_ostr_.str());
			}
			else
			{
				writeField(out, _tmp.asString(), _path_ +_ostr_.str());
			}
			_ostr_.freeze(0);
		}
	}
}
// class: LFL220
void LFL220::load(std::istream & in, const string &_path_) throw (ETAMError)
{
	Header.load(in, _path_ +"Header"+ "/" );
	{
		CreateTime.clear();
		for (int _i_=0; _i_<8; _i_++)
		{
			std::ostrstream _ostr_;
			_ostr_ << "CreateTime[" << _i_ << "]" << std::ends;
			CreateTime.push_back(IntegerVal());
			set(CreateTime[_i_], readField(in, _path_ +_ostr_.str()), _path_ +_ostr_.str());
			_ostr_.freeze(0);
		}
	}
	set(HeatId, readField(in, _path_ +"HeatId"), _path_ +"HeatId");
	set(TreatId, readField(in, _path_ +"TreatId"), _path_ +"TreatId");
	set(CarNo, readField(in, _path_ +"CarNo"), _path_ +"CarNo");
	set(ModeElec, readField(in, _path_ +"ModeElec"), _path_ +"ModeElec");
	set(ModeStirr, readField(in, _path_ +"ModeStirr"), _path_ +"ModeStirr");
	set(ModeMat, readField(in, _path_ +"ModeMat"), _path_ +"ModeMat");
	{
		Spare.clear();
		for (int _i_=0; _i_<5; _i_++)
		{
			std::ostrstream _ostr_;
			_ostr_ << "Spare[" << _i_ << "]" << std::ends;
			Spare.push_back(IntegerVal());
			set(Spare[_i_], readField(in, _path_ +_ostr_.str()), _path_ +_ostr_.str());
			_ostr_.freeze(0);
		}
	}
}
void LFL220::serialize(std::ostream & out, const string &_path_) throw (ETAMError)
{
	Header.serialize(out, _path_ +"Header"+ "/" );
	{
		IntegerVal _tmp;
		for (int _i_=0; _i_<8; _i_++)
		{
			std::ostrstream _ostr_;
			_ostr_ << "CreateTime[" << _i_ << "]" << std::ends;
			if (_i_ < CreateTime.size())
			{
				writeField(out, CreateTime[_i_].asString(), _path_ +_ostr_.str());
			}
			else
			{
				writeField(out, _tmp.asString(), _path_ +_ostr_.str());
			}
			_ostr_.freeze(0);
		}
	}
	writeField(out, HeatId.asString(), _path_ +"HeatId");
	writeField(out, TreatId.asString(), _path_ +"TreatId");
	writeField(out, CarNo.asString(), _path_ +"CarNo");
	writeField(out, ModeElec.asString(), _path_ +"ModeElec");
	writeField(out, ModeStirr.asString(), _path_ +"ModeStirr");
	writeField(out, ModeMat.asString(), _path_ +"ModeMat");
	{
		IntegerVal _tmp;
		for (int _i_=0; _i_<5; _i_++)
		{
			std::ostrstream _ostr_;
			_ostr_ << "Spare[" << _i_ << "]" << std::ends;
			if (_i_ < Spare.size())
			{
				writeField(out, Spare[_i_].asString(), _path_ +_ostr_.str());
			}
			else
			{
				writeField(out, _tmp.asString(), _path_ +_ostr_.str());
			}
			_ostr_.freeze(0);
		}
	}
}
// class: LFL221
void LFL221::load(std::istream & in, const string &_path_) throw (ETAMError)
{
	Header.load(in, _path_ +"Header"+ "/" );
	{
		CreateTime.clear();
		for (int _i_=0; _i_<8; _i_++)
		{
			std::ostrstream _ostr_;
			_ostr_ << "CreateTime[" << _i_ << "]" << std::ends;
			CreateTime.push_back(IntegerVal());
			set(CreateTime[_i_], readField(in, _path_ +_ostr_.str()), _path_ +_ostr_.str());
			_ostr_.freeze(0);
		}
	}
	set(GantryPos, readField(in, _path_ +"GantryPos"), _path_ +"GantryPos");
	set(RoofPos, readField(in, _path_ +"RoofPos"), _path_ +"RoofPos");
	set(CarNo, readField(in, _path_ +"CarNo"), _path_ +"CarNo");
	{
		Spare.clear();
		for (int _i_=0; _i_<5; _i_++)
		{
			std::ostrstream _ostr_;
			_ostr_ << "Spare[" << _i_ << "]" << std::ends;
			Spare.push_back(IntegerVal());
			set(Spare[_i_], readField(in, _path_ +_ostr_.str()), _path_ +_ostr_.str());
			_ostr_.freeze(0);
		}
	}
}
void LFL221::serialize(std::ostream & out, const string &_path_) throw (ETAMError)
{
	Header.serialize(out, _path_ +"Header"+ "/" );
	{
		IntegerVal _tmp;
		for (int _i_=0; _i_<8; _i_++)
		{
			std::ostrstream _ostr_;
			_ostr_ << "CreateTime[" << _i_ << "]" << std::ends;
			if (_i_ < CreateTime.size())
			{
				writeField(out, CreateTime[_i_].asString(), _path_ +_ostr_.str());
			}
			else
			{
				writeField(out, _tmp.asString(), _path_ +_ostr_.str());
			}
			_ostr_.freeze(0);
		}
	}
	writeField(out, GantryPos.asString(), _path_ +"GantryPos");
	writeField(out, RoofPos.asString(), _path_ +"RoofPos");
	writeField(out, CarNo.asString(), _path_ +"CarNo");
	{
		IntegerVal _tmp;
		for (int _i_=0; _i_<5; _i_++)
		{
			std::ostrstream _ostr_;
			_ostr_ << "Spare[" << _i_ << "]" << std::ends;
			if (_i_ < Spare.size())
			{
				writeField(out, Spare[_i_].asString(), _path_ +_ostr_.str());
			}
			else
			{
				writeField(out, _tmp.asString(), _path_ +_ostr_.str());
			}
			_ostr_.freeze(0);
		}
	}
}
// class: LFL222
void LFL222::load(std::istream & in, const string &_path_) throw (ETAMError)
{
	Header.load(in, _path_ +"Header"+ "/" );
	{
		CreateTime.clear();
		for (int _i_=0; _i_<8; _i_++)
		{
			std::ostrstream _ostr_;
			_ostr_ << "CreateTime[" << _i_ << "]" << std::ends;
			CreateTime.push_back(IntegerVal());
			set(CreateTime[_i_], readField(in, _path_ +_ostr_.str()), _path_ +_ostr_.str());
			_ostr_.freeze(0);
		}
	}
	set(FurnBreakOn, readField(in, _path_ +"FurnBreakOn"), _path_ +"FurnBreakOn");
	set(FurnPowerOn, readField(in, _path_ +"FurnPowerOn"), _path_ +"FurnPowerOn");
	set(TapChanger, readField(in, _path_ +"TapChanger"), _path_ +"TapChanger");
	set(ElecPos, readField(in, _path_ +"ElecPos"), _path_ +"ElecPos");
	set(GantryPos, readField(in, _path_ +"GantryPos"), _path_ +"GantryPos");
	set(ElecHydSys, readField(in, _path_ +"ElecHydSys"), _path_ +"ElecHydSys");
	set(ElecVoltTap, readField(in, _path_ +"ElecVoltTap"), _path_ +"ElecVoltTap");
	set(ElecCurvNo, readField(in, _path_ +"ElecCurvNo"), _path_ +"ElecCurvNo");
	set(ElecCons, readField(in, _path_ +"ElecCons"), _path_ +"ElecCons");
	{
		Spare.clear();
		for (int _i_=0; _i_<5; _i_++)
		{
			std::ostrstream _ostr_;
			_ostr_ << "Spare[" << _i_ << "]" << std::ends;
			Spare.push_back(IntegerVal());
			set(Spare[_i_], readField(in, _path_ +_ostr_.str()), _path_ +_ostr_.str());
			_ostr_.freeze(0);
		}
	}
}
void LFL222::serialize(std::ostream & out, const string &_path_) throw (ETAMError)
{
	Header.serialize(out, _path_ +"Header"+ "/" );
	{
		IntegerVal _tmp;
		for (int _i_=0; _i_<8; _i_++)
		{
			std::ostrstream _ostr_;
			_ostr_ << "CreateTime[" << _i_ << "]" << std::ends;
			if (_i_ < CreateTime.size())
			{
				writeField(out, CreateTime[_i_].asString(), _path_ +_ostr_.str());
			}
			else
			{
				writeField(out, _tmp.asString(), _path_ +_ostr_.str());
			}
			_ostr_.freeze(0);
		}
	}
	writeField(out, FurnBreakOn.asString(), _path_ +"FurnBreakOn");
	writeField(out, FurnPowerOn.asString(), _path_ +"FurnPowerOn");
	writeField(out, TapChanger.asString(), _path_ +"TapChanger");
	writeField(out, ElecPos.asString(), _path_ +"ElecPos");
	writeField(out, GantryPos.asString(), _path_ +"GantryPos");
	writeField(out, ElecHydSys.asString(), _path_ +"ElecHydSys");
	writeField(out, ElecVoltTap.asString(), _path_ +"ElecVoltTap");
	writeField(out, ElecCurvNo.asString(), _path_ +"ElecCurvNo");
	writeField(out, ElecCons.asString(), _path_ +"ElecCons");
	{
		IntegerVal _tmp;
		for (int _i_=0; _i_<5; _i_++)
		{
			std::ostrstream _ostr_;
			_ostr_ << "Spare[" << _i_ << "]" << std::ends;
			if (_i_ < Spare.size())
			{
				writeField(out, Spare[_i_].asString(), _path_ +_ostr_.str());
			}
			else
			{
				writeField(out, _tmp.asString(), _path_ +_ostr_.str());
			}
			_ostr_.freeze(0);
		}
	}
}
// class: LFL223
void LFL223::load(std::istream & in, const string &_path_) throw (ETAMError)
{
	Header.load(in, _path_ +"Header"+ "/" );
	{
		CreateTime.clear();
		for (int _i_=0; _i_<8; _i_++)
		{
			std::ostrstream _ostr_;
			_ostr_ << "CreateTime[" << _i_ << "]" << std::ends;
			CreateTime.push_back(IntegerVal());
			set(CreateTime[_i_], readField(in, _path_ +_ostr_.str()), _path_ +_ostr_.str());
			_ostr_.freeze(0);
		}
	}
	set(HeatId, readField(in, _path_ +"HeatId"), _path_ +"HeatId");
	set(TreatId, readField(in, _path_ +"TreatId"), _path_ +"TreatId");
	set(CarNo, readField(in, _path_ +"CarNo"), _path_ +"CarNo");
	set(ElecVoltTap, readField(in, _path_ +"ElecVoltTap"), _path_ +"ElecVoltTap");
	set(ElecCurvNo, readField(in, _path_ +"ElecCurvNo"), _path_ +"ElecCurvNo");
	set(ElecCons, readField(in, _path_ +"ElecCons"), _path_ +"ElecCons");
	{
		Spare.clear();
		for (int _i_=0; _i_<5; _i_++)
		{
			std::ostrstream _ostr_;
			_ostr_ << "Spare[" << _i_ << "]" << std::ends;
			Spare.push_back(IntegerVal());
			set(Spare[_i_], readField(in, _path_ +_ostr_.str()), _path_ +_ostr_.str());
			_ostr_.freeze(0);
		}
	}
}
void LFL223::serialize(std::ostream & out, const string &_path_) throw (ETAMError)
{
	Header.serialize(out, _path_ +"Header"+ "/" );
	{
		IntegerVal _tmp;
		for (int _i_=0; _i_<8; _i_++)
		{
			std::ostrstream _ostr_;
			_ostr_ << "CreateTime[" << _i_ << "]" << std::ends;
			if (_i_ < CreateTime.size())
			{
				writeField(out, CreateTime[_i_].asString(), _path_ +_ostr_.str());
			}
			else
			{
				writeField(out, _tmp.asString(), _path_ +_ostr_.str());
			}
			_ostr_.freeze(0);
		}
	}
	writeField(out, HeatId.asString(), _path_ +"HeatId");
	writeField(out, TreatId.asString(), _path_ +"TreatId");
	writeField(out, CarNo.asString(), _path_ +"CarNo");
	writeField(out, ElecVoltTap.asString(), _path_ +"ElecVoltTap");
	writeField(out, ElecCurvNo.asString(), _path_ +"ElecCurvNo");
	writeField(out, ElecCons.asString(), _path_ +"ElecCons");
	{
		IntegerVal _tmp;
		for (int _i_=0; _i_<5; _i_++)
		{
			std::ostrstream _ostr_;
			_ostr_ << "Spare[" << _i_ << "]" << std::ends;
			if (_i_ < Spare.size())
			{
				writeField(out, Spare[_i_].asString(), _path_ +_ostr_.str());
			}
			else
			{
				writeField(out, _tmp.asString(), _path_ +_ostr_.str());
			}
			_ostr_.freeze(0);
		}
	}
}
// class: LFL224
void LFL224::load(std::istream & in, const string &_path_) throw (ETAMError)
{
	Header.load(in, _path_ +"Header"+ "/" );
	{
		CreateTime.clear();
		for (int _i_=0; _i_<8; _i_++)
		{
			std::ostrstream _ostr_;
			_ostr_ << "CreateTime[" << _i_ << "]" << std::ends;
			CreateTime.push_back(IntegerVal());
			set(CreateTime[_i_], readField(in, _path_ +_ostr_.str()), _path_ +_ostr_.str());
			_ostr_.freeze(0);
		}
	}
	set(HeatId, readField(in, _path_ +"HeatId"), _path_ +"HeatId");
	set(TreatId, readField(in, _path_ +"TreatId"), _path_ +"TreatId");
	set(CarNo, readField(in, _path_ +"CarNo"), _path_ +"CarNo");
	set(PlugNo, readField(in, _path_ +"PlugNo"), _path_ +"PlugNo");
	set(StirrGasType, readField(in, _path_ +"StirrGasType"), _path_ +"StirrGasType");
	set(StirrStat, readField(in, _path_ +"StirrStat"), _path_ +"StirrStat");
	set(BypassStat, readField(in, _path_ +"BypassStat"), _path_ +"BypassStat");
	set(PlugDefect, readField(in, _path_ +"PlugDefect"), _path_ +"PlugDefect");
	set(StirrGasCons, readField(in, _path_ +"StirrGasCons"), _path_ +"StirrGasCons");
	{
		Spare.clear();
		for (int _i_=0; _i_<5; _i_++)
		{
			std::ostrstream _ostr_;
			_ostr_ << "Spare[" << _i_ << "]" << std::ends;
			Spare.push_back(IntegerVal());
			set(Spare[_i_], readField(in, _path_ +_ostr_.str()), _path_ +_ostr_.str());
			_ostr_.freeze(0);
		}
	}
}
void LFL224::serialize(std::ostream & out, const string &_path_) throw (ETAMError)
{
	Header.serialize(out, _path_ +"Header"+ "/" );
	{
		IntegerVal _tmp;
		for (int _i_=0; _i_<8; _i_++)
		{
			std::ostrstream _ostr_;
			_ostr_ << "CreateTime[" << _i_ << "]" << std::ends;
			if (_i_ < CreateTime.size())
			{
				writeField(out, CreateTime[_i_].asString(), _path_ +_ostr_.str());
			}
			else
			{
				writeField(out, _tmp.asString(), _path_ +_ostr_.str());
			}
			_ostr_.freeze(0);
		}
	}
	writeField(out, HeatId.asString(), _path_ +"HeatId");
	writeField(out, TreatId.asString(), _path_ +"TreatId");
	writeField(out, CarNo.asString(), _path_ +"CarNo");
	writeField(out, PlugNo.asString(), _path_ +"PlugNo");
	writeField(out, StirrGasType.asString(), _path_ +"StirrGasType");
	writeField(out, StirrStat.asString(), _path_ +"StirrStat");
	writeField(out, BypassStat.asString(), _path_ +"BypassStat");
	writeField(out, PlugDefect.asString(), _path_ +"PlugDefect");
	writeField(out, StirrGasCons.asString(), _path_ +"StirrGasCons");
	{
		IntegerVal _tmp;
		for (int _i_=0; _i_<5; _i_++)
		{
			std::ostrstream _ostr_;
			_ostr_ << "Spare[" << _i_ << "]" << std::ends;
			if (_i_ < Spare.size())
			{
				writeField(out, Spare[_i_].asString(), _path_ +_ostr_.str());
			}
			else
			{
				writeField(out, _tmp.asString(), _path_ +_ostr_.str());
			}
			_ostr_.freeze(0);
		}
	}
}
// class: LFL225
void LFL225::load(std::istream & in, const string &_path_) throw (ETAMError)
{
	Header.load(in, _path_ +"Header"+ "/" );
	{
		CreateTime.clear();
		for (int _i_=0; _i_<8; _i_++)
		{
			std::ostrstream _ostr_;
			_ostr_ << "CreateTime[" << _i_ << "]" << std::ends;
			CreateTime.push_back(IntegerVal());
			set(CreateTime[_i_], readField(in, _path_ +_ostr_.str()), _path_ +_ostr_.str());
			_ostr_.freeze(0);
		}
	}
	set(HeatId, readField(in, _path_ +"HeatId"), _path_ +"HeatId");
	set(TreatId, readField(in, _path_ +"TreatId"), _path_ +"TreatId");
	set(CarNo, readField(in, _path_ +"CarNo"), _path_ +"CarNo");
	set(StirrGasType, readField(in, _path_ +"StirrGasType"), _path_ +"StirrGasType");
	set(StirrStat, readField(in, _path_ +"StirrStat"), _path_ +"StirrStat");
	set(StirrGasCons, readField(in, _path_ +"StirrGasCons"), _path_ +"StirrGasCons");
	{
		Spare.clear();
		for (int _i_=0; _i_<5; _i_++)
		{
			std::ostrstream _ostr_;
			_ostr_ << "Spare[" << _i_ << "]" << std::ends;
			Spare.push_back(IntegerVal());
			set(Spare[_i_], readField(in, _path_ +_ostr_.str()), _path_ +_ostr_.str());
			_ostr_.freeze(0);
		}
	}
}
void LFL225::serialize(std::ostream & out, const string &_path_) throw (ETAMError)
{
	Header.serialize(out, _path_ +"Header"+ "/" );
	{
		IntegerVal _tmp;
		for (int _i_=0; _i_<8; _i_++)
		{
			std::ostrstream _ostr_;
			_ostr_ << "CreateTime[" << _i_ << "]" << std::ends;
			if (_i_ < CreateTime.size())
			{
				writeField(out, CreateTime[_i_].asString(), _path_ +_ostr_.str());
			}
			else
			{
				writeField(out, _tmp.asString(), _path_ +_ostr_.str());
			}
			_ostr_.freeze(0);
		}
	}
	writeField(out, HeatId.asString(), _path_ +"HeatId");
	writeField(out, TreatId.asString(), _path_ +"TreatId");
	writeField(out, CarNo.asString(), _path_ +"CarNo");
	writeField(out, StirrGasType.asString(), _path_ +"StirrGasType");
	writeField(out, StirrStat.asString(), _path_ +"StirrStat");
	writeField(out, StirrGasCons.asString(), _path_ +"StirrGasCons");
	{
		IntegerVal _tmp;
		for (int _i_=0; _i_<5; _i_++)
		{
			std::ostrstream _ostr_;
			_ostr_ << "Spare[" << _i_ << "]" << std::ends;
			if (_i_ < Spare.size())
			{
				writeField(out, Spare[_i_].asString(), _path_ +_ostr_.str());
			}
			else
			{
				writeField(out, _tmp.asString(), _path_ +_ostr_.str());
			}
			_ostr_.freeze(0);
		}
	}
}
// class: LFL226
void LFL226::load(std::istream & in, const string &_path_) throw (ETAMError)
{
	Header.load(in, _path_ +"Header"+ "/" );
	{
		CreateTime.clear();
		for (int _i_=0; _i_<8; _i_++)
		{
			std::ostrstream _ostr_;
			_ostr_ << "CreateTime[" << _i_ << "]" << std::ends;
			CreateTime.push_back(IntegerVal());
			set(CreateTime[_i_], readField(in, _path_ +_ostr_.str()), _path_ +_ostr_.str());
			_ostr_.freeze(0);
		}
	}
	set(HeatId, readField(in, _path_ +"HeatId"), _path_ +"HeatId");
	set(TreatId, readField(in, _path_ +"TreatId"), _path_ +"TreatId");
	set(CarNo, readField(in, _path_ +"CarNo"), _path_ +"CarNo");
	{
		StirrGasType.clear();
		for (int _i_=0; _i_<4; _i_++)
		{
			std::ostrstream _ostr_;
			_ostr_ << "StirrGasType[" << _i_ << "]" << std::ends;
			StirrGasType.push_back(IntegerVal());
			set(StirrGasType[_i_], readField(in, _path_ +_ostr_.str()), _path_ +_ostr_.str());
			_ostr_.freeze(0);
		}
	}
	{
		StirrInt.clear();
		for (int _i_=0; _i_<3; _i_++)
		{
			std::ostrstream _ostr_;
			_ostr_ << "StirrInt[" << _i_ << "]" << std::ends;
			StirrInt.push_back(IntegerVal());
			set(StirrInt[_i_], readField(in, _path_ +_ostr_.str()), _path_ +_ostr_.str());
			_ostr_.freeze(0);
		}
	}
	{
		FlowAct.clear();
		for (int _i_=0; _i_<4; _i_++)
		{
			std::ostrstream _ostr_;
			_ostr_ << "FlowAct[" << _i_ << "]" << std::ends;
			FlowAct.push_back(NumberVal());
			set(FlowAct[_i_], readField(in, _path_ +_ostr_.str()), _path_ +_ostr_.str());
			_ostr_.freeze(0);
		}
	}
	{
		Pressure.clear();
		for (int _i_=0; _i_<4; _i_++)
		{
			std::ostrstream _ostr_;
			_ostr_ << "Pressure[" << _i_ << "]" << std::ends;
			Pressure.push_back(NumberVal());
			set(Pressure[_i_], readField(in, _path_ +_ostr_.str()), _path_ +_ostr_.str());
			_ostr_.freeze(0);
		}
	}
	{
		StirrGasCons.clear();
		for (int _i_=0; _i_<4; _i_++)
		{
			std::ostrstream _ostr_;
			_ostr_ << "StirrGasCons[" << _i_ << "]" << std::ends;
			StirrGasCons.push_back(NumberVal());
			set(StirrGasCons[_i_], readField(in, _path_ +_ostr_.str()), _path_ +_ostr_.str());
			_ostr_.freeze(0);
		}
	}
	{
		Spare.clear();
		for (int _i_=0; _i_<5; _i_++)
		{
			std::ostrstream _ostr_;
			_ostr_ << "Spare[" << _i_ << "]" << std::ends;
			Spare.push_back(IntegerVal());
			set(Spare[_i_], readField(in, _path_ +_ostr_.str()), _path_ +_ostr_.str());
			_ostr_.freeze(0);
		}
	}
}
void LFL226::serialize(std::ostream & out, const string &_path_) throw (ETAMError)
{
	Header.serialize(out, _path_ +"Header"+ "/" );
	{
		IntegerVal _tmp;
		for (int _i_=0; _i_<8; _i_++)
		{
			std::ostrstream _ostr_;
			_ostr_ << "CreateTime[" << _i_ << "]" << std::ends;
			if (_i_ < CreateTime.size())
			{
				writeField(out, CreateTime[_i_].asString(), _path_ +_ostr_.str());
			}
			else
			{
				writeField(out, _tmp.asString(), _path_ +_ostr_.str());
			}
			_ostr_.freeze(0);
		}
	}
	writeField(out, HeatId.asString(), _path_ +"HeatId");
	writeField(out, TreatId.asString(), _path_ +"TreatId");
	writeField(out, CarNo.asString(), _path_ +"CarNo");
	{
		IntegerVal _tmp;
		for (int _i_=0; _i_<4; _i_++)
		{
			std::ostrstream _ostr_;
			_ostr_ << "StirrGasType[" << _i_ << "]" << std::ends;
			if (_i_ < StirrGasType.size())
			{
				writeField(out, StirrGasType[_i_].asString(), _path_ +_ostr_.str());
			}
			else
			{
				writeField(out, _tmp.asString(), _path_ +_ostr_.str());
			}
			_ostr_.freeze(0);
		}
	}
	{
		IntegerVal _tmp;
		for (int _i_=0; _i_<3; _i_++)
		{
			std::ostrstream _ostr_;
			_ostr_ << "StirrInt[" << _i_ << "]" << std::ends;
			if (_i_ < StirrInt.size())
			{
				writeField(out, StirrInt[_i_].asString(), _path_ +_ostr_.str());
			}
			else
			{
				writeField(out, _tmp.asString(), _path_ +_ostr_.str());
			}
			_ostr_.freeze(0);
		}
	}
	{
		NumberVal _tmp;
		for (int _i_=0; _i_<4; _i_++)
		{
			std::ostrstream _ostr_;
			_ostr_ << "FlowAct[" << _i_ << "]" << std::ends;
			if (_i_ < FlowAct.size())
			{
				writeField(out, FlowAct[_i_].asString(), _path_ +_ostr_.str());
			}
			else
			{
				writeField(out, _tmp.asString(), _path_ +_ostr_.str());
			}
			_ostr_.freeze(0);
		}
	}
	{
		NumberVal _tmp;
		for (int _i_=0; _i_<4; _i_++)
		{
			std::ostrstream _ostr_;
			_ostr_ << "Pressure[" << _i_ << "]" << std::ends;
			if (_i_ < Pressure.size())
			{
				writeField(out, Pressure[_i_].asString(), _path_ +_ostr_.str());
			}
			else
			{
				writeField(out, _tmp.asString(), _path_ +_ostr_.str());
			}
			_ostr_.freeze(0);
		}
	}
	{
		NumberVal _tmp;
		for (int _i_=0; _i_<4; _i_++)
		{
			std::ostrstream _ostr_;
			_ostr_ << "StirrGasCons[" << _i_ << "]" << std::ends;
			if (_i_ < StirrGasCons.size())
			{
				writeField(out, StirrGasCons[_i_].asString(), _path_ +_ostr_.str());
			}
			else
			{
				writeField(out, _tmp.asString(), _path_ +_ostr_.str());
			}
			_ostr_.freeze(0);
		}
	}
	{
		IntegerVal _tmp;
		for (int _i_=0; _i_<5; _i_++)
		{
			std::ostrstream _ostr_;
			_ostr_ << "Spare[" << _i_ << "]" << std::ends;
			if (_i_ < Spare.size())
			{
				writeField(out, Spare[_i_].asString(), _path_ +_ostr_.str());
			}
			else
			{
				writeField(out, _tmp.asString(), _path_ +_ostr_.str());
			}
			_ostr_.freeze(0);
		}
	}
}
// class: LFL230
void LFL230::load(std::istream & in, const string &_path_) throw (ETAMError)
{
	Header.load(in, _path_ +"Header"+ "/" );
	{
		CreateTime.clear();
		for (int _i_=0; _i_<8; _i_++)
		{
			std::ostrstream _ostr_;
			_ostr_ << "CreateTime[" << _i_ << "]" << std::ends;
			CreateTime.push_back(IntegerVal());
			set(CreateTime[_i_], readField(in, _path_ +_ostr_.str()), _path_ +_ostr_.str());
			_ostr_.freeze(0);
		}
	}
	set(HeatId, readField(in, _path_ +"HeatId"), _path_ +"HeatId");
	set(TreatId, readField(in, _path_ +"TreatId"), _path_ +"TreatId");
	set(CarNo, readField(in, _path_ +"CarNo"), _path_ +"CarNo");
	set(RoofWaterInlet, readField(in, _path_ +"RoofWaterInlet"), _path_ +"RoofWaterInlet");
	set(RoofWaterOutlet, readField(in, _path_ +"RoofWaterOutlet"), _path_ +"RoofWaterOutlet");
	set(RoofWaterFlow, readField(in, _path_ +"RoofWaterFlow"), _path_ +"RoofWaterFlow");
	set(WGWaterInlet, readField(in, _path_ +"WGWaterInlet"), _path_ +"WGWaterInlet");
	set(WGWaterOutlet, readField(in, _path_ +"WGWaterOutlet"), _path_ +"WGWaterOutlet");
	set(WGWaterFlow, readField(in, _path_ +"WGWaterFlow"), _path_ +"WGWaterFlow");
	set(ElecCons, readField(in, _path_ +"ElecCons"), _path_ +"ElecCons");
	{
		Spare.clear();
		for (int _i_=0; _i_<5; _i_++)
		{
			std::ostrstream _ostr_;
			_ostr_ << "Spare[" << _i_ << "]" << std::ends;
			Spare.push_back(IntegerVal());
			set(Spare[_i_], readField(in, _path_ +_ostr_.str()), _path_ +_ostr_.str());
			_ostr_.freeze(0);
		}
	}
}
void LFL230::serialize(std::ostream & out, const string &_path_) throw (ETAMError)
{
	Header.serialize(out, _path_ +"Header"+ "/" );
	{
		IntegerVal _tmp;
		for (int _i_=0; _i_<8; _i_++)
		{
			std::ostrstream _ostr_;
			_ostr_ << "CreateTime[" << _i_ << "]" << std::ends;
			if (_i_ < CreateTime.size())
			{
				writeField(out, CreateTime[_i_].asString(), _path_ +_ostr_.str());
			}
			else
			{
				writeField(out, _tmp.asString(), _path_ +_ostr_.str());
			}
			_ostr_.freeze(0);
		}
	}
	writeField(out, HeatId.asString(), _path_ +"HeatId");
	writeField(out, TreatId.asString(), _path_ +"TreatId");
	writeField(out, CarNo.asString(), _path_ +"CarNo");
	writeField(out, RoofWaterInlet.asString(), _path_ +"RoofWaterInlet");
	writeField(out, RoofWaterOutlet.asString(), _path_ +"RoofWaterOutlet");
	writeField(out, RoofWaterFlow.asString(), _path_ +"RoofWaterFlow");
	writeField(out, WGWaterInlet.asString(), _path_ +"WGWaterInlet");
	writeField(out, WGWaterOutlet.asString(), _path_ +"WGWaterOutlet");
	writeField(out, WGWaterFlow.asString(), _path_ +"WGWaterFlow");
	writeField(out, ElecCons.asString(), _path_ +"ElecCons");
	{
		IntegerVal _tmp;
		for (int _i_=0; _i_<5; _i_++)
		{
			std::ostrstream _ostr_;
			_ostr_ << "Spare[" << _i_ << "]" << std::ends;
			if (_i_ < Spare.size())
			{
				writeField(out, Spare[_i_].asString(), _path_ +_ostr_.str());
			}
			else
			{
				writeField(out, _tmp.asString(), _path_ +_ostr_.str());
			}
			_ostr_.freeze(0);
		}
	}
}
// class: LFL240
void LFL240::load(std::istream & in, const string &_path_) throw (ETAMError)
{
	Header.load(in, _path_ +"Header"+ "/" );
	{
		CreateTime.clear();
		for (int _i_=0; _i_<8; _i_++)
		{
			std::ostrstream _ostr_;
			_ostr_ << "CreateTime[" << _i_ << "]" << std::ends;
			CreateTime.push_back(IntegerVal());
			set(CreateTime[_i_], readField(in, _path_ +_ostr_.str()), _path_ +_ostr_.str());
			_ostr_.freeze(0);
		}
	}
	set(ParamName, readField(in, _path_ +"ParamName"), _path_ +"ParamName");
	set(ParamValue, readField(in, _path_ +"ParamValue"), _path_ +"ParamValue");
	{
		Spare.clear();
		for (int _i_=0; _i_<5; _i_++)
		{
			std::ostrstream _ostr_;
			_ostr_ << "Spare[" << _i_ << "]" << std::ends;
			Spare.push_back(IntegerVal());
			set(Spare[_i_], readField(in, _path_ +_ostr_.str()), _path_ +_ostr_.str());
			_ostr_.freeze(0);
		}
	}
}
void LFL240::serialize(std::ostream & out, const string &_path_) throw (ETAMError)
{
	Header.serialize(out, _path_ +"Header"+ "/" );
	{
		IntegerVal _tmp;
		for (int _i_=0; _i_<8; _i_++)
		{
			std::ostrstream _ostr_;
			_ostr_ << "CreateTime[" << _i_ << "]" << std::ends;
			if (_i_ < CreateTime.size())
			{
				writeField(out, CreateTime[_i_].asString(), _path_ +_ostr_.str());
			}
			else
			{
				writeField(out, _tmp.asString(), _path_ +_ostr_.str());
			}
			_ostr_.freeze(0);
		}
	}
	writeField(out, ParamName.asString(), _path_ +"ParamName");
	writeField(out, ParamValue.asString(), _path_ +"ParamValue");
	{
		IntegerVal _tmp;
		for (int _i_=0; _i_<5; _i_++)
		{
			std::ostrstream _ostr_;
			_ostr_ << "Spare[" << _i_ << "]" << std::ends;
			if (_i_ < Spare.size())
			{
				writeField(out, Spare[_i_].asString(), _path_ +_ostr_.str());
			}
			else
			{
				writeField(out, _tmp.asString(), _path_ +_ostr_.str());
			}
			_ostr_.freeze(0);
		}
	}
}
// class: LFL260
void LFL260::load(std::istream & in, const string &_path_) throw (ETAMError)
{
	Header.load(in, _path_ +"Header"+ "/" );
	{
		CreateTime.clear();
		for (int _i_=0; _i_<8; _i_++)
		{
			std::ostrstream _ostr_;
			_ostr_ << "CreateTime[" << _i_ << "]" << std::ends;
			CreateTime.push_back(IntegerVal());
			set(CreateTime[_i_], readField(in, _path_ +_ostr_.str()), _path_ +_ostr_.str());
			_ostr_.freeze(0);
		}
	}
	set(HeatId, readField(in, _path_ +"HeatId"), _path_ +"HeatId");
	set(TreatId, readField(in, _path_ +"TreatId"), _path_ +"TreatId");
	set(CarNo, readField(in, _path_ +"CarNo"), _path_ +"CarNo");
	set(Target, readField(in, _path_ +"Target"), _path_ +"Target");
	set(Source, readField(in, _path_ +"Source"), _path_ +"Source");
	set(RecipeNo, readField(in, _path_ +"RecipeNo"), _path_ +"RecipeNo");
	set(BatchStat, readField(in, _path_ +"BatchStat"), _path_ +"BatchStat");
	{
		MatCode.clear();
		for (int _i_=0; _i_<10; _i_++)
		{
			std::ostrstream _ostr_;
			_ostr_ << "MatCode[" << _i_ << "]" << std::ends;
			MatCode.push_back(StringVal());
			set(MatCode[_i_], readField(in, _path_ +_ostr_.str()), _path_ +_ostr_.str());
			_ostr_.freeze(0);
		}
	}
	{
		MatWeight.clear();
		for (int _i_=0; _i_<10; _i_++)
		{
			std::ostrstream _ostr_;
			_ostr_ << "MatWeight[" << _i_ << "]" << std::ends;
			MatWeight.push_back(NumberVal());
			set(MatWeight[_i_], readField(in, _path_ +_ostr_.str()), _path_ +_ostr_.str());
			_ostr_.freeze(0);
		}
	}
	{
		SourceNo.clear();
		for (int _i_=0; _i_<10; _i_++)
		{
			std::ostrstream _ostr_;
			_ostr_ << "SourceNo[" << _i_ << "]" << std::ends;
			SourceNo.push_back(IntegerVal());
			set(SourceNo[_i_], readField(in, _path_ +_ostr_.str()), _path_ +_ostr_.str());
			_ostr_.freeze(0);
		}
	}
	{
		FeedingRate.clear();
		for (int _i_=0; _i_<10; _i_++)
		{
			std::ostrstream _ostr_;
			_ostr_ << "FeedingRate[" << _i_ << "]" << std::ends;
			FeedingRate.push_back(NumberVal());
			set(FeedingRate[_i_], readField(in, _path_ +_ostr_.str()), _path_ +_ostr_.str());
			_ostr_.freeze(0);
		}
	}
	{
		Spare.clear();
		for (int _i_=0; _i_<5; _i_++)
		{
			std::ostrstream _ostr_;
			_ostr_ << "Spare[" << _i_ << "]" << std::ends;
			Spare.push_back(IntegerVal());
			set(Spare[_i_], readField(in, _path_ +_ostr_.str()), _path_ +_ostr_.str());
			_ostr_.freeze(0);
		}
	}
}
void LFL260::serialize(std::ostream & out, const string &_path_) throw (ETAMError)
{
	Header.serialize(out, _path_ +"Header"+ "/" );
	{
		IntegerVal _tmp;
		for (int _i_=0; _i_<8; _i_++)
		{
			std::ostrstream _ostr_;
			_ostr_ << "CreateTime[" << _i_ << "]" << std::ends;
			if (_i_ < CreateTime.size())
			{
				writeField(out, CreateTime[_i_].asString(), _path_ +_ostr_.str());
			}
			else
			{
				writeField(out, _tmp.asString(), _path_ +_ostr_.str());
			}
			_ostr_.freeze(0);
		}
	}
	writeField(out, HeatId.asString(), _path_ +"HeatId");
	writeField(out, TreatId.asString(), _path_ +"TreatId");
	writeField(out, CarNo.asString(), _path_ +"CarNo");
	writeField(out, Target.asString(), _path_ +"Target");
	writeField(out, Source.asString(), _path_ +"Source");
	writeField(out, RecipeNo.asString(), _path_ +"RecipeNo");
	writeField(out, BatchStat.asString(), _path_ +"BatchStat");
	{
		StringVal _tmp;
		for (int _i_=0; _i_<10; _i_++)
		{
			std::ostrstream _ostr_;
			_ostr_ << "MatCode[" << _i_ << "]" << std::ends;
			if (_i_ < MatCode.size())
			{
				writeField(out, MatCode[_i_].asString(), _path_ +_ostr_.str());
			}
			else
			{
				writeField(out, _tmp.asString(), _path_ +_ostr_.str());
			}
			_ostr_.freeze(0);
		}
	}
	{
		NumberVal _tmp;
		for (int _i_=0; _i_<10; _i_++)
		{
			std::ostrstream _ostr_;
			_ostr_ << "MatWeight[" << _i_ << "]" << std::ends;
			if (_i_ < MatWeight.size())
			{
				writeField(out, MatWeight[_i_].asString(), _path_ +_ostr_.str());
			}
			else
			{
				writeField(out, _tmp.asString(), _path_ +_ostr_.str());
			}
			_ostr_.freeze(0);
		}
	}
	{
		IntegerVal _tmp;
		for (int _i_=0; _i_<10; _i_++)
		{
			std::ostrstream _ostr_;
			_ostr_ << "SourceNo[" << _i_ << "]" << std::ends;
			if (_i_ < SourceNo.size())
			{
				writeField(out, SourceNo[_i_].asString(), _path_ +_ostr_.str());
			}
			else
			{
				writeField(out, _tmp.asString(), _path_ +_ostr_.str());
			}
			_ostr_.freeze(0);
		}
	}
	{
		NumberVal _tmp;
		for (int _i_=0; _i_<10; _i_++)
		{
			std::ostrstream _ostr_;
			_ostr_ << "FeedingRate[" << _i_ << "]" << std::ends;
			if (_i_ < FeedingRate.size())
			{
				writeField(out, FeedingRate[_i_].asString(), _path_ +_ostr_.str());
			}
			else
			{
				writeField(out, _tmp.asString(), _path_ +_ostr_.str());
			}
			_ostr_.freeze(0);
		}
	}
	{
		IntegerVal _tmp;
		for (int _i_=0; _i_<5; _i_++)
		{
			std::ostrstream _ostr_;
			_ostr_ << "Spare[" << _i_ << "]" << std::ends;
			if (_i_ < Spare.size())
			{
				writeField(out, Spare[_i_].asString(), _path_ +_ostr_.str());
			}
			else
			{
				writeField(out, _tmp.asString(), _path_ +_ostr_.str());
			}
			_ostr_.freeze(0);
		}
	}
}
// class: LFL261
void LFL261::load(std::istream & in, const string &_path_) throw (ETAMError)
{
	Header.load(in, _path_ +"Header"+ "/" );
	{
		CreateTime.clear();
		for (int _i_=0; _i_<8; _i_++)
		{
			std::ostrstream _ostr_;
			_ostr_ << "CreateTime[" << _i_ << "]" << std::ends;
			CreateTime.push_back(IntegerVal());
			set(CreateTime[_i_], readField(in, _path_ +_ostr_.str()), _path_ +_ostr_.str());
			_ostr_.freeze(0);
		}
	}
	set(ActionFlag, readField(in, _path_ +"ActionFlag"), _path_ +"ActionFlag");
	{
		MatCode.clear();
		for (int _i_=0; _i_<20; _i_++)
		{
			std::ostrstream _ostr_;
			_ostr_ << "MatCode[" << _i_ << "]" << std::ends;
			MatCode.push_back(StringVal());
			set(MatCode[_i_], readField(in, _path_ +_ostr_.str()), _path_ +_ostr_.str());
			_ostr_.freeze(0);
		}
	}
	{
		MinWeight.clear();
		for (int _i_=0; _i_<20; _i_++)
		{
			std::ostrstream _ostr_;
			_ostr_ << "MinWeight[" << _i_ << "]" << std::ends;
			MinWeight.push_back(NumberVal());
			set(MinWeight[_i_], readField(in, _path_ +_ostr_.str()), _path_ +_ostr_.str());
			_ostr_.freeze(0);
		}
	}
	{
		SourceNo.clear();
		for (int _i_=0; _i_<20; _i_++)
		{
			std::ostrstream _ostr_;
			_ostr_ << "SourceNo[" << _i_ << "]" << std::ends;
			SourceNo.push_back(IntegerVal());
			set(SourceNo[_i_], readField(in, _path_ +_ostr_.str()), _path_ +_ostr_.str());
			_ostr_.freeze(0);
		}
	}
	{
		Source.clear();
		for (int _i_=0; _i_<20; _i_++)
		{
			std::ostrstream _ostr_;
			_ostr_ << "Source[" << _i_ << "]" << std::ends;
			Source.push_back(IntegerVal());
			set(Source[_i_], readField(in, _path_ +_ostr_.str()), _path_ +_ostr_.str());
			_ostr_.freeze(0);
		}
	}
	{
		Spare.clear();
		for (int _i_=0; _i_<5; _i_++)
		{
			std::ostrstream _ostr_;
			_ostr_ << "Spare[" << _i_ << "]" << std::ends;
			Spare.push_back(IntegerVal());
			set(Spare[_i_], readField(in, _path_ +_ostr_.str()), _path_ +_ostr_.str());
			_ostr_.freeze(0);
		}
	}
}
void LFL261::serialize(std::ostream & out, const string &_path_) throw (ETAMError)
{
	Header.serialize(out, _path_ +"Header"+ "/" );
	{
		IntegerVal _tmp;
		for (int _i_=0; _i_<8; _i_++)
		{
			std::ostrstream _ostr_;
			_ostr_ << "CreateTime[" << _i_ << "]" << std::ends;
			if (_i_ < CreateTime.size())
			{
				writeField(out, CreateTime[_i_].asString(), _path_ +_ostr_.str());
			}
			else
			{
				writeField(out, _tmp.asString(), _path_ +_ostr_.str());
			}
			_ostr_.freeze(0);
		}
	}
	writeField(out, ActionFlag.asString(), _path_ +"ActionFlag");
	{
		StringVal _tmp;
		for (int _i_=0; _i_<20; _i_++)
		{
			std::ostrstream _ostr_;
			_ostr_ << "MatCode[" << _i_ << "]" << std::ends;
			if (_i_ < MatCode.size())
			{
				writeField(out, MatCode[_i_].asString(), _path_ +_ostr_.str());
			}
			else
			{
				writeField(out, _tmp.asString(), _path_ +_ostr_.str());
			}
			_ostr_.freeze(0);
		}
	}
	{
		NumberVal _tmp;
		for (int _i_=0; _i_<20; _i_++)
		{
			std::ostrstream _ostr_;
			_ostr_ << "MinWeight[" << _i_ << "]" << std::ends;
			if (_i_ < MinWeight.size())
			{
				writeField(out, MinWeight[_i_].asString(), _path_ +_ostr_.str());
			}
			else
			{
				writeField(out, _tmp.asString(), _path_ +_ostr_.str());
			}
			_ostr_.freeze(0);
		}
	}
	{
		IntegerVal _tmp;
		for (int _i_=0; _i_<20; _i_++)
		{
			std::ostrstream _ostr_;
			_ostr_ << "SourceNo[" << _i_ << "]" << std::ends;
			if (_i_ < SourceNo.size())
			{
				writeField(out, SourceNo[_i_].asString(), _path_ +_ostr_.str());
			}
			else
			{
				writeField(out, _tmp.asString(), _path_ +_ostr_.str());
			}
			_ostr_.freeze(0);
		}
	}
	{
		IntegerVal _tmp;
		for (int _i_=0; _i_<20; _i_++)
		{
			std::ostrstream _ostr_;
			_ostr_ << "Source[" << _i_ << "]" << std::ends;
			if (_i_ < Source.size())
			{
				writeField(out, Source[_i_].asString(), _path_ +_ostr_.str());
			}
			else
			{
				writeField(out, _tmp.asString(), _path_ +_ostr_.str());
			}
			_ostr_.freeze(0);
		}
	}
	{
		IntegerVal _tmp;
		for (int _i_=0; _i_<5; _i_++)
		{
			std::ostrstream _ostr_;
			_ostr_ << "Spare[" << _i_ << "]" << std::ends;
			if (_i_ < Spare.size())
			{
				writeField(out, Spare[_i_].asString(), _path_ +_ostr_.str());
			}
			else
			{
				writeField(out, _tmp.asString(), _path_ +_ostr_.str());
			}
			_ostr_.freeze(0);
		}
	}
}
// class: LFL270
void LFL270::load(std::istream & in, const string &_path_) throw (ETAMError)
{
	Header.load(in, _path_ +"Header"+ "/" );
	{
		CreateTime.clear();
		for (int _i_=0; _i_<8; _i_++)
		{
			std::ostrstream _ostr_;
			_ostr_ << "CreateTime[" << _i_ << "]" << std::ends;
			CreateTime.push_back(IntegerVal());
			set(CreateTime[_i_], readField(in, _path_ +_ostr_.str()), _path_ +_ostr_.str());
			_ostr_.freeze(0);
		}
	}
	set(HeatId, readField(in, _path_ +"HeatId"), _path_ +"HeatId");
	set(TreatId, readField(in, _path_ +"TreatId"), _path_ +"TreatId");
	set(LadleId, readField(in, _path_ +"LadleId"), _path_ +"LadleId");
	set(WeighingStat, readField(in, _path_ +"WeighingStat"), _path_ +"WeighingStat");
	set(Weight, readField(in, _path_ +"Weight"), _path_ +"Weight");
	{
		Spare.clear();
		for (int _i_=0; _i_<5; _i_++)
		{
			std::ostrstream _ostr_;
			_ostr_ << "Spare[" << _i_ << "]" << std::ends;
			Spare.push_back(IntegerVal());
			set(Spare[_i_], readField(in, _path_ +_ostr_.str()), _path_ +_ostr_.str());
			_ostr_.freeze(0);
		}
	}
}
void LFL270::serialize(std::ostream & out, const string &_path_) throw (ETAMError)
{
	Header.serialize(out, _path_ +"Header"+ "/" );
	{
		IntegerVal _tmp;
		for (int _i_=0; _i_<8; _i_++)
		{
			std::ostrstream _ostr_;
			_ostr_ << "CreateTime[" << _i_ << "]" << std::ends;
			if (_i_ < CreateTime.size())
			{
				writeField(out, CreateTime[_i_].asString(), _path_ +_ostr_.str());
			}
			else
			{
				writeField(out, _tmp.asString(), _path_ +_ostr_.str());
			}
			_ostr_.freeze(0);
		}
	}
	writeField(out, HeatId.asString(), _path_ +"HeatId");
	writeField(out, TreatId.asString(), _path_ +"TreatId");
	writeField(out, LadleId.asString(), _path_ +"LadleId");
	writeField(out, WeighingStat.asString(), _path_ +"WeighingStat");
	writeField(out, Weight.asString(), _path_ +"Weight");
	{
		IntegerVal _tmp;
		for (int _i_=0; _i_<5; _i_++)
		{
			std::ostrstream _ostr_;
			_ostr_ << "Spare[" << _i_ << "]" << std::ends;
			if (_i_ < Spare.size())
			{
				writeField(out, Spare[_i_].asString(), _path_ +_ostr_.str());
			}
			else
			{
				writeField(out, _tmp.asString(), _path_ +_ostr_.str());
			}
			_ostr_.freeze(0);
		}
	}
}
// class: LFL281
void LFL281::load(std::istream & in, const string &_path_) throw (ETAMError)
{
	Header.load(in, _path_ +"Header"+ "/" );
	{
		CreateTime.clear();
		for (int _i_=0; _i_<8; _i_++)
		{
			std::ostrstream _ostr_;
			_ostr_ << "CreateTime[" << _i_ << "]" << std::ends;
			CreateTime.push_back(IntegerVal());
			set(CreateTime[_i_], readField(in, _path_ +_ostr_.str()), _path_ +_ostr_.str());
			_ostr_.freeze(0);
		}
	}
	set(HeatId, readField(in, _path_ +"HeatId"), _path_ +"HeatId");
	set(TreatId, readField(in, _path_ +"TreatId"), _path_ +"TreatId");
	set(LadleId, readField(in, _path_ +"LadleId"), _path_ +"LadleId");
	set(CarNo, readField(in, _path_ +"CarNo"), _path_ +"CarNo");
	set(StepNo, readField(in, _path_ +"StepNo"), _path_ +"StepNo");
	{
		Spare.clear();
		for (int _i_=0; _i_<5; _i_++)
		{
			std::ostrstream _ostr_;
			_ostr_ << "Spare[" << _i_ << "]" << std::ends;
			Spare.push_back(IntegerVal());
			set(Spare[_i_], readField(in, _path_ +_ostr_.str()), _path_ +_ostr_.str());
			_ostr_.freeze(0);
		}
	}
}
void LFL281::serialize(std::ostream & out, const string &_path_) throw (ETAMError)
{
	Header.serialize(out, _path_ +"Header"+ "/" );
	{
		IntegerVal _tmp;
		for (int _i_=0; _i_<8; _i_++)
		{
			std::ostrstream _ostr_;
			_ostr_ << "CreateTime[" << _i_ << "]" << std::ends;
			if (_i_ < CreateTime.size())
			{
				writeField(out, CreateTime[_i_].asString(), _path_ +_ostr_.str());
			}
			else
			{
				writeField(out, _tmp.asString(), _path_ +_ostr_.str());
			}
			_ostr_.freeze(0);
		}
	}
	writeField(out, HeatId.asString(), _path_ +"HeatId");
	writeField(out, TreatId.asString(), _path_ +"TreatId");
	writeField(out, LadleId.asString(), _path_ +"LadleId");
	writeField(out, CarNo.asString(), _path_ +"CarNo");
	writeField(out, StepNo.asString(), _path_ +"StepNo");
	{
		IntegerVal _tmp;
		for (int _i_=0; _i_<5; _i_++)
		{
			std::ostrstream _ostr_;
			_ostr_ << "Spare[" << _i_ << "]" << std::ends;
			if (_i_ < Spare.size())
			{
				writeField(out, Spare[_i_].asString(), _path_ +_ostr_.str());
			}
			else
			{
				writeField(out, _tmp.asString(), _path_ +_ostr_.str());
			}
			_ostr_.freeze(0);
		}
	}
}
