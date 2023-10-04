#ifndef BARVYLINEK_H
#define BARVYLINEK_H

#include <QMap>
#include <QString>
#include <QDebug>
#include "VDV301struktury/line.h"



class StylLinkyOld
{
public:
    QString pozadi="";
    QString text="";
};


class BarvyLinek
{
public:
    BarvyLinek();
    void naplnMapBarev();



    //nezarazeno
    QMap<QString, QString> barvaTextu;
    QMap<QString, QString> barvaPozadi;
    //definice barev

    QString barva_PozadiA_25_25_25 ="rgb(25,25,25)";
    QString barva_PozadiB_50_50_50 ="rgb(50,50,50)"; //tmave seda
    QString barva_PozadiC_100_100_100 ="rgb(100,100,100)";
    QString barva_PozadiD_150_150_150 ="rgb(150,150,150)"; //Pozadí D
    QString barva_Zastavka_180_180_180 ="rgb(180,180,180)"; //Zastávka
    QString barva_bila_255_255_255 ="rgb(255,255,255)"; //bila
    QString barva_cerna_0_0_0 ="rgb(0,0,0);"; //bila

    QString barva_Vyluky_255_170_30 ="rgb(255,170,30)";
    QString barva_Cervena_200_0_20 ="rgb(200,0,20)";
    QString barva_CervenaTexty_220_40_40 ="rgb(220,40,40)";
    QString barva_Zelena_210_215_15 ="rgb(210,215,15)";

    QString barva_MetroA_0_165_98 ="rgb(0,165,98)";
    QString barva_MetroB_248_179_34 ="rgb(248,179,34)";
    QString barva_MetroC_207_0_61 ="rgb(207,0,61)";
    QString barva_MetroD_0_140_190 ="rgb(0,140,190)";
    QString barva_Tramvaj_120_2_0 ="rgb(120,2,0)";
    QString barva_Trolejbus_128_22_111 ="rgb(128,22,111)";
    QString barva_Autobus_0_120_160 ="rgb(0,120,160)";
    QString barva_Vlak_15_30_65 ="rgb(15,30,65)";
    QString barva_Lanovka_201_208_34 ="rgb(201,208,34)";
    QString barva_Privoz_0_164_167 ="rgb(0,164,167)";
    QString barva_Nocni_9_0_62 ="rgb(9,0,62)";
    QString barva_Letiste_155_203_234 ="rgb(155,203,234)";
    QString barva_Specialni_143_188_25 ="rgb(143,188,25)";
    
    StylLinkyOld linkaDoStylu(QString &subMode, Line linka);

};

#endif // BARVYLINEK_H
