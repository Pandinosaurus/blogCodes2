#include "mainwindow.hpp"
#include "ui_mainwindow.h"

#include "change_wrong_image_suffix.hpp"
#include "check_images_state.hpp"
#include "cluster_similar_images.hpp"
#include "convert_label_img_labels.hpp"
#include "convert_yolo_detect_results.hpp"
#include "generate_image_list.hpp"
#include "image_mover.hpp"
#include "labels_check.hpp"
#include "remove_images.hpp"
#include "split_data.hpp"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->tabWidget->addTab(new image_mover, tr("move image"));
    ui->tabWidget->addTab(new remove_images, tr("Remove images"));
    ui->tabWidget->addTab(new split_data, tr("Split data"));
    ui->tabWidget->addTab(new convert_label_img_labels, tr("Convert labels"));
    ui->tabWidget->addTab(new labels_check, tr("Check labels"));
    ui->tabWidget->addTab(new generate_image_list, tr("Generate image list"));
    ui->tabWidget->addTab(new convert_yolo_detect_results, tr("Convert yolo detect results"));
    ui->tabWidget->addTab(new change_wrong_image_suffix, tr("Change wrong image suffix"));
    ui->tabWidget->addTab(new check_images_state, tr("Check image state"));
    ui->tabWidget->addTab(new cluster_similar_images, tr("Cluster similar images"));
}

MainWindow::~MainWindow()
{
    delete ui;
}

