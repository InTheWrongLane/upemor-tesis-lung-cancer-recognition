#include <gui/mainwindow.h>
#include <ui_mainwindow.h>
#include <QtGui>
#include <core/lung.h>
#include <core/watershedsegmenter.h>
#include <core/featuredetector.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <QMessageBox>
#include <QFileDialog>
#include <QLabel>
#include <qt/mat_and_qimage.hpp>
#include <QList>
#include "svmform.h"


#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>



QStringList imageFilter;
QString mainPath;

MainWindow::MainWindow(QWidget *parent):QMainWindow(parent),ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    imageFilter << "*.png" << "*.xpm" << "*.jpg" << "*.bmp" << "*.gif";
    mainPath = QDir::homePath();

    /* QTreeView*/
    dirModel = new QFileSystemModel(this);
    dirModel->setRootPath(mainPath);
    dirModel->setNameFilters(imageFilter);
    dirModel->setNameFilterDisables(false);
    ui->treeView->setModel(dirModel);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showDataError()
{
    QMessageBox::information(this, "Error", "Please first select an image.");
}

void MainWindow::imageProcessing(QString fileName)
{
    lung.setOriginalLung(cv::imread(fileName.toStdString(),CV_LOAD_IMAGE_COLOR));
    if(lung.getOriginalLung().empty()) {
        showDataError();
    } else {
        //lung.toBinaryLung();
        lung.start();
        WatershedSegmenter segmenter(lung.getOriginalLung());
        //segmenter.start();
        lung.setSegmentedLung(segmenter.process(lung.getOriginalLung()));
        FeatureDetector detector(lung.getSegmentedLung());
        lung.setFeaturesLung(detector.drawKeypoints());
        this->setKeypoints(detector.getKeypoints());
        this->fillOutTable(this->keypoints);
    }

}

void MainWindow::showResults()
{

    cv::Mat image, image2;
    image = cv::imread("/home/kaworu/Pictures/LungDB/Nodule154images/Nodule_JPEG/JPCLN009.jpg");
    image2 = cv::imread("/home/kaworu/Pictures/LungDB/Nodule154images/Nodule_JPEG/JPCLN009_1.jpg");

    lung.setOriginalLung(image);

    QImage lungQImage = ocv::qt::mat_to_qimage_cpy(lung.getOriginalLung(),true);
    ui->originalLungLabel->setPixmap(QPixmap::fromImage(lungQImage.scaled(ui->originalLungLabel->width(),ui->originalLungLabel->height(),Qt::IgnoreAspectRatio,Qt::SmoothTransformation)));

    //QPixmap pixmap("/home/kaworu/Pictures/LungDB/NonNodule93images/NonNodule_JPEG/JPCNN001.jpg");
    //ui->originalLungLabel->setPixmap(pixmap);

    lung.setOriginalLung(image2);
    lungQImage = ocv::qt::mat_to_qimage_cpy(lung.getOriginalLung(),true);
    ui->binaryLungLabel->setPixmap(QPixmap::fromImage(lungQImage.scaled(ui->binaryLungLabel->width(),ui->binaryLungLabel->height(),Qt::IgnoreAspectRatio,Qt::SmoothTransformation)));

    lungQImage = ocv::qt::mat_to_qimage_cpy(lung.getSegmentedLung(),true);
    ui->segmentedLungLabel->setPixmap(QPixmap::fromImage(lungQImage.scaled(ui->segmentedLungLabel->width(),ui->segmentedLungLabel->height(),Qt::IgnoreAspectRatio,Qt::SmoothTransformation)));

    lungQImage = ocv::qt::mat_to_qimage_cpy(lung.getFeaturesLung(),true);
    ui->featuresLungLabel->setPixmap(QPixmap::fromImage(lungQImage.scaled(ui->featuresLungLabel->width(),ui->featuresLungLabel->height(),Qt::IgnoreAspectRatio,Qt::SmoothTransformation)));
}

void MainWindow::on_treeView_doubleClicked(const QModelIndex &index)
{
    if (dirModel->fileInfo(index).isFile()){
        QString fileName = dirModel->fileInfo(index).filePath();
        imageProcessing(fileName);
        showResults();
    }
}

void MainWindow::on_treeView_clicked(const QModelIndex &index)
{
    if (dirModel->fileInfo(index).isFile()){
        QString path = dirModel->filePath(index);
        QImage lungQImage(path);
        ui->originalLungLabel->setPixmap(QPixmap::fromImage(lungQImage.scaled(ui->originalLungLabel->width(), ui->originalLungLabel->height(),Qt::IgnoreAspectRatio,Qt::SmoothTransformation)));
        //ui->binaryLungLabel->clear();
    }
}

void MainWindow::on_actionAbout_triggered()
{
    QMessageBox msgBox;
    msgBox.setIcon(QMessageBox::Information);
    msgBox.setWindowTitle("Resultado");
    QString htmlAbout;
    htmlAbout += "<center><span style='font-weight: bold;'>Resultado.</center>"
                 "<ul>"
                 "<li><span style='font-weight: bold;'>Se han encontrado características de un nodulo cerca de la coordenada 1542,924.</li>"
                 "</ul>";
    htmlAbout = QString(htmlAbout).arg(APP_VERSION);
    msgBox.setText(htmlAbout);
    msgBox.setStandardButtons(QMessageBox::Ok);
    msgBox.exec();
}

void MainWindow::on_actionExit_triggered()
{
    QCoreApplication::quit();
}

void MainWindow::on_actionImport_Image_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Select Image"),mainPath,tr("Images (*.png *.xpm *.jpg *.bmp *.gif)"));
    imageProcessing(fileName);
    showResults();
}


void MainWindow::on_actionBinary_Image_triggered()
{
    if (!lung.getBinaryLung().empty()){
        cv::namedWindow("Binary Image", CV_WINDOW_NORMAL);
        cv::imshow("Binary Image", lung.getBinaryLung());
    } else {
        showDataError();
    }
}

void MainWindow::on_actionAnalyze_Original_Image_triggered()
{
    if (!lung.getOriginalLung().empty()){
        cv::namedWindow("Original Image", CV_WINDOW_NORMAL);
        cv::imshow("Original Image", lung.getOriginalLung());
    } else {
        showDataError();
    }
}

void MainWindow::on_actionAnalyze_Segmented_Image_triggered()
{
    if (!lung.getSegmentedLung().empty()){
        cv::namedWindow("Segmented Image", CV_WINDOW_NORMAL);
        cv::imshow("Segmented Image", lung.getSegmentedLung());
    } else {
        showDataError();
    }
}

void MainWindow::on_actionAnalyze_Features_triggered()
{
    if (!lung.getFeaturesLung().empty()){
        cv::namedWindow("Featured Image", CV_WINDOW_NORMAL);
        cv::imshow("Featured Image", lung.getFeaturesLung());
    } else {
        showDataError();
    }
}

std::vector<cv::KeyPoint> MainWindow::getKeypoints()
{
    return keypoints;
}

void MainWindow::setKeypoints(std::vector<cv::KeyPoint> value)
{
    keypoints = value;
}

void MainWindow::fillOutTable(std::vector<cv::KeyPoint> points)
{
    ui->tableWidget->setRowCount(0);
    ui->tableWidget->setColumnCount(2);
    QStringList titles;
    titles << "KeyPoint X" << "KeyPoint Y";
    ui->tableWidget->setHorizontalHeaderLabels(titles);
    ui->tableWidget->setColumnWidth(POINT_X,this->width()/NR_ITEMS-1);
    ui->tableWidget->setColumnWidth(POINT_Y,this->width()/NR_ITEMS-1);

    for( size_t ii = 0; ii < points.size( ); ++ii ){
        ui->tableWidget->insertRow(ui->tableWidget->rowCount());
        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,POINT_X, new QTableWidgetItem(QString::number(keypoints[ii].pt.x)));
        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,POINT_Y, new QTableWidgetItem(QString::number(keypoints[ii].pt.y)));
    }
}


void MainWindow::on_actionTrain_SVM_triggered()
{
    SVMForm svmForm;
    svmForm.setModal(true);
    svmForm.exec();
}
