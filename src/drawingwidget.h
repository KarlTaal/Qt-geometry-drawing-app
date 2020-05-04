#ifndef DRAWINGWIDGET_H
#define DRAWINGWIDGET_H
#include <vector>
#include <Point2.h>
#include <DynamicLine.h>

#include <QWidget>

class MainWindow;

enum DrawingWidgetState {
    NO_TOOL_SELECTED,
    ADD_VERTEX_SELECTED,
    MOVE_VERTEX_SELECTED,
    DELETE_VERTEX_SELECTED,
    ADD_LINE_SELECTED,
    DELETE_LINE_SELECTED
};

class DrawingWidget: public QWidget {
    Q_OBJECT
    public:
        DrawingWidget(MainWindow *parent = 0);
        ~DrawingWidget();
        std::vector<Point2*> m_points;
        std::vector<DynamicLine<Point2>> m_lines;
        void setFirstSelectedForLineToNull();

    public slots:
        void setState (DrawingWidgetState state);

    protected:
        void mousePressEvent(QMouseEvent *event);
        void paintEvent(QPaintEvent *event);
        void mouseMoveEvent(QMouseEvent *event);
        void mouseReleaseEvent(QMouseEvent *event);
        MainWindow *m_mainWindow;
        DrawingWidgetState m_state;
        bool movingPointRightNow;
        Point2* movablePoint;
        Point2* getClosestPoint(Point2 cursor);
        Point2* firstSelectedForLine;
        void removeAssosiatedLines(Point2* p);
        double PointdistanceFromALine(Point2 p, DynamicLine<Point2> l);
};

#endif // DRAWINGWIDGET_H
