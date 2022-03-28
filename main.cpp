#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtGui>
#include <QtQuick>
class UserModel : public QAbstractListModel
{
    Q_OBJECT

public:
    Q_INVOKABLE void g(int index) {
        qDebug() << index;
        beginRemoveRows(QModelIndex(), index, index);
        mData.removeAt(index);
        endRemoveRows();
    }
    void f(){
        beginInsertRows(QModelIndex(), mData.count(), mData.count());
        mData.append(qMakePair(QStringLiteral("John"), 52));
        endInsertRows();
    }
    UserModel() {
        mData.append(qMakePair(QStringLiteral("John"), 52));
        mData.append(qMakePair(QStringLiteral("Matt"), 23));
        mData.append(qMakePair(QStringLiteral("Lucy"), 10));
    }

    enum Roles
    {
        NameRole = Qt::UserRole,
        AgeRole
    };

    QVariant data(const QModelIndex &index, int role) const override
    {
        if (!index.isValid())
            return QVariant();

        switch (role) {
        case Qt::DisplayRole:
        case NameRole:
            qDebug() << "name role:" << mData.at(index.row()).first;
            return mData.at(index.row()).first;
        case AgeRole:
            return mData.at(index.row()).second;
        }

        return QVariant();
    }

    bool setData(const QModelIndex &index, const QVariant &value, int role) override
    {
        switch (role) {
        case NameRole: {
            const QString newName = value.toString();
            mData[index.row()].first = value.toString();
            emit dataChanged(index, index, { NameRole });
            return true;
        }
        }

        return false;
    }

    int rowCount(const QModelIndex &/*parent*/ = QModelIndex()) const override
    {
        return mData.size();
    }

    int columnCount(const QModelIndex &/*parent*/ = QModelIndex()) const override
    {
        return 1;
    }

    virtual QHash<int, QByteArray> roleNames() const override
    {
        QHash<int, QByteArray> names;
        names[NameRole] = "name";
        names[AgeRole] = "age";
        return names;
    }
    QVector<QPair<QString, int> > mData;
};

class UserModel2 : public QAbstractTableModel
{
    Q_OBJECT

public:
    Q_INVOKABLE void g(int index) {
        qDebug() << index;
        beginRemoveRows(QModelIndex(), index, index);
        mData.removeAt(index);
        endRemoveRows();
    }
    void f(){
        beginInsertRows(QModelIndex(), mData.count(), mData.count());
        mData.append(qMakePair(QStringLiteral("John"), 52));
        endInsertRows();
    }
    UserModel2() {
        mData.append(qMakePair(QStringLiteral("John"), 52));
        mData.append(qMakePair(QStringLiteral("Matt"), 23));
        mData.append(qMakePair(QStringLiteral("Lucy"), 10));
    }

    enum Roles
    {
        NameRole = Qt::UserRole,
        AgeRole
    };

    QVariant data(const QModelIndex &index, int role) const override
    {return mData.at(index.row()%mData.size()).first;
        if (!index.isValid())
            return QVariant();

        switch (role) {
        case Qt::DisplayRole:
        case NameRole:
            qDebug() << "name role:" << mData.at(index.row()).first;
            return mData.at(index.row()%mData.size()).first;
        case AgeRole:
            return mData.at(index.row()).second;
        }

        return QVariant();
    }

    bool setData(const QModelIndex &index, const QVariant &value, int role) override
    {
        switch (role) {
        case NameRole: {
            const QString newName = value.toString();
            mData[index.row()].first = value.toString();
            emit dataChanged(index, index, { NameRole });
            return true;
        }
        }

        return false;
    }

    int rowCount(const QModelIndex &/*parent*/ = QModelIndex()) const override
    {
        return mData.size();
    }

    int columnCount(const QModelIndex &/*parent*/ = QModelIndex()) const override
    {
        return mData.size();
    }

    virtual QHash<int, QByteArray> roleNames() const override
    {
        QHash<int, QByteArray> names;
        names[NameRole] = "name";
        names[AgeRole] = "age";
        return names;
    }
    QVector<QPair<QString, int> > mData;
};

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    const QUrl url(u"qrc:/untitled10/main.qml"_qs);
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);

    UserModel model;
    UserModel2 model2;
    engine.rootContext()->setContextProperty("mm", &model);
    engine.rootContext()->setContextProperty("mm2", &model2);

    engine.load(url);
model.f();
    return app.exec();
}

#include "main.moc"
