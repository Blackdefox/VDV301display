#ifndef XMLPARSER_H
#define XMLPARSER_H
#define MAX_ZAST2 10

#include <QMainWindow>
#include <QObject>
#include <QtXml>
#include "VDV301struktury/zastavka.h"
#include "VDV301struktury/zastavkacil.h"
#include "VDV301struktury/cestaudaje.h"
#include "VDV301struktury/prestup.h"
class XmlParser
{
public:
    XmlParser();
    // void nactiXML(QByteArray vstup);
    int linka=0;
    QString cil="";

    QMap<int,ZastavkaCil> globalniSeznamZastavek2_4;

    // SeznamZastavek docasnySeznamZastavek[] ;
    //SeznamZastavek* docasnySeznamZastavek = new SeznamZastavek[MAX_ZAST2];

    QDomDocument dokument;
    void Test();

    void nactiXML(QString vstup);

    int nactiVehicleGroup(CestaUdaje &stav, QDomDocument xmlko);
    int VytvorSeznamZastavek2_2CZ1_0(QVector<ZastavkaCil> &docasnySeznamZst, QVector<ZastavkaCil> &docasnySeznamZstNavazny, int &docasnyIndexZastavky, int &docasnyPocetZastavek);
    int nactiFareZoneChange(QDomDocument xmlko, QVector<Pasmo> &pasmaZ, QVector<Pasmo> &pasmaNa);
    int nactiAdditionalTextMessage(QDomDocument xmlko, QString &type, QString &headline, QString &text);
    int vyparsujPasmaZeSeznamu(QDomElement vstup, QVector<Pasmo> &pasma);
    QVector<QString> naplnVektorPriznaku(QDomNode vstup, QString nazevElementu);
    int tripDoSeznamuZastavek2_2CZ1_0(QVector<ZastavkaCil> &docasnySeznamZst, QDomElement vstup, int &docasnyPocetZastavek);
    int udajeNavaznehoSpoje(QVector<ZastavkaCil> &docasnySeznamZst, QString &linka, QString &cil);
    int existujeNavaznySpoj(QVector<ZastavkaCil> seznamZastavek);
    QVector<Prestup> nactiPrestupy(QDomElement vstup);
    Line priznakyDoLinky(QVector<QString> vstup, Line vstupniLinka);

    QDateTime vyparsujTimestamp(QDomDocument vstupniDokument);

    bool zmenaDat=false;
    static int minutDoOdjezdu(QDateTime aktCas, QDateTime casOdjezdu);

    //rozdelano
    int VytvorSeznamZastavek1_0(QVector<ZastavkaCil> &docasnySeznamZst, QVector<ZastavkaCil> &docasnySeznamZstNavazny, int &docasnyIndexZastavky, int &docasnyPocetZastavek);
    int tripDoSeznamuZastavek1_0(QVector<ZastavkaCil> &docasnySeznamZst, QDomElement vstup, int &docasnyPocetZastavek);
    QVector<Zastavka> vyparsujNacestneZastavky1_0(QDomElement zastavka);
    QVector<Pasmo> vyparsujPasma_1_0(QDomElement zastavka);

    int tripDoSeznamuZastavek2_4(QVector<ZastavkaCil> &docasnySeznamZst, QDomElement vstup, int &docasnyPocetZastavek);
    int VytvorSeznamZastavek2_4(QVector<ZastavkaCil> &docasnySeznamZst, QVector<ZastavkaCil> &docasnySeznamZstNavazny, int &docasnyIndexZastavky, int &docasnyPocetZastavek);

private:
    QVector<Zastavka> vyparsujNacestneZastavky2_2CZ1_0(QDomElement zastavka);
    QVector<Zastavka> vyparsujNacestneZastavky2_4(QDomNode displayContent);
    QVector<Pasmo> vyparsujPasma_2_2CZ1_0(QDomElement zastavka);
    QString stareXml="";
};




#endif // XMLPARSER_H
