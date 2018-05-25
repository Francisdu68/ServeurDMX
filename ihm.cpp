#include "ihm.h"
#include "myslider.h"
#include "enttecdmxusb.h"

IHM::IHM(QWidget *parent) : QWidget(parent)
{
    interfaceDMX = NULL;

    // La GUI
    labelListe = new QLabel("Interface DMX USB :", this);
    // etc ...

    // Positionnement
    QVBoxLayout *layoutPrincipal = new QVBoxLayout;
    QHBoxLayout *layoutListe = new QHBoxLayout;
    // etc ...

    layoutListe->addWidget(labelListe);
    // etc ...

    layoutPrincipal->addLayout(layoutListe);
    // etc ...

    setLayout(layoutPrincipal);

    // Initialisation
    // etc ...

    setWindowTitle(QString::fromUtf8("Test DMX512"));
    setFixedHeight(sizeHint().height());
    setFixedWidth(sizeHint().width());
}

bool IHM::estFichierPeripherique(const QString &file)
{
    QFileInfo checkFile(file);

    if (checkFile.exists())
    {
        return true;
    }
    else
    {
        return false;
    }
}
