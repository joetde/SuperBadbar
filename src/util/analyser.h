/**
 * WARNING : classe à refaire
 * Description: La classe Analyser sert à lire des fichiers et à les interpréter
 * Utilisation: Utiliser open pour ouvrir un fichier.
 * 				L'interpréter avec les méthodes appropriées
 *				Le fermer avec close
 * Fonctionnement: 	Lors de la lecture du fichier, m_current représente le prochain caractère à analyser
 *				Il est lu à chaque fois lu à l'avance par convention
**/


#ifndef _ANALYSER_
#define _ANALYSER_

#include <string>
#include <fstream>


#define COLL_EXT ".col"
#define PICS_EXT ".bmp"


class Analyser {

private:
	bool m_opened;
	std::ifstream *m_file;




public:
	/*!
	* @brief Constructeur par défaut
	*/
	Analyser();

	/*!
	* @brief Destructeur par défaut
	*/
	~Analyser();

 	/*!
	* @brief ouvre le fichier nommé file
	* @param file nom du fichier à ouvrir
	* @return renvoie 1 si l'ouverture est un succès, 0 sinon
	*/
	uint32_t open(std::string file);

  	/*!
	* @brief ferme le fichier ouvert
	*/
	void close();

   	/*!
	* @brief Saute les séparateurs dans le fichier ouvert
	*
	* Un séparateur est un espace, un retour à la ligne ou une ligne suivant //
	* @warning non fonctionnelle sous windows 
	*/
	void jump_separators();

	/*!
	* @brief Positionne le curseur après la première occurence de str à partir du début du fichier
	*
	* Si la chaine n'est pas trouvée, le curseur est positionné à la fin du fichier.
	*
	* @param str La chaine cherchée
	*/
	void find_string(std::string str);

	/*!
	* @return vrai si on est à la fin d'une section (si le caractère suivant est un '!'
	* @warning non fonctionnelle sur windows (à cause de jump_separators)
	*/
	bool end_of_section();
	
	/*!
	* @brief Lit et renvoie le prochain int du fichier, en sautant les séparateurs
	*
	* @return l'int lu
	*/
	int read_int();

	/*!
	* @brief Lit et renvoie le prochain uint32_t du fichier, en sautant les séparateurs
	*
	* @return l'uint32_t lu
	*/
	uint32_t read_uint32_t();

	/*!
	* @brief Lit et renvoie le prochain string du fichier (jusqu'au prochain espace), en sautant les séparateurs
	*
	* @return le string lu
	*/
	std::string read_string();
	
	char read_char();



};






#endif
