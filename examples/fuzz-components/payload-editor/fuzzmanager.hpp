#ifndef FUZZMANAGER_HPP
#define FUZZMANAGER_HPP

#include <QtCore/QObject>

class FuzzManager : public QObject
{
    Q_OBJECT
public:
    explicit FuzzManager(QObject *parent = nullptr);

signals:

};

#endif // FUZZMANAGER_HPP
