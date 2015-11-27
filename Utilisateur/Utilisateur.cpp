/**
 * \file Utilisateur.cpp
 * \brief Utilisation du System de Borne
 * \author Michel Tremblay
 * \date 2015-11-23
 */

#include <stdlib.h>
#include "RegistreBorne.h"
#include "BorneFontaine.h"
#include "BorneStationnement.h"
#include <iostream>
#include <string>
#include "validationFormat.h"


using namespace tp;
using namespace std;

void ajoutDeBorne(RegistreBorne& myRegistre, const string& type);
void ajoutDeBorneFontaine(RegistreBorne& myRegistre,
		int p_idBorne, string& p_direction,
		string& p_nomTopographique, double p_longitude,
		double p_latitude);
void ajoutDeBorneStationnement(RegistreBorne& myRegistre,
		int p_idBorne, string& p_direction,
		string& p_nomTopographique, double p_longitude,
		double p_latitude);
int getIntLine();
double getDoubleLine();
string getPointCardinal();
string getNotNull(const string& p_ville = "");
string typeBorneValidator();

/**
 * \brief Le Main de Utilisateur
 */
int main() {
	RegistreBorne myRegistre("Mon Registre de Borne");
	cout << "Nous allons créer une borne, quelque questions vous seront posé." << endl;
	cout << "Commencons par une Borne Fontaine. " << endl;
	ajoutDeBorne(myRegistre,"Fontaine");
	cout << endl << "Maintenant entrons une Borne de Stationnement. " << endl;
	ajoutDeBorne(myRegistre,"Stationnement");
	cout << endl << "Les bornes ont été entré avec succès, voici leur représentation :" << endl;
	cout << myRegistre.reqRegistreBorneFormate() << endl;
    return 0;
}
/**
 * \brief Une méthode pour ajouter une borne de différent type dans le registre
 * \param[in] myRegistre Objet RegistreBorne, le registre où sera ajouté la borne
 * \param[in] type string le type de borne à ajouter (Fontaine,Stationnement)
 */
void ajoutDeBorne(RegistreBorne& myRegistre, const string& type){
	//Variable de Borne de Base
	string tempString;
	int p_idBorne; //Le numéro de la borne. Not-Null
	string p_direction; //Le côté du centre de chaussé ou l'intersection dans le cas t'un terre-plein.
	string p_nomTopographique; //Le nom topographique(générique,liaison,spécifique,direction) du centre de la chaussée.
	double p_longitude;
	double p_latitude;

	cout << "Choisissez un numéro de borne : ";
	p_idBorne = getIntLine();
	cout << endl << "Choisissez le côté du centre de chaussé (Point cardinal valide) : ";
	p_direction = getPointCardinal();
	cout << endl << "Entrez l'adresse la plus près de la borne : ";
	p_nomTopographique = getNotNull();
	cout << endl << "Entrez la longitude de la borne : ";
	p_longitude = getDoubleLine();
	cout << endl << "Entrez la latitude de la borne : ";
	p_latitude = getDoubleLine();

	if(type == "Fontaine")
	{
		ajoutDeBorneFontaine(myRegistre, p_idBorne, p_direction, p_nomTopographique, p_longitude, p_latitude);
	}
	else if (type == "Stationnement")
	{
		ajoutDeBorneStationnement(myRegistre, p_idBorne, p_direction, p_nomTopographique, p_longitude, p_latitude);
	}
}

/**
 * \brief méthode qui va créer et ajouter une borne fontaine dans le registre
 * \param[in] myRegistre Objet RegistreBorne, le registre où sera ajouté la borne
 * \param[in] p_idBorne int Le numéro de la borne. Not-Null
 * \param[in] p_direction string Le côté du centre de chaussé ou l'intersection dans le cas t'un terre-plein.
 * \param[in] p_nomTopographique string Le nom topographique(générique,liaison,spécifique,direction) du centre de la chaussée.
 * \param[in] p_longitude double La longitude de la borne
 * \param[in] p_latitude double La latitude de la borne
 */
void ajoutDeBorneFontaine(RegistreBorne& myRegistre,
		int p_idBorne, string& p_direction,
		string& p_nomTopographique, double p_longitude,
		double p_latitude)
{
	//Variable pour Borne Fontaine
	string p_ville; //La ville de la borne
	string p_arrondissement; //L'arrondissement de la borne, qui est requis si la ville est <Quebec>

	cout << endl << "Entrez le nom de la ville de la borne : ";
	p_ville = getNotNull();
	cout << endl << "Entrez l'arrondissement de la borne, qui est requis si la ville est <Quebec> : ";
	p_arrondissement = getNotNull(p_ville);
	BorneFontaine myBorneFontaine(p_idBorne,p_direction,p_nomTopographique,p_longitude,p_latitude,p_ville,p_arrondissement);
	myRegistre.ajouteBorne(myBorneFontaine);
}

/**
 * \brief méthode qui va créer et ajouter une borne de Stationnement dans le registre
 * \param[in] myRegistre Objet RegistreBorne, le registre où sera ajouté la borne
 * \param[in] p_idBorne int Le numéro de la borne. Not-Null
 * \param[in] p_direction string Le côté du centre de chaussé ou l'intersection dans le cas t'un terre-plein.
 * \param[in] p_nomTopographique string Le nom topographique(générique,liaison,spécifique,direction) du centre de la chaussée.
 * \param[in] p_longitude double La longitude de la borne
 * \param[in] p_latitude double La latitude de la borne
 */
void ajoutDeBorneStationnement(RegistreBorne& myRegistre,
		int p_idBorne, string& p_direction,
		string& p_nomTopographique, double p_longitude,
		double p_latitude)
{
	//Variable pour borne Stationnement
	string p_type; //Le type de borne de stationnement, peut être <<stationnement>> ou <<paiement>>
	double p_lectureMetrique; //La distance mesurée à partir du début du tronçon dans le sens des numéros d'immeuble. Doit être > 0
	int p_segmentRue; // l'identifiant du segment de voie publique. Il doit être > 0
	string p_numBorne; //Le numéro de la borne. Il doit être non vide.
	string p_coteRue; //Le côté par rapport au centre de chaussée où est la borne. Doit correspondre à un point cardinal.

	cout << endl << "Le type de borne de stationnement, peut être <stationnement> ou <paiement>: ";
	p_type = typeBorneValidator();
	cout << endl << "La distance mesurée en mètres à partir du début du tronçon dans le sens des numéros d'immeuble: ";
	p_lectureMetrique = getDoubleLine();
	cout << endl << "l'identifiant du segment de voie publique: ";
	p_segmentRue = getIntLine();
	cout << endl << "Le numéro de la borne: ";
	getline(cin,p_numBorne);
	cout << endl << "Le côté par rapport au centre de chaussée où est la borne. Doit correspondre à un point cardinal: ";
	p_coteRue = getPointCardinal();


	//Creation de la borne et ajout dans le registre
	BorneStationnement myBorneStationnement(p_idBorne,p_direction,p_nomTopographique,p_longitude,p_latitude,p_type,p_lectureMetrique,p_segmentRue,p_numBorne,p_coteRue);
	myRegistre.ajouteBorne(myBorneStationnement);
}

/**
 * \brief une méthode pour aller chercher un Int avec getline, et s'assurer que c'est un chiffre valide sans exception
 * \post le chiffre doit >= 1
 * \return un int
 */
int getIntLine()
{
	int toReturn;
	do
	{
		string tempString;
		getline(cin,tempString);
		toReturn = strtol(tempString.c_str(),NULL,10);
		if(toReturn == 0)
		{
			cout << endl << "Ce n'est pas un chiffre valide, réessayez :";
		}
	}
	while(toReturn<1);
	return toReturn;
}
/**
 * \brief une méthode pour aller chercher un double avec getline, et s'assurer que c'est un double valide sans exception
 * \post le chiffre doit != 0.0
 * \return un double
 */
double getDoubleLine()
{
	double toReturn;
	do
	{
		string tempString;
		getline(cin,tempString);
		toReturn = strtod(tempString.c_str(),NULL);
		if(toReturn == 0.0)
		{
			cout << endl << "Ce n'est pas un chiffre valide, réessayez :";
		}
	}
	while(toReturn == 0.0);
	return toReturn;
}
/**
 * \brief une méthode pour aller chercher un Point Cardinal avec getline, et s'assurer que c'est un point cardinal valide
 * \post N'accepte qu'un point cardinal valide entre : Est,Ouest,Nord,Sud
 * \return un string
 */
string getPointCardinal()
{
	string point;
	bool valide = false;
	do
	{
		getline(cin,point);
		valide = util::validerPointCardinal(point);
		if(!valide)
		{
			cout << endl << "Ce n'est pas un point cardinal valide (Est,Ouest,Nord,Sud), réessayez :";
		}
	}
	while(!valide);
	return point;
}
/**
 * \brief une méthode pour aller chercher un string avec getline, et s'assurer que c'est une string non vide
 * \param[in] p_ville string avec valeur par default de "" (optionnel)
 * \post Si la ville n'est pas Quebec, la string peut être vide. Si il n'y a pas de ville, la string ne peut être vide
 * \return un string
 */
string getNotNull(const string& p_ville)
{
	string gotString;
	do
	{
		getline(cin,gotString);
		if((gotString.empty() && p_ville == "Quebec") || (gotString.empty() && p_ville.empty()))
			{
				cout << endl << "Nous avons besoin d'une réponse, réessayez :";
			}
	}
	while((gotString.empty() && p_ville == "Quebec") || (gotString.empty() && p_ville.empty()));
	return gotString;
}

/**
 * \brief une méthode pour aller chercher un string avec getline, et s'assurer que c'est une string non vide
 * \post N'accepte que 2 valeurs : stationnement ou paiement
 * \return un string
 */
string typeBorneValidator()
{
	string type;
	bool valide = false;
	do{
		getline(cin,type);
		if(type != "stationnement" || type != "paiement")
		{
			cout << endl << "Nous avons besoin d'un type valide (stationnement, paiement) :";
		}
		else
		{
			valide = true;
		}
	}
	while(!valide);
	return type;
}





