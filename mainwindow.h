#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "xmlparser.h"
//#include "httpserver2/myhttpserver.h"
//#include "VDV301subscriber/ibisipsubscriber.h"

#include "VDV301publisher/devicemanagementservice.h"
#include "VDV301subscriber/cissubscriber.h"
#include "VDV301struktury/cestaudaje.h"
#include "VDV301struktury/zastavkacil.h"
#include "VDV301struktury/prestup.h"
#include "pasmovedvojicelcd.h"
#include "svgrenderer.h"
#include "labelvykreslovani.h"
#include "barvylinek.h"


#include <QApplication>
#include <QCoreApplication>
//#include <QtDebug>
#include <QFile>
#include <QFontDatabase>
#include <QLabel>
#include <QMainWindow>
#include <QMessageBox>
#include <QSettings>
#include <QShortcut>
#include <QTableWidget>
#include <QTextStream>
#include <QUrl>


//#include <QWidget>

#include <QGraphicsSvgItem>
#include <QGraphicsScene>
#include <QSvgRenderer>
#include <QSvgWidget>

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>

class QByteArray;
class QNetworkAccessManager;
class QNetworkReply;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QString cestaKonfiguraku, QWidget *parent = nullptr);
    Ui::MainWindow *ui;
    ~MainWindow();




private:

    QCommandLineParser qCommandLineParser;

    //instance trid
    XmlParser instanceXMLparser;
    CestaUdaje stavSystemu;
    LabelVykreslovani labelVykreslovani;

    CisSubscriber cisSubscriber;
    SvgRenderer svgVykreslovani;
    DeviceManagementService deviceManagementService1_0;
    QSettings settings;


    //datoveStruktury jizda
    QVector<ZastavkaCil> globalniSeznamZastavek;
    QVector<ZastavkaCil> globalniSeznamZastavekNavaznehoSpoje;


    //QVector<Prestup> prestupy;
    QString nazevLinky="";
    QString nazevCile="";
    QString additionalTextMessageType="";
    QString additionalTextMessageHeadline="";
    QString additionalTextMessageText="";
    QVector<Pasmo> pasmaZ;
    QVector<Pasmo> pasmaDo;

    BarvyLinek barvyLinek;

    //stavove promenne
    bool zmenaPasma=false;
    int indexZastavky=0;
    int pocetZastavek=0;
    int cyklovaniIndex=0;
    int indexAktualniStridaneStranky =0;
    bool zobrazDvojtecku=0;

    //konstanty
    int posunRotovani=0;
    int pocetVykreslovanychZastavek=5;



    const int intervalBocniPanel=2000;
    const int intervalPosunuNacest=20;
    const int intervalStridaniStranek=10000;
    const int intervalOpozdeniStartu=500;

    //velikosti fontu v bodech
    //const int velikostFontLinka=200;
    const int velikostFontCil=100;
    const int velikostFontNacestne=72;
    const int velikostFontNasledujici=100;

    const int velikostFontPrestupLinka=48;
    const int velikostFontPrestupCil=36;

    const int velikostPiktogramPrestup=65;
    int velikostPiktogramPrestupDynamic=20;
    const int velikostPrestupRamecekSirka=95;
    const int velikostPrestupRamecekVyska=65;

    //velikosti oken

    float pomerPixelBod=1080.0/1050.0;

    float pomerPixelLed=4.105;


    //ostatni promenne


    //Fonty

    QFontDatabase fdb;

    //_LED fonty
    QFont font1;
    QFont font3;
    QFont font5;
    QFont font8;
    QFont font10;


    //_LCD fonty

    QFont fontPasmoVelke;
    QFont fontPasmoMale;

    //casovace
    QTimer *timerBocniPanel = new QTimer(this);
    QTimer *timerNacestneZastavky = new QTimer(this);
    QTimer *timer = new QTimer(this);
    QTimer *timerStridejStranky = new QTimer(this);
    QTimer *timerOpozdenyStart = new QTimer(this);

    //funkce spolecne (vsem typum zobrazeni)
    int doplneniPromennych ();
    void prepniObrazovku(int vstup);
    int formatZobrazeni();

    QString textVerze();
    int vykresleniPrijatychDat();
    void vymazTabulku(QTableWidget *tableWidget);
    void vykresliSluzbyDoTabulky(QVector<QZeroConfService> seznamSluzeb);
    void vsechnyConnecty();


    //funkce pomocne

    int jeVRozsahu(int index, int pocetHodnot); //nepouzito

    //funkce hlavni
    void hlavniAutoformat();
    void hlavniNaplnPoleLabelu();
    void hlavniVykresliCisloLinky(ZastavkaCil aktZastavka, QString subMode);
    void hlavniVykresliNacestne();
    void hlavniVykresliNazevCile(QString alias);
    void hlavniVykresliPrestupy(QVector<Prestup> seznamPrestupu);
    void hlavniVykresliSkupinuZastavekNew(QVector<ZastavkaCil> zastavky, QVector<ZastavkaCil> zastavkyNavazny, int index);
    void hlavniVykresliZastavkyiPasma(QVector<ZastavkaCil> aktZastavky, QVector<ZastavkaCil> navazZastavky);
    void hlavniVymazObrazovku();
    void hlavniZobrazAnnoucement(QString title, QString type, QString textCz, QString textEn);
    void hlavniZobrazZmenuPasma(QVector<Pasmo> zPasem, QVector<Pasmo> naPasma);
    void naplnPoleLinky(QString subMode, Line line, QLabel *label, int velikostPiktogramu, bool prestup);
    void naplnPoleLinky2_4(QString subMode, Line line, QLabel *label, int velikostPiktogramu, bool prestup);

    QVector<QWidget*> strankyKeStridani;

    //funkce led
    void ledAktualizujZobrazeniVirtualnichPanelu(QVector<ZastavkaCil> zastavky, CestaUdaje stav);
    void ledNaplnFront(QString linka, QString horniRadek, QString dolniRadek);
    void ledNaplnInner(QString linka, QString horniRadek, QString dolniRadek);
    QVector<QString> ledNaplnNacestyBocniPanel(ZastavkaCil aktualniZastavka);
    QVector<QString> ledNaplnNacestyVnitrniPanel(ZastavkaCil aktualniZastavka);
    void ledInicializujVirtualniPanely();
    void ledIterujBocniPanel(QVector<QString> texty, int &iteracniIndex);
    void ledIterujVnitrniPanel(QVector<QString> texty, int &iteracniIndex);
    void ledIterujVsechnyPanely();
    void ledNaplnSide(QString linka, QString horniRadek, QString dolniRadek);
    void ledNaplnRear(QString linka);
    void ledVymazPanely();

    void ledZmenVelikostPanelu();
    void ledZarovnejPretecenyRadek(QLabel *label);
    void ledZapisLinku(QLabel *label, QString text);
    void ledZmenVelikostOkna(QLabel *okno, int sirkaDot, int vyskaDot, float koeficient);



    void slotPublisherDoTabulky(QZeroConfService zcs);

    QVector<QString> textyBocniPanelkIteraci;
    QVector<QString> textyVnitrniPanelkIteraci;

    //funkce SVG
    bool svgOpenFile(const QString &fileName);

    //obecne Udalosti
    int jeVozidloNaKonecne(CestaUdaje stav, QVector<ZastavkaCil> zastavky);
    void navratJizda();
    void natahniKonstanty();
    void obarviPozadiPristi(QString barvaPisma, QString barvaPozadi);

    void skryjAnnouncement(); //nepouzito
    void skryjZmenuPasma(); //nepouzito

    void vyprselCasovacSluzby();
    void vymazObrazovku();

    void zobrazAnnoucement(QString title, QString type, QString textCz, QString textEn);
    void zobrazZmenuPasma(QVector<Pasmo> zPasem, QVector<Pasmo> naPasma);
    void zobrazKonecnou();

    //klávesové zkratky
    QShortcut *keyCtrlF;  // Entity of Ctrl + D hotkeys
    QShortcut  *keyF1;
    QShortcut  *keyF2;
    QShortcut  *keyF3;
    QShortcut  *keyF4;
    QShortcut  *keyF5;
    QShortcut  *keyF6;
    QShortcut  *keyF7;
    QShortcut  *keyF8;

    //polozky potrebne pro vykresleni svg
    QGraphicsScene scene;
    QGraphicsSvgItem *m_svgItem;
    QGraphicsRectItem *m_outlineItem;
    bool svgVykresleni();

    //vektory Labelu Hlavni
    QVector<QLabel*> seznamLabelNazevZastavky;
    QVector<QLabel*> seznamLabelPasmoDolni;
    QVector<QLabel*> seznamLabelPasmoHorni;

    QVector<QLabel*> seznamLabelPrestupLinka;
    QVector<QLabel*> seznamLabelPrestupCil;
    QVector<QLabel*> seznamLabelPrestupOdjezd;
    QVector<QLabel*> seznamLabelPrestupNastupiste;


    void vyskakovaciOkno(QString poznamka);


    QString nahradIconPiktogramem(QString vstup, int vyskaObrazku, QString slozka);
    void zastavkaCilDoTabulky(ZastavkaCil zastavkaCil, bool navazny);
    void vsechnyZastavkyDoTabulky(QVector<ZastavkaCil> seznamZastavek, bool navazny);
    void inicializaceFontu();
    void inicializaceKlavesovychZkratek();
    void jednaZastavkaCilDoLabelu(ZastavkaCil aktualniZastavka, bool navazny, QLabel *nazevZastavky, QLabel *dolniPasmo, QLabel *horniPasmo);
    QVector<ZastavkaCil> vektorZastavkaCilZahoditZacatek(QVector<ZastavkaCil> vstup, int zacatek);

private slots:

    void on_actiontestPolozka_triggered();
    //tlacitka
    void on_pushButton_menu_refreh_clicked();
    void on_pushButton_menu_sluzby_clicked();
    void on_pushButton_menu_hlavni_clicked();
    void on_pushButton_menu_casovac_clicked();
    void on_pushButton_menu_quit_clicked();
    void on_pushButton_menu_svg_clicked();
    void on_pushButton_menu_led_clicked();
    void on_pushButton_menu_fullscreen_clicked();

    //sloty
    int slotKazdouVterinu();
    void slotPosunNacestnych();
    void slotHlavniStridejStranky();
    void slotToggleFullscreen();
    void slotXmlDoPromenne(QString vstupniXml);
    void slotSluzbaDoTabulky(QZeroConfService zcs);
    void slotOpozdenyStart();
    void slotAktualizaceTabulkySluzeb();
    void slotZtrataOdberu();


public slots:

    void slotParametryZarizeniDoConfigu();
};

#endif // MAINWINDOW_H
