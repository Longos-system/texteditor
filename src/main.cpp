/*
 * Copyright (C) 2023 LongOS Team
 */

#include <QGuiApplication>
#include <QApplication>
#include <QQmlApplicationEngine>
#include <QCommandLineParser>
#include <QMetaObject>
#include <QTranslator>
#include <QLocale>
#include <QIcon>
#include <QFile>

#include "documenthandler.h"
#include "highlightmodel.h"
#include "texteditor.h"

QStringList formatUriList(const QStringList &list)
{
    QStringList val;

    for (const QString &i : list) {
        QFileInfo path(i);
        if (path.exists()) {
            QString absPath = path.absoluteFilePath();
            if (!val.contains(absPath, Qt::CaseSensitive))
                val.append(absPath);
        }
        else
            qDebug() << "long-texteditor: " << i << "doesn't exist";
    }

    return val;
}

void openFile(QObject *qmlObj, QString &fileUrl)
{
    QVariant val_return;
    QVariant val_arg(fileUrl);
    QMetaObject::invokeMethod(qmlObj,
                            "addPath",
                            Q_RETURN_ARG(QVariant,val_return),
                            Q_ARG(QVariant,val_arg));
}

void newTab(QObject *qmlObj)
{
    QVariant val_return;
    QVariant val_arg;
    QMetaObject::invokeMethod(qmlObj,
                            "addTab",
                            Q_RETURN_ARG(QVariant,val_return));
}

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QApplication app(argc, argv);
    app.setOrganizationName("longys");

    qmlRegisterType<DocumentHandler>("Long.TextEditor", 1, 0, "DocumentHandler");
    qmlRegisterType<FileHelper>("Long.TextEditor", 1, 0, "FileHelper");

    QCommandLineParser parser;
    parser.setApplicationDescription("A text editor specifically designed for LongOS.");
    parser.addHelpOption();
    parser.setSingleDashWordOptionMode(QCommandLineParser::ParseAsCompactedShortOptions);
    parser.addPositionalArgument("files", "Files", "[FILE1, FILE2,...]");

    parser.process(app);

    HighlightModel m;

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/qml/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);

    engine.load(url);

    QObject *root = engine.rootObjects().first();

    QStringList fileList = formatUriList(parser.positionalArguments());
    if (!fileList.isEmpty()) {
        for (QString &i : fileList)
            openFile(root, i);
    }
    else
        newTab(root);

    QLocale locale;
    QString qmFilePath = QString("zh_CN.qm").arg("/usr/share/long-texteditor/translations/").arg(locale.name());
    if (QFile::exists(qmFilePath)) {
        QTranslator *translator = new QTranslator(QGuiApplication::instance());
        if (translator->load(qmFilePath)) {
            QGuiApplication::installTranslator(translator);
        } else {
            translator->deleteLater();
        }
    }

    return app.exec();
}
