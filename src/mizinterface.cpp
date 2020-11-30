#include "mizinterface.h"
#include <qdebug.h>

const int MizInterface::EXTRACTION_FAILURE = -1;

MizInterface::MizInterface(const QString& fileName):
    m_archivePath{fileName}
{
    qDebug()<<"open archive "<<fileName;
    int readError = 0;
    m_currentZipTree =  zip_open(fileName.toLocal8Bit().data(), ZIP_RDONLY, &readError);

    if(readError != ZIP_ER_OK)
    {
        qWarning()<<"error "<< readError <<" opening file "<<fileName ;
    }
    if(nullptr == m_currentZipTree)
    {
        qWarning()<<"zip file not opened";
    }
    else{
        qDebug()<<zip_get_num_entries(m_currentZipTree, ZIP_FL_UNCHANGED)<<" files in this archive";
    }
}

MizInterface::~MizInterface()
{
    qDebug()<<"close "<<m_archivePath;
    zip_close(m_currentZipTree);
}

TMizContentFile MizInterface::extractContent(QString innerFileName)
{
    TMizContentFile result = nullptr;
    if(nullptr != m_currentZipTree)
    {
        int fileIndex = zip_name_locate(m_currentZipTree, innerFileName.toUtf8().constData() , ZIP_FL_NOCASE);
        QString content;
        if(extractFile(fileIndex, content) == ZIP_ER_OK)
        {
            result = TMizContentFile(new MizContentFile(innerFileName));
            result->setContent(content);
        }
    }
    else{
        qWarning()<<"extractContent of invalid archive";
    }
    return result;
}


int MizInterface::extractFile(int fileIndex, QString& output)
{
    int result = EXTRACTION_FAILURE;
    zip_stat_t fileStat;
    zip_stat_index(m_currentZipTree, fileIndex, ZIP_FL_UNCHANGED, &fileStat);
    if (zip_stat(m_currentZipTree, fileStat.name, 0, &fileStat) == -1)
    {
        qWarning() << zip_strerror(m_currentZipTree);
        result = ZIP_ER_READ;
    }

    zip_file_t* file_zip = zip_fopen(m_currentZipTree, fileStat.name, ZIP_FL_UNCHANGED);
    if (!file_zip)
    {
        qWarning() << zip_strerror(m_currentZipTree);
        result =  ZIP_ER_READ;
    }

    char* readFile = new char[(size_t)(fileStat.size + 1)]{ 0 };
    if (zip_fread(file_zip, readFile, (size_t)(fileStat.size)) != fileStat.size)
    {
        qWarning() << zip_strerror(m_currentZipTree);
        delete[] readFile;
        readFile = nullptr;
    }
    else{
        result = ZIP_ER_OK;
        output = QString(readFile);
    }

    return result;
}

MizContentFile::MizContentFile(QString fileName):
    m_fileName{fileName}
{

}

QString MizContentFile::content() const
{
    return m_content;
}

bool MizContentFile::getIsLoaded() const
{
    return isLoaded;
}

void MizContentFile::setContent(const QString &content)
{
    if(content.length() > 0){isLoaded = true;}
    m_content = content;
}
