#ifndef QUOTEMANAGER_H
#define QUOTEMANAGER_H

#include <QObject>
#include <QRandomGenerator>
#include <QDebug>
#include <QTimer>

class QuoteManager : public QObject {
    Q_OBJECT
    Q_PROPERTY(QString quote READ quote NOTIFY quoteChanged)

public:
    explicit QuoteManager(QObject *parent = nullptr);

    QString quote() const {
        return m_quote;
    }

public slots:
    void setQuote(QString quote);
    void randomizeQuote();

signals:
    void quoteChanged(QString quote);

private:
    QString m_quote = "";
    QTimer *randomizeQuoteTimer = nullptr;

    const QStringList quotes = {
        "„Oamenii sunt pasari cu aripile crescute inauntru.” – Nichita Stanescu",
        "„Visatorii nu mor niciodata.” – Carmen Voinea Raducanu",
        "„Nimic nu valoreaza mai mult decat ziua de azi.” – Goethe",
        "„Gandeste global, actioneaza local”– Rene Dubos",
        "„Initial a fost o lume a barbatilor. Apoi, a aparut Eva.” – Richard Armour",
        "„Nu vei zari nicicand un curcubeu daca te uiti in jos.” – Charlie Chaplin",
        "„Ai grija de corpul tau, pentru ca este singurul loc unde va trebui sa traiesti” - Jim Rohn",
        "„Când ai încetat să fii mai copil, ai murit de mult.” — Constantin Brâncuși",
        "„Educația este ceea ce rămâne după ce ai uitat tot ceea ce ai învățat în școală.” — Albert Einstein",
        "„Oricâte calităţi am avea, lumea se uită numai la defecte.” — Molière",
        "„Nu spune puţin în vorbe multe, ci mult în vorbe puţine.” — Pitagora",
        "„Femeia e o creatură menită să fie iubită, nu înțeleasă.” — Sigmund Freud"
    };
};

#endif // QUOTEMANAGER_H
