

class PianoKeyboardGraphicsItem : public QGraphicsItem
{
    public:
    PianoKeyboardGraphicsItem(QGraphicsItem *parent = nullptr, PianoKeyboard *pianoKeyboard);
    QRectF boundingRegion() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    PianoKeyboard *pianoKeyboard;
};