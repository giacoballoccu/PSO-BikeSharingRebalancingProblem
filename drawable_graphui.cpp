#include "drawable_graphui.h"
#include "ui_drawable_graphui.h"

drawable_graphUI::drawable_graphUI(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::drawable_graphUI)
{
    ui->setupUi(this);
}

drawable_graphUI::~drawable_graphUI()
{
    delete ui;
}

