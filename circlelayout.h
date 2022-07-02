#ifndef CIRCLELAYOUT_H
#define CIRCLELAYOUT_H

#include <QtMath>
#include <QDebug>
#include <QWidget>
#include <QLayout>
#include <QLayoutItem>

//Компоновщик, располагающий элементы по кругу

class CircleLayout : public QLayout
{
    Q_OBJECT
    //Исходный угол от которого мы начинаем размещать компонуемые виджеты
    //по умолчанию = 0
    Q_PROPERTY(qreal initAngle READ initAngle WRITE SetInitAngle)
    //Коэффициент разреженности (позволяет компоновать виджеты плотнее или свободнее)
    //по умолчанию = 1 (соответствует рекомендуемому значению и исключает наползание элементов друг на друга)
    Q_PROPERTY(qreal sparseCoef READ sparseCoef WRITE SetSparseCoef)
public:
  CircleLayout(QWidget * parent = 0);
  ~CircleLayout();

  void SetInitAngle(qreal angle);
  qreal initAngle(){ return m_angle; }

  void SetSparseCoef(qreal value);
  qreal sparseCoef() { return m_sparse; }

  // QLayoutItem interface
public:
  //Возвращает рекомендуемый размер компоновщика
  virtual QSize sizeHint() const;
  //Размещает компонуемые виджеты
  virtual void setGeometry(const QRect &rect);

  // QLayout interface
public:
  //Добавление нового элемента компоновки
  virtual void addItem(QLayoutItem *item);
  //Получение элемента компоновки по индексу
  virtual QLayoutItem *itemAt(int index) const;
  //Изъятие элемента компоновки по индексу
  virtual QLayoutItem *takeAt(int index);
  //Получение количества элементов компоновки
  virtual int count() const;
  //Устанавливает минимально допустимый размер компоновщика
  virtual QSize minimumSize() const;
private:
  //Вычисление радиуса наибольшей описанной окружности вокруг элементов компоновки
  qreal MaxItemRadius() const;
  //Вычисление радиуса окруженности, на которой позиционируется центр элемента компоновки
  qreal MinLoRadius() const;
  //Оценка минимальных (рекомендуемых) габаритов компоновщика
  qreal HintLoSize() const;
private:
  //Список элементов компоновки
  QList<QLayoutItem*> m_widgets;

  qreal m_angle = 0;
  qreal m_sparse = 1;

};

#endif // CIRCLELAYOUT_H
