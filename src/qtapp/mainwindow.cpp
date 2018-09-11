#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QtCharts/QChartView>
#include <QtCore/QDateTime>
#include <QtCharts/QDateTimeAxis>
#include <QtCharts/QValueAxis>
#include <QtCore/QFile>
#include <QtCore/QTextStream>
#include <QtCore/QDebug>

#include <QtCore/qmath.h>
#include <QMap>
#include <QDesktopWidget>
#include <QVBoxLayout>

#include <QTabWidget>
#include <QDir>
#include <QCheckBox>
#include <QFileDialog>
#include <QMessageBox>

#include <samara.h>
#include <qtapp/chartview.h>
#include <utils/juliancalculator.h>
#include <utils/de.h>
#include <utils/samarafitness.h>


#include <cmath>

#include <QDebug>

static const int numCol = 2;


const QString shortParamList = "CoeffLodging,StemPorosity,BundHeight,Ca,CoeffInternodeMass,CoeffLeafDeath,CoeffLeafWLRatio,CoeffPanicleMass,CoeffTillerDeath,CoeffTransplantingShock,DatesSemis,DensityField,DensityNursery,DurationNursery,EpaisseurProf,EpaisseurSurf,FtswIrrig,HumCR,HumFC,HumPF,HumSat,InternodeLengthMax,IrrigAuto,IrrigAutoResume,IrrigAutoStop,IrrigAutoTarget,KcMax,LeafLengthMax,LifeSavingDarainage,Mulch,PARCritSLA,PercolationMax,PEvap,PFactor,Phyllo,PlantsPerHill,PlotDrainageDAF,PoidsSecGrain,PourcRuiss,PPSens,ProfRacIni,RootFrontMax,RU,SDJBVP,SeuilRuiss,StockIniProf,StockIniSurf,TilAbility,Transplanting,TransplantingDepth,TxConversion";

QStringList fromVector(vector<string> list) {
    QStringList r;
    for (int i = 0; i < list.size(); ++i) {
        r << QString::fromStdString(list[i]);
    }
    //    r.sort();
    return r;
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    settings = new QSettings("PAM Cirad", "Samara");

    ui->setupUi(this);
    setWindowTitle( QCoreApplication::applicationName() );
    ui->modelCombo->addItem("Samara 2.1");
    ui->modelCombo->addItem("Samara 2.1 michael");
    ui->modelCombo->addItem("Samara 2.3");
    ui->modelCombo->addItem("Samara 2.3 lodging");
    ui->modelCombo->addItem("Samara 2.3 lodging test");
    ui->modelCombo->setCurrentText(settings->value("Samara_version","Samara 2.3").toString());

    ui->splitter->setStretchFactor(0, 0);
    ui->splitter->setStretchFactor(1, 1);

    resultsModel = new ResultsDataModel();
    ui->resultsTableView->setModel(resultsModel);

    resultsManager = new ResultsManager(ui->resultsTableView, resultsModel);
    connect(ui->colFilterCheckbox, SIGNAL(toggled(bool)), resultsManager, SLOT(filterColumns(bool)));
    connect(ui->phaseFilterCheckbox, SIGNAL(toggled(bool)), resultsManager, SLOT(filterPhases(bool)));
    connect(ui->filterColLineEdit, SIGNAL(textChanged(QString)), resultsManager, SLOT(filterColHeaders(QString)));

    SamaraParameters * paramsSam = new SamaraParameters();
    loader = new DBAccessLoader(paramsSam);
    loadDB(settings->value("SamaraDB_path").toString());

    createChartsTab();
    chartManager = new ChartManager(chartLayout, chartListLayout);
    connect(ui->selectAllBox, SIGNAL(clicked(bool)), chartManager, SLOT(selectAll(bool)));
    connect(ui->selectDefaultBox, SIGNAL(clicked(bool)), chartManager, SLOT(selectDefault(bool)));
    connect(ui->sowingButton, SIGNAL(clicked(bool)), chartManager, SLOT(fromSowing(bool)));

    comparisonManager = new ComparisonManager();

    int log = settings->value("SamaraSimulation_LOG", 0).toInt();
    if(log == 0) ui->smallRadio->setChecked(true);
    else if(log == 1) ui->completeRadio->setChecked(true);
    else ui->ecotropRadio->setChecked(true);

    obsmodel = new ObsDataModel();
//    ui->obsTable->setModel(obsmodel);

    ui->meteoTableView->horizontalHeader()->setSectionsMovable(true);
    //**//
//    ui->samaraTabs->removeTab(2);
    //**//
//    on_launchButton_clicked();
//    loadRefFile("D:/PAMStudio/dev/git/build-Samara-Desktop_Qt_5_9_1_MSVC2015_64bit-Release/Sortie Ecotrop.txt");
//    loadRefFile("D:/PAMStudio/dev/git/build-Samara-Desktop_Qt_5_9_1_MSVC2015_64bit-Release/test_621b.txt");
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_actionLoad_database_triggered()
{
    QString dirPath = settings->value("SamaraDB_folder", QDir::currentPath()).toString();
    QString filePath = QFileDialog::getOpenFileName(this, "Open database", dirPath , "Access DB (*.mdb *.accdb)");
    if(filePath.isEmpty()) return;

    settings->setValue("SamaraDB_path", filePath);
    settings->setValue("SamaraDB_folder", QFileInfo(filePath).absoluteDir().absolutePath());
    loadDB(filePath);
}

void MainWindow::loadDB(QString filePath) {
    if(filePath.isEmpty()) return;
    if(!QFileInfo(filePath).exists()) return;

    clearDBContext();
    loader->openDb(filePath);
    fillDBCombos();
}

void MainWindow::fillDBCombos() {
    ui->varComboBox->blockSignals(true);
    ui->plotComboBox->blockSignals(true);
    ui->stationComboBox->blockSignals(true);
    ui->itinComboBox->blockSignals(true);
    ui->simComboBox->blockSignals(true);
    ui->varComboBox->addItems(fromVector(loader->load_variety_list()));
    ui->plotComboBox->addItems(fromVector(loader->load_plot_list()));
    ui->stationComboBox->addItems(fromVector(loader->load_station_list()));
    ui->itinComboBox->addItems(fromVector(loader->load_itinerary_list()));
    ui->simComboBox->addItems(fromVector(loader->load_simulation_list()));
    ui->simComboBox->setCurrentText(settings->value("SamaraSimulation_Text", ui->simComboBox->itemText(0)).toString());
    loader->load_complete_simulation(ui->simComboBox->currentText().toStdString());
    ui->varComboBox->setCurrentText(QString::fromStdString(loader->parameters->getString("variety")));
    ui->plotComboBox->setCurrentText(QString::fromStdString(loader->parameters->getString("fieldcode")));
    ui->itinComboBox->setCurrentText(QString::fromStdString(loader->parameters->getString("itkcode")));
    ui->stationComboBox->setCurrentText(QString::fromStdString(loader->parameters->getString("wscode")));
    ui->varComboBox->blockSignals(false);
    ui->plotComboBox->blockSignals(false);
    ui->stationComboBox->blockSignals(false);
    ui->itinComboBox->blockSignals(false);
    ui->simComboBox->blockSignals(false);
    showDates();
    showParameters(loader->parameters);
}


void MainWindow::clearDBContext() {
    delete ui->parametersTableView->model();
    delete ui->meteoTableView->model();

    results.first.clear();
    results.second.clear();
    resultsModel->setResults(results);

    ui->varComboBox->clear();
    ui->plotComboBox->clear();
    ui->stationComboBox->clear();
    ui->itinComboBox->clear();
    ui->simComboBox->clear();
}

void MainWindow::on_launchButton_clicked() {

//    settings->setValue("SamaraSimulation_Text", ui->simComboBox->currentText());
//    Samara::SamaraLogType log = (Samara::SamaraLogType)(ui->smallRadio->isChecked() ? 0 : ui->completeRadio->isChecked() ? 1 : 2);
//    settings->setValue("SamaraSimulation_LOG", log);
//    QString version = ui->modelCombo->currentText();
//    settings->setValue("Samara_version", version);
//    for (int i = 0; i < 10000000; ++i) {
//        Samara samara;
//        results = samara.run_samara_2_1(loader->parameters, log);
//        if(i%100 == 0)
//            qDebug() << i;

//    }
//    return;


    Samara samara;
    settings->setValue("SamaraSimulation_Text", ui->simComboBox->currentText());
    Samara::SamaraLogType log = (Samara::SamaraLogType)(ui->smallRadio->isChecked() ? 0 : ui->completeRadio->isChecked() ? 1 : 2);
    settings->setValue("SamaraSimulation_LOG", log);
    QString version = ui->modelCombo->currentText();
    settings->setValue("Samara_version", version);
    if(version == "Samara 2.1")
        results = samara.run_samara_2_1(loader->parameters, log);
    else if(version == "Samara 2.1 michael")
        results = samara.run_samara_2_1_micha(loader->parameters, log);
    else if(version == "Samara 2.3")
        results = samara.run_samara_2_3(loader->parameters, log);
    else if(version == "Samara 2.3 lodging")
        results = samara.run_samara_2_3_lodging(loader->parameters, log);
    else if(version == "Samara 2.3 lodging test")
        results = samara.run_samara_2_3_lodging_test(loader->parameters, log);

    resultsModel->setResults(results);
    ui->resultsTableView->reset();
    observations = loader->load_obs("");
    obsmodel->setObs(observations);
    chartManager->setResults(results, observations, loader->parameters->getDouble("startingdate"), loader->parameters->getDouble("sowing"));
//    QMessageBox::information(this, "Simulation", "Simulation and charting done.");
}

void MainWindow::showDates() {
    string sStart = JulianCalculator::toStringDate(loader->parameters->getDouble("startingdate"),
                                                   JulianCalculator::YMD, '-');
    string sEnd = JulianCalculator::toStringDate(loader->parameters->getDouble("endingdate"),
                                                   JulianCalculator::YMD, '-');

    QDate start = QDate::fromString(QString::fromStdString(sStart),"yyyy-MM-dd");
    QDate end = QDate::fromString(QString::fromStdString(sEnd),"yyyy-MM-dd");
    ui->startDateEdit->blockSignals(true);
    ui->startDateEdit->setDate(start);
    ui->startDateEdit->blockSignals(false);
    ui->endDateEdit->blockSignals(true);
    ui->endDateEdit->setDate(end);
    ui->endDateEdit->blockSignals(false);
}

void MainWindow::on_simComboBox_currentTextChanged(const QString &arg1) {
    loader->load_simulation(arg1.toStdString());
    showDates();
    ui->varComboBox->setCurrentText(QString::fromStdString(loader->parameters->getString("variety")));
    ui->plotComboBox->setCurrentText(QString::fromStdString(loader->parameters->getString("fieldcode")));
    ui->itinComboBox->setCurrentText(QString::fromStdString(loader->parameters->getString("itkcode")));
    ui->stationComboBox->setCurrentText(QString::fromStdString(loader->parameters->getString("wscode")));
}

void MainWindow::on_varComboBox_currentTextChanged(const QString &arg1) {
    loader->load_variety(arg1.toStdString());
    showParameters(loader->parameters);
}

void MainWindow::on_stationComboBox_currentTextChanged(const QString &arg1) {
    loader->load_station(arg1.toStdString());
    loader->load_meteo(arg1.toStdString(), loader->parameters->getDouble("startingdate"),
                       loader->parameters->getDouble("endingdate"));
    showParameters(loader->parameters);
}

void MainWindow::on_plotComboBox_currentTextChanged(const QString &arg1) {
    loader->load_plot(arg1.toStdString());
    showParameters(loader->parameters);
}

void MainWindow::on_itinComboBox_currentTextChanged(const QString &arg1) {
    loader->load_itinerary(arg1.toStdString());
    showParameters(loader->parameters);
}

void MainWindow::on_startDateEdit_dateChanged(const QDate &date) {
    loader->parameters->doubles["startingdate"].first = date.toJulianDay();
    loader->parameters->strings["startingdate"].first = date.toString("yyyy-MM-dd").toStdString();
    loader->load_meteo(ui->stationComboBox->currentText().toStdString(),
                       loader->parameters->getDouble("startingdate"),
                       loader->parameters->getDouble("endingdate"));
    showParameters(loader->parameters);
}

void MainWindow::on_endDateEdit_dateChanged(const QDate &date) {
    loader->parameters->doubles["endingdate"].first = date.toJulianDay();
    loader->parameters->strings["endingdate"].first = date.toString("yyyy-MM-dd").toStdString();
    loader->load_meteo(ui->stationComboBox->currentText().toStdString(),
                       loader->parameters->getDouble("startingdate"),
                       loader->parameters->getDouble("endingdate"));
    showParameters(loader->parameters);
}


void MainWindow::showParameters(SamaraParameters *parameters) {
    if(ui->parametersTableView->model() != nullptr)
        delete ui->parametersTableView->model();

    paramModel = new ParametersDataModel(parameters);
    ui->parametersTableView->setModel(paramModel);
    for (int row = 0; row < paramModel->rowCount(); ++row) {
        if(paramModel->index(row, 0).data().toString().contains("date"))
            ui->parametersTableView->hideRow(row);
    }

    estimModel = new EstimParamDataModel(parameters);
    ui->paramToEstimList->setModel(estimModel);
    for (int row = 0; row < estimModel->rowCount(); ++row) {
        if(estimModel->index(row, 0).data().toString().contains("date"))
            ui->paramToEstimList->hideRow(row);
    }

    if(ui->meteoTableView->model() != nullptr)
        delete ui->meteoTableView->model();
    meteoModel = new MeteoDataModel(parameters);
    ui->meteoTableView->setModel(meteoModel);


}


void MainWindow::on_saveResultButton_clicked() {
    QString dirPath = settings->value("SamaraResult_folder", QDir::currentPath()).toString();
    QString selectedFilter;
    QString filePath = QFileDialog::getSaveFileName(
                this, "Save results as csv", dirPath , "csv tab separated (*.csv);;csv semicolon separated (*.csv)",&selectedFilter);
    if(filePath.isEmpty()) return;
    settings->setValue("SamaraResult_folder", filePath);
    QString sep = (selectedFilter == "csv tab separated (*.csv)" ? "\t" : ";");
    resultsModel->save(filePath, sep);
}


void MainWindow::createChartsTab() {
    QWidget *client = new QWidget();
    ui->scrollArea_2->setWidget(client);
    ui->scrollArea_2->setWidgetResizable(true);
    chartLayout = new QGridLayout();
    client->setLayout(chartLayout);
    chartLayout->setSpacing(0);
    QWidget *client2 = new QWidget();
    ui->scrollArea->setWidget(client2);
    ui->scrollArea->setWidgetResizable(true);
    chartListLayout = new QVBoxLayout();
    client2->setLayout(chartListLayout);
    chartListLayout->setSpacing(0);
}

void MainWindow::on_actionSave_Parameters_triggered()
{
    QString dirPath = settings->value("SamaraParams_folder", QDir::currentPath()).toString();
    QString selectedFilter;
    QString filePath = QFileDialog::getSaveFileName(
                this, "Save parameters as csv", dirPath , "csv tab separated (*.csv);;csv semicolon separated (*.csv)",&selectedFilter);
    if(filePath.isEmpty()) return;
    settings->setValue("SamaraParams_folder", filePath);
    QString sep = (selectedFilter == "csv tab separated (*.csv)" ? "\t" : ";");
    paramModel->save(filePath, sep);
}

void MainWindow::on_actionSave_Meteo_triggered()
{
    QString dirPath = settings->value("SamaraParams_folder", QDir::currentPath()).toString();
    QString selectedFilter;
    QString filePath = QFileDialog::getSaveFileName(
                this, "Save meteo as csv", dirPath , "csv tab separated (*.csv);;csv semicolon separated (*.csv)",&selectedFilter);
    if(filePath.isEmpty()) return;
    settings->setValue("SamaraParams_folder", filePath);
    QString sep = (selectedFilter == "csv tab separated (*.csv)" ? "\t" : ";");
    meteoModel->save(filePath, sep);
}


void MainWindow::on_actionLoad_Parameters_triggered()
{
    QString dirPath = settings->value("SamaraParams_folder", QDir::currentPath()).toString();
    QString selectedFilter;
    QString filePath = QFileDialog::getOpenFileName(
                this, "Load parameters as csv", dirPath , "csv tab separated (*.csv);;csv semicolon separated (*.csv)",&selectedFilter);
    if(filePath.isEmpty()) return;
    settings->setValue("SamaraParams_folder", filePath);
    QString sep = (selectedFilter == "csv tab separated (*.csv)" ? "\t" : ";");
    paramModel->load(filePath, sep);
//    for (int row = 0; row < paramModel->rowCount(); ++row) {
//        QString key = paramModel->index(row, 0).data().toString();
//        if(key.contains("date")) {
//            QString val = paramModel->index(row, 1).data().toString();
//            QDate d = QDate::fromString(val,"yyyy-MM-dd");
//            if(key == "startingdate") ui->startDateEdit->setDate(d);
//            else if(key == "endingdate") ui->endDateEdit->setDate(d);
//            ui->parametersTableView->hideRow(row);
//        }
//    }

    showDates();
    ui->varComboBox->blockSignals(true);
    ui->plotComboBox->blockSignals(true);
    ui->stationComboBox->blockSignals(true);
    ui->itinComboBox->blockSignals(true);
    ui->simComboBox->blockSignals(true);
    ui->simComboBox->setCurrentText(QString::fromStdString(loader->parameters->getString("simcode")));
    ui->varComboBox->setCurrentText(QString::fromStdString(loader->parameters->getString("variety")));
    ui->plotComboBox->setCurrentText(QString::fromStdString(loader->parameters->getString("fieldcode")));
    ui->itinComboBox->setCurrentText(QString::fromStdString(loader->parameters->getString("itkcode")));
    ui->stationComboBox->setCurrentText(QString::fromStdString(loader->parameters->getString("wscode")));
    ui->varComboBox->blockSignals(false);
    ui->plotComboBox->blockSignals(false);
    ui->stationComboBox->blockSignals(false);
    ui->itinComboBox->blockSignals(false);
    ui->simComboBox->blockSignals(false);
    loader->load_meteo(loader->parameters->getString("wscode"),
                       loader->parameters->getDouble("startingdate"),
                       loader->parameters->getDouble("endingdate"));
    showParameters(loader->parameters);
}




/************* COMPARISON ***************/



serieCompare MainWindow::compareSeries(QLineSeries * src, QScatterSeries * /*ref*/) {
    serieCompare comparison;
    comparison.maxVal = -999999999999999;
    comparison.minVal = 999999999999999;
    comparison.sumSrc = 0;
    comparison.sumRef = 0;
    comparison.diffStep = -1;
    comparison.diffPercent = 1;
    comparison.valid = true;

    //    if(src == NULL || ref == NULL) {
    //        comparison.valid = false;
    //        return comparison;
    //    }

    int serieSize = src->count();

    for (int i = 0; i < serieSize; ++i) {
        double srcVal = src != NULL ? src->at(i).y() : 0;
        //        double refVal = ref != NULL ? ref->at(i).y() : 0;
        if (srcVal > comparison.maxVal) comparison.maxVal = srcVal;
        if (srcVal < comparison.minVal) comparison.minVal = srcVal;
        comparison.sumSrc += srcVal;
        //        if (refVal > comparison.maxVal) comparison.maxVal = refVal;
        //        if (refVal < comparison.minVal) comparison.minVal = refVal;
        //        comparison.sumRef += refVal;

        //        if( std::abs((srcVal-refVal)/refVal) > 0.0001 && comparison.diffStep == -1 ) comparison.diffStep = i;
    }
    //    comparison.diffPercent = ((comparison.sumRef-comparison.sumSrc)/comparison.sumRef) * 100;
    return comparison;
}

void MainWindow::sectionClicked(int row) {
    int count = 0;
    QString arg1 = ui->lineEdit->text();
    for(int i = comparisonModel->columnCount() - 1; i >= 0 ; i--){
        bool isInStrFilter = !arg1.isEmpty() &&
                comparisonModel->headerData(i, Qt::Horizontal, Qt::DisplayRole).toString().startsWith(arg1, Qt::CaseInsensitive);
        if(
//                comparisonModel->index(row, i).data(Qt::UserRole).toDouble() < 10/comparisonModel->precision
                comparisonModel->index(row, i).data(Qt::UserRole).toBool()
                && !isInStrFilter) {
            ui->comparisonTableView->hideColumn(i);
        } else {
            ui->comparisonTableView->showColumn(i);
            count++;
        }
    }
    ui->comparisonTableView->resizeColumnsToContents();
    ui->diffCountLabel->setText(QString::number(count) + " diffs.");
}

void MainWindow::on_pushButton_2_clicked()
{
    for(int i = comparisonModel->columnCount() - 1; i >= 0 ; i--){
        ui->comparisonTableView->showColumn(i);
    }
    ui->diffCountLabel->setText("");
}


void MainWindow::loadRefFile(QString fileName){
    QFile inputFile(fileName);
    vector < vector <double> > values;
    vector <string> names;
    if (inputFile.open(QIODevice::ReadOnly))
    {
        QTextStream in(&inputFile);
        QStringList list = in.readLine().split('\t');
        for(QString header: list) {
            names.push_back(header.toLower().toStdString());
            values.push_back(vector<double>());
        }

        while (!in.atEnd())
        {
            list = in.readLine().split('\t');
            for (int i = 0; i < list.size(); ++i) {
                values[i].push_back(list[i].replace(',','.').toDouble());
            }
        }
        inputFile.close();
    }
    comparisonModel = new ComparisonDataModel2(
                results,
                pair <vector <string>, vector < vector <double> > > (names, values)
                );
    ui->comparisonTableView->setModel(comparisonModel);
//    ui->comparisonTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
//    ui->comparisonTableView->
    connect(ui->comparisonTableView->verticalHeader(), SIGNAL(sectionClicked(int)), this, SLOT(sectionClicked(int)));
}

void MainWindow::on_oldResButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Open results");
    loadRefFile(fileName);
}


bool startWithFrom(QString str, QStringList l) {
    for(QString s:l)
        if(str.startsWith(s, Qt::CaseInsensitive))
            return true;
    return false;
}

void MainWindow::on_lineEdit_textChanged(const QString &arg1)
{
    QStringList filters = arg1.split(QRegExp(",|;"));
    for(int i = comparisonModel->columnCount() - 1; i >= 0 ; i--){
        if(!startWithFrom(comparisonModel->headerData(i, Qt::Horizontal, Qt::DisplayRole).toString(),filters)) {
            ui->comparisonTableView->hideColumn(i);
        } else {
            ui->comparisonTableView->showColumn(i);
        }
    }
}

void MainWindow::on_pushButton_3_clicked()
{
    comparisonModel->save();
}


void MainWindow::on_filterParamButton_clicked(bool checked)
{
    QAbstractItemModel * model = ui->parametersTableView->model();
    for(int i = model->rowCount() - 1; i >= 0 ; i--){
        if(checked && !shortParamList.contains(model->index(i,0).data().toString(), Qt::CaseInsensitive)) {
            ui->parametersTableView->verticalHeader()->hideSection(i);
        } else {
            ui->parametersTableView->verticalHeader()->showSection(i);
        }
    }
}

void MainWindow::on_precisionSpinBox_valueChanged(int arg1)
{
    comparisonModel->precision = arg1;
    ui->comparisonTableView->reset();
}

void MainWindow::on_estimButton_clicked()
{
    SamaraFitness fitness(
                        estimModel->context,
                        estimModel->params(),
                        estimModel->bounds(),
                        estimModel->observations);
    de::DifferentialEvolution de(fitness, 100, std::time(nullptr));
    de.Optimize(1000, true);
}

void MainWindow::on_loadObsFromDB_clicked()
{
//    observations = loader->load_obs("");
//    obsmodel->setObs(observations);
}

void MainWindow::on_actionLoad_Meteo_triggered()
{
    QString dirPath = settings->value("SamaraParams_folder", QDir::currentPath()).toString();
    QString selectedFilter;
    QString filePath = QFileDialog::getOpenFileName(
                this, "Load parameters as csv", dirPath , "csv tab separated (*.csv);;csv semicolon separated (*.csv)",&selectedFilter);
    if(filePath.isEmpty()) return;
    settings->setValue("SamaraParams_folder", filePath);
    QString sep = (selectedFilter == "csv tab separated (*.csv)" ? "\t" : ";");
    meteoModel->load(filePath, sep);
    ui->meteoTableView->reset();
}

void MainWindow::on_loadEstimContext_clicked()
{
        QString dirPath = settings->value("SamaraEstim_folder", QDir::currentPath()).toString();
        QString dirSelected = QFileDialog::getExistingDirectory(this, "Open estimation folder", dirPath);
        if(dirSelected.isEmpty()) return;
        settings->setValue("SamaraEstim_folder", dirSelected);
        estimModel->load(dirSelected);
}

void MainWindow::on_actionSave_Observations_triggered()
{
    QString dirPath = settings->value("SamaraResult_folder", QDir::currentPath()).toString();
    QString selectedFilter;
    QString filePath = QFileDialog::getSaveFileName(
                this, "Save observations as csv", dirPath , "csv tab separated (*.csv);;csv semicolon separated (*.csv)",&selectedFilter);
    if(filePath.isEmpty()) return;
    settings->setValue("SamaraResult_folder", filePath);
    QString sep = (selectedFilter == "csv tab separated (*.csv)" ? "\t" : ";");
    obsmodel->save(filePath, sep);
}

vector<vector<double>> getNextBatch(vector<vector<double>> current, double min, double max, double step) {
    vector<vector<double>> batch;
    qDebug() << min << max << step << current.size();
    for (double var = min; var <= max; var += step) {
        vector<vector<double>> batch_step;
        for (int i = 0; i < current.size(); ++i) {
            batch_step.push_back(vector<double>());
            for (int j = 0; j < current[i].size(); ++j) {
                batch_step[i].push_back(current[i][j]);
            }
        }
//        qDebug() << batch_step.size() << batch_step[0].size();
        for (int i = 0; i < batch_step.size(); ++i) {
            batch_step[i].push_back(var);
        }
        batch.insert( batch.end(), batch_step.begin(), batch_step.end() );
    }
    return batch;
}

void MainWindow::on_actionLoad_batch_triggered()
{
    QString dirPath = settings->value("SamaraBatch_folder", QDir::currentPath()).toString();
    QString dirSelected = QFileDialog::getExistingDirectory(this, "Open batch folder", dirPath);
    if(dirSelected.isEmpty()) return;
    settings->setValue("SamaraBatch_folder", dirSelected);
qDebug()<< dirSelected;
    //load parametres
    paramModel->load(dirSelected + "/params.csv", "\t");
    //load meteo
    meteoModel->load(dirSelected + "/meteo.csv", "\t");

    qDebug() << "done params";

    //load batchparams
    vector<string> paramHeaders;
    vector< vector <double> > batch_steps;
    QFile file(dirPath + "/batch_params.csv");
    int step = 0;
    if(file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        QString line = in.readLine();
        QString sep = "";
        if(sep.isEmpty())
            sep = line.contains(";") ? ";" : "\t";

        while(!line.isEmpty()) {
            batch_steps.push_back(vector<double>());
            qDebug() << "line read" << line;
            QStringList lstLine = line.split(sep);
            int i = -1;
            qDebug() << lstLine << "\n" << lstLine[0] << lstLine[1]<< lstLine[2]<< lstLine[3];
            paramHeaders.push_back(lstLine[++i].toStdString());
            batch_steps[step].push_back(lstLine[++i].toDouble());
            batch_steps[step].push_back(lstLine[++i].toDouble());
            batch_steps[step].push_back(lstLine[++i].toDouble());
            line = in.readLine();
            step++;
        }

        file.close();
    }
    qDebug() << batch_steps.size();

    //generate batch
    vector< vector <double> > batch;
    batch.push_back(vector<double>());
    for (int i = 0; i < batch_steps.size(); ++i) {
        batch = getNextBatch(batch,
                             batch_steps[i][0],
                             batch_steps[i][1],
                             batch_steps[i][2]);
    }

    for (int i = 0; i < batch.size(); ++i) {
        QString l = "";
        for (int j = 0; j < batch[i].size(); ++j) {
            l += QString::number(batch[i][j]) + " ";
        }
        qDebug() << l;
    }

    //load output list
    vector<string> varHeaders;
    QFile file_vars(dirPath + "/batch_variables.csv");
    if(file_vars.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file_vars);
        QString line = in.readLine();
        while(!line.isEmpty()) {
            varHeaders.push_back(line.toStdString());
            qDebug() << line;
            line = in.readLine();
        }
        file_vars.close();
    }


    //launch simulations
    vector< vector <double> > outputs;
    Samara samara;
    Samara::SamaraLogType log = Samara::COMPLETE;
    QString version = ui->modelCombo->currentText();

    for (int simu = 0; simu < batch.size(); ++simu) {
        vector <double> param2change = batch[simu];
        outputs.push_back(vector<double>());
        for (int i = 0; i < paramHeaders.size(); ++i) {
            qDebug() << QString::fromStdString(paramHeaders[i]) << param2change[i];
            loader->parameters->doubles[paramHeaders[i]].first = param2change[i];
        }

        qDebug() << "Launching";
        if(version == "Samara 2.1")
            results = samara.run_samara_2_1(loader->parameters, log);
        else if(version == "Samara 2.1 michael")
            results = samara.run_samara_2_1_micha(loader->parameters, log);
        else if(version == "Samara 2.3")
            results = samara.run_samara_2_3(loader->parameters, log);
        else if(version == "Samara 2.3 lodging")
            results = samara.run_samara_2_3_lodging(loader->parameters, log);
        else if(version == "Samara 2.3 lodging test")
            results = samara.run_samara_2_3_lodging_test(loader->parameters, log);


        QString ll = "";
        for (int i = 0; i < varHeaders.size(); ++i) {
            auto it = std::find(results.first.begin(), results.first.end(), varHeaders[i]);
            if (it == results.first.end()){
                outputs[simu].push_back(nan(""));
            } else {
              auto index = std::distance(results.first.begin(), it);
              ll += QString::number(results.second[index].back()) + " ";
              outputs[simu].push_back(results.second[index].back());
            }
        }
        qDebug() << ll;
    }

    qDebug() << "DONE";

    for (int i = 0; i < outputs.size(); ++i) {
        QString l = "";
        for (int j = 0; j < outputs[i].size(); ++j) {
            l += QString::number(outputs[i][j]) + " ";
        }
        qDebug() << l;
    }

    //write results
}
