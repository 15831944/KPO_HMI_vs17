
#include "CXmlTlgProtoTypeReader.h"
#include "CTlgProtoTypSet.h"
#include "CTlg.h"

#include <iostream>
using namespace std;
//--------------------------------------------------------
void showInter(CTlgProtoTypSet* inter)
{
	int count,i,j,count_elem;
	CTlg* tlg=0;
    CTlgElem* elem = 0;
	cout << "Inerface:\t"<<inter->getName()<<endl;
	cout << "Version:\t"<<inter->getVersion()<<endl;
	cout << "Comment:\t"<<inter->getComment()<<endl;
	count = inter->getTlgCount();
	for(i=1;i<=count;i++)
	{
		cout << "===================" <<endl;
        tlg = inter->makeFlatTlg(i);
        cout << "Name:\t" << tlg->getTlgName() <<endl;
        cout << "Laenge:\t" << tlg->getTlgLen() <<endl;
        cout << "Comment:\t" << tlg->getDescription() <<endl;
        cout << "Direction:\t" << tlg->getDirection() <<endl;
		cout << "===================" <<endl;

        //elem = tlg->cloneElem(i);
        count_elem= tlg->getElemCount();
        if(count_elem > 0)
        {
            for(j=1;j<=count_elem;j++)
            {
                elem = tlg->cloneElem(j);
                cout << "------------------------------------"<<endl;
                cout <<"Name\t" <<elem->getNameElem()<<endl;
                cout <<"Comment\t"<<elem->getComment()<<endl;
                cout << "SubElemAnzahl\t"<<elem->getSubElemCount()<<endl;
                cout << "------------------------------------" << endl;
            }
        }
        
	}
}
//--------------------------------------------------------

int main()
{ 
	CTlgProtoTypSet* inter=0;
    CXmlTlgProtoTypeReader ProtoRead;
	inter = ProtoRead.readXmlProtoInterface("BAS_AOD_test.xml");
    if(inter)
	    showInter(inter);
	return 0;
}