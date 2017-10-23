#include <qtapp/mainwindow.h>

#include <QApplication>
#include <QDebug>
#include <QDate>

#include <samara.h>
#include <utils/psqlloader.h>
#include <utils/DBEcosysloader.h>
//#include <utils/fileloader.h>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

//    load_file_parameters("Z:/Downloads/SMK2013/Variete_SMK2013.txt", "");
    SamaraParameters * paramsSam = new SamaraParameters();
//    PSQLLoader loader(paramsSam);
//    ParadoxLoader loader(paramsSam, "D:/Samples/michael/DBEcosys");
    DBEcosysLoader loader(paramsSam, "D:/Samples/michael/DBEcosys");

//    loader.load_complete_simulation("06SB15-fev13-D1_SV21");
//    auto results = run_samara_2_1(paramsSam);


//    ResultsDataModel *resultsModel = new ResultsDataModel(results);
//    ui->resultsTableView->setModel(resultsModel);

    MainWindow w(&loader);
    w.show();

//    w.showResults(resultsModel);

//    QString refFileName = "D:/PAMStudio_dev/data/samara/06SB15-fev13-D1_SV21.txt";
//    w.displayData(paramsSam, results, refFileName, true);

    return a.exec();

    //    std::chrono::time_point<std::chrono::system_clock> startC, endC;
    //    startC = std::chrono::system_clock::now();
    //    endC = std::chrono::system_clock::now();
    //    double elapsed_seconds = std::chrono::duration_cast<std::chrono::microseconds>
    //            (endC-startC).count() / 1000;
    //    std::time_t end_time = std::chrono::system_clock::to_time_t(endC);
    //    std::cout << "finished computation at " << std::ctime(&end_time)
    // << "elapsed time: " << elapsed_seconds << "microsec\n";

    //    qDebug() << fixed << paramsSam->doubles["datedebut"].first;
    //    qDebug() << QString::fromStdString(paramsSam->getString("idparcelle"));
    //    for (auto const& x : paramsSam->doubles)
    //    {std::cout << x.first << " " << x.second.first << std::endl;}
    //    for (auto const& x : paramsSam->climatics)
    //    {std::cout << x.TMax << std::endl;}
    //    for (int i = 0; i < 1000; ++i) {
    //    }

    //    std::cout << "finished computation at " << std::ctime(&end_time)
    //              << "elapsed time: " << elapsed_seconds << "microsec\n";

}
