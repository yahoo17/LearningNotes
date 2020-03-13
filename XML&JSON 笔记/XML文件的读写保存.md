XML文件的读写保存



```C++
/*读XML文档
*/
void readXML()
{
    QFile testfile(qApp->applicationDirPath()+"Data/Options.opt");
    if(!testfile.exists())
        return;
    if(file.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        QXmlStreamReader testreader(&file);
            while(testreader.atEnd())
            {
                QXmlStreamReader::TokenType type=testreader.readNext();
                if(type==QXmlStreamReader::StartElement&&testreader.name()=="complier")
                {
                    this->loadDataFromXML_Help(&testreader);
                }

            }
    }
}
/*读xml文档*/
void SE_OPTIONS_COMPILER::loadDataFromXML_Help(QXmlStreamReader *reader)
{
    while(!reader->atEnd())
    {
        QXmlStreamReader::TokenType type = reader->readNext();
        if(type == QXmlStreamReader::EndElement && reader->name() == "compilers")
            break;
        if(type == QXmlStreamReader::StartElement)
        {
            if(reader->name() == "CMakePath")
            {
                reader->readNext();
                ui->lineEdit_Path->setText(reader->text().toString());
            }
            if(reader->name() == "compiler")
            {
                QString name;
                QString path;
                QString vcVersion;
                name = reader->attributes().value("name").toString();
                while(!reader->atEnd())
                {
                    type = reader->readNext();
                    if(type == QXmlStreamReader::EndElement && reader->name() == "compiler")
                        break;
                    if(type == QXmlStreamReader::StartElement && reader->name() == "path")
                    {
                        reader->readNext();
                        path = reader->text().toString();
                    }
                    if(type == QXmlStreamReader::StartElement && reader->name() == "vcVersion")
                    {
                        reader->readNext();
                        vcVersion = reader->text().toString();
                    }
                }
                this->newCompiler(name, path,vcVersion);
            }
            if(reader->name() == "flag")
            {
                reader->readNext();
                m_flag = reader->text().toInt();
            }
        }
    }
    if(m_flag > -1 && m_flag < ui->m_tableWidget->rowCount())
    {
        QWidget *widget = ui->m_tableWidget->cellWidget(m_flag, 0);
        QCheckBox *checkBox = qobject_cast<QCheckBox*>(widget->children().at(1));
        checkBox->setChecked(true);
        updateToGlobal(ui->m_tableWidget->item(m_flag, 1)->text(),ui->m_tableWidget->item(m_flag, 2)->text(),ui->m_tableWidget->item(m_flag, 3)->text());
    }


}
/*

这是在写XML文档
*/

void func(QXmlStreamWriter( *writer))
{
    QString path="C://";
    QString name="yanhao";
    QString version="18.04 LTS";
    writer->writeTextElement("CMakePath",path);
    writer->writeStartElement("compliers");
    for(int i=0;i<10;i++)
    {   
        writer->writeStartElement("compiler");
        writer->writeAttribute("name",name);
        writer->writeTextElement("path",path);
        writer->writeTextElement("vcVersion",version);
        writer->writeEndElement();
    }
}
```

