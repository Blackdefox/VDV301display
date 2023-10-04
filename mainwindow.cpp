#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QString cestaKonfiguraku, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    cisSubscriber("CustomerInformationService","AllData","2.2CZ1.0","_ibisip_http._tcp",48479),//puvodni port 48479, novy 59631
    svgVykreslovani(QCoreApplication::applicationDirPath()),
    deviceManagementService1_0("DeviceManagementService","_ibisip_http._tcp",49477,"1.0"), //49477
    settings(cestaKonfiguraku, QSettings::IniFormat)
{

    ui->setupUi(this);

    /*
   * oprava záseků při špatně nastavené IP adrese po HTTP POST
   * https://bugreports.qt.io/browse/QTBUG-10106
   */
    QNetworkProxyFactory::setUseSystemConfiguration(false);

    /*

    qCommandLineParser.addOption(QCommandLineOption("config", "Input file path", "file"));
    qCommandLineParser.process(arguments);

    QString inputFilePath =  qCommandLineParser.value("config");



    if(!qCommandLineParser.value("config").isEmpty())
    {
        QUrl cesta=QUrl::fromLocalFile(qCommandLineParser.value("config"));
        settings.setPath(QSettings::IniFormat,QSettings::UserScope,"nastaveni2.ini");
      //  settings.setPath(QSettings::IniFormat,QSettings::SystemScope,"nastaveni2.ini");
        qDebug()<<"XX parametr startu input: "<<cesta.toString()<<settings.value("deviceManagementService1_0/deviceName");
    }
    else
    {
     //   settings.setPath(QSettings::IniFormat,QSettings::SystemScope,QCoreApplication::applicationDirPath()+"/nastaveni.ini");
        settings.setPath(QSettings::IniFormat,QSettings::UserScope,QCoreApplication::applicationDirPath()+"/nastaveni.ini");

    }


*/


    labelVykreslovani.slozkaPiktogramu=QCoreApplication::applicationDirPath()+"/icons";

    inicializaceFontu();

    inicializaceKlavesovychZkratek();

    natahniKonstanty();

    vsechnyConnecty();

    ui->prepinadloStran->setCurrentWidget(ui->page_hlavniObrazovka);
    ui->stackedWidget_prostredek->setCurrentWidget(ui->page_hlavni_2);
    hlavniNaplnPoleLabelu(); //naplni pointery na labely do pole, aby se nimi dalo iterovat


    formatZobrazeni();
    hlavniAutoformat();


    cisSubscriber.odebirano=false ;

    cisSubscriber.start();

    cisSubscriber.novePrihlaseniOdberu();



    this->ledInicializujVirtualniPanely();


    bool dvaradky=true;
    if(dvaradky==true)
    {
        ui->labelFrontSingle->setVisible(false);
        ui->labelFrontBottomRow->setVisible(true);
        ui->labelFrontTopRow->setVisible(true);
    }
    else
    {
        ui->labelFrontSingle->setVisible(true);
        ui->labelFrontBottomRow->setVisible(false);
        ui->labelFrontTopRow->setVisible(false);
    }
    /*
    auto    sw1 = new QSvgWidget(QString("vystupanim.svg"), this);
    ui->verticalLayout_3->addWidget(sw1);
    sw1->setGeometry(50, 50, rect().width(), rect().height());
    */

    ui->label_build->setText(textVerze());
    ui->label_build->setTextInteractionFlags(Qt::TextSelectableByMouse);

    //


    timer->start(1000); //refresh vterin
    timerBocniPanel->start(intervalBocniPanel);

    timerStridejStranky->setInterval(intervalStridaniStranek);
    timerOpozdenyStart->setInterval(intervalOpozdeniStartu);
    timerOpozdenyStart->setSingleShot(true);

    vymazObrazovku();
    timerOpozdenyStart->start();

    QStringList seznamParametru = qCommandLineParser.optionNames();




}

void MainWindow::inicializaceFontu()
{

    fdb.addApplicationFont(":/fonts/fonty/21-pid-1.ttf");
    fdb.addApplicationFont(":/fonts/fonty/21-pid-3.ttf");
    fdb.addApplicationFont(":/fonts/fonty/21-pid-5.ttf");
    fdb.addApplicationFont(":/fonts/fonty/21-pid-8.ttf");
    fdb.addApplicationFont(":/fonts/fonty/21-pid-10.ttf");
    fdb.addApplicationFont(":/fonts/fonty/pid-3v.ttf");

    fdb.addApplicationFont(":/fonts/fonty/Roboto-Regular.ttf");
    fdb.addApplicationFont(":/fonts/fonty/Roboto-Bold.ttf");
    fdb.addApplicationFont(":/fonts/fonty/Roboto-Black.ttf");
    fdb.addApplicationFont(":/fonts/fonty/Roboto-Light.ttf");


    font1.setFamily("21-PID 1");
    font1.setPointSize(65);

    font3.setFamily("21-PID 3");
    font3.setPointSize(65);

    font5.setFamily("21-PID 5");
    font5.setPointSize(65);

    font8.setFamily("21-PID 8");
    font8.setPointSize(65);

    font10.setFamily("21-PID 10");
    font10.setPointSize(65);

    //LCD fonty
    fontPasmoVelke.setPointSize(36);
    fontPasmoVelke.setFamily("Roboto");
    fontPasmoVelke.setBold(true);

    fontPasmoMale.setPointSize(20);
    fontPasmoMale.setFamily("Roboto");
    fontPasmoMale.setBold(true);

}

void MainWindow::inicializaceKlavesovychZkratek()
{
    //klávesové zkratky menu
    keyCtrlF = new QShortcut(this); // Initialize the object Zdroj: https://evileg.com/en/post/75/
    keyCtrlF->setKey(Qt::CTRL | Qt::Key_F); // Set the key code

    keyF1 = new QShortcut(this);
    keyF1->setKey(Qt::Key_F1);

    keyF2 = new QShortcut(this);
    keyF2->setKey(Qt::Key_F2);

    keyF3 = new QShortcut(this);
    keyF3->setKey(Qt::Key_F3);

    keyF4 = new QShortcut(this);
    keyF4->setKey(Qt::Key_F4);

    keyF5 = new QShortcut(this);
    keyF5->setKey(Qt::Key_F5);

    keyF6 = new QShortcut(this);
    keyF6->setKey(Qt::Key_F6);

    keyF7 = new QShortcut(this);
    keyF7->setKey(Qt::Key_F7);

    keyF8 = new QShortcut(this);
    keyF8->setKey(Qt::Key_F8);

}

void MainWindow::natahniKonstanty()
{
    deviceManagementService1_0.setDeviceName(settings.value("deviceManagementService1_0/deviceName").toString());
    deviceManagementService1_0.setDeviceManufacturer(settings.value("deviceManagementService1_0/deviceManufacturer").toString());
    deviceManagementService1_0.setDeviceSerialNumber(settings.value("deviceManagementService1_0/deviceSerialNumber").toString());
    deviceManagementService1_0.setDeviceClass(settings.value("deviceManagementService1_0/deviceClass").toString());
    deviceManagementService1_0.setDeviceId(settings.value("deviceManagementService1_0/deviceId").toString());
    deviceManagementService1_0.setSwVersion(textVerze());
    deviceManagementService1_0.setCisloPortu(settings.value("deviceManagementService1_0/port").toInt() ); //47477


    deviceManagementService1_0.slotAktualizaceDat();
    deviceManagementService1_0.slotStartServer();

    QString verzeVdv301=settings.value("cisSubscriber/verze").toString();
    QStringList podporovaneVerze;
    podporovaneVerze<<"1.0";
    podporovaneVerze<<"2.2CZ1.0";
    podporovaneVerze<<"2.4";

    if(podporovaneVerze.contains(verzeVdv301))
    {
        cisSubscriber.setVersion(verzeVdv301);
    }
    else
    {
        vyskakovaciOkno("verze "+verzeVdv301+" neni podporována!");
    }
    cisSubscriber.setPortNumber(settings.value("cisSubscriber/port").toUInt());

    prepniObrazovku(settings.value("konstanty/defaultniObrazovka").toInt());
    if(settings.value("konstanty/fullscreen").toBool()==true)
    {
        slotToggleFullscreen();
    }

}

void MainWindow::slotOpozdenyStart()
{
    qDebug() <<  Q_FUNC_INFO;
    //  CustomerInformationServiceSubscriber.hledejSluzby("_ibisip_http._tcp.",0);
    //  CustomerInformationServiceSubscriber.hledejSluzby("_ibisip_http._tcp.",1);
    //cisSubscriber.novePrihlaseniOdberu();
}

void MainWindow::prepniObrazovku(int vstup)
{
    qDebug() <<  Q_FUNC_INFO<<" "<<vstup;

    switch(vstup)
    {
    case 0:

        break;

    case 1:
        on_pushButton_menu_hlavni_clicked();
        break;

    case 2:
        on_pushButton_menu_svg_clicked();
        break;
    case 3:
        on_pushButton_menu_led_clicked();

        break;
    case 4:
        on_pushButton_menu_sluzby_clicked();
        break;
    }
}



void MainWindow::vsechnyConnecty()
{
    qDebug() <<  Q_FUNC_INFO;
    connect(&cisSubscriber, &IbisIpSubscriber::dataNahrana  ,this, &MainWindow::slotXmlDoPromenne);
    connect(&cisSubscriber,&IbisIpSubscriber::signalUpdateList,this,&MainWindow::slotAktualizaceTabulkySluzeb);
    connect(cisSubscriber.timer,&QTimer::timeout ,this,&MainWindow::vyprselCasovacSluzby);
    connect(&cisSubscriber,&IbisIpSubscriber::signalZtrataOdberu ,this,&MainWindow::slotZtrataOdberu);
    connect(&cisSubscriber,&IbisIpSubscriberOnePublisher::signalUspesnySubscribe,this,&MainWindow::slotPublisherDoTabulky);


    connect(&deviceManagementService1_0,&DeviceManagementService::signalZmenaParametruVen,this,&MainWindow::slotParametryZarizeniDoConfigu);


    connect(timer, &QTimer::timeout, this, &MainWindow::slotKazdouVterinu);

    connect(timerBocniPanel, &QTimer::timeout, this, &MainWindow::ledIterujVsechnyPanely);
    connect(timerNacestneZastavky, &QTimer::timeout, this, &MainWindow::slotPosunNacestnych);
    connect(timerStridejStranky, &QTimer::timeout, this, &MainWindow::slotHlavniStridejStranky);
    connect(timerOpozdenyStart, &QTimer::timeout, this, &MainWindow::slotOpozdenyStart);




    //klávesové zkratky
    // connect(keyCtrlF, SIGNAL(activated()), this, SLOT(toggleFullscreen()));
    connect(keyCtrlF, &QShortcut::activated, this, &MainWindow::slotToggleFullscreen);
    connect(keyF1, &QShortcut::activated, this,&MainWindow::on_pushButton_menu_hlavni_clicked );
    connect(keyF2, &QShortcut::activated, this,&MainWindow::on_pushButton_menu_svg_clicked );
    connect(keyF3, &QShortcut::activated, this, &MainWindow::on_pushButton_menu_led_clicked);
    connect(keyF4, &QShortcut::activated, this, &MainWindow::on_pushButton_menu_sluzby_clicked);
    connect(keyF5, &QShortcut::activated, this, &MainWindow::on_pushButton_menu_casovac_clicked );
    connect(keyF6, &QShortcut::activated, this, &MainWindow::slotToggleFullscreen);
    connect(keyF7, &QShortcut::activated, this, &MainWindow::on_pushButton_menu_refreh_clicked);
    connect(keyF8, &QShortcut::activated, this, &MainWindow::on_pushButton_menu_quit_clicked);
}


QString MainWindow::textVerze()
{
    QDate datumKompilace=QLocale("en_US").toDate(QString(__DATE__).simplified(), "MMM d yyyy");
    QTime casKompilace=QTime::fromString(__TIME__,"hh:mm:ss");
    qDebug()<<" date:"<<datumKompilace<<" time:"<<casKompilace;
    QString verze=datumKompilace.toString("yyyyMMdd")+"_"+casKompilace.toString("hhmm");
    return verze;
}


int MainWindow::slotKazdouVterinu()
{

    ui->labelZbyvajiciVteriny->setText(QString::number(cisSubscriber.timer->remainingTime()/1000) );
    ui->label_odebirano->setText(QString::number(cisSubscriber.odebirano));

    if(zobrazDvojtecku==true)
    {
        ui->label_hodiny->setText(QTime::currentTime().toString("hh:mm") );
        zobrazDvojtecku=false;
    }
    else
    {
        ui->label_hodiny->setText(QTime::currentTime().toString("hh mm") );
        zobrazDvojtecku=true;
    }

    return 1;
}

void MainWindow::slotZtrataOdberu()
{
    qDebug() <<  Q_FUNC_INFO;
    vymazTabulku(ui->tableWidget_odebirano);
    vymazObrazovku();
}

void MainWindow::slotPosunNacestnych()
{
    int delkaTextu=ui->label_nacestne->width();
    int krok=1;

    if(delkaTextu<ui->scrollArea->width() )
    {
        return;
    }
    // qDebug()<<"delka beziciho textu "<< delkaTextu << " posun rotovani: "<<posunRotovani;

    posunRotovani-=krok;

    if (abs(posunRotovani)>delkaTextu)
    {
        posunRotovani=0;
        labelVykreslovani.vykresliNacestneForce(globalniSeznamZastavek,stavSystemu,ui->label_nacestne,cisSubscriber.version());
    }

    else

    {
        ui->scrollAreaWidgetContents->scroll(-krok,0);
    }

}

void MainWindow::slotAktualizaceTabulkySluzeb()
{
    qDebug() <<  Q_FUNC_INFO;
    vykresliSluzbyDoTabulky(cisSubscriber.listOfServices);
}

void MainWindow::vyprselCasovacSluzby()
{
    qDebug() <<  Q_FUNC_INFO;

}



void MainWindow::hlavniNaplnPoleLabelu()
{
    qDebug() <<  Q_FUNC_INFO;
    seznamLabelNazevZastavky.push_back(ui->Lnacestna1);
    seznamLabelNazevZastavky.push_back(ui->Lnacestna2);
    seznamLabelNazevZastavky.push_back(ui->Lnacestna3);
    seznamLabelNazevZastavky.push_back(ui->Lnacestna4);
    seznamLabelNazevZastavky.push_back(ui->Lnacestna5);

    seznamLabelPasmoDolni.push_back(ui->label_pasmo1_1);
    seznamLabelPasmoDolni.push_back(ui->label_pasmo2_1);
    seznamLabelPasmoDolni.push_back(ui->label_pasmo3_1);
    seznamLabelPasmoDolni.push_back(ui->label_pasmo4_1);
    seznamLabelPasmoDolni.push_back(ui->label_pasmo5_1);

    seznamLabelPasmoHorni.push_back(ui->label_pasmo1_2);
    seznamLabelPasmoHorni.push_back(ui->label_pasmo2_2);
    seznamLabelPasmoHorni.push_back(ui->label_pasmo3_2);
    seznamLabelPasmoHorni.push_back(ui->label_pasmo4_2);
    seznamLabelPasmoHorni.push_back(ui->label_pasmo5_2);


    seznamLabelPrestupCil .push_back(ui->label_prestup0_cil);
    seznamLabelPrestupCil.push_back(ui->label_prestup1_cil);
    seznamLabelPrestupCil.push_back(ui->label_prestup2_cil);
    seznamLabelPrestupCil.push_back(ui->label_prestup3_cil);
    seznamLabelPrestupCil.push_back(ui->label_prestup4_cil);
    seznamLabelPrestupCil.push_back(ui->label_prestup5_cil);
    seznamLabelPrestupCil.push_back(ui->label_prestup6_cil);
    seznamLabelPrestupCil.push_back(ui->label_prestup7_cil);
    seznamLabelPrestupCil.push_back(ui->label_prestup8_cil);
    seznamLabelPrestupCil.push_back(ui->label_prestup9_cil);
    seznamLabelPrestupCil.push_back(ui->label_prestup10_cil);
    seznamLabelPrestupCil.push_back(ui->label_prestup11_cil);

    seznamLabelPrestupLinka.push_back(ui->label_prestup0_linka);
    seznamLabelPrestupLinka.push_back(ui->label_prestup1_linka);
    seznamLabelPrestupLinka.push_back(ui->label_prestup2_linka);
    seznamLabelPrestupLinka.push_back(ui->label_prestup3_linka);
    seznamLabelPrestupLinka.push_back(ui->label_prestup4_linka);
    seznamLabelPrestupLinka.push_back(ui->label_prestup5_linka);
    seznamLabelPrestupLinka.push_back(ui->label_prestup6_linka);
    seznamLabelPrestupLinka.push_back(ui->label_prestup7_linka);
    seznamLabelPrestupLinka.push_back(ui->label_prestup8_linka);
    seznamLabelPrestupLinka.push_back(ui->label_prestup9_linka);
    seznamLabelPrestupLinka.push_back(ui->label_prestup10_linka);
    seznamLabelPrestupLinka.push_back(ui->label_prestup11_linka);

    seznamLabelPrestupOdjezd.push_back(ui->label_prestup0_odjezd);
    seznamLabelPrestupOdjezd.push_back(ui->label_prestup1_odjezd);
    seznamLabelPrestupOdjezd.push_back(ui->label_prestup2_odjezd);
    seznamLabelPrestupOdjezd.push_back(ui->label_prestup3_odjezd);
    seznamLabelPrestupOdjezd.push_back(ui->label_prestup4_odjezd);
    seznamLabelPrestupOdjezd.push_back(ui->label_prestup5_odjezd);
    seznamLabelPrestupOdjezd.push_back(ui->label_prestup6_odjezd);
    seznamLabelPrestupOdjezd.push_back(ui->label_prestup7_odjezd);
    seznamLabelPrestupOdjezd.push_back(ui->label_prestup8_odjezd);
    seznamLabelPrestupOdjezd.push_back(ui->label_prestup9_odjezd);
    seznamLabelPrestupOdjezd.push_back(ui->label_prestup10_odjezd);
    seznamLabelPrestupOdjezd.push_back(ui->label_prestup11_odjezd);

    seznamLabelPrestupNastupiste.push_back(ui->label_prestup0_nastupiste);
    seznamLabelPrestupNastupiste.push_back(ui->label_prestup1_nastupiste);
    seznamLabelPrestupNastupiste.push_back(ui->label_prestup2_nastupiste);
    seznamLabelPrestupNastupiste.push_back(ui->label_prestup3_nastupiste);
    seznamLabelPrestupNastupiste.push_back(ui->label_prestup4_nastupiste);
    seznamLabelPrestupNastupiste.push_back(ui->label_prestup5_nastupiste);
    seznamLabelPrestupNastupiste.push_back(ui->label_prestup6_nastupiste);
    seznamLabelPrestupNastupiste.push_back(ui->label_prestup7_nastupiste);
    seznamLabelPrestupNastupiste.push_back(ui->label_prestup8_nastupiste);
    seznamLabelPrestupNastupiste.push_back(ui->label_prestup9_nastupiste);
    seznamLabelPrestupNastupiste.push_back(ui->label_prestup10_nastupiste);
    seznamLabelPrestupNastupiste.push_back(ui->label_prestup11_nastupiste);

    /*
    seznamFramePrestup.push_back(ui->frame_odjezd0);
    seznamFramePrestup.push_back(ui->frame_odjezd1);
    seznamFramePrestup.push_back(ui->frame_odjezd2);
    seznamFramePrestup.push_back(ui->frame_odjezd3);
    seznamFramePrestup.push_back(ui->frame_odjezd4);
    seznamFramePrestup.push_back(ui->frame_odjezd5);
    seznamFramePrestup.push_back(ui->frame_odjezd6);
    seznamFramePrestup.push_back(ui->frame_odjezd7);
    seznamFramePrestup.push_back(ui->frame_odjezd8);
    seznamFramePrestup.push_back(ui->frame_odjezd9);
    seznamFramePrestup.push_back(ui->frame_odjezd10);
    seznamFramePrestup.push_back(ui->frame_odjezd11);
    */
}






void MainWindow::vymazObrazovku()
{
    qDebug() <<  Q_FUNC_INFO;
    hlavniVymazObrazovku();
    svgVykreslovani.vymazObrazovku();
    ledVymazPanely();


}


void MainWindow::hlavniVymazObrazovku()
{
    qDebug() <<  Q_FUNC_INFO;
    ui->Lcil->setText("");
    ui->label_linka->setText("");
    ui->label_nacestne->setText("");

    ui->frame_navaznySpoj->hide();

    labelVykreslovani.vymazPoleLabelu(seznamLabelNazevZastavky);
    labelVykreslovani.vymazPoleLabelu(seznamLabelPasmoDolni);
    labelVykreslovani.vymazPoleLabelu(seznamLabelPasmoHorni);
    //obrazovka prestupu
    labelVykreslovani.vymazPoleLabelu(seznamLabelPrestupCil);
    labelVykreslovani.vymazPoleLabelu(seznamLabelPrestupLinka);
    labelVykreslovani.vymazPoleLabelu(seznamLabelPrestupNastupiste);
    labelVykreslovani.vymazPoleLabelu(seznamLabelPrestupOdjezd);

    timerStridejStranky->stop();
    strankyKeStridani.clear();
    strankyKeStridani.push_back(ui->page_hlavni_2);
}


int MainWindow::vykresleniPrijatychDat()
{
    qDebug() <<  Q_FUNC_INFO;

    ui->stackedWidget_prostredek->setCurrentWidget(ui->page_hlavni_2);
    vymazTabulku(ui->tableWidget_zastavky);

    hlavniVymazObrazovku();
    ui->label_locationState->setText(stavSystemu.locationState);
    ui->label_currentStopIndex->setText(QString::number(stavSystemu.indexAktZastavky+1));

    if(stavSystemu.indexAktZastavky<0 )
    {
        vyskakovaciOkno("index zastavky je mensi nez 0");
        return 0;
    }


    hlavniVykresliNazevCile(nazevCile);
    hlavniVykresliCisloLinky(globalniSeznamZastavek.at(stavSystemu.indexAktZastavky),stavSystemu.vehicleSubMode);
    hlavniVykresliZastavkyiPasma(globalniSeznamZastavek,globalniSeznamZastavekNavaznehoSpoje);
    hlavniVykresliNacestne();

    strankyKeStridani.clear();





    //strankyKeStridani.push_back(ui->page_hlavni_2);



    if(!instanceXMLparser.existujeNavaznySpoj(globalniSeznamZastavekNavaznehoSpoje))
    {
        qDebug()<<"navazny spoj neni";
        ui->frame_navaznySpoj->hide();
        // ui->horizontalLayout_navaznySpoj;

    }
    else
    {
        QString navaznyCil="";
        QString navaznaLinka="";
        if(instanceXMLparser.udajeNavaznehoSpoje(globalniSeznamZastavekNavaznehoSpoje,navaznaLinka,navaznyCil))
        {
            ui->label_navaznaLinka->setText(navaznaLinka);
            ui->label_navaznyCil->setText(navaznyCil);
            ui->frame_navaznySpoj->show();
        }
    }

    //additional text message

    if(additionalTextMessageText!="")
    {
        zobrazAnnoucement(additionalTextMessageHeadline,additionalTextMessageType,additionalTextMessageText,"");
        strankyKeStridani.push_back(ui->page_oznameni);
    }
    else
    {
        labelVykreslovani.naplnAnouncementLabel("",ui->label_announcement);
    }

    //konecna

    if(jeVozidloNaKonecne(stavSystemu,globalniSeznamZastavek)&&(!instanceXMLparser.existujeNavaznySpoj(globalniSeznamZastavekNavaznehoSpoje)))
    {
        strankyKeStridani.push_front(ui->page_konecna);
        zobrazKonecnou();
    }
    else
    {
        if(zmenaPasma==true)
        {
            zobrazZmenuPasma(pasmaZ,pasmaDo);
        }
        else
        {
            if(instanceXMLparser.zmenaDat==true)
            {
                navratJizda();
            }
            strankyKeStridani.push_front(ui->page_hlavni_2);
            // skryjZmenuPasma();
        }

    }


    if(!globalniSeznamZastavek.at(stavSystemu.indexAktZastavky).zastavka.seznamPrestupu.isEmpty())
    {
        strankyKeStridani.push_back(ui->page_prestupy);
        hlavniVykresliPrestupy(globalniSeznamZastavek.at(stavSystemu.indexAktZastavky).zastavka.seznamPrestupu);


    }


    //   hlavniVykresliNasledne();

    formatZobrazeni();
    hlavniAutoformat();
    indexAktualniStridaneStranky=0;
    timerStridejStranky->start();

    vsechnyZastavkyDoTabulky(globalniSeznamZastavek,false);
    vsechnyZastavkyDoTabulky(globalniSeznamZastavekNavaznehoSpoje,true);

    return 1;
}

void MainWindow::vsechnyZastavkyDoTabulky(QVector<ZastavkaCil> seznamZastavek,bool navazny)
{
    if(!navazny)
    {
        vymazTabulku(ui->tableWidget_zastavky);
    }

    foreach(ZastavkaCil polozka, seznamZastavek)
    {
        zastavkaCilDoTabulky(polozka,navazny);
    }
}





void MainWindow::hlavniVykresliCisloLinky(ZastavkaCil aktZastavka,QString subMode)
{
    qDebug() <<  Q_FUNC_INFO;
    //  labelVykreslovani.naplnCisloLinkyLabel(alias,ui->Llinka);
    qDebug()<<"vypis linky:"<<aktZastavka.cil.NameLcd<<" "<<aktZastavka.linka.LineName<<" vylukova:"<<aktZastavka.linka.isDiversion ;
    
    if(cisSubscriber.version()=="2.4")
    {
        naplnPoleLinky2_4(subMode,aktZastavka.linka,ui->label_linka, qFloor(pomerPixelBod*200),false);

    }
    else
    {
        naplnPoleLinky(subMode,aktZastavka.linka,ui->label_linka, qFloor(pomerPixelBod*200),false);

    }
    //  labelVykreslovani.zmensiCisloLinkyLabel(ui->Llinka);

}

void MainWindow::hlavniVykresliNazevCile(QString nazev)
{
    qDebug() <<  Q_FUNC_INFO;

    labelVykreslovani.naplnNazevCileLabel(nazev,ui->Lcil);
    /* if(cisSubscriber.verze()=="2.4")
    {
       labelVykreslovani.naplnNazevCileLabel(labelVykreslovani.inlineFormatParser.vyparsujText(nazev, ui->Lcil->font().pixelSize(),labelVykreslovani.slozkaPiktogramu), ui->Lcil);

    }
    else
    {

    }
*/
}



void MainWindow::hlavniVykresliZastavkyiPasma(QVector<ZastavkaCil>aktZastavky, QVector<ZastavkaCil>navazZastavky )
{
    qDebug() <<  Q_FUNC_INFO;

    //
    hlavniVykresliSkupinuZastavekNew(aktZastavky,navazZastavky,stavSystemu.indexAktZastavky);

}





void MainWindow::hlavniVykresliSkupinuZastavekNew(QVector<ZastavkaCil> zastavky,QVector<ZastavkaCil> zastavkyNavazny, int index)
{
    qDebug() <<  Q_FUNC_INFO;
    //stavSystemu.indexAktZastavky;
    int pocetPoli=seznamLabelNazevZastavky.count();
    if(zastavky.isEmpty())
    {
        return ;
    }

    //   zastavky=vektorZastavkaCilZahoditZacatek(zastavky,index);

    zastavky.remove(0,index);



    for(int i=0;i<pocetPoli;i++)
    {
        ZastavkaCil aktualniZastavka;
        bool navaznySpoj=false;
        if(!zastavky.isEmpty())
        {
            aktualniZastavka=zastavky.takeFirst();
        }
        else
        {
            if(!zastavkyNavazny.isEmpty())
            {
                navaznySpoj=true;
                aktualniZastavka=zastavkyNavazny.takeFirst();
            }
            else
            {
                qDebug()<<"pro label "<<i<<" uz nezbyly zastavky";

                return;
            }
        }
        jednaZastavkaCilDoLabelu(aktualniZastavka,navaznySpoj,seznamLabelNazevZastavky.at(i),seznamLabelPasmoDolni.at(i),seznamLabelPasmoHorni.at(i));

    }



}


void MainWindow::jednaZastavkaCilDoLabelu(ZastavkaCil aktualniZastavka, bool navazny, QLabel* nazevZastavky, QLabel* dolniPasmo, QLabel* horniPasmo)
{
    PasmoveDvojiceLcd pasmoveDvojiceLcd;
    pasmoveDvojiceLcd.roztridPasma(aktualniZastavka.zastavka.seznamPasem);
    
    if(cisSubscriber.version()=="2.4")
    {
        //   QString nahradIconPiktogramem(QString vstup);
        //   nazevZastavky->setText(labelVykreslovani.zabalHtmlDoZnacek(labelVykreslovani.nahradIconPiktogramem( aktualniZastavka.zastavka.NameLcd, nazevZastavky->font().pixelSize(),labelVykreslovani.slozkaPiktogramu )));
        nazevZastavky->setText(labelVykreslovani.inlineFormatParser.vyparsujText(aktualniZastavka.zastavka.NameLcd, nazevZastavky->font().pixelSize(),labelVykreslovani.slozkaPiktogramu) );
    }
    else
    {
        nazevZastavky->setText(labelVykreslovani.zabalHtmlDoZnacek(labelVykreslovani.doplnPiktogramyBezZacatkuKonce(aktualniZastavka.zastavka.NameLcd,aktualniZastavka.zastavka.seznamPiktogramu,nazevZastavky->font().pixelSize() )));

    }


    if(pasmoveDvojiceLcd.pasmaSystemu1.isEmpty())
    {
        dolniPasmo->setText("");

    }
    else
    {
        QString pasmaString1=svgVykreslovani.pasmaDoStringu( pasmoveDvojiceLcd.pasmaSystemu1);
        QString zkratkaSystemuDvojtecka="";
        if (!pasmoveDvojiceLcd.pasmaSystemu2.isEmpty())
        {

            zkratkaSystemuDvojtecka=pasmoveDvojiceLcd.pasmaSystemu1.first().system+":";
        }
        dolniPasmo->setText(zkratkaSystemuDvojtecka+pasmaString1);
        dolniPasmo->setFont(fontPasmoVelke);
    }

    if(pasmoveDvojiceLcd.pasmaSystemu2.isEmpty())
    {
        horniPasmo->hide();
        horniPasmo->setFont(fontPasmoVelke);
    }
    else
    {
        QString pasmaString2=svgVykreslovani.pasmaDoStringu( pasmoveDvojiceLcd.pasmaSystemu2);
        horniPasmo->show();

        horniPasmo->setFont(fontPasmoMale );
        dolniPasmo->setFont(fontPasmoMale );

        horniPasmo->setText(pasmoveDvojiceLcd.pasmaSystemu2.first().system+":"+pasmaString2);
    }

    if(navazny==false)
    {
        nazevZastavky->setStyleSheet("color:"+barvyLinek.barva_bila_255_255_255+";");
        horniPasmo->setStyleSheet("color:"+barvyLinek.barva_bila_255_255_255+";");
        dolniPasmo->setStyleSheet("color:"+barvyLinek.barva_bila_255_255_255+";");
    }
    else
    {
        nazevZastavky->setStyleSheet("color:"+barvyLinek.barva_PozadiC_100_100_100+";");
        horniPasmo->setStyleSheet("color:"+barvyLinek.barva_PozadiC_100_100_100+";");
        dolniPasmo->setStyleSheet("color:"+barvyLinek.barva_PozadiC_100_100_100+";");
    }


}




void MainWindow::hlavniVykresliNacestne()
{
    qDebug() <<  Q_FUNC_INFO;

    if(globalniSeznamZastavek.isEmpty())
    {
        ui->label_nacestne->setText("");
        return;
    }
    
    QString novyVstup=labelVykreslovani.vykresliNacestneZastavkyText(globalniSeznamZastavek.at(stavSystemu.indexAktZastavky).nacestneZastavky, ui->label_nacestne->font().pixelSize(),cisSubscriber.version());



    if(ui->label_nacestne->text()!=novyVstup)
    {
        timerNacestneZastavky->start(intervalPosunuNacest);
        ui->label_nacestne->setText( novyVstup);
    }


}



int MainWindow::doplneniPromennych()
{
    qDebug() <<  Q_FUNC_INFO;
    // qInfo()<<"\n DoplneniPromennych";


    if ((globalniSeznamZastavek.size()>indexZastavky)&&(indexZastavky>=0))
    {
        ZastavkaCil aktualniZastavka=globalniSeznamZastavek.at(indexZastavky);
        nazevLinky=aktualniZastavka.linka.LineName;
        
        if(cisSubscriber.version()=="2.4")
        {
            //nazevCile=labelVykreslovani.zabalHtmlDoZnacek(labelVykreslovani.nahradIconPiktogramem(aktualniZastavka.cil.NameLcd,ui->Lcil->font().pixelSize(),labelVykreslovani.slozkaPiktogramu));
            nazevCile=labelVykreslovani.inlineFormatParser.vyparsujText(aktualniZastavka.cil.NameLcd,ui->Lcil->font().pixelSize(),labelVykreslovani.slozkaPiktogramu);
        }
        else
        {
            nazevCile=labelVykreslovani.zabalHtmlDoZnacek(labelVykreslovani.doplnPiktogramyBezZacatkuKonce(aktualniZastavka.cil.NameLcd,aktualniZastavka.cil.seznamPiktogramu,ui->Lcil->font().pixelSize()));
            nazevLinky=aktualniZastavka.linka.LineName;
        }

    }
    else
    {
        qDebug()<<"indexZastavky je"<<QString::number(indexZastavky)<<" velikost globSezZast="<<QString::number(globalniSeznamZastavek.size());
    }
    qInfo()<<"nazevCile "<<nazevCile;
    return 1;
}

int MainWindow::formatZobrazeni()
{
    qDebug() <<  Q_FUNC_INFO;



    if (stavSystemu.locationState=="AtStop" )
    {
        obarviPozadiPristi(barvyLinek.barva_PozadiB_50_50_50,barvyLinek.barva_Zastavka_180_180_180 );
    }
    else
    {
        obarviPozadiPristi(barvyLinek.barva_bila_255_255_255,barvyLinek.barva_PozadiB_50_50_50);
    }

    // hlavniAutoformat();
    return 1;

}

MainWindow::~MainWindow()
{
    qDebug() <<  Q_FUNC_INFO;
    delete ui;
}



void MainWindow::on_actiontestPolozka_triggered()
{
    qDebug() <<  Q_FUNC_INFO;

    slotToggleFullscreen();
}


/*


SITOVA CAST, ODPOVIDAC
nejsem autorem




*/



void MainWindow::on_pushButton_menu_refreh_clicked()
{
    qDebug() <<  Q_FUNC_INFO;

    //  CustomerInformationServiceSubscriber.odebirano=false ;
    //  CustomerInformationServiceSubscriber.hledejSluzby("_ibisip_http._tcp.",1);
    this->vymazObrazovku();
    slotAktualizaceTabulkySluzeb();
    //xmlDoPromenne(1);


    vymazObrazovku();
    cisSubscriber.novePrihlaseniOdberu();
}


void MainWindow::vymazTabulku(QTableWidget *tableWidget)
{
    qDebug() <<  Q_FUNC_INFO;
    //  https://stackoverflow.com/a/31564541
    tableWidget->clearSelection();

    // Disconnect all signals from table widget ! important !
    tableWidget->disconnect();

    // Remove all items
    tableWidget->clearContents();

    // Set row count to 0 (remove rows)
    tableWidget->setRowCount(0);

}

void MainWindow::vykresliSluzbyDoTabulky(QVector<QZeroConfService> seznamSluzeb)
{
    qDebug() <<  Q_FUNC_INFO;
    // ui->tabulkaSubscriberu->setRowCount(0);
    vymazTabulku(ui->tabulkaSubscriberu);


    foreach(QZeroConfService sluzba, seznamSluzeb)
    {
        slotSluzbaDoTabulky(sluzba);
    }
}


void MainWindow::slotSluzbaDoTabulky(QZeroConfService zcs)
{
    qDebug() <<  Q_FUNC_INFO;
    qint32 row;
    QTableWidgetItem *cell;

    QString nazev=zcs->name();
    QString ipadresa=zcs->ip().toString();
    QString host=zcs->host();
    QString verze=zcs.data()->txt().value("ver");
    int port=zcs->port();
    /*
    qDebug() <<"nazev sluzby "<<nazev<<" ip adresa "<<ipadresa<<" port "<<QString::number(port)<<" data" <<verze ;

 */

    row = ui->tabulkaSubscriberu->rowCount();
    ui->tabulkaSubscriberu->insertRow(row);
    cell = new QTableWidgetItem(nazev);
    ui->tabulkaSubscriberu->setItem(row, 0, cell);

    cell = new QTableWidgetItem(verze);
    ui->tabulkaSubscriberu->setItem(row, 1, cell);

    cell = new QTableWidgetItem(ipadresa);
    ui->tabulkaSubscriberu->setItem(row, 2, cell);

    cell = new QTableWidgetItem(QString::number(port));
    ui->tabulkaSubscriberu->setItem(row, 3, cell);

    cell = new QTableWidgetItem(host);
    ui->tabulkaSubscriberu->setItem(row, 4, cell);


    ui->tabulkaSubscriberu->resizeColumnsToContents();


    qDebug()<<"sluzbaDoTabulky_konec";

}


void MainWindow::slotPublisherDoTabulky(QZeroConfService zcs)
{
    qDebug() <<  Q_FUNC_INFO;
    vymazTabulku(ui->tableWidget_odebirano);
    qint32 row;
    QTableWidgetItem *cell;

    QString nazev=zcs->name();
    QString ipadresa=zcs->ip().toString();
    QString host=zcs->host();
    QString verze=zcs.data()->txt().value("ver");
    int port=zcs->port();
    /*
    qDebug() <<"nazev sluzby "<<nazev<<" ip adresa "<<ipadresa<<" port "<<QString::number(port)<<" data" <<verze ;

 */

    row = ui->tableWidget_odebirano->rowCount();
    ui->tableWidget_odebirano->insertRow(row);
    cell = new QTableWidgetItem(nazev);
    ui->tableWidget_odebirano->setItem(row, 0, cell);

    cell = new QTableWidgetItem(verze);
    ui->tableWidget_odebirano->setItem(row, 1, cell);

    cell = new QTableWidgetItem(ipadresa);
    ui->tableWidget_odebirano->setItem(row, 2, cell);

    cell = new QTableWidgetItem(QString::number(port));
    ui->tableWidget_odebirano->setItem(row, 3, cell);

    cell = new QTableWidgetItem(host);
    ui->tableWidget_odebirano->setItem(row, 4, cell);


    ui->tableWidget_odebirano->resizeColumnsToContents();


    qDebug()<<"sluzbaDoTabulky_konec";

}

void MainWindow::zastavkaCilDoTabulky(ZastavkaCil zastavkaCil, bool navazny)
{
    qDebug() <<  Q_FUNC_INFO;
    qint32 row;
    QTableWidgetItem *cell;





    /*
    qDebug() <<"nazev sluzby "<<nazev<<" ip adresa "<<ipadresa<<" port "<<QString::number(port)<<" data" <<verze ;

 */

    row = ui->tableWidget_zastavky->rowCount();
    ui->tableWidget_zastavky->insertRow(row);

    cell = new QTableWidgetItem(zastavkaCil.zastavka.NameLcd);

    if(navazny)
    {
        cell->setBackground(QColor(240,240,240));
    }
    ui->tableWidget_zastavky->setItem(row, 0, cell);

    cell = new QTableWidgetItem(zastavkaCil.linka.LineName);
    ui->tableWidget_zastavky->setItem(row, 1, cell);

    cell = new QTableWidgetItem(zastavkaCil.cil.NameLcd);
    ui->tableWidget_zastavky->setItem(row, 2, cell);








    ui->tableWidget_zastavky->resizeColumnsToContents();


    qDebug()<<"sluzbaDoTabulky_konec";

}

void MainWindow::slotXmlDoPromenne(QString vstupniXml)
{
    qDebug() <<  Q_FUNC_INFO;


    instanceXMLparser.nactiXML(vstupniXml);


    globalniSeznamZastavek.clear();
    globalniSeznamZastavekNavaznehoSpoje.clear();

    qDebug()<<"timestamp:"<<instanceXMLparser.vyparsujTimestamp(instanceXMLparser.dokument).toString(Qt::ISODate);
    
    
    if(cisSubscriber.version()=="1.0")
    {
        if(!instanceXMLparser.VytvorSeznamZastavek1_0(globalniSeznamZastavek,globalniSeznamZastavekNavaznehoSpoje, indexZastavky, pocetZastavek))
        {
            vymazObrazovku();
        }
    }
    else if(cisSubscriber.version()=="2.2CZ1.0")
    {
        if(!instanceXMLparser.VytvorSeznamZastavek2_2CZ1_0(globalniSeznamZastavek,globalniSeznamZastavekNavaznehoSpoje, indexZastavky, pocetZastavek))
        {
            vymazObrazovku();
        }
    }
    else if(cisSubscriber.version()=="2.4")
    {
        if(!instanceXMLparser.VytvorSeznamZastavek2_4(globalniSeznamZastavek,globalniSeznamZastavekNavaznehoSpoje, indexZastavky, pocetZastavek))
        {
            vymazObrazovku();
        }
    }
    else
    {
        qDebug()<<"neznámá verze";
    }



    instanceXMLparser.nactiVehicleGroup(stavSystemu,instanceXMLparser.dokument);

    //additional text message
    instanceXMLparser.nactiAdditionalTextMessage(instanceXMLparser.dokument,additionalTextMessageType,additionalTextMessageHeadline, additionalTextMessageText);

    //zmena tarifniho pasma

    zmenaPasma= instanceXMLparser.nactiFareZoneChange(instanceXMLparser.dokument,pasmaZ,pasmaDo);


    //instanceXMLparser.nactiXML(globalniSeznamZastavek, &indexZastavky, &pocetZastavek);
    //qInfo()<<globalniSeznamZastavek[4].StopName;
    qInfo()<<indexZastavky;
    qInfo()<<"CIl:"<<nazevCile;

    if(indexZastavky>=0)
    {
        if( globalniSeznamZastavek.size()>0)
        {
            if(jeVRozsahu(indexZastavky,globalniSeznamZastavek.count()))
            {
                doplneniPromennych();
                vykresleniPrijatychDat();
                formatZobrazeni();
                this->ledAktualizujZobrazeniVirtualnichPanelu(globalniSeznamZastavek,stavSystemu);
                this->svgVykresleni();
                qInfo()<<"CIl:"<<nazevCile;
            }
            else
            {
                //vyskakovaciOkno("index zastávky: "+QString::number(indexZastavky));
                qDebug()<<"index zastavky je 0";

            }

            //instanceHttpServeru.prijatoZeServeruTelo="";
        }
        else
        {
            vymazObrazovku();
            qDebug()<<"nepodarilo se vyparsovat zastavky";
        }
    }
    else
    {
        vymazObrazovku();
    }





    //NetworkCleanup();

}




void MainWindow::on_pushButton_menu_sluzby_clicked()
{
    ui->prepinadloStran->setCurrentWidget(ui->page_seznamSluzeb);
}

void MainWindow::on_pushButton_menu_hlavni_clicked()
{
    ui->prepinadloStran->setCurrentWidget(ui->page_hlavniObrazovka);
    formatZobrazeni();
    hlavniAutoformat();
}

void MainWindow::on_pushButton_menu_casovac_clicked()
{
    ui->prepinadloStran->setCurrentWidget(ui->page_casovac);
}

void MainWindow::obarviPozadiPristi(QString barvaPisma,QString barvaPozadi)
{
    qDebug() <<  Q_FUNC_INFO;
    //
    labelVykreslovani.obarviPozadiPristi(barvaPisma,barvaPozadi,ui->frame_spodniRadek);
    svgVykreslovani.obarviPozadiPristi(barvaPisma,barvaPozadi);


    QString stylTextu="color:"+barvaPisma;
    ui->Lnacestna1->setStyleSheet(stylTextu);
    ui->label_pasmo1_1->setStyleSheet(stylTextu);
    ui->label_pasmo1_2->setStyleSheet(stylTextu);


}


void MainWindow::on_pushButton_menu_quit_clicked()
{
    qDebug() <<  Q_FUNC_INFO;
    MainWindow::close();
}



void MainWindow::on_pushButton_menu_svg_clicked()
{
    qDebug()<<Q_FUNC_INFO;
    ui->prepinadloStran->setCurrentWidget(ui->page_svg);


    //QSvgRenderer *m_renderer = new QSvgRenderer(QLatin1String("./Verlauf.svg"));

    this->svgVykresleni();
    /*
    ui->graphicsView->setScene(&novaScena);
    ui->graphicsView->update();
    ui->graphicsView->show();
    */

}


//zkpirovano z svgviewer demo

bool MainWindow::svgVykresleni()
{

    if (globalniSeznamZastavek.length()>0)
    {
        //svgVykreslovac.svgReplaceName("Verlauf2.svg","vystup.txt",globalniSeznamZastavek.last().StopName,globalniSeznamZastavek.at(stavSystemu.indexAktZastavky).StopName,globalniSeznamZastavek.at(stavSystemu.indexAktZastavky+1).StopName,globalniSeznamZastavek.at(stavSystemu.indexAktZastavky+2).StopName);
        svgVykreslovani.aktualizujVse(globalniSeznamZastavek,stavSystemu);
    }
    else
    {
        qDebug()<<"seznam zastavek je prazdny";
    }

    //int vysledek=svgOpenFile("./bubbles.svg");
    int vysledek=svgOpenFile(QCoreApplication::applicationDirPath()+"/vystup.svg");
    qDebug()<<"vysledek otevirani SVG je"<<QString::number(vysledek);

    return true;
}


bool MainWindow::svgOpenFile(const QString &fileName)
{
    qDebug() <<  Q_FUNC_INFO;
    QGraphicsScene *s = &scene;

    QFile soubor;

    QScopedPointer<QGraphicsSvgItem> svgItem(new QGraphicsSvgItem(fileName));
    svgItem->renderer()->setFramesPerSecond(20);
    if (!svgItem->renderer()->isValid())
        return false;

    s->clear();
    // resetTransform();

    m_svgItem = svgItem.take();

    //m_svgItem = svgItem.take();
    m_svgItem->setFlags(QGraphicsItem::ItemClipsToShape);
    m_svgItem->setCacheMode(QGraphicsItem::NoCache);
    m_svgItem->setZValue(0);




    m_outlineItem = new QGraphicsRectItem(m_svgItem->boundingRect());
    QPen outline(Qt::black, 2, Qt::DashLine);
    outline.setCosmetic(true);
    m_outlineItem->setPen(outline);
    m_outlineItem->setBrush(Qt::NoBrush);
    m_outlineItem->setZValue(1);

    s->addItem(m_svgItem);
    s->setSceneRect(m_outlineItem->boundingRect().adjusted(-10, -10, 10, 10));
    ui->graphicsView->setScene(s);

    return true;
}

void MainWindow::on_pushButton_menu_led_clicked()
{
    ui->prepinadloStran->setCurrentWidget(ui->page_led);
    ui->labelFrontBottomRow->setText("");
}


void MainWindow::ledNaplnFront(QString linka,QString horniRadek,QString dolniRadek)
{
    qDebug() <<  Q_FUNC_INFO;

    if (dolniRadek!="")
    {
        ui->labelFrontSingle->setVisible(false);
        ui->labelFrontBottomRow->setVisible(true);
        ui->labelFrontTopRow->setVisible(true);
    }
    else
    {
        ui->labelFrontSingle->setVisible(true);
        ui->labelFrontBottomRow->setVisible(false);
        ui->labelFrontTopRow->setVisible(false);
    }


    ui->labelFrontTopRow->setText(horniRadek);
    ui->labelFrontBottomRow->setText(dolniRadek);
    ui->labelFrontSingle->setText(horniRadek);

    ledZapisLinku(ui->labelFrontLine,linka);
}


void MainWindow::ledZarovnejPretecenyRadek(QLabel* label)
{
    qDebug() <<  Q_FUNC_INFO;
    QFontMetrics metrics(label->font());

    if(metrics.horizontalAdvance(label->text())> label->width())
    {
        label->setAlignment(Qt::AlignLeading|Qt::AlignBottom);
    }
    else
    {
        label->setAlignment(Qt::AlignHCenter|Qt::AlignBottom);
    }
}

void MainWindow::ledNaplnSide(QString linka,QString horniRadek,QString dolniRadek)
{
    qDebug() <<  Q_FUNC_INFO;
    ui->labelSideLine->setText(linka);



    ui->labelSideTopRow->setText(horniRadek);
    ledZarovnejPretecenyRadek(ui->labelSideTopRow);



    ui->labelSideBottomRow->setText(dolniRadek);


    ledZapisLinku(ui->labelSideLine,linka);


}


void MainWindow::ledZapisLinku(QLabel* label, QString text)
{
    qDebug()<<Q_FUNC_INFO;
    label->setText(text);
    if (text.length()>3)
    {

        label->setFont(font10);
    }
    else
    {
        label->setFont(font8);
    }
    ledZarovnejPretecenyRadek(label);
}

void MainWindow::ledNaplnRear(QString linka)
{
    qDebug() <<  Q_FUNC_INFO;

    ledZapisLinku(ui->labelRearLine,linka);

}

void MainWindow::ledNaplnInner(QString linka,QString horniRadek,QString dolniRadek)
{
    qDebug() <<  Q_FUNC_INFO;
    ui->labelInnerLine->setText(linka);
    ui->labelInnerTopRow->setText(horniRadek);
    ui->labelInnerBottomRow->setText(dolniRadek);
}


void MainWindow::ledInicializujVirtualniPanely()
{
    qDebug() <<  Q_FUNC_INFO;
    /*
    ledNaplnFront("123","čelní horní","čelní dolní");
    ledNaplnSide("456","Boční cíl","Boční nácestné");
    ledNaplnRear("789");
    ledNaplnInner("123","vnitřní cíl", "vnitřní nácesty");
*/

    ui->labelFrontSingle->setFont(font5);


    ui->labelFrontTopRow->setFont(font1);
    ui->labelFrontBottomRow->setFont(font1);


    ui->labelSideTopRow->setFont(font1);
    ui->labelSideBottomRow->setFont(font1);




    ui->labelInnerLine->setFont(font3);
    ui->labelInnerBottomRow->setFont(font1);
    ui->labelInnerTopRow->setFont(font1);

    if(ui->labelFrontLine->text().length()>3)
    {
        ui->labelFrontLine->setFont(font10);
        ui->labelSideLine->setFont(font10);
        ui->labelRearLine->setFont(font10);
    }
    else
    {
        ui->labelFrontLine->setFont(font8);
        ui->labelSideLine->setFont(font8);
        ui->labelRearLine->setFont(font8);
    }

}

void MainWindow::ledVymazPanely()
{
    qDebug() <<  Q_FUNC_INFO;
    ledNaplnFront("","","");
    ledNaplnSide("","","");
    ledNaplnRear("");
    ledNaplnInner("","", "");
    textyBocniPanelkIteraci.clear();
    textyVnitrniPanelkIteraci.clear();
}

void MainWindow::ledAktualizujZobrazeniVirtualnichPanelu(QVector<ZastavkaCil> zastavky, CestaUdaje stav )
{
    qDebug() <<  Q_FUNC_INFO;
    if(!jeVRozsahu(stav.indexAktZastavky,zastavky.count()))
    {
        return;
    }

    ZastavkaCil aktZast=zastavky.at(stav.indexAktZastavky);

    ledNaplnFront(aktZast.linka.LineName,aktZast.cil.NameFront,aktZast.cil.NameFront2);

    //ledNaplnSide(aktZast.linka.LineName,aktZast.cil.NameSide,aktZast.zastavka.NameSide );
    ledNaplnSide(aktZast.linka.LineName,aktZast.cil.NameSide,"" );
    ledNaplnRear(aktZast.linka.LineName);
    ledNaplnInner(aktZast.linka.LineName,aktZast.cil.NameInner, aktZast.zastavka.NameInner);

    textyBocniPanelkIteraci=ledNaplnNacestyBocniPanel(aktZast);
    textyVnitrniPanelkIteraci=ledNaplnNacestyVnitrniPanel(aktZast);

    ledZmenVelikostPanelu();


}

QVector<QString> MainWindow::ledNaplnNacestyBocniPanel(ZastavkaCil aktualniZastavka)
{
    qDebug() <<  Q_FUNC_INFO;
    Zastavka nacesta;
    QVector<QString> textyNaBocniPanel;
    textyNaBocniPanel.append("přes:");
        foreach (nacesta,aktualniZastavka.nacestneZastavky)
    {
        textyNaBocniPanel.append(nacesta.NameSide);
        // qDebug()<<"pridavam nacestnou na bocni"<<nacesta.NameSide;
    }
    return textyNaBocniPanel;

}

QVector<QString> MainWindow::ledNaplnNacestyVnitrniPanel(ZastavkaCil aktualniZastavka)
{
    qDebug() <<  Q_FUNC_INFO;
    Zastavka nacesta;
    QVector<QString> textyNaVnitrniPanel;
    textyNaVnitrniPanel.append("přes:");
        foreach (nacesta,aktualniZastavka.nacestneZastavky)
    {
        textyNaVnitrniPanel.append(nacesta.NameInner);
        qDebug()<<"pridavam nacestnou na bocni"<<nacesta.NameSide;
    }
    return textyNaVnitrniPanel;

}


void MainWindow::ledIterujVsechnyPanely()
{
    // qDebug()<<"MainWindow::iterujVsechnyPanely()";
    ledIterujBocniPanel(textyBocniPanelkIteraci,cyklovaniIndex);
    ledIterujVnitrniPanel(textyVnitrniPanelkIteraci,cyklovaniIndex);




}

void MainWindow::ledIterujBocniPanel(QVector<QString> texty, int &iteracniIndex)
{
    // qDebug()<<"MainWindow::iterujBocniPanel";

    if(iteracniIndex<texty.length())
    {
        ui->labelSideBottomRow->setText(texty.at(iteracniIndex));
        ledZarovnejPretecenyRadek(ui->labelSideBottomRow);

        //  iteracniIndex++;

    }
    else
    {
        //   iteracniIndex=0;
    }
}

void MainWindow::ledIterujVnitrniPanel(QVector<QString> texty, int &iteracniIndex)
{
    // qDebug()<<"MainWindow::iterujBocniPanel";

    if(iteracniIndex<texty.length())
    {
        ui->labelInnerBottomRow->setText(texty.at(iteracniIndex));

        iteracniIndex++;

    }
    else
    {
        iteracniIndex=0;
    }
}




void MainWindow::zobrazZmenuPasma(QVector<Pasmo> zPasem, QVector<Pasmo> naPasma)
{
    qDebug() <<  Q_FUNC_INFO;
    hlavniZobrazZmenuPasma(zPasem,naPasma);
    svgVykreslovani.zobrazZmenuPasma(zPasem,naPasma);
}

void MainWindow::hlavniZobrazZmenuPasma(QVector<Pasmo> zPasem, QVector<Pasmo> naPasma)
{
    qDebug() <<  Q_FUNC_INFO;

    ui->stackedWidget_obrazovka->setCurrentWidget(ui->page_hlavni);
    ui->stackedWidget_prostredek->setCurrentWidget(ui->page_zmenaPasma);

    ui->label_pasmo1->setText(SvgRenderer::pasmaDoStringu(Pasmo::vratPidPasma(zPasem,"PID")));
    ui->label_pasmo2->setText(SvgRenderer::pasmaDoStringu(Pasmo::vratPidPasma(naPasma,"PID")));

    labelVykreslovani.naplnZmenaLabel(labelVykreslovani.vyrobTextZmenyPasma(zPasem,naPasma),ui->label_zmena);
}


void MainWindow::zobrazAnnoucement(QString title,QString type,QString textCz, QString textEn)
{
    qDebug() <<  Q_FUNC_INFO;
    hlavniZobrazAnnoucement(title,type,textCz,textEn);
    svgVykreslovani.zobrazAnnoucement(title,type,textCz,textEn);
}

void MainWindow::hlavniZobrazAnnoucement(QString title,QString type,QString textCz, QString textEn)
{
    qDebug() <<  Q_FUNC_INFO;
    labelVykreslovani.naplnAnouncementLabel(textCz,ui->label_announcement);
    ui->stackedWidget_obrazovka->setCurrentWidget(ui->page_hlavni);
    ui->stackedWidget_prostredek->setCurrentWidget(ui->page_oznameni);

    ui->label_oznTitle->setText(title);
    ui->label_oznType->setText(  labelVykreslovani.textNaPiktogramOznameni(type,100*pomerPixelBod));
    ui->label_oznTextCs->setText(textCz);
    ui->label_oznTextEn->setText(textEn);

}



void MainWindow::skryjAnnouncement()
{
    qDebug() <<  Q_FUNC_INFO;
    navratJizda();
}

void MainWindow::skryjZmenuPasma()
{
    qDebug() <<  Q_FUNC_INFO;
    navratJizda();
}


void MainWindow::navratJizda()
{
    qDebug() <<  Q_FUNC_INFO;
    ui->stackedWidget_obrazovka->setCurrentWidget(ui->page_hlavni);
    ui->stackedWidget_prostredek->setCurrentWidget(ui->page_hlavni_2);
    labelVykreslovani.naplnZmenaLabel("",ui->label_zmena);
}


void MainWindow::zobrazKonecnou()
{
    qDebug() <<  Q_FUNC_INFO;
    ui->stackedWidget_obrazovka->setCurrentWidget(ui->page_hlavni);
    ui->stackedWidget_prostredek->setCurrentWidget(ui->page_konecna);

}


int MainWindow::jeVozidloNaKonecne(CestaUdaje stav, QVector<ZastavkaCil> zastavky)
{

    qDebug() <<  Q_FUNC_INFO;
    if((stav.indexAktZastavky==(zastavky.count()-1))&&(stav.locationState=="AtStop"))
    {
        return true;
    }
    return false;
}


int MainWindow::jeVRozsahu(int index, int pocetHodnot)
{
    if((index<pocetHodnot)&&(index>=0))
    {

        return 1;
    }
    else
    {
        QMessageBox msgBox;
        msgBox.setText("hodnota "+QString::number(index)+" je mimo rozsah "+ QString::number(pocetHodnot));
        msgBox.exec();
        qDebug()<<" hodnota mimo rozsah";

        return 0;
    }

}


void MainWindow::hlavniVykresliPrestupy(QVector<Prestup> seznamPrestupu)
{
    qDebug() <<  Q_FUNC_INFO;
    //ui->stackedWidget_prostredek->setCurrentWidget(ui->page_prestupy);

    /*
    foreach(QFrame* ramec,seznamFramePrestup)
    {
        // ramec->hide();
    }*/
    foreach(QFrame* label,seznamLabelPrestupCil)
    {
        label->hide();
    }

    foreach(QFrame* label,seznamLabelPrestupLinka)
    {
        label->hide();
    }

    foreach(QFrame* label,seznamLabelPrestupNastupiste)
    {
        label->hide();
    }

    foreach(QFrame* label,seznamLabelPrestupOdjezd)
    {
        label->hide();
    }

    labelVykreslovani.vymazPoleLabelu(seznamLabelPrestupCil);
    labelVykreslovani.vymazPoleLabelu(seznamLabelPrestupLinka);
    labelVykreslovani.vymazPoleLabelu(seznamLabelPrestupNastupiste);
    labelVykreslovani.vymazPoleLabelu(seznamLabelPrestupOdjezd);





    for (int i=0;i<labelVykreslovani.minimum(seznamPrestupu.count(), seznamLabelPrestupCil.count()) ; i++)
    {
        Prestup aktualniPrestup=seznamPrestupu.at(i);
        seznamLabelPrestupCil.at(i)->setText(aktualniPrestup.destinationName);
        seznamLabelPrestupCil.at(i)->show();
        
        
        
        if(cisSubscriber.version()=="2.4")
        {
            naplnPoleLinky2_4(aktualniPrestup.subMode,aktualniPrestup.line, seznamLabelPrestupLinka.at(i), velikostPiktogramPrestupDynamic,true);

        }
        else
        {
            naplnPoleLinky(aktualniPrestup.subMode,aktualniPrestup.line, seznamLabelPrestupLinka.at(i),velikostPiktogramPrestupDynamic,true);
        }


        seznamLabelPrestupNastupiste.at(i)->setText(aktualniPrestup.platform );
        seznamLabelPrestupNastupiste.at(i)->show();

        seznamLabelPrestupOdjezd.at(i)->setText("<b>"+ QString::number( aktualniPrestup.minutDoOdjezdu(QDateTime::currentDateTime() ))+"</b> min.");
        seznamLabelPrestupOdjezd.at(i)->show();
    }
}


void MainWindow::naplnPoleLinky( QString subMode, Line line, QLabel* label, int velikostPiktogramu,bool prestup)
{
    qDebug()<<Q_FUNC_INFO;
    QString linkaStyleSheetStandard="font-weight: bold;";

    if(prestup)
    {
        linkaStyleSheetStandard+="border-radius:6px;padding: 5px; ";
    }


    QString linkaStyleSheetPiktogram="border-radius:6px; padding: 0px; margin: 0px; font-weight: bold;";



    QString nahrazeno=labelVykreslovani.nahradMetro(line.LineName,subMode,velikostPiktogramu);

    //defaultni seda barva na bile pozadi, neznama kombinace

    StylLinkyOld stylLinky;



    stylLinky.pozadi="background-color:"+barvyLinek.barva_bila_255_255_255+";";


    stylLinky.text="color:"+barvyLinek.barva_PozadiD_150_150_150+";";




    if(nahrazeno==line.LineName)
    {
        stylLinky=barvyLinek.linkaDoStylu(subMode,line);

        label->setStyleSheet(linkaStyleSheetStandard+stylLinky.text+stylLinky.pozadi);
        label->setText(line.LineName);
    }
    else
    {
        label->setStyleSheet(linkaStyleSheetPiktogram);
        label->setText(nahrazeno);
        //   qDebug()<<"nahrazeny retezec metra:"<<nahrazeno;
    }



    label->show();
}

void MainWindow::naplnPoleLinky2_4( QString subMode, Line line, QLabel* label, int velikostPiktogramu,bool prestup)
{
    qDebug()<<Q_FUNC_INFO;


    QString linkaStyleSheetStandard="font-weight: bold; background-color:#ffffff; padding: 0px; margin: 0px; ";

    if(prestup)
    {
        linkaStyleSheetStandard+="border-radius:6px;padding: 0px; ";
    }


    QString linkaStyleSheetPiktogram="border-radius:6px; padding: 0px; margin: 0px; font-weight: bold;";


    label->setStyleSheet(linkaStyleSheetStandard);

    QString vyslednyText= labelVykreslovani.inlineFormatParser.vyparsujText(line.LineName, label->font().pixelSize(),labelVykreslovani.slozkaPiktogramu);
    label->setText( vyslednyText);


    qDebug().noquote()<<"obsah pole linky: "<<vyslednyText;
    label->show();
}



void MainWindow::slotHlavniStridejStranky()
{
    qDebug() <<  Q_FUNC_INFO<<" counter ma hodnotu "<<indexAktualniStridaneStranky<<" v seznamu je "<<strankyKeStridani.count();

    if(indexAktualniStridaneStranky==(strankyKeStridani.count()-1))
    {
        indexAktualniStridaneStranky=0;
    }
    else
    {
        indexAktualniStridaneStranky++;
    }


    if(indexAktualniStridaneStranky<strankyKeStridani.count())
    {
        ui->stackedWidget_prostredek->setCurrentWidget(strankyKeStridani.at(indexAktualniStridaneStranky));

    }



}

void MainWindow::slotToggleFullscreen()
{
    qDebug() <<  Q_FUNC_INFO;
    // isFullScreen() ? showNormal() : showFullScreen();



    if (MainWindow::windowState()==Qt::WindowFullScreen )
    {
        MainWindow::setWindowState(Qt::WindowMaximized);
        // ui->verticalLayoutWidget_4->show();
        //    MainWindow::setWindowState(Qt::Window);

        ui->frame_menu->show();
        ui->menuBar->show();
        ui->statusBar->show();
        ui->mainToolBar->show();
        ui->frame_debug->show();


        // this->setWindowFlags(flags|Qt::SplashScreen);
    }
    else
    {
        MainWindow::setWindowState(Qt::WindowFullScreen);

        ui->frame_menu->hide();
        ui->menuBar->hide();
        ui->statusBar->hide();
        ui->mainToolBar->hide();
        ui->frame_debug->hide();


    }
    // hlavniAutoformat();

    ledZmenVelikostPanelu();




}


void MainWindow::hlavniAutoformat()
{
    qDebug() <<  Q_FUNC_INFO;
    this->show();
    pomerPixelBod=ui->frame_hlavni->height()/1050.0;

    velikostPiktogramPrestupDynamic=qFloor(velikostPiktogramPrestup*pomerPixelBod);


    labelVykreslovani.labelNastavVelikost(ui->Lcil,velikostFontCil,pomerPixelBod ); //100
    labelVykreslovani.labelNastavVelikost(ui->label_nacestne,velikostFontNacestne,pomerPixelBod); //72

    labelVykreslovani.poleLabelNastavVelikost(seznamLabelNazevZastavky,velikostFontNasledujici,pomerPixelBod); //100

    labelVykreslovani.poleLabelNastavVelikost(seznamLabelPrestupLinka,velikostFontPrestupLinka,pomerPixelBod); //48
    labelVykreslovani.poleLabelNastavSirku(seznamLabelPrestupLinka,pomerPixelBod*velikostPrestupRamecekSirka); //95
    labelVykreslovani.poleLabelNastavVysku(seznamLabelPrestupLinka,pomerPixelBod*velikostPrestupRamecekVyska); //65

    labelVykreslovani.poleLabelNastavVelikost(seznamLabelPrestupCil,velikostFontPrestupCil,pomerPixelBod); //36
    labelVykreslovani.poleLabelNastavVelikost(seznamLabelPrestupNastupiste,velikostFontPrestupCil,pomerPixelBod); //36
    labelVykreslovani.poleLabelNastavVelikost(seznamLabelPrestupOdjezd,velikostFontPrestupCil,pomerPixelBod); //36

    labelVykreslovani.labelNastavVelikost(ui->label_hodiny,80,pomerPixelBod); //80
    labelVykreslovani.labelNastavVelikost(ui->label_textPres,30,pomerPixelBod); //30
    labelVykreslovani.labelNastavVelikost(ui->label_textVia ,30,pomerPixelBod); //30
    /*
    labelVykreslovani.labelNastavVelikost(,,);
    labelVykreslovani.labelNastavVelikost(,,);
    labelVykreslovani.labelNastavVelikost(,,);
    labelVykreslovani.labelNastavVelikost(,,);
    */
    labelVykreslovani.zmensiCisloLinkyLabel(ui->label_linka);

}

void MainWindow::on_pushButton_menu_fullscreen_clicked()
{
    slotToggleFullscreen();
}

void MainWindow::slotParametryZarizeniDoConfigu()
{
    qDebug()<<Q_FUNC_INFO;
    settings.setValue("deviceManagementService1_0/deviceName",deviceManagementService1_0.deviceName());
    settings.setValue("deviceManagementService1_0/deviceManufacturer",deviceManagementService1_0.deviceManufacturer());
    settings.setValue("deviceManagementService1_0/deviceSerialNumber",deviceManagementService1_0.deviceSerialNumber());
    settings.setValue("deviceManagementService1_0/deviceClass",deviceManagementService1_0.deviceClass());
    settings.setValue("deviceManagementService1_0/deviceId",deviceManagementService1_0.deviceId());
}


void MainWindow::ledZmenVelikostOkna(QLabel * okno, int sirkaDot, int vyskaDot, float koeficient)
{
    //int koeficient = pomer pixel:pocetDotu
    okno->setFixedHeight(float(vyskaDot)*koeficient);
    okno->setFixedWidth(float(sirkaDot)*koeficient);
}


void MainWindow::ledZmenVelikostPanelu()
{
    qDebug()<<Q_FUNC_INFO;

    const int cilSirka=108;
    const int cilVyskaVelky=19;

    const int vyskaHorniRadek=9;
    const int vyskaDolniRadek=10;


    const int linkaSirka=30;
    const int linkaVyska=19;


    const int linkaVnitrniSirka=22;
    const int linkaVnitrniVyska=8;

    const int vyskaVnitrniHorniRadek=8;
    const int vyskaVnitrniDolniRadek=8;

    const int sirkaVnitrniHorniRadek=113;
    const int sirkaVnitrniDolniRadek=135;

    const int cilBocniSirka=82;


    int velikostFontu=font8.pointSize();
    int vyskaLinky=ui->labelFrontLine->height();
    float pomerFontuKvysce=float(velikostFontu)/float(vyskaLinky);

    pomerPixelLed=ui->labelFrontSingle->width() /(float(cilSirka)); //A

    float novaVyskaLinky=float(linkaVyska)*pomerPixelLed;
    float staraVyskaLinky=78.0;

    float novaVelikostFontu=65*(novaVyskaLinky/staraVyskaLinky);


    ui->labelFrontSingle->setFixedHeight(float(cilVyskaVelky)*pomerPixelLed);

    ui->labelFrontBottomRow->setFixedHeight(float(vyskaDolniRadek)*pomerPixelLed);
    ui->labelFrontTopRow->setFixedHeight(float(vyskaHorniRadek)*pomerPixelLed);

    ledZmenVelikostOkna(ui->labelFrontLine,linkaSirka,linkaVyska,pomerPixelLed);

    ledZmenVelikostOkna(ui->labelSideLine,linkaSirka,linkaVyska,pomerPixelLed);
    ledZmenVelikostOkna(ui->labelSideTopRow,cilBocniSirka,vyskaHorniRadek,pomerPixelLed);
    ledZmenVelikostOkna(ui->labelSideBottomRow,cilBocniSirka,vyskaDolniRadek,pomerPixelLed);

    ledZmenVelikostOkna(ui->labelRearLine,linkaSirka,linkaVyska,pomerPixelLed);

    ledZmenVelikostOkna(ui->labelInnerLine,linkaVnitrniSirka,linkaVnitrniVyska,pomerPixelLed);

    ledZmenVelikostOkna(ui->labelInnerTopRow,sirkaVnitrniHorniRadek,vyskaVnitrniHorniRadek,pomerPixelLed);
    ledZmenVelikostOkna(ui->labelInnerBottomRow,sirkaVnitrniDolniRadek,vyskaVnitrniDolniRadek,pomerPixelLed);




    qDebug()<<"pomer vysky: "<<pomerFontuKvysce; //pomer vysky:  0.833333

    font1.setPointSize(novaVelikostFontu);
    font3.setPointSize(novaVelikostFontu);
    font5.setPointSize(novaVelikostFontu);
    font8.setPointSize(novaVelikostFontu);
    font10.setPointSize(novaVelikostFontu);

    ledInicializujVirtualniPanely();
}

void MainWindow::vyskakovaciOkno(QString poznamka)
{
    qDebug() <<  Q_FUNC_INFO;
    QMessageBox msgBox;
    msgBox.setText(poznamka);
    QFont font;
    //font.setBold(true);
    font.setPointSize(30);
    msgBox.setFont(font);
    // msgBox.setStyleSheet("font-size: 30px;");
    msgBox.exec();
}


QVector<ZastavkaCil> MainWindow::vektorZastavkaCilZahoditZacatek(QVector<ZastavkaCil> vstup, int zacatek)
{
    QVector<ZastavkaCil> vystup;
    for(int i=zacatek;i<vstup.count();i++)
    {
        if(i>zacatek)
        {
            vystup.push_back(vstup.at(i));
            // qDebug()<<"orez zastavek:"<<vstup.at(i).zastavka.NameLcd;
        }

    }
    return vystup;

}
