#include "girotestwidget.h"
#include "ui_girotestwidget.h"

GiroTestWidget::GiroTestWidget(QWidget *parent) :
    QWidget         ( parent    ),
    m_oFaceDetector ( this->parentWidget() ),
    ui(new Ui::GiroTestWidget)
{
    ui->setupUi(this);

    // Connect the viewer signal to our draw slot.
    connect( ui->m_oGlViewer, SIGNAL(drawNeeded()), this, SLOT(draw()));
    // Connect the viewer signal to our init slot.
    connect( ui->m_oGlViewer, SIGNAL(viewerInitialized ()), this, SLOT(glViewerWidgetInitSlot()));

    // Подключаeм слот обновления данных
//    connect( &m_oGiroData, SIGNAL(newGiroDataSignal (qreal,qreal,qreal,qreal)),
//             this,          SLOT (newGiroDataSlot   (qreal,qreal,qreal,qreal))  );

    // Ширина основания
    m_nCameraWidth      = 640.0f / ( 2.0f * 640.0f );
    // Высота основания
    m_nCameraHigth      = 480.0f / ( 2.0f * 640.0f );
    // Расстояние до плоскости
    m_CameraDistance    = 0.5f;

//    // Установить время
//    m_oFaceDetector.setTime( 20 );
//    // Запустить
//    m_oFaceDetector.startTimer();
//    // Показать диалог
//    m_oFaceDetector.show();
}

GiroTestWidget::~GiroTestWidget()
{
    m_oFaceDetector.close();

    delete ui;
}

void GiroTestWidget::glViewerWidgetInitSlot()
{
    // Включить изображение осей
    //ui->m_oGlViewer->setAxisIsDrawn();

    // Вывести FPS
    // ui->m_oGlViewer->setFPSIsDisplayed();

    // Рисовать сетку
    ui->m_oGlViewer->setGridIsDrawn();
    // Разрешить вывод текста
    ui->m_oGlViewer->setTextIsEnabled();
    // Добавить управляемый фрейм
    ui->m_oGlViewer->setManipulatedFrame(new qglviewer::ManipulatedFrame());

#ifdef GL_RESCALE_NORMAL  // OpenGL 1.2 Only...
  glEnable(GL_RESCALE_NORMAL);
#endif

    // Make sure the manipulatedFrame is not easily clipped by the zNear and zFar planes
    ui->m_oGlViewer->setSceneRadius(30);

    // Установить положение камеры
    ui->m_oGlViewer->camera()->setPosition( qglviewer::Vec(10,10,10) );

    // Указать направление
    ui->m_oGlViewer->camera()->setUpVector( qglviewer::Vec(0.0f, 0.0f, 1.0f ) );
    // Указать направление
    ui->m_oGlViewer->camera()->lookAt( qglviewer::Vec(0,0,0) );

    // ui->m_oGlViewer->camera()->fitSphere( qglviewer::Vec(0,0,0), 1 );

    // Подготовка к выводу текстур
    glShadeModel  ( GL_FLAT       );
    glEnable      ( GL_DEPTH_TEST );

    glPixelStorei ( GL_UNPACK_ALIGNMENT, 1 );

    glGenTextures ( 1, &m_uTexture );

    glBindTexture ( GL_TEXTURE_2D, m_uTexture );

    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,        GL_REPEAT   );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,        GL_REPEAT   );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,    GL_NEAREST  );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,    GL_NEAREST  );
}

void GiroTestWidget::draw()
{
//    // Попрбовать вывести текст
//    ui->m_oGlViewer->drawText(20, 40, "X: " + QString::number(m_vGiroData.x()) );
//    ui->m_oGlViewer->drawText(20, 50, "Y: " + QString::number(m_vGiroData.y()) );
//    ui->m_oGlViewer->drawText(20, 60, "Z: " + QString::number(m_vGiroData.z()) );
//    ui->m_oGlViewer->drawText(20, 70, "W: " + QString::number(m_vGiroData.w()) );

//    ui->m_oGlViewer->drawText(20, 100, "Accel X: " + QString::number(m_vAccelData.x()) + " m/s^2 " );
//    ui->m_oGlViewer->drawText(20, 110, "Accel Y: " + QString::number(m_vAccelData.y()) + " m/s^2 " );
//    ui->m_oGlViewer->drawText(20, 120, "Accel Z: " + QString::number(m_vAccelData.z()) + " m/s^2 " );

    ui->m_oGlViewer->drawAxis( 0.1 );

    // Save the current model view matrix (not needed here in fact)
    glPushMatrix();

    // Multiply matrix to get in the frame coordinate system.
    glMultMatrixd(ui->m_oGlViewer->manipulatedFrame()->matrix());

//    qglviewer::Quaternion quat( m_vGiroData.x(),
//                                m_vGiroData.y(),
//                                m_vGiroData.z(),
//                                m_vGiroData.w()     );
//    // Пробуем его вращать
//    ui->m_oGlViewer->manipulatedFrame()->setOrientation ( quat );

    // Scale down the drawings
   glScalef(0.3f, 0.3f, 0.3f);

    // Вывести оси
    ui->m_oGlViewer->drawAxis( 0.1 );

    // Отбразить данные камеры
    drawTexture();
    // Нарисовать камеру
    drawCamera();
    //drawSpiral();

    // Restore the original (world) coordinate system
    glPopMatrix();

}

void GiroTestWidget::newGiroDataSlot(qreal x, qreal y, qreal z, qreal w)
{
    // Выводим данные в диалог
    ui->labelDataX->setText( "X: " + QString::number(x) );
    ui->labelDataY->setText( "Y: " + QString::number(y) );
    ui->labelDataZ->setText( "Z: " + QString::number(z) );
    //ui->labelDataW->setText( "W: " + QString::number(w) );

    m_vGiroData = QVector4D( x, y, z, w );

    //m_vGiroData.normalize();

    // Получаем указатель на фрейм
    //qglviewer::ManipulatedFrame* frame = ui->m_oGlViewer->manipulatedFrame();

    //qglviewer::Quaternion quat( qglviewer::Vec(x, y, z), 90 );

    ui->m_oGlViewer->update();

    // Пробуем его вращать
    //frame->setOrientation ( quat );
}

void GiroTestWidget::newAccelDataSignal(qint16 x, qint16 y, qint16 z)
{
    m_vAccelData = QVector3D(x, y, z );
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

void GiroTestWidget::drawCamera()
{
    // Вектор для хранения цвета
    GLfloat color[4];

    // Установить режим отображения
    glPolygonMode( GL_FRONT,    GL_LINE );
    glPolygonMode( GL_BACK,     GL_LINE );

    // Поменять толщину линий
    glLineWidth( 2.0f );

    glBegin( GL_TRIANGLE_FAN );

    // Получить текущий цвет
    glGetFloatv( GL_CURRENT_COLOR, color );

    // Установить свой цвет
    glColor3f( 1.0f, 0.0f , 0.0f );

    // glNormal3f(nor*c, up, nor*s);
    glVertex3f(  0.0f,  0.0f, 0.0f );
    glVertex3f(  m_nCameraWidth,  m_nCameraHigth, m_CameraDistance);
    glVertex3f(  m_nCameraWidth, -m_nCameraHigth, m_CameraDistance);
    glVertex3f( -m_nCameraWidth, -m_nCameraHigth, m_CameraDistance);
    glVertex3f( -m_nCameraWidth,  m_nCameraHigth, m_CameraDistance);
    glVertex3f(  m_nCameraWidth,  m_nCameraHigth, m_CameraDistance);

    // Вернуть цвет
    glColor3fv( color );

    glEnd();

    // Вернуть режим отображения
    glPolygonMode( GL_FRONT,    GL_FILL );
    glPolygonMode( GL_BACK,     GL_FILL );
}

void GiroTestWidget::drawTexture()
{
    QImage texture;
    texture = m_oFaceDetector.getImage();

    // Установить режим отображения
    glPolygonMode( GL_FRONT,    GL_FILL );
    glPolygonMode( GL_BACK,     GL_LINE );

    // Обновить текстуру
    glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, texture.width(), texture.height(), 0, GL_RGBA,
                  GL_UNSIGNED_BYTE, texture.bits()  );

    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    glEnable    ( GL_TEXTURE_2D );
    glTexEnvf   ( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE );

    glBindTexture ( GL_TEXTURE_2D, m_uTexture );

    glBegin( GL_QUADS );

    glTexCoord2f( 0.0, 0.0);    glVertex3f(  m_nCameraWidth,  m_nCameraHigth, m_CameraDistance);
    glTexCoord2f( 0.0, 1.0);    glVertex3f(  m_nCameraWidth, -m_nCameraHigth, m_CameraDistance);
    glTexCoord2f( 1.0, 1.0);    glVertex3f( -m_nCameraWidth, -m_nCameraHigth, m_CameraDistance);
    glTexCoord2f( 1.0, 0.0);    glVertex3f( -m_nCameraWidth,  m_nCameraHigth, m_CameraDistance);

    glEnd();

    glFlush();
    glDisable( GL_TEXTURE_2D );    

    glPolygonMode( GL_FRONT,    GL_FILL );
    glPolygonMode( GL_BACK,     GL_FILL );
}
