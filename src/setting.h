#ifndef SETTING_H
#define SETTING_H


//#include <QObject>
#include <QHash>

/**
 * @author Семенов С.А.
 *
*/

//enum VarianType{INT,DOUBLE,STRING,OTHER};

//class QDomDocument;
//class QDomElement;
//class QTreeWidgetItem;
// /**
// * @class ConfigApp
// *	Клас работы с настройками программы поддерживает открытия файла настроек его сохранение задание и чтение натроек. Класс является синголтоном. Для начала работы с ним
// *необходима иницилизация через открытия файла настроек.Делается следующим образом
// *@code
// *ConfigApp *configApp = ConfigApp::Instance();
// *configApp->slotOpen(filename);
// *@endcode
// * после чего происходит пере/инициализация настроек;
// *  @todo Cltkfnm hfpltkmyjt cj[hfytybt yfcnhjtr
// *	@todo Добавить Defauld List
// *	@todo Добавить условную компиляцию для возможности работы без GUI
// *	@todo сброс в стандартные настройки.(Уточнить общий или по конкретным пораметрам)
// *	@todo сброс к первоночальным настройкам.
// */
//class ConfigApp : public QObject{
//    Q_OBJECT
//	friend class SettingWindow;
//private:
//	//! @brief экземпляр класса
//	static ConfigApp *mcaSelf;
//	//! @brief Главный хеш настноек
//	QHash<QString, QVariant> mhSetting;
//	//! @brief настройки полученные при загрузки(заполняется в момент изменения основных)
//	//! @todo переделать на создание при загрузки
//	QHash<QString, QVariant> *mhOldSetting;
//	//! @brief лист полей для дерева
//	QTreeWidgetItem* mTreeSetting;
//	//! @brief XML документ
//	QDomDocument *p_mdm;
//	//! @brief имя файла загружнных настроек
//	QString mstrFileName;
//	QString mstrIniFileName;
//	//funtion
//	//! @brief рекурсивная функция чтения тегов
//	void readTag(QDomElement &docElem, QTreeWidgetItem *twi=0);
//	//! @brief рекурсивное построения документа для сохранения.
//	//! @warning Следует учитывать что если значение ключа отличается от возможных значений то это значение будет включенно туда.
//	void saveTag(QDomElement &docElem);
//	//! @brief функция приводит значения .
//	void pachSetting(QHash<QString, QVariant> *modSetting);
//	QTreeWidgetItem *getTree();
//protected:
//  explicit ConfigApp(QObject *parent = 0);
//public:
//	//! @brief получить указатель на класс
//	static ConfigApp* Instance();
//	//! @brief положить, изменить значение
//	int setValue(const QString &key, const QVariant &value);
//	//! @brief получить значение по ключу
//	QVariant value(const QString &key)const;
//	//! @brief возвращает все настройки с ключами
//	QString getAllSetting();
//	void setIniFileName(const QString &fileName){mstrIniFileName=fileName;}
//signals:

//public slots:
//	//! @brief открывает файл настроек с данным именем
//	int init(const QString &filename);
//	//! @brief сохраняет настройки с указанным при открытии именем
//	void slotSave();
//	//! @brief сохраняет настройки в произвольный файл
//	//! @warning Следует учитывать что если значение ключа отличается от возможных значений то это значение будет включенно туда.
//	void slotSaveAs(const QString &filename);
//	void slotIniSaveAs();
//	void slotIniLoad();


class QString;
class QVariant;
class Setting
{
	static Setting *mSelf;
	//! @brief Главный хеш настноек
	QHash<QString, QString> *m_phSetting;
public:
	//! @brief получить указатель на класс
	static Setting* Instance();
	//! @brief положить, изменить значение
	int setValue(const QString &key, const QString &value);
	//! @brief получить значение по ключу
	QString value(const QString &key)const;
	~Setting();
protected:
	explicit Setting();
};

#endif // SETTING_H
