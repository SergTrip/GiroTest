#include "girotestwidget.h"
#include "ui_girotestwidget.h"

GiroTestWidget::GiroTestWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GiroTestWidget)
{
    ui->setupUi(this);

    // Connect the viewer signal to our draw slot.
    connect( ui->m_oGlViewer, SIGNAL(drawNeeded()), this, SLOT(draw()));
    // Connect the viewer signal to our init slot.
    connect( ui->m_oGlViewer, SIGNAL(viewerInitialized ()), this, SLOT(glViewerWidgetInitSlot()));

    // Подключакм слот обновления данных
    connect( &m_oGiroData, SIGNAL(newGiroDataSignal (qint16,qint16,qint16)),
             this,          SLOT (newGiroDataSlot   (qint16,qint16,qint16)) );
}

GiroTestWidget::~GiroTestWidget()
{
    delete ui;
}

void GiroTestWidget::glViewerWidgetInitSlot()
{
    // Включить изображение осей
    // ui->m_oGlViewer->setAxisIsDrawn();

    ui->m_oGlViewer->setFPSIsDisplayed();

    ui->m_oGlViewer->setGridIsDrawn();

    ui->m_oGlViewer->setTextIsEnabled();

    ui->m_oGlViewer->setManipulatedFrame(new qglviewer::ManipulatedFrame());

#ifdef GL_RESCALE_NORMAL  // OpenGL 1.2 Only...
  glEnable(GL_RESCALE_NORMAL);
#endif

  // Make sure the manipulatedFrame is not easily clipped by the zNear and zFar planes
  ui->m_oGlViewer->setSceneRadius(30);

  ui->m_oGlViewer->camera()->fitSphere(qglviewer::Vec(0,0,0), 1);

  // Add a manipulated frame to the viewer.
  // If you are not "using namespace qglqglviewer", you need
  // to specify: new qglviewer::ManipulatedFrame().
  ui->m_oGlViewer->setManipulatedFrame(new qglviewer::ManipulatedFrame());

}

void GiroTestWidget::draw()
{
    // Попрбовать вывести текст
    ui->m_oGlViewer->drawText(20, 40, "X: " + QString::number(m_vGiroData.x()) + " mG" );
    ui->m_oGlViewer->drawText(20, 50, "Y: " + QString::number(m_vGiroData.y()) + " mG" );
    ui->m_oGlViewer->drawText(20, 60, "Z: " + QString::number(m_vGiroData.z()) + " mG" );

    ui->m_oGlViewer->drawAxis();

    // Save the current model view matrix (not needed here in fact)
    glPushMatrix();

    // Multiply matrix to get in the frame coordinate system.
    glMultMatrixd(ui->m_oGlViewer->manipulatedFrame()->matrix());

    qglviewer::Quaternion quat( qglviewer::Vec(m_vGiroData.x(), m_vGiroData.z(), m_vGiroData.y()), 90 );
    // Пробуем его вращать
    ui->m_oGlViewer->manipulatedFrame()->setOrientation ( quat );

    drawSpiral();

    // Restore the original (world) coordinate system
    glPopMatrix();

}

void GiroTestWidget::newGiroDataSlot(qint16 x, qint16 y, qint16 z)
{
    // Выводим данные в диалог
    ui->labelDataX->setText( "X: " + QString::number(x) + " mG" );
    ui->labelDataY->setText( "Y: " + QString::number(y) + " mG" );
    ui->labelDataZ->setText( "Z: " + QString::number(z) + " mG" );

    m_vGiroData.setX(x);
    m_vGiroData.setY(y);
    m_vGiroData.setZ(z);

    m_vGiroData.normalize();

    // Получаем указатель на фрейм
    //qglviewer::ManipulatedFrame* frame = ui->m_oGlViewer->manipulatedFrame();

    //qglviewer::Quaternion quat( qglviewer::Vec(x, y, z), 90 );

    ui->m_oGlViewer->update();

    // Пробуем его вращать
    ///frame->setOrientation ( quat );
}

void GiroTestWidget::drawSpiral()
{
  const float nbSteps = 200.0;
  glBegin(GL_QUAD_STRIP);
  for (float i=0; i<nbSteps; ++i)
    {
      float ratio = i/nbSteps;
      float angle = 21.0*ratio;
      float c = cos(angle);
      float s = sin(angle);
      float r1 = 1.0 - 0.8*ratio;
      float r2 = 0.8 - 0.8*ratio;
      float alt = ratio - 0.5;
      const float nor = .5;
      const float up = sqrt(1.0-nor*nor);
      glColor3f(1.0-ratio, 0.2f , ratio);
      glNormal3f(nor*c, up, nor*s);
      glVertex3f(r1*c, alt, r1*s);
      glVertex3f(r2*c, alt+0.05, r2*s);
    }
  glEnd();
}
