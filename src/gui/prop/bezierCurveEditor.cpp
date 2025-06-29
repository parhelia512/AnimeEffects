#include "beziercurveeditor.h"

#include <QDoubleSpinBox>
#include <QPainterPath>
#include <QPainter>
#include <QMouseEvent>
#include <filesystem>
#include <utility>

float normalize(const float val, const int range) {
    return val / static_cast<float>(range);
}
float denormalize(const float val, const int range) {
    return val * static_cast<float>(range - 20);
}
float invert (const int min, const int max, const float value) {
    return static_cast<float>(max) - value + static_cast<float>(min);
}

BezierCurveEditor::BezierCurveEditor(QWidget *parent, const bool isDark, util::Easing::CubicBezier* cubicBezier, QVector<QDoubleSpinBox*> spins)
    : QWidget(parent)
    , m_curvePen(isDark? Qt::white: Qt::black)
    , m_dragging(false)
{
    m_curvePen.setWidth(2);
    bezier = cubicBezier;

    spinBoxes = std::move(spins);
    if (isDark) {
        m_colors[0] = Qt::white;
        m_colors[3] = Qt::white;
    }
    else {
        m_colors[0] = Qt::black;
        m_colors[3] = Qt::black;
    }
    m_colors[1] = QColor(82, 87, 208);
    m_colors[2] = QColor(82, 87, 208);

    for (int i = 0; i < NUM_POINTS; i++) {
        m_pens[i]    = QPen(m_colors[i]);
        m_brushes[i] = QBrush(m_colors[i]);
    }
}

BezierCurveEditor::~BezierCurveEditor()
{

}

void BezierCurveEditor::mousePressEvent(QMouseEvent *event)
{
    for(int i = 0; i < NUM_POINTS; i++) {
        if(distance(m_points[i], event->pos()) <= POINT_RADIUS) {
            m_selectedPoint = i;
            m_dragging = true;
            break;
        }
    }
}

void BezierCurveEditor::mouseMoveEvent(QMouseEvent *event)
{
    if(m_dragging) {
        m_points[m_selectedPoint] = event->pos();
    }
    update();
}

void BezierCurveEditor::mouseReleaseEvent(QMouseEvent *)
{
    m_dragging = false;
}

void BezierCurveEditor::resizeEvent(QResizeEvent *)
{
    m_points[StartPoint]    = QPointF(20, height() - 20);
    m_points[ControlPoint1] = QPointF(width() - 20, height() - 20);
    m_points[ControlPoint2] = QPointF(20, 20);
    m_points[EndPoint]      = QPointF(width() - 20, 20);
    repaint();
}

void BezierCurveEditor::paintEvent(QPaintEvent *)
{
    // Points are not meant to be moved for any reason
    m_points[StartPoint]    = QPointF(20, height() - 20);
    m_points[EndPoint]      = QPointF(width() - 20, 20);
    // This would break the calculations

    // We normalize these because the points are not lower-left 0 and upper-right 1, also, we need to inverse the Y points
    // because the Y axis is inverted in the GUI
    bezier->x1 = normalize(m_points[ControlPoint1].x() + 20.0, width());
    const auto inverted_y1 = invert(0, height(), m_points[ControlPoint1].y());
    bezier->y1 = normalize(inverted_y1 - 20.0, height());

    bezier->x2 = normalize(m_points[ControlPoint2].x() - 20.0, width());
    const auto inverted_y2 = invert(0, height(), m_points[ControlPoint2].y());
    bezier->y2 = normalize(inverted_y2 + 20.0, height());

    if (!spinBoxes.empty() && spinBoxes.at(0)) {
        for (auto box : spinBoxes) {
            box->blockSignals(true);
        }
        spinBoxes.at(0)->setValue(bezier->x1);
        spinBoxes.at(1)->setValue(bezier->y1);
        spinBoxes.at(2)->setValue(bezier->x2);
        spinBoxes.at(3)->setValue(bezier->y2);
        for (auto box : spinBoxes) {
            box->blockSignals(false);
        }
    }
    //
    QPainter painter(this);

    painter.setRenderHint(QPainter::Antialiasing, true);

    painter.setPen(m_curvePen);
    QPainterPath path;
    path.moveTo(m_points[StartPoint]);
    path.cubicTo(m_points[ControlPoint1], m_points[ControlPoint2], m_points[EndPoint]);
    painter.drawPath(path);

    for (int i = 0; i < NUM_POINTS; i++) {
        painter.setPen(m_pens[i]);
        painter.setBrush(m_brushes[i]);
        painter.drawEllipse(m_points[i], POINT_RADIUS, POINT_RADIUS);
    }
}
