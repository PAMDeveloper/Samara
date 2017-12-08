#ifndef PARAMETERSDATAMODEL_H
#define PARAMETERSDATAMODEL_H

#include <QAbstractTableModel>
#include <parameters.h>
#include <QColor>

class ParametersDataModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    ParametersDataModel(SamaraParameters * parameters, QObject *parent=0);

    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role=Qt::EditRole);

    static QColor getColor(QString s);

private:
    SamaraParameters * parameters;
    QStringList keys;
};

#endif // PARAMETERSDATAMODEL_H
