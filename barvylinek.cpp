#include "barvylinek.h"

BarvyLinek::BarvyLinek()
{
    naplnMapBarev();
}


void BarvyLinek::naplnMapBarev()
{
    qDebug() <<  Q_FUNC_INFO;
    //dd1 Metro, nahrazuje se piktogramem
    barvaTextu["metro"]=barva_cerna_0_0_0;
    barvaPozadi["metro"]=barva_bila_255_255_255;

    //dd2 Denní tramvaj
    barvaTextu["localTram"]=barva_Tramvaj_120_2_0;
    barvaPozadi["localTram"]=barva_bila_255_255_255;

    barvaTextu["localTramDiversion"]=barva_Tramvaj_120_2_0;
    barvaPozadi["localTramDiversion"]=barva_Vyluky_255_170_30;

    //dd3 Denní městská autobusová linka
    barvaTextu["localBus"]=barva_Autobus_0_120_160;
    barvaPozadi["localBus"]=barva_bila_255_255_255;

    barvaTextu["localBusDiversion"]=barva_Autobus_0_120_160;
    barvaPozadi["localBusDiversion"]=barva_Vyluky_255_170_30;


    //dd4 Denní příměstská nebo regionální linka
    barvaTextu["regionalBus"]=barva_cerna_0_0_0;
    barvaPozadi["regionalBus"]=barva_bila_255_255_255;


    barvaTextu["regionalBusDiversion"]=barva_cerna_0_0_0;
    barvaPozadi["regionalBusDiversion"]=barva_Vyluky_255_170_30;

    //dd5 Noční městská autobusová linka
    barvaTextu["localBusNight"]=barva_bila_255_255_255;
    barvaPozadi["localBusNight"]=barva_Autobus_0_120_160;


    barvaTextu["localBusNightDiversion"]=barva_Vyluky_255_170_30;
    barvaPozadi["localBusNightDiversion"]=barva_Autobus_0_120_160;

    //dd6 Noční tramvaj

    barvaTextu["localTramNight"]=barva_bila_255_255_255;
    barvaPozadi["localTramNight"]=barva_Tramvaj_120_2_0;

    barvaTextu["localTramNightDiversion"]=barva_Vyluky_255_170_30;
    barvaPozadi["localTramNightDiversion"]=barva_Tramvaj_120_2_0;

    //dd7 Linka náhradní dopravy, městský autobus
    barvaTextu["localBusReplacement"]=barva_Vyluky_255_170_30;
    barvaPozadi["localBusReplacement"]=barva_bila_255_255_255;

    //dd8 Lanovka
    barvaTextu["funicular"]=barva_Lanovka_201_208_34;
    barvaPozadi["funicular"]=barva_bila_255_255_255;
    //dd9 Školní linka
    barvaTextu["schoolBus"]=barva_Autobus_0_120_160;
    barvaPozadi["schoolBus"]=barva_bila_255_255_255;
    //dd10 Invalidní
    barvaTextu["specialNeedsBus"]=barva_Specialni_143_188_25;
    barvaPozadi["specialNeedsBus"]=barva_bila_255_255_255;
    //dd11 Smluvni
    barvaTextu["localBusSpecial"]=barva_Specialni_143_188_25;
    barvaPozadi["localBusSpecial"]=barva_bila_255_255_255;
    //dd12 Přívoz
    barvaTextu["localPassengerFerry"]=barva_Privoz_0_164_167;
    barvaPozadi["localPassengerFerry"]=barva_bila_255_255_255;
    //dd13 Vlaky PID – linky S nebo R
    barvaTextu["regionalRail"]=barva_bila_255_255_255;
    barvaPozadi["regionalRail"]=barva_Vlak_15_30_65;
    //dd14 Linka náhradní dopravy, NAD za vlak
    barvaTextu["railReplacementBus"]=barva_Vyluky_255_170_30;
    barvaPozadi["railReplacementBus"]=barva_bila_255_255_255;

    barvaTextu["railReplacementBusReplacement"]=barva_Vyluky_255_170_30;
    barvaPozadi["railReplacementBusReplacement"]=barva_bila_255_255_255;



    //dd15 Linka náhradní dopravy, Tram
    barvaTextu["localTramReplacement"]=barva_Vyluky_255_170_30;
    barvaPozadi["localTramReplacement"]=barva_bila_255_255_255;
    //dd16 Noční příměstská nebo regionální linka
    barvaTextu["regionalBusNight"]=barva_bila_255_255_255;
    barvaPozadi["regionalBusNight"]=barva_Nocni_9_0_62;

    barvaTextu["regionalBusNightDiversion"]=barva_Vyluky_255_170_30;
    barvaPozadi["regionalBusNightDiversion"]=barva_Nocni_9_0_62;

    //dd17 Linka mimo systém PID (3 znaky)
    //  barvaTextu[""]=barva_PozadiD_150_150_150;
    //  barvaPozadi[""]=barva_bila_255_255_255;
    barvaTextu["unknown"]=barva_PozadiD_150_150_150;
    barvaPozadi["unknown"]=barva_bila_255_255_255;
    barvaTextu["undefined"]=barva_PozadiD_150_150_150;
    barvaPozadi["undefined"]=barva_bila_255_255_255;
    //dd18 Denní trolejbusová linka
    barvaTextu["localTrolleybus"]=barva_Trolejbus_128_22_111;
    barvaPozadi["localTrolleybus"]=barva_bila_255_255_255;


    /*
    barvaTextu[""]=barva;
    barvaPozadi[""]=barva;

    barvaTextu[""]=barva;
    barvaPozadi[""]=barva;

*/

}


StylLinkyOld BarvyLinek::linkaDoStylu(QString &subMode, Line linka )
{
    qDebug()<<Q_FUNC_INFO;
    StylLinkyOld vystup;


    if(linka.isNight==true)
    {
        subMode=subMode+"Night";
    }

    if(linka.isDiversion)
    {
        subMode=subMode+"Diversion";
        //  pozadi="background-color:"+barva_Vyluky_255_170_30+";";
        qDebug()<<"linka je vylukova";
    }
    if(linka.isReplacement)
    {
        subMode=subMode+"Replacement";
    }
    if(linka.isSpecial)
    {
        subMode=subMode+"Special";
    }


    if(barvaPozadi.contains(subMode))
    {
        vystup.pozadi="background-color:"+barvaPozadi[subMode]+";";
    }
    if(barvaTextu.contains(subMode))
    {
        vystup.text="color:"+barvaTextu[subMode]+";";
    }
    qDebug()<<"linka "<<linka.LineName<<" submode "<<subMode;

    return vystup;

}


