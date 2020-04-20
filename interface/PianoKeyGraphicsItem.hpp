#pragma once

class PianoKeyGraphicsItem : public QGraphicsItem
{
    public:
    PianoKeyGraphicsItem(QGraphicsItem *parent = nullptr, PianoKey *pianoKey);
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    PianoKey *pianoKey;
};