#pragma once

#include "TFMapWidget.h"
#include <vapor/RenderParams.h>
#include <vapor/ParamsMgr.h>
#include <vapor/VAssert.h>
#include <glm/glm.hpp>

class TFColorInfoWidget;

class TFColorWidget : public TFMapWidget {
    Q_OBJECT
    
public:
    void Update(VAPoR::DataMgr *dataMgr, VAPoR::ParamsMgr *paramsMgr, VAPoR::RenderParams *rParams);
    
    QSize minimumSizeHint() const;
    void Deactivate();
    
protected:
    TFInfoWidget *createInfoWidget();
    void paintEvent(QPaintEvent* event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);
    
private:
    VAPoR::ParamsMgr *_paramsMgr = nullptr;
    VAPoR::RenderParams *_renderParams = nullptr;
    bool _isDraggingControl = false;
    int _draggingControlID;
    int _selectedId = -1;
    glm::vec2 _dragOffset;
    glm::vec2 m;
    
    bool controlPointContainsPixel(const glm::vec2 &cp, const glm::vec2 &pixel) const;
    
    void moveControlPoint(int *index, float value, const VAPoR::ColorMap::Color &c);
    void moveControlPoint(int *index, float value);
    VAPoR::ColorMap *getColormap() const;
    void selectControlPoint(int index);
    int findSelectedControlPoint(const glm::vec2 &mouse) const;
    bool controlPointContainsPixel(float cp, const glm::vec2 &pixel) const;
    QPointF controlQPositionForValue(float value) const;
    glm::vec2 controlPositionForValue(float value) const;
    float controlXForValue(float value) const;
    float valueForControlX(float position) const;
    
    static QColor VColorToQColor(const VAPoR::ColorMap::Color &c);
    static VAPoR::ColorMap::Color QColorToVColor(const QColor &c);
    
signals:
    void ControlPointDeselected();
    void UpdateInfo(float value, QColor color);
    
public slots:
    void DeselectControlPoint();
    void UpdateFromInfo(float value, QColor color);
};