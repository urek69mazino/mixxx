// mixxxlibraryfeature.h
// Created 8/23/2009 by RJ Ryan (rryan@mit.edu)

#ifndef MIXXXLIBRARYFEATURE_H
#define MIXXXLIBRARYFEATURE_H

#include <QStringListModel>

#include "library/libraryfeature.h"
#include "library/dao/trackdao.h"
#include "treeitemmodel.h"

class BaseTrackCache;
class LibraryTableModel;
class MissingTableModel;
class HiddenTableModel;
class TrackCollection;

class MixxxLibraryFeature : public LibraryFeature {
    Q_OBJECT
    public:
    MixxxLibraryFeature(QObject* parent,
                        TrackCollection* pTrackCollection);
    virtual ~MixxxLibraryFeature();

    QVariant title();
    QIcon getIcon();
    bool dropAccept(QList<QUrl> urls, QWidget *pSource);
    bool dragMoveAccept(QUrl url);
    void setLibraryPrefix(QString sPrefix);
    TreeItemModel* getChildModel();

  public slots:
    void activate();
    void activateChild(const QModelIndex& index);
    void refreshLibraryModels();

  private:
    const QString kMissingTitle;
    const QString kHiddenTitle;
    QSharedPointer<BaseTrackCache> m_pBaseTrackCache;
    LibraryTableModel* m_pLibraryTableModel;
    MissingTableModel* m_pMissingTableModel;
    HiddenTableModel* m_pHiddenTableModel;
    TreeItemModel m_childModel;
    TrackDAO& m_trackDao;
};

#endif /* MIXXXLIBRARYFEATURE_H */
