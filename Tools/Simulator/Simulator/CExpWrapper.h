
#ifndef _CExpWrapper_H_
#define _CExpWrapper_H_
//-------------------------------------------------------------
using System::String;
//-------------------------------------------------------------
public ref class CExpWrapper
{
    public:
        enum class ErrorTyp{tUnknow,tUnknowTlg,tUnknownTranspTyp,tTlgLenWrong,tDecodeElem};
        CExpWrapper(String^ mess,ErrorTyp err);
        CExpWrapper(String^ mess);
        ~CExpWrapper();
        String^ getMessage();
        ErrorTyp getErrorTyp();
    private:
        String^ Message;
        ErrorTyp Error;
};
//-------------------------------------------------------------
#endif