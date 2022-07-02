#include "circlelayout.h"


CircleLayout::CircleLayout(QWidget *parent): QLayout(parent)
{
}

CircleLayout::~CircleLayout()
{
}

void CircleLayout::SetInitAngle(qreal angle)
{
    m_angle = angle;
    //Заставляем компоновщик заново позиционировать элементы
    invalidate();
}

void CircleLayout::SetSparseCoef(qreal value)
{
    //Ограничение диапозона значений коэфициента разреженности
    if (value < 0.5)
    {
        value = 0.5;
    }
    else
    {
        if (value > 2)
        {
            value = 2;
        }
    }
    m_sparse = value;
    //Заставляет компоновщик заново позиционировать элементы
    invalidate();
}

QSize CircleLayout::sizeHint() const
{
    //Размеры по умолчанию пустого компоновщика
    if (count() < 1)
    {
        return QSize(100, 100);
    }
    const qreal loSize = HintLoSize();
    //Рекомендованные размеры компоновщика
    return QSize(qRound(loSize), qRound(loSize));
}

void CircleLayout::setGeometry(const QRect &rect)
{
    QLayout::setGeometry(rect);
    for(int i=0; i<count(); i++)
    {
        const QSize size = itemAt(i)->sizeHint();
        const qreal angle = m_angle + i*2*M_PI/count();
        //Координаты левого верхнего угла элемента в системе координат с центром в середине родительского виджета
        const qreal xi = MinLoRadius()*qCos(angle) - size.width()*0.5;
        const qreal yi = -MinLoRadius()*qSin(angle) - size.height()*0.5;
        //Позиция и размеры элемента в системе координат родительского виджета (с центром в левом верхнем углу)
        const QRect geom(rect.center() + QPoint(qRound(xi), qRound(yi)), size);
        itemAt(i)->setGeometry(geom);
    }
}

QSize CircleLayout::minimumSize() const
{
    //Рекомендованный размер компоновщика использован еще и как минимальный
    //это гарантирует, что все элементы будут видны
    return sizeHint();
}


qreal CircleLayout::MaxItemRadius() const
{
    qreal maxRadius = 0;
    for(int i=0; i<count(); i++) {
        const QSize size = itemAt(i)->sizeHint();
        //Вычисление радиуса описанной окружности текущего элемента
        const qreal curRadius = qSqrt(qPow(size.width(), 2) + qPow(size.height(), 2))/2;
        //Выбор максимального радиуса
        maxRadius = qMax(maxRadius, curRadius);
    }
    return maxRadius;
}

qreal CircleLayout::MinLoRadius() const
{
    //Если элементов 0 или 1, радиус равен нулю
    if (count() < 2)
    {
        return 0;
    }
    return m_sparse*MaxItemRadius()/qSin(M_PI/count());
}

qreal CircleLayout::HintLoSize() const
{
    return 2*MinLoRadius() + 2*MaxItemRadius();
}

void CircleLayout::addItem(QLayoutItem *item)
{
    m_widgets.append(item);
}

QLayoutItem *CircleLayout::itemAt(int index) const
{
    //Проверка корректности индекса элемента (проверка обязательна)
    if (index < 0 || index >= count())
    {
        return 0;
    }
    return m_widgets.at(index);
}

QLayoutItem *CircleLayout::takeAt(int index)
{
    //Проверка корректности индекса элемента
    if (index < 0 || index >= count())
    {
        return 0;
    }
    return m_widgets.takeAt(index);
}

int CircleLayout::count() const
{
    return m_widgets.count();
}
