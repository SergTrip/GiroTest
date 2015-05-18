#include "girotestwidget.h"
#include "ui_girotestwidget.h"

GiroTestWidget::GiroTestWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GiroTestWidget)
{
    ui->setupUi(this);

    // Connect the viewer signal to our draw slot.
    connect( ui->m_oGlViewer, SIGNAL(drawNeeded()), this, SLOT(draw()));

    // Подключакм слот обновления данных
    connect( &m_oGiroData, SIGNAL(newGiroDataSignal (qint16,qint16,qint16)),
             this,          SLOT (newGiroDataSlot   (qint16,qint16,qint16)) );
}

GiroTestWidget::~GiroTestWidget()
{
    delete ui;
}

void GiroTestWidget::draw()
{
    const float nbSteps = 200.0;
    glBegin(GL_QUAD_STRIP);
    for (float i=0; i<nbSteps; ++i)
      {
        float ratio     = i/nbSteps;
        float angle     = 21.0*ratio;
        float c         = cos(angle);
        float s         = sin(angle);
        float r1        = 1.0 - 0.8*ratio;
        float r2        = 0.8 - 0.8*ratio;
        float alt       = ratio - 0.5;
        const float nor = .5;
        const float up  = sqrt(1.0-nor*nor);

        glColor3f   ( 1.0-ratio,    0.2f,       ratio   );
        glNormal3f  ( nor*c,        up,         nor*s   );
        glVertex3f  ( r1*c,         alt,        r1*s    );
        glVertex3f  ( r2*c,         alt+0.05,   r2*s    );
      }
    glEnd();
}

void GiroTestWidget::newGiroDataSlot(qint16 x, qint16 y, qint16 z)
{
    // Выводим данные в диалог
    ui->labelDataX->setText( "X: " + QString::number(x) + " mG" );
    ui->labelDataY->setText( "Y: " + QString::number(y) + " mG" );
    ui->labelDataZ->setText( "Z: " + QString::number(z) + " mG" );

    // Получаем указатель на фрейм
    qglviewer::ManipulatedFrame* frame = ui->m_oGlViewer->manipulatedFrame();

    qglviewer::Quaternion quat( qglviewer::Vec(x, y, z), 0 );

    // Пробуем его вращать
    // frame->setOrientation ( quat );
}
