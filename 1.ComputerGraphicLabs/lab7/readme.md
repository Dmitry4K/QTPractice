### Построение плоских полиномиальных кривых

Полиномиальная кривая неспроста имеет такое название – в ее основе лежат _полиномы_, по которым и рисует такая кривая. Мой вариант работы заключался в построении сплайна непрерывной кривизны по трем точкам у которого, как и у других _сплайнов_, есть ряд условий построений: 

1)	В точках стыках _сегментов_ (часть кривой между двумя соседними точками, которая строится по собственному полиному) первая и вторая производные равны.

2)	Для крайних точек пользователь собственноручно задает производные.

Так же стоит помнить, что в точках стыков сегментов значения координат – равные, иначе получился бы набор кривых хаотично расположенных на экране. Кроме того, уравнение каждого сегмента представляется в виде системы _параметрических уравнений_, и параметр этих уравнений принимает значения от 0 до 1

В итоге для построения сплайна нужно решить _систему уравнений_, найти коэффициенты полином всех сегментов и затем визуализировать его.

### GIF

![](lab7.gif)

### Принципы работы

Алгоритм работы состоит из нескольких шагов:

#### Обработка событий нажатия клавиш и взаимодействия с виджетом

У spinewidget который наследован от QWidget переопределено несколько функций отвечающих за взаимодействие виджета с пользователем : ```mousePressEvent(QMouseEvent* e)```, ```mouseMoveEvent(QMouseEvent* e)```, ```mouseReleaseEvent(QMouseEvent* e)```. С помощью этих событий осуществляется общение программы и пользователя, например: можно добавить точку сплайна нажатием на виджет, перенести ее или полностью очистить виджет нажатием на Delete

_Пример реализации события нажатия на виджет_

```c++
void SplineWidget::mousePressEvent(QMouseEvent* e){
    if(e->buttons()  == Qt::LeftButton){
        if(!spline.add(QPointF(centrizePointCord(cordsOnCenter(e->pos()))))){
            selectedPoint = spline.findPointOrRail(centrizePointCord(cordsOnCenter(e->pos())));
            if(selectedPoint != spline.getPoints().end()){
                isSelected = true;
                if(!isCatch(selectedPoint->getRail().x()+selectedPoint->x(),
                           selectedPoint->getRail().y()+selectedPoint->y(),
                           centrizePointCord(cordsOnCenter(e->pos())).x(),
                           centrizePointCord(cordsOnCenter(e->pos())).y())){
                    isRailSelected = false;
                } else {
                    isRailSelected = true;
                }
            }
        }
    }
}
```

#### Вычисления cплайна

Вычисление сплайна возможно только тогда, когда известны все три точки сплайна и две производные на его концах, тогда вызывается метод, в котором запрограммировано решение системы уравнений.

_Вычисление полиномов сплайна непрерывной кривизны_

```c++
void SplineClass::calculatePolynoms(Polynom& fP, Polynom& sP, int p0, int p1, int p2, int r0, int r2){

    float& a1 = fP.a;
    float& a2 = sP.a;
    float& b1 = fP.b;
    float& b2 = sP.b;
    float& c1 = fP.c;
    float& c2 = sP.c;
    float& d1 = fP.d;
    float& d2 = sP.d;
    //qDebug() << p0 << ' ' << p1 << ' '<< p2 << ' '<<r0 << ' '<< r2 << '\n';
    d1 = p0; //+
    d2 = p1; //+
    c1 = r0;

    float n = -c1;
    float h = d2-d1-c1;
    float q = p2 - d2;
    float z = r2;
    float x = 3*q + 2*n - z;

    a1 = (x-5*h)/4;
    b1 = (9*h - x)/4;

    b2 = 3*a1 + b1;
    c2 = 3*a1 + 2*b1 - n;
    a2 = q - b2 - c2;
}
void SplineClass::calculate(){
    calculatePolynoms(fSegment.xPolynom,
                      sSegment.xPolynom,
                      points[0].x(), points[1].x(),
                      points[2].x(), points[0].getRail().x(), points[2].getRail().x());
    calculatePolynoms(fSegment.yPolynom,
                      sSegment.yPolynom,
                      points[0].y(), points[1].y(),
                      points[2].y(), points[0].getRail().y(), points[2].getRail().y());
}
```

#### Визуализация

Зная, что полиномы нормализированы и принимают значения от 0 до 1, можно, задав точность отрисовки, вычислять точки полиномов и соединять их линиями. 

_Отрывок кода, отвечающего за визуализацию сплайна_

```c++
if(spline.isValid()){
        QPen pen(Qt::red);
        pen.setWidth(splineWidth);
        painter.setPen(pen);
        spline.calculate();
        float step = 1/(float)spline.getPresicion();
        QPointF prev = points[0];
        for(float i = step;i < 1.0f;i += step ){
            QPointF next = spline.fSegment.claculatePoint(i);
            painter.drawLine(subLineFunction(toNormalCord(prev)), subLineFunction(toNormalCord(next)));
            prev = next;
        }
        painter.drawLine(subLineFunction(toNormalCord(prev)), subLineFunction(toNormalCord(spline.fSegment.claculatePoint(1))));
        prev = points[1];
        for(float i = step;i < 1.0f;i += step ){
            QPointF next = spline.sSegment.claculatePoint(i);
            painter.drawLine(subLineFunction(toNormalCord(prev)), subLineFunction(toNormalCord(next)));
            prev = next;
        }
        painter.drawLine(subLineFunction(toNormalCord(prev)), subLineFunction(toNormalCord(spline.sSegment.claculatePoint(1))));
    }
```
