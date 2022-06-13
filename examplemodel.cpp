#include "examplemodel.h"

#include <QFile>
#include <QTextStream>

exampleModel::exampleModel(QObject *parent) : QAbstractTableModel(parent) {}

void exampleModel::fillDataTableFromFile(QString path)
{
    QFile inputFile(path);
    inputFile.open(QFile::ReadOnly | QFile::Text);
    QTextStream inputStream(&inputFile);

    QString firstline = inputStream.readLine();
    for (QString &item : firstline.split(","))
    {
        headerList.append(item);
    }

    while (!inputStream.atEnd())
    {
        QString line = inputStream.readLine();
        int columnNumber = 0;
        QList<QVariant> dataRow;
        for (QString &item : line.split(","))
        {
            if (columnNumber == 1 || columnNumber == 2 || columnNumber == 3 ||
                columnNumber == 4)
            {
                dataRow.append(item.toInt());
            }
            else
            {
                dataRow.append(item);
            }
            columnNumber += 1;
        }
        dataTable.append(dataRow);
    }
    inputFile.close();
}

void exampleModel::saveDataToFile(QString path)
{
    QFile outputFile(path);
    outputFile.open(QFile::WriteOnly | QFile::Text);
    QTextStream stream(&outputFile);
    for (int i = 0; i < headerList.size() - 1; ++i)
    {
        stream << headerList[i] << ", ";
    }
    stream << headerList[headerList.size() - 1];
    stream << "\n";
    for (QList<QVariant> &item : dataTable)
    {
        for (int i = 0; i < item.size() - 1; ++i)
        {
            stream << item[i].toString() << ", ";
        }
        stream << item[item.size() - 1].toString();
        stream << "\n";
    }
    outputFile.close();
}

int exampleModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid()) return 0;

    return dataTable.size();
}

int exampleModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid()) return 0;

    if (dataTable.empty())
    {
        return 0;
    }

    return dataTable[0].size();
}
QVariant exampleModel::headerData(int section, Qt::Orientation orientation,
                                  int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
    {
        return headerList[section];
    }
    return QVariant();
}

QVariant exampleModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()) return QVariant();

    if (role == Qt::DisplayRole || role == Qt::EditRole)
    {
        int row = index.row();
        int col = index.column();
        return dataTable[row][col];
    }
    return QVariant();
}

bool exampleModel::setData(const QModelIndex &index, const QVariant &value,
                           int role)
{
    if (data(index, role) != value)
    {
        int row = index.row();
        int col = index.column();
        dataTable[row][col] = value.toString();
        emit dataChanged(index, index, {role});
        return true;
    }
    return false;
}

Qt::ItemFlags exampleModel::flags(const QModelIndex &index) const
{
    if (!index.isValid()) return Qt::NoItemFlags;

    return QAbstractItemModel::flags(index) |
           Qt::ItemIsEditable;  // FIXME: Implement me!
}
void exampleModel::appendRow(const QList<QVariant> &row)
{
    size_t newRowNumber = rowCount();
    beginInsertRows(QModelIndex(), newRowNumber, newRowNumber);
    dataTable.append(row);
    endInsertRows();
}

void exampleModel::removeRow(int row)
{
    beginRemoveRows(QModelIndex(), row, row);
    dataTable.removeAt(row);
    endRemoveRows();
}
