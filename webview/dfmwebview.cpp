/**
 * Copyright (C) 2017 Deepin Technology Co., Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 **/
#include "dfmwebview.h"

#include <dfmevent.h>
#include <dfmeventdispatcher.h>

#include <QWebEngineHistory>
#include <QAction>
#include <QWebEngineContextMenuData>
#include <QWebEngineSettings>
#include <QMenu>

class DFMWebViewPrivate
{
public:
    static DFMWebView *lastCreateWebView;
};

DFMWebView *DFMWebViewPrivate::lastCreateWebView = Q_NULLPTR;

DFMWebView::DFMWebView(QWidget *parent)
    : QWebEngineView(parent)
{
    DFMWebViewPrivate::lastCreateWebView = this;

    QWebEngineSettings::defaultSettings()->setAttribute(QWebEngineSettings::PluginsEnabled, true);

    connect(this, &QWebEngineView::urlChanged, this, &DFMWebView::notifyUrlChanged);

    DFMEventDispatcher::instance()->installEventFilter(this);
}

QWidget *DFMWebView::widget() const
{
    return const_cast<DFMWebView*>(this);
}

DUrl DFMWebView::rootUrl() const
{
    return url();
}

bool DFMWebView::setRootUrl(const DUrl &url)
{
    setUrl(url);

    return true;
}

void DFMWebView::notifyUrlChanged()
{
    DFMBaseView::notifyUrlChanged();
}

void DFMWebView::openLinkInNewTab(const DUrl &url)
{
    DFMEventDispatcher::instance()->processEvent<DFMOpenNewTabEvent>(this, url);
}

bool DFMWebView::fmEventFilter(const QSharedPointer<DFMEvent> &event, DFMAbstractEventHandler *target, QVariant *resultData)
{
    Q_UNUSED(resultData)

    if (target && target->object() == window()) {
        switch ((int)event->type()) {
        case DFMEvent::Back:
            if (!history()->canGoBack())
                break;

            back();

            return true;
        case DFMEvent::Forward:
            if (!history()->canGoForward())
                break;

            forward();

            return true;
        }
    }

    return false;
}

QWebEngineView *DFMWebView::createWindow(QWebEnginePage::WebWindowType type)
{
    if (type != QWebEnginePage::WebBrowserWindow)
        return Q_NULLPTR;

    DFMWebView *lastCreateWebView = DFMWebViewPrivate::lastCreateWebView;

    DFMEventDispatcher::instance()->processEvent<DFMOpenNewWindowEvent>(this, QList<DUrl>() << DUrl("http://"));

    if (lastCreateWebView == DFMWebViewPrivate::lastCreateWebView)
        return Q_NULLPTR;

    return DFMWebViewPrivate::lastCreateWebView;
}

void DFMWebView::contextMenuEvent(QContextMenuEvent *event)
{
    const QWebEngineContextMenuData &data = page()->contextMenuData();
    const DUrl url = data.linkUrl();

    if (url.isEmpty()) {
        return QWebEngineView::contextMenuEvent(event);
    }

    QMenu menu(this);
    menu.addAction(pageAction(QWebEnginePage::OpenLinkInNewWindow));

    connect(menu.addAction(tr("Open in New Tab")), &QAction::triggered, this, [this, url] {
        openLinkInNewTab(url);
    });

    menu.addSeparator();
    menu.addAction(pageAction(QWebEnginePage::DownloadLinkToDisk));
    // Add link to bookmarks...
    menu.addSeparator();
    menu.addAction(pageAction(QWebEnginePage::CopyLinkToClipboard));
    /*if (page()->settings()->testAttribute(QWebEngineSettings::DeveloperExtrasEnabled))
        menu.addAction(pageAction(QWebEnginePage::InspectElement));*/
    menu.exec(mapToGlobal(event->pos()));
}
