#ifndef SVGRENDERER_H
#define SVGRENDERER_H
#include <QWidget>
#include <QDomDocument>
#include <VDV301struktury/zastavka.h>
#include <VDV301struktury/zastavkacil.h>
#include "VDV301struktury/cestaudaje.h"

class SvgRenderer
{
public:
    SvgRenderer(QString cesta);
    QString interniCestaSlozkaSvg="";
    bool svgReplaceName(QString souborVstup, QString souborVystup, QString cil, QString zst0, QString zst1, QString zst2);
    bool individualniNahrazeni(QDomDocument &xmlDocument, QString hledaneId, QString novaHodnota);
    QVector<ZastavkaCil> vytvorNasledujiciZastavky(QVector<ZastavkaCil> vsechnyZastavky, int index, int limit);
    QDomDocument vymazZastavky(QDomDocument xmlDocument);
    QDomDocument vykresliZastavky(QDomDocument xmlDocument, QVector<ZastavkaCil> nasledujiciZastavky);
    int aktualizujVse(QVector<ZastavkaCil> zastavky, CestaUdaje stav);
    int qDomDocumentDoSouboru(QString cestaVystupnihoSouboru, QDomDocument vstupniDom);
   // QVector<ZastavkaCil> vytvorNacestneZastavky(QVector<ZastavkaCil> vsechnyZastavky, int index);
    static QString pasmaDoStringu(QVector<Pasmo> seznamPasem);


    QString vykresliNacestneZastavkyText(QVector<Zastavka> nacestneZastavky);
    void zobrazZmenuPasma(QVector<Pasmo> zPasem, QVector<Pasmo> naPasma);
    void obarviPozadiPristi(QString barvaPisma, QString barvaPozadi);
    void vymazObrazovku();
    void zobrazAnnoucement(QString title, QString type, QString textCz, QString textEn);
private:

    QDomDocument souborDoQDomDocument(QString cesta);
    QDomDocument vykresliCil(QDomDocument xmlDocument, QVector<ZastavkaCil> globalniZastavky, CestaUdaje stav);
    QDomDocument vykresliLinku(QDomDocument xmlDocument, QVector<ZastavkaCil> globalniZastavky, CestaUdaje stav);
    QDomDocument vykresliNacestneZastavky(QDomDocument xmlDocument, QVector<Zastavka> nacestneZastavky);

};

#endif // SVGRENDERER_H
