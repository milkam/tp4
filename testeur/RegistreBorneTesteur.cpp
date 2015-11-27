/**
 * \file RegistreBorneTesteur.cpp
 * \brief Fichier de Test pour tester Registre de Borne
 * \author Michel Tremblay
 * \date 2015-11-22
 */

#include "RegistreBorne.h"
#include <gtest/gtest.h>
#include <sstream>

using namespace tp;

class RegistreBorneValide: public ::testing::Test
{
public:
	/**
	 * \brief Creation de l'objet pour la fixture
	 */
	RegistreBorneValide() :
			myRegistreBorne("Mon Registre"),
			myBorneFontaine(1,"Sud","8800 24e Avenue",24.0,21.2,"Quebec","Ville Saint je sais pas"),
			myBorneStationnement(2,"Sud","8800 24e Avenue",24.0,21.2,"stationnement",1234.3,387,"498","Nord")

	{
	}
	/**
	 * \brief Creation de l'objet pour la fixture
	 */
	RegistreBorne myRegistreBorne;
	BorneFontaine myBorneFontaine;
	BorneStationnement myBorneStationnement;
};

/**
 * \brief Test de RegistreBorne avec la fixture RegistreBorneValide Test des accesseur
 * Cas Valide : reqNomRegistreBorne retourne "Mon Registre"
 * Cas Valide : La premiere borne en sortie formatté dans reqVBornes retourne myBorneStationnement en sortie formatté
 * Cas Invalide : Le nom du registre n'est pas "Mon Registre"
 * Cas Invalide : Le formattage de la borne sortie du registre n'est pas comme le formattage de la borne de stationnement pure.
 */
TEST_F(RegistreBorneValide,test_Accesseur)
{
	ASSERT_NO_THROW(myRegistreBorne.ajouteBorne(myBorneStationnement));
	ASSERT_EQ(myRegistreBorne.reqNomRegistreBorne(), "Mon Registre");
	ASSERT_EQ(myRegistreBorne.reqVBornes()[0]->reqBorneFormate(),myBorneStationnement.reqBorneFormate());

};
/**
 * \brief Test de RegistreBorne avec la fixture RegistreBorneValide Test des méthode
 * Cas Valide : Aucun problème à ajouter une borne au registre, peu importe le type.
 * Cas Valide : Le sortie de bornes de tout les types est identique à ce qu'on s'attend avec la foncion reqRegistreBorneFormate
 * Cas Invalide : L'ajout d'une borne est problématique
 * Cas Invalide : La sortie de la fonction formatté n'est pas comme on s'y attend.
 */
TEST_F(RegistreBorneValide,test_Methode)
{
	ASSERT_NO_THROW(myRegistreBorne.ajouteBorne(myBorneFontaine));
	ASSERT_NO_THROW(myRegistreBorne.ajouteBorne(myBorneStationnement));
	ASSERT_NO_THROW(myRegistreBorne.reqRegistreBorneFormate());
	std::ostringstream os;
	os << "Registre : bornes de la ville de Québec 2015" << std::endl<<
			"Borne fontaine" <<std::endl<<
			"-----------------------------------------------------------" <<std::endl<<
			"Identifiant de la borne	: 1"<<std::endl<<
			"Direction		: Sud"<<std::endl<<
			"Nom topographique	: 8800 24e Avenue"<<std::endl<<
			"Longitude		: 24"<<std::endl<<
			"Latitude		: 21.2"<<std::endl<<
			"Ville			: Quebec"<<std::endl<<
			"Arrondissement		: Ville Saint je sais pas"<<std::endl<<
			"-----------------------------------------------------------"<<std::endl<<
			"Borne de stationnement"<<std::endl<<
			"-----------------------------------------------------------"<<std::endl<<
			"Identifiant de la borne	: 2"<<std::endl<<
			"Direction		: Sud"<<std::endl<<
			"Nom topographique	: 8800 24e Avenue"<<std::endl<<
			"Longitude		: 24"<<std::endl<<
			"Latitude		: 21.2"<<std::endl<<
			"Distance mesuree	: 1234.3"<<std::endl<<
			"Segment de rue		: 387"<<std::endl<<
			"Numero de la borne	: 498"<<std::endl<<
			"Cote de la rue		: Nord"<<std::endl<<
			"-----------------------------------------------------------"<<std::endl;
	std::string result = os.str();
ASSERT_EQ(myRegistreBorne.reqRegistreBorneFormate(), result);

};

/*
 * \brief Test du constructeur Borne
 *	Cas valide : La Borne est bien créer et lance les exceptions lorsque nécessaire (Manque un champ ou une condition)
 *  Cas invalide : Une Exception est lancé lorsque non nécessaire, ou aucune exception n'est lancé lorsque nécessaire.
 */
TEST(RegistreBorne, test_Constructeur)
{
	ASSERT_NO_THROW(RegistreBorne myRegisreTest("my new registry"));
	ASSERT_THROW(RegistreBorne myRegisreTest(""),ContratException);
};

