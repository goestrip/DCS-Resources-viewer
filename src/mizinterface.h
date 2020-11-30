#ifndef MIZINTERFACE_H
#define MIZINTERFACE_H
#include <QString>
#include <QSharedPointer>

#include "zip.h"

class MizContentFile
{
public:
    MizContentFile(QString fileName);
    QString content() const;
    bool getIsLoaded() const;
    void setContent(const QString &content);

private:
    const QString m_fileName;
    QString m_content;
    bool    isLoaded;

};
typedef QSharedPointer<MizContentFile> TMizContentFile;


class MizInterface
{
    static const int EXTRACTION_FAILURE;
public:
    MizInterface(const QString& fileName);
    virtual ~MizInterface();
    TMizContentFile extractContent(QString innerFileName);

private:

    int extractFile(int fileIndex, QString& output);

    const QString m_archivePath;
    zip_t*  m_currentZipTree;
};
typedef QSharedPointer<MizInterface> TMizInterface;

#endif // MIZINTERFACE_H
