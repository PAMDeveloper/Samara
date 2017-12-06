#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCharts/QLineSeries>
#include <QtCharts/QSplineSeries>
#include <QtCharts/QScatterSeries>
#include <QGridLayout>
#include <QMouseEvent>
#include <QDate>
#include <qtapp/comparisondatamodel.h>
#include <qtapp/comparisondatamodel.h>

#include <parameters.h>
#include <qtapp/meteodatamodel.h>
#include <qtapp/parametersdatamodel.h>
#include <qtapp/resultsdatamodel.h>
#include <qtapp/DBAccessLoader.h>
#include <qtapp/chartmanager.h>
#include <qtapp/resultsmanager.h>
#include <qtapp/comparisonmanager.h>

QT_CHARTS_USE_NAMESPACE

namespace Ui {
class MainWindow;
}


class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void displayData( pair <vector <string>, vector < vector <double> > > results );

    bool addChart(int row, int col,
                  QLineSeries *series,
                  QScatterSeries *refseries,
                  QString name);

    serieCompare compareSeries(QLineSeries * src, QScatterSeries * ref);

    QMap < QString, QLineSeries * > getRefSeries(QString refFileName);
    QMap < QString, QScatterSeries * > getObsSeries(map<string, vector<double>> observations);
    QMap < QString, QLineSeries * > getResultSeries(pair <vector <string>, vector < vector <double> > > results);

//    QLineSeries *getSeries(QString fileName, QDate endDate);

    void loadDB(QString filePath);
    void clearDBContext();

    void createChartsTab();
    void fillDBCombos();
    void showParameters(SamaraParameters * parameters);
    void loadRefFile(QString path);


private slots:
    void on_loadDbButton_clicked();
    void on_launchButton_clicked();
    void on_saveResultButton_clicked();


    void sectionClicked(int);
    void on_simComboBox_currentTextChanged(const QString &arg1);
    void on_varComboBox_currentTextChanged(const QString &arg1);
    void on_stationComboBox_currentTextChanged(const QString &arg1);
    void on_plotComboBox_currentTextChanged(const QString &arg1);
    void on_itinComboBox_currentTextChanged(const QString &arg1);
    void on_startDateEdit_dateChanged(const QDate &date);
    void on_endDateEdit_dateChanged(const QDate &date);
    void chartClicked(bool);
    void on_oldResButton_clicked();


    void on_pushButton_2_clicked();

    void on_lineEdit_textChanged(const QString &arg1);

    void on_pushButton_3_clicked();






private:
    Ui::MainWindow *ui;
    QSettings * settings;

    QStringList chartVisibles;
    QString _date;
    QString _model_name;
    QString _var_name;
    int _type;

    DBAccessLoader * loader;
    ChartManager * chartManager;
    ResultsManager * resultsManager;
    ComparisonManager * comparisonManager;

    ResultsDataModel *resultsModel;
    ComparisonDataModel2 *comparisonModel = nullptr;


    pair <vector <string>, vector < vector <double> > > results;
    map<string, vector<double>> observations;

    QGridLayout *lay;

    QList<serieCompare> comparisons;
    QStringList headers;
    QDate startDate;
};

#endif // MAINWINDOW_H
