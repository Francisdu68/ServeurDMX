#ifndef IHM_H
#define IHM_H

#include <QtGui>

#define NB_INTERFACES_DMX   4
#define NB_SLIDERS          6

class MySlider;
class EnttecDMXUSB;

class IHM : public QWidget
{
    Q_OBJECT
public:
    explicit IHM(QWidget *parent = 0);

private:
    // Les widgets
    MySlider            *sliders[NB_SLIDERS];
    QLabel              *labelListe;
    // etc ...

    EnttecDMXUSB        *interfaceDMX;

    bool estFichierPeripherique(const QString &file);

signals:
    
public slots:

};

#endif // IHM_H
