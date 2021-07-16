#ifndef LOGWRITER_H
#define LOGWRITER_H



#include <QObject>



class LogWriter : public QObject
{
    Q_OBJECT
public:
    explicit LogWriter(QObject *parent = nullptr);

signals:

};

#endif // LOGWRITER_H
