#include "myslider.h"

MySlider::MySlider( int canal, int valeur, QWidget *parent ) : QWidget( parent )
{
   lcd = new QLCDNumber(NB_DIGIT, this );
   s = new QSlider( Qt::Vertical, this );
   s->setTickPosition( QSlider::TicksBothSides );
   s->setTickInterval(VALEUR_MAX);
   s->setMinimum(VALEUR_MIN);
   s->setMaximum(VALEUR_MAX);

   sb = new QSpinBox(this);
   sb->setMaximum(NB_CANAUX);

   QVBoxLayout *mainLayout = new QVBoxLayout;
   QHBoxLayout *hLayout1 = new QHBoxLayout;
   QHBoxLayout *hLayout2 = new QHBoxLayout;
   QHBoxLayout *hLayout3 = new QHBoxLayout;
   hLayout1->addWidget(lcd);
   hLayout2->addWidget(s);
   hLayout3->addWidget(sb);
   mainLayout->addLayout(hLayout1);
   mainLayout->addLayout(hLayout2);
   mainLayout->addLayout(hLayout3);
   setLayout(mainLayout);

   connect( s, SIGNAL(valueChanged(int)), lcd, SLOT(display(int)) );
   connect( s, SIGNAL(valueChanged(int)), this, SLOT(changerValeur(int)) );
   connect( sb, SIGNAL(valueChanged(int)), this, SLOT(changerCanal(int)) );
   connect( this, SIGNAL(valeurChange(int)), lcd, SLOT(display(int)) );
   connect( this, SIGNAL(canalChange(int)), sb, SLOT(setValue(int)) );

   s->setValue(valeur);
   sb->setValue(canal);
}

void MySlider::changerValeur(int valeur)
{
    qDebug() << "valeur = " << valeur;
    emit valeurChange(valeur);
    emit sliderChange(sb->value(), valeur);
}

void MySlider::changerCanal(int canal)
{
    qDebug() << "canal = " << canal;
    emit canalChange(canal);
    emit sliderChange(canal, s->value());
}

void MySlider::setValeur(int valeur)
{
    s->setValue(valeur);
}

void MySlider::setCanal(int canal)
{
    sb->setValue(canal);
}
