#include "quotemanager.h"

QuoteManager::QuoteManager(QObject *parent) : QObject(parent) {
    randomizeQuoteTimer = new QTimer(this);
    connect(randomizeQuoteTimer, &QTimer::timeout, this, &QuoteManager::randomizeQuote);
    randomizeQuoteTimer->start(3600000); // 1 hour = 3600000 miliseconds

    randomizeQuote();
}

void QuoteManager::setQuote(QString quote) {
    if ( quote == m_quote )
        return;

    m_quote = quote;
    emit quoteChanged(quote);
}

void QuoteManager::randomizeQuote() {
    quint32 randomNumber = QRandomGenerator::global()->generate();
    QString randomQuote = quotes[randomNumber % quotes.count()];

    this->setQuote(randomQuote);
}
