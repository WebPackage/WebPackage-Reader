/*
  PictureFlow - animated image show widget
  http://pictureflow.googlecode.com

  Copyright (C) 2008 Ariya Hidayat (ariya@kde.org)
  Copyright (C) 2007 Ariya Hidayat (ariya@kde.org)

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in
  all copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
  THE SOFTWARE.
*/

#ifndef QFLOWVIEW_H
#define QFLOWVIEW_H

#include <qwidget.h>
#include "webpkg.h"

// detect Qt version
#if QT_VERSION >= 0x040000
#define QFLOWVIEW_QT4
#elif QT_VERSION >= 0x030000
#define QFLOWVIEW_QT3
#elif QT_VERSION >= 235
#define QFLOWVIEW_QT2
#else
#error QFlowView widgets need Qt 2, Qt 3 or Qt 4
#endif

#ifdef QFLOWVIEW_QT4
#include <QApplication>
#include <QCache>
#include <QHash>
#include <QImage>
#include <QKeyEvent>
#include <QPainter>
#include <QPixmap>
#include <QTimer>
#include <QVector>
#include <QWidget>
#endif

#if QT_VERSION >= 0x040000
#include <QTime>
#endif

#ifdef QFLOWVIEW_QT3
#include <qapplication.h>
#include <qcache.h>
#include <qimage.h>
#include <qpainter.h>
#include <qpixmap.h>
#include <qdatetime.h>
#include <qtimer.h>
#include <qvaluevector.h>
#include <qwidget.h>

#define qMax(x,y) ((x) > (y)) ? (x) : (y)
#define qMin(x,y) ((x) < (y)) ? (x) : (y)

#define QVector QValueVector

#define toImage convertToImage
#define contains find
#define modifiers state
#define ControlModifier ControlButton
#endif

#ifdef QFLOWVIEW_QT2
#include <qapplication.h>
#include <qarray.h>
#include <qcache.h>
#include <qimage.h>
#include <qintdict.h>
#include <qpainter.h>
#include <qpixmap.h>
#include <qdatetime.h>
#include <qtimer.h>
#include <qwidget.h>

#define qMax(x,y) ((x) > (y)) ? (x) : (y)
#define qMin(x,y) ((x) < (y)) ? (x) : (y)

#define QVector QArray

#define toImage convertToImage
#define contains find
#define modifiers state
#define ControlModifier ControlButton
#define flush flushX
#endif
class QFlowViewPrivate;

/*!
  Class PictureFlow implements an image show widget with animation effect
  like Apple's CoverFlow (in iTunes and iPod). Images are arranged in form
  of slides, one main slide is shown at the center with few slides on
  the left and right sides of the center slide. When the next or previous
  slide is brought to the front, the whole slides flow to the right or
  the right with smooth animation effect; until the new slide is finally
  placed at the center.

 */
class QFlowView : public QWidget
{
Q_OBJECT

  Q_PROPERTY(QColor backgroundColor READ backgroundColor WRITE setBackgroundColor)
  Q_PROPERTY(QSize slideSize READ slideSize WRITE setSlideSize)
  Q_PROPERTY(int slideCount READ slideCount)
  Q_PROPERTY(int centerIndex READ centerIndex WRITE setCenterIndex)

public:

  enum ReflectionEffect
  {
    NoReflection,
    PlainReflection,
    BlurredReflection
  };

  /*!
    Creates a new PictureFlow widget.
  */
  QFlowView(QWidget* parent = 0);

  /*!
    Destroys the widget.
  */
  ~QFlowView();

  /*!
    Returns the background color.
  */
  QColor backgroundColor() const;

  /*!
    Sets the background color. By default it is black.
  */
  void setBackgroundColor(const QColor& c);

  /*!
    Returns the dimension of each slide (in pixels).
  */
  QSize slideSize() const;

  /*!
    Sets the dimension of each slide (in pixels).
  */
  void setSlideSize(QSize size);

  /*!
    Returns the total number of slides.
  */
  int slideCount() const;

  /*!
    Returns QImage of specified slide.
  */
  QImage slideImage(int index) const;

  Package slidePackage(int index) const;

  /*!
    Returns the index of slide currently shown in the middle of the viewport.
  */
  int centerIndex() const;

  /*!
    Returns the effect applied to the reflection.
  */
  ReflectionEffect reflectionEffect() const;

  /*!
    Sets the effect applied to the reflection. The default is PlainReflection.
  */
  void setReflectionEffect(ReflectionEffect effect);


public slots:

  /*!
    Adds a new slide.
  */
  void addSlide(const QImage& image, Package& pak);

  /*!
    Adds a new slide.
  */
  void addSlide(const QPixmap& pixmap, Package& pak);


  Package getCurrentPackage();

  QImage getCurrentImage();

  /*!
    Sets an image for specified slide. If the slide already exists,
    it will be replaced.
  */
  void setSlide(int index, const QImage& image);

  /*!
    Sets a pixmap for specified slide. If the slide already exists,
    it will be replaced.
  */
  void setSlide(int index, const QPixmap& pixmap);

  /*!
    Sets slide to be shown in the middle of the viewport. No animation
    effect will be produced, unlike using showSlide.
  */
  void setCenterIndex(int index);

  /*!
    Clears all slides.
  */
  void clear();

  /*!
    Shows previous slide using animation effect.
  */
  void showPrevious();

  /*!
    Shows next slide using animation effect.
  */
  void showNext();

  /*!
    Go to specified slide using animation effect.
  */
  void showSlide(int index);

  /*!
    Rerender the widget. Normally this function will be automatically invoked
    whenever necessary, e.g. during the transition animation.
  */
  void render();

  /*!
    Schedules a rendering update. Unlike render(), this function does not cause
    immediate rendering.
  */
  void triggerRender();

signals:
  void centerIndexChanged(int index);

protected:
  void paintEvent(QPaintEvent *event);
  void keyPressEvent(QKeyEvent* event);
  void mousePressEvent(QMouseEvent* event);
  void resizeEvent(QResizeEvent* event);

private slots:
  void updateAnimation();

private:
  QFlowViewPrivate* d;
};
#endif // QFLOWVIEW_H

