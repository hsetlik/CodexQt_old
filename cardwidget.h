#ifndef CARDWIDGET_H
#define CARDWIDGET_H

#include <QWidget>
#include "cardstructure.h"

class CardContent : public QWidget
{
    Q_OBJECT
public:
    explicit CardContent(Card* c, QWidget* parent = nullptr);
    virtual ~CardContent() {}
    Card* const linkedCard;
    virtual void flip() {}
    virtual void setDueDate(int answerButton)
    {
        const int daysPerButton[] = {1, 3, 5, 10};
        linkedCard->setDueIn(daysPerButton[answerButton]);
    }
    void keyPressEvent(QKeyEvent* e) override
    {
        if(e->key() == Qt::Key_Return || e->key() == Qt::Key_Enter)
            emit checkAnswer();
    }
signals:
    void checkAnswer();
};
//==========================================================
class NtaContent : public CardContent
{
    Q_OBJECT
public:
    explicit NtaContent(Card* card, QWidget* parent = nullptr);
    void flip() override;
private:
    QString targetStr;
    QString nativeStr;
    QLabel* targetLabel;
    QLabel* nativeLabel;
    QVBoxLayout* layout;
};
//==========================================================
class ClozeContent : public CardContent
{
    Q_OBJECT
public:
    explicit ClozeContent(Card* card, QWidget* parent=nullptr);
    void flip() override;

private:
    std::vector<QLabel*> labels;
    QLineEdit* clozeBox;
};
//==========================================================
class FullContent : public CardContent
{
public:
    explicit FullContent(Card* card, QWidget* parent=nullptr);
    void flip() override;
private:
    QLabel* fullTarget;
    QLabel* fullNative;
    QLineEdit* answerBox;
};
//==========================================================
class CardViewer : public QWidget
{
    Q_OBJECT
public:
    explicit CardViewer(std::vector<Card*>& cards, QWidget *parent = nullptr);
    void nextCard();
public slots:
    void flip();
signals:
    void cardFlipped();
    void finishStudyMode();
private:
    void addContentForCard(Card* card);
    std::vector<Card*> allCards;
    int cardIdx;
    QVBoxLayout* contentLayout;
    CardContent* currentContent;
};

//==========================================================
namespace Ui
{
class CardWidget;
}
class CardWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CardWidget(Deck* deck, QWidget *parent = nullptr);
    Deck* const linkedDeck;
    void nextCard();
    ~CardWidget();
signals:
    void dueCardsFinished();
private slots:
    void on_button1_clicked();

    void on_button2_clicked();

    void on_button3_clicked();

    void on_button4_clicked();

    void submitCard();

    void finishStudying();
private:
    void setButtonsVisible(bool shouldBeVisible);
    Ui::CardWidget *ui;
    CardViewer* viewer;
    std::vector<Card*> cardsDue;
};

#endif // CARDWIDGET_H
