#include "xmlparser.h"
#include "VDV301struktury/zastavka.h"
#include "VDV301struktury/cestaudaje.h"
#include  "VDV301struktury/pasmo.h"
#include <QDebug>
#include <QMainWindow>




XmlParser::XmlParser()
{
    qDebug()<<Q_FUNC_INFO;
}

void XmlParser::nactiXML(QString vstup)
{
    qDebug()<<Q_FUNC_INFO;

    if(vstup!=stareXml)
    {
        zmenaDat=true;
        zmenaDat=false;
    }
    else
    {
        zmenaDat=false;
    }

    dokument.setContent(vstup);
    // QString blabla = dokument.toString();


}

int XmlParser::VytvorSeznamZastavek1_0(QVector<ZastavkaCil> &docasnySeznamZst,QVector<ZastavkaCil> &docasnySeznamZstNavazny, int &docasnyIndexZastavky, int &docasnyPocetZastavek)
{
    qDebug()<<Q_FUNC_INFO;
    docasnySeznamZst.clear();
    QDomElement root = dokument.firstChildElement();
    qDebug()<<root.tagName();
    if (root.tagName()!="CustomerInformationService.GetAllDataResponse")
    {
        qDebug()<<"vadné XML";
        return 0;
    }


    QDomElement tripInformation;//=allData.firstChildElement("TripInformation");
    QDomElement tripInformation2;
    docasnyIndexZastavky=root.elementsByTagName("CurrentStopIndex").at(0).firstChildElement().text().toInt()-1; //převod indexování od 1 (VDV301) na indexování od 0 ( C++ pole)

    QDomNodeList tripInformationList=root.elementsByTagName("TripInformation");
    int pocetZastNavazSpoje=0;

    switch(tripInformationList.count())
    {
    case 0:
        qDebug()<<"seznam tripu je prazdny";
        return 0;
        break;
    case 1:
        tripInformation=tripInformationList.at(0).toElement();
        tripDoSeznamuZastavek1_0(docasnySeznamZst,tripInformation,docasnyPocetZastavek);
        break ;
    case 2:
        qDebug()<<"existuje jeden navazny spoj";
        tripInformation=tripInformationList.at(0).toElement();
        tripDoSeznamuZastavek1_0(docasnySeznamZst,tripInformation,docasnyPocetZastavek);
        tripInformation2=tripInformationList.at(1).toElement();
        tripDoSeznamuZastavek1_0(docasnySeznamZstNavazny,tripInformation2,pocetZastNavazSpoje);

        break;

    default:
        qDebug()<<"moc navaznych spoju";
        tripInformation=tripInformationList.at(0).toElement();
        tripDoSeznamuZastavek1_0(docasnySeznamZst,tripInformation,docasnyPocetZastavek);
        tripInformation2=tripInformationList.at(1).toElement();
        tripDoSeznamuZastavek1_0(docasnySeznamZstNavazny,tripInformation2,pocetZastNavazSpoje);

        break;

    }



    return 1;
}

int XmlParser::VytvorSeznamZastavek2_2CZ1_0(QVector<ZastavkaCil> &docasnySeznamZst,QVector<ZastavkaCil> &docasnySeznamZstNavazny, int &docasnyIndexZastavky, int &docasnyPocetZastavek)
{
    qDebug()<<Q_FUNC_INFO;
    docasnySeznamZst.clear();
    QDomElement root = dokument.firstChildElement();
    qDebug()<<root.tagName();
    if (root.tagName()!="CustomerInformationService.GetAllDataResponse")
    {
        qDebug()<<"vadné XML";
        return 0;
    }


    QDomElement tripInformation;//=allData.firstChildElement("TripInformation");
    QDomElement tripInformation2;
    docasnyIndexZastavky=root.elementsByTagName("CurrentStopIndex").at(0).firstChildElement().text().toInt()-1; //převod indexování od 1 (VDV301) na indexování od 0 ( C++ pole)

    QDomNodeList tripInformationList=root.elementsByTagName("TripInformation");
    int pocetZastNavazSpoje=0;

    switch(tripInformationList.count())
    {
    case 0:
        qDebug()<<"seznam tripu je prazdny";
        return 0;
        break;
    case 1:
        tripInformation=tripInformationList.at(0).toElement();
        tripDoSeznamuZastavek2_2CZ1_0(docasnySeznamZst,tripInformation,docasnyPocetZastavek);
        break ;
    case 2:
        qDebug()<<"existuje jeden navazny spoj";
        tripInformation=tripInformationList.at(0).toElement();
        tripDoSeznamuZastavek2_2CZ1_0(docasnySeznamZst,tripInformation,docasnyPocetZastavek);
        tripInformation2=tripInformationList.at(1).toElement();
        tripDoSeznamuZastavek2_2CZ1_0(docasnySeznamZstNavazny,tripInformation2,pocetZastNavazSpoje);

        break;

    default:
        qDebug()<<"moc navaznych spoju";
        tripInformation=tripInformationList.at(0).toElement();
        tripDoSeznamuZastavek2_2CZ1_0(docasnySeznamZst,tripInformation,docasnyPocetZastavek);
        tripInformation2=tripInformationList.at(1).toElement();
        tripDoSeznamuZastavek2_2CZ1_0(docasnySeznamZstNavazny,tripInformation2,pocetZastNavazSpoje);

        break;

    }



    return 1;
}



int XmlParser::VytvorSeznamZastavek2_4(QVector<ZastavkaCil> &docasnySeznamZst,QVector<ZastavkaCil> &docasnySeznamZstNavazny, int &docasnyIndexZastavky, int &docasnyPocetZastavek)
{
    qDebug()<<Q_FUNC_INFO;
    docasnySeznamZst.clear();
    QDomElement root = dokument.firstChildElement();
    qDebug()<<root.tagName();
    if (root.tagName()!="CustomerInformationService.GetAllDataResponse")
    {
        qDebug()<<"vadné XML";
        return 0;
    }


    QDomElement tripInformation;//=allData.firstChildElement("TripInformation");
    QDomElement tripInformation2;
    docasnyIndexZastavky=root.elementsByTagName("CurrentStopIndex").at(0).firstChildElement().text().toInt()-1; //převod indexování od 1 (VDV301) na indexování od 0 ( C++ pole)

    QDomNodeList tripInformationList=root.elementsByTagName("TripInformation");
    int pocetZastNavazSpoje=0;

    switch(tripInformationList.count())
    {
    case 0:
        qDebug()<<"seznam tripu je prazdny";
        return 0;
        break;
    case 1:
        tripInformation=tripInformationList.at(0).toElement();
        tripDoSeznamuZastavek2_4(docasnySeznamZst,tripInformation,docasnyPocetZastavek);
        break ;
    case 2:
        qDebug()<<"existuje jeden navazny spoj";
        tripInformation=tripInformationList.at(0).toElement();
        tripDoSeznamuZastavek2_4(docasnySeznamZst,tripInformation,docasnyPocetZastavek);
        tripInformation2=tripInformationList.at(1).toElement();
        tripDoSeznamuZastavek2_4(docasnySeznamZstNavazny,tripInformation2,pocetZastNavazSpoje);

        break;

    default:
        qDebug()<<"moc navaznych spoju";
        tripInformation=tripInformationList.at(0).toElement();
        tripDoSeznamuZastavek2_4(docasnySeznamZst,tripInformation,docasnyPocetZastavek);
        tripInformation2=tripInformationList.at(1).toElement();
        tripDoSeznamuZastavek2_4(docasnySeznamZstNavazny,tripInformation2,pocetZastNavazSpoje);

        break;

    }



    return 1;
}
QDateTime XmlParser::vyparsujTimestamp(QDomDocument vstupniDokument)
{
    qDebug()<<Q_FUNC_INFO;



    QDateTime timestamp =  QDateTime::fromString(vstupniDokument.firstChildElement("CustomerInformationService.GetAllDataResponse").firstChildElement("AllData").firstChildElement("TimeStamp").firstChildElement("Value").firstChild().nodeValue() ,Qt::ISODate);

    return timestamp;

}


int XmlParser::udajeNavaznehoSpoje(QVector<ZastavkaCil> &docasnySeznamZst, QString &linka, QString &cil)
{
    if (docasnySeznamZst.isEmpty())
    {
        return 0;
    }
    linka=docasnySeznamZst.first().linka.LineName;
    cil=docasnySeznamZst.first().cil.NameLcd;


    return 1;
}


int XmlParser::tripDoSeznamuZastavek1_0(QVector<ZastavkaCil> &docasnySeznamZst, QDomElement vstup, int &docasnyPocetZastavek)
{
    qDebug()<<Q_FUNC_INFO;

    QDomNodeList nodes = vstup.elementsByTagName("StopPoint");

    docasnyPocetZastavek= nodes.count();
    for (int i=0; i<nodes.count();i++)
    {

        ZastavkaCil docasnaZastavka;
        QDomElement aktZastavkaDOM=nodes.at(i).toElement();
        int poradiZastavky=aktZastavkaDOM.elementsByTagName("StopIndex").at(0).firstChildElement().text().toInt();
        docasnaZastavka.zastavka.StopName=aktZastavkaDOM.firstChildElement("StopName").firstChildElement().text();
        docasnaZastavka.zastavka.NameFront=aktZastavkaDOM.firstChildElement("StopName").firstChildElement().text();
        docasnaZastavka.zastavka.NameSide=aktZastavkaDOM.firstChildElement("StopName").firstChildElement().text();
        docasnaZastavka.zastavka.NameRear=aktZastavkaDOM.firstChildElement("StopName").firstChildElement().text();
        docasnaZastavka.zastavka.NameInner=aktZastavkaDOM.firstChildElement("StopName").firstChildElement().text();
        docasnaZastavka.zastavka.NameLcd=aktZastavkaDOM.firstChildElement("StopName").firstChildElement().text();
        docasnaZastavka.linka.LineName=aktZastavkaDOM.firstChildElement("DisplayContent").firstChildElement("LineInformation").firstChildElement("LineName").firstChildElement().text();

        QVector<QString> priznakyStringy;

        QDomNodeList seznamPriznakuElements=aktZastavkaDOM.firstChildElement("DisplayContent").firstChildElement("LineInformation").elementsByTagName("LineProperty");


        for(int j=0; j<seznamPriznakuElements.count();j++)
        {
            QString priznak=seznamPriznakuElements.at(j).firstChild().nodeValue();
            priznakyStringy.push_back(priznak);
            // qDebug()<<"parsuju priznaky:"<<priznak;
        }
        docasnaZastavka.linka=priznakyDoLinky(priznakyStringy,docasnaZastavka.linka);

        docasnaZastavka.zastavka.StopIndex=i;
        docasnaZastavka.nacestneZastavky=vyparsujNacestneZastavky1_0(aktZastavkaDOM);
        docasnaZastavka.zastavka.seznamPrestupu=nactiPrestupy(aktZastavkaDOM);

        QDomElement displayContent=aktZastavkaDOM.firstChildElement("DisplayContent");
        QDomElement dDestination=displayContent.firstChildElement("Destination");
        docasnaZastavka.cil.StopName=dDestination.firstChildElement("DestinationName").text();
        docasnaZastavka.cil.NameFront=dDestination.firstChildElement("DestinationName").firstChildElement().text();
        docasnaZastavka.cil.seznamPiktogramu=naplnVektorPriznaku(displayContent.elementsByTagName("Destination").at(0),"Destination");

        QDomNodeList nazvyCelniPanel=dDestination.elementsByTagName("DestinationName");
        if (nazvyCelniPanel.length()>0)
        {
            docasnaZastavka.cil.NameFront=nazvyCelniPanel.at(0).firstChildElement().text();
        }
        if (nazvyCelniPanel.length()>1)
        {
            docasnaZastavka.cil.NameFront2=nazvyCelniPanel.at(1).firstChildElement().text();
        }
        docasnaZastavka.zastavka.seznamPiktogramu= naplnVektorPriznaku(aktZastavkaDOM,"Stop");


        docasnaZastavka.cil.NameSide=dDestination.firstChildElement("DestinationName").firstChildElement().text();
        docasnaZastavka.cil.NameRear=dDestination.firstChildElement("DestinationName").firstChildElement().text();
        docasnaZastavka.cil.NameInner=dDestination.firstChildElement("DestinationName").firstChildElement().text();
        docasnaZastavka.cil.NameLcd=dDestination.firstChildElement("DestinationName").firstChildElement().text();

        //    qInfo()<< "xml "<<QString::number(poradiZastavky)<<"i "<<QString::number(i) << docasnaZastavka.zastavka.StopName<<"cil"<<docasnaZastavka.cil.NameLcd<<"linka "<<docasnaZastavka.linka.LineName<<" nocni "<<docasnaZastavka.linka.isNight ;
        docasnaZastavka.zastavka.seznamPasem=vyparsujPasma_1_0(aktZastavkaDOM);
        docasnySeznamZst.push_back(docasnaZastavka);
    }
    if (docasnySeznamZst.size() ==0)
    {
        qDebug()<<"zastavkyNebylyNacteny";
        return 0;
    }
    return 1;
}

int XmlParser::tripDoSeznamuZastavek2_2CZ1_0(QVector<ZastavkaCil> &docasnySeznamZst, QDomElement vstup, int &docasnyPocetZastavek)
{
    qDebug()<<Q_FUNC_INFO;

    QDomNodeList nodes = vstup.elementsByTagName("StopPoint");

    docasnyPocetZastavek= nodes.count();
    for (int i=0; i<nodes.count();i++)
    {

        ZastavkaCil docasnaZastavka;
        QDomElement aktZastavkaDOM=nodes.at(i).toElement();
        int poradiZastavky=aktZastavkaDOM.elementsByTagName("StopIndex").at(0).firstChildElement().text().toInt();
        docasnaZastavka.zastavka.StopName=aktZastavkaDOM.firstChildElement("StopName").firstChildElement().text();
        docasnaZastavka.zastavka.NameFront=aktZastavkaDOM.firstChildElement("StopFrontName").firstChildElement().text();
        docasnaZastavka.zastavka.NameSide=aktZastavkaDOM.firstChildElement("StopSideName").firstChildElement().text();
        docasnaZastavka.zastavka.NameRear=aktZastavkaDOM.firstChildElement("StopRearName").firstChildElement().text();
        docasnaZastavka.zastavka.NameInner=aktZastavkaDOM.firstChildElement("StopInnerName").firstChildElement().text();
        docasnaZastavka.zastavka.NameLcd=aktZastavkaDOM.firstChildElement("StopLcdName").firstChildElement().text();
        docasnaZastavka.linka.LineName=aktZastavkaDOM.firstChildElement("DisplayContent").firstChildElement("LineInformation").firstChildElement("LineName").firstChildElement().text();

        QVector<QString> priznakyStringy;

        QDomNodeList seznamPriznakuElements=aktZastavkaDOM.firstChildElement("DisplayContent").firstChildElement("LineInformation").elementsByTagName("LineProperty");


        for(int j=0; j<seznamPriznakuElements.count();j++)
        {
            QString priznak=seznamPriznakuElements.at(j).firstChild().nodeValue();
            priznakyStringy.push_back(priznak);
            // qDebug()<<"parsuju priznaky:"<<priznak;
        }
        docasnaZastavka.linka=priznakyDoLinky(priznakyStringy,docasnaZastavka.linka);

        docasnaZastavka.zastavka.StopIndex=i;
        docasnaZastavka.nacestneZastavky=vyparsujNacestneZastavky2_2CZ1_0(aktZastavkaDOM);
        docasnaZastavka.zastavka.seznamPrestupu=nactiPrestupy(aktZastavkaDOM);

        QDomElement displayContent=aktZastavkaDOM.firstChildElement("DisplayContent");
        QDomElement dDestination=displayContent.firstChildElement("Destination");
        docasnaZastavka.cil.StopName=dDestination.firstChildElement("DestinationName").text();
        docasnaZastavka.cil.NameFront=dDestination.firstChildElement("DestinationFrontName").firstChildElement().text();
        docasnaZastavka.cil.seznamPiktogramu=naplnVektorPriznaku(displayContent.elementsByTagName("Destination").at(0),"Destination");

        QDomNodeList nazvyCelniPanel=dDestination.elementsByTagName("DestinationFrontName");
        if (nazvyCelniPanel.length()>0)
        {
            docasnaZastavka.cil.NameFront=nazvyCelniPanel.at(0).firstChildElement().text();
        }
        if (nazvyCelniPanel.length()>1)
        {
            docasnaZastavka.cil.NameFront2=nazvyCelniPanel.at(1).firstChildElement().text();
        }
        docasnaZastavka.zastavka.seznamPiktogramu= naplnVektorPriznaku(aktZastavkaDOM,"Stop");


        docasnaZastavka.cil.NameSide=dDestination.firstChildElement("DestinationSideName").firstChildElement().text();
        docasnaZastavka.cil.NameRear=dDestination.firstChildElement("DestinationRearName").firstChildElement().text();
        docasnaZastavka.cil.NameInner=dDestination.firstChildElement("DestinationInnerName").firstChildElement().text();
        docasnaZastavka.cil.NameLcd=dDestination.firstChildElement("DestinationLcdName").firstChildElement().text();

        //    qInfo()<< "xml "<<QString::number(poradiZastavky)<<"i "<<QString::number(i) << docasnaZastavka.zastavka.StopName<<"cil"<<docasnaZastavka.cil.NameLcd<<"linka "<<docasnaZastavka.linka.LineName<<" nocni "<<docasnaZastavka.linka.isNight ;
        docasnaZastavka.zastavka.seznamPasem=vyparsujPasma_2_2CZ1_0(aktZastavkaDOM);
        docasnySeznamZst.push_back(docasnaZastavka);
    }
    if (docasnySeznamZst.size() ==0)
    {
        qDebug()<<"zastavkyNebylyNacteny";
        return 0;
    }
    return 1;
}



int XmlParser::tripDoSeznamuZastavek2_4(QVector<ZastavkaCil> &docasnySeznamZst, QDomElement vstup, int &docasnyPocetZastavek)
{
    qDebug()<<Q_FUNC_INFO;

    QDomNodeList nodes = vstup.elementsByTagName("StopPoint");

    docasnyPocetZastavek= nodes.count();
    for (int i=0; i<nodes.count();i++)
    {

        ZastavkaCil docasnaZastavka;
        QDomElement aktZastavkaDOM=nodes.at(i).toElement();
        int poradiZastavky=aktZastavkaDOM.elementsByTagName("StopIndex").at(0).firstChildElement().text().toInt();
        docasnaZastavka.zastavka.StopName=aktZastavkaDOM.firstChildElement("StopName").firstChildElement().text();
        docasnaZastavka.zastavka.NameFront=aktZastavkaDOM.firstChildElement("StopName").firstChildElement().text();
        docasnaZastavka.zastavka.NameSide=aktZastavkaDOM.firstChildElement("StopName").firstChildElement().text();
        docasnaZastavka.zastavka.NameRear=aktZastavkaDOM.firstChildElement("StopName").firstChildElement().text();
        docasnaZastavka.zastavka.NameInner=aktZastavkaDOM.firstChildElement("StopName").firstChildElement().text();
        docasnaZastavka.zastavka.NameLcd=aktZastavkaDOM.firstChildElement("StopName").firstChildElement().text();
        docasnaZastavka.linka.LineName=aktZastavkaDOM.firstChildElement("DisplayContent").firstChildElement("LineInformation").firstChildElement("LineName").firstChildElement().text();

        QVector<QString> priznakyStringy;

        QDomNodeList seznamPriznakuElements=aktZastavkaDOM.firstChildElement("DisplayContent").firstChildElement("LineInformation").elementsByTagName("LineProperty");


        for(int j=0; j<seznamPriznakuElements.count();j++)
        {
            QString priznak=seznamPriznakuElements.at(j).firstChild().nodeValue();
            priznakyStringy.push_back(priznak);
            // qDebug()<<"parsuju priznaky:"<<priznak;
        }
        docasnaZastavka.linka=priznakyDoLinky(priznakyStringy,docasnaZastavka.linka);




        QDomNodeList displayContentArray=aktZastavkaDOM.elementsByTagName("DisplayContent");

        for (int k=0;k<displayContentArray.length();k++)
        {
            qDebug()<<"aktualniDisplayContent: "<<QString::number(k);
            QDomNode aktualniDisplayContent=displayContentArray.at(k);
            QString ref=aktualniDisplayContent.firstChildElement("DisplayContentRef").firstChildElement("Value").firstChild().nodeValue();
            if(ref=="Front")
            {
                docasnaZastavka.cil.NameFront=aktualniDisplayContent.firstChildElement("Destination").firstChildElement("DestinationName").firstChildElement("Value").firstChild().nodeValue();

            }
            if(ref=="Side")
            {
                docasnaZastavka.cil.NameSide=aktualniDisplayContent.firstChildElement("Destination").firstChildElement("DestinationName").firstChildElement("Value").firstChild().nodeValue();

            }
            if(ref=="Rear")
            {
                docasnaZastavka.cil.NameRear=aktualniDisplayContent.firstChildElement("Destination").firstChildElement("DestinationName").firstChildElement("Value").firstChild().nodeValue();

            }
            if(ref=="Lcd")
            {
                docasnaZastavka.cil.NameLcd=aktualniDisplayContent.firstChildElement("Destination").firstChildElement("DestinationName").firstChildElement("Value").firstChild().nodeValue();
                docasnaZastavka.nacestneZastavky=vyparsujNacestneZastavky2_4(aktualniDisplayContent);
                //   docasnaZastavka.cil.StopName =polozka.firstChildElement("Destination").firstChildElement("DestinationName").firstChildElement().text();

            }


        }



        docasnaZastavka.zastavka.StopIndex=i;


        docasnaZastavka.zastavka.seznamPrestupu=nactiPrestupy(aktZastavkaDOM);

        docasnaZastavka.zastavka.seznamPiktogramu= naplnVektorPriznaku(aktZastavkaDOM,"Stop");

        // QDomElement displayContent=aktZastavkaDOM.firstChildElement("DisplayContent");
        // QDomElement dDestination=displayContent.firstChildElement("Destination");
        //   docasnaZastavka.cil.StopName=dDestination.firstChildElement("DestinationName").text();
        //     docasnaZastavka.cil.NameFront=dDestination.firstChildElement("DestinationFrontName").firstChildElement().text();

        // XXXXX   docasnaZastavka.cil.seznamPiktogramu=naplnVektorPriznaku(displayContent.elementsByTagName("Destination").at(0),"Destination");

        /*
        QDomNodeList nazvyCelniPanel=dDestination.elementsByTagName("DestinationFrontName");
        if (nazvyCelniPanel.length()>0)
        {
            docasnaZastavka.cil.NameFront=nazvyCelniPanel.at(0).firstChildElement().text();
        }
        if (nazvyCelniPanel.length()>1)
        {
            docasnaZastavka.cil.NameFront2=nazvyCelniPanel.at(1).firstChildElement().text();
        }
        docasnaZastavka.zastavka.seznamPiktogramu= naplnVektorPriznaku(aktZastavkaDOM,"Stop");
*/

        /*
        docasnaZastavka.cil.NameSide=dDestination.firstChildElement("DestinationSideName").firstChildElement().text();
        docasnaZastavka.cil.NameRear=dDestination.firstChildElement("DestinationRearName").firstChildElement().text();
        docasnaZastavka.cil.NameInner=dDestination.firstChildElement("DestinationInnerName").firstChildElement().text();
        docasnaZastavka.cil.NameLcd=dDestination.firstChildElement("DestinationLcdName").firstChildElement().text();
*/


        //    qInfo()<< "xml "<<QString::number(poradiZastavky)<<"i "<<QString::number(i) << docasnaZastavka.zastavka.StopName<<"cil"<<docasnaZastavka.cil.NameLcd<<"linka "<<docasnaZastavka.linka.LineName<<" nocni "<<docasnaZastavka.linka.isNight ;
        docasnaZastavka.zastavka.seznamPasem=vyparsujPasma_2_2CZ1_0(aktZastavkaDOM);
        docasnySeznamZst.push_back(docasnaZastavka);
        globalniSeznamZastavek2_4.insert(poradiZastavky,docasnaZastavka);
    }
    if (docasnySeznamZst.size()==0)
    {
        qDebug()<<"zastavkyNebylyNacteny";
        return 0;
    }
    return 1;
}

QVector<QString> XmlParser::naplnVektorPriznaku(QDomNode vstup,QString nazevElementu)
{
    // qDebug()<<"XmlParser::naplnVektorPriznaku";
    QVector<QString> vystup;

    Zastavka nacesta;
    QDomNodeList priznaky=vstup.toElement().elementsByTagName(nazevElementu+"Property");
    // qDebug()<<"naplnVektor Zastavka ma tolik priznaku:"<<priznaky.count();

    for (int j=0;j<priznaky.count();j++)
    {
        QString hodnotaPriznaku=priznaky.at(j).firstChild().nodeValue();
        //     qDebug()<<"priznak "<<hodnotaPriznaku;
        vystup.push_back(hodnotaPriznaku);
    }
    return vystup;
}






QVector<Zastavka> XmlParser::vyparsujNacestneZastavky1_0(QDomElement zastavka)
{
    qDebug()<<Q_FUNC_INFO;
    QDomNodeList nacesty = zastavka.elementsByTagName("ViaPoint");
    QVector<Zastavka> vectorNacesty;
    for (int i=0;i<nacesty.count();i++)
    {
        Zastavka nacesta;
        // QDomNodeList priznaky=nacesty.at(i).toElement().elementsByTagName("ViaPointProperty");
        QDomElement aktNacesta=nacesty.at(i).toElement();
        nacesta.NameLcd=aktNacesta.firstChildElement("PlaceName").firstChildElement("Value").firstChild().nodeValue();
        nacesta.NameInner=aktNacesta.firstChildElement("PlaceName").firstChildElement("Value").firstChild().nodeValue();
        nacesta.NameSide=aktNacesta.firstChildElement("PlaceName").firstChildElement("Value").firstChild().nodeValue();
        nacesta.StopName=nacesta.NameLcd;

        /*
        nacesta.seznamPiktogramu= naplnVektorPriznaku(aktNacesta,"ViaPoint");
        for (int j=0;j<priznaky.count();j++)
        {
            QString hodnotaPriznaku=priznaky.at(j).firstChild().nodeValue();
            qDebug()<<"priznak "<<hodnotaPriznaku;


            if(hodnotaPriznaku=="RequestStop")
            {
                nacesta.naZnameni=true;
            }
        }*/

        vectorNacesty.append(nacesta);
    }

    return vectorNacesty;
}


QVector<Zastavka> XmlParser::vyparsujNacestneZastavky2_2CZ1_0(QDomElement zastavka)
{
    qDebug()<<Q_FUNC_INFO;
    QDomNodeList nacesty = zastavka.elementsByTagName("ViaPoint");
    QVector<Zastavka> vectorNacesty;
    for (int i=0;i<nacesty.count();i++)
    {
        Zastavka nacesta;
        QDomNodeList priznaky=nacesty.at(i).toElement().elementsByTagName("ViaPointProperty");
        QDomElement aktNacesta=nacesty.at(i).toElement();
        nacesta.NameLcd=aktNacesta.firstChildElement("PlaceLcdName").firstChildElement("Value").firstChild().nodeValue();
        nacesta.NameInner=aktNacesta.firstChildElement("PlaceInnerName").firstChildElement("Value").firstChild().nodeValue();
        nacesta.NameSide=aktNacesta.firstChildElement("PlaceSideName").firstChildElement("Value").firstChild().nodeValue();
        nacesta.StopName=nacesta.NameLcd;


        nacesta.seznamPiktogramu= naplnVektorPriznaku(aktNacesta,"ViaPoint");
        for (int j=0;j<priznaky.count();j++)
        {
            QString hodnotaPriznaku=priznaky.at(j).firstChild().nodeValue();
            qDebug()<<"priznak "<<hodnotaPriznaku;


            if(hodnotaPriznaku=="RequestStop")
            {
                nacesta.naZnameni=true;
            }
        }

        vectorNacesty.append(nacesta);
    }

    return vectorNacesty;
}


QVector<Zastavka> XmlParser::vyparsujNacestneZastavky2_4(QDomNode displayContent)
{
    qDebug()<<Q_FUNC_INFO;
    QDomNodeList nacesty = displayContent.toElement().elementsByTagName("ViaPoint");
    QVector<Zastavka> vectorNacesty;
    for (int i=0;i<nacesty.count();i++)
    {


        Zastavka nacesta;
        QDomElement aktNacesta=nacesty.at(i).toElement();
        nacesta.NameLcd=aktNacesta.firstChildElement("PlaceName").firstChildElement("Value").firstChild().nodeValue();
        nacesta.NameInner=aktNacesta.firstChildElement("PlaceName").firstChildElement("Value").firstChild().nodeValue();
        nacesta.NameSide=aktNacesta.firstChildElement("PlaceName").firstChildElement("Value").firstChild().nodeValue();
        nacesta.StopName=nacesta.NameLcd;

        /*
        QDomNodeList priznaky=nacesty.at(i).toElement().elementsByTagName("ViaPointProperty");
        nacesta.seznamPiktogramu= naplnVektorPriznaku(aktNacesta,"ViaPoint");
        for (int j=0;j<priznaky.count();j++)
        {
            QString hodnotaPriznaku=priznaky.at(j).firstChild().nodeValue();
            qDebug()<<"priznak "<<hodnotaPriznaku;


            if(hodnotaPriznaku=="RequestStop")
            {
                nacesta.naZnameni=true;
            }
        }
*/

        vectorNacesty.append(nacesta);
    }

    return vectorNacesty;
}

QVector<Pasmo> XmlParser::vyparsujPasma_1_0(QDomElement zastavka)
{
    qDebug()<<Q_FUNC_INFO;
    QVector<Pasmo> vystupniVektorPasmo;

    QDomNodeList domPasma = zastavka.elementsByTagName("FareZone");

    for (int i=0;i<domPasma.count();i++)
    {
        Pasmo aktPasmo;
        aktPasmo.system="";
        aktPasmo.nazev=domPasma.at(i).firstChildElement("Value").firstChild().nodeValue();
        vystupniVektorPasmo.append(aktPasmo);

    }

    return vystupniVektorPasmo;
}

QVector<Pasmo> XmlParser::vyparsujPasma_2_2CZ1_0(QDomElement zastavka)
{
    qDebug()<<Q_FUNC_INFO;
    QVector<Pasmo> vystupniVektorPasmo;

    QDomNodeList domPasma = zastavka.elementsByTagName("FareZone");

    for (int i=0;i<domPasma.count();i++)
    {
        Pasmo aktPasmo;
        aktPasmo.system=domPasma.at(i).firstChildElement("FareZoneType").firstChildElement("FareZoneTypeName").firstChildElement("Value").firstChild().nodeValue();
        aktPasmo.nazev=domPasma.at(i).firstChildElement("FareZoneLongName").firstChildElement("Value").firstChild().nodeValue();
        vystupniVektorPasmo.append(aktPasmo);

    }

    return vystupniVektorPasmo;
}
int XmlParser::nactiVehicleGroup(CestaUdaje &stav,QDomDocument xmlko )
{
    qDebug()<<Q_FUNC_INFO;
    QDomElement root = xmlko.firstChildElement();
    qDebug()<<"root name "<<root.nodeName();
    QDomElement allData=root.firstChildElement("AllData");
    qDebug()<<"alldata name "<<allData.nodeName();
    stav.indexAktZastavky=allData.firstChildElement("CurrentStopIndex").firstChildElement().firstChild().nodeValue().toInt()-1; //-1
    stav.VehicleStopRequested=allData.firstChildElement("VehicleStopRequested").firstChildElement("Value").firstChild().nodeValue().toInt();
    stav.locationState=allData.firstChildElement("TripInformation").firstChildElement("LocationState").firstChild().nodeValue();
    stav.vehicleMode=allData.firstChildElement("MyOwnVehicleMode").firstChildElement("PtMainMode").firstChild().nodeValue();
    stav.vehicleSubMode=allData.firstChildElement("MyOwnVehicleMode").firstChildElement(stav.vehicleMode).firstChild().nodeValue();
    qDebug()<<"stopIndex "<<QString::number(stav.indexAktZastavky)<<"stopRequested "<<stav.VehicleStopRequested<<" locState "<<stav.locationState;

    return 1;
}


int XmlParser::nactiAdditionalTextMessage(QDomDocument xmlko, QString &type ,QString &headline,QString &text )
{
    qDebug()<<Q_FUNC_INFO;



    QDomElement root = xmlko.firstChildElement();



    qDebug()<<"root name "<<root.nodeName();
    QDomElement allData=root.firstChildElement("AllData");


    if (allData.isNull())
    {
        qDebug()<<"element alldata neni k dispozici";
        return 0;
    }



    qDebug()<<"alldata name "<<allData.nodeName();



    QDomElement tripInformation=allData.firstChildElement("TripInformation");



    QDomElement additionalTextMessage=tripInformation.firstChildElement("AdditionalTextMessage");
    type=additionalTextMessage.firstChildElement("AdditionalTextMessageType").firstChildElement("Value").firstChild().nodeValue();
    headline=additionalTextMessage.firstChildElement("AdditionalTextMessageHeadline").firstChildElement("Value").firstChild().nodeValue();
    text=additionalTextMessage.firstChildElement("AdditionalTextMessageText").firstChildElement("Value").firstChild().nodeValue();




    qDebug()<<"additional text je "<<type<<" "<<headline<<" "<<text;


    return 1;
}

int XmlParser::nactiFareZoneChange(QDomDocument xmlko, QVector<Pasmo> &pasmaZ, QVector<Pasmo> &pasmaNa )
{
    //rozepsano
    qDebug()<<Q_FUNC_INFO;

    QDomElement root = xmlko.firstChildElement();
    QDomElement allData=root.firstChildElement("AllData");
    QDomElement tripInformation=allData.firstChildElement("TripInformation");
    QDomElement fareZoneChange=tripInformation.firstChildElement("FareZoneChange");
    if (fareZoneChange.isNull())
    {
        qDebug()<<"element FareZoneChange není vyplněn";
        return 0;
    }

    QDomElement fromFareZones=fareZoneChange.firstChildElement("FromFareZones");
    pasmaZ=vyparsujPasma_2_2CZ1_0(fromFareZones);

    QDomElement toFareZones=fareZoneChange.firstChildElement("ToFareZones");
    pasmaNa=vyparsujPasma_2_2CZ1_0(toFareZones);

    qDebug()<<"pocet pasem Z "<<pasmaZ.count()<<" pocet pasem DO "<<pasmaNa.count();
    return 1;
}



void XmlParser::Test()
{
    qDebug()<<Q_FUNC_INFO;
    qInfo()<<"xmlParserTestPoint2";
}



int XmlParser::existujeNavaznySpoj(QVector<ZastavkaCil> seznamZastavek)
{
    if (seznamZastavek.isEmpty())
    {
        return false;
    }
    return true;


}





QVector<Prestup> XmlParser::nactiPrestupy(QDomElement vstup)
{
    //rozepsano
    qDebug()<<Q_FUNC_INFO;
    QVector<Prestup> vystup;

    QDomNodeList elementyPrestupu=vstup.elementsByTagName("Connection") ;

    for (int i=0;i<elementyPrestupu.count();i++)
    {
        Prestup aktualniPrestup;
        QDomElement aktualniElement=elementyPrestupu.at(i).toElement();
        aktualniPrestup.connectionProperty=aktualniElement.firstChildElement("ConnectionProperty").firstChild().nodeValue();

        aktualniPrestup.connectionType=aktualniElement.firstChildElement("ConnectionType").firstChild().nodeValue();

        QDomElement displayContent=aktualniElement.firstChildElement("DisplayContent");
        QDomElement lineInformation=displayContent.firstChildElement("LineInformation");

        aktualniPrestup.line.LineName=lineInformation.firstChildElement("LineName").firstChildElement("Value").firstChild().nodeValue();
        aktualniPrestup.line.LineNumber=lineInformation.firstChildElement("LineNumber").firstChildElement("Value").firstChild().nodeValue();

        aktualniPrestup.destinationName=displayContent.firstChildElement("Destination").firstChildElement("DestinationName").firstChildElement("Value").firstChild().nodeValue();
        aktualniPrestup.expectedDepartureTime=QDateTime::fromString( aktualniElement.firstChildElement("ExpectedDepartureTime").firstChildElement("Value").firstChild().nodeValue(),Qt::ISODate);

        QDateTime timestamp = aktualniPrestup.expectedDepartureTime;
        // timestamp.setTimeSpec(Qt::UTC); // mark the timestamp as UTC (but don't convert it)
        //  timestamp = timestamp.toLocalTime(); // convert to local time

        /*
        QString vysledek= QString::number(-timestamp.secsTo(QDateTime::currentDateTime())/60)+" min." ;
        aktualniPrestup.expectedDepartureTime=vysledek;
    */
        // aktualniPrestup.departureTime=timestamp.toString("hh:mm");

        aktualniPrestup.platform=aktualniElement.firstChildElement("Platform").firstChildElement("Value").firstChild().nodeValue();

        QDomElement connectionMode=aktualniElement.firstChildElement("ConnectionMode");
        aktualniPrestup.mainMode=connectionMode.firstChildElement("PtMainMode").firstChild().nodeValue();
        aktualniPrestup.subMode=connectionMode.firstChildElement(aktualniPrestup.mainMode).firstChild().nodeValue();

        QVector<QString> priznakyStringy;

        QDomNodeList seznamPriznakuElements=aktualniElement.elementsByTagName("LineProperty");

        for(int j=0; j<seznamPriznakuElements.count();j++)
        {
            QString priznak=seznamPriznakuElements.at(j).firstChild().nodeValue();
            priznakyStringy.push_back(priznak);
        }
        aktualniPrestup.line=priznakyDoLinky(priznakyStringy,aktualniPrestup.line);

        //    qDebug()<<"XmlParser::nactiPrestupy "<<aktualniPrestup.connectionProperty<<" "<<aktualniPrestup.line.LineName<<" "<<aktualniPrestup.destinationName<<" "<<aktualniPrestup.expectedDepartureTime<<" "<<aktualniPrestup.mainMode<<" "<<aktualniPrestup.subMode<<" "<<aktualniPrestup.platform<<" replacement "<<aktualniPrestup.line.isReplacement;

        vystup.push_back(aktualniPrestup);
    }
    return vystup;
}


Line XmlParser::priznakyDoLinky(QVector<QString> vstup, Line vstupniLinka)
{
    qDebug()<<Q_FUNC_INFO;
    // qDebug()<<"linka je nocni:"<<vstupniLinka.isNight;
    foreach(QString textPriznak,vstup)
    {
      //  qDebug()<<"priznakLinky: "<<textPriznak;
        if(textPriznak=="Night")
        {
            vstupniLinka.isNight=true;
            //  qDebug()<<"linka je nocni";
        }
        if(textPriznak=="Day")
        {
            vstupniLinka.isNight=false;
        }
        if(textPriznak=="Diversion")
        {
            vstupniLinka.isDiversion=true;
        }
        if(textPriznak=="Replacement")
        {
            vstupniLinka.isReplacement=true;
            qDebug()<<"linak je nahradni";
        }
        if(textPriznak=="Special")
        {
            vstupniLinka.isSpecial=true;
        }
        if(textPriznak=="WheelChair")
        {
            vstupniLinka.isWheelchair=true;
        }
        /*
        if(textPriznak=="")
        {
            vstupniLinka.=true;
        }
        */
    }
    // qDebug()<<"linka je nocni:"<<vstupniLinka.isNight;
    return vstupniLinka;

}



