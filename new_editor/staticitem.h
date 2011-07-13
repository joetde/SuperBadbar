#ifndef _EDITOR_STATIC_ITEM_H_
#define _EDITOR_STATIC_ITEM_H_

#include "myitem.h"
#include "data.h"

class StaticItem: public MyItem {
	protected:
	int m_zbuffer; // 0 ou 1
	unsigned int m_colVar; // la valeur de la collision variable
	public:
	/*!
	*	@brief Constructeur
	*	@param item L'objet à encapsuler
	*	@param fileName Le nom du fichier, contenant "statics/chemindufichier"
	*/
//~ 	StaticItem(QGraphicsItem *item, QString fileName, int buffer = 0);
	StaticItem(QGraphicsScene *scene, QString fileName, int buffer = 0, unsigned int varCol = 0);
	
	/*!
	*	@brief Destructeur
	*/
	~StaticItem();
	
	/*!
	*	@brief Cree une instance identique a l'instance actuelle
	*	@param scene La scene de l'editeur
	*	@return Un pointeur vers la copie
	*/	
	virtual MyItem *duplicate(QGraphicsScene *scene);

	/*!
	*	@brief Sauvegarde l'objet dans out
	*	@param out Le flux dans lequel on doit sauvegarder
	*/
	virtual void saveItem(QTextStream &out);
	
	/*!
	*	@brief ajoute l'objet correctement à data
	*	@param data Le conteneur d'objets
	*	@param push_front Indique si l'item doit etre positionne en tete ou en queue
	*/
	virtual void addToData(Data *data, bool push_front = true);
	
	virtual void edit();

	/*!
	*	@brief transforme le nom du fichier ecrit dans un .lvl
	*	en le chemin relatif vers l'image de l'objet depuis l'editeur
	*	@return Ce chemin
	*/
	static QString picPathFromEditor(QString fileName);
	
	protected:
		
	virtual void setStaticZBuffer(int buffer);

};


#endif
