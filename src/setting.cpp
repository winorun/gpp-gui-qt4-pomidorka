#include "setting.h"

#include <QString>

Setting *Setting::mSelf=0;

Setting::Setting()
{
	m_phSetting = new QHash<QString, QString>;
}

Setting::~Setting(){
	delete m_phSetting;
}

Setting *Setting::Instance(){
	if(!Setting::mSelf)Setting::mSelf= new Setting();
	return Setting::mSelf;
}

int Setting::setValue(const QString &key, const QString &value){
	if(!Setting::mSelf)return 1;
//	if(m_phSetting->contains(key))return 1;
	m_phSetting->insert(key,value);
	return 0;
}

QString Setting::value(const QString &key)const{
	if(!Setting::mSelf)return 0;
	return m_phSetting->value(key);
}


/*
void ConfigApp::slotIniSaveAs(){
	QString filename = mstrIniFileName.isEmpty()?mhSetting["sSettingPath"].toString():mstrIniFileName;
	filename+=".ini";
	QFile file(filename);
	if (!file.open(QIODevice::WriteOnly))return;
	QTextStream stream(&file);

	QDomNodeList n = p_mdm->elementsByTagName("param");
	int s=n.size();
	for(int i=0;i<s;i++)
	{
		if(n.at(i).isElement()){
			QDomElement e = n.at(i).toElement();
			QString str = e.attribute("key")+" = "+mhSetting[e.attribute("key")].toString();
			stream << str << endl;
//			qDebug(str.toAscii());
		}
	}
	file.close();
}

void ConfigApp::slotIniLoad(){
	QString filename = mstrIniFileName.isEmpty()?mhSetting["sSettingPath"].toString():mstrIniFileName;
	filename+=".ini";
	QFile file(filename);
	if (!file.open(QIODevice::ReadOnly))return;
	QTextStream stream(&file);
	while(!stream.atEnd()){
		QString strKey,strPar;
		QString strin=stream.readLine();
		int pos = strin.indexOf("=");
		if(pos!=-1){
			strKey=strin.left(pos);
			strKey=strKey.trimmed();
			strPar=strin.right(strin.size()-pos-1);
			strPar=strPar.trimmed();
			if(mhSetting.contains(strKey)){
				mhSetting[strKey]=strPar;
			}
		}

	}

	file.close();
*/

/*
ConfigApp::ConfigApp(QObject *parent):QObject(parent){
	p_mdm=0;
	mhOldSetting=0;
	mTreeSetting = 0;
	mstrIniFileName = "";
}

int ConfigApp::init(const QString &filename){

	mstrFileName=filename;
	QFile file(mstrFileName);
	if (!file.open(QIODevice::ReadOnly))return 1;

	if(p_mdm)delete p_mdm;

	p_mdm= new QDomDocument();

	if (!p_mdm->setContent(&file)) {
		file.close();
		return 2;
	}
	file.close();

	mhSetting.clear();
	if(mTreeSetting) delete mTreeSetting;
	mTreeSetting = new QTreeWidgetItem();
	if(mhOldSetting) delete mhOldSetting;
	QDomElement qde=p_mdm->documentElement();

	readTag(qde);
	mhOldSetting=new QHash<QString, QVariant>(mhSetting);
	return 0;
}

void ConfigApp::readTag(QDomElement &docElem,QTreeWidgetItem *twi){
	QTreeWidgetItem *tw;
	QDomNode n = docElem.firstChild();
	while(!n.isNull()) {
		QDomElement e = n.toElement(); // try to convert the node to an element.
		if(!e.isNull()){
			if(e.tagName()!="param"){
				tw= new QTreeWidgetItem();
				tw->setText(0, e.tagName());
				if(twi==0)
					mTreeSetting->addChild(tw);
				else
					twi->addChild(tw);
				readTag(e,tw);
			}else {
				mhSetting[e.attribute("key")] = QVariant(e.attribute("values",e.attribute("default")));
			}
		}
	n = n.nextSibling();
	}
}

void ConfigApp::slotSave(){
	slotSaveAs(mstrFileName);
}

void ConfigApp::slotSaveAs(const QString &filename){
	QDomElement docElem = p_mdm->documentElement();
	saveTag(docElem);
	QFile file(filename);
	if (!file.open(QIODevice::WriteOnly))return;
	QTextStream stream(&file);
	p_mdm->save(stream,2);
	file.close();
}


void ConfigApp::saveTag(QDomElement &docElem){
	QDomNode n = docElem.firstChild();
	while(!n.isNull()) {
		QDomElement e = n.toElement();
		if(!e.isNull()){
			if(e.tagName()=="param"){
				e.setAttribute("values",mhSetting.value(e.attribute("key")).toString());
				if(e.attribute("edit")!="bool"){
					QDomNodeList n = e.elementsByTagName("values");
					int findElement=0;
					int s=n.size();
					for(int i=0;i<s;i++)
					{
						if(n.at(i).isElement()){
							QDomElement e1 = n.at(i).toElement();
							if(e1.text()==mhSetting.value(e.attribute("key")).toString())findElement=1;
						}
					}
					if(!findElement){
						QDomElement e1=p_mdm->createElement("values");
						QDomText textElement = p_mdm->createTextNode(mhSetting.value(e.attribute("key")).toString());
						e1.appendChild(textElement);
						e.appendChild(e1);
					}
				}
			}else saveTag(e);
		}
	n = n.nextSibling();
	}
}



void ConfigApp::pachSetting(QHash<QString, QVariant> *modSetting){
	QHashIterator<QString, QVariant> i(*modSetting);
	 while (i.hasNext()) {
		 i.next();
		 if(i.value()!=mhSetting.value(i.key()))mhSetting[i.key()]=i.value();
	 }
}

QString ConfigApp::getAllSetting(){
	QHash<QString, QVariant>::const_iterator i = mhSetting.constBegin();
	QString rezult;
	 while (i != mhSetting.constEnd()) {
		 rezult+= i.key() +QString(" : ")+QVariant(i.value()).toString() +QString("\n");
		 ++i;
	 }
	 return rezult;
}

QTreeWidgetItem* ConfigApp::getTree(){
	return mTreeSetting->clone();
}

void ConfigApp::slotIniSaveAs(){
	QString filename = mstrIniFileName.isEmpty()?mhSetting["sSettingPath"].toString():mstrIniFileName;
	filename+=".ini";
	QFile file(filename);
	if (!file.open(QIODevice::WriteOnly))return;
	QTextStream stream(&file);

	QDomNodeList n = p_mdm->elementsByTagName("param");
	int s=n.size();
	for(int i=0;i<s;i++)
	{
		if(n.at(i).isElement()){
			QDomElement e = n.at(i).toElement();
			QString str = e.attribute("key")+" = "+mhSetting[e.attribute("key")].toString();
			stream << str << endl;
//			qDebug(str.toAscii());
		}
	}
	file.close();
}

void ConfigApp::slotIniLoad(){
	QString filename = mstrIniFileName.isEmpty()?mhSetting["sSettingPath"].toString():mstrIniFileName;
	filename+=".ini";
	QFile file(filename);
	if (!file.open(QIODevice::ReadOnly))return;
	QTextStream stream(&file);
	while(!stream.atEnd()){
		QString strKey,strPar;
		QString strin=stream.readLine();
		int pos = strin.indexOf("=");
		if(pos!=-1){
			strKey=strin.left(pos);
			strKey=strKey.trimmed();
			strPar=strin.right(strin.size()-pos-1);
			strPar=strPar.trimmed();
			if(mhSetting.contains(strKey)){
				mhSetting[strKey]=strPar;
			}
		}

	}

	file.close();
}
*/
