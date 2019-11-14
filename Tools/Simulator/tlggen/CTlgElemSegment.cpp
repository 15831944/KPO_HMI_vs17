// Copyright 2006 SMS - Demag AG

//-----------------------------------------------------------------
#include "CTlgElemSegment.h"
//------------------------------------------------------------------
CTlgElemSegment::CTlgElemSegment(const CElemDescription::TransportType transp,const CElemDescription::ElementType elemType,const std::string& name):
CTlgElem(transp,0,name)
{
	 //ElemDescr->setElemType(elemType);
}
//------------------------------------------------------------------
CTlgElemSegment::CTlgElemSegment(const CTlgElemSegment& Obj)
{
  int count,i;
  this->DescrIndex = Obj.getDescrIndex();
  count = Obj.getSubElemCount();
  for(i=0;i<count;i++)
  {
    ElemVector.push_back(Obj.getSubElem(i+1)->clone());
  }
	CElemDescription::reserveElemDescription(DescrIndex);
}
//------------------------------------------------------------------
CTlgElemSegment::CTlgElemSegment(const std::string& name,CElemDescription::ElementType elemType,const long count):
CTlgElem(name,count,elemType)
{
  //int index = CElemDescription::createDescription();
  CElemDescription* descr = CElemDescription::getDescriptionInztanz(DescrIndex);
  descr->setElemCount(count);
  descr->setNameElem(name);
  descr->setElemType(elemType);
}
//------------------------------------------------------------------
CTlgElemSegment::CTlgElemSegment(int index):
CTlgElem(index)
{
}
//------------------------------------------------------------------
CTlgElemSegment::~CTlgElemSegment()
{
  int count,i;
  count = (int)ElemVector.size();
  for(i=0;i<count;i++)
  {
    delete ElemVector[i];
  }
}
//------------------------------------------------------------------
void CTlgElemSegment::addSubElem(CTlgElem* elem)
{
	ElemVector.push_back(elem);
}
//------------------------------------------------------------------
CTlgElem* CTlgElemSegment::clone() const
{
  return new CTlgElemSegment(*this);
}
//-------------------------------------------------------------------
void CTlgElemSegment::getValue(std::string& value) const
{
	int count,i;
	std::string subElem("");
	count=this->getSubElemCount();
	value.clear();
	for(i=1;i<=count;i++)
	{
		getSubElem(i)->getValue(subElem);
		value.append(subElem);
		value.append(1,'|');
	}
}
//--------------------------------------------------------------------
int CTlgElemSegment::getSubElemCount() const
{
	return int(ElemVector.size());
}
//---------------------------------------------------------------------
int CTlgElemSegment::serialize(char* buffer,int len,CInterConfig* interConfig)
{
	int ret=0;
	int count,i,j,subLen,pos;
  int bytesCount;
  char* subbuffer=0;

  //char subbuffer[1024];
	count = getSubElemCount();
	pos=0;
	for(i=1;i<=count;i++)
	{
    bytesCount=getSubElem(i)->getTransBytesCount();
    subbuffer=new char[ bytesCount*sizeof(char)];
		subLen=getSubElem(i)->serialize(subbuffer,bytesCount,interConfig);
		for(j=0;j<subLen;j++)
		{
			buffer[pos] = subbuffer[j];
			pos++;
		}
    delete subbuffer;
	}
    
	ret=pos;
	return ret;
}
//---------------------------------------------------------------------
void CTlgElemSegment::getElemAsString(std::string& elem,const std::string& del)
{
  int count,i;
  std::string subelem("");
  elem.clear();
  count=getSubElemCount();
  for(i=1;i<=count;i++)
  {
    getSubElem(i)->getElemAsString(subelem,del);
    elem.append(subelem);
    if(i != count)
      elem.append(del);
  }
}
//---------------------------------------------------------------------
CTlgElem* CTlgElemSegment::getSubElem(int index) const
{
  CTlgElem* ret = 0;

  if((index <=  int(ElemVector.size())) && (index > 0))
    ret = ElemVector[index-1];

  return ret;
}
//---------------------------------------------------------------------
CTlgElem* CTlgElemSegment::getSubElem(const std::string& id) const
{
	CTlgElem* elem=0;
	int count,i;
	bool flag;

	count=this->getSubElemCount();
	flag=false;
	i=0;
	while((i<count) && (!flag))
	{
		if(ElemVector[i]->getNameElem() == id)
		{
			elem=ElemVector[i];
			flag=true;
		}
		else
		{
			i++;
		}
	}
	return elem;
}
//---------------------------------------------------------------------
void CTlgElemSegment::setValue(const std::string& val,CInterConfig* interConf)
{
	CElemDescription* descr = CElemDescription::getDescriptionInztanz(DescrIndex);
	std::string name = descr->getNameElem();
	//throw CExpWrongOperation("",name,"segment","set value");
}
//---------------------------------------------------------------------
void CTlgElemSegment::setDefaultValue()
{
	int count,i;
	count=getSubElemCount();
	for(i=1;i<=count;i++)
	{
		getSubElem(i)->setDefaultValue();
	}
}
//---------------------------------------------------------------------
int CTlgElemSegment::decodeElem(char* bytes,int count,CInterConfig* interConfig)
{
	int ret = 0;
	int elemCount;
	int len;
	int lenSubElem;
	int i,j;
	int pos;
	char* buffer = 0;
	CTlgElem* elem = 0;

  len = getTransBytesCount();
	if(count == len)
	{
		elemCount = getSubElemCount();
		pos=0;
		for(i=1;i<=elemCount;i++)
		{
			elem=getSubElem(i);
      lenSubElem=elem->getTransBytesCount();
			buffer = new char[lenSubElem*sizeof(char)];
			for(j=0;j<lenSubElem;j++)
				buffer[j]=bytes[pos+j];
			elem->decodeElem(buffer,lenSubElem,interConfig);
			pos=pos+lenSubElem;
		}
	}
	else
	{
		ret = 1;
	}

	return ret;
}
//---------------------------------------------------------------------
int CTlgElemSegment::compare(const std::string& val,const std::string& subElemName)
{
  int ret=-2;
  CTlgElem* elem=0;

  elem=getSubElem(subElemName);
  if(elem)
    ret=elem->compare(val,subElemName);
  return ret;
}
//---------------------------------------------------------------------
int CTlgElemSegment::getTransBytesCount() const
{
  int ret=0;
  int count,i;

  count = getSubElemCount();
  for(i=1;i<=count;i++)
  {
    ret = ret + getSubElem(i)->getTransBytesCount();
  }
  return ret;
}
//---------------------------------------------------------------------
