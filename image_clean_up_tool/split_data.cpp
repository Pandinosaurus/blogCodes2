#include "split_data.hpp"
#include "ui_split_data.h"

#include "utils/iterator_create.hpp"

#include <QDebug>
#include <QDir>
#include <QDirIterator>
#include <QFileInfo>
#include <QImage>
#include <QMessageBox>
#include <QSettings>
#include <QUuid>

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>

#include <algorithm>
#include <random>

split_data::split_data(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::split_data)
{
    ui->setupUi(this);
}

split_data::~split_data()
{
    delete ui;
}

void split_data::on_pushButtonStart_clicked()
{
    auto const paths = get_sources();
    qDebug()<<__func__<<" paths size = "<<paths.size();
    if(paths.empty()){
        return;
    }

    QDir().mkpath(ui->lineEditTest->text());
    QDir().mkpath(ui->lineEditTrain->text());

    auto create_fname = [](QString const &folder, QString const &path)
    {
        auto fname = folder + "/" + QFileInfo(path).fileName();
        if(QFile::exists(fname)){
            fname = folder + "/" + QUuid::createUuid().toString() + "." + QFileInfo(path).suffix();
        }

        return fname;
    };

    auto const train_size = static_cast<size_t>(static_cast<int>(paths.size()) * ui->doubleSpinBoxTrain->value());
    for(size_t i = 0; i != train_size; ++i){
        QFile(paths[i]).copy(create_fname(ui->lineEditTrain->text(), paths[i]));
    }
    if(train_size < paths.size()){
        auto const test_size = static_cast<size_t>(static_cast<int>(paths.size()) * ui->doubleSpinBoxTest->value());
        auto const end_size = std::min(paths.size(), static_cast<size_t>(test_size + train_size));
        for(size_t i = train_size; i != end_size; ++i){
            QFile(paths[i]).copy(create_fname(ui->lineEditTest->text(), paths[i]));
        }
        QMessageBox::information(this, tr("Split data"), tr("Train size = %1, test size = %2").
                                 arg(train_size).arg(test_size));
    }else{
        QMessageBox::information(this, tr("Split data"), tr("Train size = %1").arg(train_size));
    }
}

std::vector<QString> split_data::get_sources()
{
    if(!QDir(ui->lineEditSource->text()).exists()){
        QMessageBox::warning(this, tr("image_clean_up_tool"), tr("Image folder do not exist"));
        return {};
    }

    auto const iterate_flag = ui->checkBoxIterateSource->isChecked() ?  QDirIterator::Subdirectories :
                                                                        QDirIterator::NoIteratorFlags;
    auto dir_it = create_image_iterator(ui->lineEditSource->text(), iterate_flag);
    std::vector<QString> paths;
    while(dir_it.hasNext()){
        paths.emplace_back(QFileInfo(dir_it.next()).absoluteFilePath());
    }

    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(std::begin(paths), std::end(paths), g);

    return paths;
}
