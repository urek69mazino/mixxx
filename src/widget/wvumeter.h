#pragma once

#include <QDomNode>
#include <QGLWidget>
#include <QPaintEvent>
#include <QPixmap>
#include <QString>

#include "skin/legacy/skincontext.h"
#include "util/performancetimer.h"
#include "widget/wpixmapstore.h"
#include "widget/wwidget.h"

class VSyncThread;

class WVuMeter : public QGLWidget, public WBaseWidget {
    Q_OBJECT
  public:
    explicit WVuMeter(QWidget *parent=nullptr);

    void setup(const QDomNode& node, const SkinContext& context);
    void setPixmapBackground(
            const PixmapSource& source,
            Paintable::DrawMode mode,
            double scaleFactor);
    void setPixmaps(
            const PixmapSource& source,
            bool bHorizontal,
            Paintable::DrawMode mode,
            double scaleFactor);
    void onConnectedControlChanged(double dParameter, double dValue) override;

  public slots:
    void render(VSyncThread* vSyncThread);
    void swap();

  protected slots:
    void updateState(mixxx::Duration elapsed);

  private:
    void initializeGL() override;
    void paintEvent(QPaintEvent * /*unused*/) override;

    void setPeak(double parameter);

    // To make sure we render at least once even when we have no signal
    bool m_bHasRendered;
    // To indicate that we rendered so we need to swap
    bool m_bSwapNeeded;
    // Current parameter and peak parameter.
    double m_dParameter;
    double m_dPeakParameter;

    // The last parameter and peak parameter values at the time of
    // rendering. Used to check whether the widget state has changed since the
    // last render in maybeUpdate.
    double m_dLastParameter;
    double m_dLastPeakParameter;

    // Length of the VU-meter pixmap along the relevant axis.
    int m_iPixmapLength;

    // Associated pixmaps
    PaintablePointer m_pPixmapBack;
    PaintablePointer m_pPixmapVu;

    // True if it's a horizontal vu meter
    bool m_bHorizontal;

    int m_iPeakHoldSize;
    int m_iPeakFallStep;
    int m_iPeakHoldTime;
    int m_iPeakFallTime;

    // The peak hold time remaining in milliseconds.
    double m_dPeakHoldCountdownMs;

    PerformanceTimer m_timer;
};
