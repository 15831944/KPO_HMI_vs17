#pragma once

#include "CItemWrapper.h"
#include "CTlgElemWrapper.h"

public ref class CNodeCollectionUnit
{
public:
  CNodeCollectionUnit(CommonTools::NodeCollection^ collection);
	~CNodeCollectionUnit(void);
  int ShowItem(CItemWrapper^ item,int typ);
  
  int getAllNodesCount();
	int getItemCount();
  bool getisIdTxtEnabled();
  bool getisLenTxtEnabled();
	void clear();
  String^ getMaxDescription();
  String^ getElemValue();

private:
  void fillElemValue(CTlgElemWrapper^ itemElem,array <System::Object^>^ obj);
  int buildElemNodes (CTlgElemWrapper^ elem,CommonTools::Node^ node);
  void clearAllAtributte();
	CommonTools::NodeCollection^ m_collection;
	
  //System::Collections::ArrayList* m_allNodes;
	//System::Collections::ArrayList* m_leafNodes;
  
  System::Collections::Generic::List<CommonTools::Node^>^ m_allNodes;
  System::Collections::Generic::List<CommonTools::Node^>^ m_leafNodes;
  CItemWrapper^ Item;
  int m_maxDepth;
	int itemCount;
  bool isItemEmpty;
  bool isIdTxtEnabled;
  bool isLenTxtEnabled;
  bool LenChange;
  //Interface Einstelungen - Werten
  String^ ItemId;
  String^ ItemElemId;
  String^ ItemIdValue;
  String^ ItemLenId;
  int LenIdModus;
  int typ;
  String^ maxDesc;
  String^ ElemValue;
};