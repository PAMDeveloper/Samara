/**
 * @file model/models/samara/Model.hpp
 * @author The Samara Development Team
 * See the AUTHORS file
 */

/*
 * Copyright (C) 2010-2014 Cirad http://www.cirad.fr
 * Copyright (C) 2014 ULCO http://www.univ-littoral.fr
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef MODEL_MODELS_SAMARA_MODEL_HPP
#define MODEL_MODELS_SAMARA_MODEL_HPP

#include <model/models/ModelParameters.hpp>
#include <model/models/meteo/Meteo.hpp>

#include <utils/DateTime.hpp>

namespace model { namespace models { namespace samara {

class Model
{
public:
    Model()
    { }

    virtual ~Model()
    { }

    void assignClimate(const model::models::meteo::Climate& climate);

    virtual void compute(double time) = 0;

    void init(const model::models::ModelParameters& parameters);

    double lai() const
    { return Lai; }

    double numphase() const
    { return NumPhase; }

    double degresdujour() const
    { return DegresDuJour; }

    double degresdujourcor() const
    { return DegresDuJourCor; }

    double ftsw() const
    { return FTSW; }

    double cstr() const
    { return Cstr; }

    double rootfront() const
    { return RootFront; }

    double eto() const
    { return Eto; }

    double etm() const
    { return ETM; }

    double etr() const
    { return ETR; }

    double rue() const
    { return RUE; }

    double conversioneff() const
    { return ConversionEff; }

    double ic() const
    { return Ic; }

    double culmsperplant() const
    { return CulmsPerPlant; }

    double culmspop() const
    { return CulmsPop; }

    double culmsperhill() const
    { return CulmsPerHill; }

    double grainyieldpop() const
    { return GrainYieldPop; }

    double drymatstructleafpop() const
    { return DryMatStructLeafPop; }

    double drymatstructsheathpop() const
    { return DryMatStructSheathPop; }

    double drymatstructrootpop() const
    { return DryMatStructRootPop; }

    double drymatstructinternodepop() const
    { return DryMatStructInternodePop; }

    double drymatresinternodepop() const
    { return DryMatResInternodePop; }

    double drymatstructpaniclepop() const
    { return DryMatStructPaniclePop; }

    double drymatstructtotpop() const
    { return DryMatStructTotPop; }

    double drymatvegetotpop() const
    { return DryMatVegeTotPop; }

    double drymatpanicletotpop() const
    { return DryMatPanicleTotPop; }

    double drymatstempop() const
    { return DryMatStemPop; }

    double drymatabovegroundpop() const
    { return DryMatAboveGroundPop; }

    double drymattotpop() const
    { return DryMatTotPop; }

    double sterilitycold() const
    { return SterilityCold; }

    double sterilityheat() const
    { return SterilityHeat; }

    double sterilitydrought() const
    { return SterilityDrought; }

    double sterilitytot() const
    { return SterilityTot; }

    double harvestindex() const
    { return HarvestIndex; }

    double paniclenumpop() const
    { return PanicleNumPop; }

    double paniclenumplant() const
    { return PanicleNumPlant; }

    double grainyieldpanicle() const
    { return GrainYieldPanicle; }

    double spikenumpop() const
    { return SpikeNumPop; }

    double spikenumpanicle() const
    { return SpikeNumPanicle; }

    double fertspikenumpop() const
    { return FertSpikeNumPop; }

    double grainfillingstatus() const
    { return GrainFillingStatus; }

    double phasestemelongation() const
    { return PhaseStemElongation; }

    double sla() const
    { return Sla; }

    double haunindex() const
    { return HaunIndex; }

    double apexheight() const
    { return ApexHeight; }

    double plantheight() const
    { return PlantHeight; }

    double plantwidth() const
    { return PlantWidth; }

    double krolling() const
    { return KRolling; }

    double lirkdfcl() const
    { return LIRkdfcl; }

    double ltrkdfcl() const
    { return LTRkdfcl; }

    double assimpot() const
    { return AssimPot; }

    double assim() const
    { return Assim; }

    double respmainttot() const
    { return RespMaintTot; }

    double supplytot() const
    { return SupplyTot; }

    double assimsurplus() const
    { return AssimSurplus; }

    double assimnotused() const
    { return AssimNotUsed; }

    double tillerdeathpop() const
    { return TillerDeathPop; }

    double plantleafnumtot() const
    { return PlantLeafNumTot; }

    double deadleafdrywtpop() const
    { return DeadLeafDrywtPop; }

    double laidead() const
    { return LaiDead; }

    double rescapacityinternodepop() const
    { return ResCapacityInternodePop; }

    double internoderesstatus() const
    { return InternodeResStatus; }

    double daylength() const
    { return DayLength; }

    double par() const
    { return PAR; }

    double rgcalc() const
    { return RgCalc; }

    double vpdcalc() const
    { return VPD; }

    double tmoycalc() const
    { return TMoyCalc; }

    double hmoycalc() const
    { return HMoyCalc; }

    double kcereal() const
    { return KceReal; }

    double stocktotal() const
    { return StockTotal; }

    double eaudispo() const
    { return EauDispo; }

    double stocksurface() const
    { return StockSurface; }

    double stockrac() const
    { return StockRac; }

    double rurac() const
    { return RuRac; }

    double kcp() const
    { return Kcp; }

    double kce() const
    { return Kce; }

    double evappot() const
    { return EvapPot; }

    double evap() const
    { return Evap; }

    double trpot() const
    { return TrPot; }

    double tr() const
    { return Tr; }

    double lr() const
    { return Lr; }

    double dr() const
    { return Dr; }

    double parintercepte() const
    { return PARIntercepte; }

    double sommedegresjour() const
    { return SommeDegresJour; }

    double vitesseracinaire() const
    { return VitesseRacinaire; }

    double cstrassim() const
    { return CstrAssim; }

    double rayextra() const
    { return RayExtra; }

    double cumpar() const
    { return CumPar; }

    double sommedegresjourcor() const
    { return SommeDegresJourCor; }

    double sumpp() const
    { return SumPP; }

    double sommedegresjourphaseprecedente() const
    { return SommeDegresJourPhasePrecedente; }

    double respmaintdebt() const
    { return RespMaintDebt; }

    double tminmoy() const
    { return TMinMoy; }

    double tmaxmoy() const
    { return TMaxMoy; }

    double ftswmoy() const
    { return FtswMoy; }

    double rootshootratio() const
    { return RootShootRatio; }

    double treffinst() const
    { return TrEffInst; }

    double treff() const
    { return TrEff; }

    double wueet() const
    { return WueEt; }

    double wuetot() const
    { return WueTot; }

    double floodwaterdepth() const
    { return FloodwaterDepth; }

    double irrigautoday() const
    { return IrrigAutoDay; }

    double irrigtotday() const
    { return IrrigTotDay; }

    double fractionplantheightsubmer() const
    { return FractionPlantHeightSubmer; }

    double density() const
    { return Density; }

    double rootmasspervol() const
    { return RootMassPerVol; }

    double volmacropores() const
    { return VolMacropores; }

    double stockmacropores() const
    { return StockMacropores; }

    double relpotleaflength() const
    { return RelPotLeafLength; }

    double apexheightgain() const
    { return ApexHeightGain; }

    double haungain() const
    { return HaunGain; }

    double conversion() const
    { return Conversion; }

    double stresscold() const
    { return StressCold; }

    double fractionrootslogged() const
    { return FractionRootsLogged; }

    double resutil() const
    { return ResUtil; }

    double kctot() const
    { return KcTot; }

    double nbjas() const
    { return NbJas; }

    double NullValue;


    // parameters
    double Altitude;
    double ASScstr;
    double AttenMitch;
    double BundHeight;
    double Ca;
    double CO2Cp;
    double CO2Exp;
    double CoeffAssimSla;
    double CoefficientQ10;
    double CoeffInternodeMass;
    double CoeffInternodeNum;
    double CoeffLeafDeath;
    double CoeffLeafWLRatio;
    double CoeffPanicleMass;
    double CoeffPanSinkPop;
    double CoeffResCapacityInternode;
    double CoeffReserveSink;
    double CoeffRootMassPerVolMax;
    double CoeffTillerDeath;
    double CoeffTransplantingShock;
    double DensityField;
    double DensityNursery;
    double DEVcstr;
    double DurationNursery;
    double EpaisseurProf;
    double EpaisseurSurf;
    double ExcessAssimToRoot;
    double FTSWIrrig;
    double HaunCritTillering;
    double HumFC;
    double HumPF;
    double HumSat;
    double IcTillering;
    double InternodeLengthMax;
    double IrrigAutoResume;
    double IrrigAutoStop;
    double IrrigAutoTarget;
    double KcMax;
    double KCritSterCold1;
    double KCritSterCold2;
    double KCritSterFtsw1;
    double KCritSterFtsw2;
    double KCritSterHeat1;
    double KCritSterHeat2;
    double KCritStressCold1;
    double KCritStressCold2;
    double Kdf;
    double KRespInternode;
    double KRespMaintLeaf;
    double KRespMaintRoot;
    double KRespMaintSheath;
    double KRespPanicle;
    double KTempMaint;
    double Latitude;
    double LeafLengthMax;
    double LifeSavingDrainage;
    double Mulch;
    double PanStructMassMax;
    double PercolationMax;
    double PFactor;
    double Phyllo;
    double PlantsPerHill;
    double PlotDrainageDAF;
    double PoidsSecGrain;
    double PourcRuiss;
    double PPCrit;
    double PPExp;
    double PriorityPan;
    double ProfRacIni;
    double RankLongestLeaf;
    double RelMobiliInternodeMax;
    double RollingBase;
    double RollingSens;
    double RootCstr;
    double RootFrontMax;
    double RootPartitMax;
    double SDJBVP;
    double SDJLevee;
    double SDJMatu1;
    double SDJMatu2;
    double SDJRPR;
    double SeuilPP;
    double SeuilRuiss;
    double SlaMax;
    double SlaMin;
    double StockIniProf;
    double StockIniSurf;
    double TBase;
    double TempSla;
    double TilAbility;
    double TLet;
    double TOpt1;
    double TOpt2;
    double TransplantingDepth;
    double TxAssimBVP;
    double TxAssimMatu1;
    double TxAssimMatu2;
    double TxConversion;
    double TxResGrain;
    double TxRuSurfGermi;
    double VRacBVP;
    double VRacLevee;
    double VRacMatu1;
    double VRacMatu2;
    double VRacPSP;
    double VRacRPR;
    double WaterLoggingSens;
    double WtRatioLeafSheath;
    int IrrigAuto;
    int Transplanting;

    // state variables
    double A_AssimSurplus;
    double A_DemStructLeaf;
    double A_DemStructTot;
    double A_GrowthStructLeaf;
    double A_GrowthStructTot;
    double A_IncreaseResInternodePop;
    double ApexHeight;
    double ApexHeightGain;
    double A_ResInternodeMobiliDay;
    double Assim;
    double AssimNotUsed;
    double AssimNotUsedCum;
    double AssimPot;
    double AssimSurplus;
    double CapaRDE;
    double CapaREvap;
    double CapaRFE;
    double ChangePhase;
    double ChangeSousPhase;
    double CO2SlopeTr;
    double CoeffCO2Assim;
    double CoeffCO2Tr;
    double CoeffStressLogging;
    double Conversion;
    double ConversionEff;
    double CounterNursery;
    double Cstr;
    double CstrAssim;
    double CstrCumul;
    double CstrMean;
    double CstrPhase2;
    double CstrPhase3;
    double CstrPhase4;
    double CstrPhase5;
    double CstrPhase6;
    double CulmsPerHill;
    double CulmsPerHillFin;
    double CulmsPerHillMax;
    double CulmsPerPlant;
    double CulmsPerPlantFin;
    double CulmsPerPlantMax;
    double CulmsPop;
    double CumCarbonUsedPop;
    double CumCstrPhase2;
    double CumCstrPhase3;
    double CumCstrPhase4;
    double CumCstrPhase5;
    double CumCstrPhase6;
    double CumDr;
    double CumEt;
    double CumFtswPhase2;
    double CumFtswPhase3;
    double CumFtswPhase4;
    double CumFtswPhase5;
    double CumFtswPhase6;
    double CumGrowthPop;
    double CumIcPhase2;
    double CumIcPhase3;
    double CumIcPhase4;
    double CumIcPhase5;
    double CumIcPhase6;
    double CumIrrig;
    double CumIrrigFin;
    double CumLr;
    double CumPar;
    double CumSupplyTot;
    double CumTr;
    double CumWReceived;
    double CumWuse;
    double CumWUse;
    double CumWUseFin;
    double DAF;
    double DateSemis;
    double DayLength;
    double DeadLeafDrywtPop;
    double Decli;
    double DegresDuJour;
    double DegresDuJourCor;
    double DemLeafAreaPlant;
    double DemPanicleFillPop;
    double DemResInternodePop;
    double DemStructInternodePlant;
    double DemStructInternodePop;
    double DemStructLeafPlant;
    double DemStructLeafPop;
    double DemStructPaniclePlant;
    double DemStructPaniclePop;
    double DemStructRootPlant;
    double DemStructRootPop;
    double DemStructSheathPop;
    double DemStructTotPop;
    double Density;
    double Dr;
    double DryMatAboveGroundPop;
    double DryMatAboveGroundPopFin;
    double DryMatAboveGroundTotPop;
    double DryMatPanicleTotPop;
    double DryMatResInternodePop;
    double DryMatResInternodePopOld;
    double DryMatStemPop;
    double DryMatStructInternodePop;
    double DryMatStructLeafPop;
    double DryMatStructPaniclePop;
    double DryMatStructRootPop;
    double DryMatStructSheathPop;
    double DryMatStructStemPop;
    double DryMatStructTotPop;
    double DryMatTotPop;
    double DryMatTotPopFin;
    double DryMatVegeTotPop;
    double DureeDuJour;
    double DurGermFlow;
    double DurGermMat;
    double DurPhase1;
    double DurPhase2;
    double DurPhase3;
    double DurPhase4;
    double DurPhase5;
    double DurPhase6;
    double EauDispo;
    double ETM;
    double Eto;
    double ETP;
    double ETR;
    double Evap;
    double EvapPot;
    double FertSpikeNumPop;
    double FertSpikePop;
    double FloodwaterDepth;
    double FloodWaterGain;
    double FractionPlantHeightSubmer;
    double FractionRootsLogged;
    double FTSW;
    double FtswMoy;
    double FtswPhase2;
    double FtswPhase3;
    double FtswPhase4;
    double FtswPhase5;
    double FtswPhase6;
    double GainRootSystSoilSurfPop;
    double GainRootSystVolPop;
    double GrainFillingStatus;
    double GrainFillingStatusFin;
    double GrainYieldPanicle;
    double GrainYieldPop;
    double GrainYieldPopFin;
    double GrowthDryMatPop;
    double GrowthPop;
    double GrowthResInternodePop;
    double GrowthStructDeficit;
    double GrowthStructInternodePop;
    double GrowthStructLeafPop;
    double GrowthStructPaniclePop;
    double GrowthStructRootPop;
    double GrowthStructSheathPop;
    double GrowthStructTotPop;
    double HarvestIndex;
    double HaunGain;
    double HaunIndex;
    double HMax;
    double HMin;
    double HMoy;
    double HMoyCalc;
    double Hum;
    double Ic;
    double IcCumul;
    double IcMean;
    double IcPhase2;
    double IcPhase3;
    double IcPhase4;
    double IcPhase5;
    double IcPhase6;
    double IncreaseResInternodePop;
    double Ins;
    double InternodeResStatus;
    double Irrigation;
    double IrrigAutoDay;
    double IrrigTotDay;
    double Kce;
    double KceReal; // parameter ????
    double Kcl;
    double Kcp;
    double KcTot;
    double KPar;
    double Kr;
    double KRolling;
    double Lai;
    double LaiDead;
    double LaiFin;
    double LastLeafLength; // parameter ???
    double LastLeafLengthPot; // parameter ???
    double LatRad;
    double LeafDeathPop;
    double LIRkdf;
    double LIRkdfcl;
    double Lr;
    double LTRkdf;
    double LTRkdfcl;
    double MaximumLai;
    double MobiliLeafDeath;
    double MonCompteur;
    double NbDaysSinceGermination;
    double NbJas;
    double NumPhase;
    double NumSousPhase;
    double PanicleFilDeficit;
    double PanicleFilPop;
    double PanicleNumPlant;
    double PanicleNumPop;
    double PanicleSinkPop;
    double PanStructMass;
    double PAR;
    double PARIntercepte;
    double PEvap;
    double PhaseStemElongation;
    double PlantHeight;
    double PlantLeafNumNew;
    double PlantLeafNumTot;
    double PlantWidth;
    double PPSens;
    double ProfRu;
    double Rain;
    double RayExtra;
    double RelPhylloPhaseStemElong;
    double RelPotLeafLength;
    double ResCapacityInternodePop;
    double ReservePopFin;
    double ResInternodeMobiliDay;
    double ResInternodeMobiliDayPot;
    double RespMaintDebt;
    double RespMaintTot;
    double ResUtil;
    double Rg;
    double RgCalc;
    double RgMax;
    double RootFront;
    double RootFrontOld;
    double RootMassPerVol;
    double RootShootRatio;
    double RootSystSoilSurfPop;
    double RootSystSoilSurfPopOld;
    double RootSystVolPop;
    double RootSystVolPopOld;
    double RUE;
    double RUEgreen;
    double RuRac;
    double RuSurf;
    double SDJCorPhase4;
    double SeuilCstrMortality;
    double SeuilTempPhasePrec;
    double SeuilTempPhaseSuivante;
    double SeuilTempSousPhaseSuivante;
    double SimAnthesis50;
    double SimEmergence;
    double SimEndCycle;
    double SimPanIni;
    double SimStartGermin;
    double SimStartMatu2;
    double SimStartPSP;
    double Sla;
    double SlaMitch;
    double SlaNew;
    double SommeDegresJour;
    double SommeDegresJourCor;
    double SommeDegresJourMaximale;
    double SommeDegresJourPhasePrecedente;
    double SpikeNumPanicle;
    double SpikeNumPop;
    double SterilityCold;
    double SterilityDrought;
    double SterilityHeat;
    double SterilityTot;
    double SterilityTotFin;
    double StockMacropores;
    double StockRac;
    double StockSurface;
    double StockTotal;
    double StressCold;
    double StRu;
    double StRuMax;
    double SumPP;
    double SunDistance;
    double SunPosi;
    double SupplyTot;
    double tabCstr[5];
    double TempLai;
    double TillerDeathPop;
    double TMax;
    double TMaxMoy;
    double TMin;
    double TMinMoy;
    double TMoy;
    double TMoyCalc;
    double TMoyPrec;
    double Tr;
    double TrEff;
    double TrEffInst;
    double TrPot;
    double ValRDE;
    double ValRFE;
    double ValRSurf;
    double Vent;
    double VitesseRacinaire;
    double VitesseRacinaireDay;
    double VolMacropores;
    double VolRelMacropores;
    double VPD;
    double WueEt;
    double WueTot;
    int ChangeNurseryStatus;
    int ChangeSsPhase;
    int NbJourCompte;
    int NurseryStatus;
    int tabCstrIndiceCourant;

protected:
    void initCrop();
    void degToRad();
    void avgTempHum();
    void evalDecli(double t);
    void evalSunPosi();
    void evalDayLength();
    void evalSunDistance(double t);
    void evalRayExtra();
    void evalRgMax();
    void insToRg();
    void evalPAR();
    void etoFAO();
    void evolPhenoStress(double t);
    void evalTranspi();
    void evalETRETM();
    void evalConversion();
    void evolSomDegresJour();
    void mortality();
    void evalSimAnthesis50();
    void evalDateGermination();
    void evalColdStress();
    void evalSimEmergence();
    void evalSimPanIni();
    void evalSimStartGermin();
    void evalSimStartMatu2();
    void evalSimStartPSP();
    void evalSDJPhase4();
    void phyllochron();
    void evolKcpKceBilhy();
    void evalEvapPot();
    void evalTMaxMoy();
    void evalTMinMoy();
    void evalFtswMoy();
    void evalSterility();
    void evalVitesseRacinaire();
    void evalCstrAssim();
    void evalAssim();
    void evalRespMaint();
    void evalRelPotLeafLength();
    void evolPlantLeafNumTot();
    void evalDemandStructSheath();
    void evolGrowthStructSheathPop();
    void evolGrowthStructRootPop();
    void evolGrowthStructPanPop();
    void evalMaximumLai();
    void evalSlaMitch();
    void evalRootFront();
    void evolPSPMVMD(double t);
    void evolSomDegresJourCor();
    void evalNbJas(double t);

    double calculeLaMoyenne(double laValeur, double leCompteur, double laMoyenne);

};

} } } // namespace model models samara

#endif
