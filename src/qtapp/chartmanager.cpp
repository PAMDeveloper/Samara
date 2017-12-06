#include "chartmanager.h"

#include <QCheckBox>
#include <QDate>
#include <QHash>
#include <QtCore/qmath.h>

#include <QtCharts/QDateTimeAxis>
#include <QtCharts/QValueAxis>

#include "utils/juliancalculator.h"

const QString chartDefaultList = "Cstr,CulmsPerHill,DryMatAboveGroundTotPop,DryMatResInternodePop,DryMatStructStemPop,FTSW,GrainYieldPop,Ic,Lai,LeafDeathPop,NumPhase";
const QString chartCompleteList = "ApexHeight,Assim,AssimNotUsed,AssimNotUsedCum,AssimPot,AssimSurplus,CapaREvap,CapaRFE,Conversion,ConversionEff,Cstr,CstrAssim,CstrMean,CstrPhase2,CstrPhase3,CstrPhase4,CstrPhase5,CumRain,CulmsPerHill,CulmsPerHillMax,CulmsPerPlant,CulmsPerPlantMax,CulmsPop,CumCarbonUsedPop,CumDr,CumEt,CumIrrig,CumLr,CumPAR,CumTr,CumWReceived,CumWUse,DayLength,DeadLeafdrywtPop,DegresDuJour,DegresDuJourCor,Density,Dr,DryMatAboveGroundPop,DryMatAboveGroundTotPop,DryMatPanicleTotPop,DryMatResInternodePop,DryMatStructInternodePop,DryMatStructLeafPop,DryMatStructPaniclePop,DryMatStructRootPop,DryMatStructSheathPop,DryMatStructStemPop,DryMatStructTotPop,DryMatTotPop,DryMatVegeTotPop,DurGermFlow,DurGermMat,DurPhase1,DurPhase2,DurPhase3,DurPhase4,DurPhase5,DurPhase6,EauDispo,ETM,ETo,ETP,ETR,Evap,EvapPot,FertSpikeNumPop,FloodwaterDepth,FractionPlantHeightSubmer,FractionRootsLogged,FTSW,FtswPhase2,FtswPhase3,FtswPhase4,FtswPhase5,FtswPhase6,GrainFillingStatus,GrainYieldPanicle,GrainYieldPop,HarvestIndex,HaunIndex,HMax,HMin,HMoy,Hum,Ic,IcMean,IcPhase2,IcPhase3,IcPhase4,IcPhase5,IcPhase6,Ins,InternodeResStatus,Irrigation,IrrigTotDay,Kce,KceReal,Kcl,Kcp,KcTot,Kr,KRolling,Lai,LaiDead,LastLeafLength,LastLeafLengthPot,LeafDeathPop,LIRkdfcl,Lr,LTRkdfcl,MaxLai,MobiliLeafDeath,NumPhase,NurseryStatus,PanicleNumPlant,PanicleNumPop,PanicleSinkPop,PanStructMass,Par,PARIntercepte,PlantHeight,PlantLeafNumTot,PlantWidth,Pluie,ProfRu,ResCapacityInternodePop,ReservePopFin,ResInternodeMobiliDay,ResInternodeMobiliDayPot,RespMaintDebt,RespMaintTot,ResUtil,Rg,RgCalc,RgMax,RootFront,RootMassPerVol,RootShootRatio,RUE,RUEGreen,RuRac,RuSurf,Sla,SpikeNumPanicle,SpikeNumPop,SterilityCold,SterilityDrought,SterilityHeat,SterilityTot,StockMacropores,StockRac,StockSurface,StockTotal,StressCold,SumDegreDayCor,SumDegresDay,SupplyTot,TillerDeathPop,TMax,TMin,TMoy,Tr,TrEff,TrEffInst,TrPot,VitesseRacinaire,VolMacropores,VolRelMacropores,VPDCalc,Vt,WueEt,WueTot";

ChartManager::ChartManager(QGridLayout *chartLayout, QVBoxLayout *chartListLayout, QObject *parent)
    : QObject(parent), chartLayout(chartLayout), chartListLayout(chartListLayout)
{
    chartList = chartCompleteList.split(",");
    defaultList = chartDefaultList.split(",");
    fillList();
}

void ChartManager::fillList() {
    for(QString name: chartList) {
        QCheckBox * chartBox = new QCheckBox(name);
        if(defaultList.contains(name)) {
            chartBox->setChecked(true);
            checkedList.append(name);
        }
        charts.insert(name, createChart(name));
        chartListLayout->addWidget(chartBox);
//        connect(chartBox, SIGNAL(clicked(bool)), this, SLOT(chartClicked(bool)));
    }
}

ChartView * ChartManager::createChart(QString name) {
    QChart *chart = new QChart();
    chart->legend()->hide();
    chart->setTitle(name);
    QDateTimeAxis *axisX = new QDateTimeAxis;
    axisX->setTickCount(10);
    axisX->setFormat("dd MM");
    chart->addAxis(axisX, Qt::AlignBottom);

    QValueAxis *axisY = new QValueAxis;
    axisY->setLabelFormat("%i");
    chart->addAxis(axisY, Qt::AlignLeft);

    ChartView * chartView = new ChartView(chart);
    chartView->setObjectName(name);
}

void ChartManager::displayCharts() {
    for(QString name: chartList) {
//        chartLayout->removeWidget();
//        if(checkedList.contains(name) && chartLayout->parent()->findChild<QWidget*>(name) == 0) {
//            chartLayout->addWidget(charts[name], chartLayout->count() / 2, chartLayout->count() % 2);
//        }
    }
}

void ChartManager::setResults(pair<vector<string>, vector<vector<double> > > results, map<string, vector<double> > observations) {
    clearSeries();
    generateResultSeries(results);
    generateObsSeries(observations);

    for(QString checked: checkedList) {
        QChart * chart = charts[checked]->m_chart;
        if(resultSeries[checked] != nullptr) {
            resultSeries[checked]->attachAxis(chart->axisX());
            resultSeries[checked]->attachAxis(chart->axisY());
            chart->addSeries(resultSeries[checked]);
        }

        if(obsSeries[checked] != nullptr) {
            obsSeries[checked]->attachAxis(chart->axisX());
            obsSeries[checked]->attachAxis(chart->axisY());
            chart->addSeries(obsSeries[checked]);
        }

        chartLayout->addWidget(charts[checked], chartLayout->count() / 2, chartLayout->count() % 2);
    }
}

void ChartManager::clearSeries() {
    for (auto token: resultSeries.toStdMap()) {
        delete token.second;
    }

    for (auto token: obsSeries.toStdMap()) {
        delete token.second;
    }

    resultSeries.clear();
    obsSeries.clear();
}


QColor getColor(QString s) {
    int i = qHash(s) % 256;
    double PHI = (1 + qSqrt(5)) / 2;
    double n = i * PHI - floor(i * PHI);
    int h = qFloor(n * 256);
    return QColor::fromHsv(h, 245, 245, 255);
}

void ChartManager::generateResultSeries(pair <vector <string>, vector < vector <double> > > results) {
    QDateTime date;
    for (int i = 0; i < results.first.size(); ++i) {
        QString name = QString::fromStdString(results.first[i]);
        QLineSeries * serie = new QLineSeries();
        serie->setColor(getColor(name));
        for (int d = 0; d < results.second[i].size(); ++d) {
            string dateStr = JulianCalculator::toStringDate(results.second[0][d], JulianCalculator::YMD, '-');
            date.setDate(QDate::fromString(QString::fromStdString(dateStr),"yyyy-MM-dd"));
            serie->append(date.toMSecsSinceEpoch(), results.second[i][d]);
        }
        resultSeries.insert(name, serie);
    }
}

void ChartManager::generateObsSeries(map<string, vector<double> > observations) {
    QDateTime date;
    for (auto token: observations) {
        QString name = QString::fromStdString(token.first);
        QScatterSeries * serie = new QScatterSeries();
        serie->setColor(getColor(name).darker(100));
        serie->setMarkerSize(5);
        for (int d = 0; d < token.second.size(); ++d) {
            string dateStr = JulianCalculator::toStringDate(observations["Jour"][d], JulianCalculator::YMD, '-');
            date.setDate(QDate::fromString(QString::fromStdString(dateStr),"yyyy-MM-dd"));
            if(token.second[d] != -999)
                serie->append(date.toMSecsSinceEpoch(), token.second[d]);
        }
        obsSeries.insert(name, serie);
    }
}
