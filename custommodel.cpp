#include "custommodel.h"

CustomProxyModel::CustomProxyModel(QObject *parent)
    : QSortFilterProxyModel{parent}
{
    maxOverall = 100;
    minOverall = 1;
}

bool CustomProxyModel::filterAcceptsRow(int sourceRow,
                                        const QModelIndex &sourceParent) const
{
    QModelIndex idxOverall = sourceModel()->index(sourceRow, 4, sourceParent);

    return overallRange(sourceModel()->data(idxOverall).toDouble());
}

bool CustomProxyModel::overallRange(double overall) const
{
    return overall >= minOverall && overall < maxOverall;
}

void CustomProxyModel::setFilterMinOverall(double overall)
{
    minOverall = overall;
    invalidateFilter();
}

void CustomProxyModel::setFilterMaxOverall(double overall)
{
    maxOverall = overall;
    invalidateFilter();
}
