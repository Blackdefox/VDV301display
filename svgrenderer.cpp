#include "svgrenderer.h"
#include <QWidget>
#include <QDebug>
#include <QDomDocument>
#include <QFile>
#include <VDV301struktury/zastavka.h>
#include "VDV301struktury/cestaudaje.h"

SvgRenderer::SvgRenderer(QString cesta)
{
    interniCestaSlozkaSvg=cesta;
}


QDomDocument SvgRenderer::souborDoQDomDocument(QString cesta)
{
    qDebug()<<"SvgVykreslovani::souborDoQDomDocument";



    qDebug()<<"SvgVykreslovani::svgReplaceName";
    QDomDocument xmlDocument;
    QFile f(cesta);
    if(!f.open(QIODevice::ReadOnly))
    {
        qDebug("Error While Reading the File");
        //return 0;
    }

    xmlDocument.setContent(&f);
    f.close();
    qDebug("File was closed Successfully");
    return xmlDocument;
}

int SvgRenderer::qDomDocumentDoSouboru(QString cestaVystupnihoSouboru,QDomDocument vstupniDom)
{
    qDebug()<<"SvgVykreslovani::qDomDocumentDoSouboru";



    QFile file(cestaVystupnihoSouboru);
    qDebug()<<"zapisuju svg do "<<cestaVystupnihoSouboru;
    if(!file.open(QIODevice::WriteOnly))
    {
        qDebug("Error While Reading the File");
        return 0;
    }
    QByteArray msg=vstupniDom.toByteArray();
    file.write(msg, qstrlen(msg));        // write to stderr
    file.close();
    return 1;
}

bool SvgRenderer::svgReplaceName(QString souborVstup, QString souborVystup,QString cil, QString zst0, QString zst1, QString zst2)
{
    qDebug()<<"SvgVykreslovani::svgReplaceName";
    QDomDocument xmlDocument;
    QFile f(souborVstup);
    if(!f.open(QIODevice::ReadOnly))
    {
        qDebug("Error While Reading the File");
        return 0;
    }

    xmlDocument.setContent(&f);
    f.close();
    qDebug("File was closed Successfully");



    this->individualniNahrazeni(xmlDocument,"terminal_station",cil);
    this->individualniNahrazeni(xmlDocument,"next_stop_0",zst0);
    this->individualniNahrazeni(xmlDocument,"next_stop_1",zst1);
    this->individualniNahrazeni(xmlDocument,"next_stop_2",zst2);



    QFile file(souborVystup);
    if(!file.open(QIODevice::WriteOnly))
    {
        qDebug("Error While Reading the File");
        return 0;
    }
    QByteArray msg=xmlDocument.toByteArray();
    file.write(msg, qstrlen(msg));        // write to stderr
    file.close();

    return 1;
}


bool SvgRenderer::individualniNahrazeni(QDomDocument &xmlDocument, QString hledaneId, QString novaHodnota)
{
    qDebug()<<Q_FUNC_INFO<<" "<<hledaneId<<" "<<novaHodnota;

    QDomNodeList texty = xmlDocument.elementsByTagName("text");

    for (int i=0;i<texty.length();i++)
    {
        QString idAktElementu=texty.at(i).toElement().attribute("id");

        //firstChildElement().nodeValue()
        //  qDebug()<<"nalezeny element "<<idAktElementu<<"nodeValue "<<obsah;
        if (idAktElementu==hledaneId)
        {
            qDebug()<<"menim obsah";
            texty.at(i).firstChild().firstChild().setNodeValue(novaHodnota);
            return 1;
        }
    }
    return 0;
}

QVector<ZastavkaCil> SvgRenderer::vytvorNasledujiciZastavky(QVector<ZastavkaCil> vsechnyZastavky, int index, int limit)
{
    qDebug()<<"SvgVykreslovani::vytvorNasledujiciZastavky";
    QVector<ZastavkaCil> vyslednySeznam;


    for (int i=index; i<vsechnyZastavky.size();i++)
    {
        vyslednySeznam.append(vsechnyZastavky.at(i));
    }


    return vyslednySeznam;
}




QDomDocument SvgRenderer::vymazZastavky(QDomDocument xmlDocument)
{
    qDebug()<<"SvgVykreslovani::vymazZastavky";

    for (int i=0;i<5;i++)
    {
        //this->individualniNahrazeni(xmlDocument,"pasmo"+QString::number(i)," ");
        this->individualniNahrazeni(xmlDocument,"next_stop_"+QString::number(i)," ");
        this->individualniNahrazeni(xmlDocument,"pasmo"+QString::number(i)," ");
    }

    //cil
    this->individualniNahrazeni(xmlDocument,"terminal_station"," ");
    //nacsty
    this->individualniNahrazeni(xmlDocument,"viaStops"," ");
    //linka
    this->individualniNahrazeni(xmlDocument,"line_number"," ");

    return xmlDocument;
}

QDomDocument SvgRenderer::vykresliZastavky(QDomDocument xmlDocument, QVector<ZastavkaCil> nasledujiciZastavky)
{
    qDebug()<<"SvgVykreslovani::vykresliZastavky";

    for (int i=0;i<5;i++)
    {
        if (i<nasledujiciZastavky.count())
        {
            ZastavkaCil aktZastavka=nasledujiciZastavky.at(i);
            this->individualniNahrazeni(xmlDocument,"pasmo"+QString::number(i),pasmaDoStringu(aktZastavka.zastavka.seznamPasem ) );
            qDebug()<<"zobrazuji pasmo "<<pasmaDoStringu(aktZastavka.zastavka.seznamPasem);
            this->individualniNahrazeni(xmlDocument,"next_stop_"+QString::number(i),aktZastavka.zastavka.NameLcd);
        }
        else
        {
            qDebug()<<"index zastavky "<<QString::number(i)<<"je mimo rozsah "<<QString::number(nasledujiciZastavky.count());
        }


    }

    //this->individualniNahrazeni(xmlDocument,"terminal_station",nasledujiciZastavky.at(0).DestinationName);

    return xmlDocument;
}



QDomDocument SvgRenderer::vykresliNacestneZastavky(QDomDocument xmlDocument, QVector<Zastavka> nacestneZastavky)
{
    qDebug()<<"SvgVykreslovani::vykresliNacestneZastavky";
    if (nacestneZastavky.count()==0)
    {
        return xmlDocument;
    }

    QString nacestyString="";
    nacestyString+=nacestneZastavky.at(0).NameLcd;
    for (int i=1;i<nacestneZastavky.count();i++)
    {
        nacestyString+=" – "+nacestneZastavky.at(i).NameLcd;
    }
    qDebug()<<"vypis radku nacestnych zastavek"<<nacestyString;
    this->individualniNahrazeni(xmlDocument,"viaStops",nacestyString);

    //this->individualniNahrazeni(xmlDocument,"terminal_station",nasledujiciZastavky.at(0).DestinationName);

    return xmlDocument;
}

QString SvgRenderer::vykresliNacestneZastavkyText( QVector<Zastavka> nacestneZastavky)
{
    qDebug()<<"SvgVykreslovani::vykresliNacestneZastavkyText";
    if (nacestneZastavky.count()==0)
    {
        return "";
    }

    QString nacestyString="";



    nacestyString+=  nacestneZastavky.at(0).NameLcd;
    for (int i=1;i<nacestneZastavky.count();i++)
    {
        nacestyString+=" – "+nacestneZastavky.at(i).NameLcd;
    }
    qDebug()<<"vypis radku nacestnych zastavek"<<nacestyString;
    return nacestyString;
}

void SvgRenderer::vymazObrazovku()
{
    qDebug()<<"SvgVykreslovani::vymazObrazovku()";



    QString celaCesta=interniCestaSlozkaSvg+"/hlavni.svg";

    QDomDocument xmlko = this->souborDoQDomDocument(celaCesta);
    if (xmlko.isNull())
    {
        qDebug()<<"soubor SVG se nenacetl";
    }
    xmlko=vymazZastavky(xmlko);
    qDomDocumentDoSouboru(interniCestaSlozkaSvg+"/vystup.svg",xmlko);
}






QDomDocument SvgRenderer::vykresliCil(QDomDocument xmlDocument, QVector<ZastavkaCil> globalniZastavky, CestaUdaje stav)
{
    qDebug()<<"SvgVykreslovani::vykresliCil";

    if (stav.indexAktZastavky<globalniZastavky.count())
    {
        this->individualniNahrazeni(xmlDocument,"terminal_station",globalniZastavky.at(stav.indexAktZastavky).cil.NameLcd);
    }
    else
    {
        qDebug()<<"index cile je mimo rozsah";
    }
    return xmlDocument;
}

QDomDocument SvgRenderer::vykresliLinku(QDomDocument xmlDocument, QVector<ZastavkaCil> globalniZastavky, CestaUdaje stav)
{
    qDebug()<<"SvgVykreslovani::vykresliLinku";

    if (stav.indexAktZastavky<globalniZastavky.count())
    {
        this->individualniNahrazeni(xmlDocument,"line_number",globalniZastavky.at(stav.indexAktZastavky).linka.LineName);
    }
    else
    {
        qDebug()<<"index linky je mimo rozsah";
    }
    return xmlDocument;
}

QString SvgRenderer::pasmaDoStringu(QVector<Pasmo> seznamPasem)
{
    qDebug()<<"SvgVykreslovani::pasmaDoStringu";
    QString vysledek;
    if (seznamPasem.size()>0)
    {
        vysledek=seznamPasem.at(0).nazev;
        for (int i=1;i<seznamPasem.size();i++)
        {
            vysledek+=","+seznamPasem.at(i).nazev;
        }
    }
    qDebug()<<"vysledek pasmaDoStringu"<<vysledek;
    return vysledek;
}

int SvgRenderer::aktualizujVse(QVector<ZastavkaCil> zastavky, CestaUdaje stav)
{
    QString celaCesta=interniCestaSlozkaSvg+"/hlavni.svg";
    qDebug()<<"cesta k hlavnimu SVG: "<<celaCesta;
    QDomDocument xmlko = this->souborDoQDomDocument(celaCesta);
    if (xmlko.isNull())
    {
        qDebug()<<"soubor SVG se nenacetl";
    }
    QVector<ZastavkaCil> nasledujiciZastavky=this->vytvorNasledujiciZastavky(zastavky,stav.indexAktZastavky,4);
    xmlko=vymazZastavky(xmlko);
    xmlko=vykresliZastavky(xmlko,nasledujiciZastavky);
    xmlko=vykresliCil(xmlko,zastavky,stav);
    xmlko=vykresliLinku(xmlko,zastavky,stav);
    xmlko=vykresliNacestneZastavky(xmlko,zastavky.at(stav.indexAktZastavky).nacestneZastavky);
    //xmlko=vykresliNacestneZastavky(xmlko,vytvorNacestneZastavky(zastavky,stav.indexAktZastavky));

    qDomDocumentDoSouboru(interniCestaSlozkaSvg+"/vystup.svg",xmlko);
    return 1;
}

void SvgRenderer::zobrazZmenuPasma(QVector<Pasmo> zPasem, QVector<Pasmo> naPasma)
{
    qDebug()<<"SvgVykreslovani::zobrazZmenuPasma";
}


void SvgRenderer::obarviPozadiPristi(QString barvaPisma,QString barvaPozadi)
{
    qDebug()<<"SvgVykreslovani::obarviPozadiPristi";

}


void SvgRenderer::zobrazAnnoucement(QString title,QString type,QString textCz, QString textEn)
{
    qDebug()<<"SvgVykreslovani::hlavniZobrazAnnoucement";


}
