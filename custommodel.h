#ifndef CUSTOMPROXYMODEL_H
#define CUSTOMPROXYMODEL_H

#include <QSortFilterProxyModel>

class CustomProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT

   public:
    CustomProxyModel(QObject *parent = nullptr);

    double filterMinimumFare() const { return minOverall; }
    void setFilterMinOverall(double overall);

    double filterMaximumFare() const { return maxOverall; }
    void setFilterMaxOverall(double overall);

   protected:
    bool filterAcceptsRow(int sourceRow,
                          const QModelIndex &sourceParent) const override;

   private:
    bool overallRange(double overall) const;

    double minOverall;
    double maxOverall;
};

#endif  // CUSTOMPROXYMODEL_H
