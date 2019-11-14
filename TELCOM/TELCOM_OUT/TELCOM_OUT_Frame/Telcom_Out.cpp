/*
****************************************
 File: Telcom_Out

 TAM (Telegram Access Model) Classes
 generated on Mon Sep 16 11:10:48 IST 2019

*****************************************/

#include "Telcom_Out.h"
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
// class: L2LF00
void L2LF00::load(std::istream & in, const string &_path_) throw (ETAMError)
{
	Header.load(in, _path_ +"Header"+ "/" );
	set(Status, readField(in, _path_ +"Status"), _path_ +"Status");
	set(RcvMsgId, readField(in, _path_ +"RcvMsgId"), _path_ +"RcvMsgId");
	set(ErrInf, readField(in, _path_ +"ErrInf"), _path_ +"ErrInf");
	set(ErrMess, readField(in, _path_ +"ErrMess"), _path_ +"ErrMess");
}
void L2LF00::serialize(std::ostream & out, const string &_path_) throw (ETAMError)
{
	Header.serialize(out, _path_ +"Header"+ "/" );
	writeField(out, Status.asString(), _path_ +"Status");
	writeField(out, RcvMsgId.asString(), _path_ +"RcvMsgId");
	writeField(out, ErrInf.asString(), _path_ +"ErrInf");
	writeField(out, ErrMess.asString(), _path_ +"ErrMess");
}
// class: L2LF01
void L2LF01::load(std::istream & in, const string &_path_) throw (ETAMError)
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
}
void L2LF01::serialize(std::ostream & out, const string &_path_) throw (ETAMError)
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
}
// class: L2LF01_WATCH_DOG
void L2LF01_WATCH_DOG::load(std::istream & in, const string &_path_) throw (ETAMError)
{
	set(MessageLength, readField(in, _path_ +"MessageLength"), _path_ +"MessageLength");
	set(MessageId, readField(in, _path_ +"MessageId"), _path_ +"MessageId");
	set(MessageCount, readField(in, _path_ +"MessageCount"), _path_ +"MessageCount");
	set(UnitNo, readField(in, _path_ +"UnitNo"), _path_ +"UnitNo");
	set(CreateTime, readField(in, _path_ +"CreateTime"), _path_ +"CreateTime");
}
void L2LF01_WATCH_DOG::serialize(std::ostream & out, const string &_path_) throw (ETAMError)
{
	writeField(out, MessageLength.asString(), _path_ +"MessageLength");
	writeField(out, MessageId.asString(), _path_ +"MessageId");
	writeField(out, MessageCount.asString(), _path_ +"MessageCount");
	writeField(out, UnitNo.asString(), _path_ +"UnitNo");
	writeField(out, CreateTime.asString(), _path_ +"CreateTime");
}
// class: L2LF03
void L2LF03::load(std::istream & in, const string &_path_) throw (ETAMError)
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
	set(ProdOrderId, readField(in, _path_ +"ProdOrderId"), _path_ +"ProdOrderId");
	set(SteelGradeCode, readField(in, _path_ +"SteelGradeCode"), _path_ +"SteelGradeCode");
	{
		ProdDate.clear();
		for (int _i_=0; _i_<8; _i_++)
		{
			std::ostrstream _ostr_;
			_ostr_ << "ProdDate[" << _i_ << "]" << std::ends;
			ProdDate.push_back(IntegerVal());
			set(ProdDate[_i_], readField(in, _path_ +_ostr_.str()), _path_ +_ostr_.str());
			_ostr_.freeze(0);
		}
	}
	{
		DepTime.clear();
		for (int _i_=0; _i_<8; _i_++)
		{
			std::ostrstream _ostr_;
			_ostr_ << "DepTime[" << _i_ << "]" << std::ends;
			DepTime.push_back(IntegerVal());
			set(DepTime[_i_], readField(in, _path_ +_ostr_.str()), _path_ +_ostr_.str());
			_ostr_.freeze(0);
		}
	}
	set(CarNo, readField(in, _path_ +"CarNo"), _path_ +"CarNo");
	set(LadleId, readField(in, _path_ +"LadleId"), _path_ +"LadleId");
	set(ShiftCode, readField(in, _path_ +"ShiftCode"), _path_ +"ShiftCode");
	set(CrewCode, readField(in, _path_ +"CrewCode"), _path_ +"CrewCode");
	set(OperCode, readField(in, _path_ +"OperCode"), _path_ +"OperCode");
	set(RouteCode, readField(in, _path_ +"RouteCode"), _path_ +"RouteCode");
	set(AimTemp, readField(in, _path_ +"AimTemp"), _path_ +"AimTemp");
	set(UpdateFlag, readField(in, _path_ +"UpdateFlag"), _path_ +"UpdateFlag");
	set(LadleTareWeight, readField(in, _path_ +"LadleTareWeight"), _path_ +"LadleTareWeight");
	set(LadleGrossWeight, readField(in, _path_ +"LadleGrossWeight"), _path_ +"LadleGrossWeight");
	set(SteelWeight, readField(in, _path_ +"SteelWeight"), _path_ +"SteelWeight");
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
void L2LF03::serialize(std::ostream & out, const string &_path_) throw (ETAMError)
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
	writeField(out, ProdOrderId.asString(), _path_ +"ProdOrderId");
	writeField(out, SteelGradeCode.asString(), _path_ +"SteelGradeCode");
	{
		IntegerVal _tmp;
		for (int _i_=0; _i_<8; _i_++)
		{
			std::ostrstream _ostr_;
			_ostr_ << "ProdDate[" << _i_ << "]" << std::ends;
			if (_i_ < ProdDate.size())
			{
				writeField(out, ProdDate[_i_].asString(), _path_ +_ostr_.str());
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
			_ostr_ << "DepTime[" << _i_ << "]" << std::ends;
			if (_i_ < DepTime.size())
			{
				writeField(out, DepTime[_i_].asString(), _path_ +_ostr_.str());
			}
			else
			{
				writeField(out, _tmp.asString(), _path_ +_ostr_.str());
			}
			_ostr_.freeze(0);
		}
	}
	writeField(out, CarNo.asString(), _path_ +"CarNo");
	writeField(out, LadleId.asString(), _path_ +"LadleId");
	writeField(out, ShiftCode.asString(), _path_ +"ShiftCode");
	writeField(out, CrewCode.asString(), _path_ +"CrewCode");
	writeField(out, OperCode.asString(), _path_ +"OperCode");
	writeField(out, RouteCode.asString(), _path_ +"RouteCode");
	writeField(out, AimTemp.asString(), _path_ +"AimTemp");
	writeField(out, UpdateFlag.asString(), _path_ +"UpdateFlag");
	writeField(out, LadleTareWeight.asString(), _path_ +"LadleTareWeight");
	writeField(out, LadleGrossWeight.asString(), _path_ +"LadleGrossWeight");
	writeField(out, SteelWeight.asString(), _path_ +"SteelWeight");
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
// class: L2LF05
void L2LF05::load(std::istream & in, const string &_path_) throw (ETAMError)
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
	set(StirrActivity, readField(in, _path_ +"StirrActivity"), _path_ +"StirrActivity");
	set(StirrGasType, readField(in, _path_ +"StirrGasType"), _path_ +"StirrGasType");
	set(StirrInt, readField(in, _path_ +"StirrInt"), _path_ +"StirrInt");
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
void L2LF05::serialize(std::ostream & out, const string &_path_) throw (ETAMError)
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
	writeField(out, StirrActivity.asString(), _path_ +"StirrActivity");
	writeField(out, StirrGasType.asString(), _path_ +"StirrGasType");
	writeField(out, StirrInt.asString(), _path_ +"StirrInt");
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
// class: L2LF06
void L2LF06::load(std::istream & in, const string &_path_) throw (ETAMError)
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
void L2LF06::serialize(std::ostream & out, const string &_path_) throw (ETAMError)
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
// class: L2LF07
void L2LF07::load(std::istream & in, const string &_path_) throw (ETAMError)
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
void L2LF07::serialize(std::ostream & out, const string &_path_) throw (ETAMError)
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
// class: L2LF20
void L2LF20::load(std::istream & in, const string &_path_) throw (ETAMError)
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
	set(AimVoltTap, readField(in, _path_ +"AimVoltTap"), _path_ +"AimVoltTap");
	set(AimCurveNo, readField(in, _path_ +"AimCurveNo"), _path_ +"AimCurveNo");
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
void L2LF20::serialize(std::ostream & out, const string &_path_) throw (ETAMError)
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
	writeField(out, AimVoltTap.asString(), _path_ +"AimVoltTap");
	writeField(out, AimCurveNo.asString(), _path_ +"AimCurveNo");
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
// class: L2LF20_VOLTAGE_TAP
void L2LF20_VOLTAGE_TAP::load(std::istream & in, const string &_path_) throw (ETAMError)
{
	set(MessageLength, readField(in, _path_ +"MessageLength"), _path_ +"MessageLength");
	set(MessageId, readField(in, _path_ +"MessageId"), _path_ +"MessageId");
	set(MessageCount, readField(in, _path_ +"MessageCount"), _path_ +"MessageCount");
	set(UnitNo, readField(in, _path_ +"UnitNo"), _path_ +"UnitNo");
	set(CreateTime, readField(in, _path_ +"CreateTime"), _path_ +"CreateTime");
	set(HeatId, readField(in, _path_ +"HeatId"), _path_ +"HeatId");
	set(TreatId, readField(in, _path_ +"TreatId"), _path_ +"TreatId");
	set(AimVoltTap, readField(in, _path_ +"AimVoltTap"), _path_ +"AimVoltTap");
	set(AimCurveNo, readField(in, _path_ +"AimCurveNo"), _path_ +"AimCurveNo");
	set(Spare, readField(in, _path_ +"Spare"), _path_ +"Spare");
}
void L2LF20_VOLTAGE_TAP::serialize(std::ostream & out, const string &_path_) throw (ETAMError)
{
	writeField(out, MessageLength.asString(), _path_ +"MessageLength");
	writeField(out, MessageId.asString(), _path_ +"MessageId");
	writeField(out, MessageCount.asString(), _path_ +"MessageCount");
	writeField(out, UnitNo.asString(), _path_ +"UnitNo");
	writeField(out, CreateTime.asString(), _path_ +"CreateTime");
	writeField(out, HeatId.asString(), _path_ +"HeatId");
	writeField(out, TreatId.asString(), _path_ +"TreatId");
	writeField(out, AimVoltTap.asString(), _path_ +"AimVoltTap");
	writeField(out, AimCurveNo.asString(), _path_ +"AimCurveNo");
	writeField(out, Spare.asString(), _path_ +"Spare");
}
// class: L2LF22
void L2LF22::load(std::istream & in, const string &_path_) throw (ETAMError)
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
void L2LF22::serialize(std::ostream & out, const string &_path_) throw (ETAMError)
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
// class: L2LF23
void L2LF23::load(std::istream & in, const string &_path_) throw (ETAMError)
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
void L2LF23::serialize(std::ostream & out, const string &_path_) throw (ETAMError)
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
// class: L2LF25
void L2LF25::load(std::istream & in, const string &_path_) throw (ETAMError)
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
	set(Type, readField(in, _path_ +"Type"), _path_ +"Type");
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
void L2LF25::serialize(std::ostream & out, const string &_path_) throw (ETAMError)
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
	writeField(out, Type.asString(), _path_ +"Type");
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
// class: L2LF30
void L2LF30::load(std::istream & in, const string &_path_) throw (ETAMError)
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
		Enabled.clear();
		for (int _i_=0; _i_<7; _i_++)
		{
			std::ostrstream _ostr_;
			_ostr_ << "Enabled[" << _i_ << "]" << std::ends;
			Enabled.push_back(IntegerVal());
			set(Enabled[_i_], readField(in, _path_ +_ostr_.str()), _path_ +_ostr_.str());
			_ostr_.freeze(0);
		}
	}
	{
		RemDurStep.clear();
		for (int _i_=0; _i_<7; _i_++)
		{
			std::ostrstream _ostr_;
			_ostr_ << "RemDurStep[" << _i_ << "]" << std::ends;
			RemDurStep.push_back(NumberVal());
			set(RemDurStep[_i_], readField(in, _path_ +_ostr_.str()), _path_ +_ostr_.str());
			_ostr_.freeze(0);
		}
	}
	{
		ElecEnergyStep.clear();
		for (int _i_=0; _i_<7; _i_++)
		{
			std::ostrstream _ostr_;
			_ostr_ << "ElecEnergyStep[" << _i_ << "]" << std::ends;
			ElecEnergyStep.push_back(IntegerVal());
			set(ElecEnergyStep[_i_], readField(in, _path_ +_ostr_.str()), _path_ +_ostr_.str());
			_ostr_.freeze(0);
		}
	}
	{
		TempEndStep.clear();
		for (int _i_=0; _i_<7; _i_++)
		{
			std::ostrstream _ostr_;
			_ostr_ << "TempEndStep[" << _i_ << "]" << std::ends;
			TempEndStep.push_back(IntegerVal());
			set(TempEndStep[_i_], readField(in, _path_ +_ostr_.str()), _path_ +_ostr_.str());
			_ostr_.freeze(0);
		}
	}
	{
		AimVoltTap.clear();
		for (int _i_=0; _i_<7; _i_++)
		{
			std::ostrstream _ostr_;
			_ostr_ << "AimVoltTap[" << _i_ << "]" << std::ends;
			AimVoltTap.push_back(IntegerVal());
			set(AimVoltTap[_i_], readField(in, _path_ +_ostr_.str()), _path_ +_ostr_.str());
			_ostr_.freeze(0);
		}
	}
	{
		AimCurveNo.clear();
		for (int _i_=0; _i_<7; _i_++)
		{
			std::ostrstream _ostr_;
			_ostr_ << "AimCurveNo[" << _i_ << "]" << std::ends;
			AimCurveNo.push_back(IntegerVal());
			set(AimCurveNo[_i_], readField(in, _path_ +_ostr_.str()), _path_ +_ostr_.str());
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
void L2LF30::serialize(std::ostream & out, const string &_path_) throw (ETAMError)
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
		for (int _i_=0; _i_<7; _i_++)
		{
			std::ostrstream _ostr_;
			_ostr_ << "Enabled[" << _i_ << "]" << std::ends;
			if (_i_ < Enabled.size())
			{
				writeField(out, Enabled[_i_].asString(), _path_ +_ostr_.str());
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
		for (int _i_=0; _i_<7; _i_++)
		{
			std::ostrstream _ostr_;
			_ostr_ << "RemDurStep[" << _i_ << "]" << std::ends;
			if (_i_ < RemDurStep.size())
			{
				writeField(out, RemDurStep[_i_].asString(), _path_ +_ostr_.str());
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
		for (int _i_=0; _i_<7; _i_++)
		{
			std::ostrstream _ostr_;
			_ostr_ << "ElecEnergyStep[" << _i_ << "]" << std::ends;
			if (_i_ < ElecEnergyStep.size())
			{
				writeField(out, ElecEnergyStep[_i_].asString(), _path_ +_ostr_.str());
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
		for (int _i_=0; _i_<7; _i_++)
		{
			std::ostrstream _ostr_;
			_ostr_ << "TempEndStep[" << _i_ << "]" << std::ends;
			if (_i_ < TempEndStep.size())
			{
				writeField(out, TempEndStep[_i_].asString(), _path_ +_ostr_.str());
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
		for (int _i_=0; _i_<7; _i_++)
		{
			std::ostrstream _ostr_;
			_ostr_ << "AimVoltTap[" << _i_ << "]" << std::ends;
			if (_i_ < AimVoltTap.size())
			{
				writeField(out, AimVoltTap[_i_].asString(), _path_ +_ostr_.str());
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
		for (int _i_=0; _i_<7; _i_++)
		{
			std::ostrstream _ostr_;
			_ostr_ << "AimCurveNo[" << _i_ << "]" << std::ends;
			if (_i_ < AimCurveNo.size())
			{
				writeField(out, AimCurveNo[_i_].asString(), _path_ +_ostr_.str());
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
// class: L2LF30_ELEC_PATT::TEENTRY
void L2LF30_ELEC_PATT::TEENTRY::load(std::istream & in, const string &_path_) throw (ETAMError)
{
	set(MessageCount, readField(in, _path_ +"MessageCount"), _path_ +"MessageCount");
	set(MessageIndex, readField(in, _path_ +"MessageIndex"), _path_ +"MessageIndex");
	set(HeatId, readField(in, _path_ +"HeatId"), _path_ +"HeatId");
	set(TreatId, readField(in, _path_ +"TreatId"), _path_ +"TreatId");
	set(ActivityType, readField(in, _path_ +"ActivityType"), _path_ +"ActivityType");
	set(StepNo, readField(in, _path_ +"StepNo"), _path_ +"StepNo");
	set(Enabled, readField(in, _path_ +"Enabled"), _path_ +"Enabled");
	set(RemDurStep, readField(in, _path_ +"RemDurStep"), _path_ +"RemDurStep");
	set(ElecEnergyStep, readField(in, _path_ +"ElecEnergyStep"), _path_ +"ElecEnergyStep");
	set(TempEndStep, readField(in, _path_ +"TempEndStep"), _path_ +"TempEndStep");
	set(AimVoltTap, readField(in, _path_ +"AimVoltTap"), _path_ +"AimVoltTap");
	set(AimCurveNo, readField(in, _path_ +"AimCurveNo"), _path_ +"AimCurveNo");
	set(Spare_1, readField(in, _path_ +"Spare_1"), _path_ +"Spare_1");
	set(Spare_2, readField(in, _path_ +"Spare_2"), _path_ +"Spare_2");
}
void L2LF30_ELEC_PATT::TEENTRY::serialize(std::ostream & out, const string &_path_) throw (ETAMError)
{
	writeField(out, MessageCount.asString(), _path_ +"MessageCount");
	writeField(out, MessageIndex.asString(), _path_ +"MessageIndex");
	writeField(out, HeatId.asString(), _path_ +"HeatId");
	writeField(out, TreatId.asString(), _path_ +"TreatId");
	writeField(out, ActivityType.asString(), _path_ +"ActivityType");
	writeField(out, StepNo.asString(), _path_ +"StepNo");
	writeField(out, Enabled.asString(), _path_ +"Enabled");
	writeField(out, RemDurStep.asString(), _path_ +"RemDurStep");
	writeField(out, ElecEnergyStep.asString(), _path_ +"ElecEnergyStep");
	writeField(out, TempEndStep.asString(), _path_ +"TempEndStep");
	writeField(out, AimVoltTap.asString(), _path_ +"AimVoltTap");
	writeField(out, AimCurveNo.asString(), _path_ +"AimCurveNo");
	writeField(out, Spare_1.asString(), _path_ +"Spare_1");
	writeField(out, Spare_2.asString(), _path_ +"Spare_2");
}
// class: L2LF30_ELEC_PATT
void L2LF30_ELEC_PATT::load(std::istream & in, const string &_path_) throw (ETAMError)
{
	set(MessageLength, readField(in, _path_ +"MessageLength"), _path_ +"MessageLength");
	set(MessageId, readField(in, _path_ +"MessageId"), _path_ +"MessageId");
	set(MessageCount, readField(in, _path_ +"MessageCount"), _path_ +"MessageCount");
	set(UnitNo, readField(in, _path_ +"UnitNo"), _path_ +"UnitNo");
	set(CreateTime, readField(in, _path_ +"CreateTime"), _path_ +"CreateTime");
	set(HeatId, readField(in, _path_ +"HeatId"), _path_ +"HeatId");
	set(TreatId, readField(in, _path_ +"TreatId"), _path_ +"TreatId");
	{
		ENTRY.clear();
		for (int _i_=0; _i_<7; _i_++)
		{
			std::ostrstream _ostr_;
			_ostr_ << "ENTRY[" << _i_ << "]" << std::ends;
			ENTRY.push_back(TEENTRY());
			ENTRY[_i_].load(in, _path_ +_ostr_.str()+ "/" );
			_ostr_.freeze(0);
		}
	}
}
void L2LF30_ELEC_PATT::serialize(std::ostream & out, const string &_path_) throw (ETAMError)
{
	writeField(out, MessageLength.asString(), _path_ +"MessageLength");
	writeField(out, MessageId.asString(), _path_ +"MessageId");
	writeField(out, MessageCount.asString(), _path_ +"MessageCount");
	writeField(out, UnitNo.asString(), _path_ +"UnitNo");
	writeField(out, CreateTime.asString(), _path_ +"CreateTime");
	writeField(out, HeatId.asString(), _path_ +"HeatId");
	writeField(out, TreatId.asString(), _path_ +"TreatId");
	{
		TEENTRY _tmp;
		for (int _i_=0; _i_<7; _i_++)
		{
			std::ostrstream _ostr_;
			_ostr_ << "ENTRY[" << _i_ << "]" << std::ends;
			if (_i_ < ENTRY.size())
			{
				ENTRY[_i_].serialize(out, _path_ +_ostr_.str()+ "/" );
			}
			else
			{
				_tmp.serialize(out, _path_ +_ostr_.str()+ "/" );
			}
			_ostr_.freeze(0);
		}
	}
}
// class: L2LF31
void L2LF31::load(std::istream & in, const string &_path_) throw (ETAMError)
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
		PhaseNo.clear();
		for (int _i_=0; _i_<20; _i_++)
		{
			std::ostrstream _ostr_;
			_ostr_ << "PhaseNo[" << _i_ << "]" << std::ends;
			PhaseNo.push_back(IntegerVal());
			set(PhaseNo[_i_], readField(in, _path_ +_ostr_.str()), _path_ +_ostr_.str());
			_ostr_.freeze(0);
		}
	}
	{
		Enabled.clear();
		for (int _i_=0; _i_<20; _i_++)
		{
			std::ostrstream _ostr_;
			_ostr_ << "Enabled[" << _i_ << "]" << std::ends;
			Enabled.push_back(IntegerVal());
			set(Enabled[_i_], readField(in, _path_ +_ostr_.str()), _path_ +_ostr_.str());
			_ostr_.freeze(0);
		}
	}
	{
		Duration.clear();
		for (int _i_=0; _i_<20; _i_++)
		{
			std::ostrstream _ostr_;
			_ostr_ << "Duration[" << _i_ << "]" << std::ends;
			Duration.push_back(NumberVal());
			set(Duration[_i_], readField(in, _path_ +_ostr_.str()), _path_ +_ostr_.str());
			_ostr_.freeze(0);
		}
	}
	{
		StirrInt.clear();
		for (int _i_=0; _i_<20; _i_++)
		{
			std::ostrstream _ostr_;
			_ostr_ << "StirrInt[" << _i_ << "]" << std::ends;
			StirrInt.push_back(IntegerVal());
			set(StirrInt[_i_], readField(in, _path_ +_ostr_.str()), _path_ +_ostr_.str());
			_ostr_.freeze(0);
		}
	}
	{
		StirrGasFlow.clear();
		for (int _i_=0; _i_<20; _i_++)
		{
			std::ostrstream _ostr_;
			_ostr_ << "StirrGasFlow[" << _i_ << "]" << std::ends;
			StirrGasFlow.push_back(NumberVal());
			set(StirrGasFlow[_i_], readField(in, _path_ +_ostr_.str()), _path_ +_ostr_.str());
			_ostr_.freeze(0);
		}
	}
	{
		StirrGasType.clear();
		for (int _i_=0; _i_<20; _i_++)
		{
			std::ostrstream _ostr_;
			_ostr_ << "StirrGasType[" << _i_ << "]" << std::ends;
			StirrGasType.push_back(IntegerVal());
			set(StirrGasType[_i_], readField(in, _path_ +_ostr_.str()), _path_ +_ostr_.str());
			_ostr_.freeze(0);
		}
	}
	{
		StepPriority.clear();
		for (int _i_=0; _i_<20; _i_++)
		{
			std::ostrstream _ostr_;
			_ostr_ << "StepPriority[" << _i_ << "]" << std::ends;
			StepPriority.push_back(IntegerVal());
			set(StepPriority[_i_], readField(in, _path_ +_ostr_.str()), _path_ +_ostr_.str());
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
void L2LF31::serialize(std::ostream & out, const string &_path_) throw (ETAMError)
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
		for (int _i_=0; _i_<20; _i_++)
		{
			std::ostrstream _ostr_;
			_ostr_ << "PhaseNo[" << _i_ << "]" << std::ends;
			if (_i_ < PhaseNo.size())
			{
				writeField(out, PhaseNo[_i_].asString(), _path_ +_ostr_.str());
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
			_ostr_ << "Enabled[" << _i_ << "]" << std::ends;
			if (_i_ < Enabled.size())
			{
				writeField(out, Enabled[_i_].asString(), _path_ +_ostr_.str());
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
			_ostr_ << "Duration[" << _i_ << "]" << std::ends;
			if (_i_ < Duration.size())
			{
				writeField(out, Duration[_i_].asString(), _path_ +_ostr_.str());
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
		for (int _i_=0; _i_<20; _i_++)
		{
			std::ostrstream _ostr_;
			_ostr_ << "StirrGasFlow[" << _i_ << "]" << std::ends;
			if (_i_ < StirrGasFlow.size())
			{
				writeField(out, StirrGasFlow[_i_].asString(), _path_ +_ostr_.str());
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
		for (int _i_=0; _i_<20; _i_++)
		{
			std::ostrstream _ostr_;
			_ostr_ << "StepPriority[" << _i_ << "]" << std::ends;
			if (_i_ < StepPriority.size())
			{
				writeField(out, StepPriority[_i_].asString(), _path_ +_ostr_.str());
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
// class: L2LF31_STIRR_PATT::TEENTRY
void L2LF31_STIRR_PATT::TEENTRY::load(std::istream & in, const string &_path_) throw (ETAMError)
{
	set(MessageCount, readField(in, _path_ +"MessageCount"), _path_ +"MessageCount");
	set(MessageIndex, readField(in, _path_ +"MessageIndex"), _path_ +"MessageIndex");
	set(HeatId, readField(in, _path_ +"HeatId"), _path_ +"HeatId");
	set(TreatId, readField(in, _path_ +"TreatId"), _path_ +"TreatId");
	set(PhaseNo, readField(in, _path_ +"PhaseNo"), _path_ +"PhaseNo");
	set(Enabled, readField(in, _path_ +"Enabled"), _path_ +"Enabled");
	set(Duration, readField(in, _path_ +"Duration"), _path_ +"Duration");
	set(StirrInt, readField(in, _path_ +"StirrInt"), _path_ +"StirrInt");
	set(StirrGasFlow, readField(in, _path_ +"StirrGasFlow"), _path_ +"StirrGasFlow");
	set(StirrGasType, readField(in, _path_ +"StirrGasType"), _path_ +"StirrGasType");
	set(StepPriority, readField(in, _path_ +"StepPriority"), _path_ +"StepPriority");
	set(Spare_1, readField(in, _path_ +"Spare_1"), _path_ +"Spare_1");
	set(Spare_2, readField(in, _path_ +"Spare_2"), _path_ +"Spare_2");
}
void L2LF31_STIRR_PATT::TEENTRY::serialize(std::ostream & out, const string &_path_) throw (ETAMError)
{
	writeField(out, MessageCount.asString(), _path_ +"MessageCount");
	writeField(out, MessageIndex.asString(), _path_ +"MessageIndex");
	writeField(out, HeatId.asString(), _path_ +"HeatId");
	writeField(out, TreatId.asString(), _path_ +"TreatId");
	writeField(out, PhaseNo.asString(), _path_ +"PhaseNo");
	writeField(out, Enabled.asString(), _path_ +"Enabled");
	writeField(out, Duration.asString(), _path_ +"Duration");
	writeField(out, StirrInt.asString(), _path_ +"StirrInt");
	writeField(out, StirrGasFlow.asString(), _path_ +"StirrGasFlow");
	writeField(out, StirrGasType.asString(), _path_ +"StirrGasType");
	writeField(out, StepPriority.asString(), _path_ +"StepPriority");
	writeField(out, Spare_1.asString(), _path_ +"Spare_1");
	writeField(out, Spare_2.asString(), _path_ +"Spare_2");
}
// class: L2LF31_STIRR_PATT
void L2LF31_STIRR_PATT::load(std::istream & in, const string &_path_) throw (ETAMError)
{
	set(MessageLength, readField(in, _path_ +"MessageLength"), _path_ +"MessageLength");
	set(MessageId, readField(in, _path_ +"MessageId"), _path_ +"MessageId");
	set(MessageCount, readField(in, _path_ +"MessageCount"), _path_ +"MessageCount");
	set(UnitNo, readField(in, _path_ +"UnitNo"), _path_ +"UnitNo");
	set(CreateTime, readField(in, _path_ +"CreateTime"), _path_ +"CreateTime");
	set(HeatId, readField(in, _path_ +"HeatId"), _path_ +"HeatId");
	set(TreatId, readField(in, _path_ +"TreatId"), _path_ +"TreatId");
	{
		ENTRY.clear();
		for (int _i_=0; _i_<20; _i_++)
		{
			std::ostrstream _ostr_;
			_ostr_ << "ENTRY[" << _i_ << "]" << std::ends;
			ENTRY.push_back(TEENTRY());
			ENTRY[_i_].load(in, _path_ +_ostr_.str()+ "/" );
			_ostr_.freeze(0);
		}
	}
}
void L2LF31_STIRR_PATT::serialize(std::ostream & out, const string &_path_) throw (ETAMError)
{
	writeField(out, MessageLength.asString(), _path_ +"MessageLength");
	writeField(out, MessageId.asString(), _path_ +"MessageId");
	writeField(out, MessageCount.asString(), _path_ +"MessageCount");
	writeField(out, UnitNo.asString(), _path_ +"UnitNo");
	writeField(out, CreateTime.asString(), _path_ +"CreateTime");
	writeField(out, HeatId.asString(), _path_ +"HeatId");
	writeField(out, TreatId.asString(), _path_ +"TreatId");
	{
		TEENTRY _tmp;
		for (int _i_=0; _i_<20; _i_++)
		{
			std::ostrstream _ostr_;
			_ostr_ << "ENTRY[" << _i_ << "]" << std::ends;
			if (_i_ < ENTRY.size())
			{
				ENTRY[_i_].serialize(out, _path_ +_ostr_.str()+ "/" );
			}
			else
			{
				_tmp.serialize(out, _path_ +_ostr_.str()+ "/" );
			}
			_ostr_.freeze(0);
		}
	}
}
// class: L2LF40
void L2LF40::load(std::istream & in, const string &_path_) throw (ETAMError)
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
	{
		ParamName.clear();
		for (int _i_=0; _i_<5; _i_++)
		{
			std::ostrstream _ostr_;
			_ostr_ << "ParamName[" << _i_ << "]" << std::ends;
			ParamName.push_back(StringVal());
			set(ParamName[_i_], readField(in, _path_ +_ostr_.str()), _path_ +_ostr_.str());
			_ostr_.freeze(0);
		}
	}
	{
		ParamValue.clear();
		for (int _i_=0; _i_<5; _i_++)
		{
			std::ostrstream _ostr_;
			_ostr_ << "ParamValue[" << _i_ << "]" << std::ends;
			ParamValue.push_back(NumberVal());
			set(ParamValue[_i_], readField(in, _path_ +_ostr_.str()), _path_ +_ostr_.str());
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
void L2LF40::serialize(std::ostream & out, const string &_path_) throw (ETAMError)
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
	{
		StringVal _tmp;
		for (int _i_=0; _i_<5; _i_++)
		{
			std::ostrstream _ostr_;
			_ostr_ << "ParamName[" << _i_ << "]" << std::ends;
			if (_i_ < ParamName.size())
			{
				writeField(out, ParamName[_i_].asString(), _path_ +_ostr_.str());
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
		for (int _i_=0; _i_<5; _i_++)
		{
			std::ostrstream _ostr_;
			_ostr_ << "ParamValue[" << _i_ << "]" << std::ends;
			if (_i_ < ParamValue.size())
			{
				writeField(out, ParamValue[_i_].asString(), _path_ +_ostr_.str());
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
// class: L2LF70
void L2LF70::load(std::istream & in, const string &_path_) throw (ETAMError)
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
	set(Source, readField(in, _path_ +"Source"), _path_ +"Source");
	set(RecipeNo, readField(in, _path_ +"RecipeNo"), _path_ +"RecipeNo");
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
			MatWeight.push_back(IntegerVal());
			set(MatWeight[_i_], readField(in, _path_ +_ostr_.str()), _path_ +_ostr_.str());
			_ostr_.freeze(0);
		}
	}
	{
		MatSequence.clear();
		for (int _i_=0; _i_<10; _i_++)
		{
			std::ostrstream _ostr_;
			_ostr_ << "MatSequence[" << _i_ << "]" << std::ends;
			MatSequence.push_back(IntegerVal());
			set(MatSequence[_i_], readField(in, _path_ +_ostr_.str()), _path_ +_ostr_.str());
			_ostr_.freeze(0);
		}
	}
	{
		FeedRate.clear();
		for (int _i_=0; _i_<10; _i_++)
		{
			std::ostrstream _ostr_;
			_ostr_ << "FeedRate[" << _i_ << "]" << std::ends;
			FeedRate.push_back(IntegerVal());
			set(FeedRate[_i_], readField(in, _path_ +_ostr_.str()), _path_ +_ostr_.str());
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
void L2LF70::serialize(std::ostream & out, const string &_path_) throw (ETAMError)
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
	writeField(out, Source.asString(), _path_ +"Source");
	writeField(out, RecipeNo.asString(), _path_ +"RecipeNo");
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
		IntegerVal _tmp;
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
			_ostr_ << "MatSequence[" << _i_ << "]" << std::ends;
			if (_i_ < MatSequence.size())
			{
				writeField(out, MatSequence[_i_].asString(), _path_ +_ostr_.str());
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
			_ostr_ << "FeedRate[" << _i_ << "]" << std::ends;
			if (_i_ < FeedRate.size())
			{
				writeField(out, FeedRate[_i_].asString(), _path_ +_ostr_.str());
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
// class: L2LF70_MAT_HANDL::TEENTRY
void L2LF70_MAT_HANDL::TEENTRY::load(std::istream & in, const string &_path_) throw (ETAMError)
{
	set(MessageCount, readField(in, _path_ +"MessageCount"), _path_ +"MessageCount");
	set(MessageIndex, readField(in, _path_ +"MessageIndex"), _path_ +"MessageIndex");
	set(HeatId, readField(in, _path_ +"HeatId"), _path_ +"HeatId");
	set(TreatId, readField(in, _path_ +"TreatId"), _path_ +"TreatId");
	set(Source, readField(in, _path_ +"Source"), _path_ +"Source");
	set(RecipeNo, readField(in, _path_ +"RecipeNo"), _path_ +"RecipeNo");
	set(MatCode, readField(in, _path_ +"MatCode"), _path_ +"MatCode");
	set(MatWeight, readField(in, _path_ +"MatWeight"), _path_ +"MatWeight");
	set(MatSequence, readField(in, _path_ +"MatSequence"), _path_ +"MatSequence");
	set(FeedRate, readField(in, _path_ +"FeedRate"), _path_ +"FeedRate");
	set(Spare_1, readField(in, _path_ +"Spare_1"), _path_ +"Spare_1");
	set(Spare_2, readField(in, _path_ +"Spare_2"), _path_ +"Spare_2");
}
void L2LF70_MAT_HANDL::TEENTRY::serialize(std::ostream & out, const string &_path_) throw (ETAMError)
{
	writeField(out, MessageCount.asString(), _path_ +"MessageCount");
	writeField(out, MessageIndex.asString(), _path_ +"MessageIndex");
	writeField(out, HeatId.asString(), _path_ +"HeatId");
	writeField(out, TreatId.asString(), _path_ +"TreatId");
	writeField(out, Source.asString(), _path_ +"Source");
	writeField(out, RecipeNo.asString(), _path_ +"RecipeNo");
	writeField(out, MatCode.asString(), _path_ +"MatCode");
	writeField(out, MatWeight.asString(), _path_ +"MatWeight");
	writeField(out, MatSequence.asString(), _path_ +"MatSequence");
	writeField(out, FeedRate.asString(), _path_ +"FeedRate");
	writeField(out, Spare_1.asString(), _path_ +"Spare_1");
	writeField(out, Spare_2.asString(), _path_ +"Spare_2");
}
// class: L2LF70_MAT_HANDL
void L2LF70_MAT_HANDL::load(std::istream & in, const string &_path_) throw (ETAMError)
{
	set(MessageLength, readField(in, _path_ +"MessageLength"), _path_ +"MessageLength");
	set(MessageId, readField(in, _path_ +"MessageId"), _path_ +"MessageId");
	set(MessageCount, readField(in, _path_ +"MessageCount"), _path_ +"MessageCount");
	set(UnitNo, readField(in, _path_ +"UnitNo"), _path_ +"UnitNo");
	set(CreateTime, readField(in, _path_ +"CreateTime"), _path_ +"CreateTime");
	set(HeatId, readField(in, _path_ +"HeatId"), _path_ +"HeatId");
	set(TreatId, readField(in, _path_ +"TreatId"), _path_ +"TreatId");
	{
		ENTRY.clear();
		for (int _i_=0; _i_<300; _i_++)
		{
			std::ostrstream _ostr_;
			_ostr_ << "ENTRY[" << _i_ << "]" << std::ends;
			ENTRY.push_back(TEENTRY());
			ENTRY[_i_].load(in, _path_ +_ostr_.str()+ "/" );
			_ostr_.freeze(0);
		}
	}
}
void L2LF70_MAT_HANDL::serialize(std::ostream & out, const string &_path_) throw (ETAMError)
{
	writeField(out, MessageLength.asString(), _path_ +"MessageLength");
	writeField(out, MessageId.asString(), _path_ +"MessageId");
	writeField(out, MessageCount.asString(), _path_ +"MessageCount");
	writeField(out, UnitNo.asString(), _path_ +"UnitNo");
	writeField(out, CreateTime.asString(), _path_ +"CreateTime");
	writeField(out, HeatId.asString(), _path_ +"HeatId");
	writeField(out, TreatId.asString(), _path_ +"TreatId");
	{
		TEENTRY _tmp;
		for (int _i_=0; _i_<300; _i_++)
		{
			std::ostrstream _ostr_;
			_ostr_ << "ENTRY[" << _i_ << "]" << std::ends;
			if (_i_ < ENTRY.size())
			{
				ENTRY[_i_].serialize(out, _path_ +_ostr_.str()+ "/" );
			}
			else
			{
				_tmp.serialize(out, _path_ +_ostr_.str()+ "/" );
			}
			_ostr_.freeze(0);
		}
	}
}
// class: L2LF71
void L2LF71::load(std::istream & in, const string &_path_) throw (ETAMError)
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
void L2LF71::serialize(std::ostream & out, const string &_path_) throw (ETAMError)
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
// class: L2LF72
void L2LF72::load(std::istream & in, const string &_path_) throw (ETAMError)
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
void L2LF72::serialize(std::ostream & out, const string &_path_) throw (ETAMError)
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
