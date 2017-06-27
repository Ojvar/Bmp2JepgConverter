#include <QCoreApplication>
#include <QPixmap>
#include <QDebug>
#include <QString>
#include <QFileInfo>
#include <QDir>
#include <QDirIterator>

using namespace std;

/**
 * @brief pathCombine
 * @param path1
 * @param path2
 * @return
 */
QString pathCombine(const QString& path1, const QString& path2)
{
    return path1.trimmed () +
            (path1.trimmed ().endsWith (QDir::separator ()) ? '\0' : QDir::separator ())
            + path2.trimmed ();
}

/**
 * @brief main
 * @param argc
 * @param argv
 * @return
 */
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    qDebug() << "By Ojvar" << endl;

    if (1 == argc)
    {
        qDebug() << "Usage: ConvertBmpToJepg {folder path}";
        return -1;
    }

    // Get list of files and dir
    QDirIterator it(argv[1], QDirIterator::NoIteratorFlags);

    while (it.hasNext ())
    {
        QString fileStr;
        QFileInfo file (it.next ());

        if (!file.isDir () && (file.completeSuffix ().toLower () == "bmp"))
        {
            fileStr = file.baseName () + ".jpg";
            fileStr = pathCombine (argv[1], fileStr);

            qDebug() << fileStr << " " << file.absoluteFilePath () << endl;

            try
            {
                QImage image;
                image.load (file.absoluteFilePath ());
                image.save (fileStr);

                qDebug()  << " !Converted" << endl;
            }
            catch (exception ex)
            {
                qDebug() << ex.what () << endl;
            }
        }
    }

    return 0; //a.exec ();
}
