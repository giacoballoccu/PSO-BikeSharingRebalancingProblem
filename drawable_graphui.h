#ifndef DRAWABLE_GRAPHUI_H
#define DRAWABLE_GRAPHUI_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class drawable_graphUI; }
QT_END_NAMESPACE

class drawable_graphUI : public QMainWindow
{
    Q_OBJECT

public:
    drawable_graphUI(QWidget *parent = nullptr);
    ~drawable_graphUI();

private:
    Ui::drawable_graphUI *ui;
};
#endif // DRAWABLE_GRAPHUI_H
