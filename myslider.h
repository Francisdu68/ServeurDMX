#ifndef MYSLIDER_H
#define MYSLIDER_H

#include <QtGui>

#define VALEUR_MIN   0
#define VALEUR_MAX   255
#define NB_CANAUX    512

#define NB_DIGIT     3

class MySlider : public QWidget
{
	Q_OBJECT
    
private:
        QLCDNumber  *lcd;
        QSlider     *s;
        QSpinBox    *sb;
        
public:
        MySlider( int canal = 0, int valeur = 0, QWidget *parent = 0 );

signals:
        void sliderChange(int canal, int valeur);
        void valeurChange(int valeur);
        void canalChange(int canal);

private slots:
        void changerValeur(int valeur);
        void changerCanal(int canal);

public slots:
        void setValeur(int valeur);
        void setCanal(int canal);
};

#endif //MYSLIDER_H
