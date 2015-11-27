/*
 * validationFormat.cpp
 *
 *  Created on: 2015-09-26
 *      Author: mitre319
 *      name: Michel Tremblay
 */

#include <cstdlib>
#include <iostream>
#include <string>
#include <sstream>
#include <stdlib.h>
#include "validationFormat.h"
#include <map>

/**
 * \brief un fichier d'utilitaire de validation
 */
using namespace std;
namespace util
{

/**
 * \brief valide une ligne GeoJson selont une spécification déterminé.
 * \param[in] string p_ligne une String GeoJson
 * \param[out] ostringstream p_parametres pour retourner les paramètres retrouvé dans la CVS
 * \return boolean
 */
bool valideLigneGEOJSON (string& p_ligne, ostringstream& p_parametres)
{
	bool resultat = false;
	string nomPropriete[] = {"ID","COTE_RUE","LECT_MET","SEGMENT_RU","DIRECTION","NOM_TOPOG","NO_BORNE","NO_CIVIQ","ID_VOIE_PUB","GEOM"};

	unsigned pos = p_ligne.find("\"ID\":"); //Première position à trouver, cherche le bon point dans la string.
	string values = p_ligne.substr(pos); //Création d'une substring qui par à partie de l'id
	string properties[10]; //Tableau qui contiendra les 10 valeurs.
	try{
		for(int i = 0; i < 10; i++){
			pos = values.find(":"); //on trouve le : (la valeur à retourner suivra)
			string tempValue = values.substr(pos+1,1); //On regarde si la valeur suivant est un " ou pas. Les null et certains chiffres n'ont pas de "
			if(tempValue == "\""){
				values = values.substr(pos+2); //Si c'est une string, il faut avancer d'un point de plus
				pos = values.find("\""); //pour la fin de la valeur, on trouve le prochain "
			}
			else{
				values = values.substr(pos+1); // si c'est un chiffre sans " ou null, il ne faut pas avancer plus.
				pos = values.find(","); //pour la fin de la valeur on trouve la prochaine ,
			}
			properties[i] = values.substr(0,pos); //La valeur a mettre au tableau est donc du point 0 jusqu'a pos
			if(i != 7 && i!= 8){//On passe les point 7 et 8 (NO_CIVIQ et ID_VOIE_PUB)
			p_parametres << nomPropriete[i] << " : " << properties[i] << endl; //Ajout au ostringstream de la valeur
			}
			if(i == 9){ // la dixième position est le GEOM
				if(validerGeom(properties[i])){ //on va verifier si la derniere valeur est bien un GEOM
				resultat = true;
				}
				else{
					resultat = false;
				}
			}
		}
	}
	catch(int e){
		resultat = false;
	}
	return resultat;
}
/**
 * \brief valide une ligne CVS selont une spécification déterminé.
 * \param[in] string p_ligne une String CVS
 * \param[out] ostringstream p_parametres pour retourner les paramètres retrouvé dans la CVS
 * \return boolean
 */
bool valideLigneCVS (string& p_ligne, ostringstream& p_parametres)
{
	bool resultat = false;
	string nomPropriete[] = {"ID","COTE_RUE","LECT_MET","SEGMENT_RU","DIRECTION","NOM_TOPOG","NO_BORNE","LONGITUDE","LATITUDE"};
	int i = 0;
	while (p_ligne.length() > 0){
		unsigned int pos = p_ligne.find("|");
		if (i > 8){
			resultat = false; //si il y a plus de 8 variable, c'est pas valide.
						break;
		}
			string subString;
		if(pos == string::npos){
			subString = p_ligne; //On prend la derniere string;
			p_ligne = "";//Nous somme à la dernière valeur de la ligne. On vide la variable.
			}
		else{
			subString = p_ligne.substr(0, pos);//ON prend la string courrante.
			p_ligne = p_ligne.substr(pos+1);//on remplate p_ligne avec les prochainnes valeur
		}

		p_parametres << nomPropriete[i] << " : " << subString << endl;

		if (i == 7 || i == 8){ //si on est à la propriete 7 ou 8, lat ou long, le chiffre doit être un float.
			if(!validerFloat(subString)){
				resultat = false;
			}
			else if (i == 8){
				resultat = true;
			}

		}
		i++;
	}
	return resultat;
}
/**
 * \brief une fonction pour valider GEOM
 * \param[in] string p_geom qui représente 2 point geom dans une string
 * \return boolean
 */
bool validerGeom (const string& p_geom)
{
	int startPos = p_geom.find("(");
	string geom = p_geom.substr(startPos+1);
	bool resultat = false;
	char* pEnd;
	double latit = strtod(geom.c_str(),&pEnd); //On essaie de mettre la valeur de latitude en double
	double longit = strtod(pEnd,NULL); //on essaie de mettre la valeur de longitude en double
	if(latit != 0 && longit != 0){ //si la valeur est passé, elle ne seront pas à 0, donc c'est bien des chiffres.
		resultat = true;
	}

	return resultat;
}
/**
 * \brief Fonction pour valide si le numero recu en string est un float
 * \param[in] string number une string qui représente un numero
 * \return Boolean
 */
bool validerFloat(const string& number){ //validation si c'est un chiffre à virgule (point)
	float fnumber;
	unsigned int pos = number.find(","); //la fonction n'accepte que des chiffre avec des point, donc si il y a une virgule, nous devons la remplacer.
	string fixedNumber = number;
	fixedNumber.replace(pos,1,".");
	istringstream floatTester(fixedNumber);
	floatTester >> fnumber;
	bool result = (floatTester.eof() && !floatTester.fail() && fnumber != 0); //si l'envoie de la string en float a passé, et que le chiffre n'Est pas 0, on retourne true.
	return result;
}
/**
 * \brief Une fonction pour vérifier la validité d'un point cardinal
 * \param[in] string p_cardinalite, Le point que nous voulons vérifier si il est valide
 * \return Boolean
 */
bool validerPointCardinal(const string& p_cardinalite)
{
	bool valide = false;
	const char* cardinaleValide[] = {
			"Nord",
			"Sud",
			"Est",
			"Ouest",
			"null"
	};
	for (unsigned int i = 0; i < 5;i++){
		if(p_cardinalite == cardinaleValide[i] || p_cardinalite.empty() || p_cardinalite == "" || p_cardinalite == "Empty")
		{
			valide = true;
		}
	}
	return valide;
}

} /* namespace utilitaire */


