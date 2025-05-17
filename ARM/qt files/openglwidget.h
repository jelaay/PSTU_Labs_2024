#ifndef OPENGLWIDGET_H
#define OPENGLWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>

class OpenGLWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT
public:
    explicit OpenGLWidget(QWidget *parent = nullptr);
    ~OpenGLWidget() = default;

    void setTemperature(float temp);
    void setLightLevel(int light);
    void setHeatingStatus(bool heating);

protected:
    void initializeGL() override;
    void paintGL() override;
    void resizeGL(int w, int h) override;

private:
    float temperature = 0.0f;
    int lightLevel = 0;
    bool heatingActive = false;
};

#endif // OPENGLWIDGET_H
