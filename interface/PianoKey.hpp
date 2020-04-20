#pragma once

#include <QGraphicsItem>

#include "PianoKeyboard.hpp"
#include "Synthesizer.hpp"

class PianoKey
{
    public:
    PianoKey(int midiNote, PianoKeyboard *keyboard);

    int midiNote;
    bool on;
    PianoKeyboard *keyboard;
    QGraphicsItem *graphicsItem;
    Synthesizer *assignedSynthesizer;
};

class PianoKeyGraphicsItem : public QGraphicsItem
{
    public:
    PianoKeyGraphicsItem(QGraphicsItem *parent = nullptr, PianoKey *pianoKey);
    QRectF boundingRegion() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    PianoKey *pianoKey;
};