#include "widget.h"

#include <QSlider>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    QVBoxLayout *m_mainLayout=new QVBoxLayout();
    m_tabWidget=new QTabWidget();
    m_mainLayout->addWidget(m_tabWidget);
    setLayout(m_mainLayout);

    CircleLayoutSet();
    SquareLayoutSet();
}

Widget::~Widget()
{
}

void Widget::CircleLayoutSet()
{
    //Круговой виджет

    QVBoxLayout *m_mainCircleLayout=new QVBoxLayout();
    CircleLayout *circleLayout = new CircleLayout();
    circleLayout->addWidget(new QPushButton("43423423"));
    circleLayout->addWidget(new QPushButton("fdsfds"));
    circleLayout->addWidget(new QLabel("vcxvzcxvzcx"));
    circleLayout->addWidget(new QLabel("dsdsdss"));


    QSlider *edtSparseCoefSlider=new QSlider();
    edtSparseCoefSlider->setOrientation(Qt::Horizontal);
    edtSparseCoefSlider->setRange(50, 200);
    connect(edtSparseCoefSlider, &QSlider::valueChanged, [=](int value){
        qreal coef = value * 0.01;
        //Установка нового значения компоновщику
        circleLayout->SetSparseCoef(coef);
    });


    QSlider *edtInitAngle=new QSlider();
    edtInitAngle->setOrientation(Qt::Horizontal);
    edtInitAngle->setRange(0, 360);
    connect(edtInitAngle, &QSlider::valueChanged, [=](int value){
          circleLayout->SetInitAngle(qDegreesToRadians((float)value));
    });


    m_mainCircleLayout->addLayout(circleLayout);
    m_mainCircleLayout->addWidget(edtSparseCoefSlider);
    m_mainCircleLayout->addWidget(edtInitAngle);

    QWidget *widgetCircle=new QWidget();
    widgetCircle->setLayout(m_mainCircleLayout);
    m_tabWidget->addTab(widgetCircle, "Circle widget");
}

void Widget::SquareLayoutSet()
{
    //Квадратный виджет
    QVBoxLayout *m_mainSquareLayout=new QVBoxLayout();
    BorderLayout *borderLayout = new BorderLayout();
    borderLayout->addWidget(new QPushButton("East"), BorderLayout::East);
    borderLayout->addWidget(new QPushButton("West"), BorderLayout::West);
    borderLayout->addWidget(new QPushButton("Center"), BorderLayout::Center);

        borderLayout->addWidget(new QPushButton("North"), BorderLayout::North);
    borderLayout->addWidget(new QPushButton("South"), BorderLayout::South);

    m_mainSquareLayout->addLayout(borderLayout);

    QWidget *squareWidget=new QWidget();
    squareWidget->setLayout(m_mainSquareLayout);
    m_tabWidget->addTab(squareWidget, "Border layout");
}

