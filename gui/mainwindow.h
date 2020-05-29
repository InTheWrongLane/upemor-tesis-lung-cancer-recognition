#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCore>
#include <QtGui>
#include <QFileSystemModel>
#include <core/lung.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void showDataError();
    void imageProcessing(QString fileName);
    void showResults();
    std::vector<cv::KeyPoint> getKeypoints();
    void setKeypoints(std::vector<cv::KeyPoint> value);
    void fillOutTable(std::vector<cv::KeyPoint> points);

private slots:

    void on_treeView_doubleClicked(const QModelIndex &index);
    void on_treeView_clicked(const QModelIndex &index);
    void on_actionAbout_triggered();
    void on_actionExit_triggered();
    void on_actionImport_Image_triggered();
    void on_actionBinary_Image_triggered();
    void on_actionAnalyze_Original_Image_triggered();
    void on_actionAnalyze_Segmented_Image_triggered();
    void on_actionAnalyze_Features_triggered();

    void on_actionTrain_SVM_triggered();

private:
    Ui::MainWindow *ui;
    QFileSystemModel *dirModel;
    Lung lung;
    std::vector<cv::KeyPoint> keypoints;
    enum tableHeadersLocation {
        POINT_X, POINT_Y, NR_ITEMS
    };
};

#endif // MAINWINDOW_H
