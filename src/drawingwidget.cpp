#include "drawingwidget.h"

#include <QPainter>
#include <QPaintEvent>
#include "mainwindow.h"


/**
  Constructs a drawing widget.
  \param[in] parent parent widget of the drawing widget.
*/
DrawingWidget::DrawingWidget(MainWindow *parent)
    : QWidget(parent), m_mainWindow(parent)
{
    movingPointRightNow = false;
    firstSelectedForLine = nullptr;
}

DrawingWidget::~DrawingWidget() {
    delete movablePoint;
    delete firstSelectedForLine;
    for (unsigned int i = 0; i < m_points.size(); i++){
        delete m_points[i];
    }
}

/**
  Overridden method to handle all received paint events.
  \param[in] event the paint event that was received.
*/
void DrawingWidget::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.fillRect(event->rect(), Qt::cyan);

    painter.setBrush(Qt::black);
    for (unsigned int i = 0; i < m_points.size(); i++){
        if (firstSelectedForLine != nullptr && m_points[i] == firstSelectedForLine)
            painter.setBrush(Qt::red);
        painter.drawEllipse(m_points[i]->x, m_points[i]->y, 20, 20);
        if (firstSelectedForLine != nullptr && m_points[i] == firstSelectedForLine)
            painter.setBrush(Qt::black);
    }

    painter.setPen(QPen(Qt::black, 1));
    for (unsigned int i = 0; i < m_lines.size(); i++){
        painter.drawLine(m_lines[i].p1->x+10, m_lines[i].p1->y+10, m_lines[i].p2->x+10, m_lines[i].p2->y+10);
    }
}

void DrawingWidget::mousePressEvent(QMouseEvent *event){
    if (m_state == ADD_VERTEX_SELECTED) {
        if (event->button() == Qt::LeftButton){
            Point2* p = new Point2(event->x()-10, event->y()-10);
            Point2* closest = getClosestPoint(*p);
            bool allowedToDraw = true;
            if (closest != nullptr)
                allowedToDraw = closest->distanceFrom(*p) > 10;
            if (allowedToDraw){
                m_points.push_back(p);
                update ();
                m_mainWindow->updateVerticesLabel();
            } else{
                delete p;
            }
        }
    }

    if (m_state == MOVE_VERTEX_SELECTED){
        if (event->button() == Qt::LeftButton){
            Point2 p (event->x()-10, event->y()-10);
            Point2* closest = getClosestPoint(p);
            if (closest != nullptr && closest->distanceFrom(p) <= 10){
                movingPointRightNow = true;
                movablePoint = closest;
            }
        }
    }

    if (m_state == DELETE_VERTEX_SELECTED){
        if (event->button() == Qt::LeftButton){
            Point2 p (event->x()-10, event->y()-10);
            Point2* closest = getClosestPoint(p);
            if (closest != nullptr && closest->distanceFrom(p) <= 10){
                for (unsigned int i = 0; i < m_points.size(); i++){
                    if (m_points[i] == closest){
                        removeAssosiatedLines(m_points[i]);
                        delete m_points[i];
                        m_points.erase(m_points.begin() + i);
                        break;
                    }
                }
                update();
                m_mainWindow->updateVerticesLabel();
                m_mainWindow->updateLinesLabel();
                if (m_points.size() == 0){
                    setState(NO_TOOL_SELECTED);
                    m_mainWindow->setToolToNoTool();
                }
            }
        }
    }

    if (m_state == ADD_LINE_SELECTED){
        Point2 p (event->x()-10, event->y()-10);
        Point2* closest = getClosestPoint(p);
        if (closest->distanceFrom(p) <= 10){
            if (firstSelectedForLine == nullptr)
                firstSelectedForLine = closest;
            else if (closest != firstSelectedForLine){
                DynamicLine<Point2> l (firstSelectedForLine, closest);
                m_lines.push_back(l);
                firstSelectedForLine = nullptr;
            }
            update();
            m_mainWindow->updateLinesLabel();
        }
    }

    if (m_state == DELETE_LINE_SELECTED){
        Point2 p (event->x()-10, event->y()-10);
        for (unsigned int j = 0; j < m_lines.size(); j++){
            if (PointdistanceFromALine(p, m_lines[j]) <= (double)1){
                m_lines.erase(m_lines.begin() + j);
                break;
            }
        }
        update();
        m_mainWindow->updateLinesLabel();
        if (m_lines.size() == 0){
            setState(NO_TOOL_SELECTED);
            m_mainWindow->setToolToNoTool();
        }
    }
}


void DrawingWidget::mouseMoveEvent(QMouseEvent *event){
    if (movingPointRightNow){
        if (event->x() >= 10 && event->x()<= 790)
            movablePoint->x = event->x()-10;
        if (event->y() >= 10 && event->y()<= 550)
            movablePoint->y = event->y()-10;
        update ();
    }
    if (m_state == DELETE_LINE_SELECTED){

    }
}

void DrawingWidget::mouseReleaseEvent(QMouseEvent *event){
    if (m_state == MOVE_VERTEX_SELECTED && event->button() == Qt::LeftButton){
        movingPointRightNow = false;
    }
}

Point2* DrawingWidget::getClosestPoint(Point2 cursor){
    if (m_points.size() == 0)
        return nullptr;
    Point2* p = m_points[0];
    for (unsigned int i = 0; i < m_points.size(); i++){
        if (m_points[i]->distanceFrom(cursor) < p->distanceFrom(cursor)){
            p = m_points[i];
        }
    }
   return p;
}

void DrawingWidget::setState (DrawingWidgetState state){
    if (state != ADD_LINE_SELECTED)
        setFirstSelectedForLineToNull();
    m_state = state;
}


void DrawingWidget::removeAssosiatedLines(Point2* p){
    while (true){
        bool foundDeletableLine = false;
        for (unsigned int j = 0; j < m_lines.size(); j++){
            if (m_lines[j].p1 == p || m_lines[j].p2 == p){
                foundDeletableLine = true;
                m_lines.erase(m_lines.begin() + j);
                break;
            }
        }
        if (!foundDeletableLine)
            break;
    }
}


void DrawingWidget::setFirstSelectedForLineToNull(){
    firstSelectedForLine = nullptr;
    update();
}

double DrawingWidget::PointdistanceFromALine(Point2 p, DynamicLine<Point2> l){
    float dx = l.p2->x - l.p1->x;
    float dy = l.p2->y - l.p1->y;
    float t = ((p.x - l.p1->x) * dx + (p.y - l.p1->y) * dy) / (dx * dx + dy * dy);
    if (t < 0){
        dx = p.x - l.p1->x;
        dy = p.y - l.p1->y;
    } else if (t > 1){
        dx = p.x - l.p2->x;
        dy = p.y - l.p2->y;
    } else {
        Point2 closest (l.p1->x + t * dx, l.p1->y + t * dy);
        dx = p.x - closest.x;
        dy = p.y - closest.y;
    }
    return sqrt(dx * dx + dy * dy);
}
